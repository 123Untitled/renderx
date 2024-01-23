.PHONY: all rm
	#comp

all: exec

exec: main.cpp Makefile
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang++ -std=c++23 $< -o $@ -MJ main.json
	@echo "[\n"$$(cat main.json | sed '$$s/,\s*$$//')"\n]" | jq > compile_commands.json
	rm -f main.json

rm:
	rm -rf exec main.json compile_commands.json

#comp:
#	bear -- \make -s comp
