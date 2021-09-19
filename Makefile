
CC = gcc

# Compiler flags for debug and release
CFLAGS_DEB = -Wall -pedantic -c -g
CFLAGS_REL = -Wall -pedantic -c -O2

# Program name for debug and release
PROG_NAME_DEB = test_debug
PROG_NAME_REL = test


.PHONY: all clean

all:
	@echo "Options:"
	@echo "  make $(PROG_NAME_DEB)	--> Build test program (debug version)"
	@echo "  make $(PROG_NAME_REL)		--> Build test program (release version)"
	@echo "  make clean		--> Erase program and build files"


#  MAKE DEBUG VERSION
$(PROG_NAME_DEB): test_deb.o prog_bar_deb.o
	$(CC) -o $@ $^

test_deb.o: test.c
	$(CC) $(CFLAGS_DEB) -o $@ $^

prog_bar_deb.o: prog_bar.c
	$(CC) $(CFLAGS_DEB) -o $@ $^

# MAKE RELEASE VERSION
$(PROG_NAME_REL): test.o prog_bar.o
	$(CC) -o $@ $^

test.o: test.c
	$(CC) $(CFLAGS_REL) -o $@ $^

prog_bar.o: prog_bar.c
	$(CC) $(CFLAGS_REL) -o $@ $^


clean:
	rm $(PROG_NAME_DEB) $(PROG_NAME_REL) *.o
