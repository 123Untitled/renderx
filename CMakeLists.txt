
# -- M I N I M U M  V E R S I O N ---------------------------------------------

# cmake version required
cmake_minimum_required(VERSION 3.25)


# -- P R O J E C T ------------------------------------------------------------

# project name
set(executable "renderx")

# define project
project(${executable} VERSION 0.1.0 LANGUAGES CXX)


# -- G E N E R A T O R --------------------------------------------------------

# use ninja
find_program(NINJA_FOUND ninja REQUIRED)


# -- D I R E C T O R I E S -----------------------------------------------------

# set the source directory
set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/sources)

# set the include directory
set(inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)


# -- S O U R C E S -------------------------------------------------------------

# find all c++ files in the src directory
file(GLOB_RECURSE srcs ${src_dir}/*.cpp)


# -- C O M P I L E R  O P T I O N S -------------------------------------------


# use ccache
find_program(CCACHE_FOUND ccache REQUIRED)

# set ccache as the compiler
set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_FOUND})

# define c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# set compiled flags
set(cxxflags -std=c++2a -Wall -Wextra -Werror -Wpedantic -Wno-unused -Wno-unused-variable -Wno-unused-parameter -Winline)


# -- C O M P I L E  C O M M A N D S -------------------------------------------

# set compile commands output directory
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)


# -- F E T C H  C O N T E N T -------------------------------------------------

# inclure fetch content
include(FetchContent)

# disable quiet mode
Set(FETCHCONTENT_QUIET false)

# disable update
Set(FETCHCONTENT_UPDATES_DISCONNECTED true)

# glfw download
FetchContent_Declare(
	glfw
	URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
	URL_HASH SHA256=c038d34200234d071fae9345bc455e4a8f2f544ab60150765d7704e08f3dac01
	UPDATE_COMMAND ""
)

# glm download
FetchContent_Declare(
	glm
	URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz
	URL_HASH SHA256=9f3174561fd26904b23f0db5e560971cbf9b3cbda0b280f04d5c379d03bf234c
	UPDATE_COMMAND ""
)

# set glfw cmake options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_LIBRARY_TYPE STATIC CACHE STRING "")

# set glm cmake options
set(GLM_BUILD_TESTS OFF CACHE BOOL "")

# use glfw
FetchContent_MakeAvailable(glfw glm)


# -- X N S --------------------------------------------------------------------

## run custom script for installing xns library
#add_custom_target(install_xns
#    COMMAND ${CMAKE_COMMAND} -E env zsh ${CMAKE_SOURCE_DIR}/tools/install_xns.sh
#)
#
## add dependency
#add_dependencies(${executable} install_xns)

#target_include_directories(${executable} PRIVATE ${CMAKE_SOURCE_DIR}/external/xns/include)
#target_link_libraries(${executable} PRIVATE ${CMAKE_SOURCE_DIR}/external/xns/lib/libxns.a)


# -- V U L K A N --------------------------------------------------------------

# find vulkan
find_package(Vulkan REQUIRED)



# -- E X E C U T A B L E ------------------------------------------------------

# define executable
add_executable(${executable} ${srcs})

# link libraries
target_link_libraries(${executable} glfw glm Vulkan::Vulkan)

# include directories
target_include_directories(${executable} PRIVATE ${inc_dir})

# set compile options
target_compile_options(${executable} PRIVATE ${cxxflags})

# set compile definitions
target_compile_definitions(${executable} PRIVATE GLFW_INCLUDE_NONE)


# -- L I N K ------------------------------------------------------------------

# create link to the executable in the build directory
execute_process(
	COMMAND ${CMAKE_COMMAND} -E create_symlink
		${CMAKE_BINARY_DIR}/${executable}
		${CMAKE_SOURCE_DIR}/${executable}
)




#GIT_REPOSITORY https://github.com/glfw/glfw.git
#GIT_TAG master
#GIT_PROGRESS TRUE
#GIT_SHALLOW TRUE
#GIT_SUBMODULES ""
