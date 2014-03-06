#include "Simplex.h"

class CVertex
{
public:
	int			m_nvIndex;				// 点的索引
	LPCLASS		m_pvHead;
	LPVERTEX	m_pvNext;				// 用于连接所有点的下一指针
	CVertex		*m_pvNext;
	LPVERTEX	pNext_on_edge;			// 超边上的下一个顶点
	CVertex		*pNext_on_edge;

	int			m_vWeight;				// 顶点权重，默认为1

public:
	CVertex ( int vIndex, LPCLASS pClass );
	~CVertex ( );

	void outputVertexToFile ( string fileName, LPVERTEX pVertex );
};

class CEdge
{
public:
	int			m_neIndex;				// 边的索引
	int			m_ivCnt;
    LPVERTEX	m_pvHead_on_edge;		// 边上点的链表头指针
	LPVERTEX	m_pvTail_on_edge;		// 尾指针
	LPEDGE		m_pENext;				// 用于链接每条边的下一指针
	int			m_eWeight;				// 边的权重，默认为1

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

