/**************************************************************************//**
 * @file
 *
 * @brief This file contains the function definitions for the ANN class
 *****************************************************************************/
#include "ANN.h"

ANN::ANN( string paramFileName )
{
	paramFile = paramFileName;
}

ANN::~ANN()
{
}

//Reads in the parameter file and puts each value in a separate row in the prms array
//author - Allison
bool ANN::parseParams()
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
				//cout << prms[j] << endl;
				j++;
			}
		}
	}
	//close the file
	param.close();

	setData(prms);

	return true;
}

void ANN::setData(char prms[20][50])
{
	string weightsFile = prms[0];
	int numberTrainingEpochs = stoi((string)prms[1]);
	double learningRate = stod((string)prms[2]);
	double momentum = stod(prms[3]);
	double threshold = stod(prms[4]);
	int layers = stoi(prms[5]);

	//todo convert prms[6] to int array[layers]

	string trainFile = prms[7];
	int burnedAcreage = stoi(prms[8]);
	int PDSIdata = stoi(prms[9]);
	int endMonth = stoi(prms[10]);

	int classes = stoi(prms[11]);

	int lowCutoff = stoi(prms[12]);
	int mediumCutoff = stoi(prms[13]);
	//High is anything above the medium cutoff
}

bool ANN::openFile( ifstream &fin )
{
	fin.open(paramFile);

	if (fin.fail())
	{
		cerr << "Could not open parameter file. Exiting Program" << endl;
		return false;
	}
	
	return true;
}
