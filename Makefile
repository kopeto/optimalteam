#ULTRA BASIC MAKEFILE
TARGET = solve
SOURCES = solve.cpp Team.cpp Timer.cpp
HEADERS = Team.h Athlete.h Timer.hpp
OBJECTS = $(SOURCES:.cpp=.o) 

CXXFLAGS = -O3 -std=c++17 -Wall
CXX = g++

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    rm_opts := 
else
    rm_opts := -f
endif



all: $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CXX) $(OBJECTS) -o $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(rm_opts) *.o
	rm $(rm_opts) $(TARGET)