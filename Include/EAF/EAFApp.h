#if !defined(AFX_EAFAPP_H__C8A0E941_6C55_4D2F_8BA8_4EDF03A2D99B__INCLUDED_)
#define AFX_EAFAPP_H__C8A0E941_6C55_4D2F_8BA8_4EDF03A2D99B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EAFApp.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFTypes.h>
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFDocTemplateRegistrar.h>
#include <EAF\EAFSplashScreen.h>
#include <comcat.h>

#include <UnitMgt\UnitMgt.h>


/////////////////////////////////////////////////////////////////////////////
// CEAFApp thread

class EAFCLASS CEAFApp : public CWinApp
{
	DECLARE_DYNAMIC(CEAFApp)
protected:
	CEAFApp();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
   virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

   CEAFDocTemplateRegistrar* GetDocTemplateRegistrar();
   CEAFPluginManager* GetPluginManager();

// Implementation
protected:
	virtual ~CEAFApp();

   virtual LPCTSTR GetRegistryKey() = 0;
   virtual OLECHAR* GetPluginCategoryName() = 0;
   virtual CATID GetPluginCategoryID() = 0;

   virtual CEAFSplashScreenInfo GetSplashScreenInfo() = 0;

   // calls IEAFAppPlugin::CreateDocTemplate for all
   // registered application plugins
   virtual void RegisterDocTemplates();

	// Generated message map functions
	//{{AFX_MSG(CEAFApp)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnFileNew();
   afx_msg void OnFileOpen();
	//}}AFX_MSG

   virtual void OnAbout();

public:
   eafTypes::UnitMode GetUnitsMode() const;
   void SetUnitsMode(eafTypes::UnitMode newVal);
   const unitmgtIndirectMeasure* GetDisplayUnits() const;

private:
   CEAFDocTemplateRegistrar* m_pDocTemplateRegistrar;

   // Display Units
   void InitDisplayUnits();
   void UpdateDisplayUnits();
   unitmgtLibrary m_UnitLibrary;
   const unitmgtIndirectMeasure* m_pDisplayUnits; // current setting
   eafTypes::UnitMode m_Units;

   CEAFPluginManager m_PluginManager;

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnAppAbout();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAFAPP_H__C8A0E941_6C55_4D2F_8BA8_4EDF03A2D99B__INCLUDED_)
