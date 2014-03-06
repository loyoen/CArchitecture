#ifndef TESTFILE_H
#define	TESTFILE_H 

#include "Simplex.h"

class CTestFile
{
public:
	Cstringnew					m_oString;
	LPTESTFILE					m_pNextFile;
	string						m_strFileName;				// 所要打开的文件名

	int							m_cIndex;
	// 存储当前文件中的所有class，便于后续全部连起来
	vector < stClass* >			m_pVectorClass;
    // 该map用于将函数存储于对应的类中				
	map < string, LPMETHOD >	m_pMthToClass;				

	int							m_mIndex;					// 函数索引
	// 每一个文件的函数头
	LPMETHOD					m_mpHead;				

	typedef map < string, LPMETHOD >::const_iterator CIT;	// 定义迭代器便于查找map内容

	// Operations
public:
	CTestFile ( );
	~CTestFile ( );
	void		findClass ( string fileName );
	//对每一行文本进行分析，满足函数的定义部分，则归为成员函数，返回查找到的函数
	LPMETHOD	findMethod ( string fileName );	
	bool		readString ( ifstream& pFile, string* strLine );
	//bool		findToken ( string str );
	void		outputClassToFile ( string fileName, LPCLASS pClass);

	// 此函数的作用是：在给定的字符串中查找某些指定的子串，便于扩展。为内联函数，减少调用上的时间开销
	// 在类内部定义的函数默认为内联函数，可以不指定inline关键字
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

