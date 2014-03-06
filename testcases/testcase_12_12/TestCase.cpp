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
	// �ȴ���ģ���ֵ��ڴ��ͷ�
	// ��ͼ
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

	// ���ߣ����ϰ����˶���, �ڳ��ߵĹ��캯�����ͷ�
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

	// Ȼ����parser���ֵ��ڴ��ͷ�
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
		//����һ��, relation��new������class Ҫ�ͷţ���stRelation�е��������������ͷ�
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

	

	// �����༰����ϵ���ڴ��ͷ�
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
	// ��������ϵ�����ڴ��ͷ�

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
	string				strFileName, strCpp_ext, strH_ext; 
	string				path ;									// ���·��
	string				pathFile;								// ���������ڲ��ļ����·��
	size_t				iLen;									// ���������ڲ��ļ������ȣ�����ȡ�ú�׺��
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
				m_ary_file.push_back( pathFile + strFileName );	//���Ϻ�׺���ļ��뵽ary_filename��
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

// ��������
void CTestCase::doParsing ( )
{ 
	//�����õ����ļ����Զ�����ļ����н�������Ҫ�õ���ͺ���������
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
		m_pDoc->findClass ( str_file );	*/			// ���ò����ຯ��
		//m_pVectorFile.push_back ( m_pDoc );
	} 
	// ������ͺ�������󣬽�һ���������ϵ�Ľ���
	parserClasses ( );								// �ú������ڽ���������������
	parserMethods ( );								// �ú��������к���Ϊ���������ҳ���Щ������������Щ��ĺ������ù�
	parserClassInvoke ( );							// ������亯�����ù�ϵ��������ϵ

	doModeling ( );
}

/*
 * ˼·����ÿ��CSimplex����������ҵ������й�����class, �����ҵ���findClassΪ������newһ��relation
 * relation����LPCLASS����Ϊ��������relation���У�������Ҫ�������ӵ���CSimplexΪ�׵�������
 * ��:	A->B->NULL
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
			//���õ������������������е��඼��һ��������һ���ļ��ж���ĺ��ڲ�ͬ�ļ��ж���Ķ�һ��������Ϊ��ͬ�����
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
	//Ȼ����ÿ������Ϊ��׼������һ��CSimplex��
	pstTempClass	= m_pHeadCl;
	while ( pstTempClass )
	{
		// ��ÿ����Ϊ�����������ļ��в������Ķ���
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
 ���ÿ���࣬�������ļ���ȥ���Ҹ���Ķ��󣬽���浽����ṹ�Ķ����������У����ں�����������ʱ�ȶ�
*/

