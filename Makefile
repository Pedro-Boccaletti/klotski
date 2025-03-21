# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRC = main.c matrix.c shape.c stack.c

# Header files (optional, for reference)
HEADERS = matrix.h shape.h main.h stack.h

# Output executable
OUT = labProg

# Default target
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean target
clean:
	rm -f $(OUT)