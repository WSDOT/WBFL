///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#pragma once

// EAFApp.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFTypes.h>
#include <EAF\EAFAppPluginManager.h>
#include <EAF\EAFPluginManager.h>
#include <EAF\EAFDocTemplateRegistrar.h>
#include <EAF\EAFPluginCommandManager.h>
#include <EAF\EAFSplashScreen.h>
#include <EAF\EAFCommandLineInfo.h>
#include <EAF\EAFPluginCommandManager.h>
#include <EAF\EAFMDISnapper.h>

#include <comcat.h>

#include <WBFLTools.h>

#include <Units\Units.h>

typedef void(*DocCallback)(CDocument* pDoc,void* pStuff); 

class iUnitModeListener
{
public:
   virtual void OnUnitsModeChanging() = 0;
   virtual void OnUnitsModeChanged(eafTypes::UnitMode newUnitMode) = 0;
};

#include <EAF\EAFComponentInfo.h>
using CEAFComponentInfoManager = CEAFPluginManagerBase<IEAFComponentInfo, CEAFApp>;


class CEAFHelpWindowThread;

/////////////////////////////////////////////////////////////////////////////
// CEAFApp class
// Basic EAF Application class based on MFC's doc/view architecture
class EAFCLASS CEAFApp : public CWinApp
{
	DECLARE_DYNAMIC(CEAFApp)
protected:
	CEAFApp();           // protected constructor used by dynamic creation

// Attributes
public:
   virtual CEAFCommandLineInfo& GetCommandLineInfo();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFApp)
	public:
	virtual int Run() override;
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;
	virtual LRESULT ProcessWndProcException(CException* e, const MSG* pMsg) override;
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) override;
   virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName) override;
   virtual void ReplaceDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

   virtual CDataRecoveryHandler *GetDataRecoveryHandler();

   CRecentFileList* GetRecentFileList();
   CEAFDocTemplateRegistrar* GetDocTemplateRegistrar();
   CEAFAppPluginManager* GetAppPluginManager();
   CEAFPluginCommandManager* GetPluginCommandManager();
   CEAFComponentInfoManager* GetComponentInfoManager();

   BOOL ReadWindowPlacement(const CString& strSection,const CString& strKey,LPWINDOWPLACEMENT pwp);
   void WriteWindowPlacement(const CString& strSection,const CString& strKey,LPWINDOWPLACEMENT pwp);

   // Registry helper functions
   UINT GetLocalMachineInt(LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault);
   CString GetLocalMachineString(LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault);

   AcceptanceType ShowLegalNoticeAtStartup(void);
   CString GetAppLocation();

   BOOL IsDocLoaded();

   void ForEachDoc(DocCallback pfn,void* pStuff);

   virtual void OnMainFrameClosing(); // called by the framework when the main frame window is about to close

   // Returns the name of the documentation set. This name is appended to
   // the URL returned by GetDocumentationRootLocation()
   // The default information returns AfxGetAppName();
   virtual CString GetDocumentationSetName();

   // Return the root location for application documentation
   // Can be in the form of a WEB URL (http://www.mysite.com/Documentation/")
   // or a file system URL (C:/Program Files/MyApp/Documentation/")
   // Include the last '/'
   // Documents may use this to build their documentation URLs
   virtual CString GetDocumentationRootLocation() = 0;

   // Return the URL for documentation for the application
   // Called by GetDocumentLocation to form the complete
   // documentation URL. The default documentation URL is:
   // For an Online source
   //     GetDocumentationRootLocation() + m_pszExeName + major.minor version number
   // For a local source
   //     GetDocumentationRootLocation() + m_pszExename
   virtual CString GetDocumentationURL();

   // Gets the full URL for the document associated with help id nHID
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL);

   // Toggles between online and local sources for documentation
   void UseOnlineDocumentation(BOOL bUseOnLine);

   // Returns true if an online source is being used for documentation
   BOOL UseOnlineDocumentation() const;

   void HelpWindowNavigate(LPCTSTR lpszURL);

