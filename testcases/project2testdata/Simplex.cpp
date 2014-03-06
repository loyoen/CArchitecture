#include "Simplex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG_APPEND
stMethod::stMethod ( int nIndex, string strName, string strBody )
//stMethod::stMethod ( int nIndex, string strName )
{
	mthIndex		= nIndex;
	mthName			= strName;
	mthBody			= strBody;
	mthpNext		= NULL;
	mthNextOnDoc	= NULL;
	mthNextOnIvk	= NULL;
}
#endif
stMethod::stMethod ( int nIndex, string strName, char* strBody, int bodyLen )
{
	mthIndex		= nIndex;
	mthName			= strName;
	mthBody			= strBody;
	mthBodyLen		= bodyLen;
	mthpNext		= NULL;
	mthNextOnClass	= NULL;
	mthNextOnDoc	= NULL;
	mthNextOnIvk	= NULL;
}
//stClass::stClass ( int index, string strClName, LPMETHOD pMethod, LPTESTFILE pCurrFile )
stClass::stClass ( int index, string strClName, LPMETHOD pMethod, CTestFile* pCurrFile, char* clsBody, int bodyLen )
{
	m_cIndex			= index;
	className			= strClName;
	pMethod				= NULL;

	mthPhead			= NULL;
	cpNext				= NULL;
	pCurrentFile		= pCurrFile;
	classBody			= clsBody;
	clsBodyLen			= bodyLen;

	cpNext_on_simplex	= NULL;

}

stRelation::stRelation ( string clName, int clIndex )
{
	strName			= clName;
	rClIndex		= clIndex;
	//pRelated		= 
	pNextRelation	= NULL;
	pCls	= new stClass ( rClIndex, strName, NULL, NULL, NULL, 0 );
}

stRelation::~stRelation ( )
{
	if ( pCls )
	{
		delete	pCls;
		pCls	= NULL;
	}
}

stInvoke::stInvoke ( int index, LPCLASS pCl, string mthName )
{
	ivIndex			= index;
	
	pNextMethod		= NULL;
	pNextInvoke		= NULL;
	
	pMethod			= new stMethod ( ivIndex, mthName, NULL, 0 );
}

stInvoke::~stInvoke ( )
{
	if ( pMethod )
	{
		delete	pMethod;
		pMethod	= NULL;
	}
}

CSimplex::CSimplex ( int index, LPCLASS pstClass )
{
	m_nIndex	= index;

	pclassHead	= pstClass;
	pclassTail	= pclassHead;

	pNext		= NULL;

	m_iCnt		= 1;
	//pCurrentDoc = pCurDoc;
}
CSimplex::CSimplex ( LPMETHOD pMethod )
{
	pMethodHead		= pMethod;
	pMethodTail		= pMethodHead;

	pNextByMth		= NULL;

	m_iMthCnt		= 1;
}

CSimplex::~CSimplex ( )
{
	/*if ( pMethodTail )
	{
		delete pMethodTail;
		pMethodTail = NULL;
	}
	if ( pclassTail )
	{
		delete pclassTail;
		pclassTail	= NULL;
	}*/
}

void CSimplex::addSimplexClass ( LPCLASS pstClass )
{
	
	if ( pstClass )
	{
		/*LPCLASS		pHead = NULL;
		pHead	= pstClass->cpNext_on_simplex;*/
		pclassTail->cpNext_on_simplex	= pstClass;
		pclassTail	= pstClass;
		m_iCnt ++;
		//pclassTail->cpNext_on_simplex = NULL;
	}
}
void CSimplex::addSimplexMethod ( LPMETHOD pMethod )
{
	if ( pMethod )
	{
		pMethodTail->mthNextOnIvk	= pMethod;
		pMethodTail					= pMethod;
		m_iMthCnt ++;
	}
}

