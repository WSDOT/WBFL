///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <EAF\EAFMenu.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFCommandLineInfo.h>

// The interfaces defined in this file are used by plug-ins that are integrating themselves into
// the user interface of an EAFApp/EAFBrokerDocument based application

////////////////////////////////////////////////////////////
// IEAFViewRegistrar
//
// Use this interface to register and create views

// {2ED5504D-7D5B-4d39-BCE0-9F4A1DDCA481}
DEFINE_GUID(IID_IEAFViewRegistrar, 
0x2ed5504d, 0x7d5b, 0x4d39, 0xbc, 0xe0, 0x9f, 0x4a, 0x1d, 0xdc, 0xa4, 0x81);
interface IEAFViewRegistrar : IUnknown
{
   // Registers a view class and its associated frame class. Returns the view key
   virtual long RegisterView(UINT nResourceID,IEAFCommandCallback* pCallback,CRuntimeClass* pFrameClass,CRuntimeClass* pViewClass,HMENU hSharedMenu=NULL,int maxViewCount = -1) = 0;

   // Removes a previously registered view
   virtual void RemoveView(long key) = 0;

   // Creates a view. pData is a pointer to user defined view creation data. During view creation
   // the view class can get access to the creation data from the active document template
   virtual CView* CreateView(long key,LPVOID pData=0) = 0;
};

///////////////////////////////////////////////////////////////
// IEAFCommandCallback
//
// Plug-in objects that provide commands on the menus or toolbars must
// implement this interface to receive command notifications

// {FF33AA7F-3FA8-4f24-80F1-07F2A345D6D3}
DEFINE_GUID(IID_IEAFCommandCallback, 
0xff33aa7f, 0x3fa8, 0x4f24, 0x80, 0xf1, 0x7, 0xf2, 0xa3, 0x45, 0xd6, 0xd3);

interface IEAFCommandCallback : IUnknown
{
   // Called by the framework when a command is selected. Pass the parameters into a CCmdTarget object
   // OnCmdMsg function
   virtual BOOL OnCommandMessage(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo) = 0;

   // Called by the framework to get the status bar message when the user slides the mouse over a menu item
   virtual BOOL GetStatusBarMessageString(UINT nID, CString& rMessage) const = 0;

   // Called by the framework to get the toolbar tip
   virtual BOOL GetToolTipMessageString(UINT nID, CString& rMessage) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// IEAFMainMenu
//
// Use this interface to get access to the main menu object

// {35A2295C-C062-4bfe-B86F-86A6333C2D7B}
DEFINE_GUID(IID_IEAFMainMenu, 
0x35a2295c, 0xc062, 0x4bfe, 0xb8, 0x6f, 0x86, 0xa6, 0x33, 0x3c, 0x2d, 0x7b);

interface IEAFMainMenu : IUnknown
{
   // returns the applications main menu
   virtual CEAFMenu* GetMainMenu() = 0;
   virtual CEAFMenu* CreateContextMenu() = 0;
};

//////////////////////////////////////////////////////////////////////////
// IEAFToolbars
//
// Use this interface to create toolbars

// {F8D84C5E-DEE9-4bfb-9C97-D4EEEAD610A6}
DEFINE_GUID(IID_IEAFToolbars, 
0xf8d84c5e, 0xdee9, 0x4bfb, 0x9c, 0x97, 0xd4, 0xee, 0xea, 0xd6, 0x10, 0xa6);

interface IEAFToolbars : IUnknown
{
   // Creates a new, empty toolbar. Returns the Toolbar ID
   virtual UINT CreateToolBar(LPCTSTR lpszName) = 0;

   // Returns a previously created toolbar
   virtual CEAFToolBar* GetToolBar(UINT toolbarID) = 0;

   // Destroys a toolbar
   virtual void DestroyToolBar(CEAFToolBar* pToolBar) = 0;

   // Destroys a toolbar by ID
   virtual void DestroyToolBar(UINT toolbarID) = 0;
};

//////////////////////////////////////////////////////////////////////////
// IEAFAcceleratorTable
//
// Use this interface to manage accelerator table entries

// {2D663F88-1B17-4d1b-9DE8-8CD06050E2C2}
DEFINE_GUID(IID_IEAFAcceleratorTable, 
0x2d663f88, 0x1b17, 0x4d1b, 0x9d, 0xe8, 0x8c, 0xd0, 0x60, 0x50, 0xe2, 0xc2);
interface IEAFAcceleratorTable : IUnknown
{
   // Adds an accelerator table
   virtual BOOL AddAccelTable(HACCEL hAccel,IEAFCommandCallback* pCallback) = 0;

