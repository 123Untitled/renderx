#!/usr/bin/env -S zsh --no-rcs --no-globalrcs


# -- V A R I A B L E S --------------------------------------------------------

# this script
declare -r script=$0

# directory of this script
declare -r cur_dir=${script:h}

# source directory
declare -r src_dir=$cur_dir'/sources'

# output directory
declare -r out_dir=$cur_dir'/spirv'

# shader source files
declare -r srcs=($src_dir'/'*'/'*'.glsl'(.N))

# compiler
declare -r glslc=$(which glslc)

# flags
declare -r flags='-fshader-stage='


# -- F U N C T I O N S --------------------------------------------------------

# compile function
function _compile() {

	# output file
	local src=$1
	local dir=${src:h:t}
	local out=$out_dir'/'$dir
	local spv=$out'/'${src:t:r}'.spv'

	mkdir -p $out

	# check if source file or this script is newer than output file
	if [[ -e $spv && $spv -nt $src && $spv -nt $script ]]; then
		continue
	fi

	if $glslc $flags$dir $src -o $spv; then
		echo '\x1b[90m[\x1b[33mspv\x1b[0m\x1b[90m]\x1b[0m' $dir'/'${spv:t}
	else
		echo '\x1b[32mfailed to compile' $dir'/'${src:t} '\x1b[0m'
		exit 1
	fi
}

# iterate function
function _iterate() {
	# loop over source files
	for src in $srcs; do
		_compile $src
	done
}


# -- E N T R Y P O I N T ------------------------------------------------------

# check if there is an argument
if [[ $# -eq 0 ]]; then
	_iterate
else
	if [[ $1 == 'clean' ]]; then
		rm -rfv $out_dir
	fi
fi

exit 0
