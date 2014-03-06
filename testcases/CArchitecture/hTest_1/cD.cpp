#include "cD.h"
#include "cF.h"
cD::cD()
{
	objG2= new cG();
}
cD::~cD()
{

}
void cD::m_D1()
{
	cF* objF = new cF();
	objF->m_F1();
	objG2->m_G2();
}