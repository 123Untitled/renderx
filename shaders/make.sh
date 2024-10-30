#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --pipefail

# this script compiles directx shader files to spir-v files


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




# -- H L S L ------------------------------------------------------------------

# function to check required tools
function _check_tools() {

	# required tools
	local -r required=('slangc' 'glslc' 'dxc')
	
	# loop over required tools
	for tool in $required; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'required tool' $error$tool$reset 'not found.'
			exit 1
		fi
	done
}

# need compilation
function _need_compilation() {

	# source file: $1
	# spir-v file: $2

	if [[ -f $2 ]] && [[ $2 -nt $1 ]] && [[ $2 -nt $script ]]; then
		return 1
	fi

	return 0
}


function _compile_hlsl() {

	# source files
	local -r srcs=($src_dir'/'**'/'*'.hlsl'(.N))

	# count of compiled files
	local count=0

	# compiler
	local -r cc='dxc'

	# dxcflags
	local dxcflags=('-E' 'main'
					 '-fdiagnostics-format=clang'
					 '-HV' '2021'
					 '-I'$inc_dir
					 '-WX'
					 '-Zi'
					 '-O0'
					 '-spirv'
					 '-fspv-entrypoint-name=' 'main'
					 '-fspv-target-env=vulkan1.2'
					 '-fspv-use-legacy-buffer-matrix-order'
				 )

					 #'-fspv-use-vulkan-memory-model'
					 #'-fspv-use-dx-layout'

	local -A profiles

	# vertex shader profile
	profiles[vs]='vs_6_8'
	# pixel shader profile
	profiles[ps]='ps_6_8'
	# hull shader profile
	profiles[hs]='hs_6_8'
	# domain shader profile
	profiles[ds]='ds_6_8'
	# geometry shader profile
	profiles[gs]='gs_6_8'
	# compute shader profile
	profiles[cs]='cs_6_8'


	# loop over glsl files
	for file in $srcs; do

		# file have this pattern: 'filename.[vs|ps|hs|ds|gs|cs].hlsl'

		# extract stage
		local stage=${file:t:r:e}

		# check if shader type is valid
		if [[ ! -v profiles[$stage] ]]; then
			echo 'invalid shader type' $stype
			continue
		fi

		# create spir-v path
		local spv=$spv_dir'/'${file:t:r}'.spv'

		# check if need compilation
		_need_compilation $file $spv || continue


		if $cc '-T' $profiles[$stage] $dxcflags $file -Fo $spv; then
			echo -n $success'[✓]'$reset
			count=$((count + 1))
		else
			echo -n $error'[x]'$reset
			break
		fi
	done

	# print success
	if [[ $count -gt 0 ]]; then
		echo '\n'$info'[>]'$reset $count 'spir-v compiled.'
	fi
}


function _compile_glsl() {

	# source files
	local -r srcs=($src_dir'/'**'/'*'.glsl'(.N))

	# count of compiled files
	local count=0

	# compiler
	local -r cc='glslc'

	# glslc flags
	local -r glflags=('-x' 'glsl' '-Werror' '-O0'
					  '-mfmt=bin'
					  '-std=450'
					  '--target-env=vulkan1.3'
					  '--target-spv=spv1.5'
				)

	# loop over glsl files
	for file in $srcs; do

		# file have this pattern: 'filename.[vert|frag|tesc|tese|geom|comp].glsl'

		# extract shader type
		local stype=${file:t:r:e}

		# create spir-v path
		local spv=$spv_dir'/'${file:t:r}'.spv'

		# check if need compilation
		_need_compilation $file $spv || continue

		if $cc '-fshader-stage='$stype $glflags $file -o $spv; then
			echo -n $success'[✓]'$reset
			count=$((count + 1))
		else
			echo -n $error'[x]'$reset
			break
		fi
	done

	# print success
	if [[ $count -gt 0 ]]; then
		echo '\n'$info'[>]'$reset $count 'spir-v compiled.'
	fi
}



function _prepare() {

	# create folder
	if ! mkdir -p $spv_dir; then
		echo 'failed to create spir-v directory.'
	fi
}

function _clean() {

	# remove all spir-v files
	local -r deleted=$(rm -vrf $spv_dir | wc -l)

	# print success
	echo $info'[x]'$reset 'cleaned ('${deleted##* } 'files)'
}


# -- M A I N ------------------------------------------------------------------

# check required tools
_check_tools

# prepare spir-v directory
_prepare

case $1 in

	clean|clear|fclean|rm)
		_clean
		;;
	slang)
		echo 'not implemented yet.'
		;;
	glsl)
		_compile_glsl
		;;
	hlsl)
		_compile_hlsl
		;;
	*)
		_compile_glsl
		_compile_hlsl
		;;
esac


