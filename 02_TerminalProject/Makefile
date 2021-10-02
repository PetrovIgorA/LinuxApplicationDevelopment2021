# Used c++ compiler
CC=g++
# Compilers flags
CFLAGS=-Wall -Wextra -Werror --std=c++17
LDFLAGS=-lncursesw

all: file_show

file_show: file_show.cpp file_window.cpp file_window.h
	$(CC) $(CFLAGS) file_show.cpp file_window.cpp $(LDFLAGS) -o file_show

example_run: file_show
	./file_show file_window.cpp

clean:
	rm -f *.o *.s file_show
