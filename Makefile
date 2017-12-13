OBJS = main.cpp block.hpp ball.hpp gameWorld.hpp gameWindow.hpp playerBreaker.hpp gameWindow.cpp ball.cpp gameWorld.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -std=c++1z

OBJ_NAME = main.out

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)