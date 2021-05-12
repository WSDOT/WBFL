///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// DisplayListImpl.h: interface for the CDisplayListImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYLISTIMPL_H__BCB8A10D_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_DISPLAYLISTIMPL_H__BCB8A10D_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <DManip\DisplayListEvents.h>

class ATL_NO_VTABLE CDisplayListImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDisplayListImpl, &CLSID_DisplayList>,
   public iDisplayList
{
public:
	CDisplayListImpl();
	virtual ~CDisplayListImpl();
   HRESULT FinalConstruct();

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
      if ( ulReturn == 2 )
         CreateStrongRef();

//      ATLTRACE("OA: ptr = %p m_dwRef = %3d, ulReturn = %3d\n", this, m_dwRef, ulReturn);
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
      if ( ulReturn == 1 )
         DestroyStrongRef();

//      ATLTRACE("OR: ptr = %p m_dwRef = %3d, ulReturn = %3d\n", this, m_dwRef, ulReturn);
      
      return ulReturn;
   }

   ULONG InternalAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
      if ( ulReturn == 2 )
         CreateStrongRef();

//      ATLTRACE("IA: ptr = %p m_dwRef = %3d, ulReturn = %3d\n", this, m_dwRef, ulReturn);

      return ulReturn;
   }

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
      if ( ulReturn == 1 )
         DestroyStrongRef();
      
//      ATLTRACE("IR: ptr = %p m_dwRef = %3d, ulReturn = %3d\n", this, m_dwRef, ulReturn);

      return ulReturn;
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DISPLAYLIST)

BEGIN_COM_MAP(CDisplayListImpl)
	COM_INTERFACE_ENTRY(iDisplayList)
END_COM_MAP()

   // iDisplayList Implementation
   STDMETHOD_(void,SetDisplayMgr)(iDisplayMgr* pDispMgr) override;
   STDMETHOD_(void,GetDisplayMgr)(iDisplayMgr** dispMgr) override;

   STDMETHOD_(void,SetID)(IDType id) override;
   STDMETHOD_(IDType,GetID)() override;

   STDMETHOD_(void,AddDisplayObject)(iDisplayObject* pDO) override;
   STDMETHOD_(void,GetDisplayObject)(CollectionIndexType index,iDisplayObject** dispObj) override;
   STDMETHOD_(void,FindDisplayObject)(IDType id,iDisplayObject** dispObj) override;
   STDMETHOD_(void,RemoveDisplayObject)(IDType key,AccessType access) override;
   STDMETHOD_(void,Clear)() override;
   STDMETHOD_(CollectionIndexType,GetDisplayObjectCount)() override;

   STDMETHOD_(void,FindDisplayObjects)(CRect rect,     DisplayObjectContainer* dispObjs) override;
   STDMETHOD_(void,FindDisplayObjects)(CPoint point,   DisplayObjectContainer* dispObjs) override;
   STDMETHOD_(void,FindDisplayObjects)(IPoint2d* point,DisplayObjectContainer* dispObjs) override;

   STDMETHOD_(void,DrawDisplayObjects)(CDC* pDC,bool bSkipSelected) override;
   STDMETHOD_(void,HideDisplayObjects)(bool bHide) override;

   STDMETHOD_(void,GetWorldExtents)(ISize2d* *ext) override;

#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWells)(CDC* pDC) override;
#endif 

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayListEvents* pEventSink) override;
   STDMETHOD_(void,UnregisterEventSink)() override;
   STDMETHOD_(void,GetEventSink)(iDisplayListEvents** pEventSink) override;


protected:
   void CreateStrongRef()
   {
      if ( m_pDispMgr )
         m_pDispMgr->AddRef();
   }

   void DestroyStrongRef()
   {
      if ( m_pDispMgr )
         m_pDispMgr->Release();
   }

private:
   iDisplayMgr* m_pDispMgr;
   IDType m_ID;

   CComPtr<iDisplayListEvents> m_EventSink;

   DisplayObjectContainer m_DisplayObjects;

   void Fire_OnDisplayObjectAdded(iDisplayObject* pDO);
   void Fire_OnDisplayObjectRemoved(IDType doID);
   void Fire_OnDisplayObjectsCleared();
};

#endif // !defined(AFX_DISPLAYLISTIMPL_H__BCB8A10D_E659_11D4_8B81_006097C68A9C__INCLUDED_)
