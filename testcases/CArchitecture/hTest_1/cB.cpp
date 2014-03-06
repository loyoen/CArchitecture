#include "cB.h"

cB::cB()
{
	objA	= new cA();
	objG1	= new cG();
}
cB::~cB()
{

}

void cB::m_B1()
{
	objA->m_A1();
	objG1->m_G1();
}