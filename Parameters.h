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
/***************************************************************************//**
 * @Define Structure - Parameters - Holdes all the values given in a Parameter.prm file
 *	used in 2016 AI programming
 *
 *//***************************************************************************/
struct Parameters
{
	//Parameter file that will be opened for input
	string paramFile;

	//Weights file that
	string weightsFile;

	//number of epics run by the training session
	int numberTrainingEpochs;

	//learning rate of training
	double learningRate;

	//uses the previous training change to increase the learning rate
	double momentum;

	//CutOff value when training stops
	double threshold;

	//amount of layers of trainable weights
	int layers;
	
	//array holding the number of nodes in each layer connected by weights
	int *netLayerNodes;

	string dataFile; //training and testing data file

	//number of burned acreage values to be used in the net
	int burnedAcreage;

	//number of PDSI values to be used in the net
	int PDSIdata;

	//Dictates the closest value that can be used for PDSI data
	int endMonth;

	//class info? not used but given in parameter file
	int classes;

	//burned acreage value that determines the low cut off for fire severity
	int lowCutoff;

	//burned acreage value that determines the medium cut off for fire severity
	int mediumCutoff;

	//High is anything above the medium cutoff

	//normalized value of the low cutoff
	double lowCutoffNorm;

	//normalized calue of the high cutoff
	double mediumCutoffNorm;
};

#endif
