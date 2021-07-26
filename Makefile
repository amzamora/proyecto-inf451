link_libraries = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCS = main.cpp shader.cpp graphics.cpp game.cpp deps/glad/glad.c nodes/cube.cpp

all: $(SRCS)
	g++ $(SRCS) -o main -I deps $(link_libraries)

clean:
	rm main
