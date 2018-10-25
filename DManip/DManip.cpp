///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// DManip.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f DManipps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include <WBFLGeometry_i.c>

#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <WBFLUnitServer.h>
#include <WBFLCogo.h>
#include <WBFLCogo_i.c>

#include <WBFLDManip.h>
#include <DManip\DManip.h>


#include "DisplayMgrImpl.h"
#include "DisplayListImpl.h"

#include "MappingImpl.h"

#include "TaskFactoryImpl.h"
#include "InplaceEditTaskImpl.h"
#include "RectSelectTaskImpl.h"
#include "LocalDragDropTaskImpl.h"
#include "ForeignDragDropTaskImpl.h"
#include "CenterOnPointTaskImpl.h"
#include "ZoomRectTaskImpl.h"

#include "DisplayObjectFactoryImpl.h"
#include "PointDisplayObjectImpl.h"
#include "TextBlockImpl.h"
#include "ViewTitleImpl.h"
#include "EditableTextBlockImpl.h"
#include "EditableUnitValueTextBlockImpl.h"
#include "LineImpl.h"
#include "DimensionLineImpl.h"
#include "CompositeDisplayObjectImpl.h"
#include "NorthArrowImpl.h"

#include "SimpleDrawPointStrategyImpl.h"
#include "SimpleDrawLineStrategyImpl.h"
#include "SimpleDrawDashedLineStrategyImpl.h"
#include "RectangleDrawLineStrategyImpl.h"
#include "ExtRectangleDrawLineStrategyImpl.h"
#include "ShapeDrawStrategyImpl.h"
#include "TargetDrawStrategyImpl.h"
#include "CompoundDrawLineStrategyImpl.h"

#include "ShapeGravityWellStrategyImpl.h"

#include "PlugImpl.h"
#include "SocketImpl.h"
#include "SocketFactoryImpl.h"

#include "DragDataImpl.h"

#include "ToolImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DEFINE_GROUP(DManip,DIAG_GROUP_ENABLE,0);

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(CLSID_DisplayMgr, CDisplayMgrImpl)
   OBJECT_ENTRY(CLSID_DisplayList, CDisplayListImpl)

   OBJECT_ENTRY(CLSID_Mapping, CMappingImpl)

   OBJECT_ENTRY(CLSID_TaskFactory, CTaskFactoryImpl)
   OBJECT_ENTRY(CLSID_InplaceEditTask, CInplaceEditTaskImpl)
   OBJECT_ENTRY(CLSID_RectSelectTask, CRectSelectTaskImpl)
   OBJECT_ENTRY(CLSID_LocalDragDropTask, CLocalDragDropTaskImpl)
   OBJECT_ENTRY(CLSID_ForeignDragDropTask, CForeignDragDropTaskImpl)
   OBJECT_ENTRY(CLSID_CenterOnPointTask,CCenterOnPointTaskImpl)
   OBJECT_ENTRY(CLSID_ZoomRectTask,CZoomRectTaskImpl)

   OBJECT_ENTRY(CLSID_DisplayObjectFactory,CDisplayObjectFactoryImpl)
   OBJECT_ENTRY(CLSID_PointDisplayObject,CPointDisplayObjectImpl)
   OBJECT_ENTRY(CLSID_TextBlock,CTextBlockImpl)
   OBJECT_ENTRY(CLSID_ViewTitle,CViewTitleImpl)
   OBJECT_ENTRY(CLSID_EditableTextBlock,CEditableTextBlockImpl)
   OBJECT_ENTRY(CLSID_EditableUnitValueTextBlock,CEditableUnitValueTextBlockImpl)
   OBJECT_ENTRY(CLSID_LineDisplayObject,CLineImpl)
   OBJECT_ENTRY(CLSID_DimensionLineDisplayObject,CDimensionLineImpl)
   OBJECT_ENTRY(CLSID_CompositeDisplayObject,CCompositeDisplayObjectImpl)
   OBJECT_ENTRY(CLSID_NorthArrow,CNorthArrowImpl)

   OBJECT_ENTRY(CLSID_SimpleDrawPointStrategy,CSimpleDrawPointStrategyImpl)
   OBJECT_ENTRY(CLSID_SimpleDrawLineStrategy,CSimpleDrawLineStrategyImpl)
   OBJECT_ENTRY(CLSID_SimpleDrawDashedLineStrategy,CSimpleDrawDashedLineStrategyImpl)
   OBJECT_ENTRY(CLSID_RectangleDrawLineStrategy,CRectangleDrawLineStrategyImpl)
   OBJECT_ENTRY(CLSID_ExtRectangleDrawLineStrategy,CExtRectangleDrawLineStrategyImpl)
   OBJECT_ENTRY(CLSID_ShapeDrawStrategy, CShapeDrawStrategyImpl)
   OBJECT_ENTRY(CLSID_TargetDrawStrategy, CTargetDrawStrategyImpl)
   OBJECT_ENTRY(CLSID_CompoundDrawLineStrategy, CCompoundDrawLineStrategyImpl)

   OBJECT_ENTRY(CLSID_ShapeGravityWellStrategy,CShapeGravityWellStrategyImpl)

   OBJECT_ENTRY(CLSID_Plug,CPlugImpl)
   OBJECT_ENTRY(CLSID_Socket,CSocketImpl)
   OBJECT_ENTRY(CLSID_SocketFactory,CSocketFactoryImpl)

   OBJECT_ENTRY(CLSID_DragDataSource, CDragDataSourceImpl)
   OBJECT_ENTRY(CLSID_DragDataSink, CDragDataSinkImpl)

   OBJECT_ENTRY(CLSID_Tool, CToolImpl)
END_OBJECT_MAP()

class CDManipApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDManipApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDManipApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDManipApp, CWinApp)
	//{{AFX_MSG_MAP(CDManipApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDManipApp theApp;

BOOL CDManipApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_WBFLDManip);
    return CWinApp::InitInstance();
}

int CDManipApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
   WATCHX(DManip,1,_T("DManip.DLL - DllCanUnloadNow") );
   LONG cLock = _Module.GetLockCount();
   WATCHX(DManip,1,_T("Lock Count = ") << cLock );
   bool bCanUnload = ( cLock == 0 );
   WATCHX(DManip,1,_T("DManip.DLL - DllCanUnloadNow returning ") << (bCanUnload ? _T("S_OK") : _T("S_FALSE")) );
	return ( bCanUnload ) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(FALSE); // No typelib
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(FALSE); // No typelib
}
