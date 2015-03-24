compile:
	g++ -std=c++1y -pedantic -Werror -Wall main.cpp -O3 -lSDL2 -o strange
run: compile
	./strange
