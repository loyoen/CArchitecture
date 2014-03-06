// CArchitectureDoc.cpp : implementation of the CArchitectureDoc class
//
/*
 * Project------ CArchitecture
 * Class Name--- CArchitectureDoc.cpp
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-3-30
 * Edition------ 1.0

 * Description-- MFC���ĵ�,һ��Doc��Ӧһ���򿪵�.h��.cpp�ļ���
 *		�������򿪵�Doc���н��������������а������࣬��������ṹ�У����ں�������simplex����

 * Change Log:
 *		Date----- 2013-4-13
 *		Staff---- 
 *		Edition-- 
 *		Content-- ��.h�ļ����з��������ҷ��Ϻ���ǩ���Ĳ��֣�����ȡ���������������ҳ�Ա�����Ĺ���

 * Change Log:
 *		Date----- 2013-4-17
 *		Staff---- 
 *		Edition-- 
 *		Content-- ���¶����˲��Һ����Ĺ��ܡ���.h��.cpp�ļ����з��������ҷ��Ϻ�������Ĳ��֣���ȡ������

 * Change Log:
 *		Date----- 2013-4-23
 *		Staff---- 
 *		Edition-- 
 *		Content-- �������Ҵ���ʹ��GlobalAlloc���䷽ʽ���ֶ���������Ĵ洢
*/

#include "stdafx.h"
#include "Architecture.h"

#include "ArchitectureDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArchitectureDoc

IMPLEMENT_DYNCREATE(CArchitectureDoc, CDocument)

BEGIN_MESSAGE_MAP(CArchitectureDoc, CDocument)
END_MESSAGE_MAP()


// CArchitectureDoc construction/destruction

CArchitectureDoc::CArchitectureDoc()
{
	/*strFile			= "";
	m_strText		= "";
	m_cIndex		= 1;
	m_pClass_doc	= NULL;

	m_mIndex		= 1;
	m_mpHead		= NULL;*/
}

CArchitectureDoc::~CArchitectureDoc()
{
	//�˴�Ҫ����stClass���ͷ�
	/*LPCLASS	pClass;
	pClass		= m_pClassHead;
	while ( pClass )
	{
		m_pClassHead	= pClass->cpNext;
		delete			pClass;
		pClass			= m_pClassHead;
	}*/
}

BOOL CArchitectureDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CArchitectureDoc serialization

void CArchitectureDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CArchitectureDoc diagnostics

#ifdef _DEBUG
void CArchitectureDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArchitectureDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CArchitectureDoc commands
/*
 * ��ȡ��������򿪵��ļ��������Ը��ļ����ж�ȡ�������ҳ����е���
*/
//void CArchitectureDoc::findClass ( string fileName )
//{
//	CStdioFile	file;
//	string		strLine;
//
//	strFile		= fileName;
//	file.Open ( strFile, CFile::modeRead );
//	strLine		= "";
//
//	while ( readString (&file, &strLine) )
//	{
//		// ��ÿ���ַ������н������ҳ�����class�ؼ��ֵĵط�������¼����class��ߵ�����
//		// ����Ҫ�ĳ�switch��class int�ȹؼ�����Ϊ��֧����Ҫϸ��
//		int		strPosition;
//		string strNameClass;
//		string strKeyword;
//		int		keyword_size;
//		strKeyword		= _T("class ") ;
//		keyword_size	= strKeyword.GetLength();
//		// ����������
//		strPosition		= strLine.Find( strKeyword );
//		if ( -1 != strPosition)
//		{
//			//��ȡ�ؼ���class���������
//			strNameClass	= strLine.Mid( strPosition+ keyword_size );
//			
//			m_pClass_doc		= new stClass ( m_cIndex, strNameClass, NULL, this );
//			// ����һ��.h�л��ж���������������������Ҫ��ͬһ��.h�е��������������Ʋ��Һ���������
//
//#ifdef	_DEBUG_OUTPUT
//			//outputClassToFile ("..//output//classes.txt", m_pClass_doc );
//#endif
//
//#ifdef	_DEBUG_AFXMESSAGE
//			AfxMessageBox (strNameClass);
//#endif
//		}
//		
//	}
//	file.Close();
//	findMethod (strFile);
//}

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

