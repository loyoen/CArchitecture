#include "classA.h"

// ����һ��ȫ�ֱ���
//int		globalVar = 0;
classA* catmp;

classA::classA ( )
{
	// ��ȫ�ֱ����й�
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
	// ��classA�ĳ�Ա��������ȫ�ֱ���
	//varca_1	= globalVar;
}
// ��������Ϊ���������ָ���Լ�����Ϊ���������ָ������
classA* cA::method_ca1( classA* a )
{
	catmp = m_aa;
	//...��catmp��a����һϵ�еĹ�ϵ������ȷ���Ƿ�û����ʾ����
	catmp->method_1();
	return catmp;
}
void cA::method_ca2 ( )
{

}

