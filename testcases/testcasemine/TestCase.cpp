/*
 * Project------ CArchitecture
 * Class Name--- TestCase.cpp
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-4-8
 * Edition------ 1.0

 * Description-- �Զ���ĵ����з���, �õ�simplex��ÿ������ϵ��Ӧһ��CSimplex���� 

 * Change Log:
 *		Date----- 2013-4-18
 *		Content-- �Զ���ĵ����������ڴ��ȡ��Ϊֱ��Cstdio��ȡ����ȡ����Ķ����������ں������������������Ƿ���ָ������

 * Change Log:
 *		Date----- 2013-5-5
 *		Content-- �޸��˺����������ֵ�˼·���õ������䱻���ù�ϵ����ĳ������ĳ��������������Щ���е���Щ�������ù������ֱ����ù�ϵ��Ϊ����ϵ�����ݣ�����Ϊ�������ߵ�����

 * Change Log:
 *		Date----- 2013-5-6
 *		Content-- ��ʼʵ�ֳ�ͼ��ģ���ֱ�����õ����㼰����ϵ�õ�����

 * Change Log:
 *		Date----- 2013-5-13
 *		Content-- ��Mainfrm�е�����ʵ�ַ�װ����CTestCase���У����ڽ��ж��̲߳�����Ҳʹ�ô�����������룬������ֲ
*/
#include "TestCase.h"
#include <iostream>
//#include "Shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestCase::CTestCase ( int index, string strNameTest )
{
	strTestPath = strNameTest;	
	stage			 = INIT_STAGE;
	head			 =	NULL;
	lastans		 = "";
}

CTestCase::~CTestCase ( )
{
	

}

void CTestCase::setNext ( LPTESTCASE _nextcase )
{
	m_pNext_test	= _nextcase;
}

LPTESTCASE CTestCase::getNext ( )
{
	return m_pNext_test;
}

void CTestCase::setIONext ( LPTESTCASE _nextcase )
{
	m_pIONext_test = _nextcase;
}

LPTESTCASE CTestCase::getIONext ( )
{
	return m_pIONext_test;
}

int CTestCase::getStage()
{
	return stage;
}

void CTestCase::setStage(int s)
{
	stage = s;
}

/*
 * doReading: ����ÿ��testcase����ȡ���е�����.cpp��.h�ļ�������m_ary_file������
*/
void CTestCase::doReading ( )
{
	#ifdef WIN32
	WIN32_FIND_DATA		fileData;
	HANDLE				hTempFind;
	string				strFileName, strCpp_ext, strCc_ext, strH_ext; 
	string				path= strTestPath;									// ���·��
	string				pathFile=strTestPath;								// ���������ڲ��ļ����·��
	size_t				iLen;									// ���������ڲ��ļ������ȣ�����ȡ�ú�׺��
	path				+= "//*.*";

	hTempFind	= FindFirstFile (path.c_str(), &fileData );
	while ( hTempFind != INVALID_HANDLE_VALUE ) 
	{ 
		strFileName		= fileData.cFileName;
	
		if ( strFileName != "." && strFileName != ".." )
		{
			iLen			= strFileName.length();
			strCpp_ext		= strFileName.substr ( iLen-3, 3 );
			strCc_ext		= strFileName.substr ( iLen-2, 2 );
			strH_ext		= strFileName.substr ( iLen-1, 1 );
			if ( strCpp_ext == "cpp" || strCc_ext == "cc")   
			{  
				arycpp_fileName.push_back(pathFile+"//"+strFileName);
			} 
			else if ( strH_ext == "h")
			{
				aryh_fileName.push_back(pathFile+"//"+strFileName);
			}
			
		}
		else
		{
			// �ϵ�
		}

		if ( !FindNextFile ( hTempFind,   &fileData ) ) 
		{ 
			hTempFind = INVALID_HANDLE_VALUE; 
		} 
		
	}
	CloseHandle ( hTempFind );
#else
    struct dirent* ent = NULL;
    
    DIR* pDir;

    //cout<<"testcase path:"<<m_Name_test<<endl;
    m_Name_test = m_oString.rTrim(m_Name_test,"\r");
    //char *testname = new char[m_Name_test.size()-1];
    //strcpy(testname,m_Name_test.c_str());
    //testname[m_Name_test.size()-2]='\0';
    // cout<<"tesrname:"<<testname<<endl;
    cout<<"length:"<<m_Name_test.size()<<endl;
    pDir = opendir(m_Name_test.c_str());
    cout<<m_Name_test.c_str()<<endl;
    if(pDir!=NULL)
        cout<<"open success"<<endl;
    else
    {
        cout<<"failed"<<endl;
        system(("mkdir "+m_Name_test).c_str());
    }
    //system(("ls "+m_Name_test).c_str());
    ent = readdir(pDir);
    // cout<<"open success"<<endl;
    while(NULL != (ent = readdir(pDir)))       
    {
       
	    string fullpath = "";
        fullpath += m_Name_test + string("//") + ent->d_name;
    //    cout<<m_Name_test<<endl;
    //    cout<<"FULLPATH:"<<endl;
    //    cout<<ent->d_name<<endl;
    //    cout<<"aaaaaaaaaaa"<<endl;
    //    cout<<fullpath<<endl;

        //if(IsFile(fullpath))
        {
             if(strstr(ent->d_name, "cpp")!=NULL)
             {
                   m_ary_file.push_back(fullpath);
                   cout<<"add:"<<fullpath<<endl;
             }
	         if(strstr(ent->d_name, "h")!=NULL)
             {
                   m_ary_file.push_back(fullpath);
                   cout<<"add:"<<fullpath<<endl;
             }
            // cout<<"full path:"<<fullpath<<endl;
        }
    }
    closedir(pDir);
#endif
    
}

