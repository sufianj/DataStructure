// Tree30303Doc.h : interface of the CTree30303Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE30303DOC_H__A5334ADB_5AEF_4400_AB21_6B5419E563C9__INCLUDED_)
#define AFX_TREE30303DOC_H__A5334ADB_5AEF_4400_AB21_6B5419E563C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTree30303Doc : public CDocument
{
protected: // create from serialization only
	CTree30303Doc();
	DECLARE_DYNCREATE(CTree30303Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree30303Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTree30303Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTree30303Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE30303DOC_H__A5334ADB_5AEF_4400_AB21_6B5419E563C9__INCLUDED_)
