CFLAGS=-Wall -Werror -std=c++11 -pedantic -ggdb3
OBJS=rainfall_seq.o
PROGRAM=rainfall_seq

$(PROGRAM): rainfall_seq.cpp
	g++ $(CFLAGS) -o $(PROGRAM) rainfall_seq.cpp

clean:
	rm -f $(OBJS) $(PROGRAM) *~
