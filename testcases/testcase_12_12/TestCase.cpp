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
//#include "Shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestCase::CTestCase ( int index, string strNameTest )
{
	m_Index_test	= index;
	m_Name_test		= strNameTest;
	m_pNext_test	= NULL;
	m_pIONext_test	= NULL;
	m_pFile			= NULL;
	m_pFileHead		= NULL;

	m_cIndex		= 1;
	//m_pClass_File	= NULL;

	m_mIndex		= 1;
	m_mpHead		= NULL;

	m_pHeadCl		= NULL;
	m_pstClass		= NULL;
	m_nIndexCls		= 1;

	m_pHeadMth		= NULL;
	m_pstMethod		= NULL;

	m_pIvkHead		= NULL;
	m_pInvoke		= NULL;

	m_simIndex		= 1;
	m_psimHead		= NULL;
	m_pSimplex		= NULL;

	m_pSimMthHead	= NULL;
	m_pSimMethod	= NULL;

	m_pRelated		= NULL;
	m_pReHead		= NULL;


	m_pVerHead		= NULL;
	m_pVertex		= NULL;
	m_vIndex		= 1;
	m_vTotal		= 0;

	m_pEHead		= NULL;
	m_pEdge			= NULL;
	m_eIndex		= 1;
	m_eTotal		= 0;

	m_pGraphHead	= NULL;
	m_pHypergraph	= NULL;
	m_grIndex		= 1;
	stage			= INIT_STAGE;
	
}

