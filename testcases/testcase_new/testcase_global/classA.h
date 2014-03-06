#ifndef CLASSA_H
#define CLASSA_H

//#include "classC.h"
#include <iostream>
using namespace std;


class classA
{
public:
	int		attribute_1;
	int		attribute_2;


	int  method_1 ( );
	void method_2 ( );


	classA ( );

	~classA ( );
};

// 这个类名和classA类有个对象相同，检验是否会冲突
class cA
{
public:
	int		varca_1;
	classA*	m_aa;

	cA ();

	classA*		method_ca1 ( classA* a );
	void	method_ca2 ( );

	~cA() {}
};

#endif
