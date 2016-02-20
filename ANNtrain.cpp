#include "C_Net.h"
#include "Input.h"

//function prototypes
//int train_Net(C_Net* Net, C_LoadParameters* Parameters);

int main(int argc, char** argv)
{
	//int error;
	bool b_error;

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
		return 2;

	//Passes ParamFile to the net
	net.setData(parameters.getData());

	net.TrainNet();

	net.SaveWeightsToFile();

	return 0;
}

