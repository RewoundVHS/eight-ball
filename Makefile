CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -Weffc++ -std=c++14

all: eight-ball eight-ball-interface

clean:
	rm -rf eight-ball eight-ball-interface
