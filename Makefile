
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
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := --no-rcs --no-globalrcs --errexit --no-unset -c -o pipefail

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

override OS := $(shell uname -s)

ifeq ($(OS), Darwin)
override THREADS := $(shell sysctl -n hw.logicalcpu)
endif
ifeq ($(OS), Linux)
override THREADS := $(shell nproc --all)
endif



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT := engine

# main executable
override EXEC := exec_$(PROJECT)

# compile commands database
override COMPILE_DB := compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
override PWD_DIR := $(shell pwd)

# source directory
override SRC_DIR := sources

# include directory
override INC_DIR := includes

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

# vulkan directory
ifeq ($(OS), Darwin)
override VULKAN_DIR := /Users/untitled/VulkanSDK/1.3.268.1/macOS
endif
ifeq ($(OS), Linux)
override VULKAN_DIR := $(shell pwd)/vulkansdk/x86_64
endif

# glslc compiler
override GLSLC := $(VULKAN_DIR)/bin/glslc

# vulkan include directory
override VULKAN_INCLUDE := -I$(VULKAN_DIR)/include

# os dependent vulkan dependencies
ifeq ($(OS), Darwin)
override VULKAN_DEPS := -framework Cocoa -framework IOKit -framework QuartzCore
endif
ifeq ($(OS), Linux)
override VULKAN_DEPS := -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif

# vulkan library directory
override VULKAN_LIB := -L$(VULKAN_DIR)/lib -lvulkan $(VULKAN_DEPS)



# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# get all sub include directories
override INCS := $(INC_DIR)
#$(shell find $(INC_DIR) -type d)

# pattern substitution for object files
override OBJS := $(SRCS:%.cpp=%.o)

# pattern substitution for dependency files
override DEPS := $(OBJS:%.o=%.d)



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
override CXX := clang++

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0

# debug flags
override DEBUG := -g3

# warning scope
override FLAGS := -Wall -Wextra -Werror \
				  -fno-rtti -Wpedantic -Weffc++

# unused suppression
override FLAGS += -Wno-unused -Wno-unused-variable -Wno-unused-parameter \
				  -Wno-unused-function

				  #-Wno-unused-private-field -Wno-unused-local-typedef \

# optimization
#override FLAGS += -Winline

# type conversion
#override FLAGS += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override FLAGS += -Wshadow

# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# defines
#override DEFINES ?=
override DEFINES := -DENGINE_VL_DEBUG

# include flags
override INCLUDES := $(addprefix -I, $(INCS)) $(GLFW_INCLUDE) $(VULKAN_INCLUDE) $(XNS_INCLUDE)

# linker flags
override LDFLAGS := $(GLFW_LIB) $(VULKAN_LIB) $(XNS_LIB)

# cxx flags
override CXXFLAGS = $(STD) $(OPT) $(DEBUG) $(DEFINES) $(FLAGS) $(INCLUDES) $(DEPFLAGS)

# command database flags
override CCDBFLAGS := $(STD) $(OPT) $(DEBUG) $(DEFINES) $(FLAGS) $(INCLUDES)




# -- T O O L S ----------------------------------------------------------------

override RM := rm -rf
override CP := cp -r
override MKDIR := mkdir -p


# terminal cell width
override TERM_WIDTH := $(shell tput cols)


# -- P H O N Y  T A R G E T S -------------------------------------------------

.PHONY: all clean fclean re intro shaders xns ascii


# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo '\x1b[32m\n' \
		'░  ░░░░  ░░  ░░░░  ░░  ░░░░░░░░  ░░░░  ░░░      ░░░   ░░░  ░\n' \
		'▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒  ▒▒▒  ▒▒▒▒  ▒▒    ▒▒  ▒\n' \
		'▓▓  ▓▓  ▓▓▓  ▓▓▓▓  ▓▓  ▓▓▓▓▓▓▓▓     ▓▓▓▓▓  ▓▓▓▓  ▓▓  ▓  ▓  ▓\n' \
		'███    ████  ████  ██  ████████  ███  ███        ██  ██    █\n' \
		'████  ██████      ███        ██  ████  ██  ████  ██  ███   █\n' \
		'GNU Make:' $(MAKE_VERSION)'\x1b[0m'


# -- R U L E S ----------------------------------------------------------------

all: ascii $(GLFW_DIR) xns shaders objs $(EXEC) $(COMPILE_DB)
	$(call FORMAT,"done")
	echo 'source' $(VULKAN_DIR)/../setup-env.sh
	echo

# xns
xns:
	$(call FORMAT,"installing xns")
	$(TLS_DIR)/install_xns.sh

# shaders
shaders:
	$(call FORMAT,"compiling shaders")
	$(MAKE) --silent --directory=$(SHA_DIR) GLSLC=$(GLSLC)


# executable
$(EXEC): $(OBJS)
	$(call FORMAT,"linking")
	$(CXX) $^ -o $@ $(LDFLAGS)
	\ls -l $@

# important !
# requires 'source /Users/untitled/VulkanSDK/1.3.268.1/setup-env.sh'

# launch threads
objs:
	$(call FORMAT,"compilation")
	$(MAKE) --silent --jobs=$(THREADS) $(OBJS)

# compilation
-include $(DEPS)
%.o: %.cpp Makefile
	print -f '- %s\n' $@
	$(CXX) $(CXXFLAGS) -c $< -o $@


# compile commands
$(COMPILE_DB): $(SRCS) Makefile
	$(call FORMAT,"compile database")
	$(call GENERATE_CDB)
	\ls -l $@

# clean
clean:
	$(call FORMAT,"cleaning project")
	$(RM) $(OBJS) $(DEPS) $(COMPILE_DB) .cache
	$(MAKE) --silent --directory=$(SHA_DIR) clean

# fclean
fclean: clean
	$(RM) $(EXEC) $(EXT_DIR)
	$(MAKE) --silent --directory=$(SHA_DIR) fclean

# re
re: fclean all

# glfw
$(GLFW_DIR):
	$(call FORMAT,"installing glfw")
	$(TLS_DIR)/install_glfw.sh




# -- F O R M A T T I N G ------------------------------------------------------

define FORMAT
printf '\x1b[90m%0.1s\x1b[0m' '-'{1..$(TERM_WIDTH)}
echo '\x1b[7;32m' $(1) '\x1b[0m'
endef

# generate compile_commands.json
define GENERATE_CDB
local CONTENT='[\n'
for FILE in $(SRCS); do
CONTENT+='\t{\n\t\t"directory": "'$$(pwd)'",\n\t\t"file": "'$$FILE'",\n\t\t"output": "'$${FILE%.cpp}.o'",\n\t\t"arguments": [\n\t\t\t"$(CXX)",\n'
	for FLAG in $(CCDBFLAGS); do
		CONTENT+='\t\t\t"'$$FLAG'",\n'
	done
	CONTENT+='\t\t\t"-c",\n\t\t\t"'$$FILE'",\n\t\t\t"-o",\n\t\t\t"'$${FILE%.cpp}'.o"\n\t\t]\n\t},\n'
done
echo $${CONTENT%',\n'}'\n]' > $@
endef
