# Compiler and flags
CC = clang
CFLAGS = -Wall -g

# Object files
OBJ = graph_func.o graph.o

# Target executable
TARGET = myprogram

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Build object file from graph_func.c
graph_func.o: graph_func.c graph_func.h
	$(CC) $(CFLAGS) -c graph_func.c

# Build object file from graph.c
graph.o: graph.c graph_func.h
	$(CC) $(CFLAGS) -c graph.c

# Clean up build artifacts
clean:
	rm -f *.o $(TARGET)
