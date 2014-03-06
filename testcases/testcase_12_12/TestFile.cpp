#include "TestFile.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestFile::CTestFile ( )
{
	m_strFileName	= "";
	m_cIndex		= 1;
	
	//pMthHeadOnCls	= NULL;

	m_mIndex		= 1;
	m_mpHead		= NULL;
	m_pNextFile		= NULL;
}

CTestFile::~CTestFile ( )
{
	// 在这里处理函数的内存释放
	LPMETHOD	pMethod;
	pMethod		= m_mpHead;
	while ( pMethod )
	{
		m_mpHead	= pMethod->mthpNext;
		
		/*if ( pMethod->mthBody )
		{
			delete	[] pMethod->mthBody;
		}*/
		delete		pMethod;
		pMethod		= NULL;
		pMethod		= m_mpHead;
	}
}

/*
 * 获取多个连续打开的文件名，并对该文件按行读取操作，找出其中的类
*/
void CTestFile::findClass ( string fileName )
{
	ifstream			file;
	string				strLine;
	LPCLASS				pClass;

	HGLOBAL				hClsMem;
	char*				pClsStr;

	m_strFileName		= fileName;
	file.open ( m_strFileName.c_str() );
	strLine				= "";
	pClass				= NULL;
	pClsStr				= NULL;

	while ( readString (file, &strLine) )
	{
		// 对每行字符串进行解析，找出含有class关键字的地方，并记录跟在class后边的类名
		// 可能要改成switch，class int等关键字作为分支，需要细化
		size_t			strPosition;
		string			strNameClass;
		string			strClsText;
		string			strKeyword;
		size_t			keyword_size;
		size_t			nBrace;
		size_t			semiColon;
		size_t			lBrackt;
		size_t			rBrackt;

		strKeyword		= "class";
		strClsText		= "";
		nBrace			= 0;
		keyword_size	= strKeyword.length ( );
		// 查找所有类
		strPosition		= strLine.find( strKeyword );
		// 找到有class关键字的地方，才开始后续解析工作，如得到类体，便于后续找objects
		if ( string::npos != strPosition)
		{
			// 类定义行后是不含有的;的，如果含有，则有可能是类声明，或是typedef声明包含的类指针以及在某些语句中包含了带有class作为变量等情况
			if ( string::npos != strLine.find(_T(";")) )
			{
				continue;
			}
			// 排除条件判断语句中含有带class字符作为变量的情况
			else if ( string::npos != strLine.find (_T("(")) || string::npos != strLine.find (_T(")")) )
			{
				continue;
			}
			else
			{
				//提取关键字class后面的类名
				strNameClass			= strLine.substr ( strPosition+ keyword_size );
				// 考虑花括号写在类开始的第一行后
				if ( string::npos != strLine.find ( _T("{") ) )
				{
					nBrace ++;
				}
				// 手动管理存储函数体的内存块
				m_oString.trim ( strLine, " " );
				size_t		iShift;
				size_t		dwBytes;

				iShift		= 0;
				dwBytes		= strLine.length ( ) + 1;
				hClsMem		= ::GlobalAlloc ( GHND, dwBytes );				
				pClsStr		= (char*)::GlobalLock ( hClsMem );
				::strcpy ( pClsStr, strLine.c_str() );
				iShift		= strLine.length ( ) + 1;
				::GlobalUnlock ( hClsMem );
				// 继续往下读取
				while ( readString (file, &strLine) )
				{
					m_oString.trim ( strLine, " " );
					size_t		dwBytes_new;
					size_t		sLen;
					dwBytes_new	= strLine.length ( ) + iShift + 1;
					sLen		= strLine.length ( ) ;
					hClsMem		= ::GlobalReAlloc ( hClsMem, dwBytes_new , GHND );
					pClsStr		= (char*) ::GlobalLock ( hClsMem ); 
					pClsStr		= pClsStr + iShift;
					::strcpy ( pClsStr, strLine.c_str() );
					iShift		+= strLine.length ( ) + 1;			
					::GlobalUnlock ( hClsMem );
					// 单行或是在内联函数或构造函数定义中使用到的 {
					//if ( string::npos != strLine.find( _T("{") ) )
					{
						nBrace ++;
						continue;
					}
					// 内联函数或构造函数定义中使用到的反花括号 } 
					if ( string::npos != strLine.find ( _T ("}") ) )
					{
						nBrace --;
						continue;
					}
					if ( nBrace == 0 )
					{
						char*			pStrClssBody;
						pStrClssBody	= NULL;

						hClsMem			= ::GlobalReAlloc ( hClsMem, iShift, GHND );
						pStrClssBody	= (char*) ::GlobalLock ( hClsMem );
						
						pClass			= new stClass ( m_cIndex, strNameClass, NULL, this, pStrClssBody, iShift );
						// 可能一个.h中会有多个类的声明，所以这里需要将同一个.h中的类存起来
						m_pVectorClass.push_back ( pClass );
						m_cIndex ++;
						//AfxMessageBox( pStrClssBody );
						pClsStr	= NULL;
						break;
					}
				}		
			}
				
#ifdef	_DEBUG_OUTPUT
			//outputClassToFile ("..//output//classes.txt", m_pClass_doc );
#endif
		}
	}
	file.close();
	findMethod ( m_strFileName );
}


