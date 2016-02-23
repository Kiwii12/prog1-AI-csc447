/**************************************************************************//**
 * @file
 *
 * @brief This file contains the function definitions for the ANN class
 *****************************************************************************/
#include "Input.h"

//for turning a char array to an int array
#include <vector>
#include <sstream>

Input::Input( string paramFileName )
{
	parm.paramFile = paramFileName;
}

Input::~Input()
{
	if (parm.netLayerNodes != nullptr)
	{
		delete parm.netLayerNodes;
	}
}

/*******************************************************
Function: parseParams
Author: Allison Bodvig

Description: Reads in the parameter file and puts each
value in a separate row in the prms array

Return:
	returns true if the parameter file was read in

********************************************************/
//author - Allison
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

	setData(prms);

	return true;
}

void Input::setData(char prms[20][50])
{
	parm.weightsFile = prms[0];
	parm.numberTrainingEpochs = stoi((string)prms[1]);
	parm.learningRate = stod((string)prms[2]);
	parm.momentum = stod(prms[3]);
	parm.threshold = stod(prms[4]);
	parm.layers = stoi(prms[5]);
	//int layers = parm.layers;

	//todo convert prms[6] to int array[layers]
	parm.netLayerNodes = nullptr;
	parm.netLayerNodes = new (nothrow) int[parm.layers + 1];

	string temp = prms[6];
	istringstream myStringStream(temp);
	int i = 0;
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

Parameters Input::getData()
{
	return parm;
}

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
