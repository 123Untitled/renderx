
# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := --no-rcs --no-globalrcs --errexit --no-unset -c -o pipefail

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

override OS := $(shell uname -s)



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT := engine

# main executable
override EXEC := exec_$(PROJECT)

# compile commands for clangd
override COMPILE_COMMANDS = compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# root directory
override ROOTDIR := $(shell pwd)

# build directory
override BLDDIR := build

# source directory
override SRCDIR := sources

# include directory
override INCDIR := includes

# object directory
override OBJDIR := $(BLDDIR)/objects

# dependency directory
override DEPDIR := $(BLDDIR)/dependencies

# json directory
override JSNDIR := $(BLDDIR)/json

# shader directory
override SHADIR := shaders

# external directory
override EXTDIR := $(ROOTDIR)/external




# -- G L F W  S E T T I N G S -------------------------------------------------

# glfw directory
override GLFW_DIR := $(EXTDIR)/glfw

# glfw include directory
override GLFW_INCLUDE := $(GLFW_DIR)/include

# glfw library directory
override GLFW_LIB := $(GLFW_DIR)/lib


# -- X N S  S E T T I N G S ---------------------------------------------------

# xns directory
override XNS_DIR := $(EXTDIR)/xns

# xns include directory
override XNS_INCLUDE := $(XNS_DIR)

# xns library directory
override XNS_LIB := $(XNS_DIR)



# -- V U L K A N  S E T T I N G S ---------------------------------------------

# vulkan directory
ifeq ($(OS), Darwin)
    override VULKAN_DIR := /Users/untitled/VulkanSDK/1.3.268.1/macOS
endif
ifeq ($(OS), Linux)
    override VULKAN_DIR := $(EXTDIR)/vulkan/x86_64
endif

# glslc compiler
override GLSLC := $(VULKAN_DIR)/bin/glslc

# vulkan include directory
override VULKAN_INCLUDE := $(VULKAN_DIR)/include

# vulkan library directory
override VULKAN_LIB := $(VULKAN_DIR)/lib



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
override CXX := clang++

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0

# debug flags
override DEBUG := -g3

# address sanitizer flags
override ASANFLAGS := -fsanitize=address

# warning scope
override CXXFLAGS := -Wall -Wextra

# warning impact
override CXXFLAGS += -Werror

# standard respect
override CXXFLAGS += -Weffc++ -Wpedantic

# unused suppression
override CXXFLAGS += -Wno-unused -Wno-unused-variable -Wno-unused-parameter \
					 -Wno-unused-private-field -Wno-unused-local-typedef \
					 -Wno-unused-function 

# optimization
override CXXFLAGS += -Winline

# type conversion
override CXXFLAGS += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override CXXFLAGS += -Wshadow

# linker flags
override LDFLAGS := -L$(GLFW_LIB) -lglfw3 -L$(VULKAN_LIB) -lvulkan -L$(XNS_LIB) -lxns

# os dependent linker flags
ifeq ($(OS), Darwin)
    override LDFLAGS += -framework Cocoa -framework IOKit
endif
ifeq ($(OS), Linux)
    override LDFLAGS += -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif

# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile commands flags
override CMPFLAGS = -MJ $(JSNDIR)/$*.json


# defines
override DEFINES := -DENGINE_VL_DEBUG


# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')

# pattern substitution for object files
override OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,    $(SRCS))

# pattern substitution for dependency files
override DEPS := $(patsubst $(OBJDIR)/%.o,   $(DEPDIR)/%.d,    $(OBJS))

# pattern substitution for json files
override JSNS := $(patsubst $(SRCDIR)/%.cpp, $(JSNDIR)/%.json, $(SRCS))


# get all sub source directories
override SUBSRCDIR := $(sort $(dir $(SRCS)))

# pattern substitution for sub directories
override SUBOBJDIR := $(SUBSRCDIR:$(SRCDIR)/%=$(OBJDIR)/%)
override SUBDEPDIR := $(SUBSRCDIR:$(SRCDIR)/%=$(DEPDIR)/%)
override SUBJSNDIR := $(SUBSRCDIR:$(SRCDIR)/%=$(JSNDIR)/%)

# get all sub include directories
override SUB_INCLUDE := $(shell find $(INCDIR) -type d)



# include flags
override INCLUDES := $(addprefix -I, $(SUB_INCLUDE) $(GLFW_INCLUDE) $(VULKAN_INCLUDE) $(XNS_INCLUDE))




# -- C O L O R S --------------------------------------------------------------

define COLOR
	@printf "\e[7;32m %s \e[0m\n" $(1)
endef

define LINES
	@printf "\e[90m%s\e[0m\n" '-----------------------------------------------'
endef

define LOGO
@echo -e '\x1b[32m'\
'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n'\
'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n'\
' ╱         ╱         ╱         ╱         ╱\n'\
'╱         ╱         ╱        ▁╱       ▁▁╱ \n'\
'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱\n'
endef


# -- P H O N Y  T A R G E T S -------------------------------------------------

.PHONY: all clean fclean re intro shaders xns


# -- R U L E S ----------------------------------------------------------------

all: intro $(GLFW_DIR) xns shaders objs $(EXEC) $(COMPILE_COMMANDS)
	@$(call LINES)
	$(call COLOR,"done ◝(ᵔᵕᵔ)◜")
	echo -n '\n'

intro:
	$(call LOGO)

# shaders
shaders:
	@$(MAKE) --silent --directory=$(SHADIR) GLSLC=$(GLSLC)
	$(call LINES)


# executable
$(EXEC): $(OBJS)
	@echo "  linking: $@"
	$(CXX) $^ -o $@ $(LDFLAGS)
	file $(EXEC)

# launch threads
objs:
	$(call COLOR,"compiling project")
	@$(MAKE) --silent -j8 $(OBJS)

# compilation
-include $(DEPS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(SUBOBJDIR) $(SUBDEPDIR) $(SUBJSNDIR)
	@echo "compiling: $<"
	$(CXX) $(STD) $(DEBUG) $(DEFINES) $(CXXFLAGS) $(INCLUDES) $(DEPFLAGS) $(CMPFLAGS) -c $< -o $@

# create directories
$(SUBOBJDIR) $(SUBDEPDIR) $(SUBJSNDIR):
	@mkdir -p $@

# compile commands
$(COMPILE_COMMANDS): $(JSNS)
	@echo "creating $@"
	@echo "[\n"$$(cat $(JSNS) | sed '$$s/,\s*$$//')"\n]" | jq > $@

# clean
clean: intro
	$(call LINES)
	@$(call COLOR,"cleaning project")
	@rm -rfv $(BLDDIR) $(COMPILE_COMMANDS) .cache
	$(MAKE) --silent --directory=$(SHADIR) clean

# fclean
fclean: clean
	@rm -rfv $(EXEC) $(GLFW_DIR) $(XNS_DIR)
	$(MAKE) --silent --directory=$(SHADIR) fclean


# glfw
$(GLFW_DIR):
	@$(call LINES)
	@$(call COLOR,"installing glfw")
	tools/install_glfw.sh

# xns
xns:
	@$(call LINES)
	@$(call COLOR,"installing xns")
	tools/install_xns.sh

# re
re: fclean all

