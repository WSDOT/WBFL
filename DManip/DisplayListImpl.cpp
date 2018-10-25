///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// DisplayListImpl.cpp: implementation of the CDisplayListImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "DisplayListImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplayListImpl::CDisplayListImpl()
{
}

CDisplayListImpl::~CDisplayListImpl()
{
   Clear();
}

HRESULT CDisplayListImpl::FinalConstruct()
{
   m_pDispMgr = 0;
   m_ID = -1;
   return S_OK;
}

STDMETHODIMP_(void) CDisplayListImpl::SetDisplayMgr(iDisplayMgr* pDispMgr)
{
   if ( m_dwRef >= 2 && m_pDispMgr )
      DestroyStrongRef();

   if ( m_pDispMgr )
      m_pDispMgr->Release();

   m_pDispMgr = pDispMgr;

   if ( m_dwRef >= 2 && m_pDispMgr )
      CreateStrongRef();
}

STDMETHODIMP_(void) CDisplayListImpl::GetDisplayMgr(iDisplayMgr** dispMgr)
{
   *dispMgr = m_pDispMgr;
   (*dispMgr)->AddRef();
}

STDMETHODIMP_(void) CDisplayListImpl::SetID(IDType id)
{
   m_ID = id;
}

STDMETHODIMP_(IDType) CDisplayListImpl::GetID()
{
   return m_ID;
}

STDMETHODIMP_(void) CDisplayListImpl::AddDisplayObject(iDisplayObject* pDO)
{
   m_DisplayObjects.push_back(DisplayObjectItem(pDO));
   pDO->SetDisplayList(this);
   Fire_OnDisplayObjectAdded(pDO);
}

STDMETHODIMP_(void) CDisplayListImpl::GetDisplayObject(CollectionIndexType index,iDisplayObject** dispObj)
{
   (*dispObj) = 0;
   if ( index < 0 || m_DisplayObjects.size() <= index )
      return;

   CComPtr<iDisplayObject> pDO = m_DisplayObjects[index];
   (*dispObj) = pDO;
   (*dispObj)->AddRef();
}

STDMETHODIMP_(void) CDisplayListImpl::FindDisplayObject(IDType id,iDisplayObject** dispObj)
{
   (*dispObj) = 0;

   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      if ( pDO->GetID() == id )
      {
         (*dispObj) = pDO;
         (*dispObj)->AddRef();
         return;
      }
   }

   return;
}

STDMETHODIMP_(void) CDisplayListImpl::RemoveDisplayObject(IDType key,AccessType access)
{
   IDType doID;
   if ( access = atByIndex )
   {
      IndexType index = (IndexType)key;
      // Remove display object by index
      if ( index < 0 || m_DisplayObjects.size() <= index )
         return;

      DisplayObjectContainer::iterator iter = m_DisplayObjects.begin() + index;
      
      CComPtr<iDisplayObject> pDO = *iter;
      doID = pDO->GetID();

      m_DisplayObjects.erase(iter);
   }
   else
   {
      // Remove display object by id
      DisplayObjectContainer::iterator iter;
      for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
      {
         CComPtr<iDisplayObject> pDO = *iter;
         if ( pDO->GetID() == key )
         {
            doID = key;
            m_DisplayObjects.erase(iter);
            break;
         }
      }
   }

   Fire_OnDisplayObjectRemoved(doID);
}

STDMETHODIMP_(void) CDisplayListImpl::Clear()
{
   if ( !m_DisplayObjects.empty() )
   {
      m_DisplayObjects.clear();
      Fire_OnDisplayObjectsCleared();
   }
}

STDMETHODIMP_(CollectionIndexType) CDisplayListImpl::GetDisplayObjectCount()
{
   return m_DisplayObjects.size();
}

STDMETHODIMP_(void) CDisplayListImpl::FindDisplayObjects(CPoint point,DisplayObjectContainer* dispObjs)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      if ( pDO->HitTest(point) )
      {
         dispObjs->push_back(pDO);

         // If this is a composite display object, drill down and get the individual display objects also
         CComQIPtr<iCompositeDisplayObject,&IID_iCompositeDisplayObject> pCDO(pDO);
         if ( pCDO )
         {
            CComPtr<iDisplayList> dispList;
            pCDO->GetDisplayObjects(&dispList);
            dispList->FindDisplayObjects(point,dispObjs);
         }
      }
   }
}

