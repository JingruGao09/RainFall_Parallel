CFLAGS=-std=c++11 -Wall -Werror -pedantic -ggdb3 -O3
OBJS=rainfall.o landscape.o
PROGRAM=rainfall

$(PROGRAM): rainfall.o landscape.o
	g++ -o $(PROGRAM) $(CFLAGS) rainfall.o landscape.o

%.o: %.cpp landscape.h
	g++ -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
