#Making the Graph
PROG = matrixVectorOps
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = matrixVectorOps.o matrixVectorOpsDriver.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
matrixVectorOps.o : matrixVectorOps.h matrixVectorOps.cpp
	$(CC) $(CPPFLAGS) -std=c++11 -c matrixVectorOps.cpp
matrixVectorOpsDriver.o : matrixVectorOpsDriver.cpp
	$(CC) $(CPPFLAGS) -std=c++11 -c matrixVectorOpsDriver.cpp
clean : 
	rm -f core $(PROG) $(OBJS)
