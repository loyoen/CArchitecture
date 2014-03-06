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
		size_t			strPosition_1;
		size_t			strPosition_2;
		string			strNameClass;
		string			strClsText;
		string			strKeyword_1;
		string			strKeyword_2;
		size_t			keyword_size_1;
		size_t			keyword_size_2;
		size_t			nBrace;
		size_t			semiColon;
		size_t			lBrackt;
		size_t			rBrackt;

		strKeyword_1	= "class";
		strKeyword_2	= "struct";
		strClsText		= "";
		nBrace			= 0;
		keyword_size_1	= strKeyword_1.length ( );
		keyword_size_2	= strKeyword_2.length ( );
		// 查找所有类
		strPosition_1	= strLine.find( strKeyword_1 );
		strPosition_2	= strLine.find( strKeyword_2 );
		// 找到有class或struct关键字的地方，才开始后续解析工作，如得到类体，便于后续找objects
		// 找class和struct时需要确定它们是否是关键字，即确保它们左右有空格或是tab键
		//if ( string::npos != strPosition_1 || string::npos != strPosition_2 )
		if ( string::npos != strPosition_1 )
		{
			// 类定义行后是不含有的;的，如果含有，则有可能是类声明，或是typedef声明包含的类指针以及在某些语句中包含了带有class作为变量等情况
			if ( string::npos != strLine.find(";") )
			{
				// 遇到由typedef声明的类指针类型，即实现碰到typedef定义的类指针即可对应到相应的类
				if ( string::npos != strLine.find ("typedef") )
				{
					// 这里用于提取类名及其对应的类指针名
					// 格式:typedef	class CTestFile		_CTESTFILE,		*LPTESTFILE;
					size_t			posColon;		// 分号位置
					size_t			posStar;		// *位置
					size_t			posKeyClass;	// 类关键字class
					size_t			posKeyStruct;	// 结构体关键字struct
					size_t			posCName;		// 类名，如CTestFile
					size_t			posNameEnd;
					string			pointName;
					string			className;
					//string		strTmp;

					pointName		= "";
					className		= "";
					posNameEnd		= string::npos;
					posColon		= strLine.find (";");
					posStar			= strLine.find ("*");
					pointName		= strLine.substr ( posStar + 1, posColon - posStar - 1 );
					posKeyClass		= strLine.find ("class");
					posKeyStruct	= strLine.find("struct");
					if ( posKeyClass != string::npos || posKeyStruct != string::npos )
					{
						if ( posKeyClass != string::npos )
						{
							for ( size_t pos = posKeyClass + 5; pos < posStar; pos++ )
							{
								if ( strLine[pos] == ' ' || strLine[pos] == '	' )
									continue;
								// 从class后开始遇到第一个不是空格或是tab键的字符，即为类名的起始位置
								posCName	= pos;
								break;
							}
							// 下面以同样的方法找到类名的终止位置
							for ( size_t posTmp = posCName; posTmp < posStar; posTmp++ )
							{
								if ( strLine[posTmp] != ' '&& strLine[posTmp] != '\t' )
									continue;
								posNameEnd	= posTmp;
								break;
							}
						}
						//if ( posKeyStruct != string::npos )
						//{
						//	for ( size_t pos = posKeyStruct + 6; pos < posStar; pos++ )
						//	{
						//		if ( strLine[pos] == ' ' || strLine[pos] == '	' )
						//			continue;
						//		// 从class后开始遇到第一个不是空格或是tab键的字符，即为类名的起始位置
						//		posCName	= pos;
						//		break;
						//	}
						//	// 下面以同样的方法找到类名的终止位置
						//	for ( size_t posTmp = posCName; posTmp < posStar; posTmp++ )
						//	{
						//		if ( strLine[posTmp] != ' '&& strLine[posTmp] != '	' )
						//			continue;
						//		posNameEnd	= posTmp;
						//		break;
						//	}
						//}
						
						if ( posCName != string::npos && posNameEnd != string::npos && posCName < posNameEnd )
						{
							className	= strLine.substr ( posCName, posNameEnd-posCName );
						}
						if ( className != "" && pointName != "" )
							m_pTypeToClass.insert ( pair<string, string>( className, pointName ) );
					}
					else
					{

					}
				}
				continue;
			}
			// 排除条件判断语句中含有带class字符作为变量的情况
			else if ( string::npos != strLine.find ("(") || string::npos != strLine.find (")") )
			{
				continue;
			}
			else
			{
				if ( string::npos != strPosition_1 )
				{
					//提取关键字class后面的类名
					size_t		posColon;				// 冒号的位置，为了提取包含继承情况的类名
					posColon	= strLine.find ( ":" );
					if ( posColon != string::npos )
					{
						strNameClass	= strLine.substr ( strPosition_1 + keyword_size_1, posColon - strPosition_1 - keyword_size_1 );
					}
					else
						strNameClass	= strLine.substr ( strPosition_1+ keyword_size_1 );
					if ( strNameClass == "CVertex")
					{
						AfxMessageBox(_T("类名是我 在哪"));
					}
				}
				//if ( string::npos != strPosition_2 )
				//{
				//	// 提取关键字struct后面的结构体名，也作类
				//	strNameClass	= strLine.substr ( strPosition_2+ keyword_size_2 );
				//}
				
				// 考虑花括号写在类开始的第一行后
				if ( string::npos != strLine.find ( "{" ) )
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
					if ( string::npos != strLine.find( "{" ) )
					{
						nBrace ++;
						continue;
					}
					// 内联函数或构造函数定义中使用到的反花括号 } 
					if ( string::npos != strLine.find ("}")  )
					{
						nBrace --;
						//continue;
					}
					// 类结尾
					/*if ( string::npos != strLine.find( _T("};") ) )
					{
						nBrace --;
						continue;
					}*/
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
/*
 * 获取多个连续打开的文件名，并对该文件按行读取操作，找出其中的函数
 * 找函数的思路：先找"("")"，包含括号对的语句可能有以下情况：
 * 1.控制语句 ( if, while, for, switch )
 * 2.各种情况的函数调用
 * 3.真正所要找的函数定义
 * 通过排除该行代码不含1中所提的关键字，可以排除情况1；通过继续往后寻找花括号对{ }，可排除情况2
 * 综上，逐行代码分析 if ( 该行含有括号对 )，无则继续往下行分析，有则查该行是否含有控制语句关键字；
 * if (含关键字)，则继续往下行分析，找到控制语句结尾的花括号对；不含关键字，则继续往下行分析花括号对，
 * 直到花括号配对成功，则为函数定义
*/
LPMETHOD CTestFile::findMethod ( string fileName )
{
#ifdef WIN32	
	ifstream	pFile;
	string		strMthLine;						// 按行读取的内容
	string		strMthText;						// 存某一段函数定义主体
	string		strMethod;
	string		strClsName;
	LPMETHOD	pFind;
	size_t		iLBracket;
	size_t		iRBracket;
	size_t		nBrace;							// 记录花括号对

	HGLOBAL		hMem;
	char*		pStr;

	pFile.open ( fileName.c_str() );

	pFind		= NULL;
	pStr		= NULL;
	strMthLine	= "";
	strMthText	= "";
	strClsName	= "";
	nBrace		= 0;

	//::memset( pStr, 0 );

	//while ( pFile.ReadString( strMthLine ) )
	while ( readString ( pFile, &strMthLine ) )
	{
		//omitComment ( &strMthLine );
		// 滤去空行
		if ( strMthLine == "" )
			continue;
		m_oString.lTrim ( strMthLine, " " );
		m_oString.rTrim ( strMthLine, " " );
		iLBracket	= strMthLine.find("(");
		iRBracket	= strMthLine.find(")");
		
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
				strMethod	= strMthLine.substr( 0, iLBracket );
				
				// 获取该函数所在的类名 这里将位于第一个空格(即返回值后的空格)与::之间的字符串作为类名
				size_t	posDColon	= strMethod.find ( _T("::") );
				size_t	posSpace	= strMethod.find_first_of( _T(" ") );
				if ( string::npos != posDColon && string::npos != posSpace )
				{
					strClsName	= strMethod.substr ( posSpace+1, posDColon - ( posSpace+1 ) );
				}
				//strMthText	+= strMthLine;
/*#ifdef _DEBUG_APPEND 

				strMthText.Append ( strMthLine );
				strMthText.Append ( "\n" );
#endif*/			
				// 手动管理存储函数体的内存块
				size_t		iShift;
				size_t		dwBytes;

				iShift		= 0;
				pStr		= NULL;
				dwBytes		= strMthLine.length ( ) + 1;
				hMem		= ::GlobalAlloc ( GHND, dwBytes );				
				pStr		= (char*)::GlobalLock ( hMem );
				
				::strcpy ( pStr, strMthLine.c_str() );
				//::memcpy ( pStr, strMthLine, dwBytes );
				//pStr [dwBytes - 1] = '\n';
				//AfxMessageBox(pStr);
				iShift		= strMthLine.length ( ) + 1;
				//pStr		= pStr + iShift;
				
				::GlobalUnlock ( hMem );

				//::GlobalFree ( hMem );
				//strMthText	+= "\n"; 
				// 继续往后读
				//while ( pFile.ReadString (strMthLine) )
				while ( readString ( pFile, &strMthLine ) )
				{
					//omitComment ( &strMthLine );
					/*strMthLine.TrimLeft (" ");
					strMthLine.TrimRight (" ");*/
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
					//::memcpy ( pStr, strMthLine, sLen );
					//pStr [sLen]	= '\n';
					iShift		+= strMthLine.length ( ) + 1;
					//pStr		= pStr + iShift;
					//AfxMessageBox(pStr);
					
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
						//continue;
					}
					if ( 0 == nBrace )
					{
						/*int		iColon, iSpace;
						iColon	= strMethod.Find (("::"));
						iSpace	= strMethod.Find ((" "));
						if ( -1 != iColon )
						{
							string mthClass	= strMethod.Mid ( iSpace, iColon );
							AfxMessageBox (mthClass);
						}*/
						//strMethod	= strMthText.Left ( iLBracket );
						//
						hMem			= ::GlobalReAlloc ( hMem, iShift , GHND );
						char* pStrBody	= (char*)::GlobalLock ( hMem );
						//pStrBody [iShift-1]	= '\0';

						//AfxMessageBox (pStrBody);
#ifdef _DEBUG_APPEND 
						pFind			= new stMethod ( m_mIndex, strMethod, strMthText );
#endif
						pFind			= new stMethod ( m_mIndex, strMethod, pStrBody, (int) iShift );
						m_mIndex ++;
						// 将该函数与对应的类名存在map中，便于后续将函数添加到对应的类中
						if ( strClsName != "" )
						{
							CIT		cit		= m_pMthToClass.find ( strClsName );
							if ( cit != m_pMthToClass.end() )
							{
								pFind->mthNextOnClass		= m_pMthToClass[strClsName];
								m_pMthToClass[strClsName]	= pFind;
								/*pFind->mthNextOnClass	= pMthHeadOnCls;
								pMthHeadOnCls			= pFind;*/
							}
							else 
							{
								m_pMthToClass.insert ( pair< string, LPMETHOD >( strClsName, pFind ) );
								m_pMthToClass[strClsName]	= pFind;
							}
						}
						/*else
						{

						}*/
						
						pFind->mthpNext	= m_mpHead;
						m_mpHead		= pFind;
						/*m_pSimMethod->pNextByMth	= m_pSimMthHead;
						m_pSimMthHead				= m_pSimMethod;*/

						pStr	= NULL;
						//AfxMessageBox ( strMthText );
						//strMthText	= "";
						//AfxMessageBox ( strMethod );
						break;		// 跳出当前读取字符的循环
					}	
				} // end inside while
				continue;			// 从当前位置继续往下读
			} // end else
		} // end if
		// 如果第一次遇到的不是包含有括号的行，就继续往下读
		else
			continue;
	} // end outside while
	pFile.close ( );

	return pFind;







