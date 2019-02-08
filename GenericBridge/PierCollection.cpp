///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <WBFLCogo\CogoHelpers.h>

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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPierCollection::InsertQuietly(PierIndexType index, IBridgePier* pier)
{
   return Insert(index,pier);
}

PierIndexType CPierCollection::GetPierIndex(IBridgePier* pier)
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

STDMETHODIMP CPierCollection::get_PierIndex(IBridgePier* pier,PierIndexType* index)
{
   CHECK_IN(pier);
   CHECK_RETVAL(index);

   (*index) = GetPierIndex(pier);
   return ( (*index) == ALL_PIERS ) ? S_FALSE : S_OK;
}

bool PierSearch(const PierColl::StoredType& item,const PierColl::StoredType& testItem)
{
   CComPtr<IBridgePier> pier     = item.second.m_T;
   CComPtr<IBridgePier> testPier = testItem.second.m_T;

   CComPtr<IGenericBridge> pBridge;
   pier->get_Bridge(&pBridge);

   if ( pBridge == nullptr )
   {
      testPier->get_Bridge(&pBridge);
   }

   CComPtr<IAlignment> alignment;
   pBridge->get_Alignment(&alignment);

   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);

   CComPtr<IStation> objTestStation;
   testPier->get_Station(&objTestStation);

   return (0 < cogoUtil::Compare(alignment,objStation,objTestStation));
}

STDMETHODIMP CPierCollection::FindPier(Float64 station,IBridgePier** ppPier)
{
   // Returns the pier that comes just before the specified station
   // if the station comes before the start of the bridge, returns an error
   // if the station comes after the end of the bridge, returns the last pier
   CHECK_RETOBJ(ppPier);

   if (m_coll.size() == 0 )
   {
      return E_FAIL;
   }

   // search for the pier... upper_bound does a binary search and returns an iterator
   // to the first pier that has a station greater than the specified station
   CComPtr<IStation> objStation;
   m_TestPier->get_Station(&objStation);
   objStation->put_Value(station);
   PierColl::StoredType testItem;
   testItem.first = 0;
   testItem.second.m_T = m_TestPier;
   PierColl::ContainerType::iterator found = std::upper_bound(m_coll.begin(),m_coll.end(),testItem,PierSearch);
   if ( found == m_coll.end() )
   {
      // pier wasn't found... station after the last pier
      // return the last pier
      return m_coll.back().second.m_T.CopyTo(ppPier);
   }

   if ( found == m_coll.begin() )
   {
      // specified station is before the first pier
      return E_FAIL;
   }

   // back up one...
   found--;

   return found->second.m_T.CopyTo(ppPier);

   //// Alternative (and original) implementation... linear search
   //// Walk down the bridge and find the two piers that bound the specified station
   //// Return the pier that is before specified station

   //PierIndexType nPiers;
   //get_Count(&nPiers);

   //bool bFound = false;
   //CComPtr<IBridgePier> prev_pier;
   //for ( PierIndexType pierIdx = 0; pierIdx < nPiers-1; pierIdx++ )
   //{
   //   prev_pier.Release();
   //   get_Item(pierIdx,&prev_pier);

   //   CComPtr<IStation> objPrevPierStation;
   //   prev_pier->get_Station(&objPrevPierStation);

   //   Float64 prev_pier_station;
   //   objPrevPierStation->get_Value(&prev_pier_station);

   //   if ( prev_pier_station < station )
   //   {
   //      bFound = true;
   //      break; // previous pier found
   //   }
   //}

   //if ( !bFound )
   //{
   //   return E_FAIL;
   //}

   //prev_pier.CopyTo(ppPier);
   //return S_OK;
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
//      IBridgePier* pier = st->second.m_T;
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
