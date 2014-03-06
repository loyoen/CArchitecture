#include "cE.h"
cE::cE()
{
	objD = new cD();
}
cE::~cE()
{

}

void cE::m_E1()
{
	objD->m_D1();
}