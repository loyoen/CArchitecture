#include "classA.h"

classA::classA ( )
{
	var_1	= 0 ;
	var_2	= 0 ;
	var_3	= var_1 + var_2 ;
}

void classA::method_1 ( )
{
	//cout << " the called method1... " << endl;
}

void classA::method_2 ( int var )
{
	//cout << " the calling method2... " << var << endl;
	method_1 ( ) ;
}

classA::~classA ( )
{

}

