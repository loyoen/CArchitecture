// ArchitectureDoc.h : interface of the CArchitectureDoc class
//

#pragma once

#ifndef ARCHITECTURE_H
#define	ARCHITECTURE_H

#include "Simplex.h"

class CArchitectureDoc : public CDocument
{
//protected: // create from serialization only
public:
	CArchitectureDoc();
	DECLARE_DYNCREATE(CArchitectureDoc)

// Attributes
//public:
//	CArchitectureDoc	*m_pNextDoc;			// Doc����һָ�룬���ڽ����Doc�ĵ�������
//
//	string				strFile;				// ��Ҫ�򿪵��ļ���
//
//	string				m_strText;
//	int					m_cIndex;
//	LPCLASS				m_pClass_doc;			// ��ǰDoc�е���
//
//	int					m_mIndex;				// ��������
//	LPMETHOD			m_mpHead;				// ÿһ���ĵ��ĺ���ͷ
//
//// Operations
//public:
//	void		findClass ( string fileName );
//	//��ÿһ���ı����з��������㺯���Ķ��岿�֣����Ϊ��Ա���������ز��ҵ��ĺ���
//	LPMETHOD	findMethod ( string fileName );	
//	bool		readString ( CStdioFile* pFile, string* strLine );
//	bool		findToken ( string str );
//	void		outputClassToFile ( string fileName, LPCLASS pClass);
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CArchitectureDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#endif


