///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// PolyLineDisplayObject.cpp : Implementation of CPolyLineDisplayObjectImpl
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "PolyLineDisplayObjectImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPolyLineDisplayObjectImpl

/////////////////////////////////////////////////////////////////////////////
// CPolyLineDisplayObjectImpl
CPolyLineDisplayObjectImpl::CPolyLineDisplayObjectImpl():
m_Color(RGB(0,0,0)),
m_Width(100),
m_PtType(plpCircle),
m_CurrId(0)
{
}


STDMETHODIMP CPolyLineDisplayObjectImpl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iPolyLineDisplayObject
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPolyLineDisplayObjectImpl::FinalConstruct()
{
   // for some undocumented reason, you must ask for iunknown when aggregating
   HRESULT hr = m_pDisplayObject.CoCreateInstance(CLSID_CompositeDisplayObject);

   if (FAILED(hr))
      return hr;

   return S_OK;
}

void::CPolyLineDisplayObjectImpl::FinalRelease()
{
   ClearDisplayObjects();

   m_pDisplayObject.Release();
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::get_Color(COLORREF *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Color;
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::put_Color(COLORREF color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Color = color;
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::get_Width(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Width;
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::put_Width(long width)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (width<=0)
   {
      ATLASSERT(0);
   }
   else
   {
	   m_Width = width;
   }
}


STDMETHODIMP CPolyLineDisplayObjectImpl::GetPoint(long index, IPoint2d** pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   (*pVal) = 0;
   if ( index < 0 || (long)m_Container.size() <= index )
      return E_FAIL;

   ContainerItem ppt = m_Container[index];
   return ppt.m_T.CopyTo(pVal);

}

STDMETHODIMP_(long) CPolyLineDisplayObjectImpl::get_NumberOfPoints()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   return m_Container.size();
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::AddPoint(IPoint2d *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_Container.push_back(ContainerItem(pVal));
}

STDMETHODIMP CPolyLineDisplayObjectImpl::InsertPoint(long index, IPoint2d *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (index<0 || index>(long)m_Container.size()+1)
      return E_INVALIDARG;

   if (index==m_Container.size())

      AddPoint(pVal);
   else
   {
      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.insert(it, ContainerItem(pVal));
   }

   return S_OK;
}

STDMETHODIMP CPolyLineDisplayObjectImpl::RemovePoint(long index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if (index<0 || index>(long)m_Container.size()-1)
      return E_INVALIDARG;

      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.erase(it);

      return S_OK;
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::ClearPoints()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   m_Container.clear();
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::Commit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   HRESULT hr = RebuildDisplayObjects();
   ATLASSERT(SUCCEEDED(hr));
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::put_PointType(PolyLinePointType ptType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   m_PtType = ptType;
}

STDMETHODIMP_(void) CPolyLineDisplayObjectImpl::get_PointType(PolyLinePointType* ptType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   *ptType = m_PtType;
}

HRESULT CPolyLineDisplayObjectImpl::RebuildDisplayObjects()
{
   // first remove display objects
   ClearDisplayObjects();

   // build lines
   if (m_Container.size()>1)
   {
      ContainerIterator it = m_Container.begin();
      CComPtr<IPoint2d> start_pnt = it->m_T;
      it++;
      while(it != m_Container.end())
      {
         CComPtr<IPoint2d> end_pnt = it->m_T;

         BuildLine(m_pDisplayObject, start_pnt, end_pnt);

         start_pnt = end_pnt;
         it++;
      }
   }

   return S_OK;
}


void CPolyLineDisplayObjectImpl::AddMyDisplayObject(iDisplayObject* pdo)
{
   m_pDisplayObject->AddDisplayObject(pdo);
   m_NumDos++;
}

void CPolyLineDisplayObjectImpl::ClearDisplayObjects()
{
   if (m_NumDos>0)
   {
      // first go through all connectable display objects and disconnect sockets
      long cnt =  m_pDisplayObject->GetDisplayObjectCount();
      for (long ic=0; ic<cnt; ic++)
      {
         CComPtr<iDisplayObject> pdo;
         m_pDisplayObject->GetDisplayObject(ic,atByIndex,&pdo);

         CComQIPtr<iConnectable,&IID_iConnectable> connectable(pdo);

         if (connectable)
         {
            connectable->RemoveAllSockets();
         }
      }

      m_pDisplayObject->ClearDisplayObjects();
      m_NumDos = 0;
   }
}

void CPolyLineDisplayObjectImpl::BuildLine(iCompositeDisplayObject* pCdo, IPoint2d* fromPoint,IPoint2d* toPoint)
{
   // put points at locations and make them sockets
   CComPtr<iPointDisplayObject> from_rep;
   ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&from_rep);
   from_rep->SetPosition(fromPoint,FALSE,FALSE);
   from_rep->SetID(m_CurrId++);
   CComQIPtr<iConnectable,&IID_iConnectable> from_connectable(from_rep);
   CComPtr<iSocket> from_socket;
   from_connectable->AddSocket(0,fromPoint,&from_socket);
   from_rep->Visible(FALSE);
   pCdo->AddDisplayObject(from_rep);

   CComPtr<iPointDisplayObject> to_rep;
   ::CoCreateInstance(CLSID_PointDisplayObject,NULL,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&to_rep);
   to_rep->SetPosition(toPoint,FALSE,FALSE);
   to_rep->SetID(m_CurrId++);
   CComQIPtr<iConnectable,&IID_iConnectable> to_connectable(to_rep);
   CComPtr<iSocket> to_socket;
   to_connectable->AddSocket(0,toPoint,&to_socket);
   to_rep->Visible(FALSE);
   pCdo->AddDisplayObject(to_rep);

   // Create the line object
   CComPtr<iLineDisplayObject> line;
   ::CoCreateInstance(CLSID_LineDisplayObject,NULL,CLSCTX_ALL,IID_iLineDisplayObject,(void**)&line);

   // color and width
   CComPtr<iDrawLineStrategy> pStrategy;
   line->GetDrawLineStrategy(&pStrategy);

   // dangerous cast here
   iSimpleDrawLineStrategy* pSimple = dynamic_cast<iSimpleDrawLineStrategy*>(pStrategy.p);
   if (pSimple)
   {
      pSimple->SetColor(m_Color);
      pSimple->SetWidth(m_Width);
      pSimple->SetBeginType((LineEndType)m_PtType);
      pSimple->SetEndType((LineEndType)m_PtType);
   }
   else
      ATLASSERT(0);

   // Attach connector to the sockets 
   CComPtr<iConnector> connector;
   line->QueryInterface(IID_iConnector,(void**)&connector);
   CComPtr<iPlug> startPlug;
   CComPtr<iPlug> endPlug;
   connector->GetStartPlug(&startPlug);
   connector->GetEndPlug(&endPlug);

   // connect the line to the sockets
   DWORD dwCookie;
   from_socket->Connect(startPlug,&dwCookie);
   to_socket->Connect(endPlug,&dwCookie);

   line->SetID(m_CurrId++);

   pCdo->AddDisplayObject(line);
}
