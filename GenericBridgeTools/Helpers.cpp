///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2010  Washington State Department of Transportation
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

HRESULT GetGirderSection(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 location,ISegment** segment,IGirderSection** section)
{
   HRESULT hr;

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   hr = spans->get_Item(spanIdx,&span);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISuperstructureMember> ssmbr;
   hr = span->get_SuperstructureMember(gdrIdx,&ssmbr);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISegmentItem> segItem;
   Float64 dist;
	hr = ssmbr->GetSegmentForMemberLocation(location,&dist,&segItem);
   if ( FAILED(hr) )
      return hr;

   CComPtr<ISegment> seg;
   segItem->get_Segment(&seg);

   CComPtr<IShape> shape;
   hr = seg->get_Shape(dist,&shape);
   if ( FAILED(hr) )
      return hr;

   CComQIPtr<IGirderSection> sect(shape);
   if ( sect == NULL )
      return GBMT_E_GIRDERSECTION;

   (*segment) = seg;
   (*segment)->AddRef();

   (*section) = sect;
   (*section)->AddRef();
   return S_OK;
}

HRESULT GetAlignment(IGenericBridge* bridge,IAlignment** alignment)
{
   CComPtr<ICogoInfo> cogoinfo;
   bridge->get_CogoInfo(&cogoinfo);

   CComPtr<ICogoModel> cogomodel;
   bridge->get_CogoModel(&cogomodel);

   CComPtr<IPathCollection> alignments;
   cogomodel->get_Alignments(&alignments);

   long key;
   cogoinfo->get_AlignmentKey(&key);
   CComPtr<IPath> alignpath;
   alignments->get_Item(key,&alignpath);

   alignpath->QueryInterface(alignment);

   return S_OK;
}

HRESULT GetGirderHaunch(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,Float64* pHaunch)
{
   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(spanIdx,&span);

   CComPtr<IGirderSpacing> startSpacing, endSpacing;
   span->get_GirderSpacing(etStart,&startSpacing);
   span->get_GirderSpacing(etEnd,  &endSpacing);

   Float64 startHaunch, endHaunch;
   startSpacing->get_GirderHaunch(gdrIdx,&startHaunch);
   endSpacing->get_GirderHaunch(gdrIdx,&endHaunch);

   Float64 length;
   span->get_GirderLineLength(gdrIdx,&length);

   Float64 haunch = ::LinInterp(distFromStartOfGirder,startHaunch,endHaunch,length);
   *pHaunch = haunch;
   return S_OK;
}

Float64 DistanceToStation(IGenericBridge* bridge,Float64 distFromStartOfBridge)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
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

   CComPtr<IPier> pier;
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
      CComPtr<IPier> pier1, pier2;
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
