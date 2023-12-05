# Makefile for Minesweeper

CC = gcc
CFLAGS = -Wall -I include
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
# Executable name
EXECUTABLE = Minesweeper

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

.PHONY: all clean