// Implementation
protected:
	virtual ~CEAFApp();

   virtual CString GetProductCode() = 0;
   virtual CEAFSplashScreenInfo GetSplashScreenInfo() = 0;
   virtual LPCTSTR GetRegistryKey() = 0;
   virtual BOOL CreateApplicationPlugins() = 0;

   virtual CMDIFrameWnd* CreateMainFrame();

   virtual CDocManager* CreateDocumentManager();
   virtual CEAFDocTemplateRegistrar* CreateDocTemplateRegistrar();

   // Calls CreateDocPlugins and then completes the document template
   // registration process
   virtual BOOL RegisterDocTemplates();

   // Called by the framework when an app plugin integrates into the UI
   virtual BOOL AppPluginUIIntegration(BOOL bIntegrate);

   // called by the framework during InitInstance() when registry settings need to be read
   virtual void RegistryInit();

   // called by the framework during ExitInstance() when registry settings need to be saved
   virtual void RegistryExit();

   void EnableTipOfTheDay(LPCTSTR lpszTipFile);
   void EnableTipOfTheDay(const std::vector<CString>& vTipFiles);
   bool IsTipOfTheDayEnabled();
	virtual void ShowTipOfTheDay(void);

   virtual void OnFirstRun();

   virtual CATID GetComponentInfoCategoryID() = 0;

	// Generated message map functions
	//{{AFX_MSG(CEAFApp)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnAppLegal();
   afx_msg void OnHelpSource();
   afx_msg void OnUpdateHelpSource(CCmdUI* pCmdUI);
   afx_msg void OnHelpViewer();
   afx_msg void OnFileNew();
   afx_msg void OnFileOpen();
	afx_msg void OnEditUnits();
   afx_msg void OnSIUnits();
   afx_msg void OnUpdateSIUnits(CCmdUI* pCmdUI);
   afx_msg void OnUSUnits();
   afx_msg void OnUpdateUSUnits(CCmdUI* pCmdUI);
   afx_msg void OnAutoSave();
	//}}AFX_MSG
   afx_msg void OnReplaceFile();
   CString m_ReplacementFileName;

   virtual void OnAbout();

public:
   eafTypes::UnitMode GetUnitsMode() const;
   void SetUnitsMode(eafTypes::UnitMode newVal);
   const WBFL::Units::IndirectMeasure* GetDisplayUnits() const;

   void AddUnitModeListener(iUnitModeListener* pListener);
   void RemoveUnitModeListener(iUnitModeListener* pListener);

   WBFL::System::Date GetInstallDate();
   WBFL::System::Date GetLastRunDate();
   BOOL IsFirstRun();

   BOOL IsCommandLineMode() { return m_bCommandLineMode; }

   // Don't show UI. Must be in command line mode
   CEAFCommandLineInfo::CommandLineDisplayMode GetCommandLineMode() const; 

   virtual void EnableAutoSave(BOOL bEnable, int interval);
   BOOL IsAutoSaveEnabled();
   int GetAutoSaveInterval();
   virtual void GetAutoSaveInfo(BOOL* pbAutosave, int* pAutosaveInterval);
   virtual void SaveAutoSaveInfo(BOOL bAutosave, int AutosaveInterval);

   CEAFMDISnapper& GetMDIWndSnapper();

protected:
   // Called during InitInstance when command line parameters need to be handled
   virtual void ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo);

   // Called when the user starts the application with the /? or /help flags
   // Displays command line usage parameters
   virtual void ShowUsageMessage();

   // Called by the framework when the command line parameters are invalid
   // Display an informational message to the user before the application closes
   virtual void DisplayCommandLineErrorMessage();