STDMETHODIMP_(void) CDisplayListImpl::FindDisplayObjects(IPoint2d* point,DisplayObjectContainer* dispObjs)
{
   CComPtr<iDisplayMgr> pDispMgr;
   GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   CPoint p;
   pMap->WPtoLP(point,&p.x,&p.y);
   FindDisplayObjects(p,dispObjs);
}

STDMETHODIMP_(void) CDisplayListImpl::FindDisplayObjects(CRect rect,DisplayObjectContainer* selObjs)
{
   rect.NormalizeRect();
   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      if ( pDO->TouchesRect(rect) )
         selObjs->push_back(pDO);
   }
}

STDMETHODIMP_(void) CDisplayListImpl::DrawDisplayObjects(CDC* pDC,bool bSkipSelected)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;

      if ( !bSkipSelected )
      {
         // if not skipping selected, draw
         pDO->Draw(pDC);
      }
      else
      {
         // if skipping selected, draw only if not selected
         if ( !pDO->IsSelected() )
            pDO->Draw(pDC);
      }
   }
}

STDMETHODIMP_(void) CDisplayListImpl::HideDisplayObjects(bool bHide)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      pDO->Visible( !bHide );
   }
}

STDMETHODIMP_(void) CDisplayListImpl::GetWorldExtents(ISize2d* *ext)
{
   CComPtr<IRect2d> worldRect;
   worldRect.CoCreateInstance(CLSID_Rect2d);

   CollectionIndexType nDisplayObjects = GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDisplayObjects; i++ )
   {
      CComPtr<iDisplayObject> pDO;
      GetDisplayObject(i,&pDO);

      CComPtr<IRect2d> box;
      pDO->GetBoundingBox(&box);

      if (i==0)
      {
         Float64 lBox,rBox,tBox,bBox;
         box->get_Left(&lBox);
         box->get_Right(&rBox);
         box->get_Top(&tBox);
         box->get_Bottom(&bBox);

         worldRect = box;
      }
      else
      {
         worldRect->Union(box);
      }
   }

   Float64 wx,wy;
   worldRect->get_Width(&wx);
   worldRect->get_Height(&wy);

   CComPtr<ISize2d> size;
   size.CoCreateInstance(CLSID_Size2d);
   size->put_Dx(wx);
   size->put_Dy(wy);

   (*ext) = size;
   (*ext)->AddRef();
}


#if defined(_DEBUG)
STDMETHODIMP_(void) CDisplayListImpl::DrawGravityWells(CDC* pDC)
{
   DisplayObjectContainer::iterator iter;
   for ( iter = m_DisplayObjects.begin(); iter != m_DisplayObjects.end(); iter++ )
   {
      CComPtr<iDisplayObject> pDO = *iter;
      pDO->DrawGravityWell( pDC );
   }
}
#endif

void CDisplayListImpl::RegisterEventSink(iDisplayListEvents* pEventSink)
{
   UnregisterEventSink();
   m_EventSink = pEventSink;
}

void CDisplayListImpl::UnregisterEventSink()
{
   m_EventSink = 0;
}

void CDisplayListImpl::GetEventSink(iDisplayListEvents** pEventSink)
{
   if ( pEventSink == NULL )
      return;

   (*pEventSink) = m_EventSink;
   (*pEventSink)->AddRef();
}

void CDisplayListImpl::Fire_OnDisplayObjectAdded(iDisplayObject* pDO)
{
   if ( m_EventSink )
      m_EventSink->OnDisplayObjectAdded(m_ID,pDO);
}

void CDisplayListImpl::Fire_OnDisplayObjectRemoved(IDType doID)
{
   if ( m_EventSink )
      m_EventSink->OnDisplayObjectRemoved(m_ID,doID);
}

void CDisplayListImpl::Fire_OnDisplayObjectsCleared()
{
   if ( m_EventSink )
      m_EventSink->OnDisplayObjectsCleared(m_ID);
}
