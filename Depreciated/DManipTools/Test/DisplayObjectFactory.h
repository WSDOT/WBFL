#if !defined(AFX_DISPLAYOBJECTFACTORY_H__D4D8B50C_0A5F_431C_8D9A_F6DBACB22A89__INCLUDED_)
#define AFX_DISPLAYOBJECTFACTORY_H__D4D8B50C_0A5F_431C_8D9A_F6DBACB22A89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
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

#endif // !defined(AFX_DISPLAYOBJECTFACTORY_H__D4D8B50C_0A5F_431C_8D9A_F6DBACB22A89__INCLUDED_)
