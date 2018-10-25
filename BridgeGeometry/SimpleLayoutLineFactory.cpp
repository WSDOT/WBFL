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
      CogoObjectID key;
      hr = m_Paths->Key(pathIdx,&key);
      ATLASSERT(SUCCEEDED(hr));

      CComPtr<IPath> path;
      hr = m_Paths->get_Item(key,&path);
      ATLASSERT(SUCCEEDED(hr));
      
      hr = pPaths->AddEx(key,path);
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
