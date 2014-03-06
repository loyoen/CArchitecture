//test class B
#include "classA.h"
#include <iostream>
using namespace std ;

//class classA;
class classB 
{
//protected:
public:
	int		var_4 ;
	int		var_5 ;
	int		var_6 ;

	classA  cA;

public:
	classB ( ) ;
	void method_3 ( int var ) ;
	void method_4 ( ) ;
	void method_5 ( int var ) ;
	~classB ( ) ;

};

