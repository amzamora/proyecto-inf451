link_libraries = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: main.cpp shader.cpp graphics.cpp game.cpp deps/glad/glad.c
	g++ main.cpp shader.cpp graphics.cpp game.cpp deps/glad/glad.c -o main -I deps $(link_libraries)

clean:
	rm main
