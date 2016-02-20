#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

#ifndef __PARAMETERS__H__
#define __PARAMETERS__H__
struct Parameters
{
	string paramFile;
	string weightsFile;
	int numberTrainingEpochs;
	double learningRate;
	double momentum;
	double threshold;
	int layers;

	//todo convert prms[6] to int array[layers]
	int *netLayerNodes;

	string dataFile; //training and testing data file
	int burnedAcreage;
	int PDSIdata;
	int endMonth;

	int classes;

	int lowCutoff;
	int mediumCutoff;
	//High is anything above the medium cutoff
};

#endif