protected:
   HKEY GetAppLocalMachineRegistryKey(REGSAM samDesired);
   HKEY GetUninstallRegistryKey();
   HKEY GetLocalMachineSectionKey(LPCTSTR lpszSection,REGSAM samDesired);
   HKEY GetLocalMachineSectionKey(HKEY hAppKey,LPCTSTR lpszSection,REGSAM samDesired);
   UINT GetLocalMachineInt(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,int nDefault);
   CString GetLocalMachineString(HKEY hAppKey,LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault);

   virtual CString GetDocumentationMapFile();
   virtual void LoadDocumentationMap();

   BOOL m_bUseHelpWindow; // went TRUE, the built-in EAF Help Browser Window is used to display help content, otherwise the help documents are opened with the default shell action.
   // this setting cannot be changed while the application is running. If you add a UI element to toggle this setting, the application must restart.
   // this is because I could never get the viewer thread to start properly after InitInstance was called.

private:
   CEAFDocTemplateRegistrar* m_pDocTemplateRegistrar;

   friend CEAFHelpWindowThread;
   CEAFHelpWindowThread* m_pHelpWindowThread;

   BOOL m_bUseOnlineDocumentation; // set to TRUE if documentation is from an online source
   CString m_strOnlineDocumentationMapFile;
   CString m_strDocumentationMapFile; // name of documentation map file
   std::map<UINT,CString> m_HelpTopics; // maps a help topic ID to the topic file name

   CString m_LastError;

   std::vector<CString> m_TipFiles;
   bool m_bTipsEnabled;

   BOOL m_bAutoSaveEnabled; // TRUE If AutoSave mode is enabled

   BOOL m_bCommandLineMode; // set to TRUE if the application is running in command line mode
   CEAFCommandLineInfo::CommandLineDisplayMode m_CommandLineDisplayMode;  // display mode if in command line mode

   WBFL::System::Date m_LastRunDate;

   // Manages legal notice at application start up
	AcceptanceType ShowLegalNotice(VARIANT_BOOL bGiveChoice = VARIANT_FALSE);
   VARIANT_BOOL m_bShowLegalNotice;

   // Display Units
   void InitDisplayUnits();
   void UpdateDisplayUnits();
   WBFL::Units::Library m_UnitLibrary;
   const WBFL::Units::IndirectMeasure* m_pDisplayUnits; // current setting
   eafTypes::UnitMode m_Units;
   std::set<iUnitModeListener*> m_UnitModeListeners;
   void Fire_UnitsChanging();
   void Fire_UnitsChanged();

   CEAFPluginCommandManager m_PluginCommandMgr;
   CEAFAppPluginManager m_AppPluginManager;
   CEAFComponentInfoManager m_ComponentInfoManager;

   CString m_strWindowPlacementFormat;

   CEAFCommandLineInfo* m_pCommandLineInfo;

   CEAFMDISnapper m_MDISnapper;

	DECLARE_MESSAGE_MAP()

public:
   afx_msg void OnAppAbout();
   virtual BOOL PreTranslateMessage(MSG* pMsg) override;
};

/////////////////////////////////////////////////////////////////////////////
// CEAFPluginApp class
// Extends the basic application type to include plug-in applications
class EAFCLASS CEAFPluginApp : public CEAFApp
{
	DECLARE_DYNAMIC(CEAFPluginApp)
public:
   BOOL InitInstance();

   // Category information for plug-in applications
   virtual LPCTSTR GetAppPluginCategoryName() = 0;
   virtual CATID GetAppPluginCategoryID() = 0;

   // Category information for plug-ins to the main application
   virtual LPCTSTR GetPluginCategoryName() = 0;
   virtual CATID GetPluginCategoryID() = 0;
   
   afx_msg void OnUpdateManageApplicationPlugins(CCmdUI* pCmdUI);
   afx_msg void OnManageApplicationPlugins();

	DECLARE_MESSAGE_MAP()

   CEAFPluginManager* GetPluginManager();

protected:

   CEAFPluginManager m_PluginManager;

   BOOL RegisterDocTemplates();
   BOOL AppPluginUIIntegration(BOOL bIntegrate);
   virtual BOOL CreateApplicationPlugins() override;
   virtual BOOL CreatePlugins();
   virtual void LoadDocumentationMap() override;
   virtual eafTypes::HelpResult GetDocumentLocation(LPCTSTR lpszDocSetName,UINT nHID,CString& strURL) override;
};
