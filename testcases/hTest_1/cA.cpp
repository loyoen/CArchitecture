#include "cA.h"
#include "cC.h"
cA::cA()
{
	//objC = new cC();
}
cA::~cA()
{

}

void cA::m_A1(cC* objC)
{
	objC->m_C1();
}
