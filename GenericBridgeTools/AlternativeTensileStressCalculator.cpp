///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include <WBFLGenericBridgeTools\AlternativeTensileStressCalculator.h>

#include <Lrfd\Details.h>
#include <Lrfd\RebarPool.h>
#include <Lrfd\Rebar.h>

#include <WBFLGenericBridge.h>

#include <MathEx.h>

gbtAlternativeTensileStressRequirements::gbtAlternativeTensileStressRequirements()
{
   fy = 0;
   bLimitBarStress = true;
   fsMax = 0;
   concreteType = matConcrete::Normal;
   fc = 0;
   bHasFct = false;
   Fct = 0;
   density = 0;;

   Yna = 0;
   NAslope = 0;
   AreaTension = 0;
   T = 0;
   AsProvided = 0;
   AsRequired = 0;
   bIsAdequateRebar = false;
}

gbtAlternativeTensileStressRequirements::gbtAlternativeTensileStressRequirements(const gbtAlternativeTensileStressRequirements& other)
{
   fy = other.fy;
   bLimitBarStress = other.bLimitBarStress;
   fsMax = other.fsMax;
   concreteType = other.concreteType;
   fc = other.fc;
   bHasFct = other.bHasFct;
   Fct = other.Fct;
   density = other.density;

   shape = other.shape;
   rebarSection = other.rebarSection;
   pntTopLeft = other.pntTopLeft;
   pntTopRight = other.pntTopRight;
   pntBottomLeft = other.pntBottomLeft;
   pntBottomRight = other.pntBottomRight;

   tensionArea = other.tensionArea;
   Yna = other.Yna;
   NAslope = other.NAslope;
   AreaTension = other.AreaTension;
   T = other.T;
   AsProvided = other.AsProvided;
   AsRequired = other.AsRequired;
   bIsAdequateRebar = other.bIsAdequateRebar;
}

void gbtAlternativeTensileStressRequirements::operator=(const gbtAlternativeTensileStressRequirements& other)
{
   fy = other.fy;
   bLimitBarStress = other.bLimitBarStress;
   fsMax = other.fsMax;
   concreteType = other.concreteType;
   fc = other.fc;
   bHasFct = other.bHasFct;
   Fct = other.Fct;
   density = other.density;

   shape = other.shape;
   rebarSection = other.rebarSection;
   pntTopLeft = other.pntTopLeft;
   pntTopRight = other.pntTopRight;
   pntBottomLeft = other.pntBottomLeft;
   pntBottomRight = other.pntBottomRight;

   tensionArea = other.tensionArea;
   Yna = other.Yna;
   NAslope = other.NAslope;
   AreaTension = other.AreaTension;
   T = other.T;
   AsProvided = other.AsProvided;
   AsRequired = other.AsRequired;
   bIsAdequateRebar = other.bIsAdequateRebar;
}


