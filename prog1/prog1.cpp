#include "ANNtrain.h"

int main(int argc, char const *argv[])
{
	ANNtrain annTrain(argv[1]);
	annTrain.parseParams();


	return 0;
}