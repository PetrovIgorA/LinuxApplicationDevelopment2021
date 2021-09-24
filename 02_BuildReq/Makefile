all: hello_world run clean

hello_world: hello_world.cpp
	g++ hello_world.cpp -o hello_world

run: hello_world
	./hello_world

clean:
	rm -f *.s *.o hello_world
