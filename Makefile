#ULTRA BASIC MAKEFILE
TARGET = solve
SOURCES = solve.cpp Team.cpp 
HEADERS = Team.h Athlete.h
OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS = -O3
CXX = g++


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o
	rm $(TARGET)