void stMethod::outputMethodInvoke ( string fileName, LPMETHOD pMethod )
{
	char		cpMethod [128];
	char		cpIndex [128];

	LPMETHOD	pMthTemp;
	LPMETHOD	pMthTmpOnDoc;
	LPMETHOD	pMthTmpIvk;
	ofstream	pfile;
	pfile.open (fileName.c_str());

	pMthTemp		= NULL;
	pMthTmpOnDoc	= NULL;
	pMthTmpIvk		= NULL;

	pMthTmpOnDoc	= pMethod;
	while ( pMthTmpOnDoc )
	{
		pMthTemp	= pMthTmpOnDoc;
		while ( pMthTemp )
		{
			pMthTmpIvk	= pMthTemp;
			while ( pMthTmpIvk )
			{
				#ifdef WIN32
					sprintf_s ( cpIndex, 128, "%d ", pMthTmpIvk->mthIndex );
					sprintf_s ( cpMethod, 128, "%s ", pMthTmpIvk->mthName.c_str() );
				#else
					sprintf ( cpMethod, "%s ", pMthTmpIvk->mthName.c_str() );
				#endif
				pfile.write ( cpIndex, (int) strlen ( cpIndex ) );
				pfile.write ( cpMethod, (int) strlen ( cpMethod ) );	
				if ( pMthTmpIvk->mthNextOnIvk != NULL )
				{
					pfile.write ("->", 2 );
				}
				pMthTmpIvk	= pMthTmpIvk->mthNextOnIvk;
			}
			pfile.write ( "\n", 1 );
			pMthTemp	= pMthTemp->mthpNext;
		}
		pfile.write ( "\n", 1 );
		pMthTmpOnDoc	= pMthTmpOnDoc->mthNextOnDoc;		
	}
}

void stClass::outputClassToFile ( string fileName, LPCLASS pClass )
{
	char	cpstrClass [128];

	ofstream	pfile;
	pfile.open ( fileName.c_str() );

	if ( pClass )
	{
		/*sprintf_s ( cpClass, 128, "%d ", pClass->m_cIndex );
		pfile.write ( cpClass, strlen (cpClass) );*/
		//AfxMessageBox(("write")+pClass->className);
		#ifdef WIN32
			sprintf_s ( cpstrClass, 128, "%s ", pClass->className.c_str() );
		#else
			sprintf ( cpstrClass, "%s ", pClass->className.c_str() );
		#endif
		pfile.write ( cpstrClass, (int) strlen (cpstrClass) );
		pfile.write ( "\n", 1 );
	}
	pfile.close();
}

void CSimplex::outputSimplexToFile ( string fileName, LPSIMPLEX pSimplex )
{
	char		cpSimplex [128];
	char		cpstrClass [128];
	char		cpIndex [128];

	LPCLASS		pClass;
	LPSIMPLEX	pSimTemp;

	ofstream	pfile;
	pfile.open ( fileName.c_str() );

	pSimTemp	= NULL;

	pSimTemp	= pSimplex;
	while ( pSimTemp )
	{
		pClass	= pSimTemp->pclassHead;
		#ifdef WIN32
			sprintf_s ( cpSimplex, 128, "%d ", pSimTemp->m_nIndex );
		#else
			sprintf ( cpSimplex, "%d ", pSimTemp->m_nIndex );
		#endif
		pfile.write ( cpSimplex, (int) strlen ( cpSimplex ) );
		while ( pClass)
		{
			#ifdef WIN32
				sprintf_s ( cpstrClass, 128, "%s ", pClass->className.c_str() );
			#else
				sprintf ( cpstrClass, "%s ", pClass->className.c_str() );
			#endif
			pfile.write ( cpstrClass, (int) strlen ( cpstrClass ) );
			#ifdef WIN32
				sprintf_s ( cpIndex, 128, "%d ", pClass->m_cIndex );
			#else
				sprintf ( cpIndex, "%d ", pClass->m_cIndex );
			#endif
			pfile.write ( cpIndex, (int) strlen ( cpIndex ) );
			pClass	= pClass->cpNext_on_simplex;
		}
		pfile.write ( "\n", 1 );
		pSimTemp = pSimTemp->pNext;
	}
}
