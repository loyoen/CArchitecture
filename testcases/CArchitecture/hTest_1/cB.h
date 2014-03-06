#ifndef CB_H
#define CB_H
#include "cA.h"
#include "cG.h"

class cB
{
public:
	cA* objA;
	cG* objG1;
	
	cB();
	~cB();

	void m_B1();
};
#endif