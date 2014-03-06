#ifndef CLASSC_H
#define CLASSC_H

#include "classB.h"
#include <iostream>
using namespace std;
template <class T>
class classC : public cA 
{
public:
	int		attribute_5;
	int		attribute_6;

	classB	cB;

	void method_5 ( );
	void method_6 ( );

	//Constructor
	classC ( ) {}
	//Destructor
	~classC ( ) {}
};
#endif

