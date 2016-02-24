#include "C_Net.h"
#include <cstring>
#include <algorithm>

//#define c_net_debug

#ifdef c_net_debug
    ofstream debug_log;
#endif // c_net_debug

/*******************************************************
Function: C_Net::C_Net()
Author: 

Description: Constructor 

Parameters:
	None

Return:
	None

********************************************************/
C_Net::C_Net()
{
#ifdef c_net_debug
    debug_log.open("debug_log.txt", ofstream::out | ofstream::trunc);
    debug_log << "Debug Log Start...\n";
#endif // c_net_debug
}

/*******************************************************
Function: C_Net::~C_Net()
Author: 

Description: deallocates all the dynamically allocated
memory

Parameters:
	None

Return:
	None

********************************************************/
C_Net::~C_Net()
{
#ifdef c_net_debug
    debug_log << "Debug Log End...";
    debug_log.close();
#endif // c_net_debug

	//free dynamically allocated memory
	int i;
	for (i = 0; i<parm.layers; i++)
	{
		delete[] layers[i].weights;
		delete[] layers[i].deltaW;
		delete[] layers[i].node_activation;
		delete[] layers[i].node_value;
	}
	for( i=0; i<sets_training_data; i++)
    {
        delete[] training_data[i];
    }
	delete[] training_data;
	delete[] layers;
	delete[] desired_outputs;
	delete[] outputs;

}
/*******************************************************
Function: C_Net::Initialize()
Author: 

Description: Initializes the data.

Parameters:
	None

Return:
	None

********************************************************/
unsigned int C_Net::Initialize()
{
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


/*******************************************************
Function: C_Net::LoadWeightsFromFile()
Author: 

Description: This function loads the weights from the 
weights file. 

Parameters:
	None

Return:
	None

********************************************************/
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
		}
	}
	fin.close();
    return 1;
}

/*******************************************************
Function: C_Net::SaveWeightsToFile()
Author: 

Description: This function writes the new weights to the 
weights file

Parameters:
	None

Return:
	None

********************************************************/
unsigned int C_Net::SaveWeightsToFile()
{
	int count = 0;
	int nodes, nodes_prev;
	ofstream fout;

	//open the weights file
	fout.open(parm.weightsFile, std::ios_base::trunc);

	for (int i = 0; i<(parm.layers); i++)
	{

		nodes = parm.netLayerNodes[i + 1];
		nodes_prev = parm.netLayerNodes[i];
		count = nodes*nodes_prev + nodes;

		for (int j = 0; j < count; ++j)
		{
			//print weigths to file 
			fout << layers[i].weights[j] << endl;
		}
	}
	fout.close();

    return 1;
}

/*******************************************************
Function: C_Net::SetSmallRandomWeights()
Author: Allison Bodvig

Description: This function calculates random weights
between -1 and 1.

Parameters:
	None

Return:
	None

********************************************************/
unsigned int C_Net::SetSmallRandomWeights(void)
{
	int i, j;
	int count;
	int nodes, nodes_prev;

    srand(time(NULL));

	//loop through the number of layers and nodes
	for (i = 0; i<(parm.layers); i++)
	{

		nodes = parm.netLayerNodes[i+1];
		nodes_prev = parm.netLayerNodes[i];
		count = nodes*nodes_prev + nodes;

	 	for (j = 0; j < count; ++j)
		{
			//creates random weights bewtween [-1,1]
			layers[i].weights[j] = -1 + float (rand())/ (float (RAND_MAX/(2)));
		}
	}

  return 1;
}

