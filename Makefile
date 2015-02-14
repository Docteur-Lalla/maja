CXX=g++
CXXFLAGS=-Wall -std=c++14
LIB=bin/libmaja.a
SRCS=$(wildcard src/*.cpp)

test: $(SRCS) test/bwt.cpp
	$(CXX) $(CXXFLAGS) -o bin/bwt $(SRCS) test/bwt.cpp

.PHONY: clean mrproper

clean:
	rm -rf src/*.o
	rm -rf test/*.o

mrproper: clean
	rm -rf $(LIB)
