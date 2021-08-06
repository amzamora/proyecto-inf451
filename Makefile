link_libraries = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCS = src/main.cpp src/shader.cpp src/graphics.cpp src/game.cpp deps/glad/glad.c src/nodes/cube.cpp src/nodes/quad.cpp
OBJS = main.o shader.o graphics.o game.o glad.o cube.o quad.o


all: $(OBJS)
	g++ $(OBJS) -o main -I deps $(link_libraries)

%.o: src/%.cpp src/*.hpp src/nodes/*.hpp
	g++ $< -c -o $@ -I deps

%.o: src/nodes/%.cpp src/*.hpp src/nodes/*.hpp
	g++ $< -c -o $@ -I deps

glad.o: deps/glad/glad.c deps/glad/glad.h
	g++ $< -c -o $@ -I deps

clean:
	rm -f main && rm *.o
