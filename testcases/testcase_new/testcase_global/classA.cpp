#include "classA.h"

// 定义一个全局变量
//int		globalVar = 0;
classA* catmp;

classA::classA ( )
{
	// 与全局变量有关
	//extern int		globalVar;
	attribute_1		= 0;
	attribute_2		= 0;
}

int classA::method_1 ( )
{
	method_2 ( );
	//cC.method_6();
	return 0;
}

void classA::method_2 ( )
{
	//cout<<"method2..."<<endl;
}

classA::~classA ( )
{

}

cA::cA ()
{
	m_aa = NULL;
	// 与classA的成员变量共享全局变量
	//varca_1	= globalVar;
}
// 返回类型为其他类的类指针以及参数为其他类的类指针类型
classA* cA::method_ca1( classA* a )
{
	catmp = m_aa;
	//...由catmp或a产生一系列的关系，但不确定是否没有显示调用
	catmp->method_1();
	return catmp;
}
void cA::method_ca2 ( )
{

}

