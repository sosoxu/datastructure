#include "paramscontrols.h"

int main(int argc, char *argv[])
{
	ParamsControls pcs;
	pcs.exec(argc, argv);

#ifdef WIN32
	//system("pause");
#endif
    return 0;
}

