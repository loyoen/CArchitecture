#ifndef TESTFILE_H
#define	TESTFILE_H 

#include "Simplex.h"

class CTestFile
{
public:
	Cstringnew					m_oString;
	LPTESTFILE					m_pNextFile;
	string						m_strFileName;				// ��Ҫ�򿪵��ļ���

	int							m_cIndex;
	// �洢��ǰ�ļ��е�����class�����ں���ȫ��������
	vector < stClass* >			m_pVectorClass;
    // ��map���ڽ������洢�ڶ�Ӧ������				
	map < string, LPMETHOD >	m_pMthToClass;				

	int							m_mIndex;					// ��������
	// ÿһ���ļ��ĺ���ͷ
	LPMETHOD					m_mpHead;				

	typedef map < string, LPMETHOD >::const_iterator CIT;	// ������������ڲ���map����

	// Operations
public:
	CTestFile ( );
	~CTestFile ( );
	void		findClass ( string fileName );
	//��ÿһ���ı����з��������㺯���Ķ��岿�֣����Ϊ��Ա���������ز��ҵ��ĺ���
	LPMETHOD	findMethod ( string fileName );	
	bool		readString ( ifstream& pFile, string* strLine );
	//bool		findToken ( string str );
	void		outputClassToFile ( string fileName, LPCLASS pClass);

	// �˺����������ǣ��ڸ������ַ����в���ĳЩָ�����Ӵ���������չ��Ϊ�������������ٵ����ϵ�ʱ�俪��
	// �����ڲ�����ĺ���Ĭ��Ϊ�������������Բ�ָ��inline�ؼ���
	inline bool findToken ( string str )
	{
		if ( string::npos != str.find ( ("if") ) )
			return true;
		if ( string::npos != str.find ( ("while") ) )
			return true;
		if ( string::npos != str.find ( ("for") ) )
			return true;
		if ( string::npos != str.find ( ("switch") ) )
			return true;

		return false;
	}
};
#endif

