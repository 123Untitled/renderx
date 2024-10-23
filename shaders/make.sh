#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --pipefail


# -- C O L O R S --------------------------------------------------------------

local -r success='\x1b[32m'
local -r error='\x1b[31m'
local -r warning='\x1b[33m'
local -r info='\x1b[34m'
local -r dim='\x1b[90m'
local -r reset='\x1b[0m'


# -- D I R E C T O R I E S ----------------------------------------------------

# script absolute directory
declare -r cwd_dir=${${0%/*}:a}

# source directory
declare -r src_dir=$cwd_dir'/sources'

# spir-v directory
declare -r spv_dir=$cwd_dir'/spir-v'


# -- F I L E S ----------------------------------------------------------------

# this script
declare -r script=${0:a}

# source files
declare -r srcs=($src_dir'/'**'/'*'.glsl'(.N))

# spir-v files
#declare -r spvs=(${glsls/%.glsl/.spv})


declare -r stages=(
	'vertex'
	'fragment'
	'compute'
	'geometry'
	'tessellation'
)

function _compile() {

	local count=0

	# loop over glsl files
	for file in $srcs; do

		local stage=${${file##$src_dir'/'}%%/*}
		local name=${${file##*/}%.*}
		local spv=$spv_dir'/'$stage'/'$name'.spv'

		if [[ -f $spv ]] && [[ $spv -nt $file ]] && [[ $spv -nt $script ]]; then
			continue
		fi

		if glslc -fshader-stage=$stage $file -o $spv; then
			echo -n $success'[✓]'$reset
			((++count))
		else
			echo -n $error'[x]'$reset
		fi
	done

	if (($count > 0)); then
		echo '\n'$count 'spir-v compiled.'
	else
		echo 'done.'
	fi
}

function _prepare() {

	# create directories
	for stage in $stages; do

		local dir=$spv_dir'/'$stage

		if [[ ! -d $dir ]]; then
			mkdir -p $dir
			echo $success'[+]'$reset ${dir:t}
		fi
	done
}


function _clean() {

	# remove all spir-v files
	local -r deleted=$(rm -vrf $spv_dir | wc -l)

	# print success
	echo $info'[x]'$reset 'cleaned ('${deleted##* } 'files)'
}


case $1 in
	clean)
		_clean
		;;
	fclean)
		_clean
		;;
	rm)
		_clean
		;;
	*)
		_prepare
		_compile
		;;
esac


# extract stage
# local stage=${sha:t:r:e}
