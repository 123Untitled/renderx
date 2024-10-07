#!/usr/bin/env -S zsh --no-rcs --no-globalrcs

# library name
declare -r lib_name='glm'

# target directory
declare -r target_dir=$(pwd)'/external/'$lib_name

# repository url
declare -r repo_url='https://github.com/g-truc/glm.git'

# repository directory
declare -r repo_dir=$(pwd)'/'$lib_name

# build directory
declare -r build_dir=$repo_dir'/build'



# check if the repository is already cloned
if [[ ! -d $repo_dir ]]; then
	# clone the repository
	if ! git clone $repo_url $repo_dir; then
		echo 'failed to clone the repository'
		exit 1
	fi
fi

# create directories
if ! mkdir -p $target_dir $build_dir; then
	echo 'failed to create directories'
	exit 1
fi


declare -r cmake_flags=(
	'-DGLM_BUILD_TESTS=OFF'
	'-DBUILD_SHARED_LIBS=OFF'
	'-DCMAKE_INSTALL_PREFIX='$target_dir
)

# prepare the build
if ! cmake -S $repo_dir -B $build_dir $cmake_flags; then
	echo 'failed to prepare the build'
	exit 1
fi

# build the library
if ! cmake --build $build_dir --config Release -- all; then
	echo 'failed to build the library'
	exit 1
fi

# install the library
if ! cmake --build $build_dir --config Release -- install; then
	echo 'failed to install the library'
	exit 1
fi

# cleanup
if ! rm -rf $repo_dir; then
	echo 'failed to cleanup'
	exit 1
fi
