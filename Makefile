CFLAGS=-std=c++11 -Wall -Werror -pedantic -ggdb3
OBJS=rainfall.o landscape.o
PROGRAM=rainfall

$(PROGRAM): rainfall.o landscape.o
	g++ -o $(PROGRAM) $(CFLAGS) rainfall.o landscape.o

%.o: %.cpp landscape.hpp
	g++ -c $(CFALGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
