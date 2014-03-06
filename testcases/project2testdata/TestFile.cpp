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
		// ����������
		strPosition_1	= strLine.find( strKeyword_1 );
		strPosition_2	= strLine.find( strKeyword_2 );
		// �ҵ���class��struct�ؼ��ֵĵط����ſ�ʼ����������������õ����壬���ں�����objects
		// ��class��structʱ��Ҫȷ�������Ƿ��ǹؼ��֣���ȷ�����������пո����tab��
		//if ( string::npos != strPosition_1 || string::npos != strPosition_2 )
		if ( string::npos != strPosition_1 )
		{
			// �ඨ���к��ǲ����е�;�ģ�������У����п�����������������typedef������������ָ���Լ���ĳЩ����а����˴���class��Ϊ���������
			if ( string::npos != strLine.find(";") )
			{
				// ������typedef��������ָ�����ͣ���ʵ������typedef�������ָ�뼴�ɶ�Ӧ����Ӧ����
				if ( string::npos != strLine.find ("typedef") )
				{
					// ����������ȡ���������Ӧ����ָ����
					// ��ʽ:typedef	class CTestFile		_CTESTFILE,		*LPTESTFILE;
					size_t			posColon;		// �ֺ�λ��
					size_t			posStar;		// *λ��
					size_t			posKeyClass;	// ��ؼ���class
					size_t			posKeyStruct;	// �ṹ��ؼ���struct
					size_t			posCName;		// ��������CTestFile
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
								// ��class��ʼ������һ�����ǿո����tab�����ַ�����Ϊ��������ʼλ��
								posCName	= pos;
								break;
							}
							// ������ͬ���ķ����ҵ���������ֹλ��
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
						//		// ��class��ʼ������һ�����ǿո����tab�����ַ�����Ϊ��������ʼλ��
						//		posCName	= pos;
						//		break;
						//	}
						//	// ������ͬ���ķ����ҵ���������ֹλ��
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
			// �ų������ж�����к��д�class�ַ���Ϊ���������
			else if ( string::npos != strLine.find ("(") || string::npos != strLine.find (")") )
			{
				continue;
			}
			else
			{
				if ( string::npos != strPosition_1 )
				{
					//��ȡ�ؼ���class���������
					size_t		posColon;				// ð�ŵ�λ�ã�Ϊ����ȡ�����̳����������
					posColon	= strLine.find ( ":" );
					if ( posColon != string::npos )
					{
						strNameClass	= strLine.substr ( strPosition_1 + keyword_size_1, posColon - strPosition_1 - keyword_size_1 );
					}
					else
						strNameClass	= strLine.substr ( strPosition_1+ keyword_size_1 );
					if ( strNameClass == "CVertex")
					{
						AfxMessageBox(_T("�������� ����"));
					}
				}
				//if ( string::npos != strPosition_2 )
				//{
				//	// ��ȡ�ؼ���struct����Ľṹ������Ҳ����
				//	strNameClass	= strLine.substr ( strPosition_2+ keyword_size_2 );
				//}
				
				// ���ǻ�����д���࿪ʼ�ĵ�һ�к�
				if ( string::npos != strLine.find ( "{" ) )
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
					if ( string::npos != strLine.find( "{" ) )
					{
						nBrace ++;
						continue;
					}
					// �����������캯��������ʹ�õ��ķ������� } 
					if ( string::npos != strLine.find ("}")  )
					{
						nBrace --;
						//continue;
					}
					// ���β
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
/*
 * ��ȡ��������򿪵��ļ��������Ը��ļ����ж�ȡ�������ҳ����еĺ���
 * �Һ�����˼·������"("")"���������ŶԵ������������������
 * 1.������� ( if, while, for, switch )
 * 2.��������ĺ�������
 * 3.������Ҫ�ҵĺ�������
 * ͨ���ų����д��벻��1������Ĺؼ��֣������ų����1��ͨ����������Ѱ�һ����Ŷ�{ }�����ų����2
 * ���ϣ����д������ if ( ���к������Ŷ� )��������������з��������������Ƿ��п������ؼ��֣�
 * if (���ؼ���)������������з������ҵ���������β�Ļ����Ŷԣ������ؼ��֣�����������з��������Ŷԣ�
 * ֱ����������Գɹ�����Ϊ��������
*/
LPMETHOD CTestFile::findMethod ( string fileName )
{
#ifdef WIN32	
	ifstream	pFile;
	string		strMthLine;						// ���ж�ȡ������
	string		strMthText;						// ��ĳһ�κ�����������
	string		strMethod;
	string		strClsName;
	LPMETHOD	pFind;
	size_t		iLBracket;
	size_t		iRBracket;
	size_t		nBrace;							// ��¼�����Ŷ�

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
		// ��ȥ����
		if ( strMthLine == "" )
			continue;
		m_oString.lTrim ( strMthLine, " " );
		m_oString.rTrim ( strMthLine, " " );
		iLBracket	= strMthLine.find("(");
		iRBracket	= strMthLine.find(")");
		
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
				strMethod	= strMthLine.substr( 0, iLBracket );
				
				// ��ȡ�ú������ڵ����� ���ｫλ�ڵ�һ���ո�(������ֵ��Ŀո�)��::֮����ַ�����Ϊ����
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
				// �ֶ�����洢��������ڴ��
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
				// ���������
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
						// ���ú������Ӧ����������map�У����ں�����������ӵ���Ӧ������
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
						break;		// ������ǰ��ȡ�ַ���ѭ��
					}	
				} // end inside while
				continue;			// �ӵ�ǰλ�ü������¶�
			} // end else
		} // end if
		// �����һ�������Ĳ��ǰ��������ŵ��У��ͼ������¶�
		else
			continue;
	} // end outside while
	pFile.close ( );

	return pFind;







