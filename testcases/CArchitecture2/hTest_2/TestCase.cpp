/*
 * Project------ CArchitecture
 * Class Name--- TestCase.cpp
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-4-8
 * Edition------ 1.0

 * Description-- 对多个文档进行分析, 得到simplex，每个类间关系对应一个CSimplex对象 

 * Change Log:
 *		Date----- 2013-4-18
 *		Content-- 对多个文档分析，由内存读取改为直接Cstdio读取。并取得类的对象名，用于后续查找其他函数中是否出现该类对象

 * Change Log:
 *		Date----- 2013-5-5
 *		Content-- 修改了函数解析部分的思路，得到函数间被调用关系，即某个类中某个函数被其他哪些类中的哪些函数调用过。这种被调用关系作为类间关系的依据，并作为建立超边的依据

 * Change Log:
 *		Date----- 2013-5-6
 *		Content-- 开始实现超图建模，分别由类得到顶点及类间关系得到超边

 * Change Log:
 *		Date----- 2013-5-13
 *		Content-- 将Mainfrm中的所有实现封装在了CTestCase类中，便于进行多线程操作，也使得代码与界面脱离，便于移植
*/
#include "TestCase.h"
#include <iostream>
#include "CLog.h"
//#include "Shlwapi.h"



calledclass::calledclass()
{
	next = NULL;
	count = 1;
	bIsmemberVar = false;
}

CTestCase::CTestCase ()
{
	
}

void CTestCase::doModeling()
{
}

void CTestCase::doParsing()
{
}

void CTestCase::doReading()
{

}

void CTestCase::doWriting()
{
}

CTestCaseCpp::CTestCaseCpp ( int index, string strNameTest )
{
	runtime = ::GetTickCount();
	writeTime = "";
	stage			 = INIT_STAGE;
	head			 =	NULL;
	lastans		 = "";
	cutnum       = 0;
	allTime		 = 0;
	strPara  = strNameTest;
	testcasename = "";
	strTestPath = strNameTest.substr(0,strNameTest.find(" "));
	for(int i=int(strTestPath.length())-1;i>=0&&strTestPath.at(i)!='/';i--)
	{
		testcasename = strTestPath.at(i) + testcasename;
	}
	
	cout<<"TestCase: "<<testcasename<<"  start...."<<endl;


	CLogNote(string("now class name: "+strNameTest).c_str());
}

CTestCase::~CTestCase ( )
{

}

CTestCaseCpp::~CTestCaseCpp ( )
{
	CReadCpp *p = head;
	CReadCpp *q;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		delete q;
	}
	map <string, CReadH*>::iterator it;
	for(it = hmap.begin();it!=hmap.end();++it)
	{
		CReadH *m = it->second;
		delete m;
	}

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

//字符串分割函数
vector<string> CTestCaseCpp::split(string line,string pattern)
{
	string str = line+",";
    std::vector<std::string> result;
	int position = -1;

	if(line.find("{")!=string::npos||line.find("<")!=string::npos||line.find("/")!=string::npos||line.find("(")!=string::npos||line.find("}")!=string::npos)
		return result;

	for(int i=0;i<int(str.length());i++)
	{
		for(int j=0;j<int(pattern.length());j++)
		{
			if(str.at(i)==pattern.at(j))
			{
				string ans = str.substr(position+1,i-1-position);
				if(ans!="")
				{
					result.push_back(ans);
				}
				position = i;
				break;
			}
		}
	}
   
    return result;
}
/*
 * doReading: 遍历每个testcase，获取其中的所有.cpp和.h文件，存于m_ary_file数组中
*/

void CTestCaseCpp::dfsFolder(string path)  //递归深度优先遍历整个testcase文件夹，找出所有.cpp,.cc和.h文件
{
	struct _finddata_t fileinfo;
	int hFile = 0;
	string strFind = path+"//*.*";
	hFile	= int(_findfirst (strFind.c_str(), &fileinfo ));
	if(hFile!=-1L)
	{
		do{
			 //判断是否有子目录
			if (fileinfo.attrib & _A_SUBDIR)    
			{
				//这个语句很重要
				if( (strcmp(fileinfo.name,".") != 0 ) &&(strcmp(fileinfo.name,"..") != 0))   
				{
					string newPath = path + "//" + fileinfo.name;
					dfsFolder(newPath);
				}
			}
			else  
			{
				string				strFileName, strCpp_ext, strCc_ext, strH_ext; 
				strFileName = fileinfo.name;
				int iLen			= int(strFileName.length());
				if(iLen>=4)
					strCpp_ext		= strFileName.substr ( iLen-4, 4 );
				else
					strCpp_ext     = "";
				if(iLen>=3)
					strCc_ext		= strFileName.substr ( iLen-3, 3 );
				else
					strCc_ext = "";
				if(iLen>=2)
					strH_ext		= strFileName.substr ( iLen-2, 2 );
				else
					strH_ext     = "";
				if ( strCpp_ext == ".cpp" || strCc_ext == ".cc")   
				{  
					arycpp_fileName.push_back(path+"//"+strFileName);
				} 
				else if ( strH_ext == ".h")
				{
					aryh_fileName.push_back(path+"//"+strFileName);
				}
			}
		}while (_findnext(hFile, &fileinfo) == 0);

		
	}
	_findclose( hFile );
}

