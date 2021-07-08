///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

#if defined USING_OPENBRIDGEML

#include <WBFLCogo\OpenBridgeML.h>
#include <WBFLUnitServer\OpenBridgeML.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::Alignment& obmlAlignment);
void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentPathType& obmlAlignmentPath);
void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::EquationsType& obmlAlignmentPathEquations);
void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::EquationType& obmlAlignmentPathEquation);
void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::ProfileType& obmlProfile);

BOOL GetProfile(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::ProfileType& obmlProfile,IProfile* pProfile);

BOOL CreateAlignmentsCollection(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentsType& obmlAlignments,IAlignmentCollection** ppAlignments)
{
   CComPtr<IAlignmentCollection> alignments;
   alignments.CoCreateInstance(CLSID_AlignmentCollection);

   GetAlignments(obmlUnitServer,pOurUnitServer,obmlAlignments,alignments);

   alignments.CopyTo(ppAlignments);
   return TRUE;
}

BOOL COGOFUNC GetAlignments(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentsType& obmlAlignments,IAlignmentCollection* pAlignments)
{
   CogoObjectID id = 0; 
   for(OpenBridgeML::Alignments::Alignment& obmlAlignment : obmlAlignments.Alignment())
   {
      CComPtr<IAlignment> alignment;
      if ( CreateAlignment(obmlUnitServer,pOurUnitServer,obmlAlignment,&alignment) )
      {
         pAlignments->AddEx(id++,alignment);
      }
   }
   return TRUE;
}

BOOL CreateAlignment(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::Alignment& obmlAlignment,IAlignment** ppAlignment)
{
   ConvertToOurUnits(obmlUnitServer,pOurUnitServer,obmlAlignment);

   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   Float64 startStation = obmlAlignment.Path().Station();
   alignment->put_RefStation(CComVariant(startStation));

   Float64 Sx = obmlAlignment.Path().Start().X();
   Float64 Sy = obmlAlignment.Path().Start().Y();
   CComPtr<IPoint2d> pntStart;
   pntStart.CoCreateInstance(CLSID_Point2d);
   pntStart->Move(Sx,Sy);
   alignment->AddEx(pntStart);

   Float64 Ex = obmlAlignment.Path().End().X();
   Float64 Ey = obmlAlignment.Path().End().Y();
   CComPtr<IPoint2d> pntEnd;
   pntEnd.CoCreateInstance(CLSID_Point2d);
   pntEnd->Move(Ex,Ey);

   OpenBridgeML::Alignments::AlignmentPathType::PI_const_iterator iter(obmlAlignment.Path().PI().begin());
   OpenBridgeML::Alignments::AlignmentPathType::PI_const_iterator iterEnd(obmlAlignment.Path().PI().end());
   for ( ; iter != iterEnd; iter++ )
   {
      const OpenBridgeML::Alignments::PointOfInterestionType& poi(*iter);
      Float64 X = poi.X();
      Float64 Y = poi.Y();
      CComPtr<IPoint2d> pntPI;
      pntPI.CoCreateInstance(CLSID_Point2d);
      pntPI->Move(X,Y);

      if ( poi.Radius().present() )
      {
         // There is a horizontal curve
         Float64 radius = poi.Radius().get();

         CComPtr<IPoint2d> pntPBT;
         CComPtr<IPoint2d> pntPFT;

         // Get the previous point
         IndexType nItems;
         alignment->get_Count(&nItems);
         CComPtr<IPathElement> pathElement;
         alignment->get_Item(nItems-1,&pathElement);
         PathElementType pathElementType;
         pathElement->get_Type(&pathElementType);
         CComPtr<IUnknown> punk;
         pathElement->get_Value(&punk);
         if ( pathElementType == petPoint )
         {
            punk->QueryInterface(&pntPBT);
         }
         else if ( pathElementType == petLineSegment )
         {
            ATLASSERT(false); // should never get here (not using this element type)
         }
         else if ( pathElementType == petCompoundCurve )
         {
            CComPtr<ICompoundCurve> hc;
            punk->QueryInterface(&hc);
            hc->get_PI(&pntPBT);
         }
         else if ( pathElementType == petCubicSpline )
         {
            ATLASSERT(false); // should never get here (not using this element type)
         }
         else
         {
            ATLASSERT(false); // should never get here (is there a new type?)
         }

         if ( iter != iterEnd-1 )
         {
            const OpenBridgeML::Alignments::PointOfInterestionType& nextPOI(*(iter+1));
            X = nextPOI.X();
            Y = nextPOI.Y();
            pntPFT.CoCreateInstance(CLSID_Point2d);
            pntPFT->Move(X,Y);
         }
         else
         {
            pntEnd->Clone(&pntPFT);
         }

         CComPtr<ICompoundCurve> hc;
         hc.CoCreateInstance(CLSID_CompoundCurve);
         hc->putref_PBT(pntPBT);
         hc->putref_PI(pntPI);
         hc->putref_PFT(pntPFT);
         hc->put_Radius(radius);

         if ( poi.EntrySpiralLength().present() )
         {
            hc->put_SpiralLength(spEntry,poi.EntrySpiralLength().get());
         }

         if ( poi.ExitSpiralLength().present() )
         {
            hc->put_SpiralLength(spExit,poi.ExitSpiralLength().get());
         }

         alignment->AddEx(hc);
      }
      else
      {
         alignment->AddEx(pntPI);
      }
   }

   alignment->AddEx(pntEnd);

   if ( obmlAlignment.Profile().present() )
   {
      CComPtr<IProfile> profile;
      alignment->get_Profile(&profile);
      GetProfile(obmlUnitServer,pOurUnitServer,obmlAlignment.Profile().get(),profile);
   }

   alignment.CopyTo(ppAlignment);

   return TRUE;
}

