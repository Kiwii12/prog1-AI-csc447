#include "C_Net.h"
#include <cstring>

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
	unsigned int i;
	for (i = 0; i<(num_layers - 1); i++)
	{
		delete[] layers[i].weights;
		delete[] layers[i].node_activated;
		delete[] layers[i].node_value;
	}
	delete[] layers;
	delete[] parm.netLayerNodes;
	delete[] desired_outputs;
	delete[] outputs;
	delete[] inputs;
}

//set values and allocate all needed memory
unsigned int C_Net::Initialize()
{
	//Make sure set data is called before this function!!!
	//Train Function ALWAYS starts with new weights
	SetSmallRandomWeights();

	//memory allocation

	//inputs will be the number of nodes in the first layer
	inputs = new double[parm.netLayerNodes[0]];

	//output will be the number of nodes in the last layer
	outputs = new double[parm.netLayerNodes[parm.layers -1]];

	desired_outputs = new double[parm.netLayerNodes[parm.layers - 1]];
	layers = new T_Layer[parm.layers];
	//memory allocation for network nodes/layers
	unsigned int i;
	unsigned int count;
	for (i = 0; i<(parm.layers); i++)
	{
		if(i == 0)
		{
			count = (parm.netLayerNodes[i] + 1) * parm.netLayerNodes[i+1];
		}
		else
		{
			count = parm.netLayerNodes[i] * parm.netLayerNodes[i + 1];
		}
		layers[i].weights = new double[count];
		count = parm.netLayerNodes[i + 1];
		layers[i].node_activated = new uint8_t[count];
		layers[i].node_value = new double[count];
	}


    return 1;
}

//set values and allocate all needed memory
unsigned int C_Net::Initialize(unsigned int num_of_layers, unsigned int* num_of_nodes_in_each_layer)
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
	parm.netLayerNodes = new int [num_layers];
	layers = new T_Layer [num_layers - 1];
	//memory allocation for network nodes/layers
	unsigned int i;
	unsigned int count;
	for( i=0; i<(num_layers - 1); i++)
	{
		count = parm.netLayerNodes[i]*parm.netLayerNodes[i+1];
		layers[i].weights = new double [count];
		count = parm.netLayerNodes[i+1];
		layers[i].node_activated = new uint8_t [count];
	}




    return 0;
}

//load weights into memory
//return an error if file does not exist
//return different error if number of weights in file
//    do not match expected number of weights
unsigned int C_Net::LoadWeightsFromFile(string filename)
{

    return 1;
}

//save weights to file
unsigned int C_Net::SaveWeightsToFile(string filename)
{

	//make sure to save Weights Array

    return 1;
}

//generate small random weights as starting point
//not sure if we need/want a parameter or not for this?
unsigned int C_Net::SetSmallRandomWeights(void)
{
	// unsigned int i, j;
	// unsigned int count;

	// for (i = 0; i<(parm.layers); i++)
	// {
	// 	if(i == 0)
	// 	{
	// 		count = (parm.netLayerNodes[i] + 1) * parm.netLayerNodes[i+1];
	// 	}
	// 	else
	// 	{
	// 		count = parm.netLayerNodes[i] * parm.netLayerNodes[i + 1];
	// 	}

	// 	for (j = 0; i < count; ++i)
	// 	{
	// 		//creates random weights bewtween [-1,1]
	// 		layers[i].weights[j] = -1 + float (rand())/ (float (RAND_MAX/(2)));
	// 		//cout << layers[i].weights[i] << endl;
	// 	}
	// }

  return 1;
}

float C_Net::findMin(float values[][13], int years, int vals)
{
	float min = 11;

	for (int i = 0; i < years + 1; ++i)
	{
		for (int j = 1; j < vals; j++)
		{
			if (values[i][j] < min)
				min = values[i][j];
		}
	}

	return min;
}

float C_Net::findMax(float values[][13], int years, int vals)
{
	float max = -11;

	for (int i = 0; i < years + 1; ++i)
	{
		for (int j = 1; j < vals; j++)
		{
			if (values[i][j] > max)
				max = values[i][j];
		}
	}

	return max;
}

