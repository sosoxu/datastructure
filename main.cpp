#include "paramscontrols.h"
#include <iostream>
#include <vector>
#include "utlity.h"

template<typename T>
class A
{
public:
	void fun(){};
};
template<typename T>
class B : public A<T>
{

};
template<typename T>
class C
{
public:
	C()
	{
		A<T>* a = new B<T>;
		B<T>* b = static_cast<B<T>* >(a);
	}
};
int main(int argc, char *argv[])
{
	ParamsControls pcs;
	pcs.exec(argc, argv);


#ifdef WIN32
	//system("pause");
#endif
    return 0;
}

