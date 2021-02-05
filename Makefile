WIN_LIB = -LC:\Dev\mingw64\lib -LC:\Dev\SFML-2.5.1\lib
WIN_INCLUDE = -IC:\Dev\mingw64\include -IC:\Dev\SFML-2.5.1\include -IC:\Dev\eigen-3.3.9
all:
	g++ -std=c++17 main.cpp -o evosim -lsfml-graphics -lsfml-window -lsfml-system -pthread -I ../eigen-3.3.9 -g

windows:
	g++ -std=c++17 $(WIN_LIB) $(WIN_INCLUDE) main.cpp -o ./build/evosim.exe -lsfml-graphics -lsfml-window -lsfml-system -static -static-libstdc++ -static-libgcc


