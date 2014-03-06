#include "Simplex.h"

class CVertex
{
public:
	int			m_nvIndex;				// �������
	LPCLASS		m_pvHead;
	LPVERTEX	m_pvNext;				// �����������е����һָ��
	CVertex		*m_pvNext;
	LPVERTEX	pNext_on_edge;			// �����ϵ���һ������
	CVertex		*pNext_on_edge;

	int			m_vWeight;				// ����Ȩ�أ�Ĭ��Ϊ1

public:
	CVertex ( int vIndex, LPCLASS pClass );
	~CVertex ( );

	void outputVertexToFile ( string fileName, LPVERTEX pVertex );
};

class CEdge
{
public:
	int			m_neIndex;				// �ߵ�����
	int			m_ivCnt;
    LPVERTEX	m_pvHead_on_edge;		// ���ϵ������ͷָ��
	LPVERTEX	m_pvTail_on_edge;		// βָ��
	LPEDGE		m_pENext;				// ��������ÿ���ߵ���һָ��
	int			m_eWeight;				// �ߵ�Ȩ�أ�Ĭ��Ϊ1

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
    { 
    }

	void	outputHypergraph ( string fileName, LPHYPERGRAPH pGraph );
};

