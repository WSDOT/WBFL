#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFMenu.h>
#include <EAF\EAFToolBar.h>
#include <WBFLCore.h> // IStructuredSave, IStructuredLoad, et. al.

class CEAFDocTemplate;
class CEAFMainFrame;
class CPluginCommandManager;

// CEAFDocument

class EAFCLASS CEAFDocument : public CDocument
{
	DECLARE_DYNAMIC(CEAFDocument)

public:
	CEAFDocument();
	virtual ~CEAFDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
   virtual void Serialize(CArchive& ar);
#endif

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFBrokerDocument)
	virtual BOOL OnNewDocument();
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
   virtual void OnCloseDocument();
   virtual BOOL OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo);

   virtual void SetModifiedFlag(BOOL bModified = TRUE);

	//}}AFX_VIRTUAL

   /// called when a document is created (New or Open)
   virtual BOOL Init(); 

   /// Use this method to log a message when
   /// the during application start-up
   /// Writes message to file named ("AppName.log")
   virtual void FailSafeLogMessage(const char* msg);

   CEAFMenu* GetMenu();
   
   /// Called to initialize menus. 
   virtual void InitMenus();

   /// Called to initialize tool bars. 
   virtual void InitToolBars();

   /// called by the framework to create the main menu object
   /// over-ride to create sub-classed types
   virtual CEAFMenu* CreateMainMenu();


   /// called by the framework where there is an initialization failure
   virtual void InitFailMessage();

   virtual BOOL OpenTheDocument(LPCTSTR lpszPathName);
   virtual BOOL SaveTheDocument(LPCTSTR lpszPathName);

   virtual void HandleOpenDocumentError( HRESULT hr, LPCTSTR lpszPathName );
   virtual void HandleSaveDocumentError( HRESULT hr, LPCTSTR lpszPathName );

   // Called by the framework when the document is to be loaded and saved
   virtual HRESULT SaveTheDocument(IStructuredSave* pStrSave) = 0;
   virtual HRESULT LoadTheDocument(IStructuredLoad* pStrLoad) = 0;


protected:
	DECLARE_MESSAGE_MAP()

   CEAFMenu* m_pMainMenu;
   CPluginCommandManager* m_pPluginCommandMgr;

   friend CEAFDocTemplate;
   friend CEAFMainFrame;
};