LPMETHOD CTestFile::findMethod ( string fileName )
{
#ifdef WIN32
	ifstream	pFile;
	string		strMthLine;						
	string		strMthText;					
	string		strMethod;
	string		strClsName;
	LPMETHOD	pFind;
	size_t		iLBracket;
	size_t		iRBracket;
	size_t		nBrace;

	HGLOBAL		hMem;
	char*		pStr;

	pFile.open ( fileName.c_str() );

	pFind		= NULL;
	pStr		= NULL;
	strMthLine	= "";
	strMthText	= "";
	strClsName	= "";
	nBrace		= 0;

	while ( readString ( pFile, &strMthLine ) )
	{
		//omitComment ( &strMthLine );
		// 滤去空行
		if ( strMthLine == "" )
			continue;

		iLBracket	= strMthLine.find( ("(") );
		iRBracket	= strMthLine.find( (")") );
		// 首先查找括号对
		if ( string::npos != iLBracket && string::npos != iRBracket )
		{
			// 查找到控制语句关键字
			if ( findToken ( strMthLine ) )
			{
				continue;
			}
			// 可能是函数调用
			else if ( string::npos != strMthLine.find((";")) )
			{
				continue;
			}
			//函数定义部分
			else
			{
				//strMthLine.TrimLeft (" ");
				m_oString.lTrim ( strMthLine, " " );
				//strMthLine.TrimRight (" ");
				m_oString.rTrim ( strMthLine, " " );
				strMethod	= strMthLine.substr( 0, iLBracket );
				// 获取该函数所在的类名 这里将位于第一个空格(即返回值后的空格)与::之间的字符串作为类名
				size_t	posDColon	= strMethod.find ( _T("::") );
				size_t	posSpace	= strMethod.find_first_of( _T(" ") );
				if ( string::npos != posDColon && string::npos != posSpace )
				{
					strClsName	= strMethod.substr ( posSpace+1, posDColon - ( posSpace+1 ) );
				}
				// 手动管理存储函数体的内存块
				size_t		iShift;
				size_t		dwBytes;

				iShift		= 0;
				pStr		= NULL;
				dwBytes		= strMthLine.length ( ) + 1;
				hMem		= ::GlobalAlloc ( GHND, dwBytes );				
				pStr		= (char*)::GlobalLock ( hMem );
				
				::strcpy ( pStr, strMthLine.c_str() );
				
				iShift		= strMthLine.length ( ) + 1;
			
				::GlobalUnlock ( hMem );

				while ( readString ( pFile, &strMthLine ) )
				{
					m_oString.lTrim ( strMthLine, " " );
					m_oString.rTrim ( strMthLine, " " );
					size_t		dwBytes_new;
					size_t		sLen;
					dwBytes_new	= strMthLine.length ( ) + iShift + 1;
					sLen		= strMthLine.length ( ) ;
					hMem		= ::GlobalReAlloc ( hMem, dwBytes_new , GHND );
					pStr		= (char*) ::GlobalLock ( hMem ); 
					pStr		= pStr + iShift;
					::strcpy ( pStr, strMthLine.c_str() );
					iShift		+= strMthLine.length ( ) + 1;
				
					::GlobalUnlock ( hMem );
#ifdef _DEBUG_APPEND 
					strMthText.Append(strMthLine);
					strMthText.Append("\n");
#endif
					//strMthText	+= strMthLine;
					//strMthText	+= "\n";
					if ( string::npos != strMthLine.find(("{")) )
					{
						nBrace ++;
						continue;
					}
					if ( string::npos != strMthLine.find(("}")) )
					{
						nBrace --;
						continue;
					}
					if ( 0 == nBrace )
					{
						hMem			= ::GlobalReAlloc ( hMem, iShift , GHND );
						char* pStrBody	= (char*)::GlobalLock ( hMem );

						//AfxMessageBox (pStrBody);
#ifdef _DEBUG_APPEND 
						pFind			= new stMethod ( m_mIndex, strMethod, strMthText );
#endif
						pFind			= new stMethod ( m_mIndex, strMethod, pStrBody, (int) iShift );
						// 将该函数与对应的类名存在map中，便于后续将函数添加到对应的类中
						if ( strClsName != "" )
						{
							CIT		cit		= m_pMthToClass.find ( strClsName );
							if ( cit != m_pMthToClass.end() )
							{
								pFind->mthNextOnClass		= m_pMthToClass[strClsName];
								m_pMthToClass[strClsName]	= pFind;
							}
							else 
							{
								m_pMthToClass.insert ( pair< string, LPMETHOD >( strClsName, pFind ) );
								m_pMthToClass[strClsName]	= pFind;
							}
						}			
						pFind->mthpNext	= m_mpHead;
						m_mpHead		= pFind;
						pStr	= NULL;
						break;	
					}	
				} 
				continue;
			} 
		} 
		else
			continue;
	} 
	pFile.close ( );
	return pFind;
}

