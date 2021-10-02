# Executable build constants
CC=gcc
CFLAGS=-Wall -Wextra -Werror
# Dynamic build constants
LDFLAGS=-fPIC -shared
# Artifacts
GENERATES=prog prog-* *.so *.a *.txt README
TRASH=*.o *~ o.*
# Test constants
ONE_ARGUMENT=arg_alone
THREE_ARGUMENTS=arg1 arg2 arg3
FILE_OUT_0=prog-0-out.txt
FILE_ERR_0=prog-0-err.txt
FILE_A_OUT_0=prog-a-0-out.txt
FILE_A_ERR_0=prog-a-0-err.txt
FILE_SO_OUT_0=prog-so-0-out.txt
FILE_SO_ERR_0=prog-so-0-err.txt
FILE_OUT_1=prog-1-out.txt
FILE_ERR_1=prog-1-err.txt
FILE_A_OUT_1=prog-a-1-out.txt
FILE_A_ERR_1=prog-a-1-err.txt
FILE_SO_OUT_1=prog-so-1-out.txt
FILE_SO_ERR_1=prog-so-1-err.txt
FILE_OUT_3=prog-3-out.txt
FILE_ERR_3=prog-3-err.txt
FILE_A_OUT_3=prog-a-3-out.txt
FILE_A_ERR_3=prog-a-3-err.txt
FILE_SO_OUT_3=prog-so-3-out.txt
FILE_SO_ERR_3=prog-so-3-err.txt

all: README prog prog-a prog-so

README: prog
	./$< 2> $@

prog: prog.o fun.o const.o
	$(CC) $(CFLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) $(CFLAGS) $^ -o $@

prog-so: prog.o liboutput.so
	$(CC) $(CFLAGS) -Wl,-rpath,`pwd` $^ -o $@

prog.o: prog.c outlib.h
	$(CC) $(CFLAGS) -o $@ -c $<

fun.o: fun.c outlib.h
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

const.o: const.c
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) $(LDFLAGS) $^ -o $@

test: prog prog-a prog-so
	./prog 1> $(FILE_OUT_0) 2> $(FILE_ERR_0)
	./prog $(ONE_ARGUMENT) 1> $(FILE_OUT_1) 2> $(FILE_ERR_1)
	./prog $(THREE_ARGUMENTS) 1> $(FILE_OUT_3) 2> $(FILE_ERR_3)
	./prog-a 1> $(FILE_A_OUT_0) 2> $(FILE_A_ERR_0)
	./prog-a $(ONE_ARGUMENT) 1> $(FILE_A_OUT_1) 2> $(FILE_A_ERR_1)
	./prog-a $(THREE_ARGUMENTS) 1> $(FILE_A_OUT_3) 2> $(FILE_A_ERR_3)
	./prog-so 1> $(FILE_SO_OUT_0) 2> $(FILE_SO_ERR_0)
	./prog-so $(ONE_ARGUMENT) 1> $(FILE_SO_OUT_1) 2> $(FILE_SO_ERR_1)
	./prog-so $(THREE_ARGUMENTS) 1> $(FILE_SO_OUT_3) 2> $(FILE_SO_ERR_3)
	cmp $(FILE_OUT_0) $(FILE_A_OUT_0)
	cmp $(FILE_ERR_0) $(FILE_A_ERR_0)
	cmp $(FILE_OUT_0) $(FILE_SO_OUT_0)
	cmp $(FILE_ERR_0) $(FILE_SO_ERR_0)
	cmp $(FILE_SO_OUT_0) $(FILE_A_OUT_0)
	cmp $(FILE_SO_ERR_0) $(FILE_A_ERR_0)
	cmp $(FILE_OUT_1) $(FILE_A_OUT_1)
	cmp $(FILE_ERR_1) $(FILE_A_ERR_1)
	cmp $(FILE_OUT_1) $(FILE_SO_OUT_1)
	cmp $(FILE_ERR_1) $(FILE_SO_ERR_1)
	cmp $(FILE_SO_OUT_1) $(FILE_A_OUT_1)
	cmp $(FILE_SO_ERR_1) $(FILE_A_ERR_1)
	cmp $(FILE_OUT_3) $(FILE_A_OUT_3)
	cmp $(FILE_ERR_3) $(FILE_A_ERR_3)
	cmp $(FILE_OUT_3) $(FILE_SO_OUT_3)
	cmp $(FILE_ERR_3) $(FILE_SO_ERR_3)
	cmp $(FILE_SO_OUT_3) $(FILE_A_OUT_3)
	cmp $(FILE_SO_ERR_3) $(FILE_A_ERR_3)

clean:
	rm -f $(TRASH)

distclaean: clean
	rm -f $(GENERATES)
