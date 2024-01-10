all:
	g++ -m64 -I src\include -o game main.cpp -L src\lib -lmingw32 -lSDL2main -lSDL2

#	ko imamo več datotek:
#	g++ -m64 -I src\include objekt.cpp -o game main.cpp -L src\lib -lmingw32 -lSDL2main -lSDL2