//LPMETHOD CArchitectureDoc::findMethod( string fileName )
//{
//	CStdioFile	pFile;
//	string		strMthLine;						// ���ж�ȡ������
//	string		strMthText;						// ��ĳһ�κ�����������
//	string		strMethod;
//	LPMETHOD	pFind;
//	int			iLBracket;
//	int			iRBracket;
//	int			nBrace;							// ��¼�����Ŷ�
//
//	HGLOBAL		hMem;
//	char*		pStr;
//
//	pFile.Open ( fileName, CFile::modeRead );
//
//	pFind		= NULL;
//	pStr		= NULL;
//	strMthLine	= "";
//	strMthText	= "";
//	nBrace		= 0;
//
//	//while ( pFile.ReadString( strMthLine ) )
//	while ( readString ( &pFile, &strMthLine ) )
//	{
//		//omitComment ( &strMthLine );
//		// ��ȥ����
//		if ( strMthLine == "" )
//			continue;
//
//		iLBracket	= strMthLine.Find( _T("(") );
//		iRBracket	= strMthLine.Find( _T(")") );
//		// ���Ȳ������Ŷ�
//		if ( -1 != iLBracket && -1 != iRBracket )
//		{
//			// ���ҵ��������ؼ���
//			if ( findToken ( strMthLine ) )
//			{
//				continue;
//			}
//			// �����Ǻ�������
//			else if ( -1 != strMthLine.Find(_T(";")) )
//			{
//				continue;
//			}
//			//�������岿��
//			else
//			{
//				strMthLine.TrimLeft (" ");
//				strMthLine.TrimRight (" ");
//				strMethod	= strMthLine.Left ( iLBracket );
//				//strMthText	+= strMthLine;
//#ifdef _DEBUG_APPEND 
//
//				strMthText.Append ( strMthLine );
//				strMthText.Append ( "\n" );
//#endif			
//				// �ֶ�����洢��������ڴ��
//				int			iShift;
//				int			dwBytes;
//
//				iShift		= 0;
//				pStr		= NULL;
//				dwBytes		= strMthLine.GetLength ( ) + 1;
//				hMem		= ::GlobalAlloc ( GHND, dwBytes );				
//				pStr		= (char*)::GlobalLock ( hMem );
//				::memcpy ( pStr, strMthLine.GetBuffer(), dwBytes );
//				//pStr [dwBytes - 1] = '\n';
//				//AfxMessageBox(pStr);
//				iShift		= strMthLine.GetLength() + 1;
//				//pStr		= pStr + iShift;
//				
//				::GlobalUnlock ( hMem );
//
//				//::GlobalFree ( hMem );
//				//strMthText	+= "\n"; 
//				// ���������
//				//while ( pFile.ReadString (strMthLine) )
//				while ( readString ( &pFile, &strMthLine ) )
//				{
//					//omitComment ( &strMthLine );
//					strMthLine.TrimLeft (" ");
//					strMthLine.TrimRight (" ");
//					int			dwBytes_new;
//					int			sLen;
//					dwBytes_new	= strMthLine.GetLength ( ) + iShift + 1;
//					sLen		= strMthLine.GetLength ( ) ;
//					hMem		= ::GlobalReAlloc ( hMem, dwBytes_new , GHND );
//					pStr		= (char*) ::GlobalLock ( hMem ); 
//					pStr		= pStr + iShift;
//					::memcpy ( pStr, strMthLine.GetBuffer(), sLen );
//					//pStr [sLen]	= '\n';
//					iShift		+= strMthLine.GetLength ( ) + 1;
//					//pStr		= pStr + iShift;
//					//AfxMessageBox(pStr);
//					
//					::GlobalUnlock ( hMem );
//#ifdef _DEBUG_APPEND 
//					strMthText.Append(strMthLine);
//					strMthText.Append("\n");
//#endif
//					//strMthText	+= strMthLine;
//					//strMthText	+= "\n";
//					if ( -1 != strMthLine.Find(_T("{")) )
//					{
//						nBrace ++;
//						continue;
//					}
//					if ( -1 != strMthLine.Find(_T("}")) )
//					{
//						nBrace --;
//						continue;
//					}
//					if ( 0 == nBrace )
//					{
//						/*int		iColon, iSpace;
//						iColon	= strMethod.Find (_T("::"));
//						iSpace	= strMethod.Find (_T(" "));
//						if ( -1 != iColon )
//						{
//							string mthClass	= strMethod.Mid ( iSpace, iColon );
//							AfxMessageBox (mthClass);
//						}*/
//						//strMethod	= strMthText.Left ( iLBracket );
//						//
//						hMem			= ::GlobalReAlloc ( hMem, iShift , GHND );
//						char* pStrBody	= (char*)::GlobalLock ( hMem );
//						//pStrBody [iShift-1]	= '\0';
//
//						//AfxMessageBox (pStrBody);
//#ifdef _DEBUG_APPEND 
//						pFind			= new stMethod ( m_mIndex, strMethod, strMthText );
//#endif
//						pFind			= new stMethod ( m_mIndex, strMethod, pStrBody, iShift );
//						//m_pSimMethod	= new CSimplex ( pFind );
//						pFind->mthpNext	= m_mpHead;
//						m_mpHead		= pFind;
//						/*m_pSimMethod->pNextByMth	= m_pSimMthHead;
//						m_pSimMthHead				= m_pSimMethod;*/
//
//						pStr	= NULL;
//						//AfxMessageBox ( strMthText );
//						//strMthText	= "";
//						//AfxMessageBox ( strMethod );
//						break;		// ������ǰ��ȡ�ַ���ѭ��
//					}	
//				} // end inside while
//				continue;			// �ӵ�ǰλ�ü������¶�
//			} // end else
//		} // end if
//		// �����һ�������Ĳ��ǰ��������ŵ��У��ͼ������¶�
//		else
//			continue;
//	} // end outside while
//	pFile.Close ( );
//	return pFind;
//
//}

