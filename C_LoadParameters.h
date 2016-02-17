/**************************************************************************//**
 * @file
 *
 * @brief
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



#ifndef __ANN__H__
#define __ANN__N__
class C_LoadParameters
{
public:
/******************************************************************************
*                         Function Prototypes
******************************************************************************/

	C_LoadParameters( string paramFileName );

	C_LoadParameters();

	~C_LoadParameters();

	bool parseParams();

	string paramFile;
	string weightsFile;
	int numberTrainingEpochs;
	double learningRate;
	double momentum;
	double threshold;
	int layers;

	//todo convert prms[6] to int array[layers]
	uint32_t *netLayerNodes;

	//string trainFile;
	string dataFile;

	int burnedAcreage;
	int PDSIdata;
	int endMonth;

	int classes;

	int lowCutoff;
	int mediumCutoff;
	//High is anything above the medium cutoff

private:
    char prms[20][50];

	void setData();

	bool openFile(ifstream &fin);

};

#endif
