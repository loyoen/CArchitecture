// MainFrm.cpp : implementation of the CMainFrame class
//
/*
 * Project------ CArchitecture
 * Class Name--- MainFrm.cpp
 * Author------- wxf891201@gmail.com
 * Date--------- 2013-4-8
 * Edition------ 1.0

 * Description-- �Զ���ĵ����з���, �õ�simplex��ÿ������ϵ��Ӧһ��CSimplex���� 

 * Change Log:
 *		Date----- 2013-4-18
 *		Content-- �Զ���ĵ����������ڴ��ȡ��Ϊֱ��Cstdio��ȡ����ȡ����Ķ����������ں������������������Ƿ���ָ������

 * Change Log:
 *		Date----- 2013-5-5
 *		Content-- �޸��˺����������ֵ�˼·���õ������䱻���ù�ϵ����ĳ������ĳ��������������Щ���е���Щ�������ù������ֱ����ù�ϵ��Ϊ����ϵ�����ݣ�����Ϊ�������ߵ�����

 * Change Log:
 *		Date----- 2013-5-6
 *		Content-- ��ʼʵ�ֳ�ͼ��ģ���ֱ�����õ����㼰����ϵ�õ�����
*/

#include "stdafx.h"
#include "Architecture.h"

#include "MainFrm.h"

#include "Hypergraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
	//LPCLASS	pClass;
	//pClass		= m_pHeadCl;
	//while ( pClass )
	//{
	//	m_pHeadCl	= pClass->cpNext;
	//	delete	pClass;
	//	pClass	= m_pHeadCl;
	//}

	//LPSIMPLEX	pSimplex;
	//pSimplex	= m_psimHead;
	//while ( pSimplex )
	//{
	//	m_psimHead	= pSimplex->pNext;
	//	delete	pSimplex;
	//	pSimplex	= m_psimHead;
	//}

	//LPRELATION	pRelation;
	//pRelation	= m_pReHead;
	//while ( pRelation )
	//{
	//	m_pReHead	= pRelation->pNextRelation;
	//	delete	pRelation->pCls;
	//	//����һ��, relation��new������class Ҫ�ͷ�
	//	delete	pRelation;
	//	pRelation	= m_pReHead;
	//}
	//
	// ������Ҫ��������ϵ�����ڴ��ͷ�
	/*LPMETHOD	pMethodDoc;
	LPMETHOD	pMethod;
	LPMETHOD	pMethodIvk;

	pMethodDoc	= m_pHeadMth;
	while ( pMethodDoc )
	{
		pMethod	= pMethodDoc;
		while ( pMethod )
		{
			pMethodIvk	= pMethod;
			while ( pMethodIvk )
			{
				m_pHeadMth	= pMethodIvk->mthNextOnIvk;
				delete		pMethodIvk;
				pMethodIvk	= m_pHeadMth;
			}
			m_pHeadMth	= pMethod->mthpNext;
			delete		pMethod;
			pMethod		= m_pHeadMth;
		}
		m_pHeadMth	= pMethodDoc->mthNextOnDoc;
		delete		pMethodDoc;
		pMethodDoc	= m_pHeadMth;
	}*/

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG
