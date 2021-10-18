# Executable build constants
CC=g++
CFLAGS=--std=c++17 -Wall -Wextra -Werror -O0 -g
# Dynamic build constants
LDFLAGS=-fPIC -shared
# Artifacts
GENERATES=range *.so output-*.txt
TRASH=*.o *~ o.*


all: range test

range.o: range.cpp range.h
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

librange.so: range.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.cpp range.h
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

range: main.o librange.so
	$(CC) $(CFLAGS) -Wl,-rpath,`pwd` $^ -o $@

test: range
	gdb --quiet --batch -x scenario1.gdb --args ./range 1 12 | grep "@@@" | sed 's/@@@ //' 1> output-1.txt
	gdb --quiet --batch -x scenario2.gdb --args ./range -100 100 3 | grep "@@@" | sed 's/@@@ //' 1> output-2.txt
	cmp output-1.txt correct_output_1.txt
	cmp output-2.txt correct_output_2.txt

clean:
	rm -f $(TRASH) $(GENERATES)
