#!/usr/bin/env -S zsh --no-rcs --no-globalrcs


# library name
declare -r lib_name='sdl'

# target directory
declare -r target_dir=$(pwd)'/external/'$lib_name

# repository url
declare -r repo_url='https://github.com/libsdl-org/SDL.git'

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


# sdl subsystems
declare -r cmake_flags_subsystems=(
	'-DSDL_VIDEO=ON'
	'-DSDL_AUDIO=OFF'
	'-DSDL_GPU=OFF'
	'-DSDL_RENDER=OFF'
	'-DSDL_CAMERA=OFF'
	'-DSDL_JOYSTICK=OFF'
	'-DSDL_HAPTIC=OFF'
	'-DSDL_HIDAPI=ON' # off generate compile error
	'-DSDL_POWER=OFF'
	'-DSDL_SENSOR=OFF'
	'-DSDL_DIALOG=OFF'

	'-DSDL_VULKAN=ON'
	'-DSDL_RENDER_VULKAN=ON'
	'-DSDL_DISABLE_INSTALL_DOCS=ON'
	'-DSDL_EXAMPLES=OFF'
	'-DSDL_TESTS=OFF'
	'-DSDL_INSTALL_TESTS=OFF'
	'-DSDL_SHARED=OFF'
	'-DSDL_STATIC=ON'

	'-DSDL_DUMMYVIDEO=OFF'

	'-DSDL_OFFSCREEN=OFF'

	'-DSDL_HIDAPI_JOYSTICK=OFF'
	'-DSDL_VIRTUAL_JOYSTICK=OFF'
	'-DSDL_HIDAPI_LIBUSB=OFF'
	'-DSDL_HIDAPI_LIBUSB_SHARED=OFF'
)

	#'-DSDL_LIBC=OFF'
	#'-DSDL_RENDER_GPU=ON'
	#'-DSDL_SNDIO=OFF'
	#'-DSDL_OFFSCREEN=OFF'


declare -r cmake_flags=(
	'-DCMAKE_INSTALL_PREFIX='$target_dir
	'-DCMAKE_BUILD_TYPE=Release'
	'-DCMAKE_COLOR_MAKEFILE=ON'
)

# prepare the build
if ! cmake -S $repo_dir -B $build_dir $cmake_flags $cmake_flags_subsystems; then
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

