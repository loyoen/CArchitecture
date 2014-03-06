/*
 * Project------ CArchitecture
 * Class Name--- Simplex.h
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-4-8
 * Edition------ 1.0

 * Description-- This is a simplex structure, abstracting the attributes or methods or classes as a simplex object, 
 *		representing the relationship among these objects.

 * Change Log:
 *		Date----- 2013-4-9
 *		Staff---- wxf891201@gmail.com
 *		Edition-- 1.0
 *		Content-- Redefine the CSimplex class

 * Change Log:
 *		Date----- 2013-4-18
 *		Staff---- wxf891201@gmail.com
 *		Edition-- 1.0
 *		Content-- Add the struct stInvoke

*/
#ifndef SIMPLEX_H
#define SIMPLEX_H
#ifdef WIN32
#include "stdafx.h"
#else
#include <string.h>
#endif
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "define.h"
#include "stringnew.h"

using namespace std;
//class CArchitectureDoc;
class	CTestFile;

struct stAttribute
{
	string			attName;
	LPATTRIBUTE		attpNext;
	int				aflag;
};
/*
 * ��Ա�����Ľṹ���������� ������ (�����б�) { �������� };
*/
struct stMethod
{
	string		mthReturnType;
	string		mthName;
	//string		mthBrackt;
	string		mthParam;
	int			mthIndex;
	//string		mthBody;
	char*		mthBody;
	int			mthBodyLen;

	LPMETHOD	mthpNext;		// ��ǰ���к����������һָ��
	LPMETHOD	mthNextOnClass; // һ�����еĺ�����
	LPMETHOD	mthNextOnDoc;	// ���ڽ�������еĺ��������ͷָ����������
	LPMETHOD	mthNextOnIvk;
	int			mflag;

	//stMethod ( int nIndex, string strName, string strBody );
	stMethod ( int nIndex, string strName , char* strBody, int bodyLen );
	void	outputMethodInvoke	( string fileName, LPMETHOD pMethod );
	//void	addInvokeMethod ( LPMETHOD pMth );
};

struct stClass
{
public:
	string		className;	
	//string	objName;		// ��¼����������ֻ����һ�����Ӧһ�������������(�������Ƕ�����������string�������ţ���ע�� )	
	/*string *	objName;
	string *	objNext;*/
	char*		classBody;
	int			clsBodyLen;

	vector <string> objName;
	
	LPCLASS		cpNext;
	int			m_cIndex;

	LPCLASS		cpNext_on_simplex;

	LPMETHOD	mthPhead;					// ���к�����ͷ���

	LPTESTFILE	pCurrentFile;				// ��ǰ���ļ�ָ�룬���ڶԵ�ǰ���к������в���

	//stClass ( int index, string strClName, LPMETHOD pMethod, LPTESTFILE pCurrFile );
	stClass ( int index, string strClName, LPMETHOD pMethod, CTestFile* pCurrFile, char* clsBody, int bodyLen );

	void	outputClassToFile ( string fileName, LPCLASS pClass);

};

/*
 * ��������ݽṹ��Ϊ���������������
 * ����������A,B,C, ��B����C����Ϊ��A�ĳ�Ա���֣�����B��C֮�䲻ȷ����û�й�ϵ����Ҫ���ݺ������ý�һ��ȷ��
 * ��ֹA,B,C������ͬһ�����ϣ�����B,A��C,A������
*/
struct stRelation
{
	LPRELATION	pNextRelation;				// ��ͬһ����Ϊ���ĵ���һ���й����Ĺ�ϵ��
	
	LPCLASS		pCls;						// ĳһ����ϵ�ϵ���
	string		strName;					// �ù�ϵ������
	int			rClIndex;					// �ù�ϵ�������ĸ�����
	//LPSIMPLEX	pNextSimplex;				// ÿһ��������ϵ�����ϵ���һ��simplex

	stRelation ( string clName, int clIndex );
	~stRelation();
	//void addRelatedSimplexClass ( LPCLASS pstClass );
};

/*
 * Ŀ�ģ�����������ĵ��ù�ϵ
 * ����¼��ǰ���е�ÿ����Ա����������������Щ�����Щ���� 
 * ( ��¼�Ķ�����method�ṹ��ÿ����һ����������ù�ϵ����newһ���ýṹ���� )
 * ����Ŀ�ģ��Ƿ�������ѯ��ĳ��������������Щ��ĺ������ù�
*/
struct stInvoke
{
	int			ivIndex;
	LPMETHOD	pMethod;
	LPINVOKE	pNextInvoke;	// ��һ�����ù�ϵ
	LPMETHOD	pNextMethod;	// ���ù�ϵ�ϵ���һ������
	//LPCLASS		pClass;

	stInvoke ( int index, LPCLASS pCl, string mthName );
	~stInvoke();
};

//
class CSimplex
{
public:
	//LPATTRIBUTE		simplexAttribute;		// ��ϵ���еı���
	//LPMETHOD		simplexMethod;			// ��ϵ���еĺ���
	//LPCLASS			simplexClass;			// ��

	LPMETHOD		pMethodHead;
	LPMETHOD		pMethodTail;

	LPCLASS			pclassHead;
	LPCLASS			pclassTail;

	LPSIMPLEX		pNext;					// ��ϵ�������һ����
	LPSIMPLEX		pNextByMth;
	int				m_iMthCnt;

	int				m_nIndex;				// ��ϵ����
	int				m_iCnt;					// һ����ϵ����ļ���

public:
	//Constructor ( each class corresponding a CSimplex )
	CSimplex ( int index,  LPCLASS pstClass );
	// Override constructor ( each method also corresponding a CSimplex )
	CSimplex ( LPMETHOD pMth );
	
	// �ҵ��е��õĺ����ӵ�һ��������
	void	addSimplexMethod ( LPMETHOD pMethod );
	// �ҵ��е��ù�ϵ�ĺ����ӵ�һ��������
	void	addSimplexClass ( LPCLASS pstClass );
	void	outputSimplexToFile ( string fileName, LPSIMPLEX pSimplex );
	~CSimplex ( );

};
#endif
