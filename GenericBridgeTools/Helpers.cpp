///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "Helpers.h"
#include <WBFLGenericBridgeTools.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT GetGirderSectionBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,IGirderSection** ppSection)
{
   HRESULT hr;

   CComPtr<ISuperstructureMember> ssmbr;
   hr = bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);
   ATLASSERT(segment);

   CComPtr<IShape> shape;
   hr = segment->get_PrimaryShape(distFromStartOfSegment,&shape);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IGirderSection> gdrSection(shape);
   if ( gdrSection == nullptr )
      return GBMT_E_GIRDERSECTION;

   (*ppSection) = gdrSection;
   (*ppSection)->AddRef();
   return S_OK;
}

HRESULT GetAlignment(IGenericBridge* bridge,IAlignment** alignment)
{
   return bridge->get_Alignment(alignment);
}

Float64 DistanceToStation(IGenericBridge* bridge,Float64 distFromStartOfBridge)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IBridgePier> pier;
   piers->get_Item(0,&pier);

   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);

   Float64 station;
   objStation->get_Value(&station);

   return station + distFromStartOfBridge;
}

Float64 StationToDistance(IGenericBridge* bridge,Float64 station)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IBridgePier> pier;
   piers->get_Item(0,&pier);

   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);

   Float64 start_station;
   objStation->get_Value(&start_station);

   return station - start_station;
}

void GetPiers(IGenericBridge* bridge,Float64 station,PierIndexType* pPrevPier,PierIndexType* pNextPier)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   PierIndexType nPiers;
   piers->get_Count(&nPiers);

   // before first pier
   *pPrevPier = INVALID_INDEX;
   *pNextPier = 0;

   for ( PierIndexType pierIdx = 0; pierIdx < nPiers-1; pierIdx++ )
   {
      CComPtr<IBridgePier> pier1, pier2;
      piers->get_Item(pierIdx,  &pier1);
      piers->get_Item(pierIdx+1,&pier2);

      CComPtr<IStation> objStation1, objStation2;
      pier1->get_Station(&objStation1);
      pier2->get_Station(&objStation2);

      Float64 station1,station2;
      objStation1->get_Value(&station1);
      objStation2->get_Value(&station2);

      if ( pierIdx == 0 && station < station1 )
      {
         // before first pier
         *pPrevPier = INVALID_INDEX;
         *pNextPier = 0;
         return;
      }

      if ( InRange(station1,station,station2) )
      {
         *pPrevPier = pierIdx;
         *pNextPier = pierIdx + 1;
         return;
      }
   }

   // after last pier
   *pPrevPier = nPiers-1;
   *pNextPier = INVALID_INDEX;
}
