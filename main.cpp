#include <iostream>
#include "bstreetest.h"

const char* sc_help = "-h";
const char* sc_version = "-v";
const char* sc_bst = "-bst";
const char* sc_avl = "-avl";
const char* sc_rb = "-rb";

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char* param = argv[1];
		if (strcmp(param, sc_help) == 0)
		{
			printf("-bst : binary search tree\n"
				"-avl : avl tree\n"
				"-rb : red-black tree\n");
		}
		else if (strcmp(param, sc_version) == 0)
		{
			printf("version : 1.0.0\n");
		}
		else if (strcmp(param, sc_bst) == 0)
		{
			BstreeTest bsttest;
			bsttest.test();
		}
		else if (strcmp(param, sc_avl) == 0)
		{
		}
		else if (strcmp(param, sc_rb) == 0)
		{
		}
	}
	else
	{
		printf("please input -h to get help\n");
	}
   
#ifdef WIN32
	system("pause");
#endif

    return 0;
}

