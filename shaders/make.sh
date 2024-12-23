#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --pipefail

# this script compiles glsl shader files to spir-v files


# -- C O L O R S --------------------------------------------------------------

local -r success='\x1b[32m'
local -r error='\x1b[31m'
local -r warning='\x1b[33m'
local -r info='\x1b[34m'
local -r dim='\x1b[90m'
local -r reset='\x1b[0m'


# -- A S C I I ----------------------------------------------------------------

#echo $success\
#' ▗▄▄▖▗▖ ▗▖ ▗▄▖ ▗▄▄▄ ▗▄▄▄▖▗▄▄▖  ▗▄▄▖\n'\
#'▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌  █▐▌   ▐▌ ▐▌▐▌   \n'\
#' ▝▀▚▖▐▛▀▜▌▐▛▀▜▌▐▌  █▐▛▀▀▘▐▛▀▚▖ ▝▀▚▖\n'\
#'▗▄▄▞▘▐▌ ▐▌▐▌ ▐▌▐▙▄▄▀▐▙▄▄▖▐▌ ▐▌▗▄▄▞▘\n'$reset




# -- D I R E C T O R I E S ----------------------------------------------------

# script absolute directory
declare -r cwd_dir=${${0%/*}:a}

# source directory
declare -r src_dir=$cwd_dir'/sources'

# include directory
declare -r inc_dir=$cwd_dir'/include'

# spir-v directory
declare -r spv_dir=$cwd_dir'/spir-v'


# -- F I L E S ----------------------------------------------------------------

# this script
declare -r script=${0:a}

# log file
declare -r log_file=$cwd_dir'/.log'

# source files
declare -r srcs=($src_dir'/'**'/'*'.glsl'(.N))

# dependency files
declare -r deps=(${srcs/%'.glsl'/'.d'})


# check for glsl files
if [[ ${#srcs[@]} -eq 0 ]]; then
	echo $error'[x]'$reset 'no glsl files found.'
	exit 1
fi


# -- C O M P I L E R ----------------------------------------------------------

# compiler
declare -r cc='glslc'

# language
declare -r lang='glsl'

# optimization
declare -r opt='0'

# standard
declare -r std='450'

# format
declare -r fmt='bin'

# environment
declare -r env='vulkan1.3'

# target
declare -r target='spv1.5'


# compiler flags
local -r cflags=('-x'$lang
				 '-O'$opt
				 '-Werror'
				 '-I'$inc_dir
				 '-mfmt='$fmt
				 '-std='$std
				 '--target-env='$env
				 '--target-spv='$target)


# -- F U N C T I O N S --------------------------------------------------------


# -- check tools --------------------------------------------------------------

function _check_tools() {

	# required tools
	local -r required=('glslc' 'mkdir' 'rm' 'echo')
	
	# loop over required tools
	for tool in $required; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'required tool' $error$tool$reset 'not found.'
			exit 1
		fi
	done
}


# -- need compilation ---------------------------------------------------------

function _need_compilation() {

	# $1: spir-v file
	# $2: dependency file

	# check if object or dependency file is missing
	if [[ ! -f $1 ]] || [[ ! -f $2 ]] || [[ $script -nt $1 ]]; then
		return 0
	fi

	# loop over words in dependency file
	for word in ${=$(<$2)}; do

		# check if word is not target or escape
		if [[ $word != '\' ]] && [[ $word != *':' ]]; then

			# check if dependency is missing
			[[ $word -nt $1 ]] && return 0
		fi
	done

	# no need to compile
	return 1
}


# -- compile ------------------------------------------------------------------

function _compile() {

	# count of compiled files
	local -i count=0

	# loop over glsl files
	for file in $srcs; do

		# extract stage
		local stage='-fshader-stage='${file:t:r:e}

		# create spir-v path
		local spv=$spv_dir'/'${file:t:r}'.spv'

		# create dependency path
		local dep=${file:r}'.d'

		# check if need compilation
		_need_compilation $spv $dep || continue

		# compile glsl to spir-v
		if $cc $stage $cflags -MD -MF $dep -MT $spv -o $spv $file &> $log_file; then
			echo -n '\r\x1b[2K'$info'[✓]'$reset ${file:t}
			count=$((++count))
			continue
		fi

		echo $error'[x]'$reset ${file:t}
		local -r log_content=$(<$log_file)
		echo ${log_content#$file:}
		exit 1
	done

	# print success
	if [[ $count -gt 0 ]]; then
		echo '\r\x1b[2K'$success'[+]'$reset $count 'spir-v compiled.'
	else
		echo $success'[>]'$reset 'shaders are up to date.'
	fi
}


# -- prepare ------------------------------------------------------------------

function _prepare() {

	# create folder
	if ! mkdir -p $spv_dir; then
		echo 'failed to create spir-v directory.'
	fi
}


# -- clean --------------------------------------------------------------------

# clean generated files
function _clean() {

	# remove all spir-v files
	local -r deleted=($(rm -vrf $spv_dir $deps $log_file))

	# number of deleted files
	local -r count=${#deleted[@]}

	if [[ $count -eq 0 ]]; then
		echo $info'[>]'$reset 'nothing to clean.'
		return
	fi

	# print success
	echo $info'[x]'$reset $count 'files deleted.'
}



# -- build --------------------------------------------------------------------

function _build() {

	# check required tools
	_check_tools

	# prepare spir-v directory
	_prepare

	# compile glsl files
	_compile
}


# -- M A I N ------------------------------------------------------------------

case $1 in

	clean | clear | fclean | rm)
		_clean
		;;
	*)
		_build
		;;
esac
