

# -- V A R I A B L E S --------------------------------------------------------

# library name
override lib_name    := glfw

# repository url
override repo_url    := https://github.com/glfw/glfw.git

# branch
override branch      := master

# cmake flags
override cmake_flags := -DCMAKE_INSTALL_PREFIX=external/$(lib_name) \
						-DBUILD_SHARED_LIBS=OFF \
						-DGLFW_INSTALL=ON \
						-DGLFW_LIBRARY_TYPE=STATIC \
						-DGLFW_BUILD_EXAMPLES=OFF \
						-DGLFW_BUILD_TESTS=OFF \
						-DGLFW_BUILD_DOCS=OFF

# launch builder
include tools/builder.mk
