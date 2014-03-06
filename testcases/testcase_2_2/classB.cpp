#include "classB.h"

classB::classB ( )
{
	var_4	= 0 ;
	var_5	= 0 ;
	var_6	= 0 ;
}

void classB::method_3 (int var )
{
	//cout << " method3 called method4... " << endl << var <<endl;
	//classB cB = new classB();
	//classA *cA = new classA();
	cA.method_1();
	method_4 ( ) ;
}

void classB::method_4 ( )
{
	//cout << " the called method4... " << endl;
}

void classB::method_5 (int var )
{
	//cout << " the calling method5... " << var << endl;
	method_4 ( ) ;
}

classB::~classB ( )
{

}