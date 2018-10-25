///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include "GenericBridgeHelpers.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CogoObjectID g_AlignmentKey = 0;
const CogoObjectID g_CLBridgeKey  = 1;

HRESULT GB_GetPierGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(1)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetBearingGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(0)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetPierAlignmentPointId(PierIndexType pierIdx,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*PIER_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetTemporarySupportAlignmentPointId(SpanIndexType spanIdx,SupportIndexType tsIdx,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = -1*( (spanIdx+1)*TS_ID_OFFSET + (tsIdx+1)*TS_ID_OFFSET/100 );
   return S_OK;
}

HRESULT GB_GetTemporarySupportGirderPointId(SpanIndexType spanIdx,SupportIndexType tsIdx,GirderIndexType gdrIdx,PositionType posType,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = -1*( (spanIdx+1)*TS_ID_OFFSET 
                   + (tsIdx+1)*TS_ID_OFFSET/100 
                   + (gdrIdx+1)*GIRDER_ID_OFFSET
                   + (0)*LOCATION_OFFSET
                   + (posType)*SIDE_OFFSET
      );
   return S_OK;
}

HRESULT GB_GetPierCLBridgePointId(PierIndexType pierIdx,CogoObjectID* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*BRIDGE_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetGirderLineId(SpanIndexType spanIdx,GirderIndexType gdrIdx,CogoObjectID* pVal)
{
   *pVal = -1*( (spanIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
              );

   return S_OK;
}

// function to deal with fractional and absolute values
Float64 GB_GetFracDistance(Float64 fracLoc, Float64 Length, bool ignoreTooBig)
{
   ATLASSERT(Length>0.0);

   if (fracLoc>=0.0)
   {
      if (ignoreTooBig || IsLE(fracLoc,Length) )
      {
         return fracLoc;
      }
      else
      {
         throw frTooBig;
      }
   }
   else
   {
      if (fracLoc>=-1.0)
      {
         return -fracLoc*Length;
      }
      else
         throw frTooSmall;
   }

   ATLASSERT(false); //can't get here
   return 0.0;
}

Float64 GB_GetHaunchDepth(ISegment* pSegment,Float64 distAlongSegment)
{
   Float64 startHaunch,endHaunch;
   pSegment->get_HaunchDepth(etStart,&startHaunch);
   pSegment->get_HaunchDepth(etEnd,&endHaunch);

   Float64 segment_length;
   pSegment->get_Length(&segment_length);
   Float64 haunch = ::LinInterp(distAlongSegment,startHaunch,endHaunch,segment_length);

   return haunch;
}

HRESULT GB_GetSectionLocation(ISegment* pSegment,Float64 distAlongSegment,IPoint2d** ppTopCenter)
{
   CComPtr<IGirderLine> gdrLine;
   pSegment->get_GirderLine(&gdrLine);

   CComPtr<IPath> gdrPath;
   gdrLine->get_Path(&gdrPath);

   CComPtr<IPoint2d> pnt;
   gdrPath->LocatePoint(distAlongSegment,omtNormal,0.00,CComVariant(NULL),&pnt);
   Float64 x,y;
   pnt->Location(&x,&y);

   CComPtr<ISuperstructureMember> ssmbr;
   pSegment->get_SuperstructureMember(&ssmbr);

   CComPtr<IGenericBridge> bridge;
   ssmbr->get_Bridge(&bridge);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IStation> station;
   Float64 offset;
   alignment->Offset(pnt,&station,&offset);

   CComPtr<IProfile> profile;
   alignment->get_Profile(&profile);

   Float64 elevation;
   profile->Elevation(CComVariant(station),offset,&elevation);

   Float64 elevation_offset = 0;
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   if ( deck )
   {
      Float64 gross_depth;
      deck->get_GrossDepth(&gross_depth);

      Float64 haunch;
      pSegment->GetHaunchDepth(distAlongSegment,&haunch);

      elevation_offset = gross_depth + haunch;
   }

   elevation -= elevation_offset;

   CComPtr<IPoint2d> pntTopCenter;
   pntTopCenter.CoCreateInstance(CLSID_Point2d);
   pntTopCenter->Move(offset,elevation);

   return pntTopCenter.CopyTo(ppTopCenter);
}