   // Adds an accelerator key
   virtual BOOL AddAccelKey(BYTE fVirt,WORD key,WORD cmd,IEAFCommandCallback* pCallback) = 0;

   // Removes an accelerator key by command
   virtual BOOL RemoveAccelKey(WORD cmd,IEAFCommandCallback* pCallback) = 0;

   // Removes an accelerator key by key combination
   virtual BOOL RemoveAccelKey(BYTE fVirt,WORD key) = 0;
};

//////////////////////////////////////////////////////////////////////////
// IEAFDocument
//
// Use this interface to get information about the document

// {37322672-EFA0-4823-95AE-EFCDC8812450}
DEFINE_GUID(IID_IEAFDocument, 
0x37322672, 0xefa0, 0x4823, 0x95, 0xae, 0xef, 0xcd, 0xc8, 0x81, 0x24, 0x50);

interface IEAFDocument : IUnknown
{
   // Returns TRUE if the document is modified
   virtual BOOL IsModified() = 0;

   // Set the modified state of the document
   virtual void SetModified(BOOL bModified = TRUE) = 0;

   // example: c:\my documents\myfile.txt
   virtual CString GetFileName() = 0; // returns myfile.txt
   virtual CString GetFileTitle() = 0; // returns myfile
   virtual CString GetFilePath() = 0; // returns c:\my documents\myfile.txt
   virtual CString GetFileRoot() = 0; // returns c:\my documents

   // Notifies all views of an update
   virtual void UpdateAllViews(CView* pSender,LPARAM lHint = 0L,CObject* pHint = NULL) = 0;
};


//////////////////////////////////////////////////////////////////////////
// IEAFProcessCommandLine
//
// Implement this interface in agents and extension agents that process
// command line prameters. DO NOT register this interface with the broker.

// {D39456A3-33CD-4ea0-91EE-D15BBEA574B8}
DEFINE_GUID(IID_IEAFProcessCommandLine, 
0xd39456a3, 0x33cd, 0x4ea0, 0x91, 0xee, 0xd1, 0x5b, 0xbe, 0xa5, 0x74, 0xb8);

interface IEAFProcessCommandLine : IUnknown
{
   // Processes command line options. Return TRUE if they were handled, otherwise FALSE.
   // cmdInfo is the basic command line information from the application class. You may
   // need to re-parse the command line parameters to get your parameters. The following
   // example may be used
   //
   // CMyCommandLineInfo ci; // your custom command line parser derived from CEAFCommandLineInfo
   // EAFGetApp()->ParcseCommandLine(ci);
   // cmdInfo = ci; // copies the base parameters... note there will be object slicing here
   // if ( ci.IsThisMyCommandLine )
   // {
   //    DoSomethingUseful(); // note, if there was a file name on the command line, the file is already open
   //    return TRUE; // handled
   // }
   // return FALSE;
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo) = 0;
};

// Virtual key codes not defined by Windows API
#define VK_0   0x30
#define VK_1   0x31
#define VK_2   0x32
#define VK_3   0x33
#define VK_4   0x34
#define VK_5   0x35
#define VK_6   0x36
#define VK_7   0x37
#define VK_8   0x38
#define VK_9   0x39

#define VK_A   0x41
#define VK_B   0x42
#define VK_C   0x43
#define VK_D   0x44
#define VK_E   0x45
#define VK_F   0x46
#define VK_G   0x47
#define VK_H   0x48
#define VK_I   0x49
#define VK_J   0x4A
#define VK_K   0x4B
#define VK_L   0x4C
#define VK_M   0x4D
#define VK_N   0x4E
#define VK_O   0x4F
#define VK_P   0x50
#define VK_Q   0x51
#define VK_R   0x52
#define VK_S   0x53
#define VK_T   0x54 
#define VK_U   0x55
#define VK_V   0x56
#define VK_W   0x57 
#define VK_X   0x58
#define VK_Y   0x59
#define VK_Z   0x5A

