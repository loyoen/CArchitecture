// ATinyTest.cpp : Defines the entry point for the console application.

/*This is a tiny test for testing complexity metrics by coupling and cohesion 
  based on hyper-graph model
*/

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "classA.h"
#include "classB.h"

using namespace std ;

//the main thread
int main ( )
{
	classA	a ;
	classB	b ;
	//a.method_1 ( ) ;
	a.method_2 ( a.var_3 ) ;
	b.method_3 ( b.var_4 ) ;
	//b.method_4 ( ) ;
	b.method_5 ( b.var_5 ) ;
	//Sleep ( 5000 ) ;
	return 0 ;
}
