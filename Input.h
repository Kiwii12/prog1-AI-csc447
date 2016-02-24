/**************************************************************************//**
 * @file
 *
 * @brief This file contains the parent Class for ANN.cpp.
 *****************************************************************************/
#include "Parameters.h"

#ifndef __INPUT__H__
#define __INPUT__N__
class Input
{
public:
/******************************************************************************
*                         Function Prototypes
******************************************************************************/
	//takes a paramfile.prm file and reads the data into a structure
	Input( string paramFileName );

	~Input();

	//does the actual converting from *.prm file to internal data 
	bool parseParams();

	//converts internal data to a Parameter structure
	void setData(char prms[20][50]);
	//returns the parameter structure
	Parameters getData();

	//opens a file
	bool openFile(ifstream &fin);

	//data
	Parameters parm; //Parameters structure
};

#endif