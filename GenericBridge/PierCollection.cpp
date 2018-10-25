///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// PierCollection.cpp : Implementation of CPierCollection
#include "stdafx.h"
#include "WBFLGenericBridge.H"
#include "GenericBridgeImpl.h"
#include "PierCollection.h"
#include "Pier.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPierCollection

void CPierCollection::FinalRelease()
{
   Clear(); // Forces all of the pier objects to be unadvised
}

STDMETHODIMP CPierCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPierCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPierCollection::InsertQuietly(PierIndexType index, IPier* pier)
{
   return Insert(index,pier);
}

PierIndexType CPierCollection::GetPierIndex(IPier* pier)
{
   PierIndexType idx = 0;
   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      StoredType* st = *iter;
      if ( st->second.m_T.IsEqualObject(pier) )
         return idx;

      idx++;
   }

   ATLASSERT( iter != end() ); // Pier wasn't found
   return ALL_PIERS;
}

STDMETHODIMP CPierCollection::get__EnumPiers(IEnumPiers* *enumPiers)
{
   return get__EnumElements(enumPiers);
}

STDMETHODIMP CPierCollection::get_PierIndex(IPier* pier,PierIndexType* index)
{
   CHECK_IN(pier);
   CHECK_RETVAL(index);

   (*index) = GetPierIndex(pier);
   return ( (*index) == ALL_PIERS ) ? S_FALSE : S_OK;
}

/////////////////////////////////////////////////////////////
STDMETHODIMP CPierCollection::Load(IStructuredLoad2 *pload)
{
   HRESULT hr = PersistentPierCollection::Load(pload);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

//#if defined _DEBUG
//void CPierCollection::Dump(CDumpContext& ctx)
//{
//   ctx << "Pier Collection Dump\n";
//   iterator iter;
//   long count = 0;
//   for ( iter = begin(); iter != end(); iter++, count++ )
//   {
//      StoredType* st = *iter;
//      IPier* pier = st->second.m_T;
//      CComPtr<IStation> objStation;
//      pier->get_Station(&objStation);
//     
//      Float64 station;
//      objStation->get_Value(&station);
//
//      ctx << "Pier " << (count+1) << " Station " << station << "\n";
//   }
//}
//#endif // _DEBUG
