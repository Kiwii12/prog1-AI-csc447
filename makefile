# CC = g++

# CFLAGS = -std=c++11 -Wall

all: ANNtrain
	
	ANNtrain : C_Net.o Input.o Parameters.o ANNtrain.o
		g++ C_Net.o Input.o Parameters.o ANNtrain.o -o ANNtrain -std=c++11

	C_Net.o: C_Net.h C_Net.cpp
		g++ C_Net.h C_Net.cpp -std=c++11

	Input.o: Input.h Input.cpp
		g++ Input.h Input.cpp -std=c++11

	Parameters.o: Parameters.h
		g++ Parameters.h -std=c++11

	ANNtrain.o: ANNtrain.cpp
		g++ ANNtrain.cpp -std=c++11

	clean:
		rm *o hello