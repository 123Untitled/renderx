
# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# set shell program
override SHELL := $(shell which sh)

# set shell flags
.SHELLFLAGS := -c -e -o pipefail -u




# -- O P E R A T I N G  S Y S T E M -------------------------------------------

override os := $(shell uname -s)

ifeq ($(os), Darwin)
override threads := $(shell sysctl -n hw.logicalcpu)
endif
ifeq ($(os), Linux)
override threads := $(shell nproc --all)
endif


# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules --no-print-directory \
					  --jobs=$(threads) --output-sync=none



# -- T A R G E T S ------------------------------------------------------------

# project name
override project := vulkan_engine

# main executable
override executable := exec_$(project)

# compile commands database
override compile_db := compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
override PWD_DIR := $(shell pwd)

# source directory
override SRC_DIR := sources

# include directory
override INC_DIR := include

# shader directory
override SHA_DIR := shaders

# tools directory
override TLS_DIR := tools

# external directory
override EXT_DIR := $(PWD_DIR)/external




# -- G L F W ------------------------------------------------------------------

# glfw directory
override GLFW_DIR     := $(EXT_DIR)/glfw

# glfw include directory
override GLFW_INCLUDE := -I$(GLFW_DIR)/include

# glfw library directory
override GLFW_LIB     := -L$(GLFW_DIR)/lib -lglfw3


# -- X N S --------------------------------------------------------------------

# xns directory
override XNS_DIR      := $(EXT_DIR)/xns

# xns include directory
override XNS_INCLUDE  := -I$(XNS_DIR)/include

# xns library directory
override XNS_LIB      := -L$(XNS_DIR)/lib -lxns



# -- V U L K A N --------------------------------------------------------------

ifeq ($(shell echo $$VULKAN_SDK),)
$(error VULKAN_SDK is not set, source $(shell find ~/VulkanSDK -type f -name 'setup-env.sh'))
endif

# vulkan directory
override vulkan_dir := $(shell echo $$VULKAN_SDK)

# vulkan include directory
override VULKAN_INCLUDE := -I$(vulkan_dir)/include

# os dependent vulkan dependencies
ifeq ($(os), Darwin)
override vulkan_dependencies := -framework Cocoa -framework IOKit -framework QuartzCore
endif
ifeq ($(os), Linux)
override vulkan_dependencies := -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif

# vulkan library directory
override VULKAN_LIB := -L$(vulkan_dir)/lib -lvulkan $(vulkan_dependencies)



# -- F I L E S ----------------------------------------------------------------

# source files
override srcs := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# object files
override objs := $(srcs:%.cpp=%.o)

# dependency files
override deps := $(objs:%.o=%.d)



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
override cxx := clang++

# compiler standard
override std := -std=c++2a

# compiler optimization
override opt := -O0

# debug flags
override debug := -g3

# defines
override defines := -DENGINE_VL_DEBUG

# warning scope
override wflags := -Wall -Wextra -Werror \
				  -fno-rtti -Wpedantic -Weffc++

# unused suppression
override wflags += -Wno-unused -Wno-unused-variable -Wno-unused-parameter \
				  -Wno-unused-function -Wno-unused-private-field -Wno-unused-local-typedef

# optimization
#override wflags += -Winline

# type conversion
#override wflags += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override wflags += -Wshadow

# dependency flags
override depflags = -MT $@ -MMD -MP -MF $*.d

# include flags
override includes := $(addprefix -I, $(INC_DIR)) $(GLFW_INCLUDE) $(VULKAN_INCLUDE) $(XNS_INCLUDE)

# linker flags
override ldflags := $(GLFW_LIB) $(VULKAN_LIB) $(XNS_LIB)

# cxx flags
override cxxflags = $(std) $(opt) $(debug) $(defines) $(wflags) $(includes)



# -- P H O N Y  T A R G E T S -------------------------------------------------

.PHONY: all clean fclean re shaders xns ascii

.NOTPARALLEL: xns $(GLFW_DIR) shaders $(compile_db)


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
	$(call make_shader,all)


# executable
$(executable): $(objs)
	$(cxx) $^ -o $@ $(ldflags)
	$(call print,36,exe,$@)


# compilation
-include $(deps)
%.o: %.cpp Makefile | shaders
	$(cxx) $(cxxflags) $(depflags) -c $< -o $@
	$(call print,32,cxx,$@)


# compile commands
$(compile_db): $(srcs) Makefile | xns
	node $(TLS_DIR)'/generate_cdb.js' $(PWD_DIR) '$(srcs)' '$(objs)' '$(cxx)' '$(cxxflags)'
	$(call print,34,cdb,$@)

# clean
clean:
	rm -rfv $(objs) $(deps) $(compile_db) .cache
	$(call make_shader,clean)

# fclean
fclean: clean
	rm -rfv $(executable) $(EXT_DIR)
	$(call make_shader,fclean)

# re
re: fclean all

# glfw
$(GLFW_DIR):
	$(TLS_DIR)/install_glfw.sh
# xns
xns: | $(GLFW_DIR)
	$(TLS_DIR)/install_xns.sh





# -- F O R M A T T I N G ------------------------------------------------------

define print
echo '[\x1b[$(1)m'$(2)'\x1b[0m]' '$(3)'
endef

define make_shader
make --silent --directory=$(SHA_DIR) $(1)
endef

