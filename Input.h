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

	Input( string paramFileName );

	Input();

	~Input();

	bool parseParams();

	void setData(char prms[20][50]);
	Parameters getData();

	bool openFile(ifstream &fin);


	//data
	Parameters parm;

};

#endif