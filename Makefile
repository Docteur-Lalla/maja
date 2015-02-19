CXX=g++
CXXFLAGS=-Wall -std=c++14
LIB=bin/libmaja.a
SRCS=$(wildcard src/*.cpp)

test: $(SRCS) test/bwt.cpp test/lz77.cpp
	$(CXX) $(CXXFLAGS) -o bin/bwt src/bwt.cpp test/bwt.cpp
	$(CXX) $(CXXFLAGS) -o bin/lz77 src/lz77.cpp test/lz77.cpp

.PHONY: clean mrproper

clean:
	rm -rf src/*.o
	rm -rf test/*.o

mrproper: clean
	rm -rf $(LIB)
