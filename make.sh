#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --errexit --pipefail


local -r success='\x1b[32m'
local -r error='\x1b[31m'
local -r warning='\x1b[33m'
local -r info='\x1b[34m'
local -r reset='\x1b[0m'


echo $info \
	'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n' \
	'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n' \
	' ╱         ╱         ╱         ╱         ╱\n' \
	'╱         ╱         ╱        ▁╱       ▁▁╱ \n' \
	'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱  \n' \
	$reset



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# get operating system
local -r os=$(uname -s)


# -- T H I S  S C R I P T -----------------------------------------------------

# get current absolute directory path
local -r cwd_dir='.'
#$(pwd -P)

# get script absolute directory path
local -r script_dir=${${0%/*}:a}

# get script absolute path
local -r script=${0:a}

# script name
local -r script_name=${0##*/}


# -- T A R G E T S ------------------------------------------------------------

# project name
local -r project='renderx'

# main executable
local -r executable=$project

# compile commands database
local -r compile_db='compile_commands.json'

# ninja file
local -r ninja='build.ninja'


# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
#local -r cwd_dir='.'

# source directory
local -r src_dir=$cwd_dir'/sources'

# include directory
local -r inc_dir=$cwd_dir'/include'

# shader directory
local -r sha_dir=$cwd_dir'/shaders'

# external directory
local -r ext_dir=$cwd_dir'/external'

# spirv directory
local -r spv_dir=$cwd_dir'/spirv'


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
local -r cxx='ccache clang++'

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

# install dependency
function _install_dependency() {

	# library name
	local -r libname=$1

	# version
	local -r version=$2

	# archive path
	local -r archive=$libname'.tar.gz'

	# github url
	local -r url='https://github.com/'$3'/'$libname'/archive/refs/tags/'$version'.tar.gz'

	# repository path
	local -r repo=$libname'-'$version

	# build directory
	local -r build=$repo'/build'

	# install prefix
	local -r prefix=$ext_dir'/'$libname

	# cmake flags
	local -r flags=('-DCMAKE_INSTALL_PREFIX='$prefix ${@:4})

	# return if already installed
	[[ -d $prefix ]] && return

	# create external directory
	mkdir -p $ext_dir

	# download if not present
	if [[ ! -f $archive ]]; then
		curl --progress-bar --location $url --output $archive
	fi

	# extract
	tar --extract --verbose --file $archive

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

	local file=''

	file+='# Minimal version of Ninja required by this file\n'
	file+='ninja_required_version = 1.10\n\n'

	file+='cxx = '$cxx'\ncxxflags = '$cxxflags'\nldflags = '$ldflags'\n\n'

	file+='rule compile\n'
	file+='  command = $cxx $cxxflags -MT $out -MMD -MP -MF $out.d -c $in -o $out\n'
	file+='  description = compile $in\n'
	file+='  depfile = $out.d\n'
	file+='  deps = gcc\n\n'

	file+='rule link\n  command = $cxx $in -o $out $ldflags\n  description = link $out\n\n'

	for ((i = 1; i <= $#srcs; ++i)); do
		file+='# compile '${srcs[$i]:t:r}'\n'
		file+='build '$objs[$i]': compile '$srcs[$i]' | '$ninja'\n\n'
	done

	file+='build '$executable': link '$objs'\n\n'



	# -- shaders --------------------------------------------------------------

	file+='# rule to compile shaders\n'
	file+='rule shader\n'
	file+='  command = glslc -fshader-stage=$stage $in -o $out\n'
	file+='  description = shader $in\n\n'



	# loop over shader files
	for ((i = 1; i <= $#shas; ++i)); do

		# shader file
		local sha=${shas[$i]}

		# output file
		local spv=${spvs[$i]}

		# extract stage
		local stage=${sha:t:r:e}

		file+='# shader '${sha:t:r}'\n'
		file+='build '$spv': shader '$sha' | '$ninja'\n'
		file+='  stage = '$stage'\n\n'
	done


	# all target
	file+='build all: phony '$executable' '$spvs'\n'

	file+='default all\n'



	echo $file > $ninja

	# print success
	print $success'[+]'$reset $ninja
}

# ninja
function _ninja() {
	ninja -f $ninja
}

# install dependencies
function _install_dependencies() {

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


	echo -n '[\n' > $compile_db

	# loop over source files
	for ((i = 1; i <= $#srcs; ++i)); do

		# new entry
		local entry=('\t{\n'
					 '\t\t"directory": "'$cwd_dir'",\n'
					 '\t\t"file": "'$srcs[$i]'",\n'
					 '\t\t"output": "'$objs[$i]'",\n'
					 '\t\t"arguments": [\n'
					 '\t\t\t"'$cxx'",\n'
					 '\t\t\t"-c",\n'
					 '\t\t\t"'$srcs[$i]'",\n'
					 '\t\t\t"-o",\n'
					 '\t\t\t"'$objs[$i]'",\n')

		# loop over compiler flags
		for flag in $cxxflags; do
			entry+=('\t\t\t"'$flag'",\n')
		done

		if [[ $i -lt $#srcs ]]; then
			entry+=('\t\t]\n\t},\n')
		else
			entry+=('\t\t]\n\t}\n')
		fi

		echo -n $entry >> $compile_db

	done

	echo -n ']' >> $compile_db

	# print success
	print $success'[+]'$reset $compile_db

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

	# build shaders
	#$sha_dir'/make.sh'

	# build
	_ninja
}


# clean
function _clean() {
	_generate_ninja
	ninja -f $ninja -t clean
	#$sha_dir'/make.sh' clean
}

# fclean
function _fclean() {
	_clean
	rm -rvf $ninja '.ninja'*(.N) $ext_dir $compile_db '.cache'
}


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

	*)
		echo 'usage: '$script_name' [clean|fclean]'
		;;
esac
