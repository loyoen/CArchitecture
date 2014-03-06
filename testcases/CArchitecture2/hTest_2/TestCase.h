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

#define END_NUM					2
#define INIT_STAGE				0
#define READ_END_STAGE		1	
#define MODEL_END_STAGE		2
#define WRITE_END_STAGE		3
#include <string>
#include "define.h"
#include "CHypergraph.h"
#include "Multilevel.h"
#include "ReadH.h"
#include "ReadCpp.H"
#include <vector>
#include <map>
#include <queue>

#ifdef WIN32
#include "Shlwapi.h"
#include <direct.h>
#include <io.h>
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
class calledclass
{
public:
	string name;
	int count;
	bool bIsmemberVar;   //�ж��Ƿ��ǳ�Ա����    
	calledclass *next;
	calledclass();
};



class CTestCase
{
public:
	int							stage;								//0��ʾ��ʼ�׶Σ�1��ʾ����ɣ�2��ʾ������ɣ�3��ʾд���
	LPTESTCASE			m_pNext_test;
	LPTESTCASE			m_pIONext_test;
	CTestCase ();
	virtual ~CTestCase ( );

	void		setNext ( LPTESTCASE _nextcase );
	LPTESTCASE	getNext();

	void		setIONext ( LPTESTCASE _nextcase );
	LPTESTCASE	getIONext();

	virtual void		doReading ( );

	virtual void		doParsing ( );
	


	virtual void		doModeling ( );
	
	virtual void		doWriting ( );
	int			getStage();
	void		setStage(int s);
};

class CTestCaseCpp:public CTestCase
{
public:
	CReadCpp *head;
	string						strTestPath;
	string						strPara;
	string						testcasename;
	string						lastans;
	CHypergraph           *pHyper;
	int							cutnum;
	int							allTime;
	DWORD		runtime;
	string  writeTime;
	map<string,calledclass*> calledrelation;
	map<string,string> mapForTypeDef;
	vector < string >	arycpp_fileName;
	vector < string >	aryh_fileName;
	map <string, CReadH*> hmap;
	map<string,string> fathermap;
public:
	CTestCaseCpp ( int index, string strNameTest );
	~CTestCaseCpp ( );


	void		doReading ( );

	void		doParsing ( );
	


	void		doModeling ( );
	
	void		doWriting ( );

	string    findtype(string content,string valuename,int endpos);
	void      findsymbol(string symbol,string methodbody,string classname,CReadCpp *p);
	void      readEachfile();
	void		createHypergraph();
	void		doHmetis();
	void		createSubGraph(CHypergraph *G,CHypergraph *subG1,CHypergraph *subG2);
	void		dealwithTypeDef(string content);
	void		dfsFolder(string path);
	vector<string> split(string str,string pattern);
	int        dfsForWriteParts(CHypergraph *G,int parts);

};


#endif
