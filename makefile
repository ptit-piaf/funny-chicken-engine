CC := gcc
CFLAGS := -g -I include --include /usr/include/HOL/HOL_standard.h -Wall -pedantic
LIB := -lglfw -lm -lyyjson

OBJ:= build/context.o build/opengl_context.o build/file.o build/opengl_engine.o build/glfw_callback.o\
      build/opengl_error.o build/global_variable.o build/opengl_render.o build/main.o build/opengl_shader.o build/mat.o\
      build/shader.o build/model_3d.o build/mouse_event.o build/window_event.o build/glad.o

bin/funny: $(OBJ)
	$(CC) -o bin/funny $(OBJ) $(LIB)

$(OBJ): build/%.o: src/%.c
	$(CC) -o $@ $^ $(CFLAGS) -c

init:
	mkdir build

clean:
	rm -r build
