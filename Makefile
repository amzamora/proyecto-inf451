link_libraries = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCS = src/main.cpp src/shader.cpp src/graphics.cpp src/game.cpp deps/glad/glad.c src/nodes/cube.cpp src/nodes/quad.cpp
OBJS = main.o shader.o graphics.o game.o utilities.o glad.o cube.o quad.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_demo.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_stdlib.o gifdec.o


all: $(OBJS)
	g++ $(OBJS) -o main -I deps $(link_libraries)

%.o: src/%.cpp src/*.hpp src/nodes/*.hpp
	g++ $< -c -o $@ -I deps

%.o: src/nodes/%.cpp src/*.hpp src/nodes/*.hpp
	g++ $< -c -o $@ -I deps

glad.o: deps/glad/glad.c
	g++ $< -c -o $@ -I deps

gifdec.o: deps/gifdec/gifdec.c
	g++ $< -c -o $@ -I deps -fpermissive

%.o: deps/imgui/%.cpp
	g++ $< -c -o $@ -I deps/imgui -I deps

clean:
	rm -f main && rm *.o