/*******************************************************
Function: C_Net::findMin()
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
Function: C_Net::findMax()
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
Function: C_Net::normalize()
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
Function: C_Net::readInData()
Author: Allison Bodvig and Jacob St. Amand

Description: This function reads in the data from the 
csv file and normalizes all the data. Also moves the data
to the training_data array

Parameters:
	None

Return:
	returns true or false if data was read in

********************************************************/
bool C_Net::readInData()
{
	ifstream dataFile;
	float PDSI[100][13] = { 0 };
	//float NormPDSI[100][13] = { 0 };
	float acres[100][13] = { 0 };
	int i, j, m;
	int c_m, c_y;
	j = 0;
	char value[15];
	int years_acreage;
	int start_year, start_year_tmp, num_data_sets;
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

		dataFile.getline(value, 15, ',');
		acres[j][1] = atof(value);

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
		}
	}

	min = findMin(acres, j, 2);
	max = findMax(acres, j, 2);

	for (int i = 0; i < j; ++i)
	{
		for (int k = 1; k < 2; ++k)
		{
			acres[i][k] = normalize(min, max, acres[i][k]);
		}
	}
	parm.lowCutoffNorm = normalize(min, max, parm.lowCutoff);
	parm.mediumCutoffNorm = normalize(min, max, parm.mediumCutoff);

	//put data in class variables
    years_acreage = j - 1;

    start_year = parm.burnedAcreage;
    start_year_tmp = (int)(parm.PDSIdata - parm.endMonth + 11)/(int)12;
    if(start_year_tmp > start_year)
    {
        start_year = start_year_tmp;
    }
    num_data_sets = years_acreage - start_year;

    sets_training_data = num_data_sets;
    //m = number of inputs
    m = parm.netLayerNodes[0] + 2;
    training_data = new double*[sets_training_data];
    for( i=0; i<sets_training_data; i++)
    {
        training_data[i] = new double[m];
    }

    for(i=start_year; i < years_acreage; i++)
    {
        //answer first
        training_data[i - start_year][0] = acres[i][1];

        //now months of PDSI data
        c_m = parm.endMonth;
        c_y = i;
        for(j=0; j < parm.PDSIdata; j++)
        {
            training_data[i - start_year][j + 1] = PDSI[c_y][c_m];
            c_m--;
            if(c_m == 0)
            {
                c_m = 12;
                c_y--;
            }
        }
        for(j=0; j < parm.burnedAcreage; j++)
        {
            training_data[i - start_year][j + parm.PDSIdata + 1] = acres[i - 1 - j][1];
        }
        //adds year to trainging data2
        training_data[i - start_year][parm.netLayerNodes[0] + 1] = acres[i][0];

    }

	return false;
}

/*******************************************************
Function: C_Net::randomizeTrainingSets()
Author: 

Description: This function randomizes the trainging data

Parameters:
	None

Return:
	None

********************************************************/
void C_Net::randomizeTrainingSets(void)
{
    //randomly shuffle the training data using Knuth shuffle
    int i, j, m;
    double* tempA;
    //number of inputs + desired_output + year
    m = parm.netLayerNodes[0] + 2;
    srand(time(NULL));
    tempA = new double[m];
    for(i=0; i<sets_training_data - 1; i++)
    {
        //j = random integer
        //0 <= j <= n-i
        j = rand() % (sets_training_data - i);

        //swap a[i] and a[i+j]
        memcpy(tempA, training_data[i], sizeof(double)*m);
        memcpy(training_data[i], training_data[i+j], sizeof(double)*m);
        memcpy(training_data[i+j], tempA, sizeof(double)*m);
    }

    delete[] tempA;
}

/*******************************************************
Function: C_Net::UpdateNet()
Author: 

Description: 

Parameters:
	None

Return:
	None

********************************************************/

