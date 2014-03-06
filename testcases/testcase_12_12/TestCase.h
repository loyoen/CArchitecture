/*
 * Project------ CArchitecture
 * Class Name--- TestCase.h
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-5-8
 * Edition------ 1.0

 * Description-- 每一个testcase对应一个TestCase类，在该类中可以进行多种操作，如parser，超图建模。
 * 原本在Doc和Mainfrm中实现，现在全部封装在TestCase类中。
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
	typedef map < string, LPMETHOD >::const_iterator m_CIT;	// 定义迭代器便于查找map内容
	Cstringnew			m_oString;
	// Do Parsing 部分
	int					m_Index_test;
	string				m_Name_test;	
	LPTESTCASE			m_pNext_test;
	LPTESTCASE			m_pIONext_test;
	int					stage;								//0表示初始阶段，1表示读完成，2表示处理完成，3表示写完成

	vector <string> m_ary_file;								// 用来存储每个testcase文件中找到的符合条件的文件名
	vector < CTestFile* > m_pVectorFile;					// 用来存储每个testcase中的所有文件，即一个testcase对应一个m_pVectorFile
	LPTESTFILE			m_pFile;
	LPTESTFILE			m_pFileHead;

	// findClass 所用的成员变量
	int					m_cIndex;
	// findMethod 所用的成员变量
	int					m_mIndex;
	LPMETHOD			m_mpHead;							
	// 用于链接所有类
	LPCLASS				m_pHeadCl;
	LPCLASS				m_pstClass;
	int					m_nIndexCls;
	// 用于链接所有已找出的函数
	LPMETHOD			m_pHeadMth;
	LPMETHOD			m_pstMethod;
	// 用于链接所有函数调用关系
	LPINVOKE			m_pInvoke;
	LPINVOKE			m_pIvkHead;
	// 用于链接所有类对应的CSimplex对象
	int					m_simIndex;
	LPSIMPLEX			m_psimHead;
	LPSIMPLEX			m_pSimplex;
	// 用于链接所有函数对应的CSimplex对象
	LPSIMPLEX			m_pSimMethod;
	LPSIMPLEX			m_pSimMthHead;
	// 用于链接所有类间调用关系
	LPRELATION			m_pReHead;
	LPRELATION			m_pRelated;

	// Do Modeling 部分
public:
	// 用于超图建模的成员变量
	// 顶点部分
	LPVERTEX			m_pVerHead;
	LPVERTEX			m_pVertex;
	int					m_vIndex;
	int					m_vTotal;
	// 超边部分
	LPEDGE				m_pEHead;
	LPEDGE				m_pEdge;
	int 				m_eIndex;
	int					m_eTotal;
	// 建立超边时所需要的新增结构体
	LPSTEDGE			m_pstEHead;
	LPSTEDGE			m_pstEdge;
	// 形成超图部分
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
	// 完成parser需要的那些函数
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
