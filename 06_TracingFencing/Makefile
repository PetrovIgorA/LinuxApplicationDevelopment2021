# Executable build constants
CC=gcc
CFLAGS=-Wall -Wextra -Werror -O0 -g
# Dynamic build constants
LDFLAGS=-shared -Wl,--no-as-needed -ldl
# Artifacts
GENERATES=move *.so *.txt o
TRASH=*.o *~ o.*
MOVING_FILE=files/1.txt
COPIED_FILE=files/1_copy.txt
MOVED_FILE=2.txt
PROTECTED_FILE=files/some_PROTECTsome.py
TEXT_FOR_FILES="London is\nthe capital of\n Great Britain\n!"

all: test

move: move.c
	$(CC) $(CFLAGS) $^ -o $@

injection.so: injection.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# outfile does not exist
# Test must create new file and delete infile
move_to_non_exist_test: move
	touch $(MOVING_FILE)
	echo $(TEXT_FOR_FILES) 1> $(MOVING_FILE)
	cp $(MOVING_FILE) $(COPIED_FILE)
	./move $(MOVING_FILE) $(MOVED_FILE)
	test -f $(MOVED_FILE) # Check that new file was created
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that new file copied correctly
	@if [ ! -f $(MOVING_FILE) ]; then echo "Test passed"; else exit 2; fi # Check that old file was deleted
	rm -f $(MOVED_FILE) $(COPIED_FILE) # Clear workspace

# outfile exist
# Test must correctly copy data from infile to outfile
move_to_exist_file: move
	touch $(MOVING_FILE)
	echo $(TEXT_FOR_FILES) 1> $(MOVING_FILE)
	cp $(MOVING_FILE) $(COPIED_FILE)
	touch $(MOVED_FILE)
	echo $(TEXT_FOR_FILES) 1> $(MOVED_FILE)
	echo $(TEXT_FOR_FILES) 1>> $(MOVED_FILE)
	cp $(MOVING_FILE) $(COPIED_FILE)
	./move $(MOVING_FILE) $(MOVED_FILE)
	test -f $(MOVED_FILE) # Check for existing of new file
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that new file copied correctly
	@if [ ! -f $(MOVING_FILE) ]; then echo "Test passed"; else exit 2; fi # Check that old file was deleted
	rm -f $(MOVED_FILE) $(COPIED_FILE) # Clear workspace

# infile does not exist
# Test must not delete infile and must not change outfile
error_cases_test: move
	touch $(MOVED_FILE) $(MOVING_FILE)
	echo $(TEXT_FOR_FILES) 1> $(MOVED_FILE)
	cp $(MOVED_FILE) $(COPIED_FILE)
	strace -foo -e fault=rename:error=ENOENT ./move $(MOVING_FILE) $(MOVED_FILE)
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that outfile was not changed
	test -f $(MOVING_FILE) # Check that infile exist
	strace -foo -e fault=rename:error=EACCES ./move $(MOVING_FILE) $(MOVED_FILE)
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that outfile was not changed
	test -f $(MOVING_FILE) # Check that infile exist
	strace -foo -e fault=rename:error=EIO ./move $(MOVING_FILE) $(MOVED_FILE)
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that outfile was not changed
	test -f $(MOVING_FILE) # Check that infile exist
	strace -foo -e fault=rename:error=EROFS ./move $(MOVING_FILE) $(MOVED_FILE)
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that outfile was not changed
	test -f $(MOVING_FILE) # Check that infile exist
	@echo "Error cases tests passed"
	rm $(MOVING_FILE) $(MOVED_FILE) $(COPIED_FILE) # Clear workspace

# Use LD_PRELOAD for file protection
protect_test: move injection.so
	touch $(MOVING_FILE)
	echo $(TEXT_FOR_FILES) 1> $(MOVING_FILE)
	cp $(MOVING_FILE) $(COPIED_FILE)
	LD_PRELOAD=`pwd`/injection.so ./move $(MOVING_FILE) $(MOVED_FILE)
	cmp $(MOVED_FILE) $(COPIED_FILE) # Check that new file copied correctly
	@if [ ! -f $(MOVING_FILE) ]; then echo "Test passed"; else exit 2; fi # Check that old file was deleted
	rm -f $(MOVED_FILE) $(COPIED_FILE) # Clear workspace
	LD_PRELOAD=./injection.so ./move $(PROTECTED_FILE) $(MOVED_FILE)
	test -f $(PROTECTED_FILE) # Check that old file was not deleted
	@if [ ! -f $(MOVED_FILE) ]; then echo "Test passed"; else exit 2; fi # Check that new file was not created

test: move_to_non_exist_test move_to_exist_file error_cases_test protect_test
	@echo "All tests passed"

clean:
	rm -f $(TRASH) $(GENERATES)
