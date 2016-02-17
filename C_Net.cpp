#include "C_Net.h"
#include <string.h>

//set values to zero
//set pointers to null
C_Net::C_Net()
{

}

//deallocate memory used by non-null pointers
C_Net::~C_Net()
{
	//free dynamically allocated memory
	uint32_t i;
	for ( i=0; i<(num_layers - 1); i++)
	{
		delete[] layers[i].weights;
		delete[] layers[i].node_activated;
	}
	delete[] layers;
	delete[] num_nodes_in_each_layer;
	delete[] desired_outputs;
	delete[] outputs;
	delete[] inputs;
}

//set values and allocate all needed memory
uint32_t C_Net::Initialize(uint32_t num_of_layers, uint32_t* num_of_nodes_in_each_layer)
{
	if(num_of_layers+1 < 3)
		return 1;
	//set variables
	num_of_inputs = num_of_nodes_in_each_layer[0];
	num_of_outputs = num_of_nodes_in_each_layer[num_of_layers - 1];
	num_layers = num_of_layers+1;
	//memory allocation
	inputs = new double [num_of_inputs];
	outputs = new double [num_of_outputs];
	desired_outputs = new double [num_of_outputs];
	num_nodes_in_each_layer = new uint32_t [num_layers];
	memcpy(num_nodes_in_each_layer, num_of_nodes_in_each_layer, sizeof(uint32_t)*num_layers);
	layers = new T_Layer [num_layers - 1];
	//memory allocation for network nodes/layers
	uint32_t i;
	uint32_t count;
	for( i=0; i<(num_layers - 1); i++)
	{
		count = num_nodes_in_each_layer[i]*num_nodes_in_each_layer[i+1];
		layers[i].weights = new double [count];
		count = num_nodes_in_each_layer[i+1];
		layers[i].node_activated = new uint8_t [count];
	}




    return 0;
}

//load weights into memory
//return an error if file does not exist
//return different error if number of weights in file
//    do not match expected number of weights
uint32_t C_Net::LoadWeightsFromFile(char* filename)
{

    return 1;
}

//save weights to file
uint32_t C_Net::SaveWeightsToFile(char* filename)
{

    return 1;
}

//generate small random weights as starting point
//not sure if we need/want a parameter or not for this?
uint32_t C_Net::SetSmallRandomWeights(void)
{

    return 1;
}

//simply take input parameters(need to be added still)
//and store the values in the corresponding private variables(also not added yet)
uint32_t C_Net::SetTrainingParameters(void)
{

    return 1;
}

//sets the inputs to the net
//still need to run UpdateNet command to calculate new output values
uint32_t C_Net::SetInputs(double* inputs_array, uint32_t length)
{

    return 1;
}

//just returns the output values
uint32_t C_Net::GetOutputs(double* outputs_array, uint32_t length)
{

    return 1;
}

//set desired output values (used for training the net)
uint32_t C_Net::SetDesiredOutputs(double* desired_outputs_array, uint32_t length)
{

    return 1;
}

//uses the input values to calculate new output values
uint32_t C_Net::UpdateNet(void)
{

    return 1;
}

//runs a single iteration of the generalized delta learning rule
//training parameters need to be added still (private variables to class)
uint32_t C_Net::RunTrainingCycle(void)
{

    return 1;
}

uint32_t C_Net::TrainNet(void)
{
	
	return 1;
}

uint32_t C_Net::TestNet(void)
{
	
	return 1;
}

uint32_t C_Net::CrossValidateNet(void)
{
	
	return 1;
}