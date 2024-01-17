///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include "TensionStressPlaneModel.h"

gbtAlternativeTensileStressRequirements::gbtAlternativeTensileStressRequirements()
{
   fy = 0;
   bLimitBarStress = true;
   fsMax = 0;
   concreteType = WBFL::Materials::ConcreteType::Normal;
   fc = 0;
   bHasFct = false;
   Fct = 0;
   density = 0;
   bAdjustForDevelopmentLength = true;
   Ytg = 0;

   Yna = 0;
   NAslope = 0;
   AreaTension = 0;
   T = 0;
   AsProvided = 0;
   AsRequired = 0;
   bIsAdequateRebar = false;
}


void gbtComputeAlternativeStressRequirements(gbtAlternativeTensileStressRequirements* pRequirements)
{
   // Determine neutral axis location and mild steel requirement for alternative tensile stress

   // Shape must be in Centroidal/Stress Point coordinates

   typedef enum { slAllTens, slAllComp, slOther } StressLocation;
   StressLocation stressLoc;
   pRequirements->Yna = -1;
   pRequirements->NAslope = 0;

   // Get stress in the stress at the four control points
   Float64 fTopLeft = pRequirements->pntTopLeft.Z();
   Float64 fTopRight = pRequirements->pntTopRight.Z();
   Float64 fBotLeft = pRequirements->pntBottomLeft.Z();
   Float64 fBotRight = pRequirements->pntBottomRight.Z();

   // Determine maximum bar stress for computing higher allowable temporary tensile (5.9.4.1.2)
   Float64 allowable_bar_stress = 0.5*pRequirements->fy;
   if (pRequirements->bLimitBarStress && pRequirements->fsMax < allowable_bar_stress)
   {
      allowable_bar_stress = pRequirements->fsMax;
   }
   ATLASSERT(!IsZero(allowable_bar_stress));

   // Evaluate the state of stress
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
      // no stress anywhere
      pRequirements->Yna = 0;
   }
   else
   {
      // get two points on the neutral axis line by evaluating at x1 and x2 with a stress (z) of 0.0
      x1 = pRequirements->pntTopLeft.X();
      stressPlane->GetY(x1, 0.0, &y1);
      x2 = pRequirements->pntTopRight.X();
      stressPlane->GetY(x2, 0.0, &y2);

      // compute slope of neutral axis
      Float64 slope = IsZero(x2 - x1) ? Float64_Max : (y2 - y1) / (x2 - x1);
      pRequirements->NAslope = IsZero(slope) ? 0 : slope;

      // depth of neutral axis from top of girder
      // neutral axis line in y=m*x+b form
      // y1 = m*x1 + b, rearranging b = y1 - m*x1
      Float64 b = y1 - (pRequirements->NAslope)*x1;
      pRequirements->Yna = b; // this is Y at vertical line passing through center of bounding box in CG coordinates
      pRequirements->Yna -= pRequirements->Ytg; // convert to girder section coordinates (now measured from 0,0 at top center of bounding box)
   }
                              
   // Compute area of concrete in tension and total tension
   Float64 AreaTens; // area of concrete in tension
   Float64 T;        // tension force in concrete
   if (stressLoc == slAllComp)
   {
      // Compression over entire cross section
      AreaTens = 0.0;
      T = 0.0;
   }
   else
   {
      if (stressLoc == slAllTens)
      {
         // Tension over entire cross section
         CComPtr<IShapeProperties> shapeProps;
         pRequirements->shape->get_ShapeProperties(&shapeProps);
         shapeProps->get_Area(&AreaTens);
         pRequirements->tensionArea = pRequirements->shape;
      }
      else
      {
         // Portion of section in tension
         // Clip shape with neutral axis line to determine concrete tension area
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
         Float64 Z; // stress at X,Y
         stressPlane->GetZ(X, Y, &Z);
         if (0 < Z)
         {
            // tension is on the left, we need tension on the right because we want to retain the tension area
            // reverse the clipping line
            line->Reverse();
         }

         // get angle of neutral axis
         CComPtr<IPoint2d> pnt;
         CComPtr<IVector2d> v;
         line->GetExplicit(&pnt, &v);
         Float64 vx, vy;
         v->get_X(&vx);
         v->get_Y(&vy);
         ATLASSERT(IsEqual(pRequirements->NAslope, IsZero(vx) ? Float64_Max : vy / vx));

         CComPtr<IShape> clipped_shape;
         pRequirements->shape->ClipWithLine(line, &clipped_shape); // retains the shape on the right side of the clipping line
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
      }

      if (pRequirements->tensionArea)
      {
         // because the cross section is not a simple rectangle, as suggested in LRFD C5.9.2.3.1b, we have to numerically
      // integrate the stress over the cross section. The WBFL::RCCapacity library, General Section service, has this capability
      // however it uses a strain plane and a stress-strain model. We can fake it out be using the stress plane as the strain
         // plane and creating a stress-strain model that simply coverts the "strain" to a stress by returning the provided "strain"
      // See CTensionStressPlaneModel for more details.
         CComObject<CTensionStressPlaneModel>* pMaterialModel;
         CComObject<CTensionStressPlaneModel>::CreateInstance(&pMaterialModel);

         CComPtr<IStressStrain> ssModel;
         pMaterialModel->QueryInterface(&ssModel);

         CComPtr<IGeneralSection> generalSection;
         generalSection.CoCreateInstance(CLSID_GeneralSection);

         //generalSection->AddShape(pRequirements->shape, ssModel, nullptr, 0, 1.0); // no need to use full shape when we have the tension side shape
         generalSection->AddShape(CComBSTR(""),pRequirements->tensionArea, ssModel, nullptr, nullptr, 1.0, VARIANT_TRUE); // use the tension side shape

         CComPtr<IGeneralSectionSolver> solver;
         solver.CoCreateInstance(CLSID_GeneralSectionSolver);

         solver->put_Slices(5); // we are using the tension side shape, so we don't need too many slices
         solver->put_SliceGrowthFactor(0.25); // start with small slices on the tension side and then grow as they move to the compression side (tension is going to zero so it has a smaller contribution per slice)
         solver->putref_Section(generalSection);
         CComPtr<IGeneralSectionSolution> solution;
         solver->Solve(stressPlane, &solution);

         solution->get_TensionResultant(&T);

         pRequirements->tensionForceSolution = solution;

#if defined _DEBUG
         // validate the sum of the slice areas in tension are equal to the
         // total area on the tension side of the neutral axis
         Float64 At = 0;
         IndexType nSlices;
         solution->get_SliceCount(&nSlices);
         for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
         {
            CComPtr<IGeneralSectionSlice> slice;
            solution->get_Slice(sliceIdx, &slice);
            Float64 slice_area;
            slice->get_Area(&slice_area);

            Float64 f;
            slice->get_ForegroundStress(&f);
            if (0 < f)
            {
               At += slice_area;
            }
         }
         ATLASSERT(IsEqual(At, AreaTens));
#endif // _DEBUG
      }
      else
      {
         T = 0;
      }
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
         WBFL::Materials::Rebar::Size size = WBFL::LRFD::RebarPool::GetBarSize(OLE2CT(name));

         Float64 dev_length_factor = 1.0;
         if (pRequirements->bAdjustForDevelopmentLength)
         {
            // Adjust bar area for development
            auto devLengthDetails = WBFL::LRFD::Rebar::GetRebarDevelopmentLengthDetails(size, Ab, db, pRequirements->fy, pRequirements->concreteType, pRequirements->fc, pRequirements->bHasFct, pRequirements->Fct, pRequirements->density,false,false,true);

            // Get distances from section cut to ends of bar
            Float64 start, end;
            rebarSectionItem->get_LeftExtension(&start);
            rebarSectionItem->get_RightExtension(&end);

            Float64 cut_length = Min(start, end);
            Float64 fra = cut_length / devLengthDetails.ld;
            fra = Min(fra, 1.0);
            dev_length_factor = fra;
         }

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
            y += pRequirements->Ytg;

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

   if (pRequirements->tensionForceSolution)
   {
      // In the solution space, the slices are rotated so they are aligned with the
      // neutral axis. Rotate them back to the centroidal coordinate system
      Float64 neutral_axis_angle;
      pRequirements->tensionForceSolution->get_NeutralAxisDirection(&neutral_axis_angle);
      IndexType nSlices;
      pRequirements->tensionForceSolution->get_SliceCount(&nSlices);
      for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
      {
         CComPtr<IGeneralSectionSlice> slice;
         pRequirements->tensionForceSolution->get_Slice(sliceIdx, &slice);
         CComPtr<IShape> shape;
         slice->get_Shape(&shape);
         CComQIPtr<IXYPosition> position(shape);
         position->Rotate(0.0, 0.0, neutral_axis_angle);
      }
   }


#if defined _DEBUG
   if (stressLoc != slAllTens && stressLoc != slAllComp && IsEqual(fTopLeft, fTopRight) && IsEqual(fBotLeft, fBotRight))
   {
      // if left/right stresses are the same, we have uniaxial bending
      // therefore, the slope of the neutral axis must be zero
      ATLASSERT(IsZero(pRequirements->NAslope));
   }
#endif // _DEBUG
}