float C_Net::normalize(float min, float max, float val)
{
	return ((val - min) / (max - min));
}

bool C_Net::readInData()
{
	ifstream dataFile;
	float PDSI[100][13] = { 0 };
	float NormPDSI[100][13] = { 0 };
	float acres[100][2] = { 0 };
	int j = 0;
	char value[15];
	float min, max;

	dataFile.open(parm.dataFile);

	if (dataFile.fail())
	{
		cout << "Unable to open " << parm.dataFile << endl;;
	}

	dataFile.ignore(256, '\n');
	dataFile.ignore(256, '\n');

	while (dataFile.getline(value, 5, ','))
	{
		PDSI[j][0] = atof(value);
		acres[j][0] = atof(value);
		//cout << PDSI[j][0] << endl;

		dataFile.getline(value, 15, ',');
		acres[j][1] = atof(value);
		//cout << acres[j][1] << endl;

		for (int i = 1; i < 13; ++i)
		{
			if (i < 12)
			{
				dataFile.getline(value, 10, ',');
			}
			if (i == 12)
			{
				dataFile.getline(value, 10, '\n');
			}


			PDSI[j][i] = atof(value);
			//cout << PDSI[j][i] << endl;
		}

		j++;

	}
	return false;
}


//sets the inputs to the net
//still need to run UpdateNet command to calculate new output values
unsigned int C_Net::SetInputs(double* inputs_array, unsigned int length)
{

    return 1;
}

//just returns the output values
unsigned int C_Net::GetOutputs(double* outputs_array, unsigned int length)
{

    return 1;
}

//set desired output values (used for training the net)
unsigned int C_Net::SetDesiredOutputs(double* desired_outputs_array, unsigned int length)
{

    return 1;
}

//uses the input values to calculate new output values
//runs forward through the net
unsigned int C_Net::UpdateNet(void)
{
	int i, j, k;
	int nodes;
	int nodes_prev;
	//loop through layers
	for( i=0; i<parm.layers; i++)
	{
		//number of nodes in current layer
		nodes = parm.netLayerNodes[i+1];
		//number of nodes in previous layer
		if(i == 0)
		{
			//special case: input has 1 bias node
			nodes_prev = (parm.netLayerNodes[i] + 1) * nodes;
		}
		else
		{
			nodes_prev = parm.netLayerNodes[i] * nodes;
		}
		//loop through nodes
		for( j=0; j<nodes; j++)
		{
			//clear node value
			layers[i].node_value[j] = 0;
			//loop through weights
			for( k=0; k<nodes_prev; k++)
			{
				//sum inputs (from prev layer nodes)
				if(i == 0)
				{
					//input layer is special case
					//weight is j*nodes + k
					//wieght is (current node)*nodes + (current weight)
					layers[i].node_value[j] += inputs[k]*layers[i].weights[j*nodes + k];
				}
				else if( layers[i-1].node_activated[j] == 1)
				{
					layers[i].node_value[j] += layers[i].weights[j*nodes + k];
				}
				
			}
			
			//now use sigmoid function
			if(1.0/(1.0 + pow(2.7182818284, (-1.0*layers[i].node_value[j]))) > 0.5)
			{
				layers[i].node_activated[j] = 1;
			}
			else
			{
				layers[i].node_activated[j] = 0;
			}
			
		}
	}
	
    return 1;
}

//runs a single iteration of the generalized delta learning rule
//training parameters need to be added still (private variables to class)
unsigned int C_Net::RunTrainingCycle(void)
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
	for (int i = 0; i < parm.layers; i++)
	{
		//take the value of the layer before it multiplied by the weight connecting
		//it
		//Add these all together... but keep a different tally for PDSI and acrees 
		//burned
	}

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

unsigned int C_Net::TrainNet(void)
{
	Initialize();
	return 1;
}

unsigned int C_Net::TestNet(void)
{
	
	return 1;
}

unsigned int C_Net::CrossValidateNet(void)
{
	
	return 1;
}

