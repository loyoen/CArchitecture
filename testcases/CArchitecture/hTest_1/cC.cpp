#include "cC.h"

cC::cC()
{
	objB = new cB();
}
cC::~cC()
{

}
void cC::m_C1()
{
	objB->m_B1();
}