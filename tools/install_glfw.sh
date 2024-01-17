#!/usr/bin/env -S zsh --no-rcs --no-globalrcs

# -- V A R I A B L E S --------------------------------------------------------

REPO_PATH='https://github.com/glfw/glfw.git'
REPO_DIR='glfw_repo'
BUILD_DIR=$REPO_DIR'/build'
INSTALL_DIR='external/glfw'


if [[ -d $REPO_DIR ]]; then
	rm -rf $REPO_DIR
fi

if [[ -d $INSTALL_DIR ]]; then
	rm -rf $INSTALL_DIR
fi

if ! git clone $REPO_PATH $REPO_DIR; then
	echo "failed to clone glfw"
	exit 1
fi

if ! command -v cmake &> '/dev/null'; then
	echo "cmake not found"
	exit 1
fi

if ! mkdir -p $BUILD_DIR $INSTALL_DIR; then
	echo "failed to create build and install directories"
	exit 1
fi

CMAKE_FLAGS=(
	"-DCMAKE_INSTALL_PREFIX=$INSTALL_DIR"
	'-DBUILD_SHARED_LIBS=OFF'
	'-DGLFW_BUILD_EXAMPLES=OFF'
	'-DGLFW_BUILD_TESTS=OFF'
	'-DGLFW_BUILD_DOCS=OFF'
)

cmake -S $REPO_DIR -B $BUILD_DIR $CMAKE_FLAGS
cmake --build $BUILD_DIR --target install --config Release

rm -rf $REPO_DIR