CTestCase::~CTestCase ( )
{
	// m_pFile
	LPTESTFILE	pFile;
	pFile		= NULL;

	pFile		= m_pFile;
	while ( pFile )
	{
		m_pFile		= pFile->m_pNextFile;
		delete		pFile;
		pFile		= NULL;
		pFile		= m_pFile;
	}
	// 先处理建模部分的内存释放
	// 超图
	LPHYPERGRAPH	pHypergraph;
	pHypergraph		= NULL;
	pHypergraph		= m_pGraphHead;
	while ( pHypergraph )
	{
		m_pGraphHead	= pHypergraph->m_pGraphNext;
		delete			pHypergraph;
		pHypergraph		= NULL;
		pHypergraph		= m_pGraphHead;
	}

	//LPSTEDGE	pstEdge;
	//pstEdge		= m_pstEdge;
	//while ( pstEdge )
	//{
	//	m_pstEdge	= pstEdge->pNext;
	//	//delete		pstEdge;
	//	pstEdge		= NULL;
	//	pstEdge		= m_pstEdge;
	//}

	// 超边，边上包括了顶点, 在超边的构造函数中释放
	LPEDGE		pEdge;
	pEdge		= NULL;
	pEdge		= m_pEHead;
	while ( pEdge )
	{
		m_pEHead	= pEdge->m_pENext;
		delete		pEdge;
		pEdge		= NULL;
		pEdge		= m_pEHead;
	}

	// 然后处理parser部分的内存释放
	LPSIMPLEX	pSimplex;
	pSimplex	= NULL;
	pSimplex	= m_psimHead;
	while ( pSimplex )
	{
		m_psimHead	= pSimplex->pNext;
		delete		pSimplex;
		pSimplex	= NULL;
		pSimplex	= m_psimHead;
	}

	LPRELATION	pRelation;
	pRelation	= NULL;
	pRelation	= m_pReHead;
	while ( pRelation )
	{
		m_pReHead	= pRelation->pNextRelation;
		//还有一层, relation中new出来的class 要释放，在stRelation中调用其析构函数释放
		delete		pRelation;
		pRelation	= NULL;
		pRelation	= m_pReHead;
	}
	
	LPINVOKE	pInvoke;
	pInvoke		= NULL;
	pInvoke		= m_pIvkHead;
	while ( pInvoke )
	{
		m_pIvkHead	= pInvoke->pNextInvoke;
		delete		pInvoke;
		pInvoke		= NULL;
		pInvoke		= m_pIvkHead;
	}

	// m_pSimMethod
	LPSIMPLEX	pMthSim;
	pMthSim		= NULL;
	pMthSim		= m_pSimMthHead;
	while ( pMthSim )
	{
		m_pSimMthHead	= pMthSim->pNextByMth;
		delete			pMthSim;
		pMthSim			= NULL;
		pMthSim			= m_pSimMthHead;
	}

	

	// 处理类及类间关系的内存释放
	LPCLASS		pClass;
	pClass		= NULL;
	pClass		= m_pHeadCl;
	while ( pClass )
	{
		m_pHeadCl	= pClass->cpNext;
		delete		pClass;
		pClass		= NULL;
		pClass		= m_pHeadCl;
	}
	// 处理函数关系链的内存释放

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
 * doReading: 遍历每个testcase，获取其中的所有.cpp和.h文件，存于m_ary_file数组中
*/

void CTestCase::doReading ( )
{
#ifdef WIN32
	WIN32_FIND_DATA		fileData;
	HANDLE				hTempFind;
	string				strFileName, strCpp_ext, strH_ext; 
	string				path ;									// 相对路径
	string				pathFile;								// 遍历到的内部文件相对路径
	size_t				iLen;									// 被遍历的内部文件名长度，便于取得后缀名
	path				= m_Name_test + "//*.*";
	pathFile			= m_Name_test + "//";

	hTempFind	= FindFirstFile ( path.c_str(), &fileData );
	while ( hTempFind != INVALID_HANDLE_VALUE ) 
	{ 
		strFileName		= fileData.cFileName;
		
		if ( strFileName != "." && strFileName != ".." )
		{
			iLen			= strFileName.length();
			strCpp_ext		= strFileName.substr ( iLen-3, 3 );
			strH_ext		= strFileName.substr ( iLen-1, 1 );
			if ( strCpp_ext == "cpp" )   
			{  
				m_ary_file.push_back ( pathFile + strFileName );		
			} 
			if ( strH_ext == "h")
			{
				m_ary_file.push_back( pathFile + strFileName );	//符合后缀名的加入到ary_filename中
			}
			
		}
		else
		{
			// 断点
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
    m_Name_test = m_oString.rTrim(m_Name_test,"\r");
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

// 解析部分
void CTestCase::doParsing ( )
{ 
	//遍历得到的文件并对读入的文件进行解析。主要得到类和函数的链表
	for ( int i = 0; i < (int) m_ary_file.size(); i++ )
	{
		string str_file = "";
		str_file	= m_ary_file.at ( i );
		m_pFile		= new CTestFile ( );

		m_pFile->m_pNextFile	= m_pFileHead;
		m_pFileHead				= m_pFile;

		m_pFile->findClass ( str_file );
		m_pVectorFile.push_back ( m_pFile );
		/*m_pDoc		= new CArchitectureDoc ( );
		m_pDoc->findClass ( str_file );	*/			// 调用查找类函数
		//m_pVectorFile.push_back ( m_pDoc );
	} 
	// 生成类和函数链表后，进一步完成类间关系的解析
	parserClasses ( );								// 该函数用于将所有类连接起来
	parserMethods ( );								// 该函数以所有函数为分析对象，找出哪些函数被其他哪些类的函数调用过
	parserClassInvoke ( );							// 根据类间函数调用关系分析类间关系

	doModeling ( );
}

/*
 * 思路：对每个CSimplex分析，如果找到跟其有关联的class, 就以找到的findClass为参数，new一个relation
 * relation是以LPCLASS对象为参数，在relation类中，我们需要将其链接到以CSimplex为首的链表中
 * 如:	A->B->NULL
 *		B->C->D->NULL
 *		C->NULL
 *		D->NULL
*/

void CTestCase::parserClasses ( )
{
	//CArchitectureDoc*	pDocFile;
	LPTESTFILE		pFileTmp;
	LPCLASS			pstTempClass;

	pFileTmp		= NULL;
	pstTempClass	= NULL;

	vector < stClass* >		pTmpVector;

	for ( int i=0; i < (int)m_pVectorFile.size(); i++ )
	{
		pFileTmp	= m_pVectorFile.at (i);
		//map<LPCLASS, LPMETHOD> mapDoc	= pDocFile->cl_mth_map;
		//m_pstClass  = pFileTmp->m_pClass_file;
		pTmpVector	= pFileTmp->m_pVectorClass;
		for ( int j=0; j < (int) pTmpVector.size(); j++ )
		{
			//将得到的类链接起来，所有的类都成一条链表，在一个文件中定义的和在不同文件中定义的都一样，都作为不同类分析
			m_pstClass	= pTmpVector.at (j);
			m_pstClass->cpNext	= m_pHeadCl;
			m_pHeadCl					= m_pstClass;
			m_pHeadCl->m_cIndex			= m_nIndexCls;
			m_nIndexCls++ ;
		}	
		m_pstMethod	= pFileTmp->m_mpHead;
		if ( m_pstMethod )
		{
			m_pstMethod->mthNextOnDoc	= m_pHeadMth;
			m_pHeadMth					= m_pstMethod;
		}
	}
	//然后以每个类作为标准，建立一个CSimplex类
	pstTempClass	= m_pHeadCl;
	while ( pstTempClass )
	{
		// 对每个类为主，到其他文件中查找它的对象
		findObject ( pstTempClass );
		pstTempClass	= pstTempClass->cpNext;
	}
#ifdef _DEBUG_OUTPUT
	//outputSimplexToFile ( ("..//output//simplex.txt"), m_pSimplex );
	/*outputMethodInvoke ( ("..//output//methodInvoke.txt" ), m_pHeadMth );*/
#endif

#ifdef _DEBUG_AFXMESSAGE
	AfxMessageBox (("success! See simplex.txt") );
#endif
}

/*
 针对每个类，到其他文件中去查找该类的对象，将其存到该类结构的对象名数组中，便于后续分析调用时比对
*/

void CTestCase::findObject ( LPCLASS pClass  )
{
	LPTESTFILE		pFileTmp;
	LPCLASS			pClassTmp;
	//ifstream		pFileMfr;			// 这里出现过严重问题，ifstream在使用时需要为其定义，只定义一次不能多次使用
	int				j;
	size_t			pos_class;
	size_t			pos_colon;
	string			strLine;

	pFileTmp		= NULL;
	pClassTmp		= NULL;

	for ( j=0; j<(int)m_pVectorFile.size(); j++ )
	{
		pFileTmp = m_pVectorFile.at(j);
		// 确保文件不为空，且不在当前类的文件中找,因为在当前类中声明当前类的对象，与其他类不存在调用关系
		for ( int k=0; k < (int) pFileTmp->m_pVectorClass.size(); k++ )
		{
			pClassTmp	= pFileTmp->m_pVectorClass.at (k);
			if ( pFileTmp->m_strFileName != "" && pClassTmp != pClass )
			{
				// 符合条件的才打开分析
				ifstream		pFileMfr;
				pFileMfr.open( pFileTmp->m_strFileName.c_str() );
				while ( pFileTmp->readString ( pFileMfr, &strLine ) )
				{
					// 在其他文件中查找是否有该类的对象声明,如类似这样的声明 类名 对象名;
                    m_oString.trim(pClass->className,"\r");
					pos_class	= strLine.find ( pClass->className );

					if ( -1 != pos_class )
					{
						//pClassFind	= pDocFile->m_pClass_doc;
						pos_colon	= strLine.find(";");
						if ( -1 != pos_colon )
						{
							string		strName		= strLine.substr ( pos_class + pClass->className.length() + 1, pos_colon - (pos_class + pClass->className.length() + 1) );
							pClass->objName.push_back ( strName );
						}
					}
				}
				pFileMfr.close();	
			}
		}
		
	}
}

/* 
 执行这个函数前，我们所拥有的信息如下：
 1. 所有的类链表
 2. 所有的函数链表
 3. 所有的类中对应的对象
 该函数需要做的事：遍历每一个函数，定位到其中函数调用的语句，确定它是类间成员函数的调用
*/

void CTestCase::parserMethods ( )
{
	//CArchitectureDoc	*pTempDoc;
	LPTESTFILE			pFileTmp;
	LPMETHOD			pMethodTmp;
	LPCLASS				pClassTmp;
	LPSIMPLEX			pSimMthTemp;	
	char*				methodBody;
	int					mthLength;
	int					iShift;
	int					index;
	string				mthLine;
	string				strObjName;
	string				ivkMthName;

	pFileTmp			= NULL;
	pMethodTmp			= NULL;
	pClassTmp			= NULL;
	pSimMthTemp			= NULL;
	mthLine				= "";
	strObjName			= "";
	ivkMthName			= "";
	for ( int k = 0; k < (int) m_pVectorFile.size(); k++ )
	{
		
		pFileTmp	= m_pVectorFile.at(k);
		//pSimTmp		= pTempDoc->m_pSimMethod;
		pMethodTmp	= pFileTmp->m_mpHead;
		//while ( pSimTmp )
		while ( pMethodTmp )
		{
          
			//pMethodTmp	= pSimTmp->pMethodHead;
			methodBody	= pMethodTmp->mthBody;
			mthLength	= pMethodTmp->mthBodyLen;
			iShift		= 0;
			index		= 0;
			//for ( int index=0; index < mthLength; index++ )
			while ( index < mthLength )
			{
				mthLine		= methodBody;
				// 消除左边的tab空格，这里可能有问题，有可能不是tab空格而是space空格，需改进
				//mthLine.TrimLeft("	");
                m_oString.trim ( mthLine, " ");
				m_oString.trim ( mthLine, "\t");
				// 该行长度，便于指针往后移
				iShift		= (int) strlen ( methodBody ) + 1;
				// 分析调用关系处 ( 语句中出现. 和 -> 的部分初步定为函数调用部分，排除调用成员变量的情况 )
				// 也有可能是调用了库函数，比如文件流操作中的Open等函数，如何确定是不同类间的函数调用？
				// 所以要进一步确定操作符左边的字符串是否为某个类的对象
				size_t	posObj		= mthLine.find ( "." );				// 对象调用
				size_t	posArrow	= mthLine.find ( "->" );			// 指针调用
				size_t	posBracket	= mthLine.find ( "(" );				// 确保是函数调用
				size_t	posColon	= mthLine.find (  ";" );			// 确保是语句
				// 判断是否属于函数调用
				if ( (-1 != posObj || -1 != posArrow ) && -1 != posBracket && -1 != posColon )
				{
					// 两种调用情况下获得的最左边字符串，如果是类间函数调用，那么它应该为类名
					// 下述做法是先假定它为某个类的对象名，再到各个类的对象表中查找，
					// 若对应上，则该条语句为类间函数调用，且为它new一个调用关系，链接到当前call method的链表后，形成成员函数调用关系链
					if ( -1 != posObj )
					{
						strObjName		= mthLine.substr ( 0, posObj );
						ivkMthName		= mthLine.substr ( posObj + 1, posBracket - (posObj + 1) );
					}

					if ( -1 != posArrow	)
					{
						strObjName		= mthLine.substr ( 0, posArrow );
						ivkMthName		= mthLine.substr ( posArrow + 2, posBracket - ( posArrow + 2 ) );
					}

					//string		ivkMthName	= mthLine.Mid( posObj + 1, posBracket - (posObj + strObjName.GetLength() + 1) );
					// 查找对应的对象名, 这里每次比对，如果使用hash表来存，会快很多
					pClassTmp	= m_pHeadCl;
					while ( pClassTmp )
					{
						string		objTmp = "";
						for ( int i = 0; i < (int) pClassTmp->objName.size(); i++ )
						{
							objTmp	= pClassTmp->objName [i];
							//objTmp.Trim(" ");
							m_oString.trim ( objTmp, " " );
							if ( strObjName == objTmp )
							{
								ivkMthName	= pClassTmp->className + (("::")) + ivkMthName;
								LPMETHOD		pMthTemp;
								LPMETHOD		pMthTmpDoc;
								//pMthTemp					= new stMethod ( 0, ivkMthName, NULL, 0 );
								// 遍历已有函数，找出对应的函数，以该函数作为参数建立一个CSimplex对象，便于添加函数调用关系
								pMthTmpDoc		= m_pHeadMth;
								while ( pMthTmpDoc )
								{
									pMthTemp	= pMthTmpDoc;
									while ( pMthTemp )
									{
										if ( -1 != pMthTemp->mthName.find ( ivkMthName ) )
										{
											// m_pSimMethod 为空时，即最初还没有形成链表时 （这个过程只会在第一次进入该语句时发生）
											if ( m_pSimMethod == NULL )
											{
												m_pSimMethod				= new CSimplex ( pMthTemp );
												m_pSimMethod->pNextByMth	= m_pSimMthHead;
												m_pSimMthHead				= m_pSimMethod;	
												// 初始化
												pSimMthTemp					= m_pSimMethod;
											}
											else 
											{
												// 这里的目的是为了实现当某一个函数被多个函数调用时，只new一个Simplex，将所有调用它的函数连在一起
												/*if ( m_pSimMethod->pMethodHead->mthName != pMthTemp->mthName )
												{
													m_pSimMethod				= new CSimplex ( pMthTemp );
													m_pSimMethod->pNextByMth	= m_pSimMthHead;
													m_pSimMthHead				= m_pSimMethod;	
												}
												else 
												{
													break;
												}*/
												pSimMthTemp		= m_pSimMethod;
												int flag		= 0;
												while ( pSimMthTemp )
												{	
													// 没有遇到相同头结点
													if ( pSimMthTemp->pMethodHead->mthName != pMthTemp->mthName )
														flag	= 1;
													// 遇到相同头结点
													else
													{
														flag	= 0;
														break;
													}
													pSimMthTemp	= pSimMthTemp->pNextByMth;
												}
												// 没有遇到相同头结点
												if ( flag == 1 )
												{
													m_pSimMethod				= new CSimplex ( pMthTemp );
													m_pSimMethod->pNextByMth	= m_pSimMthHead;
													pSimMthTemp		= m_pSimMethod;	
												}
												// 遇到相同头结点
												else if ( flag == 0 )
												{
													break;
												}
											}
										}
										pMthTemp	= pMthTemp->mthpNext;
									}
									pMthTmpDoc		= pMthTmpDoc->mthNextOnDoc;
								}
								
								//m_pInvoke	= new stInvoke ( 1, pClassTmp, ivkMthName );			// 这里也需要处理内存泄露
								m_pInvoke	= new stInvoke ( 1, pClassTmp, pMethodTmp->mthName );	// 这里也需要处理内存泄露
								m_pInvoke->pNextInvoke	= m_pIvkHead;
								m_pIvkHead				= m_pInvoke;
								if ( m_pInvoke->pMethod )
								{
									/* 将找到的被调用的函数加到之前的函数链上
									 * 如有三个函数m1, m2, m3 已首先被连成链表
									 * m3 -> m2
									 * m2 
									 * m1 -> m2
									*/
									//pFindDoc	= pTempDoc;
									//m_pSimMethod->addSimplexMethod ( m_pInvoke->pMethod );
									pSimMthTemp->addSimplexMethod ( m_pInvoke->pMethod );
									//invokeFlag	= true;
									//AfxMessageBox ( ivkMthName );	
								}
							}
							continue;
						}
						pClassTmp	= pClassTmp->cpNext;
					}	
				}	
				methodBody	+= iShift;			// 往后移
				index		+= iShift;			// 防止出现溢出
			}
			pMethodTmp	= pMethodTmp->mthpNext;
			//pSimTmp		= pSimTmp->pNextByMth;		
		}
	}
#ifdef _DEBUG_OUTPUT
	//outputMethodInvoke ( ("..//output//methodInvoke.txt" ), m_pHeadMth );
#endif
}

void CTestCase::parserClassInvoke ( )
{
	//CArchitectureDoc*	pDocTmp;
	LPTESTFILE			pFileTmp;
	LPCLASS				pClassTmp;
	LPCLASS				pFindClass;

	pFileTmp			= NULL;
	pClassTmp			= NULL;
	pFindClass			= NULL;

	pClassTmp			= m_pHeadCl;
	while ( pClassTmp )
	{
		LPMETHOD	pMethod;
		pMethod		= NULL;
		// 将每个函数对应到每个类中
		for ( int j = 0; j < (int) m_pVectorFile.size(); j++ )
		{
			pFileTmp		= m_pVectorFile[j];
			if ( pFileTmp->m_mpHead )
			{
				pMethod		= pFileTmp->m_mpHead;
				size_t		pos;
				pMethod		= pFileTmp->m_mpHead;
				m_oString.trim ( pClassTmp->className, " " ); 
				m_oString.trim(pClassTmp->className,"\r");
				pos			= pMethod->mthName.find ( pClassTmp->className );
               
				if ( -1 != pos ) 
				{
					pClassTmp->mthPhead	= pMethod;
				}
			}
		
        }
		//以每个类作为标准，建立一个CSimplex类，便于后续生成类的调用关系
		m_pSimplex			= new CSimplex ( m_simIndex, pClassTmp );
		m_pSimplex->pNext	= m_psimHead;
		m_psimHead			= m_pSimplex;
		m_simIndex ++;
		m_pSimplex->pclassHead->cpNext_on_simplex = NULL;
		// 对每个Simplex，根据它们中的成员函数调用得到每个类间的调用关系
		pFindClass	= findRelationClass (  m_pSimplex );
		pClassTmp	= pClassTmp->cpNext;
	}
#ifdef _DEBUG_OUTPUT
	//outputSimplexToFile ( ("..//output//simplex.txt"), m_pSimplex );
#endif
}

LPCLASS CTestCase::findRelationClass ( LPSIMPLEX pSim )
{
	LPCLASS		pFind;
	LPCLASS		pClTmp;
	LPMETHOD	pMthTemp;
	LPMETHOD	pMthTmpIvk;
	string		strNameCl;

	pFind		= NULL;
	pClTmp		= NULL;
	pMthTemp	= NULL;
	pMthTmpIvk	= NULL;
	strNameCl	= "";
	// 遍历每个类的函数链表，对其中有函数调用的部分分析
	pClTmp		= pSim->pclassHead;
	if ( pClTmp )
		pMthTemp	= pClTmp->mthPhead;

	while ( pMthTemp )
	{
		pMthTmpIvk	= pMthTemp;	
		while ( pMthTmpIvk )
		{
			if ( pMthTmpIvk->mthNextOnIvk )
			{
				//pFind	= pClTmp;
				string strNameMth	= pMthTmpIvk->mthNextOnIvk->mthName;
				size_t posComma	= strNameMth.find( "::" );
				size_t posSpace	= strNameMth.find( " " );
				strNameCl	= strNameMth.substr ( posSpace+1, posComma - ( posSpace + 1 ) );
				LPCLASS		pClassTemp;
				pClassTemp	= m_pHeadCl;
				while ( pClassTemp )
				{
					if ( pClassTemp->className == strNameCl )
					{
						pFind	= pClassTemp;
						m_pRelated = new stRelation ( pFind->className, pFind->m_cIndex );
						m_pRelated->pNextRelation	= m_pReHead;
						m_pReHead	= m_pRelated;
						pSim->addSimplexClass ( m_pRelated->pCls );
					}
					else
					{
						// 此处作为断点，不做处理
					}
					pClassTemp	= pClassTemp->cpNext;
				}
				//m_pRelated = new stRelation ( pFind->className, pFind->m_cIndex );
				//m_pRelated = new stRelation ( strNameCl, 0 );
				/*m_pRelated->pNextRelation	= m_pReHead;
				m_pReHead	= m_pRelated;
				pSim->addSimplexClass ( m_pRelated->pCls );*/
			}
			pMthTmpIvk = pMthTmpIvk->mthNextOnIvk;
		}
		pMthTemp	= pMthTemp->mthpNext;
	}
	return pFind;
}

void CTestCase::doModeling ( )
{
	hypergraphVertex ( );
	hypergraphEdge ( );
	hypergraphGraph ( );
}


/*
 * 以下部分开始超图建模
*/
// Create vertices based on classes
void CTestCase::hypergraphVertex ( )
{
	LPCLASS			pClassTmp;

	pClassTmp		= m_pHeadCl;
	while ( pClassTmp )
	{	
		m_pVertex				= new CVertex ( pClassTmp->m_cIndex, pClassTmp );
		m_pVertex->m_pvNext		= m_pVerHead;
		m_pVerHead				= m_pVertex;
		//m_vIndex ++;
		m_vTotal ++;

		pClassTmp	= pClassTmp->cpNext;
	}
#ifdef _DEBUG_OUTPUT
	//m_pVertex->outputVertexToFile ( ("..//output//vertex.txt"), m_pVertex );
#endif
}

// Create edges according to vertices
void CTestCase::hypergraphEdge ( )
{
	LPVERTEX		pVerteTmp;
	LPCLASS			pClassTmp;
	LPSIMPLEX		pSimplexTmp;

	pClassTmp		= NULL;
	pVerteTmp		= m_pVertex;
	pSimplexTmp		= m_pSimplex;

	while ( pVerteTmp )
	{
		m_pEdge		= new CEdge ( m_eIndex, pVerteTmp );
		while ( pSimplexTmp )
		{
			pClassTmp	= pSimplexTmp->pclassHead;
			if ( pClassTmp = pVerteTmp->m_pvHead )
			{
				while ( pClassTmp )
				{	
					if ( pClassTmp->cpNext_on_simplex && pClassTmp->cpNext_on_simplex->className != "")
					{
						m_pstEdge	= new stEdge ( pClassTmp->cpNext_on_simplex );
						m_pEdge->addVertex ( m_pstEdge->pVertex );

					}	
					pClassTmp	= pClassTmp->cpNext_on_simplex;
				}
				break;
			}

			pSimplexTmp		= pSimplexTmp->pNext;
		}
		m_pEdge->m_pENext	= m_pEHead;
		m_pEHead			= m_pEdge;
		m_eIndex ++;
		m_eTotal ++;
		pVerteTmp	= pVerteTmp->m_pvNext;
	}
#ifdef _DEBUG_OUTPUT
	//m_pEdge->outputEdgesToFile ( ("..//output//edges.txt"), m_pEdge );
#endif
}

// 形成超图
void CTestCase::hypergraphGraph ( )
{
	LPVERTEX		pVertex;				// 顶点
	LPEDGE			pEdge;					// 超边
	//LPHYPERGRAPH	pGraph;					// 形成的超图
	//int				iVerCnt;				// 该超图上的顶点数
	//int				iEdgeCnt;				// 该超图的超边数

	pVertex			= m_pVertex;
	pEdge			= m_pEdge;
	// 什么情况下可以建立多个超图？
	if ( pEdge && pVertex )
	{
		m_pHypergraph		= new CHypergraph ( m_grIndex, m_vTotal, m_eTotal, pVertex, pEdge );
		m_pHypergraph->m_pGraphNext		= m_pGraphHead;
		m_pGraphHead					= m_pHypergraph;
		m_grIndex ++;
	}
}

void CTestCase::doWriting ( )
{
	string			outFoldPath;
	string			outFileName;
	size_t			pos;
	string			preFix;
	preFix			=  "..//testcases//";
	pos				= m_Name_test.find ( preFix );
	if ( -1 != pos )
	{
		outFileName		= m_Name_test.substr ( pos + preFix.length() );
		outFoldPath		= "..//output//" + outFileName;
	}
	//
	#ifdef WIN32
	if ( !PathIsDirectory ( outFoldPath.c_str() ) )
	{
		CreateDirectory ( outFoldPath.c_str(), NULL );
	}
	#else
	if(NULL==opendir(outFoldPath.c_str()))
	{
		mkdir((outFoldPath.c_str()),0755);
	}
	#endif
	// 这里路径的表示，在使用//时会因为处理注释的原因将其滤掉 
	m_pHeadMth->outputMethodInvoke ( outFoldPath + ("methodInvoke.txt"), m_pHeadMth );
	m_pSimplex->outputSimplexToFile ( outFoldPath + ("simplex.txt"), m_pSimplex );

	m_pVertex->outputVertexToFile ( outFoldPath + ("vertex.txt"), m_pVertex );
	m_pEdge->outputEdgesToFile ( outFoldPath + ("edges.txt"), m_pEdge );
	m_pHypergraph->outputHypergraph ( outFoldPath + ("Hypergraph.hgr"), m_pHypergraph );
	
}


