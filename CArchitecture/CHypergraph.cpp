#include "CHypergraph.h"
#include <iostream>
#include <cstdlib>

using namespace std;


CHypergraph::CHypergraph()
{
	coupling = 0;
	cohesion = 0;
	leftSon = NULL;
	rightSon = NULL;
	fatherGraph = NULL;
}