all:
	g++ -std=c++17 main.cpp -o evosim -lsfml-graphics -lsfml-window -lsfml-system -pthread -I ../eigen-3.3.9
