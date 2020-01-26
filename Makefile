CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp board.hpp mcts.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f main *.o