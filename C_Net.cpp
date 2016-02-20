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
	// if (parm.netLayerNodes != nullptr)
	// {
	// 	delete[] parm.netLayerNodes;
	// }

	//free dynamically allocated memory
	unsigned int i;
	for (i = 0; (int)i<(parm.layers); i++)
	{
		delete[] layers[i].weights;
		delete[] layers[i].deltaW;
		delete[] layers[i].node_activation;
		delete[] layers[i].node_value;
	}
	delete[] layers;
	delete[] desired_outputs;
	delete[] outputs;
	delete[] inputs;
}

//set values and allocate all needed memory
unsigned int C_Net::Initialize()
{
	//Make sure setData is called before this function!!!

	//memory allocation

	//inputs will be the number of nodes in the first layer
	inputs = new double[parm.netLayerNodes[0]];

	//output will be the number of nodes in the last layer
	outputs = new double[parm.netLayerNodes[parm.layers]];

	desired_outputs = new double[parm.netLayerNodes[parm.layers]];
	layers = new T_Layer[parm.layers];
	//memory allocation for network nodes/layers
	int i;
	int count;
	int nodes, nodes_prev;
	
	for (i = 0; i<(parm.layers); i++)
	{
		nodes_prev = parm.netLayerNodes[i];
		nodes = parm.netLayerNodes[i+1];
		//account for bias weights
		count = nodes*nodes_prev + nodes;
		layers[i].weights = new double[count];
		layers[i].deltaW = new double[count];
		
		layers[i].node_activation = new double[nodes];
		layers[i].node_value = new double[nodes];
	}

	//Train Function ALWAYS starts with new weights
	SetSmallRandomWeights();

    return 0;
}


//load weights into memory
//return an error if file does not exist
//return different error if number of weights in file
//    do not match expected number of weights
unsigned int C_Net::LoadWeightsFromFile()
{
	int count = 0;
	int nodes, nodes_prev;
	ifstream fin;
	fin.open(parm.weightsFile);
	for (int i = 0; i<(parm.layers); i++)
	{

		nodes = parm.netLayerNodes[i + 1];
		nodes_prev = parm.netLayerNodes[i];
		count = nodes*nodes_prev + nodes;

		for (int j = 0; j < count; ++j)
		{
			//creates random weights bewtween [-1,1]
			fin >> layers[i].weights[j];
			cout << layers[i].weights[j];
		}
	}
	fin.close();
    return 1;
}

//save weights to file
unsigned int C_Net::SaveWeightsToFile()
{
	int count = 0;
	int nodes, nodes_prev;
	ofstream fout;
	fout.open(parm.weightsFile, std::ios_base::trunc);
	for (int i = 0; i<(parm.layers); i++)
	{

		nodes = parm.netLayerNodes[i + 1];
		nodes_prev = parm.netLayerNodes[i];
		count = nodes*nodes_prev + nodes;

		for (int j = 0; j < count; ++j)
		{
			//creates random weights bewtween [-1,1]
			fout << layers[i].weights[j] << endl;
		}
	}
	fout.close();
	//make sure to save Weights Array

    return 1;
}

/*******************************************************
Function: SetSmallRandomWeights		
Author: Allison Bodvig

Description: This function calculates random weights
between -1 and 1. 

Return:
	returns 1

********************************************************/
unsigned int C_Net::SetSmallRandomWeights(void)
{
	int i, j;
	int count;
	int nodes, nodes_prev;
	
	//loop through the number of layers and nodes
	for (i = 0; i<(parm.layers); i++)
	{
		
		nodes = parm.netLayerNodes[i+1];
		nodes_prev = parm.netLayerNodes[i];
		count = nodes*nodes_prev + nodes;

		srand(time(NULL));
	 	for (j = 0; j < count; ++j)
		{
			//creates random weights bewtween [-1,1]
			layers[i].weights[j] = -1 + float (rand())/ (float (RAND_MAX/(2)));
			//cout << layers[i].weights[j] << endl;
		}
	}

  return 1;
}

/*******************************************************
Function: findMin		
Author: Allison Bodvig

Description: This function finds the minimum value found
in the array of values 

Parameters:
	values		- holds the values that are to be used
	years 		- number of years of data
	vals 			- how many indexes in the values array

Return:
	returns minimum value

********************************************************/
float C_Net::findMin(float values[][13], int years, int vals)
{
	float min = 1000000;

	//loop through array looking for min
	for (int i = 0; i < years + 1; ++i)
	{
		for (int j = 1; j < vals; j++)
		{
			//set new min
			if (values[i][j] < min)
				min = values[i][j];
		}
	}

	return min;
}


