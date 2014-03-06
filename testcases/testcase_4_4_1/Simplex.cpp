#include "Simplex.h"

CAttribute::CAttribute ( int index, string attName )
{
	m_attIndex	= index;
	m_attName	= attName;

}

void CAttribute::outputAttributes ( string fileName )
{

}

CMethod::CMethod ( int index, string mthName )
{
	m_mthIndex	= index;
	m_mthName	= mthName;
}

void CMethod::outputMethods ( string fileName )
{

}

CClass::CClass ( int index, string clsName )
{
	m_clsIndex	= index;
	m_clsName	= clsName;

	pAttribute	= NULL;
	pMethod		= NULL;
}

void CClass::outputClasses ( string fileName )
{
	pAttribute->outputAttributes ( fileName );
	pMethod->outputMethods ( fileName );
}

CSimplex::CSimplex ( int index )
{
	m_simIndex	= index;

	pMethod		= NULL;
	pClass		= NULL;
}

//void CSimplex::addMethod ( )
//{
//
//}

void CSimplex::addClass ( )
{

}

void CSimplex::outputSimplex ( string fileName )
{
	pClass->outputClasses(fileName);
}

