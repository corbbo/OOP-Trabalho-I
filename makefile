SPECULATE = app
CFLAGS = -c -std=c++11

all:									${SPECULATE}

${SPECULATE}:							main.o game.o board.o player.o opponent.o die.o
										g++ main.o game.o board.o player.o opponent.o die.o -o ${SPECULATE}

main.o:									main.cpp game.cpp
										g++ ${CFLAGS} main.cpp

game.o:									game.cpp game.hpp board.hpp board.cpp player.cpp player.hpp die.cpp die.hpp opponent.cpp opponent.hpp
										g++ ${CFLAGS} game.cpp

board.o:								board.cpp board.hpp
										g++ ${CFLAGS} board.cpp

player.o:								player.cpp player.hpp
										g++ ${CFLAGS} player.cpp

opponent.o:								opponent.cpp opponent.hpp
										g++ ${CFLAGS} opponent.cpp

die.o:									die.cpp die.hpp
										g++ ${CFLAGS} die.cpp

run:									${SPECULATE}
										./${SPECULATE}

clean:									
										rm -f die.o opponent.o player.o board.o game.o main.o ${SPECULATE}