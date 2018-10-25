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

// CompositeDisplayObjectImpl.cpp: implementation of the CCompositeDisplayObjectImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "CompositeDisplayObjectImpl.h"
#include "DisplayListImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompositeDisplayObjectImpl::CCompositeDisplayObjectImpl()
{
}

CCompositeDisplayObjectImpl::~CCompositeDisplayObjectImpl()
{
}

HRESULT CCompositeDisplayObjectImpl::FinalConstruct()
{
   SetDisplayObject(this); // Must be called from FinalConstruct and not c'tor

   CComObject<CDisplayListImpl>* pList;
   CComObject<CDisplayListImpl>::CreateInstance(&pList);
   m_CompositeItems = pList;

   return S_OK;
}

void CCompositeDisplayObjectImpl::FinalRelease()
{
   CDisplayObjectDefaultImpl::Do_FinalRelease();

   m_CompositeItems.Release();
   m_BoundingBox.Release();
}

//////////////////////////////////////////
// iCompositeDisplayObject implementation
STDMETHODIMP_(void) CCompositeDisplayObjectImpl::AddDisplayObject(iDisplayObject* pDO)
{
   m_CompositeItems->AddDisplayObject(pDO);
   m_BoundingBox.Release();
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::RemoveDisplayObject(IDType key,AccessType access)
{
   m_CompositeItems->RemoveDisplayObject(key,access);
   m_BoundingBox.Release();
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::GetDisplayObject(IDType key,AccessType access,iDisplayObject* *ppDO)
{
   if ( access == atByIndex )
      m_CompositeItems->GetDisplayObject(key,ppDO);
   else
      m_CompositeItems->FindDisplayObject(key,ppDO);
}

STDMETHODIMP_(CollectionIndexType) CCompositeDisplayObjectImpl::GetDisplayObjectCount()
{
   return m_CompositeItems->GetDisplayObjectCount();
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::ClearDisplayObjects()
{
   m_CompositeItems->Clear();
   m_BoundingBox.Release();
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::GetDisplayObjects(iDisplayList** dispList)
{
   (*dispList) = m_CompositeItems;
   (*dispList)->AddRef();
}

//////////////////////////////////////////
// iDisplayObject implementation
STDMETHODIMP_(void) CCompositeDisplayObjectImpl::SetDisplayList(iDisplayList * pDL)
{

   Do_SetDisplayList(pDL);

   // Sync the display manager with the internal display list
   if ( pDL )
   {
      CComPtr<iDisplayMgr> dispMgr;
      pDL->GetDisplayMgr(&dispMgr);
      m_CompositeItems->SetDisplayMgr(dispMgr);
   }
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::Visible(BOOL bVisible)
{
   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      dispObj->Visible(bVisible);
   }

   Do_Visible(bVisible); 
   m_BoundingBox.Release();
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   // Draw every display object
   m_CompositeItems->DrawDisplayObjects(pDC,FALSE);
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      dispObj->Highlite(pDC,bHighlite);
   }
}

#if defined(_DEBUG)
STDMETHODIMP_(void) CCompositeDisplayObjectImpl::DrawGravityWell(CDC* pDC)
{
   m_CompositeItems->DrawGravityWells(pDC);
}
#endif

STDMETHODIMP_(CRect) CCompositeDisplayObjectImpl::GetBoundingBox()
{
   CRect box;
   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      CRect doBox = dispObj->GetBoundingBox();
      if ( i == 0 )
         box = doBox;
      else
         box.UnionRect(&box,&doBox);
   }

   return box;
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::GetBoundingBox(IRect2d** rect)
{
   if ( m_BoundingBox )
   {
      (*rect) = m_BoundingBox;
      (*rect)->AddRef();
      return;
   }

   m_BoundingBox.CoCreateInstance(CLSID_Rect2d);

   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      CComPtr<IRect2d> box;
      dispObj->GetBoundingBox(&box);
      if ( i == 0 )
      {
         Float64 l,r,t,b;
         box->get_Left(&l);
         box->get_Right(&r);
         box->get_Top(&t);
         box->get_Bottom(&b);

         m_BoundingBox->put_Left(l);
         m_BoundingBox->put_Right(r);
         m_BoundingBox->put_Top(t);
         m_BoundingBox->put_Bottom(b);
      }
      else
      {
         m_BoundingBox->Union(box);
      }
   }

   (*rect) = m_BoundingBox;
   (*rect)->AddRef();
}

STDMETHODIMP_(BOOL) CCompositeDisplayObjectImpl::HitTest(CPoint point)
{
   if ( m_pGravityWellStrategy )
   {
      // If the composite has its own gravity well, use it
      CRgn rgn;
      m_pGravityWellStrategy->GetGravityWell(this,&rgn);
      return rgn.PtInRegion(point);
   }
   else
   {
      // Hit test each member of the composite individually
      CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
      for ( CollectionIndexType i = 0; i < nDO; i++ )
      {
         CComPtr<iDisplayObject> dispObj;
         m_CompositeItems->GetDisplayObject(i,&dispObj);

         if ( dispObj->HitTest(point) )
            return TRUE;
      }

      return FALSE;
   }

   return FALSE;
}

STDMETHODIMP_(BOOL) CCompositeDisplayObjectImpl::TouchesRect(CRect r)
{
   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      if ( dispObj->TouchesRect(r) )
         return TRUE;
   }

   return FALSE;
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::Select(BOOL bSelect)
{
   // This this display object isn't selectable, simply return
   if ( Do_GetSelectionType() == stNone )
      return;

   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      dispObj->Select(bSelect);
   }

   Do_Select(bSelect); 
}

STDMETHODIMP_(void) CCompositeDisplayObjectImpl::SetSelectionType(SelectionType st)
{
   CollectionIndexType nDO = m_CompositeItems->GetDisplayObjectCount();
   for ( CollectionIndexType i = 0; i < nDO; i++ )
   {
      CComPtr<iDisplayObject> dispObj;
      m_CompositeItems->GetDisplayObject(i,&dispObj);

      dispObj->SetSelectionType(st);
   }

   Do_SetSelectionType(st);
}