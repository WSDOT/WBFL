///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// EdgePathStrategy.cpp : Implementation of CConstantOverhangStrategy
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "EdgePathStrategy.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdgePathStrategy
HRESULT CEdgePathStrategy::FinalConstruct()
{
   return S_OK;
}

void CEdgePathStrategy::FinalRelease()
{
   Unadvise(m_Path,m_dwPathCookie);
}

STDMETHODIMP CEdgePathStrategy::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEdgePathStrategy,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// IOverhangPathStrategy implementation
STDMETHODIMP CEdgePathStrategy::get_Path(IPath** path)
{
   CHECK_RETOBJ(path);

   if ( m_Path )
   {
      (*path) = m_Path;
      (*path)->AddRef();
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IEdgePathStrategy implementation
STDMETHODIMP CEdgePathStrategy::putref_Path(IPath* path)
{
   CHECK_IN(path);
   Unadvise(m_Path,m_dwPathCookie);
   m_Path = path;
   Advise(m_Path,&m_dwPathCookie);
   Fire_OnStrategyChanged();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CEdgePathStrategy::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);
   load->BeginUnit(CComBSTR("EdgePathStrategy"));

   CComVariant var;

   if ( m_Path )
      m_Path.Release();

   load->get_Property(CComBSTR("Path"),&var);
   var.punkVal->QueryInterface(&m_Path);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CEdgePathStrategy::Save(IStructuredSave2* save)
{
   CHECK_IN(save);
   save->BeginUnit(CComBSTR("EdgePathStrategy"),1.0);
   save->put_Property(CComBSTR("Path"),CComVariant(m_Path));
   save->EndUnit();
   return S_OK;
}

void CEdgePathStrategy::Advise(IPath* path,DWORD* pdwCookie)
{
   if ( path == NULL )
      return;

   HRESULT hr = AtlAdvise(path,GetUnknown(),IID_IPathEvents,pdwCookie);
   ATLASSERT(SUCCEEDED(hr));
   InternalRelease();
}

void CEdgePathStrategy::Unadvise(IPath* path,DWORD dwCookie)
{
   if ( path == NULL )
      return;

   InternalAddRef();
   HRESULT hr = AtlUnadvise(path,IID_IPathEvents,dwCookie);
   ATLASSERT( SUCCEEDED(hr) );
}