

override GLFW := $(PWD)/glfw
override GLFW_INCLUDE_DIR := $(GLFW)/include
override GLFW_LIB_DIR := $(GLFW)/lib

override CXXFLAGS := -Wall -Wextra -Werror -Wpedantic
override CXX := clang++
override LDFLAGS := -L$(GLFW_LIB_DIR) -lglfw3 -lvulkan
override INCLUDES := -I$(GLFW_INCLUDE_DIR)
override STD := -std=c++2a
override DEBUG := -g3
override OPT := -O0

all: main.o
	$(CXX) $^ $(LDFLAGS) -o exec
	@echo "linking done"

main.o: sources/main.cpp
	@$(CXX) $(CXXFLAGS) $(STD) $(DEBUG) $(OPT) $(INCLUDES) -c sources/main.cpp -o main.o
	@echo "compilation done"
