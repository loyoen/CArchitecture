// ASmallTest.cpp : Defines the entry point for the console application.
/*
 * Project------ ASmallTest
 * File Name---- main.cpp
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-3-30
 * Edition------ 1.0

 * Description-- This is a small test case for parser. It contains three classes, classA, classB and classC.
 *		They have the following relationship A->B, B->C
		
 * Change Log:
 *		Date-----
 *		Staff----
 *		Edition--
 *		Content--
*/

#include "stdafx.h"
#include <iostream>
//#include <Windows.h>
#include "classA.h"
#include "classB.h"
#include "classC.h"
using namespace std;

int main ( )
{
	classA a;
	classB b;
	classC c;
	a.method_1();
	b.method_3();
	c.method_5();
	//Sleep ( 5000 );
	return 0;
}

