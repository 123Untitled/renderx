
# -- S E T T I N G S ----------------------------------------------------------

# default target
.DEFAULT_GOAL := all

# set shell program
override SHELL := $(shell which sh)

# set shell flags
.SHELLFLAGS := -c -e

# make flags
override MAKEFLAGS += --jobs=1 --output-sync=none


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# get operating system
override os := $(shell uname -s)

# macos specific
ifeq ($(os), Darwin)
override threads := $(shell sysctl -n hw.logicalcpu)
endif

# linux specific
ifeq ($(os), Linux)
override threads := $(shell nproc --all)
endif


# -- V A R I A B L E S --------------------------------------------------------

# repository directory
override repo_dir    := $(lib_name)

# build directory
override build_dir   := $(repo_dir)/build

# target directory
override target_dir  := external/$(lib_name)


# -- C O M M A N D S ----------------------------------------------------------

# make build system
ifeq ($(shell command -v ninja),)

override build_command   := make --directory=$(build_dir) --jobs=$(threads)
override install_command := make --directory=$(build_dir) install
override build_system    := -G Unix\ Makefiles

# ninja build system
else

override build_command   := ninja -j$(threads) -C $(build_dir)
override install_command := ninja -C $(build_dir) install
override build_system    := -G Ninja

endif


# -- B U I L T - I N  T A R G E T S -------------------------------------------

# non-file targets
.PHONY: all clean re

# secondary expansion
.SECONDARY: $(repo_dir)

# precious targets
.PRECIOUS: $(target_dir)

# delete target on error
.DELETE_ON_ERROR: $(build_dir)

# use one shell for all commands
.ONESHELL:


# -- T A R G E T S ------------------------------------------------------------

all: $(target_dir) clean

$(repo_dir):
	@git clone --branch $(branch) --single-branch --depth 1 $(repo_url) $(repo_dir)

$(target_dir): $(repo_dir)
	@cmake -S $(repo_dir) -B $(build_dir) $(build_system) $(cmake_flags)
	$(build_command)
	$(install_command)

clean:
	@rm -rf $(repo_dir)

fclean: clean
	@rm -rf $(target_dir)

re: fclean all
