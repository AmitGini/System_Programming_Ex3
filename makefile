# Define compiler
CC := gcc

# Define flags, including the current directory for header files
CFLAGS := -Wall -g -I.

# Specify all targets
.PHONY: all clean

all: main

# Main target: depends on main.o and the static library
main: main.o libstrlist.a
	$(CC) $(CFLAGS) -o $@ $< -L. -lstrlist

# Compile main.c to main.o
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library from StrList.o
libstrlist.a: StrList.o
	ar rcs $@ $<

# Compile StrList.c to StrList.o
StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c $< -o $@


# Clean up build artifacts
clean:
	rm -f $(TARGET) *.o *.a