void C_Net::UpdateNet(void)
{

#ifdef c_net_debug
    debug_log << "\n\n\n\n\nStarting UpdateNet...\n";
    debug_log << "Looping through " << parm.layers << " layers\n";
#endif // c_net_debug

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

#ifdef c_net_debug
    debug_log << "Processing layer " << i << "\n\n\n";
    debug_log << "Nodes in current layer: " << nodes << "\n";
    debug_log << "Nodes in previous layer: " << nodes_prev << "\n";
#endif // c_net_debug

		//loop through nodes
		for( j=0; j<nodes; j++)
		{
#ifdef c_net_debug
    debug_log << "Processing node " << j << " \n\n";
    debug_log << "Setting node_value " << i << ", " << j << " to zero\n";
    debug_log << "Looping through " << nodes_prev << " weights\n";
#endif // c_net_debug

			//clear node value
			layers[i].node_value[j] = 0;
			//loop through weights
			for( k=0; k<nodes_prev; k++)
			{
#ifdef c_net_debug
    debug_log << "Processing weight " << k << "\n";
#endif // c_net_debug
				//sum inputs (from prev layer nodes)
				if(i == 0)
				{
					//input layer is special case
					//weight is j*nodes + k
					//wieght is (current node)*nodes + (current weight)
					//+1 to account for bias weight
					layers[i].node_value[j] += inputs[k]*layers[i].weights[j*(nodes_prev+1) + k];
#ifdef c_net_debug
    debug_log << "node_value += input*weight\n";
    debug_log << "input " << k << " = " << inputs[k] << "\n";
    debug_log << "weight " << j << ", " << k << " = " << layers[i].weights[j*(nodes_prev+1) + k] << "\n";
    debug_log << "node_value = " << layers[i].node_value[j] << "\n";
#endif // c_net_debug
				}
				else
				{
					layers[i].node_value[j] += layers[i-1].node_activation[k]*layers[i].weights[j*(nodes_prev+1) + k];
#ifdef c_net_debug
    debug_log << "node_value += prev node activation*weight\n";
    debug_log << "prev node activation " << k << " = " << layers[i-1].node_activation[k] << "\n";
    debug_log << "weight " << j << ", " << k << " = " << layers[i].weights[j*(nodes_prev+1) + k] << "\n";
    debug_log << "node_value = " << layers[i].node_value[j] << "\n";
#endif // c_net_debug
				}

			}
			//process bias weight
			layers[i].node_value[j] += layers[i].weights[j*(nodes_prev+1) + k];

			//now use sigmoid function
			layers[i].node_activation[j] = (1.0/(1.0 + pow(2.7182818284, (-1.0*layers[i].node_value[j]))));

#ifdef c_net_debug
    debug_log << "processing bias weight\n";
    debug_log << "node_value += weight\n";
    debug_log << "weight " << j << ", " << k << " = " << layers[i].weights[j*(nodes_prev+1) + k] << "\n";
    debug_log << "node_value = " << layers[i].node_value[j] << "\n";
    debug_log << "node_activation = " << layers[i].node_activation[j] << "\n";
#endif // c_net_debug

			//set output values
			if(i == (parm.layers - 1))
      {
        outputs[j] = layers[i].node_activation[j];
#ifdef c_net_debug
    debug_log << "setting output " << j << " = " << outputs[j] << "\n";
#endif // c_net_debug
      }
		}
	}
}

