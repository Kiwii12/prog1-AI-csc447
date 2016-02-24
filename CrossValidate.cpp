/***************************************
Artificial Intelligence
Program 1 - Wildfire Prediction

Authors: Jacob St. Amand, Johnathan Avkerman, and  Allison Bodvig

Due Date: February 24, 2016

Description: 


Usage: ANNtest <parameter>

****************************************/

#include "C_Net.h"
#include "Input.h"

/*******************************************************
Function: main
Author: 

Description: This function checks for correct usage and then
calls the appropiate functions to read in the parameters file
and use cross validation to train and test the data.

Parameters:
	argc  		- number of arguments
	argv	 		- list og arguments from the command line

Return:
	None

*****************************************************/

int main(int argc, char** argv)
{
	int error;
	bool b_error;

	if (argc != 2)
	{
		cout << "Usage: CrossValidate <ParmeterFile>" << endl;
		return 1;
	}

	//initialize classes
  C_Net net;
	Input parameters(argv[1]);

	//load parameters
	b_error = parameters.parseParams();
	if(b_error == false)
		exit(2);

	//Passes ParamFile to the net
	net.setData(parameters.getData());

	net.CrossValidateNet();

	return 0;
}