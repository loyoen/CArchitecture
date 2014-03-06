#include "Hypergraph.h"
CVertex::CVertex ( int vIndex, LPCLASS pClass )
{
	m_nvIndex		= vIndex;
	m_pvHead		= pClass;
	m_pvNext		= NULL;
	pNext_on_edge	= NULL;
	m_vWeight		= 1;
	//m_vTotal		= 0;
}

CVertex::~CVertex ()
{

}

void CVertex::outputVertexToFile ( string fileName, LPVERTEX pVertex )
{
	// ��ģʱ��ÿһ������Ϊ����vertex����������CVertex���CClass���������
	m_pvHead->outputClasses ( fileName );
}

CEdge::CEdge ( int eIndex, LPVERTEX pVertex )
{
	m_neIndex			= eIndex;
	m_pENext			= NULL;

	m_pvHead_on_edge	= pVertex;
	m_pvTail_on_edge	= m_pvHead_on_edge;

	m_eWeight			= 1;
	m_ivCnt				= 1;
}

CEdge::~CEdge ( )
{
	
}

void CEdge::addVertex ( LPVERTEX pVertex )
{
	if ( pVertex )
	{
		m_pvTail_on_edge->pNext_on_edge		= pVertex;
		m_pvTail_on_edge					= pVertex;
		m_ivCnt ++;
	}
}

void CEdge::outputEdgesToFile ( string fileName, LPEDGE pEdge )
{
	// ���㹹�ɱߣ�����CEdge����CVertex���й�ϵ
	m_pvHead_on_edge->outputVertexToFile ( fileName, m_pvHead_on_edge );
}

CHypergraph::CHypergraph (  int index, int iCnt_ver, int iCnt_edge, LPVERTEX pVer, LPEDGE pEdge )
{
	m_Index			= index;
	m_iCnt_Ver		= iCnt_ver;
	m_iCnt_Edge		= iCnt_edge;
	m_pVertex		= pVer;
	m_pEdge			= pEdge;
	m_pGraphNext	= NULL;
}

void CHypergraph::outputHypergraph ( string fileName, LPHYPERGRAPH pGraph )
{
	// CHypergraph�����CVertex��CEdge���к���
	m_pVertex->outputVertexToFile ( fileName, m_pVertex );
	m_pEdge->outputEdgesToFile ( fileName, m_pEdge );
}