/*******************************************************
Function: C_Net::RunTrainingCycle()
Author: 

Description: 

Parameters:
	None

Return:
	None

********************************************************/
void C_Net::RunTrainingCycle(void)
{
#ifdef c_net_debug
    debug_log << "\n\n\n\n\nStarting TrainingCycle...\n";
    debug_log << "Looping through " << parm.layers << " layers\n";
#endif // c_net_debug

	int i, j, k, l;
	int nodes;
	int nodes_prev;
	int nodes_next;
    double delta;
	double activation;
	double deltaWSum;
	//loop through layers
	for( i = (parm.layers - 1); i>=0; i--)
	{
		//number of nodes in current layer
		nodes = parm.netLayerNodes[i+1];
		//number of nodes in previous layer
		nodes_prev = parm.netLayerNodes[i];

#ifdef c_net_debug
    debug_log << "Processing layer " << i << "\n\n\n";
    debug_log << "Nodes in current layer: " << nodes << "\n";
    debug_log << "Nodes in previous layer: " << nodes_prev << "\n";
#endif // c_net_debug

		//number of nodes in next layer (unless output layer)
		if(i < (parm.layers - 1))
		{
		    nodes_next = parm.netLayerNodes[i + 2];
#ifdef c_net_debug
    debug_log << "Nodes in next layer: " << nodes_next << "\n";
#endif // c_net_debug
	    }

		//loop through nodes
		for( j=0; j<nodes; j++)
		{

            activation = layers[i].node_activation[j];

#ifdef c_net_debug
    debug_log << "Processing node " << j << " \n\n";
    debug_log << "activation value " << activation << "\n";
#endif // c_net_debug

            //check if output layer
            if(i == (parm.layers - 1))
            {
                delta = activation*(1 - activation)*(desired_outputs[j] - activation);
            }

#ifdef c_net_debug
    debug_log << "desired output " << j << " = " << desired_outputs[j] << "\n";
    debug_log << "looping through " << nodes_prev + 1 << " weights\n";
#endif // c_net_debug

			//loop through weights
			for( k=0; k<(nodes_prev + 1); k++)
			{
#ifdef c_net_debug
    debug_log << "Processing weight " << k << "\n";
#endif // c_net_debug
			    //not output layer
                if(i != (parm.layers - 1))
                {
                    deltaWSum = 0;
                    //sum all the deltaW of next layer
                    for( l=0; l<nodes_next; l++)
                    {
                        deltaWSum += layers[i+1].deltaW[l*(nodes + 1) + k];
                    }
#ifdef c_net_debug
    debug_log << "deltaWSum = " << deltaWSum << "\n";
#endif // c_net_debug
                    delta = activation*(1 - activation)*(deltaWSum);
                }
				
#ifdef c_net_debug
    debug_log << "delta = " << delta << "\n";
#endif // c_net_debug

				//set deltaW
				layers[i].deltaW[j*(nodes_prev + 1) + k] = delta*layers[i].weights[j*(nodes_prev + 1) + k];

#ifdef c_net_debug
    debug_log << "weight = " << layers[i].weights[j*(nodes_prev + 1) + k] << "\n";
    debug_log << "deltaW " << j << ", " << k << " = " << layers[i].deltaW[j*(nodes_prev + 1) + k] << "\n";
#endif // c_net_debug

				//adjust weight
				if(k == nodes_prev)
				{
					//bias weight
					layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta;
#ifdef c_net_debug
    debug_log << "bias weight\n" << "weight change = " << parm.learningRate*delta << "\n";
    debug_log << "new weight = " << layers[i].weights[j*(nodes_prev + 1) + k] << "\n";
#endif // c_net_debug
				}
				else
				{
					//input layer special case
					if(i == 0)
					{
						layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta*inputs[k];
#ifdef c_net_debug
    debug_log << "input layer\n" << "weight change = " << parm.learningRate*delta*inputs[k] << "\n";
    debug_log << "new weight = " << layers[i].weights[j*(nodes_prev + 1) + k] << "\n";
#endif // c_net_debug
					}
					else
					{
					    //if(layers[i - 1].node_activation[k] >= 0.5)
                        //{
                        //    layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta;
                        //}
						layers[i].weights[j*(nodes_prev + 1) + k] += parm.learningRate*delta*layers[i - 1].node_activation[k];
#ifdef c_net_debug
    debug_log << "weight change = " << parm.learningRate*delta*layers[i - 1].node_activation[k] << "\n";
    debug_log << "new weight = " << layers[i].weights[j*(nodes_prev + 1) + k] << "\n";
#endif // c_net_debug

					}
				}
			}
		}
	}
}

