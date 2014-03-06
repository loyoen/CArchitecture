#include "classB.h"

classB::classB ( )
{
	
}

classA* classB::method_3 ()
{
	method_4 ();
	cA->method_2();
	return cA;
}

void classB::method_4 ()
{
	//cout<<"method4..."<<endl;
}

classB::~classB ()
{

}
