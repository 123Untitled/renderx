

# default target
.DEFAULT_GOAL := all

# use basic shell
override SHELL := $(shell which sh)

# define the shell flags
.SHELLFLAGS := -c -e


# -- D I R E C T O R I E S ----------------------------------------------------

override build_dir := build


.PHONY: all clean fclean enter_screen exit_screen compile run
.DELETE_ON_ERROR: $(build_dir)


.SILENT:

override xns_dir := external/xns


# -- T A R G E T S ------------------------------------------------------------

all: $(xns_dir) enter_screen compile exit_screen

compile: | $(build_dir)
	cmake --build $(build_dir)

$(build_dir): Makefile
	cmake -B $(build_dir) -S . -G Ninja

run:
	./$(build_dir)/renderx

clean:
	cmake --build $(build_dir) --target clean
	rm -f renderx

fclean:
	rm -rfv $(build_dir) external .cache
	rm -fv compile_commands.json

$(xns_dir):
	tools/install_xns.sh

enter_screen:
	echo '\033[?1049h\033[H\033[2J'

exit_screen:
	read -p "Press any key to continue..." -n 1 -r
	echo '\033[?1049l'
