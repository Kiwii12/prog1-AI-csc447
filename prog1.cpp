#include "Input.h"
#include "C_Net.h"

int main(int argc, char const *argv[])
{
	if (argc != 2)
		cout << "Usage: " << endl;
	Input ann(argv[1]);
	ann.parseParams();
	C_Net net;
	net.setData(ann.getData());

	//net.getNodeData(<Possibly FileName>);

	//net.trainNode();


	return 0;
}