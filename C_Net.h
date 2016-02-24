#include "Parameters.h"
#include <cstdint>

#ifndef _C_NET_H_
#define _C_NET_H_


using namespace std;


struct T_Layer
{
    //number of weights will be nodes in layer[i] * nodes in layer[i-1]
    //all weights of node[0], then all weights of node[1], etc
    double* weights;
	double* deltaW;

    //number of each below will be nodes in layer[i]
    double* node_activation;
    double* node_value;
};

class C_Net
{
public:

/******************************************************************************
*                         Function Prototypes
******************************************************************************/
    C_Net();
    ~C_Net();
    unsigned int Initialize();

    unsigned int LoadWeightsFromFile();
    unsigned int SaveWeightsToFile();
    unsigned int SetSmallRandomWeights(void);

	//Nomralization functions
	float findMin(float values[][13], int years, int vals);
	float findMax(float values[][13], int years, int vals);
	float normalize(float min, float max, float val);

	//Read in the actual data
	bool readInData();

    void UpdateNet(void);
    void RunTrainingCycle(void);

	//completes the training cycle
	void fullTrainingRun(bool print);
    
    //completes the test cycle
    void testRun();

    //completes the test cycle for cross validation 
    void CVtestRun();

	//Needs to get the param file data <- pulled from ANN.h
	void setData(Parameters newData);

	//Randomize training data for epic
	void randomizeTrainingSets(void);

	unsigned int TrainNet(void);
	unsigned int TestNet(void);
	unsigned int CrossValidateNet(void);

    //print epoch and RMS
    void printEpoch(int eNum, double squareError);

    //print results to the screen
    void printResults();

private:
    unsigned int num_of_inputs;
    double* inputs;

    unsigned int num_of_outputs;
    double* outputs;
    double* desired_outputs;

    unsigned int num_layers;
    unsigned int* num_nodes_in_each_layer;

    T_Layer* layers;

	int sets_training_data;
	double** training_data;
    double** temp_training_data;

	int sets_testing_data;
	double** testing_data;

	Parameters parm;

};

#endif
