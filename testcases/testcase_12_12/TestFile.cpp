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
	// �����ﴦ�������ڴ��ͷ�
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
 * ��ȡ��������򿪵��ļ��������Ը��ļ����ж�ȡ�������ҳ����е���
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
		// ��ÿ���ַ������н������ҳ�����class�ؼ��ֵĵط�������¼����class��ߵ�����
		// ����Ҫ�ĳ�switch��class int�ȹؼ�����Ϊ��֧����Ҫϸ��
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
		// ����������
		strPosition		= strLine.find( strKeyword );
		// �ҵ���class�ؼ��ֵĵط����ſ�ʼ����������������õ����壬���ں�����objects
		if ( string::npos != strPosition)
		{
			// �ඨ���к��ǲ����е�;�ģ�������У����п�����������������typedef������������ָ���Լ���ĳЩ����а����˴���class��Ϊ���������
			if ( string::npos != strLine.find(_T(";")) )
			{
				continue;
			}
			// �ų������ж�����к��д�class�ַ���Ϊ���������
			else if ( string::npos != strLine.find (_T("(")) || string::npos != strLine.find (_T(")")) )
			{
				continue;
			}
			else
			{
				//��ȡ�ؼ���class���������
				strNameClass			= strLine.substr ( strPosition+ keyword_size );
				// ���ǻ�����д���࿪ʼ�ĵ�һ�к�
				if ( string::npos != strLine.find ( _T("{") ) )
				{
					nBrace ++;
				}
				// �ֶ�����洢��������ڴ��
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
				// �������¶�ȡ
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
					// ���л����������������캯��������ʹ�õ��� {
					//if ( string::npos != strLine.find( _T("{") ) )
					{
						nBrace ++;
						continue;
					}
					// �����������캯��������ʹ�õ��ķ������� } 
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
						// ����һ��.h�л��ж���������������������Ҫ��ͬһ��.h�е��������
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
		// ��ȥ����
		if ( strMthLine == "" )
			continue;

		iLBracket	= strMthLine.find( ("(") );
		iRBracket	= strMthLine.find( (")") );
		// ���Ȳ������Ŷ�
		if ( string::npos != iLBracket && string::npos != iRBracket )
		{
			// ���ҵ��������ؼ���
			if ( findToken ( strMthLine ) )
			{
				continue;
			}
			// �����Ǻ�������
			else if ( string::npos != strMthLine.find((";")) )
			{
				continue;
			}
			//�������岿��
			else
			{
				//strMthLine.TrimLeft (" ");
				m_oString.lTrim ( strMthLine, " " );
				//strMthLine.TrimRight (" ");
				m_oString.rTrim ( strMthLine, " " );
				strMethod	= strMthLine.substr( 0, iLBracket );
				// ��ȡ�ú������ڵ����� ���ｫλ�ڵ�һ���ո�(������ֵ��Ŀո�)��::֮����ַ�����Ϊ����
				size_t	posDColon	= strMethod.find ( _T("::") );
				size_t	posSpace	= strMethod.find_first_of( _T(" ") );
				if ( string::npos != posDColon && string::npos != posSpace )
				{
					strClsName	= strMethod.substr ( posSpace+1, posDColon - ( posSpace+1 ) );
				}
				// �ֶ�����洢��������ڴ��
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
						// ���ú������Ӧ����������map�У����ں�����������ӵ���Ӧ������
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
		// �ж���ע��
		if ( string::npos != flagCommom_1 )
		{
			continue;
		}
		// �ж϶�ע��, ���а������������ں�ע�͵��������
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
		// �ж��Ƿ�ΪԤ�����У�����#include
		if ( string::npos != flag_pre )
		{
			continue;
		}
		return true;
	}
	// ���������������ʱ��Ĭ������·���false
	return false;
}

