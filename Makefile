
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
override MAKEFLAGS += --warn-undefined-variables  --warn-undefined-functions \
					  --jobs=$(threads) --output-sync=none


# -- T A R G E T S ------------------------------------------------------------

# project name
override project := renderx

# main executable
override executable := exec_$(project)

# compile commands database
override compile_db := compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
override cwd_dir := $(shell pwd)

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



# -- G L M --------------------------------------------------------------------

# glm directory
override glm_dir := $(ext_dir)/glm

# glm include directory
override glm_include := -I$(glm_dir)/include

# glm library directory
override glm_library := -L$(ext_dir)/glm/lib -lglm


# -- X N S --------------------------------------------------------------------

# xns directory
override xns_dir := $(ext_dir)/xns

# xns include directory
override xns_include  := -I$(xns_dir)/include

# xns library directory
override xns_library  := -L$(ext_dir)/xns/lib -lxns


# -- G L F W ------------------------------------------------------------------

# glfw directory
override glfw_dir := $(ext_dir)/glfw

# glfw include directory
override glfw_include := -I$(glfw_dir)/include

# glfw library directory
override glfw_library := -L$(glfw_dir)/lib -lglfw3




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
.PHONY: all clean fclean re shaders xns ascii dependencies

# do not run targets in parallel
.NOTPARALLEL: ascii shaders $(compile_db) dependencies xns $(glm_dir) $(glfw_dir)



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

all: ascii $(executable)

# shaders
shaders: | $(compile_db)
	$(sha_dir)/make.sh



# executable
$(executable): $(objs)
	$(cxx) $^ -o $@ $(ldflags)
	$(call print,36,exe,$@)

# compilation
-include $(deps)
%.o: %.cpp Makefile | shaders
	$(cxx) $(cxxflags) $(depflags) -c $< -o $@
	$(call print,32,cxx,$(@F))

# compile commands
$(compile_db): $(srcs) Makefile | dependencies
	node $(tls_dir)/generate_cdb.js '$(cwd_dir)' '$(srcs)' '$(objs)' '$(cxx)' '$(cxxflags)'
	$(call print,34,cdb,$@)

# clean
clean:
	rm -rfv $(objs) $(deps) $(compile_db) .cache
	$(sha_dir)/make.sh clean

# fclean
fclean: clean
	rm -rfv $(executable) $(ext_dir)

# re
re: fclean all

# dependencies
dependencies: | $(glm_dir) $(glfw_dir) xns

# glm
$(glm_dir):
	make '--makefile='$(tls_dir)'/glm.mk'

# glfw
$(glfw_dir):
	make '--makefile='$(tls_dir)'/glfw.mk'

# xns
xns:
	$(tls_dir)/install_xns.sh


# -- F O R M A T T I N G ------------------------------------------------------

define print
echo '\033[90m[\033[$(1)m'$(2)'\033[0m\033[90m]\033[0m' '$(3)'
endef
