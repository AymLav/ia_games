
clean:
	rm -rf build
	
build: 
	mkdir -p build

build/list.o: lib/board/list.c lib/board/list.h lib/board/item.h | build
	gcc -c lib/board/list.c -I ./lib -o build/list.o

build/board.o: lib/board/board.c lib/board/board.h | build
	gcc -c lib/board/board.c -I ./lib -o build/board.o

build/board_knight.o: lib/knight/board_knight.c lib/knight/board_knight.h | build
	gcc -c lib/knight/board_knight.c -I ./lib -o build/board_knight.o

build/board_taquin.o: lib/taquin/board_taquin.c lib/taquin/board_taquin.h | build
	gcc -c lib/taquin/board_taquin.c -I ./lib -o build/board_taquin.o


# Building libraries
build/libboard.a: build/board.o
	ar crs build/libboard.a build/board.o

build/liblist.a: build/list.o
	ar crs build/liblist.a build/list.o

build/libknight.a: build/board_knight.o
	ar crs build/libknight.a build/board_knight.o

build/libtaquin.a: build/board_taquin.o
	ar crs build/libtaquin.a build/board_taquin.o

build/nqueens: lib/queen/nqueens.c build/libboard.a build/liblist.a | build
	gcc -g -I ./lib lib/queen/nqueens.c build/libboard.a build/liblist.a -Lbuild/ -llist -lboard -o build/nqueens

build/knights: lib/knight/knights.c build/libknight.a build/liblist.a | build
	gcc -g -I ./lib lib/knight/knights.c  build/libknight.a build/liblist.a -Lbuild/ -lknight -llist -o build/knights

build/taquin: lib/taquin/taquin.c build/libtaquin.a build/liblist.a | build
	gcc -g -I ./lib lib/taquin/taquin.c build/libtaquin.a build/liblist.a -Lbuild/ -ltaquin -llist -o build/taquin

all: build/taquin build/nqueens build/knights

nqueens: build/nqueens
	./build/nqueens

knights: build/knights
	./build/knights

taquin: build/taquin
	./build/taquin
	