void CTestCaseCpp::doReading ( )
{

	cout<<"TestCase: "<<testcasename<<"  start reading...."<<endl;
	runtime = ::GetTickCount();
	dfsFolder(strTestPath);

	int now = runtime;
	runtime = ::GetTickCount();
	now = runtime - now;
	char gettime[100];
	sprintf_s(gettime,"%d",now);
	writeTime += "read path time : " + string(gettime)+"ms\n";
	allTime += now;

#ifdef WIN32

	
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
	readEachfile();
    
}

void CTestCaseCpp::readEachfile()
{
	runtime = ::GetTickCount();
	for ( int i=0; i < int(aryh_fileName.size()); i++ )
	{
		CReadH *p		= new CReadH (aryh_fileName.at(i));
		
		int k;
		for(k=int(aryh_fileName.at(i).length())-1;aryh_fileName.at(i).at(k)!='/';k--);
		string headname = aryh_fileName.at(i).substr(k+1,aryh_fileName.at(i).length()-1-k);   //只取文件名，不要路径
		hmap.insert(pair <string,CReadH*>(headname, p));
	}

	for ( int i=0; i < int(arycpp_fileName.size()); i++ )
	{
		CReadCpp *p		= new CReadCpp (arycpp_fileName.at(i));
		p->setnext(head);
		head = p;
	}

	cout<<"TestCase: "<<testcasename<<"  end reading...."<<endl;

	int now = runtime;
	runtime = ::GetTickCount();
	now = runtime - now;
	char gettime[100];
	sprintf_s(gettime,"%d",now);
	writeTime += "readfile time : " + string(gettime)+"ms\n";
	allTime += now;
}

// 解析部分

void CTestCaseCpp::dealwithTypeDef(string content)
{
	int pos1 = int(content.find("typedef"));
	int pos2 = int(content.find(";",pos1));
	while(pos1!=string::npos&&pos2!=string::npos)
	{
		string line=content.substr(pos1,pos2-pos1);
		vector<string> words = split(line," \t,\n*");
		string name1="",name2="";
		if(words.size()>=3)
		{
			if(words.at(1)=="class")
			{
				name1=words.at(2);
				for(int k=3;k<int(words.size());k++)
				{
					mapForTypeDef.insert(pair<string,string>(words.at(k),name1));
				}
			}
			else
			{
				name1=words.at(1);
				for(int k=2;k<int(words.size());k++)
				{
					mapForTypeDef.insert(pair<string,string>(words.at(k),name1));
				}
			}
		}
		
		pos1 = int(content.find("typedef",pos1+int(strlen("typedef"))));
		pos2 = int(content.find(";",pos1));
	}
}

