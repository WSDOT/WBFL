// DimensionDoc.h : interface of the CDimensionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMENSIONDOC_H__2FC36C6C_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
#define AFX_DIMENSIONDOC_H__2FC36C6C_6F5A_11D2_9D88_00609710E6CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDimensionDoc : public CDocument
{
protected: // create from serialization only
	CDimensionDoc();
	DECLARE_DYNCREATE(CDimensionDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDimensionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDimensionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDimensionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMENSIONDOC_H__2FC36C6C_6F5A_11D2_9D88_00609710E6CE__INCLUDED_)
