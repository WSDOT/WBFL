///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>

#include <initguid.h>
#include <WBFLGeometry_i.c>

#include <Lrfd\AlternativeTensileStressCalculator.h>
#include <Lrfd\Details.h>
#include <Lrfd\RebarPool.h>
#include <Lrfd\Rebar.h>

/****************************************************************************
CLASS
   lrfdAlternativeTensileStressCalculator
****************************************************************************/

lrfdAlternativeTensileStressCalculator::lrfdAlternativeTensileStressCalculator(const matConcrete& concrete,Float64 fy,bool bLimitBarStress,Float64 fsMax)
{
   m_Concrete = concrete;

   m_fy = fy;

   m_bLimitBarStress = bLimitBarStress;
   m_fsMax = fsMax;
}

void lrfdAlternativeTensileStressCalculator::SetReinforcementYieldStrength(Float64 fy)
{
   m_fy = fy;
}

Float64 lrfdAlternativeTensileStressCalculator::GetReinforcementYieldStrength() const
{
   return m_fy;
}

void lrfdAlternativeTensileStressCalculator::LimitBarStress(bool bLimit)
{
   m_bLimitBarStress = bLimit;
}

bool lrfdAlternativeTensileStressCalculator::LimitBarStress() const
{
   return m_bLimitBarStress;
}

void lrfdAlternativeTensileStressCalculator::SetBarStressLimit(Float64 fsMax)
{
   m_fsMax = fsMax;
}

Float64 lrfdAlternativeTensileStressCalculator::GetBarStressLimit() const
{
   return m_fsMax;
}

void lrfdAlternativeTensileStressCalculator::SetConcrete(const matConcrete& concrete)
{
   m_Concrete = concrete;
}

const matConcrete& lrfdAlternativeTensileStressCalculator::GetConcrete() const
{
   return m_Concrete;
}