void CTestCaseCpp::doParsing ( )
{ 
	cout<<"TestCase: "<<testcasename<<"  start parsing...."<<endl;

	runtime = ::GetTickCount();
	
	//结果存在mapForTypeDef里
	map<string, CReadH*>::iterator iterForTypeDef;
	for(iterForTypeDef = hmap.begin();iterForTypeDef!=hmap.end();++iterForTypeDef)
	{
		dealwithTypeDef(iterForTypeDef->second->globalStr);
	}
	CReadCpp *p = head;
	while(p!=NULL)
	{
		dealwithTypeDef(p->globalStr);
		p=p->getnext();
	}

	p = head;
	while(p!=NULL)
	{
		CLogNote(string("cppname::"+p->CppName).c_str());
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
	//cout<<lastans<<endl;


	map <string, CReadH*>::iterator fatherclassmap;
	for(fatherclassmap = hmap.begin();fatherclassmap!=hmap.end();++fatherclassmap)
	{
		map <string,CClassContent*>::iterator it;
		for(it=fatherclassmap->second->classdef.begin();it!=fatherclassmap->second->classdef.end();++it)
		{
			string sonclass = it->first;
			string fatherclass = it->second->fatherclass;
			if(fatherclass!="")
				fathermap.insert(pair<string,string>(sonclass,fatherclass));
		}
	}

	int now = runtime;
	runtime = ::GetTickCount();
	now = runtime - now;
	char gettime[100];
	sprintf_s(gettime,"%d",now);
	writeTime += "parsing time : " + string(gettime)+"ms\n";
	allTime += now;

	cout<<"TestCase: "<<testcasename<<"  end parsing...."<<endl;

	doModeling();
}

void CTestCaseCpp::findsymbol(string symbol,string methodbody,string classname,CReadCpp *p)
{
	int pos = int(methodbody.find(symbol));
	while(pos!=string::npos)
	{
		string valuename = "";
		string typeofname ="";
		int declarationPos = -1; // 声明的位置，1表示在当前函数体内，2表示在.h类的定义里，3表示在全局变量里
		for(int i=pos-1;(methodbody.at(i)>=65&&methodbody.at(i)<=90)||(methodbody.at(i)>=97&&methodbody.at(i)<=122)||(methodbody.at(i)>=48&&methodbody.at(i)<=57)||(methodbody.at(i)=='_');i--)
		{
			valuename = methodbody.at(i) + valuename;
		}

		int pos2 = int(methodbody.find(valuename));
		if(valuename != "")
		{
			typeofname = findtype(methodbody,valuename,int(pos));   // 在当前的方法体中寻找变量的声明

			if(typeofname=="")                                                 //在.h的类的定义里寻找变量声明
			{
				for(int i=0;i<int(p->headfile.size());i++)
				{
					string headname = p->headfile.at(i);
					map<string,CReadH*>::iterator it;
					map<string,CClassContent*>::iterator ite;
					if(headname.find("/")!=string::npos)
					{
						int k;
						for(k=int(headname.length())-1;headname.at(k)!='/';k--);
						headname = headname.substr(k+1,headname.length()-1-k);
					}
					
					it = hmap.find(headname);
					if(it!=hmap.end())
					{
						ite = it->second->classdef.find(classname);
					
						if(ite != it->second->classdef.end())
						{
							typeofname = findtype(ite->second->defbody,valuename,int(ite->second->defbody.length()));
							if(typeofname!="")
								declarationPos = 2;
							break;
						}
					}
				}
			}

			if(typeofname=="")                                           //在包含的.h文件和当前文件的全局变量里寻找
			{
				typeofname = findtype(p->globalStr,valuename,int(p->globalStr.length()));
				if(typeofname=="")
				{
					map <string,bool> donemap;
					queue <string> allheadfile;

					for(int i=0;i<int(p->headfile.size());i++)
					{
						string headname = p->headfile.at(i);
						if(headname.find("/")!=string::npos)
						{
							int k;
							for(k=int(headname.length())-1;headname.at(k)!='/';k--);
							headname = headname.substr(k+1,headname.length()-1-k);
						}
						map <string,bool>::iterator iterfordone;
						iterfordone = donemap.find(headname);
						if(iterfordone==donemap.end())
						{
							donemap.insert(pair<string,bool>(headname,true));
							allheadfile.push(headname);
						}
					}
					while(!allheadfile.empty())
					{
						string oneheadfile = allheadfile.front();
						allheadfile.pop();
						map<string,CReadH*>::iterator iterforH;
						iterforH = hmap.find(oneheadfile);
						if(iterforH!=hmap.end())
						{
							typeofname = findtype(iterforH->second->globalStr,valuename,int(iterforH->second->globalStr.length()));
							if(typeofname!="")
								break;
							else
							{
								for(int count=0;count<int(iterforH->second->headfile.size());count++)
								{
									string oneheadname = iterforH->second->headfile.at(count);
									if(oneheadname.find("/")!=string::npos)
									{
										int k;
										for(k=int(oneheadname.length())-1;oneheadname.at(k)!='/';k--);
										oneheadname = oneheadname.substr(k+1,oneheadname.length()-1-k);
									}
									map <string,bool>::iterator iterfordone;
									iterfordone = donemap.find(oneheadname);
									if(iterfordone==donemap.end())
									{
										donemap.insert(pair<string,bool>(oneheadname,true));
										allheadfile.push(oneheadname);
									}
								}
							}
						}
					}

				}
			}

			if(typeofname!="")
			{
				map<string,string>::iterator iterfordef;
				iterfordef = mapForTypeDef.find(typeofname);
				if(iterfordef!=mapForTypeDef.end())
				{
					typeofname = iterfordef->second;
				}

				map<string,CReadH*>::iterator it;
				for(it = hmap.begin();it!=hmap.end();++it)
				{
					map<string,CClassContent*>::iterator ite;
					ite = it->second->classdef.find(typeofname);
					if(ite!=it->second->classdef.end())
					{
						lastans += classname+"  called  "+typeofname + "\n";


						if(classname != typeofname)
						{
							calledclass *newrelation = new calledclass();
							newrelation->name = classname;
							newrelation->next = NULL;
							if(declarationPos==2)   //是类成员变量
							{
								newrelation->bIsmemberVar = true;
							}
							map<string,calledclass*>::iterator itera;
							itera = calledrelation.find(typeofname);
							if(itera != calledrelation.end())
							{
								calledclass *temp = itera->second;
								calledclass *last;
								bool belong = false;
								while(temp!=NULL)
								{
									if(temp->name==classname)
									{
										temp->count++;
										belong = true;
										break;
									}
									last  = temp;
									temp=temp->next;
								}
								if(!belong)
									last->next = newrelation;	
							}
							else
							{
								calledrelation.insert(pair<string,calledclass*>(typeofname,newrelation));
							}
							break;
						}
					}
				}
			}
		}
		pos = int(methodbody.find(symbol,pos+symbol.length()));
	}
}
string CTestCaseCpp::findtype(string content,string valuename,int endpos)  //找变量类型
{
	char num[100];
	sprintf_s(num, "%d", endpos);
	if(valuename =="AllocationSiteInfo")
	{
		int tem = -1;
	}

	CLogNote(string("Find Type---valuename:"+valuename+"---endpos:"+string(num)).c_str());
	string typeofname="";
	int pos2 = int(content.find(valuename));
	while(pos2!=string::npos)
	{
		if(valuename.length()+pos2>content.length()-1)
			return "";
		char c = content.at(valuename.length()+pos2);
		if((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57)||(c=='_'))
		{
			pos2 = int(content.find(valuename,valuename.length()+pos2));
			continue;
		}
		if(pos2-1<0)
			return "";
		c = content.at(pos2-1);
		if((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57)||(c=='_'))
		{
			pos2 = int(content.find(valuename,valuename.length()+pos2));
			continue;
		}

		if(pos2>=int(endpos))
			break;
		int k = pos2-1;
		c = content.at(k);
		while(c=='*'||c==' '||c=='\t')
		{
			k--;
			c = content.at(k);
		}
		while((c>=65&&c<=90)||(c>=97&&c<=122)||(c>=48&&c<=57)||(c=='_'))
		{
			typeofname = content.at(k) + typeofname;
			k--;
			if(k<0)
				return "";
			c = content.at(k);
		}

		break;
	}
	return typeofname;
}

void CTestCaseCpp::doModeling ( )
{
	cout<<"TestCase: "<<testcasename<<"  start modeling...."<<endl;
	runtime = ::GetTickCount();

	createHypergraph();

	//int *part = new int[pHyper->nvtxs];
	
	cout<<"TestCase: "<<testcasename<<"  end modeling...."<<endl;

	cout<<"TestCase: "<<testcasename<<"  start cuting...."<<endl;

	

	doHmetis();
	
	

	cout<<"TestCase: "<<testcasename<<"  end cuting...."<<endl;

	int now = runtime;
	runtime = ::GetTickCount();
	now = runtime - now;
	char gettime[100];
	sprintf_s(gettime,"%d",now);
	writeTime += "modeling and cuting time : " + string(gettime)+"ms\n";
	allTime += now;

	

}

void CTestCaseCpp::doHmetis()
{
	int *hcut = &cutnum;
	CMultilevel *pSolve = new CMultilevel();
	queue <CHypergraph*> subGraph;
	pHyper->floor = 1;
	pHyper->coupling =0;
	pHyper->cohesion =1;
	int nowfloor =1;
	float nowcoupling = 0;
	int couplingnum=0;
	float nowcohesion = 0;
	int cohesionnum = 0;
	pHyper->trueNvtxs = pHyper->nvtxs;
	pHyper->Modu = 0.0;
	subGraph.push(pHyper);
	while(!subGraph.empty())
	{
		CHypergraph *p=subGraph.front();
		
		if(p->nvtxs>END_NUM)
		{
			p->Modu = 0.0;
			pSolve->myPartition(p,hcut);
			
			if(p->is_parted)
			{
				CHypergraph *subG1,*subG2;
				subG1 = new CHypergraph();
				subG2 = new CHypergraph();
				createSubGraph(p,subG1,subG2);
			
				p->leftSon = subG1;
				p->rightSon = subG2;
				if(subG1->nvtxs!=0&&subG2->nvtxs!=0)
				{
					subGraph.push(subG1);
					subGraph.push(subG2);
				}
			}
			
			/*
			HMETIS_PartRecursive(p->nvtxs, p->nhedges, p->vwgts, \
				p->eptr, p->eind, p->hewgts, p->npart, p->ubfactor, \
				p->inOptions, p->part, hcut);
			*/
			
			/* 先做二分，多层分割，后面再加上
			
			CHypergraph *subG1,*subG2;
			subG1 = new CHypergraph();
			subG2 = new CHypergraph();
			createSubGraph(p,subG1,subG2);
			
			p->leftSon = subG1;
			p->rightSon = subG2;
			if(subG1->nvtxs!=0&&subG2->nvtxs!=0)
			{
				subGraph.push(subG1);
				subGraph.push(subG2);
			}

			*/

			
		}

		subGraph.pop();
	}

	if(nowfloor!=1)
	{
		cout<<"floor: "<<nowfloor<<endl;
		cout<<"   coupling:"<<nowcoupling/couplingnum<<endl;
		cout<<"   cohesion:"<<nowcohesion/cohesionnum<<endl;

	}
	else
	{
		cout<<"floor: "<<nowfloor<<endl;
		cout<<"   coupling:"<<"0"<<endl;
		cout<<"   cohesion:"<<"1"<<endl;
	}


}

void CTestCaseCpp::createSubGraph(CHypergraph *G,CHypergraph *subG1,CHypergraph *subG2)
{
	subG1->fatherGraph = G;
	subG1->npart		 = 2;
	subG1->hewgts   = new int[G->nhedges];
	subG1->eptr		 = new int[G->nhedges+1];
	subG1->eind		 = new int[G->eptr[G->nhedges]];
	subG1->part        = new int[G->nvtxs];
	subG1->vwgts      = new int[G->nvtxs];
	subG1->inOptions = new int[9];
	subG1->ubfactor   = G->ubfactor;
	subG1->eptr[0] = 0;
	for(int i=0;i<9;i++)
	{
		subG1->inOptions[i] = G->inOptions[i];
	}

	subG2->fatherGraph = G;
	subG2->npart		 = 2;
	subG2->hewgts   = new int[G->nhedges];
	subG2->eptr		 = new int[G->nhedges+1];
	subG2->eind		 = new int[G->eptr[G->nhedges]];
	subG2->part        = new int[G->nvtxs];
	subG2->vwgts      = new int[G->nvtxs];
	subG2->inOptions = new int[9];
	subG2->ubfactor   = G->ubfactor;
	subG2->eptr[0] = 0;
	for(int i=0;i<9;i++)
	{
		subG2->inOptions[i] = G->inOptions[i];
	}

	int G1num=0,G2num=0;
	int eindnum_G1=0,eindnum_G2=0;
	int edgenumG1=0,edgenumG2=0;

	
	
	//按照超边处理

	//重新构建新的子超图

	int wightG1=0,wightG2=0,wightG1_G2=0;
	for(int i=0;i<G->nhedges;i++)
	{
		int startG1=-1,startG2=-1,endG1=-1,endG2=-1;
		bool allzero=true,allone=true;
		
		for(int j=G->eptr[i];j<G->eptr[i+1];j++)
		{
			
			if(G->part[G->eind[j]]==0)
			{
				map<int,int>::iterator iter;
				iter = G->mapForG1.find(G->eind[j]);
				if(iter!=G->mapForG1.end())
				{	
					subG1->eind[eindnum_G1] = iter->second;
					startG1 = startG1==-1?eindnum_G1:startG1;
					endG1 = eindnum_G1;
					eindnum_G1 ++;
				}
				else
				{
					G->mapForG1.insert(pair<int,int>(G->eind[j],G1num));
					subG1->mapForFather.insert(pair<int,int>(G1num,G->eind[j]));
					subG1->vwgts[G1num] = G->vwgts[G->eind[j]]; 
					subG1->eind[eindnum_G1] = G1num;
					startG1 = startG1==-1?eindnum_G1:startG1;
					endG1 = eindnum_G1;
					G1num++;
					eindnum_G1 ++;
					
				}
				allone = false;
			}
			else if(G->part[G->eind[j]]==1)
			{

				map<int,int>::iterator iter;
				iter = G->mapForG2.find(G->eind[j]);
				if(iter!=G->mapForG2.end())
				{	
					subG2->eind[eindnum_G2] = iter->second;
					startG2 = startG2==-1?eindnum_G2:startG2;
					endG2 = eindnum_G2;
					eindnum_G2 ++;
					
				}
				else
				{
					G->mapForG2.insert(pair<int,int>(G->eind[j],G2num));
					subG2->mapForFather.insert(pair<int,int>(G2num,G->eind[j]));
					subG2->eind[eindnum_G2] = G2num;
					subG2->vwgts[G2num] = G->vwgts[G->eind[j]]; 
					startG2 = startG2==-1?eindnum_G2:startG2;
					endG2 = eindnum_G2;
					G2num++;
					eindnum_G2 ++;
					
				}
				allzero = false;

			}
			else
				cout<<"cut error"<<endl;
		} //END FOR

		
		if(allzero)
		{
			edgenumG1++;
			subG1->eptr[edgenumG1] = endG1+1; 
			subG1->hewgts[edgenumG1-1] = G->hewgts[i];
			wightG1 += G->hewgts[i];
		}
		else if(allone)
		{
			edgenumG2++;
			subG2->eptr[edgenumG2] = endG2+1; 
			subG2->hewgts[edgenumG2-1] = G->hewgts[i];
			wightG2 += G->hewgts[i];
		}
		else
		{
			edgenumG1++;
			subG1->eptr[edgenumG1] = endG1+1; 
			subG1->hewgts[edgenumG1-1] = 0;
			edgenumG2++;
			subG2->eptr[edgenumG2] = endG2+1;
			subG2->hewgts[edgenumG2-1] = 0;
			wightG1_G2 += G->hewgts[i];
		}

	}
	if(wightG1+wightG2+wightG1_G2 ==0 )
	{
		subG1->coupling = 0;
		subG2->coupling = 0;
	}
	else
	{
		subG1->coupling = float(wightG1_G2)/float(wightG1+wightG2+wightG1_G2);
		subG2->coupling = float(wightG1_G2)/float(wightG1+wightG2+wightG1_G2);
	}
	if(wightG1==0)
	{
		subG1->cohesion = 0;
	}
	else
		subG1->cohesion = float(wightG1)/float(wightG1+wightG1_G2);
	if(wightG2==0)
		subG2->cohesion = 0;
	else
		subG2->cohesion = float(wightG2)/float(wightG2+wightG1_G2);
	subG1->nhedges = edgenumG1;
	subG2->nhedges = edgenumG2;
	subG1->nvtxs = G1num;
	subG2->nvtxs = G2num;
	

	//在原图基础上构建子超图

	/*
	int wightG1=0,wightG2=0,wightG1_G2=0;
	for(int i=0;i<G->nhedges;i++)
	{
		int startG1=-1,startG2=-1,endG1=-1,endG2=-1;
		bool allzero=true,allone=true;
		
		for(int j=G->eptr[i];j<G->eptr[i+1];j++)
		{
			
			if(G->part[G->eind[j]]==0)
			{
				subG1->eind[eindnum_G1] = G->eind[j];
				startG1 = startG1==-1?eindnum_G1:startG1;
				endG1 = eindnum_G1;
				eindnum_G1 ++;
				subG1->vwgts[G->eind[j]] = G->vwgts[G->eind[j]]; 
				subG2->vwgts[G->eind[j]] = 0; 
				
				allone = false;
			}
			else if(G->part[G->eind[j]]==1)
			{
				subG2->eind[eindnum_G2] = G->eind[j];
				startG2 = startG2==-1?eindnum_G2:startG2;
				endG2 = eindnum_G2;
				eindnum_G2 ++;
				subG1->vwgts[G->eind[j]] = 0; 
				subG2->vwgts[G->eind[j]] = G->vwgts[G->eind[j]]; 
				
				allzero = false;

			}
			else
				cout<<"cut error"<<endl;
		} //END FOR

		
		if(allzero)
		{
			edgenumG1++;
			subG1->eptr[edgenumG1] = endG1+1; 
			subG1->hewgts[edgenumG1-1] = G->hewgts[i];
			wightG1 += G->hewgts[i];
		}
		else if(allone)
		{
			edgenumG2++;
			subG2->eptr[edgenumG2] = endG2+1; 
			subG2->hewgts[edgenumG2-1] = G->hewgts[i];
			wightG2 += G->hewgts[i];
		}
		else
		{
			edgenumG1++;
			subG1->eptr[edgenumG1] = endG1+1; 
			subG1->hewgts[edgenumG1-1] = 0;
			edgenumG2++;
			subG2->eptr[edgenumG2] = endG2+1;
			subG2->hewgts[edgenumG2-1] = 0;
			wightG1_G2 += G->hewgts[i];
		}

	}
	
	subG1->nhedges = edgenumG1;
	subG2->nhedges = edgenumG2;
	subG1->nvtxs = G->nvtxs;
	subG2->nvtxs = G->nvtxs;

	for(int i=0;i<G->nvtxs;i++)
	{
		if(G->part[i]==0)
		{
			subG1->vwgts[i] = G->vwgts[i]; 
			subG2->vwgts[i] = 0; 
			if(subG1->vwgts[i]!=0)
				G1num++;
		}
		else if(G->part[i]==1)
		{
			subG1->vwgts[i] = 0; 
			subG2->vwgts[i] = G->vwgts[i];
			if(subG2->vwgts[i]!=0)
				G2num++;
		}
		else
			cout<<"error"<<endl;
	}
	subG1->trueNvtxs = G1num;
	subG2->trueNvtxs = G2num;
	*/

}

void CTestCaseCpp::createHypergraph()
{
	pHyper = new CHypergraph();

	pHyper->fatherGraph = NULL;

	map<string,int> classtonum;
	int classnum = 1;
	int i=0;
	int eind_length = 0;
	string hyperstring="";
	string verticestring="";
	string answerstring="";
	map<string,calledclass*>::iterator iterat;
	for(iterat = calledrelation.begin();iterat!=calledrelation.end();++iterat)
	{
		map<string,int>::iterator ensurenum;
		ensurenum = classtonum.find(iterat->first);
		hyperstring += "1 ";
		if(ensurenum == classtonum.end())
		{
			classtonum.insert(pair<string,int>(iterat->first,classnum));
			char nownum[100];
			sprintf_s(nownum,"%d",classnum);
			verticestring += string(nownum)+"  "+iterat->first;

			map<string,string>::iterator findfather;
			findfather = fathermap.find(iterat->first);
			if(findfather!=fathermap.end())
			{
				verticestring += "  father: ";
				verticestring += findfather->second;
			}
			
			verticestring += "\n";
			eind_length ++;
			hyperstring +=string(nownum)+" ";
			//hypergraph.write(nownum,strlen(nownum));
			//hypergraph.write(" ",1);

			classnum ++;
		}
		else
		{
			char nownum[100];
			sprintf_s(nownum,"%d",ensurenum->second);
			hyperstring +=string(nownum)+" ";
			eind_length ++;
			//hypergraph.write(nownum,strlen(nownum));
			//hypergraph.write(" ",1);
		}
		
		answerstring += iterat->first+"   ->   ";;
		
		calledclass *p = iterat->second;
		while(p!=NULL)
		{
			answerstring += p->name+"  ";
		

			ensurenum = classtonum.find(p->name);
			if(ensurenum == classtonum.end())
			{
				classtonum.insert(pair<string,int>(p->name,classnum));
				char nownum[100];
				sprintf_s(nownum,"%d",classnum);
				verticestring += string(nownum)+"  "+p->name+"\n";
				
				hyperstring +=string(nownum)+" ";
				eind_length ++;
				//hypergraph.write(nownum,strlen(nownum));
				//hypergraph.write(" ",1);

				classnum ++;
			}
			else
			{
				char nownum[100];
				sprintf_s(nownum,"%d",ensurenum->second);
				hyperstring +=string(nownum)+" ";
				eind_length ++;
				//hypergraph.write(nownum,strlen(nownum));
				//hypergraph.write(" ",1);
			}
			p=p->next;
		}
		answerstring +="\n";
		hyperstring +="\n";
		//hypergraph.write("\n",1);
		
		i++;

	}

	char stredgenum[100],strverticenum[100];
	sprintf_s(stredgenum,"%d",i);
	sprintf_s(strverticenum,"%d",classnum-1);
	hyperstring = string(stredgenum) + " " + string(strverticenum) + " " +"11" +"\n" + hyperstring;
	for(int k=0;k<classnum-1;k++)
		hyperstring += "1\n";

	pHyper->hyperstring = hyperstring;
	pHyper->answerstring = answerstring;
	pHyper->verticestring = verticestring;
	pHyper->nhedges = i;
	pHyper->nvtxs = classnum-1;
	pHyper->hewgts = new int[i];
	for(int loop=0;loop<i;loop++)
		pHyper->hewgts[loop]=1;

	pHyper->eptr = new int[i+1];
	pHyper->eind = new int[eind_length];
	pHyper->vwgts = new int[classnum-1];
	pHyper->part = new int[classnum-1];
	for(int loop=0;loop<classnum-1;loop++)
		pHyper->vwgts[loop]=1;

	pHyper->inOptions = new int[9];

	int eindnum = 0;
	int edgenum = 0;
	for(iterat = calledrelation.begin();iterat!=calledrelation.end();++iterat)
	{
		map<string,int>::iterator ensurenum;
		ensurenum = classtonum.find(iterat->first);
		
		pHyper->eind[eindnum] = ensurenum->second-1;   //顶点编号从0开始
		pHyper->eptr[edgenum] = eindnum;

		eindnum++;
		
		calledclass *p = iterat->second;
		while(p!=NULL)
		{
			ensurenum = classtonum.find(p->name);
			
			pHyper->eind[eindnum] = ensurenum->second-1;
			eindnum++;
				
			p=p->next;
		}
		edgenum++;


	}
	
	pHyper->eptr[edgenum] = eindnum;
	



	int NumOfLineWord=0;
	string str[10];
	int lastpos = 0;
	int pos = int(strPara.find(" "));
	while(pos!=string::npos)
	{
		str[NumOfLineWord]=strPara.substr(lastpos,pos-lastpos);
		NumOfLineWord ++;
		lastpos = pos;
		pos = int(strPara.find(" ",pos+1));
	}
			
	switch(NumOfLineWord+1)
	{
		case 3:		pHyper->npart				=  atoi(str[1].c_str());
						pHyper->ubfactor			=  atoi(str[2].c_str());
						pHyper->inOptions[0]=0;
						pHyper->inOptions[1]=10;
						pHyper->inOptions[2]=1;
						pHyper->inOptions[3]=1;
						pHyper->inOptions[4]=1;
						pHyper->inOptions[5]=0;
						pHyper->inOptions[6]=0;
						pHyper->inOptions[7]=-1;
						pHyper->inOptions[8]=0;
						break;
		
		case 9:		pHyper->npart				=  atoi(str[1].c_str());
						pHyper->ubfactor			=  atoi(str[2].c_str());
						pHyper->inOptions[0]      =  1;
						pHyper->inOptions[1]		=  atoi(str[3].c_str());
						pHyper->inOptions[2]		=  atoi(str[4].c_str());                     
						pHyper->inOptions[3]		=  atoi(str[5].c_str());
						pHyper->inOptions[4]		=  atoi(str[6].c_str());
						pHyper->inOptions[5]		=  atoi(str[7].c_str());  
						pHyper->inOptions[6]		=  0;
						pHyper->inOptions[7]      =  -1;
						pHyper->inOptions[8]		=  atoi(str[8].c_str());	
						break;
				
		default:		cout<<"hypergraphes wrong format"<<endl;
			
	}
	


}

void CTestCaseCpp::doWriting ( )
{

	cout<<"TestCase: "<<testcasename<<"  start writing...."<<endl;

	runtime = ::GetTickCount();

	string outFoldPath = "..//output";
	#ifdef WIN32
	_mkdir(outFoldPath.c_str());
	#else
	if(NULL==opendir(outFoldPath.c_str()))
	{
		mkdir((outFoldPath.c_str()),0755);
	}
	#endif

	outFoldPath += "//";
	
	outFoldPath += testcasename;
	#ifdef WIN32
	_mkdir(outFoldPath.c_str());
	#else
	if(NULL==opendir(outFoldPath.c_str()))
	{
		mkdir((outFoldPath.c_str()),0755);
	}
	#endif
	
	ofstream ansfile,ansfile2,hypergraph,vertice,timefile,partition, excelFile;
	ansfile.open(string(outFoldPath+"//ans.txt").c_str());
	ansfile.write(lastans.c_str(),int(lastans.length()));
	ansfile.close();

	ansfile2.open(string(outFoldPath+"//relation.txt").c_str());
	hypergraph.open(string(outFoldPath+"//hypergraph.hgr").c_str());
	vertice.open(string(outFoldPath+"//vertice.txt").c_str());
	timefile.open(string(outFoldPath+"//time.txt").c_str());
	partition.open(string(outFoldPath+"//partition.txt").c_str());

	ansfile2.write(pHyper->answerstring.c_str(),int(pHyper->answerstring.length()));
	ansfile2.close();
	hypergraph.write(pHyper->hyperstring.c_str(),int(pHyper->hyperstring.length()));
	hypergraph.close();
	vertice.write(pHyper->verticestring.c_str(),int(pHyper->verticestring.length()));
	vertice.close();

	CHypergraph *pGraphForWrite = pHyper;
	dfsForWriteParts(pGraphForWrite,0);
	
	for(int i=0;i<pHyper->nvtxs;i++)
	{
		char strpart[128];
		sprintf_s(strpart,"%d",pHyper->part[i]);
		partition.write(strpart,int(strlen(strpart)));
		partition.write("\n",1);
	}
	partition.close();

	int now = runtime;
	runtime = ::GetTickCount();
	now = runtime - now;
	char gettime[100];
	sprintf_s(gettime,"%d",now);
	writeTime += "writing time : " + string(gettime)+"ms\n";
	allTime += now;
	writeTime = "testcase name : " + strTestPath + "\n" + writeTime;


	timefile.write(writeTime.c_str(),int(writeTime.length()));
	timefile.close();

	string	filePathName = "..//recordsForExcel.txt";
	excelFile.open ( filePathName.c_str(), ios::app );
	//excelFile.write ( "file name \t hcut \t coupling \t cohesion \t time \n ", strlen("file name \t hcut \t coupling \t cohesion \t time \n ") );
	excelFile.write ( testcasename.c_str(), int(testcasename.length()) );
	excelFile.write("\t", 1 );
	char cpCutNum[128];
	sprintf_s ( cpCutNum, "%d", cutnum );
	excelFile.write ( cpCutNum, int(strlen(cpCutNum)) );
	excelFile.write("\t",1);
	excelFile.write ( "000000", int(strlen("000000")));
	excelFile.write ("\t",1);
	excelFile.write ("000000", 6 );
	excelFile.write ("\t",1);
	sprintf_s(gettime,"%d",allTime);
	excelFile.write (gettime, int(strlen(gettime)) );
	excelFile.write ("\n",1);
	excelFile.close();

	cout<<"TestCase: "<<testcasename<<"  end writing...."<<endl;

}
int CTestCaseCpp::dfsForWriteParts(CHypergraph *G,int parts)
{
	if(G!=NULL)
	{
		CHypergraph *p=G->leftSon;
		CHypergraph *q=G->rightSon;
		CHypergraph *cur_Graph = G;
		if(p==NULL&&q==NULL)
		{
			for(int i=0;i<G->nvtxs;i++)
			{
				int node = i;
				cur_Graph = G;
				while(cur_Graph->fatherGraph!=NULL)
				{
					map<int,int>::iterator iter;
					iter = cur_Graph->mapForFather.find(node);
					node = iter->second;
					cur_Graph = cur_Graph->fatherGraph;
				}
				pHyper->part[node]=parts;
			}
			return 1;
		}
		int count = dfsForWriteParts(p,parts);
		count += dfsForWriteParts(q,parts+count);
		return count;
	}
}
