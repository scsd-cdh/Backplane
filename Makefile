# Compiler settings
CC=msp430-elf-gcc
CFLAGS=-mmcu=msp430fr5969

# Target
TARGET=Build/main.elf

#Drivers
Drivers=$(wildcard Drivers/*.c)

# Object files to build, replace .c extensions with .o
OBJECTS=$(Drivers:.c=.o)

# Your main file (add path if it's not in the same directory)
MAIN=main.c

# Default target
all: $(TARGET)

# Rule for linking final executable
# Depends on OBJECTS and MAIN object file
$(TARGET): $(OBJECTS) $(MAIN:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@


# Rule for building object files from c source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJECTS) main.o

# Flash the MSP430 with the compiled program (example using mspdebug)
flash: $(TARGET)
	mspdebug tilib "prog $(TARGET)"