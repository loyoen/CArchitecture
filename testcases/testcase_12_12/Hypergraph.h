/*
 * Project------ CArchitecture
 * Class Name--- Hypergraph.h
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-4-8
 * Edition------ 1.0

 * Description-- ��ͼ��ģ������CSimplex���еõ���classes�������ɶ��㡣��������ϵ�õ����ߡ���CSimplex���еõ��Ĺ�ϵ���ɱߣ����ݶ���ͳ��߽�����ͼ
 *		

 * Change Log:
 *		Date-----
 *		Staff----
 *		Edition--
 *		Content--
*/
#ifndef	HYPERGRAPH_H
#define	HYPERGRAPH_H

#include "Simplex.h"
#include <string.h>
struct stEdge
{
	LPVERTEX	pVertex;				// ĳ�����ϵ�
	LPSTEDGE	pNext;					// ��һ���ж������ı�

	stEdge ( LPCLASS pClass );
	~stEdge ( );
};

class CVertex
{
public:
	int			m_nvIndex;				// �������
	LPCLASS		m_pvHead;
    // �����������е����һָ��			 
	LPVERTEX	m_pvNext;
    // �����ϵ���һ������				
	LPVERTEX	pNext_on_edge;			

	int			m_vWeight;				// ����Ȩ�أ�Ĭ��Ϊ1
	//int			m_vTotal;				// �������

public:
	CVertex ( int vIndex, LPCLASS pClass );
	~CVertex ( );

	void outputVertexToFile ( string fileName, LPVERTEX pVertex );
};

class CEdge
{
public:
	int			m_neIndex;				// �ߵ�����
	int			m_ivCnt;				// һ�����ϵ�ļ���

    // ���ϵ������ͷָ��
	LPVERTEX	m_pvHead_on_edge;		
	LPVERTEX	m_pvTail_on_edge;

	// ��������ÿ���ߵ���һָ��
	LPEDGE		m_pENext;				

	int			m_eWeight;				// �ߵ�Ȩ�أ�Ĭ��Ϊ1
	//int			m_eTotal;				// ��������

public:
	CEdge ( int eIndex, LPVERTEX pVertex );
	~CEdge ( );

	void	addVertex ( LPVERTEX pVertex );
	void	outputEdgesToFile ( string fileName, LPEDGE pEdge );
};

class CHypergraph
{
public:
	LPVERTEX		m_pVertex;
	LPEDGE			m_pEdge;
	int				m_Index;
	int				m_iCnt_Ver;
	int				m_iCnt_Edge;

	LPHYPERGRAPH	m_pGraphNext;

public:
	CHypergraph ( int index, int iCnt_ver, int iCnt_edge, LPVERTEX pVer, LPEDGE pEdge );
	~CHypergraph ( )

	void	outputHypergraph ( string fileName, LPHYPERGRAPH pGraph );
};

#endif