/*******************************************************
Function: C_Net::fullTrainingRun()
Author: 

Description: 

Parameters:
	None

Return:
	None

********************************************************/
void C_Net::fullTrainingRun(bool print)
{
  int i, j;
	int a1, a2, a3;

	double s_error, output_diff1, output_diff2, output_diff3;

	for (i = 0; i < parm.numberTrainingEpochs; i++)
	{
	  s_error = 0.0;

    //randomize training sets
    randomizeTrainingSets();
    //loop through training sets
    for(j=0; j<sets_training_data; j++)
    {
      //set inputs
      inputs = training_data[j] + 1;

      //set desired outputs
			if(training_data[j][0] < parm.lowCutoffNorm)
			{
				a1 = 1;
				a2 = 0;
				a3 = 0;
			}
			else if(training_data[j][0] < parm.mediumCutoffNorm)
			{
				a1 = 0;
				a2 = 1;
				a3 = 0;
			}
			else
			{
				a1 = 0;
				a2 = 0;
				a3 = 1;
			}
			desired_outputs[0] = a1;
			desired_outputs[1] = a2;
			desired_outputs[2] = a3;

            UpdateNet();

            //add s_errror
            output_diff1 = desired_outputs[0] - outputs[0];
            output_diff2 = desired_outputs[1] - outputs[1];
            output_diff3 = desired_outputs[2] - outputs[2];
            output_diff1 = output_diff1*output_diff1;
            output_diff2 = output_diff2*output_diff2;
            output_diff3 = output_diff3*output_diff3;
            s_error += (output_diff1 + output_diff2 + output_diff3)/3.0;


      RunTrainingCycle();

    }

    s_error = s_error/(double)sets_training_data;

    //checks if we want epoch number printed
    if (print)
    {
     	if (( (i+1) % 10 ) == 0)
     		printEpoch(i+1, s_error);
    }
	}

}

/*******************************************************
Function: C_Net::testRun()
Author: 

Description: Tests the array of data that is given

Parameters:
	None

Return:
	None

********************************************************/

void C_Net::testRun()
{
  int i, j;
	int a1, a2, a3;
  //loop through training sets
  for(j=0; j<sets_training_data; j++)
  {
    //set inputs
    inputs = training_data[j] + 1;
		cout << "inputs: = ";
		for (i = 0; i < parm.netLayerNodes[0]; i++)
			cout << inputs[i] << " ";
		cout << endl;

    //set desired outputs
		if(training_data[j][0] < parm.lowCutoffNorm)
		{
			a1 = 1;
			a2 = 0;
			a3 = 0;
		}
		else if(training_data[j][0] < parm.mediumCutoffNorm)
		{
			a1 = 0;
			a2 = 1;
			a3 = 0;
		}
		else
		{
			a1 = 0;
			a2 = 0;
			a3 = 1;
		}

    UpdateNet();

		desired_outputs[0] = a1;
		desired_outputs[1] = a2;
		desired_outputs[2] = a3;

    cout << "Desired Output " << j << " : " << desired_outputs[0] <<
      ", " << desired_outputs[1] << ", " << desired_outputs[2] <<
      ". Test output: " << outputs[0] << ", " << outputs[1] << ", "
      << outputs[2] << endl;
  }
}

/*******************************************************
Function: C_Net::CVtestRun()
Author: 

Description: Tests a single year of data. Used for testing 
with cross validation

Parameters:
	None

Return:
	None

********************************************************/

void C_Net::CVtestRun()
{
	int i;
	int a1, a2, a3;
  //loop through training sets
  cout << "starting cross validation test run" << endl;
  //set inputs
  inputs = training_data[sets_training_data] + 1;
  cout << inputs[0] << " is the first input " << training_data[sets_training_data][1] << endl;
  //set desired outputs
  if(training_data[sets_training_data-1][0] < parm.lowCutoffNorm)
	{
  	a1 = 1;
		a2 = 0;
		a3 = 0;
	}
	else if(training_data[sets_training_data-1][0] < parm.mediumCutoffNorm)
	{
		a1 = 0;
		a2 = 1;
		a3 = 0;
	}
	else
	{
		a1 = 0;
		a2 = 0;
		a3 = 1;
	}

  UpdateNet();

  desired_outputs[0] = a1;
	desired_outputs[1] = a2;
	desired_outputs[2] = a3;

  cout << "Desired Output: " << desired_outputs[0] <<
    ", " << desired_outputs[1] << ", " << desired_outputs[2] <<
    ". Test output: " << outputs[0] << ", " << outputs[1] << ", "
     << outputs[2] << endl;
}

