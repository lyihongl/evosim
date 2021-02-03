all:
	g++ -std=c++17 main.cpp -o evosim -lsfml-graphics -lsfml-window -lsfml-system -pthread -I ../eigen-3.3.9 -g

windows:
	x86_64-w64-mingw32-g++ -std=c++17 -L/home/yihong/SFML-2.5.1/lib -I/home/yihong/SFML-2.5.1/include main.cpp -o evosim.exe -lsfml-graphics -lsfml-window -lsfml-system -pthread -I ../eigen-3.3.9 -g -static


