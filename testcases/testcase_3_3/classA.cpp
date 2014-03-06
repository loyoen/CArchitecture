#include "classA.h"

classA::classA ( )
{
	attribute_1		= 0;
	attribute_2		= 0;
}

void classA::method_1 ( )
{
	method_2 ( );
	cB.method_4();
	cC.method_6();
}

void classA::method_2 ( )
{
	//cout<<"method2..."<<endl;
}

classA::~classA ( )
{

}