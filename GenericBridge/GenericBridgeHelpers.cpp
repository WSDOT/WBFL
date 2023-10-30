///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Math\MathUtils.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT GB_GetPierGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,IDType* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(1)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetBearingGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,IDType* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(0)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetPierAlignmentPointId(PierIndexType pierIdx,IDType* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*PIER_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetTemporarySupportAlignmentPointId(SpanIndexType spanIdx,SupportIndexType tsIdx,IDType* pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = -1*( (spanIdx+1)*TS_ID_OFFSET + (tsIdx+1)*TS_ID_OFFSET/100 );
   return S_OK;
}

HRESULT GB_GetTemporarySupportGirderPointId(SpanIndexType spanIdx,SupportIndexType tsIdx,GirderIndexType gdrIdx,PositionType posType,IDType* pVal)
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

HRESULT GB_GetPierCLBridgePointId(PierIndexType pierIdx,IDType* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*BRIDGE_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetGirderLineId(SpanIndexType spanIdx,GirderIndexType gdrIdx,IDType* pVal)
{
   *pVal = -1*( (spanIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
              );

   return S_OK;
}

// function to deal with fractional and absolute values
Float64 GB_GetFracDistance(Float64 fracLoc, Float64 Length, bool ignoreTooBig)
{
   ATLASSERT(0.0 < Length);

   if (0.0 <= fracLoc)
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
      if (-1.0 <= fracLoc)
      {
         return -fracLoc*Length;
      }
      else
         throw frTooSmall;
   }

   ATLASSERT(false); //can't get here
   return 0.0;
}

HRESULT GB_GetSectionLocation(ISuperstructureMemberSegment* pSegment,Float64 distAlongSegment,IPoint2d** ppTopCenter)
{
   CComPtr<IGirderLine> gdrLine;
   pSegment->get_GirderLine(&gdrLine);

   CComPtr<IPath> gdrPath;
   gdrLine->get_Path(&gdrPath);

   Float64 brgOffset;
   gdrLine->get_BearingOffset(etStart,&brgOffset);
   
   Float64 endDist;
   gdrLine->get_EndDistance(etStart,&endDist);

   Float64 distAlongPath = distAlongSegment + brgOffset - endDist;

   CComPtr<IPoint2d> pnt;
   CComQIPtr<IPathElement> element(gdrPath);
   element->LocatePoint(distAlongPath,omtNormal,0.00,CComVariant(0),&pnt);
   Float64 x,y;
   pnt->Location(&x,&y);

   CComPtr<ISuperstructureMember> ssmbr;
   pSegment->get_SuperstructureMember(&ssmbr);

   CComPtr<IGenericBridge> bridge;
   ssmbr->get_Bridge(&bridge);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   IDType profileID, surfaceID;
   bridge->get_ProfileID(&profileID);
   bridge->get_SurfaceID(&surfaceID);

   CComPtr<IStation> station;
   Float64 offset;
   alignment->StationAndOffset(pnt,&station,&offset);

   CComPtr<IProfile> profile;
   alignment->GetProfile(profileID,&profile);

   Float64 elevation;
   profile->Elevation(surfaceID,CComVariant(station),offset,&elevation);

   Float64 elevation_offset = 0;
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);
   if ( deck )
   {
      Float64 gross_depth;
      deck->get_GrossDepth(&gross_depth);

      Float64 haunch;
      pSegment->ComputeHaunchDepth(distAlongSegment,&haunch);

      elevation_offset = gross_depth + haunch;
   }

   elevation -= elevation_offset;
   

   // If there is an overlay constructed with the bridge (not a future overlay)
   // then the top of the overlay is the finished grade elevation
   VARIANT_BOOL vbHasFutureOverlay;
   bridge->HasFutureOverlay(&vbHasFutureOverlay);
   StageIndexType wearingSurfaceStage;
   bridge->get_WearingSurfaceStage(&wearingSurfaceStage);
   if (wearingSurfaceStage != INVALID_INDEX && vbHasFutureOverlay == VARIANT_FALSE)
   {
      Float64 wearing_surface_depth;
      bridge->get_WearingSurfaceDepth(&wearing_surface_depth);
      elevation -= wearing_surface_depth;
   }

   CComPtr<IPoint2d> pntTopCenter;
   pntTopCenter.CoCreateInstance(CLSID_Point2d);
   pntTopCenter->Move(offset,elevation);

   return pntTopCenter.CopyTo(ppTopCenter);
}
