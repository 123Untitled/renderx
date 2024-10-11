#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --errexit --pipefail


# -- C O L O R S --------------------------------------------------------------

local -r success='\x1b[32m'
local -r error='\x1b[31m'
local -r warning='\x1b[33m'
local -r info='\x1b[34m'
local -r dim='\x1b[90m'
local -r reset='\x1b[0m'


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# get operating system
local -r os=$(uname -s)


# -- T H I S  S C R I P T -----------------------------------------------------

# get script absolute directory path
local -r cwd_dir=${0%/*}

#local -r cwd_dir=${${0%/*}:a}

# get script absolute path
local -r script=${0:a}


# -- T A R G E T S ------------------------------------------------------------

# project name
local -r project='renderx'

# main executable
local -r executable=$cwd_dir'/'$project

# compile commands database
local -r compile_db=$cwd_dir'/compile_commands.json'

# ninja file
local -r ninja=$cwd_dir'/build.ninja'


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
local -r src_dir=$cwd_dir'/sources'

# include directory
local -r inc_dir=$cwd_dir'/include'

# shader directory
local -r sha_dir=$cwd_dir'/shaders'

# external directory
local -r ext_dir=$cwd_dir'/.external'

# ninja directory
local -r ninja_dir=$cwd_dir'/.ninja'

# git directory
local -r git_dir=$cwd_dir'/.git'


# -- F I L E S ----------------------------------------------------------------

# source files
local -r srcs=($src_dir'/'**'/'*'.cpp'(.N))

# object files
local -r objs=(${srcs/%.cpp/.o})

# shader files
local -r shas=($sha_dir'/'*'.glsl'(.N))

# spirv files
local -r spvs=(${shas/%.glsl/.spv})


# -- V U L K A N --------------------------------------------------------------

# check for vulkan
if [[ -z $VULKAN_SDK ]]; then

	# search for vulkan sdk
	local -r setup=(~'/VulkanSDK/'**'/setup-env.sh'(.N))

	# check if found
	[[ -z $setup ]] && (echo $error'Vulkan SDK not installed'$reset; exit 1)

	# warn to source vulkan sdk
	echo 'required Vulkan SDK found at:' $warning$setup$reset
fi

# vulkan include
local -r vulkan_include='-I'$VULKAN_SDK'/include'

# vulkan library
local -r vulkan_library=('-L'$VULKAN_SDK'/lib' '-lvulkan')


# -- G L F W ------------------------------------------------------------------

# glfw include
local -r glfw_include='-I'$ext_dir'/glfw/include'

# glfw library
local -r glfw_library=('-L'$ext_dir'/glfw/lib' '-lglfw3')


# -- G L M --------------------------------------------------------------------

# glm include
local -r glm_include='-I'$ext_dir'/glm/include'

# glm library
local -r glm_library=('-L'$ext_dir'/glm/lib' '-lglm')


# -- O S  D E P E N D E N C I E S ---------------------------------------------

# linux dependencies
if [[ $os =~ 'Linux' ]]; then
	local -r os_dependencies=('-lX11' '-lXxf86vm' '-lXrandr' '-lpthread' '-lXi' '-ldl')

# macos dependencies
elif [[ $os =~ 'Darwin' ]]; then
	local -r os_dependencies=('-framework Cocoa' '-framework IOKit')
fi


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
local -r cxx='clang++'

# cxx flags
local -r cxxflags=('-std=c++2a'
				   '-O0'
				   '-g2'
				   '-DENGINE_VL_DEBUG'
				   '-Wall'
				   '-Wextra'
				   '-Werror'
				   '-fno-rtti'
				   '-Wpedantic'
				   '-Weffc++'
				   '-Wno-unused'
				   '-Wno-unused-variable'
				   '-Wno-unused-parameter'
				   '-Wno-unused-function'
				   '-Wno-unused-private-field'
				   '-Wno-unused-local-typedef'
				   '-fdiagnostics-color=always'
				   '-Winline'
				   '-Wconversion'
				   '-Wsign-conversion'
				   '-Wfloat-conversion'
				   '-Wnarrowing'
				   '-Wshadow'
				   '-I'$inc_dir
				   $vulkan_include
				   $glfw_include
				   $glm_include)

# linker flags
local -r ldflags=($vulkan_library $glfw_library $glm_library $os_dependencies)


# -- F U N C T I O N S --------------------------------------------------------

# check we are in the correct repository
function _repository() {

	# local variables
	local -r ssh_repo='git@github.com:123Untitled/renderx.git'
	local -r pub_repo='https://github.com/123Untitled/renderx.git'

	# check we are in a git repository
	if [[ ! -d $git_dir ]]; then
		echo 'please run this script in the' $error$project$reset 'repository.'
		exit 1
	fi

	# get the git remote url
	local -r remote=$(git --git-dir=$git_dir config --get 'remote.origin.url')

	# check we are in the correct repository
	if [[ $remote != $ssh_repo ]] && [[ $remote != $pub_repo ]]; then
		echo 'please run this script in the' $error$project$reset 'repository.'
		exit 1
	fi
}

# function to check required tools
function _check_tools() {

	# required tools
	local -r required=('uname' 'git' 'curl' 'tar'
					   'cmake' 'ninja' 'rm' 'mkdir' 'wc'
					   'ccache' 'clang++' 'glslc')

	# loop over required tools
	for tool in $required; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'required tool' $error$tool$reset 'not found.'
			exit 1
		fi
	done
}

# install dependency
function _install_dependency() {

	# library name
	local -r name=$1

	# version
	local -r version=$2

	# github url
	local -r url='https://github.com/'$3'/'$name'/archive/refs/tags/'$version'.tar.gz'

	# archive path
	local -r archive=$cwd_dir'/'$name'.tar.gz'

	# repo directory
	local -r repo=$cwd_dir'/'$name

	# build directory
	local -r build=$repo'/build'

	# install prefix
	local -r prefix=$ext_dir'/'$name

	# cmake flags
	local -r flags=('-DCMAKE_INSTALL_PREFIX='$prefix ${@:4})

	# return if already installed
	[[ -d $prefix ]] && return

	# create external and build directories
	mkdir -p $ext_dir $build

	# download if not present
	if [[ ! -f $archive ]]; then
		curl --progress-bar --location $url --output $archive
	fi

	# extract
	tar --extract --strip-components=1 --file $archive --directory $repo

	# configure
	cmake -S $repo -B $build $flags -G 'Ninja'

	# build and install
	ninja -C $build install

	# cleanup
	rm -rf $repo $archive
}


# generate ninja file
function _generate_ninja() {

	# check ninja file exists and is up to date
	[[ -f $ninja ]] && [[ $ninja -nt $script ]] && return

	# file content
	local file='\n'


	# -- logo -----------------------------------------------------------------

	file+='# -----------------------------------------------------------------------------\n'
	file+='# ░▒▓███████▓▒░░▒▓█▓▒░▒▓███████▓▒░       ░▒▓█▓▒░░▒▓██████▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░▒▓████████▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░\n'
	file+='# ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░\n'
	file+='# -----------------------------------------------------------------------------\n\n'


	# minimal version
	file+='# minimal version of Ninja required by this file\n'
	file+='ninja_required_version = 1.10\n\n'

	# build directory
	file+='# build directory\n'
	file+='builddir = '$ninja_dir'\n\n'

	file+='# ninja file\n'
	file+='ninja = '$ninja'\n\n'
	file+='# compiler and flags\n'
	file+='cxx = ccache '$cxx'\ncxxflags = '$cxxflags'\nldflags = '$ldflags'\n\n'


	# -- rules ----------------------------------------------------------------

	file+='# -- R U L E S ----------------------------------------------------------------\n\n'

	file+='# rule to compile source files\n'
	file+='rule compile\n'
	file+='  command = $cxx $cxxflags -MT $out -MMD -MP -MF $out.d -c $in -o $out\n'
	file+='  description = compile $in\n'
	file+='  depfile = $out.d\n'
	file+='  deps = gcc\n\n'

	file+='# rule to compile shaders\n'
	file+='rule shader\n'
	file+='  command = glslc -fshader-stage=$stage $in -o $out\n'
	file+='  description = shader $stage\n\n'

	file+='# rule to link object files\n'
	file+='rule link\n  command = $cxx $in -o $out $ldflags\n  description = link $out\n\n\n'



	# -- builds ---------------------------------------------------------------

	file+='# -- B U I L D S --------------------------------------------------------------\n\n'


	# -- sources --------------------------------------------------------------

	# loop over source files
	for ((i = 1; i <= $#srcs; ++i)); do
		file+='# compile '${srcs[$i]:t:r}'\n'
		file+='build '$objs[$i]': $\n  compile '$srcs[$i]' | $ninja\n\n'
	done


	# -- shaders --------------------------------------------------------------

	# loop over shader files
	for ((i = 1; i <= $#shas; ++i)); do

		# shader file
		local sha=${shas[$i]}

		# output file
		local spv=${spvs[$i]}

		# extract stage
		local stage=${sha:t:r:e}

		file+='# shader '${sha:t:r}'\n'
		file+='build '$spv': $\n  shader '$sha' | $ninja\n'
		file+='  stage = '$stage'\n\n'
	done



	# -- executable -----------------------------------------------------------

	# link
	file+='# link\n'
	file+='build '$executable': $\n  link '$objs'\n\n'

	## all target
	file+='# all target\n'
	file+='build all: phony '$executable' $\n'$spvs'\n\n'

	# default target
	file+='# default target\n'
	file+='default all'

	# create ninja directory
	mkdir -p $ninja_dir

	# write to ninja file
	echo $file > $ninja

	# print success
	print $success'[+]'$reset ${ninja:t}
}


# ninja
function _ninja() {
	ninja -f $ninja
}

# install dependencies
function _install_dependencies() {

	# install ninja
	#_install_dependency 'ninja' 'v1.12.1' 'ninja-build' '-DBUILD_TESTING=OFF' \
	#													'-DCMAKE_BUILD_TYPE=Release' \
	#													'-DNINJA_BUILD_BINARY=ON'

	# install glfw
	_install_dependency 'glfw' '3.4' 'glfw' '-DBUILD_SHARED_LIBS=OFF' \
											'-DGLFW_LIBRARY_TYPE=STATIC' \
											'-DGLFW_BUILD_EXAMPLES=OFF' \
											'-DGLFW_BUILD_TESTS=OFF' \
											'-DGLFW_BUILD_DOCS=OFF'

	# install glm
	_install_dependency 'glm' '1.0.1' 'g-truc' '-DBUILD_SHARED_LIBS=OFF' \
											   '-DGLM_BUILD_TESTS=OFF'

}

# generate compile database
function _generate_compile_db() {

	# use ninja to generate compile database
	ninja -f $ninja -t compdb > $compile_db

	# print success
	print $success'[+]'$reset ${compile_db:t}
}

# compile db
function _compile_database() {

	# check compile db exists and is up to date
	if [[ ! -f $compile_db ]] || [[ $compile_db -ot $script ]]; then
		_generate_compile_db
		return
	fi

	# loop over source files
	for src in $srcs; do

		# check if src is newer than compile db
		if [[ $src -nt $compile_db ]]; then
			_generate_compile_db
			break
		fi

	done
}


# build
function _build() {

	# install dependencies
	_install_dependencies

	# generate ninja file
	_generate_ninja

	# generate compile database
	_compile_database

	# build
	_ninja
}


# clean
function _clean() {

	# remove all intermediate files
	local -r deleted=$(rm -rfv $objs $spvs | wc -l)

	# print success
	echo $info'[x]'$reset 'full cleaned ('${deleted##* } 'files)'
}

# fclean
function _fclean() {

	# remove all build files
	local -r deleted=$(rm -rfv $objs $spvs $ninja_dir $ninja $ext_dir $compile_db '.cache' | wc -l)

	# print success
	echo $info'[x]'$reset 'full cleaned ('${deleted##* } 'files)'
}


# -- M A I N ------------------------------------------------------------------

echo $warning \
	'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n' \
	'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n' \
	' ╱         ╱         ╱         ╱         ╱\n' \
	'╱         ╱         ╱        ▁╱       ▁▁╱ \n' \
	'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱  \n' \
	$reset

_check_tools
_repository

if [[ $# -eq 0 ]]; then
	_build
	exit
fi

# handle arguments
case $1 in

	# clean
	clean)
		_clean
		;;

	# fclean
	fclean)
		_fclean
		;;

	# unknown (usage)
	*)
		echo 'usage: '$script_name' [clean|fclean]'
		;;
esac
