
# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# set shell program
override SHELL := $(shell which sh)

# set shell flags
.SHELLFLAGS := -c -e


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

override os := $(shell uname -s)

ifeq ($(os), Darwin)
override threads := $(shell sysctl -n hw.logicalcpu)
endif
ifeq ($(os), Linux)
override threads := $(shell nproc --all)
endif

# set make flags
override MAKEFLAGS += --warn-undefined-variables \
					  --no-print-directory \
					  --jobs=1


# -- T A R G E T S ------------------------------------------------------------

# project name
override project := renderx

# main executable
override executable := exec_$(project)

# compile commands database
override compile_db := compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
override cwd_dir := .
#$(shell pwd)

# source directory
override src_dir := $(cwd_dir)/sources

# include directory
override inc_dir := $(cwd_dir)/include

# shader directory
override sha_dir := $(cwd_dir)/shaders

# tools directory
override tls_dir := $(cwd_dir)/tools

# external directory
override ext_dir := $(cwd_dir)/external

# temporary directory
override tmp_dir := $(cwd_dir)/tmp




# -- X N S --------------------------------------------------------------------

# xns directory
override xns_dir := $(ext_dir)/xns

# xns include directory
override xns_include  := -I$(xns_dir)/include

# xns library directory
override xns_library  := -L$(ext_dir)/xns/lib -lxns


# -- G L F W ------------------------------------------------------------------

override glfw             := glfw
override glfw_dir         := $(ext_dir)/$(glfw)
override glfw_include     := -I$(glfw_dir)/include
override glfw_library     := -L$(glfw_dir)/lib -lglfw3
override glfw_url         := https://github.com/glfw/glfw.git
override glfw_branch      := master
override glfw_repo        := $(tmp_dir)/$(glfw)
override glfw_cmake_flags := -DCMAKE_INSTALL_PREFIX=$(glfw_dir) \
							 -DBUILD_SHARED_LIBS=OFF \
							 -DGLFW_INSTALL=ON \
							 -DGLFW_LIBRARY_TYPE=STATIC \
							 -DGLFW_BUILD_EXAMPLES=OFF \
							 -DGLFW_BUILD_TESTS=OFF \
							 -DGLFW_BUILD_DOCS=OFF


# -- G L M --------------------------------------------------------------------

override glm             := glm
override glm_dir         := $(ext_dir)/glm
override glm_include     := -I$(glm_dir)/include
override glm_library     := -L$(ext_dir)/glm/lib -lglm
override glm_url         := https://github.com/g-truc/glm.git
override glm_branch      := master
override glm_repo        := $(tmp_dir)/$(glm)
override glm_cmake_flags := -DCMAKE_INSTALL_PREFIX=$(glm_dir) \
							-DBUILD_SHARED_LIBS=OFF \
							-DGLM_BUILD_TESTS=OFF


# -- V U L K A N --------------------------------------------------------------

ifeq ($(shell echo $$VULKAN_SDK),)
$(error VULKAN_SDK env is not set, source $(shell find ~/VulkanSDK -type f -name 'setup-env.sh'))
endif

# os dependent vulkan dependencies
ifeq ($(os), Darwin)
override vulkan_dependencies := -framework Cocoa -framework IOKit -framework QuartzCore -framework Carbon
endif
ifeq ($(os), Linux)
override vulkan_dependencies := -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif

# vulkan directory
override vulkan_dir := $(shell echo $$VULKAN_SDK)

# vulkan include directory
override vulkan_include := -I$(vulkan_dir)/include

# vulkan library directory
override vulkan_library := -L$(vulkan_dir)/lib -lvulkan $(vulkan_dependencies)



# -- F I L E S ----------------------------------------------------------------

# source files
override srcs := $(shell find $(src_dir) -type f -name '*.cpp')

# object files
override objs := $(srcs:%.cpp=%.o)

# dependency files
override deps := $(objs:%.o=%.d)



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
#override cxx := clang++
override cxx := $(shell echo $$(brew --prefix llvm)/bin/clang++)
#override cxx := $(shell echo $$(brew --prefix gcc)/bin/g++*)

# compiler standard
override std := -std=c++2a

# compiler optimization
override opt := -O0

# debug flags
override debug := -g2

# defines
override defines := -DENGINE_VL_DEBUG

# warning scope
override wflags := -Wall -Wextra -Werror \
				  -fno-rtti -Wpedantic -Weffc++

# unused suppression
override wflags += -Wno-unused -Wno-unused-variable -Wno-unused-parameter \
				  -Wno-unused-function -Wno-unused-private-field -Wno-unused-local-typedef \

# optimization
#override wflags += -Winline

# type conversion
override wflags += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override wflags += -Wshadow

# dependency flags
override depflags = -MT $@ -MMD -MP -MF $*.d

# include flags
override includes := $(addprefix -I, $(inc_dir)) $(vulkan_include) $(xns_include) $(glm_include) $(glfw_include)

# linker flags
override ldflags := $(vulkan_library) \
					$(xns_library) \
					$(glm_library) \
					$(glfw_library)

# cxx flags
override cxxflags = $(std) $(opt) $(debug) $(defines) $(wflags) $(includes)



# -- P H O N Y  T A R G E T S -------------------------------------------------

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# non file targets
.PHONY: all clean fclean re objs shaders xns ascii



# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo '\033[32m\n' \
		' ██▒   █▓ █    ██  ██▓     ██ ▄█▀▄▄▄       ███▄    █ \n' \
		'▓██░   █▒ ██  ▓██▒▓██▒     ██▄█▒▒████▄     ██ ▀█   █ \n' \
		' ▓██  █▒░▓██  ▒██░▒██░    ▓███▄░▒██  ▀█▄  ▓██  ▀█ ██▒\n' \
		'  ▒██ █░░▓▓█  ░██░▒██░    ▓██ █▄░██▄▄▄▄██ ▓██▒  ▐▌██▒\n' \
		'   ▒▀█░  ▒▒█████▓ ░██████▒▒██▒ █▄▓█   ▓██▒▒██░   ▓██░\n' \
		'   ░ ▐░  ░▒▓▒ ▒ ▒ ░ ▒░▓  ░▒ ▒▒ ▓▒▒▒   ▓▒█░░ ▒░   ▒ ▒ \n' \
		'   ░ ░░  ░░▒░ ░ ░ ░ ░ ▒  ░░ ░▒ ▒░ ▒   ▒▒ ░░ ░░   ░ ▒░\n' \
		'     ░░   ░░░ ░ ░   ░ ░   ░ ░░ ░  ░   ▒      ░   ░ ░ \n' \
		'      ░     ░         ░  ░░  ░        ░  ░         ░ \n' \
		'     ░ GNU Make:' $(MAKE_VERSION)'\033[0m'



# -- R U L E S ----------------------------------------------------------------

all: ascii shaders $(glfw_dir) $(glm_dir) xns objs $(executable) $(compile_db)

# shaders
shaders:
	$(sha_dir)/make.sh

# executable
$(executable): $(objs)
	$(cxx) $^ -o $@ $(ldflags)
	$(call print,36,exe,$@)

objs:
	$(MAKE) --jobs=$(threads) $(objs)

# compilation
-include $(deps)
%.o: %.cpp Makefile
	$(cxx) $(cxxflags) $(depflags) -c $< -o $@
	$(call print,32,cxx,$(@F))

# compile commands
$(compile_db): $(srcs) Makefile
	node $(tls_dir)/generate_cdb.js '$(cwd_dir)' '$(srcs)' '$(objs)' '$(cxx)' '$(cxxflags)'
	$(call print,34,cdb,$@)

# clean
clean:
	rm -rfv $(objs) $(deps) $(compile_db) .cache
	$(sha_dir)/make.sh clean

# fclean
fclean: clean
	rm -rfv $(executable) $(ext_dir) $(tmp_dir)

# re
re: fclean all

# xns
xns:
	$(tls_dir)/install_xns.sh

# glm
$(glm_dir):
	git clone --branch $(glm_branch) --single-branch --depth 1 \
		$(glm_url) $(glm_repo)
	cmake -S $(glm_repo) -B $(glm_repo)/build $(glm_cmake_flags) -G Ninja
	ninja -C $(glm_repo)/build -j$(threads) install
	rm -rf $(glm_repo)

# glfw
$(glfw_dir):
	git clone --branch $(glfw_branch) --single-branch --depth 1 \
		$(glfw_url) $(glfw_repo)
	cmake -S $(glfw_repo) -B $(glfw_repo)/build $(glfw_cmake_flags) -G Ninja
	ninja -C $(glfw_repo)/build -j$(threads) install
	rm -rf $(glfw_repo)

#override depflags = -MT $@ -MMD -MP -MF $*.d

generate_ninja:

	ninja='cxx = $(cxx)\n'
	ninja+='cxxflags = $(cxxflags)\n'
	ninja+='ldflags = $(ldflags)\n'

	ninja+='rule compile\n'
	ninja+='  command = $$cxx $$cxxflags -MT $$out -MMD -MP -MF $$out.d -c $$in -o $$out\n'
	ninja+='  description = compile $$in\n'
	ninja+='  depfile = $$out.d\n'
	ninja+='  deps = gcc\n\n'

	ninja+='rule link\n'
	ninja+='  command = $$cxx $$in -o $$out $$ldflags\n'
	ninja+='  description = link $$out\n\n'

	for src in $(srcs); do
		ninja+="build $${src%.cpp}.o: compile $$src\n"
	done

	ninja+='build $(executable): link $(objs)\n\n'

	ninja+='default $(executable)\n\n'

	echo "$$ninja" > build.ninja

	




## Règles
#rule cxx
#  command = g++ -Wall -std=c++17 -MMD -MF $out.d -c $in -o $out
#  description = Compile $in
#  depfile = $out.d
#  deps = gcc
#
#rule link
#  command = g++ $in -o $out
#  description = Link $out
#
## Compilation avec gestion des dépendances
#build main.o: cxx main.cpp
#build foo.o: cxx foo.cpp
#build bar.o: cxx bar.cpp
#
## Lien
#build program: link main.o foo.o bar.o
#
## Cible par défaut
#default program
#
## Nettoyage
#rule clean
#  command = rm -f *.o *.d program
#  description = Clean build files
#
#build clean: clean


# -- F O R M A T T I N G ------------------------------------------------------

define enter_screen
echo '\033[?1049h\033[H\033[2J'
endef

define exit_screen
echo '\033[?1049l'
endef

define print
echo '\033[90m[\033[$(1)m'$(2)'\033[0m\033[90m]\033[0m' '$(3)'
endef
