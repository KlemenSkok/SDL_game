all:
	g++ -m64 -I src\include -o game main.cpp -L src\lib -lmingw32 -lSDL2main -lSDL2