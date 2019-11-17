SOURCES=$(wildcard *.cpp)
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
PROGRAM=rainfall

$(PROGRAM): rainfall.o landscape.o
	g++ $(CPPFLAGS) -o $(PROGRAM) $(OBJS)

%.o: %.cpp landscape.hpp
	g++ $(CPPFLAGS) -c $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
