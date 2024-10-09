# Which compiler to use
CC = gcc
# Compiler flags
CFLAGS = -Wall -Werror -I. -g -Werror=vla -std=gnu99
# Final executable
TARGET = webster
# Constituent object files
OBJS = dictionary.o sh.o

# Default Make recipe
default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean recipe: removes all build artifacts
clean:
	$(RM) $(TARGET) $(OBJS)