void lrfdAlternativeTensileStressCalculator::ComputeAlternativeStressRequirements(IShape* pShape,IRebarSection* pRebarSection,
                                        Float64 Wtop,Float64 Wbot,
                                        Float64 fTopLeft, Float64 fTopRight, Float64 fBotLeft, Float64 fBotRight,
                                        Float64 *pYna, Float64* pNAslope, Float64 *pAreaTens, Float64 *pT, 
                                        Float64 *pAsProvd, Float64 *pAsReqd, bool* pbIsAdequateRebar)
{
   // Determine neutral axis location and mild steel requirement for alternative tensile stress
   typedef enum {slAllTens, slAllComp, slOther} StressLocation;
   StressLocation stressLoc;
   *pYna = -1;
   *pNAslope = -1;

   CComPtr<IShapeProperties> shapeProps;
   pShape->get_ShapeProperties(&shapeProps);
   Float64 Ytop, Ybot;
   shapeProps->get_Ytop(&Ytop);
   shapeProps->get_Ybottom(&Ybot);

   Float64 H = Ybot + Ytop;

   // Max bar stress for computing higher allowable temporary tensile (5.9.4.1.2)
   Float64 allowable_bar_stress = 0.5*m_fy;
   if ( m_bLimitBarStress && m_fsMax < allowable_bar_stress )
   {
       allowable_bar_stress = m_fsMax;
   }
   ATLASSERT(!IsZero(allowable_bar_stress));

   if ( ::IsLE(fTopLeft,0.0) && ::IsLE(fTopRight,0.0) && ::IsLE(fBotLeft,0.0) && ::IsLE(fBotRight,0.0) )
   {
      // compression over entire cross section
      stressLoc = slAllComp;
   }
   else if ( ::IsLT(0.0,fTopLeft) && ::IsLT(0.0,fTopRight) && ::IsLT(0.0,fBotLeft) && ::IsLT(0.0,fBotRight) )
   {
       // tension over entire cross section
      stressLoc = slAllTens;
   }
   else
   {
      stressLoc = slOther;
   //   ATLASSERT( BinarySign(fBot) != BinarySign(fTop) );

   //   stressLoc = 0.0 <= fBot ? slBotTens : slTopTens;

   //   // Location of neutral axis from Bottom of Girder/Deck
   //   Yna = (IsZero(fBot) ? 0 : H - (fTop*H/(fTop-fBot)) );

   //   ATLASSERT( 0 <= Yna );
   }

   // Compute area on concrete in tension and total tension
   Float64 AreaTens; // area of concrete in tension
   Float64 T;        // tension force in concrete
   CComPtr<IPlane3d> stressPlane;
   if ( stressLoc == slAllComp )
   {
       // Compression over entire cross section
      AreaTens = 0.0;
      T = 0.0;
   }
   else if ( stressLoc == slAllTens )
   {
      // Tension over entire cross section
      shapeProps->get_Area(&AreaTens);

      Float64 fAvg = (Max(fTopLeft,fTopRight,fBotLeft,fBotRight) + Min(fTopLeft,fTopRight,fBotLeft,fBotRight))/2;
      T = fAvg * AreaTens;

      ATLASSERT( T != 0 );
   }
   else
   {
      // Clip shape to determine concrete tension area
      
      // use a 3d plane to determine the neutral axis
      stressPlane.CoCreateInstance(CLSID_Plane3d);

      CComQIPtr<IXYPosition> position(pShape);
      CComPtr<IPoint3d> p1,p2,p3;
      p1.CoCreateInstance(CLSID_Point3d);
      p2.CoCreateInstance(CLSID_Point3d);
      p3.CoCreateInstance(CLSID_Point3d);
      if ( Wtop < Wbot )
      {
         CComPtr<IPoint2d> tc,bl,br;
         position->get_LocatorPoint(lpTopCenter,&tc);
         position->get_LocatorPoint(lpBottomLeft,&bl);
         position->get_LocatorPoint(lpBottomRight,&br);

         Float64 fTop = (fTopLeft + fTopRight)/2;
         Float64 x,y;
         tc->Location(&x,&y);
         p1->Move(x,y,fTop);

         bl->Location(&x,&y);
         p2->Move(x,y,fBotLeft);

         br->Location(&x,&y);
         p3->Move(x,y,fBotRight);
      }
      else
      {
         CComPtr<IPoint2d> tl,tr,bc;
         position->get_LocatorPoint(lpTopLeft,&tl);
         position->get_LocatorPoint(lpTopRight,&tr);
         position->get_LocatorPoint(lpBottomCenter,&bc);

         Float64 fBot = (fBotLeft + fBotRight)/2;
         Float64 x,y;
         bc->Location(&x,&y);
         p1->Move(x,y,fBot);

         tl->Location(&x,&y);
         p2->Move(x,y,fTopLeft);

         tr->Location(&x,&y);
         p3->Move(x,y,fTopRight);
      }

      stressPlane->ThroughPoints(p1,p2,p3);

      CComPtr<IPoint2d> tl,tr;
      position->get_LocatorPoint(lpTopLeft,&tl);
      position->get_LocatorPoint(lpTopRight,&tr);
      Float64 x1;
      tl->get_X(&x1);
      Float64 y1;
      stressPlane->GetY(x1,0,&y1);
      Float64 x2;
      tr->get_X(&x2);
      Float64 y2;
      stressPlane->GetY(x2,0,&y2);

      CComPtr<IPoint2d> pnt1,pnt2;
      pnt1.CoCreateInstance(CLSID_Point2d);
      pnt2.CoCreateInstance(CLSID_Point2d);
      pnt1->Move(x1,y1);
      pnt2->Move(x2,y2);
      
      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pnt1,pnt2);
      Float64 C;
      CComPtr<IVector2d> vN; // normal vector points to the left hand side of the line
      line->GetImplicit(&C,&vN);
      Float64 dx,dy;
      vN->get_X(&dx);
      vN->get_Y(&dy);

      // create a point to the left of the clipping line
      Float64 Offset = 10;
      Float64 X = x1 + Offset*dx;
      Float64 Y = y1 + Offset*dy;
      Float64 Z;
      stressPlane->GetZ(X,Y,&Z);
      if ( Z < 0 )
      {
         // compression is on the left, we need tension on the left... reverse the clipping line
         line->Reverse();
      }

      // depth of neutral axis
      CComPtr<IPoint2d> center;
      position->get_LocatorPoint(lpCenterCenter,&center);
      Float64 x;
      center->get_X(&x);
      stressPlane->GetY(x,0.0,pYna);

      // get angle of neutral axis
      CComPtr<IPoint2d> pnt;
      CComPtr<IVector2d> v;
      line->GetExplicit(&pnt,&v);
      v->get_Direction(pNAslope);
      if ( IsEqual(TWO_PI,*pNAslope) )
      {
         *pNAslope = 0;
      }

      if ( M_PI <= *pNAslope )
      {
         *pNAslope -= M_PI;
      }

      *pNAslope = IsZero(*pNAslope) ? 0 : *pNAslope;
      
      Float64 fAvg = Max(fTopLeft,fTopRight,fBotLeft,fBotRight)/2;

      CComPtr<IShape> clipped_shape;
      pShape->ClipWithLine(line,&clipped_shape);

      if ( clipped_shape )
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


      ATLASSERT( !::IsZero(T) );
   }

   // Area of steel required to meet higher tensile stress requirement
   Float64 AsReqd = T/allowable_bar_stress;
   ATLASSERT( 0 <= AsReqd );

   CComQIPtr<IXYPosition> position(pShape);
   CComPtr<IPoint2d> tc;
   position->get_LocatorPoint(lpTopCenter,&tc);
   Float64 Xtc, Ytc;
   tc->Location(&Xtc,&Ytc);

   // NOTE: This function assumes that longitudinal rebar does not change during design.
   // This will need to be revisited if we start designing longitudinal rebar.

   // Compute area of rebar actually provided in tension zone. Reduce values for development
   Float64 AsProvd = 0.0; // As provided
   if ( stressLoc == slAllComp )
   {
      AsReqd = -1;
   }
   else
   {
      CComPtr<IEnumRebarSectionItem> enumItems;
      pRebarSection->get__EnumRebarSectionItem(&enumItems);

      CComPtr<IRebarSectionItem> rebarSectionItem;
      while ( enumItems->Next(1,&rebarSectionItem,NULL) != S_FALSE )
      {
         CComPtr<IRebar> rebar;
         rebarSectionItem->get_Rebar(&rebar);

         Float64 Ab, db, fy;
         rebar->get_NominalArea(&Ab);
         rebar->get_NominalDiameter(&db);
         rebar->get_YieldStrength(&fy);

         ATLASSERT(IsEqual(fy,m_fy));

         CComBSTR name;
         rebar->get_Name(&name);
         matRebar::Size size = lrfdRebarPool::GetBarSize(OLE2CT(name));

         // Adjust bar area for development
         REBARDEVLENGTHDETAILS devLengthDetails = lrfdRebar::GetRebarDevelopmentLengthDetails(size, Ab, db, fy, m_Concrete);


         // Get distances from section cut to ends of bar
         Float64 start,end;
         rebarSectionItem->get_LeftExtension(&start);
         rebarSectionItem->get_RightExtension(&end);

         Float64 dev_length_factor;
         Float64 cut_length = Min(start, end);
         ATLASSERT(!IsZero(cut_length)); // sections shouldn't be cutting bars that don't exist
         Float64 fra = cut_length/devLengthDetails.ldb;
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

            Float64 x,y;
            location->get_X(&x);
            location->get_Y(&y);

            // put the bar into section coordinates
            x += Xtc;
            y += Ytc;

            Float64 z;
            stressPlane->GetZ(x,y,&z);

            if ( ::IsLE(0.0,z) )
            {
               // if z is > 0 bar is on the tension side of neutral axis
               AsProvd += Ab;
            }
         }

         rebarSectionItem.Release();
      }
   }

   if ( stressLoc == slAllComp )
   {
      *pbIsAdequateRebar = true;
   }
   else
   {
      *pbIsAdequateRebar = (::IsLE(AsReqd,AsProvd,0.000001) ? true : false);
   }

   // convert the location of the neutral axis so that it is relative
   // to the top of the girder shape
   *pYna -= Ytc;

   *pAreaTens = AreaTens;
   *pT        = T;
   *pAsProvd  = AsProvd;
   *pAsReqd   = AsReqd;

#if defined _DEBUG
   if ( stressLoc != slAllTens && stressLoc != slAllComp && IsEqual(fTopLeft,fTopRight) && IsEqual(fBotLeft,fBotRight) )
   {
      // if left/right stresses are the same, we have uniaxial bending
      // therefore, the slope of the neutral axis must be zero
      ATLASSERT(IsZero(*pNAslope));
   }
#endif // _DEBUG
}

void lrfdAlternativeTensileStressCalculator::ComputeReqdFcTens(Float64 lambda,Float64 ft, // stress demand
                       Float64 rcsT, bool rcsBfmax, Float64 rcsFmax, Float64 rcsTalt, // allowable stress coeff's
                       Float64* pFcNo,Float64* pFcWithRebar)
{
   if ( 0 < ft )
   {
      // Without rebar
      if ( rcsBfmax && (rcsFmax < ft) )
      {
         // allowable stress is limited and we hit the limit
         *pFcNo = -99999;
      }
      else
      {
         *pFcNo = pow(ft/(lambda*rcsT),2);
      }

      // With rebar
      *pFcWithRebar = pow(ft/(lambda*rcsTalt),2);

   }
   else
   {
      // Compression
      *pFcNo = 0.0;
      *pFcWithRebar = 0.0;
   }
}
