/**************************************************************************//**
 * @file
 *
 * @brief This file contains the parent Class for ANN.cpp.
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



#ifndef __ANN__H__
#define __ANN__N__
class ANN
{
public:
/******************************************************************************
*                         Function Prototypes
******************************************************************************/

	ANN( string paramFileName );

	~ANN();

	bool parseParams();

	void setData(char prms[20][50]);

	bool openFile(ifstream &fin);



private:
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