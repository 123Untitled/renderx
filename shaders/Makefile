
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
.SHELLFLAGS := -c -e



# -- C O M P I L E R  S E T T I N G S -----------------------------------------


# get compiler
GLSLC := glslc


# vertex shader flags
override VERT_FLAGS := -fshader-stage=vert

# fragment shader flags
override FRAG_FLAGS := -fshader-stage=frag



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRC_DIR := sources

# output directory
override OUT_DIR := spirv

# shader directories
override SHADER_DIRS := $(shell find $(SRC_DIR) -maxdepth 1 -type d)

# output directories
override OUT_DIRS := $(patsubst $(SRC_DIR)%, $(OUT_DIR)%, $(SHADER_DIRS))



# -- S O U R C E S ------------------------------------------------------------

# shader sources
override SRCS  := $(shell find $(SRC_DIR) -type f -name '*.glsl')



# -- T A R G E T S ------------------------------------------------------------

# spirv files
override SPIRVS := $(patsubst $(SRC_DIR)%.glsl, $(OUT_DIR)%.spv, $(SRCS))


# -- F L A G S ----------------------------------------------------------------

# glslc flags
override glslc_flags = -fshader-stage=$(patsubst $(SRC_DIR)/%,%,$(<D))


# -- R U L E S ----------------------------------------------------------------

.PHONY: all clean fclean re

all: $(SPIRVS)

$(OUT_DIR)/%.spv: $(SRC_DIR)/%.glsl Makefile | $(OUT_DIRS)
	$(GLSLC) $(glslc_flags) $< -o $@
	echo '-' $@

$(OUT_DIRS):
	mkdir -pv $@

clean:
	rm -rfv $(SPIRVS) $(OUT_DIR)

fclean: clean

re: fclean all
