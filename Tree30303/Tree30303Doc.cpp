// Tree30303Doc.cpp : implementation of the CTree30303Doc class
//

#include "stdafx.h"
#include "Tree30303.h"

#include "Tree30303Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree30303Doc

IMPLEMENT_DYNCREATE(CTree30303Doc, CDocument)

BEGIN_MESSAGE_MAP(CTree30303Doc, CDocument)
	//{{AFX_MSG_MAP(CTree30303Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree30303Doc construction/destruction

CTree30303Doc::CTree30303Doc()
{
	// TODO: add one-time construction code here

}

CTree30303Doc::~CTree30303Doc()
{
}

BOOL CTree30303Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTree30303Doc serialization

void CTree30303Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTree30303Doc diagnostics

#ifdef _DEBUG
void CTree30303Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTree30303Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree30303Doc commands
