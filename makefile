CC = g++

CFLAGS = -std=c++11 -c -Wall

all: ANNtrain
	
	ANNtrain : C_Net.o Input.o Parameters.o ANNtrain.o
		$(CC) C_Net.o Input.o Parameters.o ANNtrain.o -o ANNtrain

	C_Net.o: C_Net.h C_Net.cpp
		$(CC) $(CFLAGS) C_Net.h C_Net.cpp

	Input.o: Input.h Input.cpp
		$(CC) $(CFLAGS) Input.h Input.cpp

	Parameters.o: Parameters.h
		$(CC) $(CFLAGS) Parameters.h

	ANNtrain.o: ANNtrain.cpp
		$(CC) $(CFLAGS) ANNtrain.cpp

	clean:
		rm *o hello