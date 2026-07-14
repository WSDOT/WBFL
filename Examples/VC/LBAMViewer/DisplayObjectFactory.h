
#pragma once
// DisplayObjectFactory.h : header file
//

class CLBAMViewerDoc;

/////////////////////////////////////////////////////////////////////////////
// CDisplayObjectFactory command target

class CDisplayObjectFactory : public WBFL::DManip::iDisplayObjectFactory
{
public:
   CDisplayObjectFactory() = delete;
   CDisplayObjectFactory(CLBAMViewerDoc* pDoc);
   virtual ~CDisplayObjectFactory();

// Attributes
public:

// Operations
public:


// Implementation
protected:

   // iDisplayObjectFactory Implementation
   std::shared_ptr<WBFL::DManip::iDisplayObject> Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject) const override;

private:
   std::shared_ptr<WBFL::DManip::iDisplayObjectFactory> m_Factory;
   CLBAMViewerDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

