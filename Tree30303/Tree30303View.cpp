// Tree30303View.cpp : implementation of the CTree30303View class
//

#include "stdafx.h"
#include "Tree30303.h"

#include "Tree30303Doc.h"
#include "Tree30303View.h"

#include "EmiTree.h"
#include <CString>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree30303View

IMPLEMENT_DYNCREATE(CTree30303View, CView)

BEGIN_MESSAGE_MAP(CTree30303View, CView)
	//{{AFX_MSG_MAP(CTree30303View)
	ON_COMMAND(IDM_SHOW_TREE, OnShowTree)
	ON_COMMAND(IDM_POT_R, OnPotR)
	ON_COMMAND(IDM_POT_NR, OnPotNr)
	ON_COMMAND(IDM_IOT_R, OnIotR)
	ON_COMMAND(IDM_IOT_NR, OnIotNr)
	ON_COMMAND(IDM_PostOT_R, OnPostOTR)
	ON_COMMAND(IDM_PostOT_NR, OnPostOTNR)
	ON_COMMAND(IDM_LOT, OnLot)
	ON_COMMAND(IDM_GET_LEAVE_SUM, OnGetLeaveSum)
	ON_COMMAND(IDM_IS_COMPLETE, OnIsComplete)
	ON_COMMAND(IDM_PROSPERITY, OnProsperity)
	ON_COMMAND(IDM_GET_DEPTH, OnGetDepth)
	ON_COMMAND(IDM_EXCHANGE_LANDR, OnExchangeLandr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CString g_strOutput;//辅助输出
bool AddToOutput(tnode *p);
/////////////////////////////////////////////////////////////////////////////
// CTree30303View construction/destruction
CTree30303View::CTree30303View()
{
	// TODO: add construction code here
	m_lnCnt = 0;
}

CTree30303View::~CTree30303View()
{
}

BOOL CTree30303View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTree30303View drawing

void CTree30303View::OnDraw(CDC* pDC)
{
	CTree30303Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_lnCnt = 0;
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTree30303View printing

BOOL CTree30303View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTree30303View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTree30303View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTree30303View diagnostics

#ifdef _DEBUG
void CTree30303View::AssertValid() const
{
	CView::AssertValid();
}

void CTree30303View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTree30303Doc* CTree30303View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTree30303Doc)));
	return (CTree30303Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree30303View message handlers

void CTree30303View::OnShowTree() 
{
	// TODO: Add your command handler code here
	CString str;
	CClientDC dc(this);
	CPoint pt;
	pt.x = 500;
	pt.y = 10;
	int dx = 500, dy = 400;
	dc.MoveTo(pt);
	str.Format("%c", T.root->data);
	dc.TextOut(pt.x, pt.y, str);
	if (T.root->lp)
	{
		dc.LineTo(pt.x - dx / 2, pt.y + dy / 2);
		DrawTree(T.root->lp , pt.x - dx/2, pt.y + dy/2, dx/2, dy/2);
	}
	if (T.root->rp)
	{
		dc.MoveTo(pt);
		dc.LineTo(pt.x + dx / 2, pt.y + dy / 2);
		DrawTree(T.root->rp , pt.x + dx/2, pt.y + dy/2, dx/2, dy/2);
	}
}


void CTree30303View::DrawTree(tnode *p, int x, int y, int dx, int dy)
{	
	CString str;
	CClientDC dc(this);
	dc.MoveTo(x, y);
	str.Format("%c", p->data);
	dc.TextOut(x, y , str);
	if (p->lp)
	{
		dc.LineTo(x - dx/2, y + dy/2);
		DrawTree(p->lp, x - dx/2, y + dy/2, dx/2, dy/2);
	}
	if (p->rp)
	{
		dc.MoveTo(x, y);
		dc.LineTo(x + dx/2, y + dy/2);
		DrawTree(p->rp, x + dx/2, y + dy/2, dx/2, dy/2);
	}
}

void CTree30303View::OnPotR() 
{
	CClientDC dc(this);
	g_strOutput.Format("PreOrderTraverse (recursion): ");
	T.PreOrderTraverse(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

bool AddToOutput(tnode *p)
{
	g_strOutput += p->data;
	return true;
}

void CTree30303View::OnPotNr() 
{
	CClientDC dc(this);
	g_strOutput.Format("PreOrderTraverse (non-recursion): ");
	T.PreOrderTraverse1(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnIotR() 
{
	CClientDC dc(this);
	g_strOutput.Format("InOrderTraverse (recursion): ");
	T.InOrderTraverse(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnIotNr() 
{
	CClientDC dc(this);
	g_strOutput.Format("InOrderTraverse (non-recursion): ");
	T.InOrderTraverse63(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnPostOTR() 
{
	CClientDC dc(this);
	g_strOutput.Format("PostOrderTraverse (recursion): ");
	T.PostOrderTraverse(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnPostOTNR() 
{
	CClientDC dc(this);
	g_strOutput.Format("PostOrderTraverse (non-recursion): ");
	T.PostOrderTraverse1(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnLot() 
{
	CClientDC dc(this);
	g_strOutput.Format("LevelOrderTraverse: ");
	T.LevelOrderTraverse(T.root, AddToOutput);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

//DEL void CTree30303View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	m_lnCnt = 0;
//DEL 	
//DEL }

void CTree30303View::OnGetLeaveSum() 
{
	CClientDC dc(this);
	g_strOutput.Format("the sum of leaves is %d",T.GetLeaveSum(T.root));
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}


void CTree30303View::OnIsComplete() 
{
	CClientDC dc(this);
	if (T.IsComplete(T.root))
		g_strOutput.Format("Yeah, ur tree is absolutely complete~");
	else
		g_strOutput.Format("oh, no, ur tree is not complete.");
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);
}

void CTree30303View::OnProsperity() 
{
	CClientDC dc(this);
	int n;
	T.Prosperity(T.root, n);
	g_strOutput.Format("the prosperity of ur tree comes %d .", n);
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);	
}

void CTree30303View::OnGetDepth() 
{
	CClientDC dc(this);
	g_strOutput.Format("the depth of ur tree comes %d .",	T.Depth(T.root));
	m_lnCnt += 20;
	dc.TextOut(10, m_lnCnt, g_strOutput);	
}

void CTree30303View::OnExchangeLandr() 
{
//	CRect rect;
	CRect rc;
	CClientDC dc(this);
//	MessageBox("please adjust you window to another size then click 'showTree'");
//	this->Invalidate(true);//终于找到啦~
//	this->ValidateRect(null);
	GetClientRect(&rc);
	dc.FillSolidRect(&rc,RGB( 255, 255, 255));
	T.ExchangeLnR(T.root);
//	OnShowTree();
	//AfxMessageBox("ok");
//	MessageBox("确定交换左右子树?","提示",MB_OKCANCEL);	
	CPoint pt;
	CString str;
	pt.x = 500;
	pt.y = 10;
	int dx = 500, dy = 400;
	dc.MoveTo(pt);
	str.Format("%c", T.root->data);
	dc.TextOut(pt.x, pt.y, str);
	if (T.root->lp)
	{
		dc.LineTo(pt.x - dx / 2, pt.y + dy / 2);
		DrawTree(T.root->lp , pt.x - dx/2, pt.y + dy/2, dx/2, dy/2);
	}
	if (T.root->rp)
	{
		dc.MoveTo(pt);
		dc.LineTo(pt.x + dx / 2, pt.y + dy / 2);
		DrawTree(T.root->rp , pt.x + dx/2, pt.y + dy/2, dx/2, dy/2);
	}

}
