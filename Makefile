#ULTRA BASIC MAKEFILE
TARGET = solve
SOURCES = solve.cpp Team.cpp Timer.cpp
HEADERS = Team.h Athlete.h Timer.hpp
OBJECTS = $(SOURCES:.cpp=.o) 

CXXFLAGS = -O3 -std=c++17
CXX = g++


all: $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CXX) $(OBJECTS) -o $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o
	rm $(TARGET)

