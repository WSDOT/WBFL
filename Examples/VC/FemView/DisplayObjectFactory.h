#ifndef INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_
#define INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayObjectFactory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory command target

class CDisplayObjectFactory : public CCmdTarget
{
public:
	CDisplayObjectFactory(CFEA2DDoc* pDoc);
   ~CDisplayObjectFactory();

   DECLARE_INTERFACE_MAP()

   // iDisplayObjectFactory Implementation
   BEGIN_INTERFACE_PART(Factory,iDisplayObjectFactory)
      STDMETHOD_(void,Create)(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj);
   END_INTERFACE_PART(Factory)

private:
   CComPtr<iDisplayObjectFactory> m_Factory;
   CFEA2DDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_
