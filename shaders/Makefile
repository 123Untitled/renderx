
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




# -- V A R I A B L E S --------------------------------------------------------

override GLSLC := $(shell which glslc)

override SRCS  := $(shell find . -type f -name '*.vert' -o -name '*.frag')

override SPIRV := $(patsubst %.vert, %.vert.spv, $(SRCS))



