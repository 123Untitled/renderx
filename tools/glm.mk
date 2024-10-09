

# -- V A R I A B L E S --------------------------------------------------------

# library name
override lib_name := glm

# repository url
override repo_url := https://github.com/g-truc/glm.git

# branch
override branch := master

# cmake flags
override cmake_flags := -DCMAKE_INSTALL_PREFIX=external/$(lib_name) \
						-DBUILD_SHARED_LIBS=OFF \
						-DGLM_BUILD_TESTS=OFF

# launch builder
include tools/builder.mk