BOOL GetProfile(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::ProfileType& obmlProfile,IProfile* pProfile)
{
   OpenBridgeML::Alignments::ProfileType::ProfilePoint_iterator ppIter(obmlProfile.ProfilePoint().begin());
   OpenBridgeML::Alignments::ProfileType::ProfilePoint_iterator ppIterEnd(obmlProfile.ProfilePoint().end());
   OpenBridgeML::Alignments::ProfilePointType& prevProfilePoint(*ppIter++);

   CComPtr<IProfilePoint> pp;
   pp.CoCreateInstance(CLSID_ProfilePoint);
   pp->put_Station(CComVariant(prevProfilePoint.Station()));
   pp->put_Elevation(prevProfilePoint.Elevation());
   pProfile->AddEx(pp);

   for ( ; ppIter != ppIterEnd; ppIter++ )
   {
      OpenBridgeML::Alignments::ProfilePointType& thisProfilePoint(*ppIter);
      Float64 thisStation = thisProfilePoint.Station();
      Float64 thisElevation = thisProfilePoint.Elevation();
      Float64 thisGrade = thisProfilePoint.Grade();

      Float64 prevStation = prevProfilePoint.Station();
      Float64 prevElevation = prevProfilePoint.Elevation();
      Float64 prevGrade = prevProfilePoint.Grade();

      Float64 expectedElevation = (thisStation - prevStation)*prevGrade + prevElevation;
      if ( !IsEqual(expectedElevation,thisElevation) )
      {
         // There is a vertical "jump" in the profile... model two profile points here and not a VC
         CComPtr<IProfilePoint> pp;
         pp.CoCreateInstance(CLSID_ProfilePoint);
         pp->put_Station(CComVariant(thisStation));
         pp->put_Elevation(expectedElevation);
         pProfile->AddEx(pp);

         pp.Release();
         pp.CoCreateInstance(CLSID_ProfilePoint);
         pp->put_Station(CComVariant(thisStation));
         pp->put_Elevation(thisElevation);
         pProfile->AddEx(pp);
      }
      else if ( IsEqual(prevStation,thisStation) )
      {
         // There is a grade break... model a profile points here and not a VC
         CComPtr<IProfilePoint> pp;
         pp.CoCreateInstance(CLSID_ProfilePoint);
         pp->put_Station(CComVariant(thisStation));
         pp->put_Elevation(thisElevation);
         pProfile->AddEx(pp);
      }
      else
      {
         // Model a vertical curve between profile points
         CComPtr<IVertCurve> vc;
         vc.CoCreateInstance(CLSID_VertCurve);
         vc->put_ComputeFromGradePoints(VARIANT_TRUE);
         CComPtr<IProfilePoint> bvc, evc;
         bvc.CoCreateInstance(CLSID_ProfilePoint);
         bvc->put_Station(CComVariant(prevStation));
         bvc->put_Elevation(prevElevation);
         
         evc.CoCreateInstance(CLSID_ProfilePoint);
         evc->put_Station(CComVariant(thisStation));
         evc->put_Elevation(thisElevation);

         // We have to set the bvc and evc as the PBG and PFG points and 
         // input the entry and exitfor this input method.
         vc->putref_PBG(bvc);
         vc->put_EntryGrade(prevGrade);

         vc->putref_PFG(evc);
         vc->put_ExitGrade(thisGrade);

         pProfile->AddEx(vc);
      }

      prevProfilePoint = thisProfilePoint;
   }

   return TRUE;
}

