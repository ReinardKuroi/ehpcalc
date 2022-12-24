CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $^ -o $@
    
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
    
.PHONY: clean

clean:
    rm -f $(EXECUTABLE) $(OBJECTS)