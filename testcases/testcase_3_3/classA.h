#pragma once

#include "classC.h"
#include "classB.h"
#include <iostream>
using namespace std;

class classA
{
	//Attributes
public:
	int		attribute_1;
	int		attribute_2;

	classB	cB;
	classC	cC;

	//Methods
	void method_1 ( );
	void method_2 ( );

	//Constructor
	classA ( );
	//Destructor
	~classA ( );
};

