#include "paramscontrols.h"
#include <iostream>

template<typename T>
class A
{

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
	C<int> c;
	ParamsControls pcs;
	pcs.exec(argc, argv);


#ifdef WIN32
	//system("pause");
#endif
    return 0;
}

