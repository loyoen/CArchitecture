#ifndef CLASSD_H
#define CLASSD_H
#pragma once

#include "classB.h"
#include "classA.h"
#include <iostream>
using namespace std;

class classD
{
	//Attributes
public:
	int		attribute_7;
	int		attribute_8;
    classA  cAa;
    classB	cBb;

	//Methods
	void method_7 ( );
	void method_8 ( );

	//Constructor
	classD ( );
	//Destructor
	~classD ( );
};

#endif
