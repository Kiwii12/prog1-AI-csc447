/***************************************
Artificial Intelligence
Program 1 - Wildfire Prediction

Authors: Jacob St. Amand, Johnathan Avkerman, and  Allison Bodvig

Due Date: February 24, 2016

Description: Once a weights file has been made from training. It 
test the net on the given data and outputs the percent correct


Usage: ANNtest <parameter>

****************************************/

#include <iostream>
#include "C_Net.h"
#include "Input.h"

/*******************************************************
Function: main
Author: Jacob, Johnathan, Allison

Description: This function checks for correct usage and then
calls the appropiate functions to read in the parameters file
and test the data. 

Parameters:
	argc  		- number of arguments
	argv	 		- list og arguments from the command line

Return:
	None

********************************************************/

int main(int argc, char** argv)
{
	int error;
	bool b_error;

	//checks for correct number of arguments
	if (argc != 2)
	{
		cout << "Usage: ANNtrain <ParmeterFile>" << endl;
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

	//test the net
	net.TestNet();

	return 0;
}

