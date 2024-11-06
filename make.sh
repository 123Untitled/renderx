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


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
declare -rg src_dir=$cwd_dir'/sources'

# include directory
declare -rg inc_dir=$cwd_dir'/include'

# shader directory
declare -rg sha_dir=$cwd_dir'/shaders'

# external directory
declare -rg ext_dir=$cwd_dir'/.external'

# git directory
declare -rg git_dir=$cwd_dir'/.git'


# -- F I L E S ----------------------------------------------------------------

# source files
declare -rg srcs=($src_dir'/'**'/'*'.cpp'(.N))

# object files
declare -rg objs=(${srcs/%.cpp/.o})

# dependency files
declare -rg deps=(${objs/%.o/.d})


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
	local -r os_dependencies=('-framework' 'Cocoa' '-framework' 'IOKit')
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
				   '-ferror-limit=1'
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
					   'cmake' 'rm' 'mkdir' 'wc'
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


# -- C O M P I L E  D A T A B A S E -------------------------------------------

# generate compile database
function _generate_compile_db() {

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



# -- C O M P I L A T I O N ----------------------------------------------------

function _check_dependency {
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
	return 1
}


function _handle_compilation {

	# $1 source file
	# $2 object file
	# $3 dependency file

	if command -v ccache > '/dev/null'; then
		ccache $cxx $cxxflags -MT $2 -MMD -MF $3 -c $1 -o $2
	else
		$cxx $cxxflags -MT $2 -MMD -MF $3 -c $1 -o $2
	fi
	# compile source file

	# check if compilation failed
	if [[ $? -ne 0 ]]; then
		echo -n $error'[x]'$reset
		exit 1
	fi

	echo -n '\r\x1b[2K'$success'[✓]'$reset ${1:t}
	exit 0
}

declare -g max_jobs=''
if [[ $os =~ 'Darwin' ]]; then
	max_jobs=$(sysctl -n hw.ncpu)
elif [[ $os =~ 'Linux' ]]; then
	max_jobs=$(nproc)
fi



function _wait_processes {

	# loop over pids
	for pid in $1; do
		# wait for pid
		wait $pid
		# check if compilation failed
		if [[ $? -ne 0 ]]; then
			wait
			exit 1
		fi
	done
}


function _compile {

	# number of compiled files
	local count=0

	# array of pids
	local pids=()

	# loop over source files
	for src in $srcs; do

		# add object file extension
		local obj=${src%.cpp}'.o'

		# add dependency file extension
		local dep=${src%.cpp}'.d'

		# check if source file is modified
		if ! _check_dependency $obj $dep; then
			continue
		fi

		if [[ ${#pids[@]} -eq $max_jobs ]]; then
			_wait_processes $pids
			pids=()
		fi

		count=$((count + 1))

		_handle_compilation $src $obj $dep &

		pids+=($!)
	done

	# wait for remaining pids
	_wait_processes $pids

	if [[ $count -eq 0 ]]; then
		echo $info'[>]'$reset 'nothing to compile'
	else
		echo '\r\x1b[2K'$info'[+]'$reset 'compiled' $count 'files'
	fi
}


# -- L I N K  F U N C T I O N S -----------------------------------------------


function _link {

	# loop over object files
	for obj in $objs; do

		# check if object file is newer than target
		if [[ $obj -nt $executable ]]; then

			# link object files
			if $cxx $objs '-o' $executable $ldflags; then
				echo $success'[+]'$reset 'linked' ${executable:t}
			else
				echo $error'[x]'$reset 'linking failed'
				exit 1
			fi
			return
		fi
	done

	echo $info'[>]'$reset ${executable:t} 'is up to date'
}



# build
function _build() {

	# install dependencies
	_install_dependencies

	# compile shaders
	$sha_dir'/make.sh'

	# generate compile database
	_compile_database

	# build
	_compile
	_link
}


# clean
function _clean() {

	# clean shaders
	$sha_dir'/make.sh' 'rm'

	# remove all intermediate files
	local -r deleted=$(rm -rfv $objs $deps $compile_db | wc -l)

	# print success
	echo $info'[x]'$reset 'cleaned ('${deleted##* } 'files)'
}

# fclean
function _fclean() {

	# clean shaders
	$sha_dir'/make.sh' 'rm'

	# remove all build files
	local -r deleted=$(rm -rfv $objs $deps $executable $ext_dir $compile_db '.cache' | wc -l)

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
