/**************************************************************************//**
 * @file
 *
 * @brief This file contains the function definitions for the ANN class
 *****************************************************************************/
#include "C_LoadParameters.h"

C_LoadParameters::C_LoadParameters( string paramFileName )
{
	paramFile = paramFileName;
}

C_LoadParameters::C_LoadParameters()
{
	paramFile = "Parameter.prm";
}

C_LoadParameters::~C_LoadParameters()
{
    delete[] netLayerNodes;
}

//Reads in the parameter file and puts each value in a separate row in the prms array
//author - Allison
bool C_LoadParameters::parseParams()
{
	char line[256] = { 0 };
	char firstChar;
	int j = 0;
	bool found;

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
				//cout << prms[j] << endl;
				j++;
			}
		}
	}
	//close the file
	param.close();

	setData();

	return true;
}

void C_LoadParameters::setData()
{
	weightsFile = prms[0];
	numberTrainingEpochs = stoi((string)prms[1]);
	learningRate = stod((string)prms[2]);
	momentum = stod(prms[3]);
	threshold = stod(prms[4]);
	layers = stoi(prms[5]);

	//todo convert prms[6] to uint32_t array[layers]

	//string trainFile = prms[7];
	dataFile = prms[7];
	burnedAcreage = stoi(prms[8]);
	PDSIdata = stoi(prms[9]);
	endMonth = stoi(prms[10]);

	classes = stoi(prms[11]);

	lowCutoff = stoi(prms[12]);
	mediumCutoff = stoi(prms[13]);
	//High is anything above the medium cutoff
}

bool C_LoadParameters::openFile( ifstream &fin )
{
	fin.open(paramFile);

	if (fin.fail())
	{
		cerr << "Could not open parameter file. Exiting Program" << endl;
		return false;
	}

	return true;
}
