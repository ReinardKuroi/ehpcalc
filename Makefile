CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=bin/%.o)

EXECUTABLE = bin/$(notdir $(shell pwd))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
    
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
    
.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)