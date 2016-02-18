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
	if (parm.netLayerNodes != nullptr)
	{
		delete parm.netLayerNodes;
	}

	//free dynamically allocated memory
	uint32_t i;
	for (i = 0; i<(num_layers - 1); i++)
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
uint32_t C_Net::Initialize()
{
	//Make sure set data is called before this function!!!
	if (LoadWeightsFromFile(parm.weightsFile) /* == file does not exist */)
	{
		SetSmallRandomWeights();
		//If Weights are different perhaps overright file and start over?
	}

	//Now that we have the weights we can set up the nerual net
	//SetInputs();
	//SetDesiredOutputs();

    return 1;
}

//set values and allocate all needed memory
uint32_t C_Net::Initialize(uint32_t num_of_layers, uint32_t* num_of_nodes_in_each_layer)
{
	if(num_of_layers+1 < 3)
		return 1;
	//set variables
	num_of_inputs = parm.netLayerNodes[0];
	num_of_outputs = parm.netLayerNodes[parm.layers - 1];
	num_layers = parm.layers+1;
	//memory allocation
	inputs = new double [num_of_inputs];
	outputs = new double [num_of_outputs];
	desired_outputs = new double [num_of_outputs];
	num_nodes_in_each_layer = new uint32_t [num_layers];
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
uint32_t C_Net::LoadWeightsFromFile(string filename)
{

    return 1;
}

//save weights to file
uint32_t C_Net::SaveWeightsToFile(string filename)
{

	//make sure to save Weights Array

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

	//I think this is done with the structure

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
	//Will have to run a forward process then a backward proccess
	fowardRunData(); // could return a high low or medium signal to give to backwardsTrain
	backwardsTrain();

	//Might do this after entire loop - that way only done once
	//SaveWeightsToFile(parm.weightsFile.c_str);
    return 1;
}

void C_Net::fullTrainingRun() 
{
	int numberOfYears; // = number of years of training data in array
	for (int i = 0; i < parm.numberTrainingEpochs; i++)
	{
		//we need a double array of the training data
		//each row of the array will have its pdia and burn acrage data
		//randomizeOrderOfDataArray()
		for (int j = 0; j < numberOfYears; j++)
		{
			//set training cycle to dataArray[j]
			RunTrainingCycle();
		}

		//possibly check if training is ready for early break
	}
}



/**************************************************************************//**
 * @Description - This function has to run a test run of the Neural Net
 *	It has to save these values so they can be compared against the "Actual"
 *  value.
 *
 *
 *//**************************************************************************/
void C_Net::fowardRunData()
{
	//for each node in each hidden layer.
	//take the value of the layer before it multiplied by the weight connecting
	//it
	//Add these all together... but keep a different tally for PDSI and acrees 
	//burned
}

/**************************************************************************//**
 * @Description - This function has to back though the weights and modify
 *   Their values based on success and falure. If the test was succesful this
 *   Should not be run. If the test failed then the values will be modified
 *   by the training value.
 *
 *
 *//**************************************************************************/
void C_Net::backwardsTrain()
{
	//This has to back up though the array, adding the training value to weights
	//that led to sucess and subtracting from weights that led to falure <- if 
	//there was a falure.
	UpdateNet();

}

void C_Net::setData(Parameters newData)
{
	parm = newData;
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

