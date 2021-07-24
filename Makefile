link_libraries = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all:
	g++ main.cpp shader.cpp deps/glad/glad.c -o main -I deps $(link_libraries)

clean:
	rm main
