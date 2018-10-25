#if !defined(AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_)
#define AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EAFAppPlugin.h : header file
//

#include <EAF\EAFDocTemplate.h>

// {78D5872C-663A-4920-B1A1-E2E2528D5E3F}
DEFINE_GUID(IID_IEAFAppPlugin, 
0x78d5872c, 0x663a, 0x4920, 0xb1, 0xa1, 0xe2, 0xe2, 0x52, 0x8d, 0x5e, 0x3f);

interface IEAFAppPlugin : IUnknown
{
   virtual void Init() = 0;
   virtual void Terminate() = 0;
   virtual CEAFDocTemplate* CreateDocTemplate() = 0;
   virtual CCmdTarget* GetCommandTarget() = 0;
   virtual HMENU GetSharedMenuHandle() = 0;
   virtual UINT GetDocumentResourceID() = 0;

   ///
   /// About Dialog
   ///

   /// The text returned from this function goes in the About dialog
   virtual CString GetComponentName() = 0;

   /// The icon returned goes in the About dialog
   virtual HICON GetIcon() = 0;

   /// This function is called when the entry for this plugin
   /// is clicked in the about dialog. License information
   /// should be shown
   virtual void OnAbout() = 0;
};

#endif // !defined(AFX_EAFAPPPLUGIN_H__DC344A29_BA50_41C3_AAD4_DD3571113293__INCLUDED_)
