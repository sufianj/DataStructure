// Tree30303View.h : interface of the CTree30303View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE30303VIEW_H__21C8B766_FF5F_49F7_B676_0D53E6E11BCB__INCLUDED_)
#define AFX_TREE30303VIEW_H__21C8B766_FF5F_49F7_B676_0D53E6E11BCB__INCLUDED_

#include "EmiTree.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTree30303View : public CView
{
protected: // create from serialization only
	CTree30303View();
	DECLARE_DYNCREATE(CTree30303View)

// Attributes
public:
	CTree30303Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree30303View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawTree(tnode *p, int x, int y, int dx, int dy);
	EmiTree T;
	virtual ~CTree30303View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	unsigned int m_lnCnt;//记录输出的行数
	//{{AFX_MSG(CTree30303View)
	afx_msg void OnShowTree();
	afx_msg void OnPotR();
	afx_msg void OnPotNr();
	afx_msg void OnIotR();
	afx_msg void OnIotNr();
	afx_msg void OnPostOTR();
	afx_msg void OnPostOTNR();
	afx_msg void OnLot();
	afx_msg void OnGetLeaveSum();
	afx_msg void OnIsComplete();
	afx_msg void OnProsperity();
	afx_msg void OnGetDepth();
	afx_msg void OnExchangeLandr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Tree30303View.cpp
inline CTree30303Doc* CTree30303View::GetDocument()
   { return (CTree30303Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE30303VIEW_H__21C8B766_FF5F_49F7_B676_0D53E6E11BCB__INCLUDED_)
