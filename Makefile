CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGLEW -lGL -lGLU -lglut 
SOURCES=OpnGl.cpp classes.cpp main.cpp header.h
OBJECTS=$(SOURCES:.cpp=.o)
INCS = -I/usr/include 

EXECUTABLE=opngl

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INCS)  $(OBJECTS) $(LDFLAGS)-o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
