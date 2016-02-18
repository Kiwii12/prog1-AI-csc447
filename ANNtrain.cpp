#include "C_Net.h"
#include "Input.h"

//function prototypes
//int train_Net(C_Net* Net, C_LoadParameters* Parameters);

int main(int argc, char** argv)
{
	int error;
	bool b_error;

	if(argc != 2)
		return 1;

	//initialize classes
    C_Net Net;
	Input Parameters(argv[1]);

	//load parameters
	b_error = Parameters.parseParams();
	if(b_error == false)
		return 2;

	//initialize net
	//(this will segfault. because netLaerNodes isn't parsed in)
	//error = Net.Initialize(Parameters.layers, Parameters.netLayerNodes);
	if(error)
		return 3;

//	error = train_Net(&Net, &Parameters);
	if(error)
		return 4;


	return 0;
}

//int train_Net(C_Net* Net, C_LoadParameters* Parameters)
//{

//	return 0;
//}
