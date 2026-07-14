
#pragma once
// DisplayObjectFactory.h : header file
//

class CTestDoc;

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory command target

class CDisplayObjectFactory : public CCmdTarget
{
public:
	CDisplayObjectFactory(CTestDoc* pDoc);

// Attributes
public:

// Operations
public:


// Implementation
protected:
	CDisplayObjectFactory();

	virtual ~CDisplayObjectFactory();

   DECLARE_INTERFACE_MAP()

   // iDisplayObjectFactory Implementation
   BEGIN_INTERFACE_PART(Factory,iDisplayObjectFactory)
      STDMETHOD_(void,Create)(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj);
   END_INTERFACE_PART(Factory)

private:
   CComPtr<iDisplayObjectFactory> m_Factory;
   CTestDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

