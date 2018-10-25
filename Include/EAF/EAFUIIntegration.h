#ifndef INCLUDED_EAFUIINTEGRATION_H_
#define INCLUDED_EAFUIINTEGRATION_H_
#pragma once

#include <EAF\EAFMenu.h>
#include <EAF\EAFToolBar.h>

// {2ED5504D-7D5B-4d39-BCE0-9F4A1DDCA481}
DEFINE_GUID(IID_IViewRegistrar, 
0x2ed5504d, 0x7d5b, 0x4d39, 0xbc, 0xe0, 0x9f, 0x4a, 0x1d, 0xdc, 0xa4, 0x81);
interface IViewRegistrar : IUnknown
{
   virtual long RegisterView(CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount = -1) = 0;
   virtual void RemoveView(long key) = 0;
   virtual CView* CreateView(long key) = 0;
};

// {FF33AA7F-3FA8-4f24-80F1-07F2A345D6D3}
DEFINE_GUID(IID_ICommandCallback, 
0xff33aa7f, 0x3fa8, 0x4f24, 0x80, 0xf1, 0x7, 0xf2, 0xa3, 0x45, 0xd6, 0xd3);

interface ICommandCallback : IUnknown
{
   virtual BOOL OnCommandMessage(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo) = 0;
   virtual void GetStatusBarMessageString(UINT nID, CString& rMessage) const = 0;
   virtual void GetToolTipMessageString(UINT nID, CString& rMessage) const = 0;
};

// {35A2295C-C062-4bfe-B86F-86A6333C2D7B}
DEFINE_GUID(IID_IMainMenu, 
0x35a2295c, 0xc062, 0x4bfe, 0xb8, 0x6f, 0x86, 0xa6, 0x33, 0x3c, 0x2d, 0x7b);

interface IMainMenu : IUnknown
{
   virtual CEAFMenu* GetMainMenu() = 0;
};

// {F8D84C5E-DEE9-4bfb-9C97-D4EEEAD610A6}
DEFINE_GUID(IID_IToolBars, 
0xf8d84c5e, 0xdee9, 0x4bfb, 0x9c, 0x97, 0xd4, 0xee, 0xea, 0xd6, 0x10, 0xa6);

interface IToolBars : IUnknown
{
   virtual CEAFToolBar* GetMainToolBar() = 0;
   virtual CEAFToolBar* CreateToolBar(LPCTSTR lpszName = NULL) = 0;
   virtual void DestroyToolBar(CEAFToolBar* pToolBar) = 0;
};

// {37322672-EFA0-4823-95AE-EFCDC8812450}
DEFINE_GUID(IID_IDocument, 
0x37322672, 0xefa0, 0x4823, 0x95, 0xae, 0xef, 0xcd, 0xc8, 0x81, 0x24, 0x50);

interface IDocument : IUnknown
{
   virtual BOOL IsModified() = 0;
   virtual void SetModified() = 0;

   // example: c:\my documents\myfile.txt
   virtual CString GetFileName() = 0; // returns myfile.txt
   virtual CString GetFileTitle() = 0; // returns myfile
   virtual CString GetFilePath() = 0; // returns c:\my documents\myfile.txt
   virtual CString GetFileRoot() = 0; // returns c:\my documents

   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = NULL) = 0;
};

#endif // INCLUDED_EAFUIINTEGRATION_H_