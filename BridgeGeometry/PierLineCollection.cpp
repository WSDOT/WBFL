///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2018  Washington State Department of Transportation
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

// PierLineCollection.cpp : Implementation of CPierCollection

#include "stdafx.h"
#include "PierLineCollection.h"
#include "PierLine.h"

// CPierLineCollection
STDMETHODIMP CPierLineCollection::get_PierLine(PierIndexType index, IPierLine* *pVal)
{
   return get_Item(index,pVal);
}

STDMETHODIMP CPierLineCollection::get_PierLineIndex(IPierLine* pier,PierIndexType* index)
{
   CHECK_IN(pier);
   CHECK_RETVAL(index);

   (*index) = GetPierLineIndex(pier);
   return ( (*index) == INVALID_INDEX ) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CPierLineCollection::get__EnumPiers(IEnumPierLines* *enumPiers)
{
   return get__EnumElements(enumPiers);
}

STDMETHODIMP CPierLineCollection::FindPierLine(PierIDType pierID, IPierLine* *pVal)
{
   CHECK_RETOBJ(pVal);
   iterator iter( begin() );
   iterator end( end() );
   for ( ; iter != end; iter++ )
   {
      StoredType* st = *iter;
      PierIDType id;
      st->second.m_T->get_ID(&id);
      if ( id == pierID )
      {
         return st->second.m_T.CopyTo(pVal);
      }
   }

   return E_FAIL;
}

PierIndexType CPierLineCollection::GetPierLineIndex(IPierLine* pier)
{
   PierIndexType idx = 0;
   iterator iter( begin() );
   iterator end( end() );
   for ( ; iter != end; iter++ )
   {
      StoredType* st = *iter;
      if ( st->second.m_T.IsEqualObject(pier) )
         return idx;

      idx++;
   }

   ATLASSERT( iter != end ); // Pier wasn't found
   return INVALID_INDEX;
}

HRESULT CPierLineCollection::OnAfterAdd( StoredType* pVal, PierIndexType idx)
{
   Sort();
   return S_OK;
}

bool CPierLineCollection::PierSort(StoredType a,StoredType b)
{
   IPierLine* pPier1 = a.second.m_T;
   IPierLine* pPier2 = b.second.m_T;

   CComPtr<IStation> sta1, sta2;
   pPier1->get_Station(&sta1);
   pPier2->get_Station(&sta2);

   Float64 v1,v2;
   sta1->get_Value(&v1);
   sta2->get_Value(&v2);

   return v1 < v2;
}

void CPierLineCollection::Sort()
{
   // sort the pier collection based on statino
   std::sort(m_coll.begin(),m_coll.end(),CPierLineCollection::PierSort);

   // update the pier index values on the pier objects
   // reset the prev/next pier points
   PierIndexType idx = 0;
   CComPtr<IPierLine> prevPier, nextPier;
   iterator iter( begin() );
   iterator end( end() );
   for ( ; iter != end; iter++ )
   {
      StoredType* st = *iter;
      CComPtr<IPierLine> pier = st->second.m_T;
      CPierLine* pPier = (CPierLine*)(pier.p);
      pPier->m_Index = idx++;

      pPier->m_pPrevPier = prevPier;

      // if there was a previous pier, the previous pier's next pier is this pier
      if ( prevPier )
         ((CPierLine*)(prevPier.p))->m_pNextPier = pier;

      prevPier = pier;
   }

#if defined _DEBUG
   CPierLine* pPier = (CPierLine*)(m_coll.front().second.m_T.p);
   PierIndexType nPiers = 0;
   while ( pPier )
   {
      nPiers++;
      pPier = (CPierLine*)(pPier->m_pNextPier);
   }
   ATLASSERT( nPiers == m_coll.size() );

   pPier = (CPierLine*)(m_coll.back().second.m_T.p);
   nPiers = 0;
   while ( pPier )
   {
      nPiers++;
      pPier = (CPierLine*)(pPier->m_pPrevPier);
   }
   ATLASSERT( nPiers == m_coll.size() );
#endif
}
