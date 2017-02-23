CC=g++
opts=-O2 -std=c++11
GLlib = -lglut -lGL -lglfw
VKlib = `pkg-config --static --libs glfw3` -lvulkan -I /usr/include/vulkan

base_files = base_code.cpp

VDeleterHeader = VDeleter.hpp

all: base_code

base_code: $(base_files) $(VDeleterHeader)
	$(CC) $(opts) $(VDeleter.hpp) $(base_files) -o $@ $(GLlib) $(VKlib)

clean:
	rm base_code *.o
