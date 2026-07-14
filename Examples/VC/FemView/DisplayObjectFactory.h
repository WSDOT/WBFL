
#pragma once
// DisplayObjectFactory.h : header file
//

using namespace WBFL::DManip;

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory command target

class CDisplayObjectFactory : public iDisplayObjectFactory
{
public:
	CDisplayObjectFactory(CFEA2DDoc* pDoc);
   ~CDisplayObjectFactory();

   virtual std::shared_ptr<iDisplayObject> Create(CLIPFORMAT cfFormat, COleDataObject* pDataObject) const;

private:
   CFEA2DDoc* m_pDoc;
   std::shared_ptr<DisplayObjectFactory> m_Factory;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

