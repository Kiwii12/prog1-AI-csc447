/*************************************************
* Basic layout of how I think this class will work
* Pretty much all the functions are not implemented yet
*
* Dynamic memory allocation should only happen inside
*      the Initialize function (deallocate in deconstructor)
* I guess if a function does need to allocate it should de-allocate
*      before returning (obvious exception)
* (The public functions should be passed in pre-allocated arrays
*      by the higher level function calling them)
*
* Let me know if you have questions/concerns/improvements/etc.
*
**************************************************
* Example Usage:
**************************************************
*
* //call constructor and initialize
* C_Net test_net();
* unsigned int layer_data = [10, 12, 20, 20, 2];
* error = test_net.Initialize(5, layer_data);
* error = test_net.SetTrainingParameters(..., ..., ...);
*
* //set weights
* string weights_file = "weights_file.w";
* error = test_net.LoadWeightsFromFile(weights_file.c_str());
* if(error == 1)
*   { test_net.SetSmallRandomWeights(); }
*
* //Training Loop
* test_net.SetInputs(..., ...);
* test_net.UpdateNet();
* test_net.SetDesiredOutputs(..., ...);
* test_net.RunTrainingCycle(..., ...);
*
* //Testing the Net
* test_net.SetInputs(..., ...);
* test_net.UpdateNet();
* test_net.GetOutputs();
*
**************************************************/
#include "Parameters.h"

#ifndef _C_NET_H_
#define _C_NET_H_


using namespace std;
#include <cstdint>

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
    C_Net();
    ~C_Net();
    unsigned int Initialize();


    //unsigned int Initialize(unsigned int num_of_layers, unsigned int* num_of_nodes_in_each_layer);

//I think these function have been done by Allison
    unsigned int LoadWeightsFromFile();
    unsigned int SaveWeightsToFile();
    unsigned int SetSmallRandomWeights(void);

	//Nomralization functions
	float findMin(float values[][13], int years, int vals);
	float findMax(float values[][13], int years, int vals);
	float normalize(float min, float max, float val);

	//Read in the actual data
	bool readInData();


    unsigned int SetInputs(double* inputs_array, unsigned int length);
    unsigned int GetOutputs(double* outputs_array, unsigned int length);
    unsigned int SetDesiredOutputs(double* desired_outputs_array, unsigned int length);

    unsigned int UpdateNet(void);
    unsigned int RunTrainingCycle(void);

	//completes the training cycle
	void fullTrainingRun();

	//Does a test run of the net
	void fowardRunData();

	//revers process though net for training
	void backwardsTrain();

	//Needs to get the param file data <- pulled from ANN.h
	void setData(Parameters newData);
	
	unsigned int TrainNet(void);
	unsigned int TestNet(void);
	unsigned int CrossValidateNet(void);

    //print epoch and RMS
    void printEpoch(int eNum, double squareError);

private:
    unsigned int num_of_inputs;
    double* inputs;

    unsigned int num_of_outputs;
    double* outputs;
    double* desired_outputs;

    unsigned int num_layers;
    unsigned int* num_nodes_in_each_layer;

    //this should be num_layers - 1 (input layer has no weights)
    //number of weights in each layer is nodes in layer * nodes in previous layer
    T_Layer* layers;
	
	int sets_training_data;
	double* training_data;
	
	int sets_testing_data;
	double* testing_data;

    //training parameters variables need to be added here as well
    //double learning_rate //<-- is learning_rate the only one?

	Parameters parm;

};

#endif // _C_NET_H_
