/**************************************************************************//**
 * @file
 *
 * @brief This file contains the function definitions for the Input class
 *****************************************************************************/
#include "Input.h"

//for turning a char array to an int array
#include <vector>
#include <sstream>

/*******************************************************
Function: Input::Input()
Author: 

Description: This function sets the name of the parameter
file

Parameters:
	paramFileName		- the name of the parameter file

Return:
	None

********************************************************/
Input::Input( string paramFileName )
{
	parm.paramFile = paramFileName;
}

/*******************************************************
Function:Input::~Input()
Author: 

Description: Deallocates all the dynmaically allocated arrays

Parameters:
	None

Return:
	None

********************************************************/
Input::~Input()
{
	if (parm.netLayerNodes != nullptr)
	{
		delete parm.netLayerNodes;
	}
}

/*******************************************************
Function: Input::parseParams()
Author: Allison Bodvig

Description: Reads in the parameter file and puts each
value in a separate row in the prms array

Parameters:
	None

Return:
	returns true if the parameter file was read in

********************************************************/
bool Input::parseParams()
{
	char line[256] = { 0 };
	char firstChar;
	int j = 0;
	bool found;

	char prms[20][50] = { 0 };
	ifstream param;

	if (!openFile( param ))
	{
		return false;
	};

	//read in the file
	while (param)
	{
		//look at first character
		param.get(firstChar);

		//if # or % ignore
		if (firstChar == '#' || firstChar == '%')
		{
			//Removes the current line
			param.getline(line, 256, '\n');
		}
		else
		{
			//checks if the line is empty
			if (firstChar != '\n')
				param.putback(firstChar);

			//reads inthe line
			param.getline(line, 256, '\n');

			//checks to make sure the line isnt a comment
			if (line[0] != '#' && line[0] != '%')
			{
				found = false;
				//reads in line until it reaches the comment
				for (int i = 0; i < 50; ++i)
				{
					//stoes char in the correct row
					if (line[i] != '#' && found == false)
					{
						prms[j][i] = line[i];
					}
					else
						found = true;

					line[i] = 0;

				}
				j++;
			}
		}
	}
	//close the file
	param.close();

	//moves the data into the parameter file
	setData(prms);

	return true;
}

/*******************************************************
Function: Input::setData()
Author: 

Description: sets the data read in fromt he parameters 
file to the parm structure

Parameters:
	prms 		- 2D array of the parameters that were read in

Return:
	None

********************************************************/
void Input::setData(char prms[20][50])
{
	int i;

	parm.weightsFile = prms[0];
	//get rid of trailing spaces in weightsFile
	i = 0;
	while(1)
	{
		if((int)parm.weightsFile[i] == 32)
		{
			parm.weightsFile[i] = 0;
			break;
		}
		if((int)parm.weightsFile[i] == 0)
		{
			break;
		}
		i++;
	}
	parm.numberTrainingEpochs = stoi((string)prms[1]);
	parm.learningRate = stod((string)prms[2]);
	parm.momentum = stod(prms[3]);
	parm.threshold = stod(prms[4]);
	parm.layers = stoi(prms[5]);

	//todo convert prms[6] to int array[layers]
	parm.netLayerNodes = nullptr;
	parm.netLayerNodes = new (nothrow) int[parm.layers + 1];

	string temp = prms[6];
	istringstream myStringStream(temp); //used to parse char* into int*
	i = 0;
	while (getline(myStringStream, temp, ' ') && i < parm.layers + 1)
	{
		parm.netLayerNodes[i] = (stoi(temp));
		//cout << "net layer nodes has " << parm.netLayerNodes[i] << endl;
		i++;
	}

	parm.dataFile = prms[7];
	parm.burnedAcreage = stoi(prms[8]);
	parm.PDSIdata = stoi(prms[9]);
	parm.endMonth = stoi(prms[10]);

	parm.classes = stoi(prms[11]);

	parm.lowCutoff = stoi(prms[12]);
	parm.mediumCutoff = stoi(prms[13]);
	//High is anything above the medium cutoff
}

/*******************************************************
Function: Input::getData()
Author: Johnathan

Description: Returns the parameters

Parameters:
	None

Return:
	parm which holds the paramters from the parameter fiel

********************************************************/
Parameters Input::getData()
{
	return parm;
}

/*******************************************************
Function: Input::openFile()
Author: Johnathan

Description: Checks if the file can be opened or not. Prints
error messagae and returns false if the file was not found.

Parameters:
	fin 	- file that is to be opened

Return:
	True or false depending on if the file was opened or not

********************************************************/
bool Input::openFile( ifstream &fin )
{
	fin.open(parm.paramFile);

	if (fin.fail())
	{
		cerr << "Could not open parameter file. Exiting Program" << endl;
		return false;
	}

	return true;
}