#else

	ifstream	pFile;
	string	 strMthLine;	 // 按行读取的内容
	string	 strMthText;	 // 存某一段函数定义主体
	string	 strMethod;
	LPMETHOD	pFind;
	size_t	 iLBracket;
	size_t	 iRBracket;
	size_t	 nBrace;	 // 记录花括号对

	string pStr;

	pFile.open ( fileName.c_str() );

	pFind	 = NULL;
	pStr	 = "";
	strMthLine	= "";
	strMthText	= "";
	nBrace	 = 0;

	//::memset( pStr, 0 );

	//while ( pFile.ReadString( strMthLine ) )
	while ( readString ( pFile, &strMthLine ) )
	{
		//omitComment ( &strMthLine );
		// 滤去空行
		if ( strMthLine == "" )
			continue;

		iLBracket	= strMthLine.find( ("(") );
		iRBracket	= strMthLine.find( (")") );
		// 首先查找括号对
		if ( -1 != iLBracket && -1 != iRBracket )
		{
			// 查找到控制语句关键字
			if ( findToken ( strMthLine ) )
			{
				continue;
			}
			// 可能是函数调用
			else if ( -1 != strMthLine.find((";")) )
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
				//strMthText	+= strMthLine;
				/*#ifdef _DEBUG_APPEND 

				strMthText.Append ( strMthLine );
				strMthText.Append ( "\n" );
				#endif*/	

				pStr.append ( strMthLine );
				pStr.append ("\n");

				//strMthText	+= "\n"; 
				// 继续往后读
				//while ( pFile.ReadString (strMthLine) )
				while ( readString ( pFile, &strMthLine ) )
				{
					//omitComment ( &strMthLine );
					/*strMthLine.TrimLeft (" ");
					strMthLine.TrimRight (" ");*/
					m_oString.lTrim ( strMthLine, " " );
					m_oString.rTrim ( strMthLine, " " );

					pStr.append ( strMthLine );
					pStr.append ("\n");

					#ifdef _DEBUG_APPEND 
					strMthText.Append(strMthLine);
					//strMthText.Append("\n");
					#endif
					//strMthText	+= strMthLine;
					//strMthText	+= "\n";
					if ( -1 != strMthLine.find(("{")) )
					{
						nBrace ++;
						continue;
					}
					if ( -1 != strMthLine.find(("}")) )
					{
						nBrace --;
						continue;
					}
					if ( 0 == nBrace )
					{
						/*int	 iColon, iSpace;
						iColon	= strMethod.Find (("::"));
						iSpace	= strMethod.Find ((" "));
						if ( -1 != iColon )
						{
							string mthClass	= strMethod.Mid ( iSpace, iColon );
							AfxMessageBox (mthClass);
						}*/
						//strMethod	= strMthText.Left ( iLBracket );
						//
						//char* pStrBody	= (char*)::GlobalLock ( hMem );
						//pStrBody [iShift-1]	= '\0';

						//AfxMessageBox (pStrBody);
						#ifdef _DEBUG_APPEND 
						pFind	 = new stMethod ( m_mIndex, strMethod, strMthText );
						#endif
						//pFind	 = new stMethod ( m_mIndex, strMethod, pStrBody, (int) iShift );
						char *methodBody = new char[pStr.size()+1];

                        //pStr = m_oString.rTrim(pStr,"\r");
                        /*
                        for(int i=0;i<pStr.size();i++)
                        {
                            if(pStr.at(i)=='\r')
                                pStr.erase(i,i+1);
                        }
                        */
						strcpy(methodBody,pStr.c_str());
                        //cout<<"methodbody:"<<endl;
                        //cout<<methodBody<<endl;
                        size_t bodyLen = strlen ( methodBody ); 
						for(int i=0;i<(int) bodyLen;i++)
						{
                            if(methodBody[i]=='\n')
                            {   
                                methodBody[i]='\0';
                                //cout<<"jia:"<<i<<endl;
                            }
                            else if(methodBody[i]=='\r')
                            {
                                //methodBody[i]='\n';
                                //cout<<"jiushini:"<<i<<endl;
                            }
							//methodBody[i] = methodBody[i]=='\n'?'\0':methodBody[i];
						}
                        //cout<<"22222:"<<endl;
                        //cout<<methodBody<<endl;
						pFind	 = new stMethod ( m_mIndex, strMethod, methodBody, (int) pStr.size() );
						//m_pSimMethod	= new CSimplex ( pFind );
						pFind->mthpNext	= m_mpHead;
						m_mpHead	 = pFind;
						/*m_pSimMethod->pNextByMth	= m_pSimMthHead;
						m_pSimMthHead	 = m_pSimMethod;*/

						pStr	= "";
						//AfxMessageBox ( strMthText );
						//strMthText	= "";
						//AfxMessageBox ( strMethod );
						break;	 // 跳出当前读取字符的循环
					}	
				} // end inside while
				continue;	 // 从当前位置继续往下读
			} // end else
		} // end if
		// 如果第一次遇到的不是包含有括号的行，就继续往下读
		else
			continue;
	} // end outside while
	pFile.close ( );
	return pFind;