void gbtComputeAlternativeStressRequirements(gbtAlternativeTensileStressRequirements* pRequirements)
{
   // Determine neutral axis location and mild steel requirement for alternative tensile stress

   // Shape must be in Centroidal/Stress Point coordinates

   typedef enum { slAllTens, slAllComp, slOther } StressLocation;
   StressLocation stressLoc;
   pRequirements->Yna = -1;
   pRequirements->NAslope = 0;

   Float64 fTopLeft = pRequirements->pntTopLeft.Z();
   Float64 fTopRight = pRequirements->pntTopRight.Z();
   Float64 fBotLeft = pRequirements->pntBottomLeft.Z();
   Float64 fBotRight = pRequirements->pntBottomRight.Z();

   // Max bar stress for computing higher allowable temporary tensile (5.9.4.1.2)
   Float64 allowable_bar_stress = 0.5*pRequirements->fy;
   if (pRequirements->bLimitBarStress && pRequirements->fsMax < allowable_bar_stress)
   {
      allowable_bar_stress = pRequirements->fsMax;
   }
   ATLASSERT(!IsZero(allowable_bar_stress));

   if (::IsLE(fTopLeft, 0.0) && ::IsLE(fTopRight, 0.0) && ::IsLE(fBotLeft, 0.0) && ::IsLE(fBotRight, 0.0))
   {
      // compression over entire cross section
      stressLoc = slAllComp;
   }
   else if (::IsLT(0.0, fTopLeft) && ::IsLT(0.0, fTopRight) && ::IsLT(0.0, fBotLeft) && ::IsLT(0.0, fBotRight))
   {
      // tension over entire cross section
      stressLoc = slAllTens;
   }
   else
   {
      stressLoc = slOther;
   }

   CComQIPtr<IXYPosition> position(pRequirements->shape);
   CComPtr<IPoint2d> pntTC;
   position->get_LocatorPoint(lpTopCenter, &pntTC);
   Float64 Xtc, Ytc;
   pntTC->Location(&Xtc, &Ytc);

   // use a 3d plane to determine the neutral axis
   CComPtr<IPlane3d> stressPlane;
   stressPlane.CoCreateInstance(CLSID_Plane3d);

   CComPtr<IPoint3d> p1, p2, p3;
   p1.CoCreateInstance(CLSID_Point3d);
   p2.CoCreateInstance(CLSID_Point3d);
   p3.CoCreateInstance(CLSID_Point3d);
   p1->Move(pRequirements->pntTopLeft.X(), pRequirements->pntTopLeft.Y(), pRequirements->pntTopLeft.Z());
   p2->Move(pRequirements->pntTopRight.X(), pRequirements->pntTopRight.Y(), pRequirements->pntTopRight.Z());
   p3->Move(pRequirements->pntBottomLeft.X(), pRequirements->pntBottomLeft.Y(), pRequirements->pntBottomLeft.Z());
   stressPlane->ThroughPoints(p1, p2, p3);

   Float64 x1(0), y1(0), x2(0), y2(0);
   if (IsZero(fTopLeft) && IsZero(fTopRight) && IsZero(fBotLeft) && IsZero(fBotRight))
   {
      pRequirements->Yna = 0;
   }
   else
   {
      x1 = pRequirements->pntTopLeft.X();
      stressPlane->GetY(x1, 0, &y1);
      x2 = pRequirements->pntTopRight.X();
      stressPlane->GetY(x2, 0, &y2);

      Float64 slope = IsZero(x2 - x1) ? Float64_Max : (y2 - y1) / (x2 - x1);
      pRequirements->NAslope = IsZero(slope) ? 0 : slope;

      // depth of neutral axis
      // neutral asxis line in y=mx+b form
      // y1 = mx1 + b... b = y1 - mx1
      Float64 b = y1 - (pRequirements->NAslope)*x1;
      pRequirements->Yna = (pRequirements->NAslope)*Xtc + b; // this is Y at vertical line passing through center of bounding box in CG coordinates
      pRequirements->Yna -= Ytc; // convert to girder section coordinates (now measured from 0,0 at top center of bounding box)
   }
                              
                              // Compute area on concrete in tension and total tension
   Float64 AreaTens; // area of concrete in tension
   Float64 T;        // tension force in concrete
   if (stressLoc == slAllComp)
   {
      // Compression over entire cross section
      AreaTens = 0.0;
      T = 0.0;
   }
   else if (stressLoc == slAllTens)
   {
      // Tension over entire cross section
      CComPtr<IShapeProperties> shapeProps;
      pRequirements->shape->get_ShapeProperties(&shapeProps);
      shapeProps->get_Area(&AreaTens);

      Float64 fAvg = (Max(fTopLeft, fTopRight, fBotLeft, fBotRight) + Min(fTopLeft, fTopRight, fBotLeft, fBotRight)) / 2;
      T = fAvg * AreaTens;

      ATLASSERT(T != 0);
   }
   else
   {
      // Clip shape to determine concrete tension area

      CComPtr<IPoint2d> pnt1, pnt2;
      pnt1.CoCreateInstance(CLSID_Point2d);
      pnt2.CoCreateInstance(CLSID_Point2d);
      pnt1->Move(x1, y1);
      pnt2->Move(x2, y2);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pnt1, pnt2);
      Float64 C;
      CComPtr<IVector2d> vN; // normal vector points to the left hand side of the line
      line->GetImplicit(&C, &vN);
      Float64 dx, dy;
      vN->get_X(&dx);
      vN->get_Y(&dy);

      // create a point to the left of the clipping line
      Float64 Offset = 10;
      Float64 X = x1 + Offset*dx;
      Float64 Y = y1 + Offset*dy;
      Float64 Z;
      stressPlane->GetZ(X, Y, &Z);
      if (0 < Z)
      {
         // compression is on the left, we need tension on the left... reverse the clipping line
         line->Reverse();
      }

      // get angle of neutral axis
      CComPtr<IPoint2d> pnt;
      CComPtr<IVector2d> v;
      line->GetExplicit(&pnt, &v);
      Float64 vx, vy;
      v->get_X(&vx);
      v->get_Y(&vy);
      ATLASSERT(IsEqual(pRequirements->NAslope,IsZero(vx)?Float64_Max:vy/vx));

      Float64 fAvg = Max(fTopLeft, fTopRight, fBotLeft, fBotRight) / 2;

      CComPtr<IShape> clipped_shape;
      pRequirements->shape->ClipWithLine(line, &clipped_shape);
      pRequirements->tensionArea = clipped_shape;

      if (clipped_shape)
      {
         CComPtr<IShapeProperties> clippedShapeProps;
         clipped_shape->get_ShapeProperties(&clippedShapeProps);

         clippedShapeProps->get_Area(&AreaTens);
      }
      else
      {
         ATLASSERT(false); // the clipping line should leave a shape
         AreaTens = 0.0;
      }

      T = fAvg * AreaTens;
   }

   // Area of steel required to meet higher tensile stress requirement
   Float64 AsReqd = T / allowable_bar_stress;
   ATLASSERT(0 <= AsReqd);

   // Compute area of rebar actually provided in tension zone. Reduce values for development
   Float64 AsProvd = 0.0; // As provided
   if (stressLoc == slAllComp)
   {
      AsReqd = -1;
   }
   else
   {
      CComPtr<IEnumRebarSectionItem> enumItems;
      pRequirements->rebarSection->get__EnumRebarSectionItem(&enumItems);

      CComPtr<IRebarSectionItem> rebarSectionItem;
      while (enumItems->Next(1, &rebarSectionItem, nullptr) != S_FALSE)
      {
         CComPtr<IRebar> rebar;
         rebarSectionItem->get_Rebar(&rebar);

         Float64 Ab, db, fy;
         rebar->get_NominalArea(&Ab);
         rebar->get_NominalDiameter(&db);
         rebar->get_YieldStrength(&fy);

         ATLASSERT(IsEqual(fy, pRequirements->fy));

         CComBSTR name;
         rebar->get_Name(&name);
         matRebar::Size size = lrfdRebarPool::GetBarSize(OLE2CT(name));

         // Adjust bar area for development
         REBARDEVLENGTHDETAILS devLengthDetails = lrfdRebar::GetRebarDevelopmentLengthDetails(size, Ab, db, pRequirements->fy, pRequirements->concreteType, pRequirements->fc, pRequirements->bHasFct, pRequirements->Fct, pRequirements->density);

         // Get distances from section cut to ends of bar
         Float64 start, end;
         rebarSectionItem->get_LeftExtension(&start);
         rebarSectionItem->get_RightExtension(&end);

         Float64 dev_length_factor;
         Float64 cut_length = Min(start, end);
         Float64 fra = cut_length / devLengthDetails.ldb;
         fra = Min(fra, 1.0);
         dev_length_factor = fra;

         Ab *= dev_length_factor;

         if (stressLoc == slAllTens)
         {
            // all bars in tension - just add
            AsProvd += Ab;
         }
         else
         {
            CComPtr<IPoint2d> location;
            rebarSectionItem->get_Location(&location);

            Float64 x, y;
            location->Location(&x, &y); // in girder section coordinates (0,0 at top center)
                                        // put the bar into centroid coordinates
            x += Xtc;
            y += Ytc;

            Float64 z;
            stressPlane->GetZ(x, y, &z);

            if (::IsLE(0.0, z))
            {
               // if z is > 0 bar is on the tension side of neutral axis
               AsProvd += Ab;
            }
         }

         rebarSectionItem.Release();
      }
   }

   if (stressLoc == slAllComp)
   {
      pRequirements->bIsAdequateRebar = true;
   }
   else
   {
      pRequirements->bIsAdequateRebar = (::IsLE(AsReqd, AsProvd, 0.000001) ? true : false);
   }

   pRequirements->AreaTension = AreaTens;
   pRequirements->T = T;
   pRequirements->AsProvided = AsProvd;
   pRequirements->AsRequired = AsReqd;

#if defined _DEBUG
   if (stressLoc != slAllTens && stressLoc != slAllComp && IsEqual(fTopLeft, fTopRight) && IsEqual(fBotLeft, fBotRight))
   {
      // if left/right stresses are the same, we have uniaxial bending
      // therefore, the slope of the neutral axis must be zero
      ATLASSERT(IsZero(pRequirements->NAslope));
   }
#endif // _DEBUG
}