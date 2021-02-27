
WIN_LIB = -LC:/Dev/mingw64/lib -LC:/Dev/SFML-2.5.1/lib -lopengl32 -lwinmm -lgdi32 -lfreetype -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system
WIN_INCLUDE = -IC:/Dev/mingw64/include -IC:/Dev/SFML-2.5.1/include -IC:/Dev/eigen-3.3.9 -I ./imgui -I ./imgui-sfml-master

NIX_INCLUDE = -I ./imgui -I ./imgui-sfml-master -I ../eigen-3.3.9
NIX_LIB = -lGL -lGLU -lglut -lsfml-graphics -lsfml-window -lsfml-system -pthread 

SRC = main.cpp ./obj/*.o
IMGUI = ./imgui/*.cpp ./imgui-sfml-master/*.cpp
all:
	g++ -std=c++2a  $(SRC) -o ./build/evosim -g $(NIX_INCLUDE) $(NIX_LIB) -O2

windows: obj $(SRC)
	g++ -std=c++17 $(SRC) -o ./build/evosim.exe -static -static-libstdc++ -static-libgcc $(WIN_LIB) $(WIN_INCLUDE) -O2

obj: $(IMGUI)
	g++ -std=c++17 -c $(IMGUI) $(WIN_LIB) $(WIN_INCLUDE)
	mv *.o ./obj