bool CTestFile::readString ( ifstream& pFile, string* strLine )
{
	size_t		flagCommom_1;
	size_t		flagCommom_2; 
	size_t		flagCommom_3;
	size_t		flag_pre;

	while ( getline ( pFile, *strLine ) )
	{
		flagCommom_1	= strLine->find(("//"));		
		flagCommom_2	= strLine->find(("/*"));		
		flag_pre		= strLine->find(("#"));
		// 判断行注释
		if ( string::npos != flagCommom_1 )
		{
			continue;
		}
		// 判断段注释, 其中包括函数参数内含注释的特殊情况
		if ( string::npos != flagCommom_2 )
		{
			//flagCommom_3	= strLine->find(("*/"));
			if ( string::npos != flagCommom_3 )
			{
				strLine->erase ( flagCommom_2, flagCommom_3 - flagCommom_2 + 2 );
				return true;
			}
			else
			{
				while ( getline ( pFile, *strLine ) )
				{
					//flagCommom_3	= strLine->find(("*/"));
					if ( string::npos != flagCommom_3 )
					{
						break;
					}
					continue;
				}
			
			}
			continue;
		}
		// 判断是否为预处理行，包括#include
		if ( string::npos != flag_pre )
		{
			continue;
		}
		return true;
	}
	// 均不符合上述情况时，默认情况下返回false
	return false;
}