#else

	ifstream	pFile;
	string	 strMthLine;	 // ���ж�ȡ������
	string	 strMthText;	 // ��ĳһ�κ�����������
	string	 strMethod;
	LPMETHOD	pFind;
	size_t	 iLBracket;
	size_t	 iRBracket;
	size_t	 nBrace;	 // ��¼�����Ŷ�

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
		// ��ȥ����
		if ( strMthLine == "" )
			continue;

		iLBracket	= strMthLine.find( ("(") );
		iRBracket	= strMthLine.find( (")") );
		// ���Ȳ������Ŷ�
		if ( -1 != iLBracket && -1 != iRBracket )
		{
			// ���ҵ��������ؼ���
			if ( findToken ( strMthLine ) )
			{
				continue;
			}
			// �����Ǻ�������
			else if ( -1 != strMthLine.find((";")) )
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
				//strMthText	+= strMthLine;
				/*#ifdef _DEBUG_APPEND 

				strMthText.Append ( strMthLine );
				strMthText.Append ( "\n" );
				#endif*/	

				pStr.append ( strMthLine );
				pStr.append ("\n");

				//strMthText	+= "\n"; 
				// ���������
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
						break;	 // ������ǰ��ȡ�ַ���ѭ��
					}	
				} // end inside while
				continue;	 // �ӵ�ǰλ�ü������¶�
			} // end else
		} // end if
		// �����һ�������Ĳ��ǰ��������ŵ��У��ͼ������¶�
		else
			continue;
	} // end outside while
	pFile.close ( );
	return pFind;
#endif

}

// �ú����������ǰ��б����ļ�������ÿһ���Ƿ�Ϊע�ͣ�Ϊע�ͷ���false����ע�ͷ���true����Ϊ��Ч��
// Ҫ���ǵ���һ����������������ڲ�������ע�� void method ( /* int param */ )�����
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
		// �ж���ע��
		/*if ( string::npos != flagCommom_1 )
		{
			continue;
		}*/
		if ( string::npos != flagCommom_1 )
		{
			strLine->erase ( flagCommom_1 );
			return true;
		}
		// �ж϶�ע��, ���а������������ں�ע�͵��������
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
		// �ж��Ƿ�ΪԤ�����У�����#include
		if ( string::npos != flag_pre )
		{
			continue;
		}
		// ����������Ϊ��Ҳ����������
		/*if ( strLine->IsEmpty() )
		{
			continue;
		}*/
		return true;
	}
	// ���������������ʱ��Ĭ������·���false
	return false;
}

