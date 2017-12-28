

CC=g++

CFLAGS= -std=c++11
LFLAGS=-L/usr/lib -lm -lGL -lglut

EXEC=plot
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

$(EXEC) : $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)


clean :
	/bin/rm $(EXEC) *.o
