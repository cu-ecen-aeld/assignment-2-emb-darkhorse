# Define default compilers for native builds if not specified on the command line
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++

# Define compiler flags
CFLAGS = -g -Wall
LDFLAGS = -g -Wall -I/

# Name of the final executable
TARGET = writer

# List of object files
OBJECTS = writer.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	rm -f *.o $(TARGET) *.elf *.map
