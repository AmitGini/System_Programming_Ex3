# Define compiler
CC := gcc

# Define flags, including the current directory for header files
CFLAGS := -Wall -g -I.

# Specify all targets
.PHONY: all clean

all: StrList

# Main target: depends on main.o and the static library
StrList: Main.o libStrList.a
	$(CC) $(CFLAGS) -o $@ $< -L. -lStrList

# Compile Main.c to Main.o
Main.o: Main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library from StrList.o
libStrList.a: StrList.o
	ar rcs $@ $<

# Compile StrList.c to StrList.o
StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f *.o *.a StrList