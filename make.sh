#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --errexit --pipefail


# -- C O L O R S --------------------------------------------------------------

declare -rg success='\x1b[32m'
declare -rg error='\x1b[31m'
declare -rg warning='\x1b[33m'
declare -rg info='\x1b[34m'
declare -rg dim='\x1b[90m'
declare -rg reset='\x1b[0m'


# -- L O G O ------------------------------------------------------------------

echo $warning \
	'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n' \
	'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n' \
	' ╱         ╱         ╱         ╱         ╱\n' \
	'╱         ╱         ╱        ▁╱       ▁▁╱ \n' \
	'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱  \n' \
	$reset


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# get operating system
declare -rg os=$(uname -s)


# -- T H I S  S C R I P T -----------------------------------------------------

# get script absolute directory path
declare -rg cwd_dir=${${0%/*}:a}

# get script absolute path
declare -rg script=${0:a}


# -- T A R G E T S ------------------------------------------------------------

# project name
declare -rg project='void_engine'

# main executable
declare -rg executable=$cwd_dir'/'$project

# compile commands database
declare -rg compile_db=$cwd_dir'/compile_commands.json'

# ninja file
declare -rg ninja=$cwd_dir'/build.ninja'


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
declare -rg src_dir=$cwd_dir'/sources'

# include directory
declare -rg inc_dir=$cwd_dir'/include'

# shader directory
declare -rg sha_dir=$cwd_dir'/shaders'

# external directory
declare -rg ext_dir=$cwd_dir'/.external'

# ninja directory
declare -rg ninja_dir=$cwd_dir'/.ninja'

# git directory
declare -rg git_dir=$cwd_dir'/.git'


# -- F I L E S ----------------------------------------------------------------

# source files
local -r srcs=($src_dir'/'**'/'*'.cpp'(.N))

# object files
local -r objs=(${srcs/%.cpp/.o})


# -- V U L K A N --------------------------------------------------------------

# check for vulkan sdk environment variable
if [[ -z $VULKAN_SDK ]]; then

	# search for vulkan sdk versions
	local -r vulkan_versions=(~'/VulkanSDK/'*(/N))

	# check if vulkan sdk is installed
	[[ -z $vulkan_versions ]] && (echo $error'Vulkan SDK'$reset 'is not installed.'; exit 1)

	# get first version
	local version=$vulkan_versions[1]

	# loop over versions (if more than one)
	for ((i = 2; i <= ${#vulkan_versions}; ++i)); do

		# compare versions
		if [[ $vulkan_versions[i] > $version ]]; then
			version=$vulkan_versions[i]
		fi
	done

	# check if setup-env.sh exists
	if [[ ! -f $version'/setup-env.sh' ]]; then
		echo 'Vulkan' $error'setup-env.sh'$reset 'not found.'
		exit 1
	fi

	# source setup-env.sh
	if ! source $version'/setup-env.sh' > '/dev/null' 2>&1; then
		echo 'error while sourcing' $error'setup-env.sh'$reset
		exit 1
	fi

	# print success
	echo $success'[>]'$reset 'using Vulkan' $version:t
fi



# -- O S  D E P E N D E N C I E S ---------------------------------------------

# linux dependencies
if [[ $os =~ 'Linux' ]]; then
	local -r os_dependencies=('-lwayland-client' '-lX11' '-lXxf86vm' '-lXrandr' '-lpthread' '-lXi' '-ldl')

# macos dependencies
elif [[ $os =~ 'Darwin' ]]; then
	local -r os_dependencies=('-framework Cocoa' '-framework IOKit')
fi


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
local -r cxx='clang++'
#local -r cxx='/opt/homebrew/opt/llvm/bin/clang++'

# cxx flags
local -r cxxflags=('-std=c++2a' '-O0'
				   '-g3' #'-fsanitize=address' '-gdwarf-4'
				   '-DENGINE_VL_DEBUG'
				   '-Wall' '-Wextra' '-Werror' '-Wpedantic' '-Weffc++'
				   '-fno-rtti' '-Winline'
				   '-Wno-unused' '-Wno-unused-variable' '-Wno-unused-parameter'
				   '-Wno-unused-function' '-Wno-unused-private-field' '-Wno-unused-local-typedef'
				   '-Wconversion' '-Wsign-conversion' '-Wfloat-conversion' '-Wnarrowing'
				   '-fdiagnostics-color=always'
				   '-fno-diagnostics-show-note-include-stack'
				   '-fdiagnostics-show-location=once'
				   '-fdiagnostics-show-template-tree'
				   '-Wshadow'
				   '-Wno-gnu-anonymous-struct'
				   '-Wno-nested-anon-types'
				   '-I'$inc_dir
				   '-I'$VULKAN_SDK'/include'
				   '-I'$ext_dir'/glfw/include'
				   '-I'$ext_dir'/glm/include'
			   )

# linker flags
local -r ldflags=('-L'$VULKAN_SDK'/lib' '-lvulkan'
				  '-L'$ext_dir'/glfw/lib' '-lglfw3'
				  '-L'$ext_dir'/glm/lib' '-lglm'
				  $vulkan_library
				  $glfw_library
				  $glm_library
				  $os_dependencies
			  )
				#-fsanitize=address)


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
					   'clang++' 'glslc')
	
	# optional tools
	local -r optional=('ccache')

	# loop over required tools
	for tool in $required; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'required tool' $error$tool$reset 'not found.'
			exit 1
		fi
	done

	# loop over optional tools
	for tool in $optional; do

		# check if tool is available
		if ! command -v $tool > '/dev/null'; then
			echo 'optional tool' $warning$tool$reset 'not found.'
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
	local -r flags=('-DCMAKE_INSTALL_PREFIX='$prefix '-DCMAKE_BUILD_TYPE=Release' ${@:4})

	# return if already installed
	[[ -d $prefix ]] && return

	# create external and build directories
	mkdir -p $ext_dir $build

	# download if not present
	if [[ ! -f $archive ]]; then
		echo -n $success
		curl --progress-bar --location $url --output $archive
		echo -n $reset
	fi

	# extract
	tar --extract --strip-components=1 --file $archive --directory $repo

	# configure
	cmake -S $repo -B $build $flags -G 'Ninja'

	# build and install
	ninja -C $build install

	# cleanup
	rm -rf $repo $archive

	# print success
	echo $success'[+]'$reset $name $version
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

	if ! command -v ccache > '/dev/null'; then
		file+='cxx = '$cxx'\ncxxflags = '$cxxflags'\nldflags = '$ldflags'\n\n'
	else
		file+='cxx = ccache '$cxx'\ncxxflags = '$cxxflags'\nldflags = '$ldflags'\n\n'
	fi


	# -- rules ----------------------------------------------------------------

	file+='# -- R U L E S ----------------------------------------------------------------\n\n'

	file+='# rule to compile source files\n'
	file+='rule compile\n'
	file+='  command = $cxx $cxxflags -MT $out -MMD -MP -MF $out.d -c $in -o $out\n'
	file+='  description = compile $in\n'
	file+='  depfile = $out.d\n'
	file+='  deps = gcc\n\n'

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


	# -- executable -----------------------------------------------------------

	# link
	file+='# link\n'
	file+='build '$executable': $\n  link '$objs'\n\n'

	## all target
	file+='# all target\n'
	file+='build all: phony '$executable'\n\n'

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

	# use custom script to generate compile database
	#node $cwd_dir'/generate_cdb.js' $cwd_dir "$srcs" "$objs" "$cxx" "$cxxflags"

	# use ninja to generate compile database
	#ninja -f $ninja -t compdb > $compile_db


	local content='[\n'

	for file in $srcs; do

		# current directory
		content+='\t{\n\t\t"directory": "'$cwd_dir'",'

		# source file
		content+='\n\t\t"file": "'$file'",'

		# output file
		content+='\n\t\t"output": "'${file%.cpp}'.o",'

		# arguments
		content+='\n\t\t"arguments": [\n\t\t\t"'$cxx'",\n'

		# cxx flags
		for flag in $cxxflags; do
			content+='\t\t\t"'$flag'",\n'
		done

		# source file
		content+='\t\t\t"-c",\n\t\t\t"'$file'",\n'

		# output file
		content+='\t\t\t"-o",\n\t\t\t"'${file%.cpp}'.o"\n\t\t]\n\t},\n'
	done

	# erase last comma with newline
	content[-3]='\'
	content[-2]='n'
	content[-1]=']'

	# write to compile db
	if ! echo $content > $compile_db; then
		echo 'error while generating' $error'compile_commands.json'$reset
		exit 1
	fi

	# print success
	print $success'[+]'$reset ${compile_db:t}
}

# generate compile_commands.json
#define GENERATE_CDB
#CONTENT='[\n'
#for FILE in $(SRCS); do
#CONTENT+='\t{\n\t\t"directory": "'$$(pwd)'",\n\t\t"file": "'$$FILE'",\n\t\t"output": "'$${FILE%.cpp}.o'",\n\t\t"arguments": [\n\t\t\t"$(CXX)",\n'
#	for FLAG in $(CXXFLAGS); do
#		CONTENT+='\t\t\t"'$$FLAG'",\n'
#	done
#	CONTENT+='\t\t\t"-c",\n\t\t\t"'$$FILE'",\n\t\t\t"-o",\n\t\t\t"'$${FILE%.cpp}'.o"\n\t\t]\n\t},\n'
#done
#echo $${CONTENT%',\n'}'\n]' > $@
#endef

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

	# compile shaders
	$sha_dir'/make.sh'

	# generate ninja file
	_generate_ninja

	# generate compile database
	_compile_database

	# build
	_ninja
}


# clean
function _clean() {

	# clean shaders
	$sha_dir'/make.sh' 'rm'

	# remove all intermediate files
	local -r deleted=$(rm -rfv $objs $ninja $ninja_dir $compile_db | wc -l)

	# print success
	echo $info'[x]'$reset 'cleaned ('${deleted##* } 'files)'
}

# fclean
function _fclean() {

	# clean shaders
	$sha_dir'/make.sh' 'rm'

	# remove all build files
	local -r deleted=$(rm -rfv $objs $executable $ninja_dir $ninja $ext_dir $compile_db '.cache' | wc -l)

	# print success
	echo $info'[x]'$reset 'full cleaned ('${deleted##* } 'files)'
}


# -- M A I N ------------------------------------------------------------------


_check_tools
_repository

if [[ $# -eq 0 ]]; then
	_build
	exit
fi

# handle arguments
case $1 in

	# clean
	clean | clear | rm)
		_clean
		;;

	# fclean
	fclean | purge)
		_fclean
		;;

	# ninja
	ninja)
		touch $script
		_generate_ninja
		;;

	# lldb
	lldb)
		echo $VULKAN_SDK'/lib'
		install_name_tool -add_rpath $VULKAN_SDK'/lib' $executable && echo $success'[+]'$reset 'install_name_tool done'
		lldb $executable
		;;

	# gpu
	gpu)
		lspci | grep -i vga
		;;


	# unknown (usage)
	*)
		echo 'usage: '$script_name' [clean|fclean]'
		;;
esac