/*******************************************************
Function: findMax	
Author: Allison Bodvig

Description: This function finds the maximum value found
in the array of values 

Parameters:
	values		- holds the values that are to be used
	years 		- number of years of data
	vals 			- how many indexes in the values array

Return:
	returns maximum value

********************************************************/
float C_Net::findMax(float values[][13], int years, int vals)
{
	float max = -11;

	//loop through array
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

/*******************************************************
Function: normalize		
Author: Allison Bodvig

Description: This function finds the minimum values found
in the list of values 

Parameters:
	min 			- the minimum value of the data
	max 			- the maximum value of the data
	val 			- the value to be normalized

Return:
	returns normalized value

********************************************************/
float C_Net::normalize(float min, float max, float val)
{
	//normalize the data
	return ((val - min) / (max - min));
}


/*******************************************************
Function: finMin		
Author: Allison Bodvig

Description: This function finds the minimum values found
in the list of values 

Return:
	returns true or false if data was read in 

********************************************************/
bool C_Net::readInData()
{
	ifstream dataFile;
	float PDSI[100][13] = { 0 };
	float NormPDSI[100][13] = { 0 };
	float acres[100][13] = { 0 };
	int j = 0;
	char value[15];
	int years_data, years_acreage, months_pdsi;
	float min, max;

	dataFile.open(parm.dataFile);

	//checks for data file
	if (dataFile.fail())
	{
		cout << "Unable to open " << parm.dataFile << endl;;
	}

	//ignores the first two lines
	dataFile.ignore(256, '\n');
	dataFile.ignore(256, '\n');

	//reads in the data
	while (dataFile.getline(value, 5, ','))
	{
		PDSI[j][0] = atof(value);
		acres[j][0] = atof(value);
		//cout << PDSI[j][0] << endl;

		dataFile.getline(value, 15, ',');
		acres[j][1] = atof(value);
		//cout << acres[j][1] << endl;

		//reads in each month of data
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
		}

		j++;

	}
	dataFile.close();
	
	min = findMin(PDSI, j, 13);
	max = findMax(PDSI, j, 13);

	for (int i = 0; i < j; ++i)
	{
		for (int k = 1; k < 13; ++k)
		{
			PDSI[i][k] = normalize(min, max, PDSI[i][k]);
			//cout << PDSI[i][k] << " ";
		}
		//cout << endl;
	}

	min = findMin(acres, j, 2);
	max = findMax(acres, j, 2);

	for (int i = 0; i < j; ++i)
	{
		for (int k = 1; k < 2; ++k)
		{
			acres[i][k] = normalize(min, max, acres[i][k]);
			cout << acres[i][k] << endl;
		}
	}


	//put data in class variables
    years_data = j;
    years_acreage = j - 1;
    months_pdsi = 12*(j - 1) + parm.endMonth;
	
	
	return false;
}


//sets the inputs to the net
//still need to run UpdateNet command to calculate new output values
unsigned int C_Net::SetInputs(int Count)
{
	//inputArray = arrayOfInputs[count];
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
		nodes = parm.netLayerNodes[i + 1];
		//number of nodes in previous layer
		nodes_prev = parm.netLayerNodes[i];
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
					//+1 to account for bias weight
					layers[i].node_value[j] += inputs[k]*layers[i].weights[j*(nodes_prev+1) + k];
				}
				else if( layers[i-1].node_activation[j] >= 0.5)
				{
					layers[i].node_value[j] += layers[i].weights[j*(nodes_prev+1) + k];
				}
				
			}
			//process bias weight
			layers[i].node_value[j] += layers[i].weights[j*(nodes_prev+1) + k];
			
			//now use sigmoid function
			layers[i].node_activation[j] = (1.0/(1.0 + pow(2.7182818284, (-1.0*layers[i].node_value[j]))));
			
		}
	}
	
  return 0;
}

//runs a single iteration of the generalized delta learning rule
//training parameters need to be added still (private variables to class)
unsigned int C_Net::RunTrainingCycle(void)
{
	int i, j, k, l;
	int nodes;
	int nodes_prev;
	int nodes_next;
    double delta;
	double activation;
	double deltaWSum;
	//loop through layers
	for( i=parm.layers; i>0; i--)
	{
		//number of nodes in current layer
		nodes = parm.netLayerNodes[i];
		//number of nodes in previous layer
		nodes_prev = parm.netLayerNodes[i - 1];
		//number of nodes in next layer (unless output layer)
		if(i < (parm.layers))
		{
		    nodes_next = parm.netLayerNodes[i + 1];
	    }
	
		//loop through nodes
		for( j=0; j<nodes; j++)
		{
			
			//loop through weights
			for( k=0; k<(nodes_prev + 1); k++)
			{	
		        activation = layers[i].node_activation[j];
				//check if output layer
				if(i == parm.layers)
				{
					delta = activation*(1 - activation)*(desired_outputs[j] - activation);
				}
				else
				{
					deltaWSum = 0;
					//sum all the deltaW of next layer
					for( l=0; i<nodes_next; l++)
					{
						deltaWSum += layers[i+1].deltaW[l*(nodes + 1) + k];
					}
					delta = activation*(1 - activation)*(deltaWSum);
				}
				//set deltaW
				layers[i].deltaW[j*(nodes_prev + 1) + k] = delta*layers[i].weights[j*(nodes_prev + 1) + k];
				
				//adjust weight
				if(k == nodes_prev)
				{
					//bias weight
					layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta;		
				}
				else
				{
					//input layer special case
					if(i == 1)
					{
						layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta*inputs[k];
					}
					else
					{
						layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta*layers[i - 1].node_activation[k];
					}			
				}	
				
			}
				
		}
		
	}
	
	
    return 0;
}

void C_Net::fullTrainingRun() 
{
	int numberOfYears; // = number of years of training data in array
	int errorSum = 0;
	for (int i = 0; i < parm.numberTrainingEpochs; i++)
	{
		//we need a double array of the training data
		//each row of the array will have its pdia and burn acrage data
		randomizeTrainingData();
		for (int j = 0; j < numberOfYears; j++)
		{
			//set training cycle to dataArray[j]
			SetInputs(j);
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

void C_Net::randomizeTrainingData()
{
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
	readInData();
	//fullTrainingRun();
	SaveWeightsToFile();
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

void printEpoch(int eNum, double squareError)
{
	//need to calcualte RMS
	double rms; 

	rms = squareError / eNum;
	rms = sqrt(rms);

	cout << "Epoch Number: " << eNum << " RMS: " << rms << endl;
}
