#include <iostream>
#include <string>
using namespace std;

class CAttribute
{
public:
	int		m_attIndex;
	string	m_attName;

	CAttribute ( int index, string attName );
	void	outputAttributes ( string fileName );
};

class CMethod
{
public:
	int		m_mthIndex;
	string	m_mthName;

	CMethod ( int index, string mthName );
	void	outputMethods ( string fileName );
};

class CClass
{
public:
	int			m_clsIndex;
	string		m_clsName;

	CAttribute	*pAttribute;
	CMethod		*pMethod;

	CClass	( int index, string clsName );
	void	outputClasses ( string fileName );
};

class CSimplex
{
public:
	int			m_simIndex;

	CClass		*pClass;

	CSimplex ( int index );

	//void		addMethod ();
	//void		addClass ();

	void		outputSimplex ( string fileName );
};


