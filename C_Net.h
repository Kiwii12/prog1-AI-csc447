#include "Parameters.h"
#include <cstdint>

#ifndef _C_NET_H_
#define _C_NET_H_


using namespace std;

/***************************************************************************//*
 * @Define Structure - T_Layer - information corresponding to a single layer 
 * in the network
 *
 **//*************************************************************************/
struct T_Layer
{
    //number of weights will be nodes in layer[i] * nodes in layer[i-1]
    //all weights of node[0], then all weights of node[1], etc
    double* weights;

	//Array of changes in weights
	double* deltaW;

	//Array of changes in weights from the last time changes were calculated
	double* deltaW_prev;

    //number of each below will be nodes in layer[i]

	// Value of sigmoid prime
    double* node_activation;

	// Value from the sigmoid function
    double* node_value;

	// Error from desired * (1-desired) * (desired - actual)
    double* node_error;

};

/***************************************************************************//*
 * @Define Class - C_Net - Handles everything related to a neural network. Take
 * based parameter structure. Holds the code for ANNtrain ANNtest and 
 * CrossValidation.
 **//*************************************************************************/
class C_Net
{
public:

/******************************************************************************
*                         Function Prototypes
******************************************************************************/
	C_Net();
    ~C_Net();

	//Initiallizes dynamic memory
    unsigned int Initialize();

	//Loads in weights from a file
    unsigned int LoadWeightsFromFile();

	//save weights weighs from a file
    unsigned int SaveWeightsToFile();

	//sets random weights between -1 and 1
    unsigned int SetSmallRandomWeights(void);

	//Nomralization functions
	float findMin(float values[][13], int years, int vals);
	float findMax(float values[][13], int years, int vals);
	float normalize(float min, float max, float val);

	//Read in the actual data
	bool readInData();

	//Does the foward processing of the net
    void UpdateNet(void);

	//Does the backwards processing of the net
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

	//Three functions called by diffrent main files
	unsigned int TrainNet(void); //Only trains the net
	unsigned int TestNet(void);//Only test output of the net
	unsigned int CrossValidateNet(void); //CrossValidates on a set of data

    //print epoch and RMS
    void printEpoch(int eNum, double squareError);

    //print results to the screen
    void printResults(int rowNum);

    //print percent error
    void printError();

private:
	//number of inputs for input array
    unsigned int num_of_inputs;
	//holds the input values for a given year including PDSI data and burnAcreage
    double* inputs;

	//Number of outputs in desired_output array and output array
    unsigned int num_of_outputs;
	//outputs after a forward run
    double* outputs;
	//outputs based on that years burned acreage
    double* desired_outputs;

	//number of layers in net
    unsigned int num_layers;
	//number of nodes in a given layer
    unsigned int* num_nodes_in_each_layer;

	//container for data from a layer
    T_Layer* layers;

	//number of sets of training data
	int sets_training_data;
	//array based on years of array of training data
	double** training_data;
	//temporary storaged for training data used in CrossValidate
    double** temp_training_data;

	//number of testing data sets
	int sets_testing_data;
	//double array of testing data values based on years
	double** testing_data;

	//parameter value structure
	Parameters parm;

	//amount of incorrect answers
    int wrong;

};

#endif
