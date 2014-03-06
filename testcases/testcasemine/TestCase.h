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
#include <string>
#include "define.h"
#ifdef WIN32
#include "stdafx.h"
#include "Shlwapi.h"
#include "ReadH.h"
#include "ReadCpp.H"
#include <vector>
#include <map>
#else 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <dirent.h>
#endif
//#include "ArchitectureDoc.h"

using namespace std;
class CTestCase
{
public:
	CReadCpp *head;
	LPTESTCASE			m_pNext_test;
	LPTESTCASE			m_pIONext_test;
	int							stage;								//0��ʾ��ʼ�׶Σ�1��ʾ����ɣ�2��ʾ������ɣ�3��ʾд���
	string						strTestPath;
	string						lastans;
	vector < string >	arycpp_fileName;
	vector < string >	aryh_fileName;
	map <string, CReadH*> hmap;
public:
	CTestCase ( int index, string strNameTest );
	~CTestCase ( );

	void		setNext ( LPTESTCASE _nextcase );
	LPTESTCASE	getNext();

	void		setIONext ( LPTESTCASE _nextcase );
	LPTESTCASE	getIONext();

	void		doReading ( );

	void		doParsing ( );
	


	void		doModeling ( );
	
	void		doWriting ( );
	int			getStage();
	void		setStage(int s);
	string    findtype(string content,string valuename,int endpos);
	void      findsymbol(string symbol,string methodbody,string classname,CReadCpp *p);
	//void		HypergraphVertex();
	
};

#endif
