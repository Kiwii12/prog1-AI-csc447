
#include "prog1/ANN.h"

//Reads in the parameter file and puts each value in a separate row in the prms array
//author - Allison


int main(int argc, char const *argv[])
{
	ANN ann(argv[1]);
	ann.parseParams();


	return 0;
}