// ��������
void CTestCase::doParsing ( )
{ 
	for ( int i=0; i < aryh_fileName.size(); i++ )
	{
		CReadH *p		= new CReadH (aryh_fileName.at(i));
		hmap.insert(pair <string,CReadH*>(aryh_fileName.at(i), p));
	}

	for ( int i=0; i < arycpp_fileName.size(); i++ )
	{
		CReadCpp *p		= new CReadCpp (arycpp_fileName.at(i));
		p->setnext(head);
		head = p;
	}
	doModeling ( );
}

void CTestCase::findsymbol(string symbol,string methodbody,string classname,CReadCpp *p)
{
	int pos = methodbody.find(symbol);
	if(pos!=string::npos)
	{
		string valuename = "";
		string typeofname ="";
		for(int i=pos-1;methodbody.at(i)!=' '&&methodbody.at(i)!='\t';i--)
		{
			valuename = methodbody.at(i) + valuename;
		}

		int pos2 = methodbody.find(valuename);
					
		typeofname = findtype(methodbody,valuename,pos);

		if(pos2 == string::npos)
		{
			for(int i=0;i<p->headfile.size();i++)
			{
				string headname = p->headfile.at(i);
				map<string,CReadH*>::iterator it;
				map<string,string>::iterator ite;
				it = hmap.find(headname);
				ite = it->second->classdef.find(classname);
				if(ite != it->second->classdef.end())
					string typeofname = findtype(ite->second,valuename,ite->second.length());
			}
		}
		if(typeofname!="")
		{
			map<string,CReadH*>::iterator it;
			for(it = hmap.begin();it!=hmap.end();++it)
			{
				map<string,string>::iterator ite;
				ite = it->second->classdef.find(typeofname);
				if(ite!=it->second->classdef.end())
				{
					lastans += classname+"  called  "+typeofname + "\n";
					break;
				}
			}
		}
	}
}
void CTestCase::doModeling ( )
{
	CReadCpp *p = head;
	while(p!=NULL)
	{
		map<string,CMethodBody*>::iterator iter;
		for(iter=p->cppclass.begin();iter!=p->cppclass.end();++iter)
		{
			string classname  = iter->first;
			CMethodBody *q  = iter->second;
			while(q!=NULL)
			{
				string methodbody = q->body;
				findsymbol("->",methodbody,classname,p);
				findsymbol(".",methodbody,classname,p);
				q=q->next;
			}


		}
		p=p->getnext();
	}
	cout<<lastans<<endl;

	
}

string CTestCase::findtype(string content,string valuename,int endpos)
{
	string typeofname="";
	int pos2 = content.find(valuename);
	while(pos2!=string::npos)
	{
		char c = content.at(valuename.length()+pos2);
		if((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57))
		{
			pos2 = content.find(valuename,valuename.length()+pos2);
			continue;
		}
		c = content.at(pos2-1);
		if((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57))
		{
			pos2 = content.find(valuename,valuename.length()+pos2);
			continue;
		}

		if(pos2>=endpos)
			break;
		int k = pos2-1;
		c = content.at(k);
		while(c=='*'||c==' '||c='\t')
		{
			k--;
			c = content.at(k);
		}
		while((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57))
		{
			typeofname = content.at(k) + typeofname;
			k--;
			c = content.at(k);
		}

		break;
	}
	return typeofname;
}

void CTestCase::doWriting ( )
{
	
}
