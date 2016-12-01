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
		A<T>*& c = a;
		//B<T>*  d = static_cast<B<T>*>(c);
	}
};

class TA
{};
class TB : public TA
{
};
int main(int argc, char *argv[])
{
	TA* ta = new TB();
	TA*& taa = ta;
	TB* tbb = static_cast<TB*>(ta);
	TB*& tb = tbb;
	C<int> cc;
	ParamsControls pcs;
	pcs.exec(argc, argv);


#ifdef WIN32
	//system("pause");
#endif
    return 0;
}