void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::Alignment& obmlAlignment)
{
   // Alignment Path
   ConvertToOurUnits(obmlUnitServer,pOurUnitServer,obmlAlignment.Path());

   // Profile
   if ( obmlAlignment.Profile().present() )
   {
      ConvertToOurUnits(obmlUnitServer,pOurUnitServer,obmlAlignment.Profile().get());
   }

   // Surfaces
}

void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::AlignmentPathType& obmlAlignmentPath)
{
   ConvertBetweenBaseUnits(obmlAlignmentPath.Station(), obmlUnitServer, pOurUnitServer);

   ConvertBetweenBaseUnits(obmlAlignmentPath.Start().X(), obmlUnitServer, pOurUnitServer);
   ConvertBetweenBaseUnits(obmlAlignmentPath.Start().Y(), obmlUnitServer, pOurUnitServer);

   for (OpenBridgeML::Alignments::PointOfInterestionType& poi : obmlAlignmentPath.PI())
   {
      ConvertBetweenBaseUnits(poi.X(), obmlUnitServer, pOurUnitServer);
      ConvertBetweenBaseUnits(poi.Y(), obmlUnitServer, pOurUnitServer);
      if ( poi.Radius().present() )
      {
         ConvertBetweenBaseUnits(poi.Radius().get(), obmlUnitServer, pOurUnitServer);
      }

      if ( poi.EntrySpiralLength().present() )
      {
         ConvertBetweenBaseUnits(poi.EntrySpiralLength().get(), obmlUnitServer, pOurUnitServer);
      }

      if ( poi.ExitSpiralLength().present() )
      {
         ConvertBetweenBaseUnits(poi.ExitSpiralLength().get(), obmlUnitServer, pOurUnitServer);
      }
   }

   ConvertBetweenBaseUnits(obmlAlignmentPath.End().X(), obmlUnitServer, pOurUnitServer);
   ConvertBetweenBaseUnits(obmlAlignmentPath.End().Y(), obmlUnitServer, pOurUnitServer);

   // Equations
   if ( obmlAlignmentPath.Equations().present() )
   {
      ConvertToOurUnits(obmlUnitServer,pOurUnitServer,obmlAlignmentPath.Equations().get());
   }
}

void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::EquationsType& obmlAlignmentPathEquations)
{
   for(OpenBridgeML::Alignments::EquationType& equation : obmlAlignmentPathEquations.Equation())
   {
      ConvertToOurUnits(obmlUnitServer,pOurUnitServer,equation);
   }
}

void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::EquationType& obmlAlignmentPathEquation)
{
   ConvertBetweenBaseUnits(obmlAlignmentPathEquation.BackStation(), obmlUnitServer, pOurUnitServer);
   ConvertBetweenBaseUnits(obmlAlignmentPathEquation.AheadStation(), obmlUnitServer, pOurUnitServer);
}

void ConvertToOurUnits(IUnitServer* obmlUnitServer,IUnitServer* pOurUnitServer,OpenBridgeML::Alignments::ProfileType& obmlProfile)
{
#pragma Reminder("IMPLEMENT")
}

#endif USING_OPENBRIDGEML
