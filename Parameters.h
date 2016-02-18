#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef __PARAMETERS__H__
#define __PARAMETERS__N__
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

	string trainFile;
	int burnedAcreage;
	int PDSIdata;
	int endMonth;

	int classes;

	int lowCutoff;
	int mediumCutoff;
	//High is anything above the medium cutoff
};

#endif
