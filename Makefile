WIN_LIB = -LC:\Dev\mingw64\lib -LC:\Dev\SFML-2.5.1\lib
WIN_INCLUDE = -IC:\Dev\mingw64\include -IC:\Dev\SFML-2.5.1\include -IC:\Dev\eigen-3.3.9
NIX_INCLUDE = -I ./imgui -I ./imgui-sfml-master
NIX_LIB = -lGL -lGLU -lglut
all:
	g++ -std=c++2a main.cpp ./imgui/*.cpp ./imgui-sfml-master/*.cpp -o ./build/evosim -lsfml-graphics -lsfml-window -lsfml-system -pthread -I ../eigen-3.3.9 -g $(NIX_INCLUDE) $(NIX_LIB) -O2

windows:
	g++ -std=c++17 $(WIN_LIB) $(WIN_INCLUDE) main.cpp -o ./build/evosim.exe -lsfml-graphics -lsfml-window -lsfml-system -static -static-libstdc++ -static-libgcc


