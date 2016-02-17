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
* uint32_t layer_data = [10, 12, 20, 20, 2];
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
    double* weights;
    uint8_t* node_activated; // <-- we need this for training right?
    // not sure if anything else is needed for training
    // besides weights and if the node is activated/not activated
};

class C_Net
{
public:
    C_Net();
    ~C_Net();
    uint32_t Initialize();


    uint32_t Initialize(uint32_t num_of_layers, uint32_t* num_of_nodes_in_each_layer);

//I think these function have been done by Allison
    uint32_t LoadWeightsFromFile(char* filename);
    uint32_t SaveWeightsToFile(char* filename);
    uint32_t SetSmallRandomWeights(void);

    uint32_t SetTrainingParameters(void); //<-- need to add parameters to be passed

    uint32_t SetInputs(double* inputs_array, uint32_t length);
    uint32_t GetOutputs(double* outputs_array, uint32_t length);
    uint32_t SetDesiredOutputs(double* desired_outputs_array, uint32_t length);

    uint32_t UpdateNet(void);
    uint32_t RunTrainingCycle(void);

	//completes the training cycle
	void fullTrainingRun();

	//Does a test run of the net
	void fowardRunData();

	//revers process though net for training
	void backwardsTrain();

	//Needs to get the param file data <- pulled from ANN.h
	void setData(Parameters newData);
	
	uint32_t TrainNet(void);
	uint32_t TestNet(void);
	uint32_t CrossValidateNet(void);

private:
    uint32_t num_of_inputs;
    double* inputs;

    uint32_t num_of_outputs;
    double* outputs;
    double* desired_outputs;

    uint32_t num_layers;
    uint32_t* num_nodes_in_each_layer;

    //this should be num_layers - 1 (input layer has no weights)
    //number of weights in each layer is nodes in layer * nodes in previous layer
    T_Layer* layers;

    //training parameters variables need to be added here as well
    //double learning_rate //<-- is learning_rate the only one?

	Parameters parm;

};

#endif // _C_NET_H_
