/*
 * Project------ CArchitecture
 * Class Name--- TestCase.h
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-5-8
 * Edition------ 1.0

 * Description-- ÿһ��testcase��Ӧһ��TestCase�࣬�ڸ����п��Խ��ж��ֲ�������parser����ͼ��ģ��
 * ԭ����Doc��Mainfrm��ʵ�֣�����ȫ����װ��TestCase���С�
*/
#ifndef	TESTCASE_H
#define	TESTCASE_H

#define INIT_STAGE			0
#define READ_END_STAGE		1	
#define MODEL_END_STAGE		2
#define WRITE_END_STAGE		3

#include "TestFile.h"
#include "Hypergraph.h"
#include "define.h"
#ifdef WIN32
#include "stdafx.h"
#include "Shlwapi.h"
#else 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <dirent.h>
#endif
//#include "ArchitectureDoc.h"

class CTestCase
{
public:
	typedef map < string, LPMETHOD >::const_iterator m_CIT;	// ������������ڲ���map����
	Cstringnew			m_oString;
	// Do Parsing ����
	int					m_Index_test;
	string				m_Name_test;	
	LPTESTCASE			m_pNext_test;
	LPTESTCASE			m_pIONext_test;
	int					stage;								//0��ʾ��ʼ�׶Σ�1��ʾ����ɣ�2��ʾ������ɣ�3��ʾд���

	vector <string> m_ary_file;								// �����洢ÿ��testcase�ļ����ҵ��ķ����������ļ���
	vector < CTestFile* > m_pVectorFile;					// �����洢ÿ��testcase�е������ļ�����һ��testcase��Ӧһ��m_pVectorFile
	LPTESTFILE			m_pFile;
	LPTESTFILE			m_pFileHead;

	// findClass ���õĳ�Ա����
	int					m_cIndex;
	// findMethod ���õĳ�Ա����
	int					m_mIndex;
	LPMETHOD			m_mpHead;							
	// ��������������
	LPCLASS				m_pHeadCl;
	LPCLASS				m_pstClass;
	int					m_nIndexCls;
	// ���������������ҳ��ĺ���
	LPMETHOD			m_pHeadMth;
	LPMETHOD			m_pstMethod;
	// �����������к������ù�ϵ
	LPINVOKE			m_pInvoke;
	LPINVOKE			m_pIvkHead;
	// ���������������Ӧ��CSimplex����
	int					m_simIndex;
	LPSIMPLEX			m_psimHead;
	LPSIMPLEX			m_pSimplex;
	// �����������к�����Ӧ��CSimplex����
	LPSIMPLEX			m_pSimMethod;
	LPSIMPLEX			m_pSimMthHead;
	// �����������������ù�ϵ
	LPRELATION			m_pReHead;
	LPRELATION			m_pRelated;

	// Do Modeling ����
public:
	// ���ڳ�ͼ��ģ�ĳ�Ա����
	// ���㲿��
	LPVERTEX			m_pVerHead;
	LPVERTEX			m_pVertex;
	int					m_vIndex;
	int					m_vTotal;
	// ���߲���
	LPEDGE				m_pEHead;
	LPEDGE				m_pEdge;
	int 				m_eIndex;
	int					m_eTotal;
	// ��������ʱ����Ҫ�������ṹ��
	LPSTEDGE			m_pstEHead;
	LPSTEDGE			m_pstEdge;
	// �γɳ�ͼ����
	LPHYPERGRAPH		m_pGraphHead;
	LPHYPERGRAPH		m_pHypergraph;
	int					m_grIndex;


public:
	CTestCase ( int index, string strNameTest );
	~CTestCase ( );

	void		setNext ( LPTESTCASE _nextcase );
	LPTESTCASE	getNext();

	void		setIONext ( LPTESTCASE _nextcase );
	LPTESTCASE	getIONext();

	void		doReading ( );

	void		doParsing ( );
	// ���parser��Ҫ����Щ����
	void		parserClasses ( );
	void		findObject ( LPCLASS pClass );
	void		parserMethods ( );
	LPCLASS		findRelationClass ( LPSIMPLEX pSim );
	void		parserClassInvoke ( );


	void		doModeling ( );
	void		hypergraphVertex ( );
	void		hypergraphEdge ( );
	void		hypergraphGraph ( );

	void		doWriting ( );
	int			getStage();
	void		setStage(int s);
	//void		HypergraphVertex();
	
};

#endif
