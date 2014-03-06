#include "cC.h"

cC::cC()
{
}
cC::~cC()
{

}
void cC::m_C1()
{
    cB *objB;
    cA *objA;
    cC *objC = new cC();
    objB = new cB();
    objA = new cA();
    
	objB->m_B1(objC);
    objA->m_A1(objC);
}
