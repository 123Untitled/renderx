#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --pipefail

# this script compiles slangs to spir-v


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

# include directory
declare -r inc_dir=$cwd_dir'/include'

# spir-v directory
declare -r spv_dir=$cwd_dir'/spir-v'


# -- F I L E S ----------------------------------------------------------------

# this script
declare -r script=${0:a}

# source files
declare -r srcs=($src_dir'/'**'/'*'.sl'(.N))



# -- C O M P I L E R ----------------------------------------------------------

# lang
declare -r lang='slang'

# target
declare -r target='spirv'

# entry
declare -r entry='main'

# profile
declare -r profile='spirv_1_5'

# debug
declare -r debug='-gmaximal'

# optimization
declare -r optimization='-O0'


# slflags
declare -r slflags=('-lang'    $lang
					'-target'  $target
					'-entry'   $entry
					'-profile' $profile
					'-I'$inc_dir
					$debug
					$optimization)




# function to check required tools
function _check_tools() {

	# required tools
	local -r required=('slangc')
	
	# loop over required tools
	for tool in $required; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'required tool' $error$tool$reset 'not found.'
			exit 1
		fi
	done
}

function _compile() {

	local -r file=$1
	local -r spv=$2

	if [[ -f $spv ]] && [[ $spv -nt $file ]] && [[ $spv -nt $script ]]; then
		exit 0
	fi

	if slangc $slflags $file -o $spv; then
		echo -n $success'[✓]'$reset
		exit 1
	else
		echo -n $error'[x]'$reset
		exit 2
	fi
}

function _handle_compilation() {

	# count of compiled files
	local count=0

	# exit status
	local state=''

	# pid array
	local pids=()
	local nprocesses=0

	local max_jobs=8


	# loop over glsl files
	for file in $srcs; do

		# compile file
		_compile $file $spv_dir'/'${file:t:r}'.spv' &

		# append pid to pids
		pids+=($!)
		# increment nprocesses
		nprocesses=$((++nprocesses))

		if [[ $nprocesses -eq $max_jobs ]]; then
			nprocesses=0
			wait
		fi
	done


	# loop over pids
	for pid in $pids; do
		# wait for pid
		wait $pid
		# get exit status
		state=$?

		# check if compilation failed
		if [[ $state -eq 2 ]]; then
			wait
			echo $error'failed to compile spir-v.'$reset
			exit 1

		elif [[ $state -eq 1 ]]; then
			count=$((++count))
		fi
	done

	# print success
	if [[ $count -gt 0 ]]; then
		echo $success'[✓]'$reset $count 'spir-v compiled.'
	fi
}




function _prepare() {

	# append spir-v directory to directories
	local directories=($spv_dir)

	# create directories
	if ! mkdir -p $directories; then
		echo $error'[x]'$reset 'failed to create directories.'
	fi
}


function _clean() {

	# remove all spir-v files
	local -r deleted=$(rm -vrf $spv_dir | wc -l)

	# print success
	echo $info'[x]'$reset 'cleaned ('${deleted##* } 'files)'
}


case $1 in
	clean|clear|fclean|rm)
		_clean
		;;
	*)
		_prepare
		_handle_compilation
		;;
esac


