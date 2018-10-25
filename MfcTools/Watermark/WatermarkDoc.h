// WatermarkDoc.h : interface of the CWatermarkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATERMARKDOC_H__FD92433E_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
#define AFX_WATERMARKDOC_H__FD92433E_315B_11D2_8EB6_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CWatermarkDoc : public CDocument
{
protected: // create from serialization only
	CWatermarkDoc();
	DECLARE_DYNCREATE(CWatermarkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatermarkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWatermarkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWatermarkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERMARKDOC_H__FD92433E_315B_11D2_8EB6_006097DF3C68__INCLUDED_)
