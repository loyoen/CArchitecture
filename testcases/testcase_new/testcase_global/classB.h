#ifndef CLASSB_H
#define CLASSB_H
#pragma once

#include "classA.h"
#include <iostream>
using namespace std;

class classB
{
public:
	int		attribute_3;
	int		attribute_4;

	classA	*cA;

	classA* method_3 ( );
	void method_4 ( );

	//Constructor
	classB ( );
	//Destructor
	~classB ( );
};
#endif

