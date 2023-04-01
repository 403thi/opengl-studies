all: compile run

compile:
	g++ -c main.cpp include/glad/glad.c -I include
	g++ *.o -o main.exe -L lib -lglfw3 -lopengl32 -lgdi32 -Wall

run:
	main.exe