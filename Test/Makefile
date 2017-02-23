CC=g++
opts=-O2 -std=c++11
GLlib = -lglut -lGL -lglfw
VKlib = `pkg-config --static --libs glfw3` -lvulkan -I /usr/include/vulkan

intro_files = test.cpp

all: intro

intro: $(intro_files)
	$(CC) $(opts) $(intro_files) -o $@ $(GLlib) $(VKlib)

clean:
	rm intro *.o