// �ú����������ǰ��б����ļ�������ÿһ���Ƿ�Ϊע�ͣ�Ϊע�ͷ���false����ע�ͷ���true����Ϊ��Ч��
// Ҫ���ǵ���һ����������������ڲ�������ע�� void method ( /* int param */ )�����
//bool CArchitectureDoc::readString ( CStdioFile* pFile, string* strLine )
//{
//	int		flagCommom_1;
//	int		flagCommom_2; 
//	int		flagCommom_3;
//	int		flag_pre;
//
//	while ( pFile->ReadString ( *strLine ) )
//	{
//		flagCommom_1	= strLine->Find(_T("//"));		
//		flagCommom_2	= strLine->Find(_T("/*"));		
//		flag_pre		= strLine->Find(_T("#"));
//		// �ж���ע��
//		if ( -1 != flagCommom_1 )
//		{
//			continue;
//		}
//		// �ж϶�ע��, ���а������������ں�ע�͵��������
//		if ( -1 != flagCommom_2 )
//		{
//			flagCommom_3	= strLine->Find(_T("*/"));
//			if ( -1 != flagCommom_3 )
//			{
//				strLine->Delete ( flagCommom_2, flagCommom_3 - flagCommom_2 + 2 );
//				return true;
//			}
//			else
//			{
//				while ( pFile->ReadString ( *strLine ) )
//				{
//					flagCommom_3	= strLine->Find(_T("*/"));
//					if ( -1 != flagCommom_3 )
//					{
//						break;
//					}
//					continue;
//				}
//			
//			}
//			continue;
//		}
//		// �ж��Ƿ�ΪԤ�����У�����#include
//		if ( -1 != flag_pre )
//		{
//			continue;
//		}
//		// ����������Ϊ��Ҳ����������
//		/*if ( strLine->IsEmpty() )
//		{
//			continue;
//		}*/
//		return true;
//	}
//	// ���������������ʱ��Ĭ������·���false
//	return false;
//}
// �˺����������ǣ��ڸ������ַ����в���ĳЩָ�����Ӵ���������չ���ɸ�Ϊ������������������
//bool CArchitectureDoc::findToken ( string str )
//{
//	if ( -1 != str.Find ( _T("if") ) )
//		return true;
//	if ( -1 != str.Find ( _T("while") ) )
//		return true;
//	if ( -1 != str.Find ( _T("for") ) )
//		return true;
//	if ( -1 != str.Find ( _T("switch") ) )
//		return true;
//
//	return false;
//}

//void CArchitectureDoc::outputClassToFile ( string fileName, LPCLASS pClass )
//{
//	//char	cpClass [128];
//	char	cpstrClass [128];
//
//	ofstream	pfile;
//	pfile.open ( fileName.c_str(), ios::app );
//
//	if ( pClass )
//	{
//		/*sprintf_s ( cpClass, 128, "%d ", pClass->m_cIndex );
//		pfile.write ( cpClass, strlen (cpClass) );*/
//		//AfxMessageBox(_T("write")+pClass->className);
//		sprintf_s ( cpstrClass, 128, "%s ", pClass->className );
//		pfile.write ( cpstrClass, (int) strlen (cpstrClass) );
//		pfile.write ( "\n", 1 );
//	}
//	pfile.close();
//}