void CTestCase::findObject ( LPCLASS pClass  )
{
	LPTESTFILE		pFileTmp;
	LPCLASS			pClassTmp;
	//ifstream		pFileMfr;			// ������ֹ��������⣬ifstream��ʹ��ʱ��ҪΪ�䶨�壬ֻ����һ�β��ܶ��ʹ��
	int				j;
	size_t			pos_class;
	size_t			pos_colon;
	string			strLine;

	pFileTmp		= NULL;
	pClassTmp		= NULL;

	for ( j=0; j<(int)m_pVectorFile.size(); j++ )
	{
		pFileTmp = m_pVectorFile.at(j);
		// ȷ���ļ���Ϊ�գ��Ҳ��ڵ�ǰ����ļ�����,��Ϊ�ڵ�ǰ����������ǰ��Ķ����������಻���ڵ��ù�ϵ
		for ( int k=0; k < (int) pFileTmp->m_pVectorClass.size(); k++ )
		{
			pClassTmp	= pFileTmp->m_pVectorClass.at (k);
			if ( pFileTmp->m_strFileName != "" && pClassTmp != pClass )
			{
				// ���������ĲŴ򿪷���
				ifstream		pFileMfr;
				pFileMfr.open( pFileTmp->m_strFileName.c_str() );
				while ( pFileTmp->readString ( pFileMfr, &strLine ) )
				{
					// �������ļ��в����Ƿ��и���Ķ�������,���������������� ���� ������;
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
 ִ���������ǰ��������ӵ�е���Ϣ���£�
 1. ���е�������
 2. ���еĺ�������
 3. ���е����ж�Ӧ�Ķ���
 �ú�����Ҫ�����£�����ÿһ����������λ�����к������õ���䣬ȷ����������Ա�����ĵ���
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
				// ������ߵ�tab�ո�������������⣬�п��ܲ���tab�ո����space�ո���Ľ�
				//mthLine.TrimLeft("	");
                m_oString.trim ( mthLine, " ");
				m_oString.trim ( mthLine, "\t");
				// ���г��ȣ�����ָ��������
				iShift		= (int) strlen ( methodBody ) + 1;
				// �������ù�ϵ�� ( ����г���. �� -> �Ĳ��ֳ�����Ϊ�������ò��֣��ų����ó�Ա��������� )
				// Ҳ�п����ǵ����˿⺯���������ļ��������е�Open�Ⱥ��������ȷ���ǲ�ͬ���ĺ������ã�
				// ����Ҫ��һ��ȷ����������ߵ��ַ����Ƿ�Ϊĳ����Ķ���
				size_t	posObj		= mthLine.find ( "." );				// �������
				size_t	posArrow	= mthLine.find ( "->" );			// ָ�����
				size_t	posBracket	= mthLine.find ( "(" );				// ȷ���Ǻ�������
				size_t	posColon	= mthLine.find (  ";" );			// ȷ�������
				// �ж��Ƿ����ں�������
				if ( (-1 != posObj || -1 != posArrow ) && -1 != posBracket && -1 != posColon )
				{
					// ���ֵ�������»�õ�������ַ������������亯�����ã���ô��Ӧ��Ϊ����
					// �����������ȼٶ���Ϊĳ����Ķ��������ٵ�������Ķ�����в��ң�
					// ����Ӧ�ϣ���������Ϊ��亯�����ã���Ϊ��newһ�����ù�ϵ�����ӵ���ǰcall method��������γɳ�Ա�������ù�ϵ��
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
					// ���Ҷ�Ӧ�Ķ�����, ����ÿ�αȶԣ����ʹ��hash�����棬���ܶ�
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
								// �������к������ҳ���Ӧ�ĺ������Ըú�����Ϊ��������һ��CSimplex���󣬱�����Ӻ������ù�ϵ
								pMthTmpDoc		= m_pHeadMth;
								while ( pMthTmpDoc )
								{
									pMthTemp	= pMthTmpDoc;
									while ( pMthTemp )
									{
										if ( -1 != pMthTemp->mthName.find ( ivkMthName ) )
										{
											// m_pSimMethod Ϊ��ʱ���������û���γ�����ʱ ���������ֻ���ڵ�һ�ν�������ʱ������
											if ( m_pSimMethod == NULL )
											{
												m_pSimMethod				= new CSimplex ( pMthTemp );
												m_pSimMethod->pNextByMth	= m_pSimMthHead;
												m_pSimMthHead				= m_pSimMethod;	
												// ��ʼ��
												pSimMthTemp					= m_pSimMethod;
											}
											else 
											{
												// �����Ŀ����Ϊ��ʵ�ֵ�ĳһ�������������������ʱ��ֻnewһ��Simplex�������е������ĺ�������һ��
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
													// û��������ͬͷ���
													if ( pSimMthTemp->pMethodHead->mthName != pMthTemp->mthName )
														flag	= 1;
													// ������ͬͷ���
													else
													{
														flag	= 0;
														break;
													}
													pSimMthTemp	= pSimMthTemp->pNextByMth;
												}
												// û��������ͬͷ���
												if ( flag == 1 )
												{
													m_pSimMethod				= new CSimplex ( pMthTemp );
													m_pSimMethod->pNextByMth	= m_pSimMthHead;
													pSimMthTemp		= m_pSimMethod;	
												}
												// ������ͬͷ���
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
								
								//m_pInvoke	= new stInvoke ( 1, pClassTmp, ivkMthName );			// ����Ҳ��Ҫ�����ڴ�й¶
								m_pInvoke	= new stInvoke ( 1, pClassTmp, pMethodTmp->mthName );	// ����Ҳ��Ҫ�����ڴ�й¶
								m_pInvoke->pNextInvoke	= m_pIvkHead;
								m_pIvkHead				= m_pInvoke;
								if ( m_pInvoke->pMethod )
								{
									/* ���ҵ��ı����õĺ����ӵ�֮ǰ�ĺ�������
									 * ������������m1, m2, m3 �����ȱ���������
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
				methodBody	+= iShift;			// ������
				index		+= iShift;			// ��ֹ�������
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
		// ��ÿ��������Ӧ��ÿ������
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
		//��ÿ������Ϊ��׼������һ��CSimplex�࣬���ں���������ĵ��ù�ϵ
		m_pSimplex			= new CSimplex ( m_simIndex, pClassTmp );
		m_pSimplex->pNext	= m_psimHead;
		m_psimHead			= m_pSimplex;
		m_simIndex ++;
		m_pSimplex->pclassHead->cpNext_on_simplex = NULL;
		// ��ÿ��Simplex�����������еĳ�Ա�������õõ�ÿ�����ĵ��ù�ϵ
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
	// ����ÿ����ĺ��������������к������õĲ��ַ���
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
						// �˴���Ϊ�ϵ㣬��������
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
 * ���²��ֿ�ʼ��ͼ��ģ
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

// �γɳ�ͼ
void CTestCase::hypergraphGraph ( )
{
	LPVERTEX		pVertex;				// ����
	LPEDGE			pEdge;					// ����
	//LPHYPERGRAPH	pGraph;					// �γɵĳ�ͼ
	//int				iVerCnt;				// �ó�ͼ�ϵĶ�����
	//int				iEdgeCnt;				// �ó�ͼ�ĳ�����

	pVertex			= m_pVertex;
	pEdge			= m_pEdge;
	// ʲô����¿��Խ��������ͼ��
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
	// ����·���ı�ʾ����ʹ��//ʱ����Ϊ����ע�͵�ԭ�����˵� 
	m_pHeadMth->outputMethodInvoke ( outFoldPath + ("methodInvoke.txt"), m_pHeadMth );
	m_pSimplex->outputSimplexToFile ( outFoldPath + ("simplex.txt"), m_pSimplex );

	m_pVertex->outputVertexToFile ( outFoldPath + ("vertex.txt"), m_pVertex );
	m_pEdge->outputEdgesToFile ( outFoldPath + ("edges.txt"), m_pEdge );
	m_pHypergraph->outputHypergraph ( outFoldPath + ("Hypergraph.hgr"), m_pHypergraph );
	
}


