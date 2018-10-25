///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2015  Washington State Department of Transportation
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

// SimpleLayoutLineFactory.cpp : Implementation of CSimpleLayoutLineFactory

#include "stdafx.h"
#include "SimpleLayoutLineFactory.h"


// CSimpleLayoutLineFactory

STDMETHODIMP CSimpleLayoutLineFactory::Create(IBridgeGeometry* pBridge,IPathCollection* pPaths)
{
   CHECK_IN(pBridge);
   CHECK_IN(pPaths);

   HRESULT hr;
   CollectionIndexType nPaths;
   m_Paths->get_Count(&nPaths);
   for ( CollectionIndexType pathIdx = 0; pathIdx < nPaths; pathIdx++ )
   {
      CogoObjectID id;
      hr = m_Paths->ID(pathIdx,&id);
      ATLASSERT(SUCCEEDED(hr));

      CComPtr<IPath> path;
      hr = m_Paths->get_Item(id,&path);
      ATLASSERT(SUCCEEDED(hr));
      
      hr = pPaths->AddEx(id,path);
      ATLASSERT(SUCCEEDED(hr));
   }

   return S_OK;
}

STDMETHODIMP CSimpleLayoutLineFactory::Reset()
{
   return m_Paths->Clear();
}

STDMETHODIMP CSimpleLayoutLineFactory::AddPath(LineIDType ID,IPath* path)
{
   HRESULT hr = m_Paths->AddEx(ID,path);
   if ( FAILED(hr) )
      return hr;
   return S_OK;
}