#endif

}

// 该函数的作用是按行遍历文件，分析每一行是否为注释，为注释返回false，非注释返回true，即为有效行
// 要考虑到的一种特殊情况，函数内参数含有注释 void method ( /* int param */ )的情况
bool CTestFile::readString ( ifstream& pFile, string* strLine )
{
	size_t		flagCommom_1;
	size_t		flagCommom_2; 
	size_t		flagCommom_3;
	size_t		flag_pre;

	while ( /*!pFile.eof()*/getline ( pFile, *strLine ) )
	{
		/*char temp[100000];
		pFile.getline(temp,100000);
		*strLine = string(temp);*/
		flagCommom_1	= strLine->find(("//"));		
		flagCommom_2	= strLine->find(("/*"));	
		flag_pre		= strLine->find(("#"));
		// 判断行注释
		/*if ( string::npos != flagCommom_1 )
		{
			continue;
		}*/
		if ( string::npos != flagCommom_1 )
		{
			strLine->erase ( flagCommom_1 );
			return true;
		}
		// 判断段注释, 其中包括函数参数内含注释的特殊情况
		if ( string::npos != flagCommom_2 )
		{
			flagCommom_3	= strLine->find(("*/"));
			if ( string::npos != flagCommom_3 )
			{
				strLine->erase ( flagCommom_2, flagCommom_3 - flagCommom_2 + 2 );
				return true;
			}
			else
			{
				while ( getline ( pFile, *strLine ) )
				{
					flagCommom_3	= strLine->find(("*/"));
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
		// 若该行内容为空也继续读下行
		/*if ( strLine->IsEmpty() )
		{
			continue;
		}*/
		return true;
	}
	// 均不符合上述情况时，默认情况下返回false
	return false;
}

