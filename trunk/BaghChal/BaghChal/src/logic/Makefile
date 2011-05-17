#
#Makefile for the game logic of Bagh-Chal
#

GXX=g++
CPPFLAGS=-c -Wall -ansi -pedantic -ggdb
SOURCES=Cell.cpp LogicMain.cpp FileIO.cpp Game.cpp Goat.cpp \
	Grid.cpp PlayerGoat.cpp PlayerTiger.cpp  Tiger.cpp
OBJECTS=$(SOURCES: .cpp=.o)
TARGET=LogicTest

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(GXX) $(FLAGS) $(OBJECTS) -o $(TARGET)

#clean:
#	rm $(TARGET)

