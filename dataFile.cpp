#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//this fucntion will read in the data file
//also has functions to normalize and find the min/max values 

//PDSI values [0][0] - year [0][1] - January [0][2] - February etc
//arces burned [year][acrees]

float findMin (float values[][13], int years, int vals);
float findMax (float values[][13], int years, int vals);
float normalize(float min, float max, float val);


float normalize(float min, float max, float val)
{
	return ((val - min) / (max - min));
}

float findMin (float values[][13], int years, int vals)
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

float findMax (float values[][13], int years, int vals)
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

int main(int argc, char const *argv[])
{
	ifstream dataFile;
	float PDSI[100][13] = {0};
	float NormPDSI[100][13] = {0};
	float acres[100][2] = {0};
	int j = 0;
	char value[15];
	float min, max;

	dataFile.open(argv[1]);

	if (dataFile.fail())
	{ 
		cout << "Unable to open " << argv[1] << endl;;
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
			if ( i == 12 )
			{
				dataFile.getline(value, 10, '\n');
			}

			
			PDSI[j][i] = atof(value);
			//cout << PDSI[j][i] << endl;
		}

		j++;

	}

	//for PDSI use min(PDSI, j, 13);
	//for BurnedAcreage use min(acres, j , 2);

	return 0;
}