game:main.o OnePlay.o TwoPlay.o tetromino.o minos.o board.o gametime.o SETTING.o
	g++ -o game main.o OnePlay.o SETTING.o TwoPlay.o tetromino.o minos.o gametime.o board.o -lncursesw -lpanel
main.o: main.cpp OnePlay.h
	g++ -c main.cpp
OnePlay.o: OnePlay.cpp OnePlay.h tetromino.h board.h minos.h gametime.h
	g++ -c OnePlay.cpp
TwoPlay.o: TwoPlay.cpp TwoPlay.h OnePlay.h tetromino.h board.h minos.h gametime.h
	g++ -c TwoPlay.cpp
tetromino.o: tetromino.cpp tetromino.h board.h
	g++ -c tetromino.cpp 
minos.o: minos.cpp minos.h board.h tetromino.h
	g++ -c minos.cpp
board.o: board.cpp board.h
	g++ -c board.cpp
gametime.o: gametime.cpp gametime.h
	g++ -c gametime.cpp
SETTING.o:SETTING.cpp SETTING.h
	g++ -c SETTING.cpp
clean :
	rm *.o