/*******************************************************
Function: C_Net::setData()
Author: 

Description: Moves the parameter data the parm parameter

Parameters:
	newData		- holds the data from the parameter file 

Return:
	None

********************************************************/

void C_Net::setData(Parameters newData)
{
	parm = newData;
}

/*******************************************************
Function: C_Net::TrainNet
Author: 

Description: Calls the functions to train the data 

Parameters:
	None

Return:
	None

********************************************************/

unsigned int C_Net::TrainNet(void)
{
	Initialize();
	readInData();
	fullTrainingRun(true);
	SaveWeightsToFile();
	return 1;
}

/*******************************************************
Function: C_Net::TestNet()
Author: 

Description: This function gets the data from the parameter
file and then test the data

Parameters:
	None

Return:
	None

********************************************************/

unsigned int C_Net::TestNet(void)
{
    Initialize();
    readInData();
    testRun();

	return 1;
}

/*******************************************************
Function: C_Net::CrossValidateNet()
Author: 

Description: Goes through the data and takes one point out, 
trains on the rest and then tests the point that was taken
out. This is repeated for each data point that is given.

Parameters:
	None

Return:
	None

********************************************************/

unsigned int C_Net::CrossValidateNet(void)
{
	int i, j, m;

	double temp;

	Initialize();
	readInData();

	m = parm.PDSIdata + parm.burnedAcreage;

	//double temp_training_data[sets_training_data][m];

	temp_training_data = new double*[sets_training_data];

    for( i=0; i<sets_training_data; i++)
    {
        temp_training_data[i] = new double[m];
    }

  //put clean copy of training data in temp

  for (i = 0; i < sets_training_data; i++)
  {
  	temp_training_data[i][0] = training_data[i][0];
  	for (j = 0; j < m; j++)
  	{
  		temp_training_data[i][j] = training_data[i][j];
  	}
  }

	for (i = 0; i < sets_training_data; i++)
	{
		//make new weights file for each training call
		if (i != 0)
		{
			SetSmallRandomWeights();
		}

		//swtiches point that will be tested with last point
		for (j = 0; j < m; j++)
		{
			temp = training_data[i][j];
			training_data[i][j] = training_data[sets_training_data-1][j];
			training_data[sets_training_data-1][j] = temp;
		}
		//decrease 1 since one point was 'removed'
		sets_training_data--;
		// train on remeaining data

		fullTrainingRun(false);

		// test on training_data[i][all]
		CVtestRun();


		// reset training_data and sets_training_data
		for (j = 0; j < m; j++)
		{
			training_data[i][j] = temp_training_data[i][j];
			training_data[sets_training_data][j] = temp_training_data[sets_training_data][j];
		}
		sets_training_data++;
	}

	for( i=0; i<sets_training_data; i++)
    {
        delete[] temp_training_data[i];
    }
	delete[] temp_training_data;

	//print test results 
	return 0;
}

/*******************************************************
Function: C_Net::printEpoch()
Author: 

Description: This function prints the epoch number and
the root mean square error to the command line.

Parameters:
	eNum					- epoch number
	squareError 	- mean squared error that is calculated

Return:
	None

********************************************************/

void C_Net::printEpoch(int eNum, double squareError)
{
	//need to calcualte RMS
	double rms;

	//rms = squareError / eNum;
	rms = sqrt(squareError);

	cout << "Epoch Number: " << eNum << " RMS: " << rms << endl;
}

/*******************************************************
Function: C_Net::printResults()
Author: 

Description: This function prints the year, actual fire
severity and the predicted fire severity. If the actual 
and predicted do not match, an * is printed as well.

Parameters:
	None

Return:
	None

********************************************************/
void C_Net::printResults()
{

	cout << "Year, Actual, Predicted" << endl;
	/*************
	for (int i = 0; i < years; i++)
	{
		cout << year << ", " << actual, << ", " << predicted;
		if (predicted != actual)
			cout << ", *";

		cout << endl;
	}


	***************/
}