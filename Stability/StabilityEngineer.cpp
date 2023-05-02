///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Stability/StabilityLib.h>
#include <Stability/StabilityEngineer.h>

#include <WBFLFem2d_i.c>

#include <array>
#include <algorithm>

#include <Units\Units.h>
#include <LRFD\ConcreteUtil.h>
#include <Math\CubicSolver.h>

#include <WBFLGenericBridge.h>
#include <WBFLGenericBridge_i.c>
#include <WBFLGenericBridgeTools.h>
#include <WBFLGenericBridgeTools_i.c>
#include <WBFLGeometry_i.c>

#define LCID_GIRDER 0
#define LCID_WIND   1
#define LCID_CF     2
#define LCID_LIFT   3

#define THETA_MAX 0.4

using namespace WBFL::Stability;

StabilityEngineer::StabilityEngineer()
{
}

LiftingResults StabilityEngineer::AnalyzeLifting(const IGirder* pGirder,const ILiftingStabilityProblem* pStabilityProblem) const
{
   LiftingResults results;
   PrepareResults(pGirder,pStabilityProblem,results);
   AnalyzeLifting(pGirder,pStabilityProblem,results);

   return results;
}

HaulingResults StabilityEngineer::AnalyzeHauling(const IGirder* pGirder,const IHaulingStabilityProblem* pStabilityProblem) const
{
   HaulingResults results;
   PrepareResults(pGirder,pStabilityProblem,results);
   AnalyzeHauling(pGirder,pStabilityProblem,results);
   return results;
}

OneEndSeatedResults StabilityEngineer::AnalyzeOneEndSeated(const IGirder * pGirder, const IOneEndSeatedStabilityProblem * pStabilityProblem) const
{
   OneEndSeatedResults results;

   PrepareResults(pGirder, pStabilityProblem, results);

   AnalyzeOneEndSeated(pGirder, pStabilityProblem, results);
   return results;
}

LiftingCheckArtifact StabilityEngineer::CheckLifting(const IGirder* pGirder,const ILiftingStabilityProblem* pStabilityProblem,const LiftingCriteria& criteria) const
{
   LiftingResults results = AnalyzeLifting(pGirder,pStabilityProblem);
   LiftingCheckArtifact artifact(results,criteria);
   return artifact;
}

HaulingCheckArtifact StabilityEngineer::CheckHauling(const IGirder* pGirder,const IHaulingStabilityProblem* pStabilityProblem,const HaulingCriteria& criteria) const
{
   HaulingResults results = AnalyzeHauling(pGirder,pStabilityProblem);
   HaulingCheckArtifact artifact(results,criteria);
   return artifact;
}

OneEndSeatedCheckArtifact StabilityEngineer::CheckOneEndSeated(const IGirder* pGirder, const IOneEndSeatedStabilityProblem* pStabilityProblem, const OneEndSeatedCriteria& criteria) const
{
   OneEndSeatedResults results = AnalyzeOneEndSeated(pGirder, pStabilityProblem);
   OneEndSeatedCheckArtifact artifact(results, criteria);
   return artifact;
}

void StabilityEngineer::PrepareResults(const IGirder* pGirder,const IStabilityProblem* pStabilityProblem,Results& results) const
{
   Float64 Ll,Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);
   Float64 Lg = pGirder->GetGirderLength();

   results.Ll = Ll;
   results.Lr = Lr;
   results.Ls = Lg - Ll - Lr;

   // offset factor for unequal spans
   Float64 a = Min(Ll, Lr);
   Float64 b = Max(Ll, Lr);
   Float64 La = Lg - 2 * a;
   results.OffsetFactor = pow(La / Lg, 2) * (1 - 2 * (b - a) / La) - 1. / 3.;
   results.OffsetFactor = IsZero(results.OffsetFactor) ? 0 : results.OffsetFactor;

#if defined _DEBUG
   if (IsEqual(a, b))
   {
      Float64 span_ratio = results.Ls / Lg;
      Float64 Fo = (span_ratio) * (span_ratio)-1. / 3.;
      ATLASSERT(IsEqual(results.OffsetFactor, Fo));
   }
#endif

   results.LateralSweep = pStabilityProblem->GetSweepTolerance()*Lg + pStabilityProblem->GetSweepGrowth();

   ComputeXcg(pGirder, pStabilityProblem, results);

   for ( IndexType i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      if (pStabilityProblem->IncludeLateralRollAxisOffset())
      {
         results.EccLateralSweep[+impact] = results.OffsetFactor*(results.LateralSweep + fabs(pStabilityProblem->GetLateralCamber())) + pStabilityProblem->GetSupportPlacementTolerance() + results.Xleft;
      }
      else
      {
         results.EccLateralSweep[+impact] = results.OffsetFactor*results.LateralSweep + pStabilityProblem->GetSupportPlacementTolerance();
      }
   }
}

void StabilityEngineer::Analyze(const IGirder* pGirder,const IStabilityProblem* pStabilityProblem,Results& results,IFem2dModel** ppModel) const
{
   BuildModel(pGirder,pStabilityProblem,results,ppModel);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   // adjust lateral eccentricity for total dead load
   Float64 eb, Wb;
   pStabilityProblem->GetAppurtenanceLoading(&eb, &Wb);
   Float64 ea = Wb*Lg * eb / results.Wg; // Wb is in force per unit length, so multiply by girder length
   results.ea = ea;
   for (IndexType i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      results.EccLateralSweep[+impact] += ea;
   }

   // BuildModel sets results.Ywind[NoImpact] equal to the location of the resultant wind force measured from the top of the girder in girder section coordinates
   // we need to get it from the roll axis
   Float64 Yra = pStabilityProblem->GetYRollAxis(); // positive means roll axis is above top of girder, negative means roll axis is below top of girder
   Float64 y = results.Ywind[+ImpactDirection::NoImpact] - Yra; // this value is less than zero if the location of the wind force is below the roll axis
   Float64 Ywind = fabs(y); // for the stability calcs, we want positive to be down for this value

   // adjust for camber
   Float64 Camber = pStabilityProblem->GetCamber();
   Float64 Precamber = pGirder->GetPrecamber();
   Float64 m = pStabilityProblem->GetCamberMultiplier();
   Ywind += ::BinarySign(y)*results.OffsetFactor*(m*Camber + Precamber); // binary sign is used to make the adjustment to Ywind correct if the camber makes it larger or smaller

   // additional effects due to impact adjusted force of inclined lifting cable will be added later
   results.Ywind[+ImpactDirection::NoImpact]   = Ywind;
   results.Ywind[+ImpactDirection::ImpactUp]   = Ywind;
   results.Ywind[+ImpactDirection::ImpactDown] = Ywind;

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll, &Lr);
   Float64 leftSupportLoc = Ll;
   Float64 rightSupportLoc = Lg - Lr;

   Float64 Ytop1, Ytop2;
   Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf;
   pGirder->GetSectionProperties(leftSupportLoc, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtf, &Wbf);
   Ytop1 = Ytop;
   pGirder->GetSectionProperties(rightSupportLoc, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtf, &Wbf);
   Ytop2 = Ytop;
   
   Ytop = Min(Ytop1, Ytop2);

   results.Yr = Yra - Ytop; // location from the center of gravity to the roll axis (positive means roll center is above CG)

   Float64 Dra = fabs(results.Yr);  // adjusted distance between CG and roll axis (using fabs because distance is an absolute value)
   Dra -= ::BinarySign(results.Yr)*results.OffsetFactor*(m*Camber + Precamber);
   results.CamberOffsetFactor = 1.0; // not applicable, but set it to a nice number

   // additional effects due to impact adjusted force of inclined lifting cable will be added later
   results.Dra[+ImpactDirection::NoImpact]   = Dra;
   results.Dra[+ImpactDirection::ImpactUp]   = Dra;
   results.Dra[+ImpactDirection::ImpactDown] = Dra;

   // lateral deflection due to full load applied laterally
   Float64 zo = ComputeZo(pGirder,pStabilityProblem,*ppModel,results);

   Float64 ImpactUp, ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   std::array<Float64, 3> IM = { 1.0, 1.0 - ImpactUp, 1.0 + ImpactDown };
   for ( IndexType i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      results.Zo[+impact] = IM[+impact]*zo;
      results.ZoWind[+impact] = results.Zo[+impact]*results.Wwind/(IM[+impact]*Wg);
   }
}

void StabilityEngineer::AnalyzeLifting(const IGirder* pGirder,const ILiftingStabilityProblem* pStabilityProblem,LiftingResults& results) const
{
   CComPtr<IFem2dModel> model;
   Analyze(pGirder,pStabilityProblem,results,&model);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   // compute critical buckling load
   Float64 Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtop,Wbot;
   pGirder->GetSectionProperties(Lg/2,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wtop,&Wbot);
   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   const auto& concrete = pStabilityProblem->GetConcrete();

   Float64 Ec = concrete.GetE();
   Float64 L = Lg - Ll - Lr;
   results.Pcrit = M_PI*M_PI*Ec*(Ixx*Iyy-Ixy*Ixy)/(Ixx*L*L);

   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   std::array<Float64, 3> IM = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   // horizontal component of force due to inclined lifting cables
   // negative value because it causes compression
   results.Plift = -(Wg/2)*tan(PI_OVER_2 - pStabilityProblem->GetLiftAngle());
   results.Plift = ::IsZero(results.Plift) ? 0.0 : results.Plift;

   if (::IsLT(Max(Wtop, Wbot) / 2, Xleft))
   {
      // we generally assume the girder tilts to the left. this is how the equations are developed in Mast and PCI.
      // however, we have a case where the CG is to the right of the centerline of the girder. this makes the
      // natural tendency of the girder to roll to the right.
      results.AssumedTiltDirection = GirderSide::Right;
   }

   ATLASSERT( !IsZero(pStabilityProblem->GetLiftAngle()) );
   for ( IndexType i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;

      // compute lateral deflection multiplier
      if ( results.Plift < 0 )
      {
         // inclined cables cause compression
         results.emag[+impact] = 1/(1 - fabs(IM[+impact]*results.Plift/results.Pcrit)); // lateral deflection multiplier
      }
      else
      {
         // inclined cables cause tension which will straighten the girder
         results.emag[+impact] = 1.0;
      }

      // adjust eccentricity of CG of girder due to lateral sweep
      results.EccLateralSweep[+impact] *= results.emag[+impact];
   }


   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   CComPtr<IRebarLayout> rebarLayout;
   if ( segment )
   {
      // only need the rebar model if we are checking tension with rebar, and that can only happen
      // if the girder is modeled with an ISegment object
      GetRebarLayout(pGirder,&rebarLayout);
   }

   // Get deflection due to horizontal component of lifting cable force
   CComQIPtr<IFem2dModelResults> femResults(model);
   // recall that the deflection is based on a unit force, so scale the value from the fem model by the actual force
   Float64 dx,dy1,dy2,rz;
   femResults->ComputePOIDeflections(LCID_LIFT,m_StartPoi,lotMember,&dx,&dy1,&rz);
   femResults->ComputePOIDeflections(LCID_LIFT,m_MidSpanPoi,lotMember,&dx,&dy2,&rz);
   //results.dLift = results.Plift*(dy2 - dy1); // does not include impact... measured relative to the ends of the girder

   for ( IndexType i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;

      // magnify lateral deflections due to horizontal component of lifting cable force
      results.Zo[+impact]     *= results.emag[+impact]; // emag includes impact
      results.ZoWind[+impact] *= results.emag[+impact];

      //// add the deflection due to the horizontal component of the lifting cable force
      //// to the location of the resultant gravity and wind forces
      //results.Dra[+impact]   -= results.OffsetFactor*IM[+impact]*results.dLift;
      //results.Ywind[+impact] -= results.OffsetFactor*IM[+impact]*results.dLift;

      // compute the lateral eccentricity of the girder self-weight due to the wind load
      results.EccWind[+impact] = results.Wwind*results.Ywind[+impact]/(IM[+impact]*Wg);

      // if the roll axis is below the center of mass for a hanging girder, it is unstable.
      // the girder will have to turn completely over to achieve equilibrium

      // Compute tilt equilibrium angle
      for ( IndexType w = 0; w < 2; w++ )
      {
         WindDirection wind = (WindDirection)w;
         Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

         // OffsetFactor = [(L-2a)/L]^2 - 1/3... The CG is exactly on the roll axis when OffsetFactor = 0
         // When OffsetFactor is less than zero, the CG is above the roll axis
         // ThetaEq = THETA_MAX when Dra = Zo + ei/THET_MAX. If Dra < Zo + ei/THETA_MAX ThetaEq > THETA_MAX which violates small angle theory
         // If Dra = Zo we will get a divide by zero. If Dra < Zo we will get a negative equilibrium angle.
         // Going back to the fundamental equations, Mr = Ma, W*Dra*theta = W(Zo*theta + ei). If you plot these equations Ma > Mr when Dra < Zo + ei/THETA_MAX
         results.bIsStable[+impact][+wind] = true;
         if (results.Dra[+impact] < 0 || results.OffsetFactor < 0 || results.Dra[+impact] < (results.Zo[+impact] + (results.EccLateralSweep[+impact] + windSign*(results.ZoWind[+impact] - results.EccWind[+impact])) / THETA_MAX))
         {
            results.bIsStable[+impact][+wind] = false;
            results.FScrMin = 0;
            results.MinFsFailure = 0;
            results.MinAdjFsFailure = 0;
            continue;
         }

         results.ThetaEq[+impact][+wind] = (results.EccLateralSweep[+impact] + windSign*(results.ZoWind[+impact] - results.EccWind[+impact])) / (results.Dra[+impact] - results.Zo[+impact]);
#if defined _DEBUG
         if (results.EccLateralSweep[+impact] + windSign*results.ZoWind[+impact] < windSign*results.EccWind[+impact])
         {
            // wind is great enough to reverse rotation
            ATLASSERT(wind == WindDirection::Left); // this case can only happen for left wind (reducing rotation)
            ATLASSERT(results.ThetaEq[+impact][+wind] < 0);
         }
#endif
      } // next wind direction
   } // next impact direction

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   Float64 fr = concrete.GetFlexureFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();

   // this parameter is used to compute the moment arm for the horizontal force in the inclined
   // lift cable measured transversely from the laterally deflected beam.
   // we are conservative to assume equal overhangs based on the smallest overhang
   // this puts the force furthest from the arc which is conservative
   Float64 a = Min(Ll,Lr);

   PoiIDType poiID = 0;
   IndexType analysisPointIdx = 0;
   const auto& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   for( const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 X = pAnalysisPoint->GetLocation();

      LiftingSectionResult sectionResult;

      sectionResult.AnalysisPointIndex = analysisPointIdx++;

      CComPtr<IRebarSection> rebarSection;
      CComPtr<IShape> shape;
      if ( segment )
      {
         rebarLayout->CreateRebarSection(X,INVALID_INDEX,&rebarSection);
         segment->get_GirderShape(X,sbLeft,cstGirder, &shape); // this is in girder section coordinates

         // position the shape in centroidal/stress point coordinates
         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         CComPtr<IPoint2d> pntCG;
         props->get_Centroid(&pntCG);
         Float64 x, y;
         pntCG->Location(&x, &y);
         CComQIPtr<IXYPosition> position(shape);
         position->Offset(-x, -y);
      }

      // eccentricity of horizontal load due to inclined cable at X
      sectionResult.OffsetFactor = pow((Lg - 2*a)/Lg,2) - pow((Lg - 2*X)/Lg,2);
      sectionResult.OffsetFactor = IsZero(sectionResult.OffsetFactor) ? 0.0 : sectionResult.OffsetFactor;

      // Get forces from external loads
      Float64 fx,fy,mz;
      femResults->ComputePOIForces(LCID_GIRDER,poiID,mftLeft,lotMember,&fx,&fy,&mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mg = mz;

      femResults->ComputePOIForces(LCID_WIND,poiID,mftLeft,lotMember,&fx,&fy,&mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mw = mz;

      Float64 Hg,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Wtf,Wbf;
      pGirder->GetSectionProperties(X,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wtf,&Wbf);

      Float64 D = Ixx*Iyy - Ixy*Ixy;

      std::array<Point,4> pntStress;
      pGirder->GetStressPoints(X, &pntStress[+Corner::TopLeft], &pntStress[+Corner::TopRight], &pntStress[+Corner::BottomLeft], &pntStress[+Corner::BottomRight]);

      // stress due to prestressing
      std::vector<LPCTSTR> vNames = pStabilityProblem->GetPrestressNames();
      for(const auto strName : vNames)
      {
         Float64 Fpe, Xps, Yps;
         pStabilityProblem->GetFpe(strName, X, &Fpe, &Xps, &Yps);
      
         if (!IsZero(Fpe))
         {
            Float64 eyps = Ytop - Yps; // eccentricity of strands (positive values means ps force is below CG)
            Float64 exps = Xleft - Xps; // lateral eccentricity of strands (positive values means ps force is left of the CG)

            Float64 Mxps = -Fpe*eyps;
            Float64 Myps = -Fpe*exps;

            for (int c = 0; c < 4; c++)
            {
               Corner corner = (Corner)c;
               Float64 f = ((Myps*Ixx + Mxps*Ixy)*pntStress[+corner].X() - (Mxps*Iyy + Myps*Ixy)*pntStress[+corner].Y()) / D - (Fpe/Ag);
               sectionResult.fps[+corner] += f;
            }
         }
      }

      // stress due to inclined lift cable
      Float64 Plift = results.Plift;
      if ( X < Ll || (Lg - Lr) < X )
      {
         Plift = 0; // X is not between the lifting devices so there isn't any axial load due to the inclined cable
      }

      Float64 MxLift = -Plift*results.Dra[+ImpactDirection::NoImpact];
      Float64 MyLift = 0;
      Float64 MxGirder = sectionResult.Mg;
      Float64 MyGirder = 0;
      Float64 MxWind = 0;
      Float64 MyWind = -sectionResult.Mw;
      for (int c = 0; c < 4; c++)
      {
         Corner corner = (Corner)c;

         // stress due to inclined lift cables (no impact)
         sectionResult.fcable[+corner] = ((MyLift*Ixx + MxLift*Ixy)*pntStress[+corner].X() - (MxLift*Iyy + MyLift*Ixy)*pntStress[+corner].Y()) / D - (-Plift / Ag);
         
         // stress due to plumb girder (no impact)
         sectionResult.fg[+corner] = ((MyGirder*Ixx + MxGirder*Ixy)*pntStress[+corner].X() - (MxGirder*Iyy + MyGirder*Ixy)*pntStress[+corner].Y()) / D;

         // stress due to wind towards the left
         sectionResult.fw[+corner] = ((MyWind*Ixx + MxWind*Ixy)*pntStress[+corner].X() - (MxWind*Iyy + MyWind*Ixy)*pntStress[+corner].Y()) / D;
      } // next corner

      // analyze the girder for all the combinations of impact and wind
      for ( IndexType i = 0; i < 3; i++ )
      {
         ImpactDirection impact = (ImpactDirection)i;

         for (IndexType c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;

            GirderFace face = GetFace(corner);
            GirderSide side = GetSide(corner);

            Float64 sideSign = (side == GirderSide::Left ? -1 : 1);

            // stress due to direct loads
            sectionResult.fDirect[+impact][+corner] = sectionResult.fps[+corner] + IM[+impact] * (sectionResult.fg[+corner] + sectionResult.fcable[+corner]);

            if (::IsLT(sectionResult.fMaxDirect[+face], sectionResult.fDirect[+impact][+corner]))
            {
               sectionResult.fMaxDirect[+face] = sectionResult.fDirect[+impact][+corner];
               sectionResult.MaxDirectStressImpactDirection[+face] = impact;
               sectionResult.MaxDirectStressCorner[+face] = corner;
            }

            if (::IsLT(sectionResult.fDirect[+impact][+corner], sectionResult.fMinDirect[+face]))
            {
               sectionResult.fMinDirect[+face] = sectionResult.fDirect[+impact][+corner];
               sectionResult.MinDirectStressImpactDirection[+face] = impact;
               sectionResult.MinDirectStressCorner[+face] = corner;
            }

            // Overall max direct stress
            if (::IsLT(results.MaxDirectStress, sectionResult.fDirect[+impact][+corner]))
            {
               results.MaxDirectStress = sectionResult.fDirect[+impact][+corner];
               results.MaxDirectStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
               results.MaxDirectStressImpactDirection = impact;
               results.MaxDirectStressCorner = corner;
            }

            // Overall min direct stress
            if (::IsLT(sectionResult.fDirect[+impact][+corner], results.MinDirectStress))
            {
               results.MinDirectStress = sectionResult.fDirect[+impact][+corner];
               results.MinDirectStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
               results.MinDirectStressImpactDirection = impact;
               results.MinDirectStressCorner = corner;
            }
            
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               if (results.bIsStable[+impact][+wind])
               {
                  Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

                  if (IsZero(Plift))
                  {
                     // if there isn't a lifting force, the force cannot be eccentric
                     sectionResult.eh[+impact][+wind] = 0;
                     sectionResult.Mh[+impact][+wind] = 0;
                  }
                  else
                  {
                     // Because there is lateral deflection of the girder, the force in the inclined lift cable creates a moment about the Y-axis
                     // Compute the eccentricity of the force and the moment at this section
                     sectionResult.eh[+impact][+wind] = SupportPlacementTolerance*results.emag[+impact] * (1 - sectionResult.OffsetFactor) + (results.EccLateralSweep[+impact] + windSign*results.ZoWind[+impact])*sectionResult.OffsetFactor;
                     sectionResult.Mh[+impact][+wind] = -Plift*sectionResult.eh[+impact][+wind];
                  }

                  // stress due to lateral loads caused by the girder being tilted
                  //Float64 Mx = 0;
                  Float64 My = -1.0*IM[+impact] * ((sectionResult.Mg - Plift*results.Zo[+impact])*results.ThetaEq[+impact][+wind] + sectionResult.Mh[+impact][+wind]);
                  Float64 f = ((My*Ixx/* + Mx*Ixy*/)*pntStress[+corner].X() - (/*Mx*Iyy + */My*Ixy)*pntStress[+corner].Y()) / D;
                  if (results.AssumedTiltDirection == GirderSide::Right)
                  {
                     // girder is tilted to the right so flip the sign
                     // f is computed assuming tilt to the left
                     f *= -1;
                  }
                  sectionResult.fTilt[+impact][+wind][+corner] = f;

                  // total stress
                  sectionResult.f[+impact][+wind][+corner] = sectionResult.fDirect[+impact][+corner] + windSign*sectionResult.fw[+corner] + sectionResult.fTilt[+impact][+wind][+corner];

                  if (::IsLT(sectionResult.fMax[+face], sectionResult.f[+impact][+wind][+corner]))
                  {
                     sectionResult.fMax[+face] = sectionResult.f[+impact][+wind][+corner];
                     sectionResult.MaxStressImpactDirection[+face] = impact;
                     sectionResult.MaxStressWindDirection[+face] = wind;
                     sectionResult.MaxStressCorner[+face] = corner;
                  }

                  if (::IsLT(sectionResult.f[+impact][+wind][+corner], sectionResult.fMin[+face]))
                  {
                     sectionResult.fMin[+face] = sectionResult.f[+impact][+wind][+corner];
                     sectionResult.MinStressImpactDirection[+face] = impact;
                     sectionResult.MinStressWindDirection[+face] = wind;
                     sectionResult.MinStressCorner[+face] = corner;
                  }

                  if (::IsLT(results.MaxStress, sectionResult.f[+impact][+wind][+corner]))
                  {
                     results.MaxStress = sectionResult.f[+impact][+wind][+corner];
                     results.MaxStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                     results.MaxStressImpactDirection = impact;
                     results.MaxStressWindDirection = wind;
                     results.MaxStressCorner = corner;
                  }

                  if (::IsLT(sectionResult.f[+impact][+wind][+corner], results.MinStress))
                  {
                     results.MinStress = sectionResult.f[+impact][+wind][+corner];
                     results.MinStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                     results.MinStressImpactDirection = impact;
                     results.MinStressWindDirection = wind;
                     results.MinStressCorner = corner;
                  }

                  // compute cracking moment and cracking factor of safety
                  Float64 mcr = 0; // if the direct stress exceeded the modulus of rupture, the beam is cracked before it is tilted
                  Float64 f_direct = sectionResult.fDirect[+impact][+corner] + windSign*sectionResult.fw[+corner];
                  if (f_direct < fr)
                  {
                     // the direct stress is less than the modulus of rupture, therefore there needs to be additional moment applied to cause cracking

                     // basic_mcr could be positive or negative. Negative means that the girder self-weight moment must reverse direction in order
                     // to crack the girder at [+corner]
                     Float64 basic_mcr = ((f_direct - fr)*D / (Ixx*pntStress[+corner].X() - Ixy*pntStress[+corner].Y()));

                     mcr = basic_mcr - sectionResult.Mh[+impact][+wind];

                     if (0 <= basic_mcr && mcr < 0)
                     {
                        // If basic_mcr is greater than zero and, Mh is larger, Mh causes the girder to crack without any tilting
                        // take mcr to be zero
                        mcr = 0;
                     }
                  }

                  Float64 m = IM[+impact] * sectionResult.Mg - Plift*results.Zo[+impact];

                  Float64 theta_crack = (IsZero(m) ? ::BinarySign(results.ThetaEq[+impact][+wind])*THETA_MAX : mcr / m);

                  if (results.AssumedTiltDirection == GirderSide::Right)
                  {
                     // girder is tilted to the right so flip the sign of the cracking angle
                     theta_crack *= -1;
                  }

                  theta_crack = ::ForceIntoRange(-THETA_MAX, theta_crack, THETA_MAX);

                  sectionResult.Mcr[+impact][+wind][+corner] = mcr;
                  sectionResult.ThetaCrack[+impact][+wind][+corner] = theta_crack;


                  Float64 fscr = 0;
                  if (results.ThetaEq[+impact][+wind] < 0)
                  {
                     ATLASSERT(wind == WindDirection::Left);
                     if (theta_crack < 0)
                     {
                        Float64 Mr = results.EccLateralSweep[+impact] + results.ZoWind[+impact] + (results.Zo[+impact] - results.Dra[+impact])*theta_crack;
                        Float64 Ma = results.EccWind[+impact];
                        fscr = IsZero(Ma) ? Float64_Max : Mr / Ma;
                     }
                     else
                     {
                        fscr = Float64_Max;
                     }
                  }
                  else
                  {
                     if (theta_crack < 0)
                     {
                        // the lateral moment due to girder self-weight must reverse direction in order to crack this flange tip
                        // that's impossible
                        fscr = Float64_Max;
                     }
                     else
                     {
                        Float64 Mr = results.Dra[+impact] * theta_crack;
                        Float64 Ma = results.Zo[+impact] * theta_crack + results.EccLateralSweep[+impact] + windSign*(results.ZoWind[+impact] - results.EccWind[+impact]);
                        fscr = IsZero(Ma) ? Float64_Max : Mr / Ma;
                     }
                  }

                  sectionResult.FScr[+impact][+wind][+corner] = fscr;

                  // keep track of the minimum FScr at this section for this loading
                  if (::IsLT(sectionResult.FScr[+impact][+wind][+corner], sectionResult.MinFScr[+impact][+wind]))
                  {
                     // for this impact and wind, the minimum FScr occurs at the current corner
                     sectionResult.MinFScr[+impact][+wind] = sectionResult.FScr[+impact][+wind][+corner];
                     sectionResult.MinFScrCorner[+impact][+wind] = corner;
                  }

                  // keep track of the minimum FScr at this section for all loadings
                  if (::IsLT(sectionResult.FScr[+impact][+wind][+corner], sectionResult.FScrMin))
                  {
                     // for all impact and wind, the minimum FScr occurs at the current corner
                     sectionResult.FScrMin = sectionResult.FScr[+impact][+wind][+corner];
                     sectionResult.FScrMinImpactDirection = impact;
                     sectionResult.FScrMinWindDirection = wind;
                     sectionResult.FScrMinCorner = corner;
                  }
               } // if stable
                    
               // keep track of the minimum FScr for all analysis points for this load case
               if (::IsLT(sectionResult.MinFScr[+impact][+wind], results.MinFScr[+impact][+wind]))
               {
                  // for this impact and wind, the minimum FScr along the beam occurs at this section
                  results.MinFScr[+impact][+wind] = sectionResult.MinFScr[+impact][+wind];
                  results.FScrAnalysisPointIndex[+impact][+wind] = sectionResult.AnalysisPointIndex;
                  results.FScrCorner[+impact][+wind] = sectionResult.MinFScrCorner[+impact][+wind];
               }

               // keep track of overall minimum FScr
               if (::IsLT(sectionResult.MinFScr[+impact][+wind], results.FScrMin))
               {
                  // for all impact and wind cases, the minimum FScr along the beam occurs at this section
                  results.FScrMin = sectionResult.MinFScr[+impact][+wind];
                  results.FScrMinAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                  results.FScrMinImpactDirection = impact;
                  results.FScrMinWindDirection = wind;
                  results.FScrMinCorner = sectionResult.MinFScrCorner[+impact][+wind];
               }
            } // next wind direction
         } // next corner

         // compute rebar requirements for tension stresses
         if (segment && concrete.GetType() != WBFL::Materials::ConcreteType::UHPC)
         {
            gbtAlternativeTensileStressRequirements altTensionRequirements;

            CComPtr<IShapeProperties> sp;
            shape->get_ShapeProperties(&sp);
            sp->get_Ytop(&altTensionRequirements.Ytg);

            altTensionRequirements.shape = shape;
            altTensionRequirements.rebarSection = rebarSection;
            altTensionRequirements.fy = pStabilityProblem->GetRebarYieldStrength();
            altTensionRequirements.fsMax = WBFL::Units::ConvertToSysUnits(30.0, WBFL::Units::Measure::KSI);
            altTensionRequirements.bLimitBarStress = true;
            altTensionRequirements.concreteType = concrete.GetType();
            altTensionRequirements.fc = concrete.GetFc();
            altTensionRequirements.bHasFct = concrete.HasAggSplittingStrength();
            altTensionRequirements.Fct = concrete.GetAggSplittingStrength();
            altTensionRequirements.density = concrete.GetDensity();

#if defined REBAR_FOR_DIRECT_TENSION
            altTensionRequirements.pntTopLeft.Move(    pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.fDirect[+impact][+Corner::TopLeft]);
            altTensionRequirements.pntTopRight.Move(   pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.fDirect[+impact][+Corner::TopRight]);
            altTensionRequirements.pntBottomLeft.Move( pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.fDirect[+impact][+Corner::BottomLeft]);
            altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.fDirect[+impact][+Corner::BottomRight]);

            gbtComputeAlternativeStressRequirements(&altTensionRequirements);
            sectionResult.altTensionRequirements[+impact] = altTensionRequirements;
#else 
            for (IndexType w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;

               altTensionRequirements.pntTopLeft.Move    (pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.f[+impact][+wind][+Corner::TopLeft]);
               altTensionRequirements.pntTopRight.Move   (pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.f[+impact][+wind][+Corner::TopRight]);
               altTensionRequirements.pntBottomLeft.Move (pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.f[+impact][+wind][+Corner::BottomLeft]);
               altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.f[+impact][+wind][+Corner::BottomRight]);

               gbtComputeAlternativeStressRequirements(&altTensionRequirements);
               sectionResult.altTensionRequirements[+impact][+wind] = altTensionRequirements;
            }
#endif // REBAR_FOR_DIRECT_TENSION
         } // if segment
      } // next impact

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure for all combinations of impact and wind
   for ( int i = 0; i < 3; i++ )
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

         if (results.bIsStable[+impact][+wind])
         {
            Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

            if (results.ThetaEq[+impact][+wind] < 0)
            {
               ATLASSERT(wind == WindDirection::Left);
               results.ThetaMax[+impact][+wind] = (results.Zo[+impact] - results.Dra[+impact] - windSign*2.5*results.ZoWind[+impact] ) / (5 * results.Zo[+impact]);
               ATLASSERT(results.ThetaMax[+impact][+wind] <= 0);
            }
            else
            {
               Float64 S = results.EccLateralSweep[+impact] + windSign*(results.ZoWind[+impact] - results.EccWind[+impact]);
               S /= 2.5*results.Zo[+impact];
               ATLASSERT(0 <= S);
               results.ThetaMax[+impact][+wind] = sqrt(S);
            }
            results.ThetaMax[+impact][+wind] = ::ForceIntoRange(-THETA_MAX, results.ThetaMax[+impact][+wind], THETA_MAX);

            Float64 FSf = 0;
            if (results.ThetaEq[+impact][+wind] < 0)
            {
               ATLASSERT(wind == WindDirection::Left);
               Float64 Mr = results.EccLateralSweep[+impact] - results.Dra[+impact] * results.ThetaMax[+impact][+wind] + (results.ZoWind[+impact] + results.Zo[+impact] * results.ThetaMax[+impact][+wind]) * (1 - 2.5*results.ThetaMax[+impact][+wind]);
               Float64 Ma = results.EccWind[+impact];
               FSf = IsZero(Ma) ? Float64_Max : Mr / Ma;
            }
            else
            {
               Float64 Mr = results.Dra[+impact] * results.ThetaMax[+impact][+wind];
               Float64 Ma = (1 + 2.5*results.ThetaMax[+impact][+wind])*(results.Zo[+impact] * results.ThetaMax[+impact][+wind] + windSign*results.ZoWind[+impact]) - windSign*results.EccWind[+impact] + results.EccLateralSweep[+impact];
               FSf = IsZero(Ma) ? Float64_Max : Mr / Ma;
            }
            results.FsFailure[+impact][+wind] = FSf;
         
            // if FSf < FScr then FSf = FScr (if the girder doesn't crack, it doesn't fail)
            results.AdjFsFailure[+impact][+wind] = Max(results.FsFailure[+impact][+wind],results.MinFScr[+impact][+wind]);

            if ( ::IsLT(results.AdjFsFailure[+impact][+wind],results.MinAdjFsFailure) )
            {
               results.MinFsFailure = results.FsFailure[+impact][+wind];
               results.MinAdjFsFailure = results.AdjFsFailure[+impact][+wind];
               results.FSfImpactDirection = impact;
               results.FSfWindDirection = wind;
            }
         } // next wind direction
      }// if stable
   } // next impact
}

void StabilityEngineer::AnalyzeOneEndSeated(const IGirder * pGirder, const IOneEndSeatedStabilityProblem* pStabilityProblem, OneEndSeatedResults & results) const
{
   CComPtr<IFem2dModel> model;
   Analyze(pGirder, pStabilityProblem, results, &model);

   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   CComPtr<IRebarLayout> rebarLayout;
   if (segment)
   {
      // only need the rebar model if we are checking tension with rebar, and that can only happen
      // if the girder is modeled with an ISegment object
      GetRebarLayout(pGirder, &rebarLayout);
   }

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;


   Float64 ImpactUp, ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp, &ImpactDown);
   std::array<Float64, 3> IM = { 1.0, 1.0 - ImpactUp, 1.0 + ImpactDown };
   
   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll, &Lr);

   Float64 La = Lg/2 - Ll;
   Float64 Lb = Lg/2 - Lr;
   Float64 Ls = Lg - Ll - Lr;

   if (pStabilityProblem->GetSeatedEnd() == GirderSide::Right)
   {
      std::swap(La, Lb);
      std::swap(Ll, Lr);
   }

   Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
   pGirder->GetSectionProperties(Lg / 2, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);
   if (::IsLT(Max(Wtop, Wbot) / 2, Xleft))
   {
      // we generally assume the girder tilts to the left. this is how the equations are developed in Mast and PCI.
      // however, we have a case where the CG is to the right of the centerline of the girder. this makes the
      // natural tendency of the girder to roll to the right.
      results.AssumedTiltDirection = GirderSide::Right;
   }

   const auto & concrete = pStabilityProblem->GetConcrete();
   Float64 fr = concrete.GetFlexureFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();
   Float64 Ktheta = pStabilityProblem->GetRotationalStiffness();
   Float64 crownSlope = pStabilityProblem->GetSupportSlope();
   Float64 Hrs = pStabilityProblem->GetHeightOfRollAxis();
   Float64 Wcc = pStabilityProblem->GetSupportWidth();

   Float64 Kadjust = pStabilityProblem->GetRotationalStiffnessAdjustmentFactor();
   Ktheta *= Kadjust;

   // Offset factor is for equal length overhangs based on the seated end
   results.OffsetFactor = pow(((Lg - 2 * Ll) / Lg), 2) - 1. / 3.;

   // PrepareResults computes the initial eccentricity assuming seated or hanging from both ends
   // The eccentricity for that case is  ei = Fo*Delta_sweep + e_seat
   // but the eccentricity for seated at one end must account for different offsets of the seated and hanging end
   // ei = Fo*Delta_Sweep + Lb/Ls*e_seat + La/Ls*e_lift
   // Re-compute ei for this case
   Float64 e_seat = pStabilityProblem->GetSupportPlacementTolerance();
   Float64 e_lift = pStabilityProblem->GetLiftPlacementTolerance();
   Float64 ei = results.OffsetFactor * results.LateralSweep + (La * e_lift + Lb * e_seat) / Ls;
   for (IndexType i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      results.EccLateralSweep[+impact] = ei;
   }

   // Compute roll axis location
   //
   // In the Analyze method Dra is computed assuming a horizontal roll axis through two lift points or to seat points.
   // For this analysis, the roll axis is inclined going from the bottom to the top of the girder.
   // Recompute Dra here
   Float64 Camber = pStabilityProblem->GetCamber();
   Float64 Precamber = pGirder->GetPrecamber();
   Float64 m = pStabilityProblem->GetCamberMultiplier();
   Float64 Ybot = Hg + Ytop;
   Float64 Yroll = pStabilityProblem->GetYRollAxis(); // location of roll axis down (negative value) from top of girder for the seated end
   Float64 h_roll = -(Hg + Yroll);
   Float64 ylift = pStabilityProblem->GetYRollLiftEnd(); 
   Float64 Dra = Ybot + results.OffsetFactor*(m*Camber + Precamber) + (Lb / Ls) * h_roll - (La / Ls) * (Hg + ylift);
   results.Dra[+ImpactDirection::NoImpact] = Dra;
   results.Dra[+ImpactDirection::ImpactUp] = Dra;
   results.Dra[+ImpactDirection::ImpactDown] = Dra;

   // overturning moment due to wind applied toward the left
   // Ywind and Dra are a function of impact because of impact forces in the horizontal
   // component of the lifting cable. Since this is a hauling case, such force effects
   // do not exist so we can just use the no impact case.
   //
   // Ywind is measured from the roll center at the seated end
   // The wind overturning moment is the wind force times the distance to the roll axis
   // MotWind = Wwind * (Ywind - (La/Ls)*(h roll + Hg + ylift))
   // Update Ywind so that it is the distance from the roll axis to the wind force
   results.Ywind[+ImpactDirection::NoImpact] -= (La / Ls) * (h_roll + Hg + ylift);
   results.Ywind[+ImpactDirection::ImpactUp] -= (La / Ls) * (h_roll + Hg + ylift);
   results.Ywind[+ImpactDirection::ImpactDown] -= (La / Ls) * (h_roll + Hg + ylift);
   results.MotWind = results.Wwind * results.Ywind[+ImpactDirection::NoImpact];

   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      Float64 alpha = crownSlope;

      Float64 im = IM[+impact];

      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

         Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

         Float64 Zt = windSign * results.ZoWind[+impact];
         Float64 Mot = windSign * results.MotWind;

         Float64 ei = results.EccLateralSweep[+impact];

         results.ThetaEq[+impact][+wind] = (Ktheta * alpha + im * Wg * (ei + Zt) + Mot) / (Ktheta - im * Wg * (results.Dra[+impact] + im * results.Zo[+ImpactDirection::NoImpact]));
         // if ThetaEq < 0, then girder is rolling to the right

         if (results.ThetaEq[+impact][+wind] < -THETA_MAX || THETA_MAX < results.ThetaEq[+impact][+wind])
         {
            // if the equilibrium angle is excessive the rotational spring stiffness is probably too small...
            // consider this an unstable condition
            results.bRotationalStability[+impact][+wind] = false;
            results.FsRollover[+impact][+wind] = 0;
            results.MinFsRollover = 0;
            results.MinFScr = 0;
         }
      }
   }

   PoiIDType poiID = 0;
   CComQIPtr<IFem2dModelResults> femResults(model);
   const auto& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   IndexType analysisPointIdx = 0;
   for (const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 X = pAnalysisPoint->GetLocation();

      OneEndSeatedSectionResult sectionResult;

      sectionResult.AnalysisPointIndex = analysisPointIdx++;

      CComPtr<IRebarSection> rebarSection;
      CComPtr<IShape> shape;
      if (segment)
      {
         rebarLayout->CreateRebarSection(X, INVALID_INDEX, &rebarSection);
         segment->get_GirderShape(X, sbLeft, cstGirder, &shape); // this is in girder section coordinates

         // position the shape in centroidal/stress point coordinates
         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         CComPtr<IPoint2d> pntCG;
         props->get_Centroid(&pntCG);
         Float64 x, y;
         pntCG->Location(&x, &y);
         CComQIPtr<IXYPosition> position(shape);
         position->Offset(-x, -y);
      }

      // Get forces from external loads
      Float64 fx, fy, mz;
      femResults->ComputePOIForces(LCID_GIRDER, poiID, mftLeft, lotMember, &fx, &fy, &mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mg = mz;

      femResults->ComputePOIForces(LCID_WIND, poiID, mftLeft, lotMember, &fx, &fy, &mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mw = mz;

      femResults->ComputePOIForces(LCID_CF, poiID, mftLeft, lotMember, &fx, &fy, &mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mcf = mz;

      Float64 Hg, Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Wbf, Wtf;
      pGirder->GetSectionProperties(X, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtf, &Wbf);

      Float64 D = Ixx * Iyy - Ixy * Ixy;

      std::array<Point, 4> pntStress;
      pGirder->GetStressPoints(X, &pntStress[+Corner::TopLeft], &pntStress[+Corner::TopRight], &pntStress[+Corner::BottomLeft], &pntStress[+Corner::BottomRight]);

      // stress due to prestressing
      std::vector<LPCTSTR> vNames = pStabilityProblem->GetPrestressNames();
      for (const auto strName : vNames)
      {
         Float64 Fpe, Xps, Yps;
         pStabilityProblem->GetFpe(strName, X, &Fpe, &Xps, &Yps);
         Float64 eyps = Ytop - Yps; // eccentricity of strands (positive values means ps force is below CG)
         Float64 exps = Xleft - Xps; // lateral eccentricity of strands (positive values means ps force is left of the CG)

         Float64 Mxps = -Fpe * eyps;
         Float64 Myps = -Fpe * exps;

         for (int c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            Float64 f = ((Myps * Ixx + Mxps * Ixy) * pntStress[+corner].X() - (Mxps * Iyy + Myps * Ixy) * pntStress[+corner].Y()) / D - (Fpe / Ag);
            sectionResult.fps[+corner] += f;
         }
      }

      Float64 MxCF = 0;
      Float64 MyCF = sectionResult.Mcf;
      Float64 MxGirder = sectionResult.Mg;
      Float64 MyGirder = 0;
      Float64 MxWind = 0;
      Float64 MyWind = -sectionResult.Mw;
      for (int c = 0; c < 4; c++)
      {
         Corner corner = (Corner)c;

         // stress due to plumb girder (no impact)
         sectionResult.fg[+corner] = ((MyGirder * Ixx + MxGirder * Ixy) * pntStress[+corner].X() - (MxGirder * Iyy + MyGirder * Ixy) * pntStress[+corner].Y()) / D;

         // stress due to wind towards the left
         sectionResult.fw[+corner] = ((MyWind * Ixx + MxWind * Ixy) * pntStress[+corner].X() - (MxWind * Iyy + MyWind * Ixy) * pntStress[+corner].Y()) / D;

         // stress due to centrifugal forces
         sectionResult.fcf[+corner] = ((MyCF * Ixx + MxCF * Ixy) * pntStress[+corner].X() - (MxCF * Iyy + MyCF * Ixy) * pntStress[+corner].Y()) / D;
      } // next corner

      for (int i = 0; i < 3; i++)
      {
         ImpactDirection impact = (ImpactDirection)i;

         Float64 im = IM[+impact];

         for (int cn = 0; cn < 4; cn++)
         {
            Corner corner = (Corner)cn;
            GirderFace face = GetFace(corner);
            Float64 b = (face == GirderFace::Top ? Wtf : Wbf);

            Float64 cornerSign = (corner == Corner::TopLeft || corner == Corner::BottomLeft ? 1 : -1);

            // stress due to direct loads (plumb girder)
            sectionResult.fDirect[+impact][+corner] = sectionResult.fps[+corner] + im * sectionResult.fg[+corner];

            // keep track of the max direct stress at this section including the corner where it occurs
            if (::IsLT(sectionResult.fMaxDirect[+face], sectionResult.fDirect[+impact][+corner]))
            {
               sectionResult.fMaxDirect[+face] = sectionResult.fDirect[+impact][+corner];
               sectionResult.MaxDirectStressImpactDirection[+face] = impact;
               sectionResult.MaxDirectStressCorner[+face] = corner;
            }

            // keep track of the min direct stress at this section including the corner where it occurs
            if (::IsLT(sectionResult.fDirect[+impact][+corner], sectionResult.fMinDirect[+face]))
            {
               sectionResult.fMinDirect[+face] = sectionResult.fDirect[+impact][+corner];
               sectionResult.MinDirectStressImpactDirection[+face] = impact;
               sectionResult.MinDirectStressCorner[+face] = corner;
            }

            // keep track of the max direct stress of ALL sections including the corner where it occurs
            if (::IsLT(results.MaxDirectStress, sectionResult.fDirect[+impact][+corner]))
            {
               results.MaxDirectStress = sectionResult.fDirect[+impact][+corner];
               results.MaxDirectStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
               results.MaxDirectStressImpactDirection = impact;
               results.MaxDirectStressCorner = corner;
            }

            // keep track of the min direct stress of ALL sections including the corner where it occurs
            if (::IsLT(sectionResult.fDirect[+impact][+corner], results.MinDirectStress))
            {
               results.MinDirectStress = sectionResult.fDirect[+impact][+corner];
               results.MinDirectStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
               results.MinDirectStressImpactDirection = impact;
               results.MinDirectStressCorner = corner;
            }

            for (int w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;

               if (results.bRotationalStability[+impact][+wind])
               {
                  Float64 windSign = (wind == WindDirection::Left ? 1 : -1);
                  Float64 Zt = windSign * im * results.ZoWind[+ImpactDirection::NoImpact]; // using NoImpact because we scale by IM here
                  Float64 Mot = windSign * results.MotWind;
                  Float64 ei = results.EccLateralSweep[+impact];

                  // stress due to lateral loads caused by the girder being tilted
                  //Float64 Mx = 0;
                  Float64 My = -1 * im * sectionResult.Mg * results.ThetaEq[+impact][+wind]; // this sign of ThetaEq will take care of the girder rolling to the right
                  Float64 f = ((My * Ixx/* + Mx*Ixy*/) * pntStress[+corner].X() - (/*Mx*Iyy + */My * Ixy) * pntStress[+corner].Y()) / D;
                  if (results.AssumedTiltDirection == GirderSide::Right)
                  {
                     // girder is tilted to the right so flip the sign
                     // f is computed assuming tilt to the left
                     f *= -1;
                  }
                  sectionResult.fTilt[+impact][+wind][+corner] = f;

                  // total stress
                  sectionResult.f[+impact][+wind][+corner] = sectionResult.fDirect[+impact][+corner] + sectionResult.fTilt[+impact][+wind][+corner] + windSign * sectionResult.fw[+corner];

                  // keep track of max stress at this section including the corner where it occurs
                  if (::IsLT(sectionResult.fMax[+face], sectionResult.f[+impact][+wind][+corner]))
                  {
                     sectionResult.fMax[+face] = sectionResult.f[+impact][+wind][+corner];
                     sectionResult.MaxStressImpactDirection[+face] = impact;
                     sectionResult.MaxStressWindDirection[+face] = wind;
                     sectionResult.MaxStressCorner[+face] = corner;
                  }

                  // keep track of min stress at this section including the corner where it occurs
                  if (::IsLT(sectionResult.f[+impact][+wind][+corner], sectionResult.fMin[+face]))
                  {
                     sectionResult.fMin[+face] = sectionResult.f[+impact][+wind][+corner];
                     sectionResult.MinStressImpactDirection[+face] = impact;
                     sectionResult.MinStressWindDirection[+face] = wind;
                     sectionResult.MinStressCorner[+face] = corner;
                  }

                  // keep track of max stress of ALL sections including the corner where it occurs
                  if (::IsLT(results.MaxStress, sectionResult.f[+impact][+wind][+corner]))
                  {
                     results.MaxStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                     results.MaxStress = sectionResult.f[+impact][+wind][+corner];
                     results.MaxStressImpactDirection = impact;
                     results.MaxStressWindDirection = wind;
                     results.MaxStressCorner = corner;
                  }

                  // keep track of min stress of ALL sections including the corner where it occurs
                  if (::IsLT(sectionResult.f[+impact][+wind][+corner], results.MinStress))
                  {
                     results.MinStressAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                     results.MinStress = sectionResult.f[+impact][+wind][+corner];
                     results.MinStressImpactDirection = impact;
                     results.MinStressWindDirection = wind;
                     results.MinStressCorner = corner;
                  }

                  // compute cracking moment and cracking factor of safety
                  Float64 mcr = 0; // if the direct stress exceeds the modulus of rupture, the beam is cracked before it is tilted...
                  Float64 fscr = 0; // ... and the FScr is 0.
                  Float64 theta_crack = 0;
                  Float64 f_direct = sectionResult.fDirect[+impact][+corner] + windSign * sectionResult.fw[+corner];

                  if (f_direct < fr)
                  {
                     // the direct stress is less than the modulus of rupture, therefore there needs to be additional moment applied to cause cracking
                     mcr = (f_direct - fr) * D / (Ixx * pntStress[+corner].X() - Ixy * pntStress[+corner].Y());

                     Float64 m = im * sectionResult.Mg;

                     theta_crack = (IsZero(m) ? ::BinarySign(results.ThetaEq[+impact][+wind]) * THETA_MAX : mcr / m);

                     if (results.AssumedTiltDirection == GirderSide::Right)
                     {
                        // girder is tilted to the right so flip the sign of the cracking angle
                        theta_crack *= -1;
                     }

                     theta_crack = ::ForceIntoRange(-THETA_MAX, theta_crack, THETA_MAX);

                     if (theta_crack < 0)
                     {
                        // the lateral moment due to girder self-weight must reverse direction in order to crack this flange tip
                        // that's impossible
                        fscr = Float64_Max;
                     }
                     else
                     {
                        Float64 alpha = crownSlope;
                        Float64 Mr = Ktheta * (theta_crack - alpha);
                        Float64 Ma = im * Wg * ((results.Dra[+ImpactDirection::NoImpact] + im * results.Zo[+ImpactDirection::NoImpact]) * theta_crack + ei + Zt) + Mot;
                        fscr = IsZero(Ma) ? Float64_Max : Mr / Ma;
                        fscr = Max(fscr, 0.0); // can't be less than zero... theta_crack-alpha < 0 means the slope of alpha alone will crack the girder
                     }
                  }

                  sectionResult.Mcr[+impact][+wind][+corner] = mcr;
                  sectionResult.ThetaCrack[+impact][+wind][+corner] = theta_crack;
                  sectionResult.FScr[+impact][+wind][+corner] = fscr;

                  // keep track of minimum FScr at this section
                  if (::IsLT(fscr, sectionResult.FScrMin))
                  {
                     sectionResult.FScrMin = fscr;
                     sectionResult.FScrImpactDirection = impact;
                     sectionResult.FScrWindDirection = wind;
                     sectionResult.FScrCorner = corner;
                  }
               } // if stable

               // keep track of the minimum FScr for all analysis points
               if (::IsLT(sectionResult.FScrMin, results.MinFScr))
               {
                  results.MinFScr = sectionResult.FScrMin;
                  results.FScrAnalysisPointIndex = sectionResult.AnalysisPointIndex;
                  results.FScrImpactDirection = sectionResult.FScrImpactDirection;
                  results.FScrWindDirection = sectionResult.FScrWindDirection;
                  results.FScrCorner = sectionResult.FScrCorner;
               }
            } // next wind direction
         } // next corner

         if (segment && concrete.GetType() != WBFL::Materials::ConcreteType::UHPC)
         {
            gbtAlternativeTensileStressRequirements altTensionRequirements;

            CComPtr<IShapeProperties> sp;
            shape->get_ShapeProperties(&sp);
            sp->get_Ytop(&altTensionRequirements.Ytg);

            altTensionRequirements.shape = shape;
            altTensionRequirements.rebarSection = rebarSection;
            altTensionRequirements.fy = pStabilityProblem->GetRebarYieldStrength();
            altTensionRequirements.fsMax = WBFL::Units::ConvertToSysUnits(30.0, WBFL::Units::Measure::KSI);
            altTensionRequirements.bLimitBarStress = true;
            altTensionRequirements.concreteType = concrete.GetType();
            altTensionRequirements.fc = concrete.GetFc();
            altTensionRequirements.bHasFct = concrete.HasAggSplittingStrength();
            altTensionRequirements.Fct = concrete.GetAggSplittingStrength();
            altTensionRequirements.density = concrete.GetDensity();

#if defined REBAR_FOR_DIRECT_TENSION
            altTensionRequirements.pntTopLeft.Move(    pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.fDirect[+impact][+Corner::TopLeft]);
            altTensionRequirements.pntTopRight.Move(   pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.fDirect[+impact][+Corner::TopRight]);
            altTensionRequirements.pntBottomLeft.Move( pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.fDirect[+impact][+Corner::BottomLeft]);
            altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.fDirect[+impact][+Corner::BottomRight]);

            gbtComputeAlternativeStressRequirements(&altTensionRequirements);
            sectionResult.altTensionRequirements[+impact] = altTensionRequirements;
#else
            for (int w = 0; w < 2; w++)
            {
               WindDirection wind = (WindDirection)w;
               altTensionRequirements.pntTopLeft.Move(    pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.f[+impact][+wind][+Corner::TopLeft]);
               altTensionRequirements.pntTopRight.Move(   pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.f[+impact][+wind][+Corner::TopRight]);
               altTensionRequirements.pntBottomLeft.Move( pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.f[+impact][+wind][+Corner::BottomLeft]);
               altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.f[+impact][+wind][+Corner::BottomRight]);

               gbtComputeAlternativeStressRequirements(&altTensionRequirements);
               sectionResult.altTensionRequirements[+impact][+wind] = altTensionRequirements;
            }
#endif // REBAR_FOR_DIRECT_TENSION
         } // if segment
      } // next impact

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure and roll over for all combinations of impact and wind

   // reaction at seated end
   Float64 Rseat = (pStabilityProblem->GetSeatedEnd() == GirderSide::Left ? results.Rl : results.Rr);
   ATLASSERT(IsEqual(Rseat,Wg * Lb / Ls));

   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;

      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

         Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

         Float64 ei = results.EccLateralSweep[+impact];
         Float64 alpha = crownSlope;

         Float64 im = IM[+impact];

         Float64 Zt = windSign * im * results.ZoWind[+ImpactDirection::NoImpact];
         Float64 Mot = windSign * results.MotWind;

         if (results.bRotationalStability[+impact][+wind])
         {
            ////////////////////////////////////////
            // Factor of Safety Against Failure
            ////////////////////////////////////////
            
            // This usually doesn't control because rollover will occur at a smaller angle then failure
            // However, we don't know this to be true in all cases so we compute FSf
            
            // compute theta max... PCI examples use a numerical solver in mathcad, however I derived the closed form solution.
            // (See SupportingDocuments folder for derivation)

            if (0 < results.ThetaEq[+impact][+wind] && ::IsLE(results.ThetaEq[+impact][+wind], alpha))
            {
               // girder is tilted to the left (CCW rotation, but it isn't tilted more than the superelevation
               // Mr = Ktheta(theta_roll - alpha) which is < 0
               // the girder is going to fail on the left side if it does not tilt at least equal to the superelevation
               // In the special case that theta_max = alpha, Mr is 0 and for equilibrium, Ma also must be zero
               // This is a perfectly balanced case and failure will not occur
               results.ThetaMax[+impact][+wind] = 0;
               results.FsFailure[+impact][+wind] = Float64_Max;
            }
            else
            {
               Float64 theta_max;
               if (IsZero(im * Wg))
               {
                  theta_max = THETA_MAX;
               }
               else
               {
                  Float64 sign = (results.ThetaEq[+impact][+wind] < 0 ? -1 : 1); // let equilibrium angle determine direction of failure mode

                  Float64 Z = Zt + ei + Mot / (im * Wg) + (im * results.Zo[+ImpactDirection::NoImpact] + results.Dra[+ImpactDirection::NoImpact] + sign * 2.5 * Zt) * alpha;
                  Float64 S = alpha * alpha + sign * Z / (2.5 * im * results.Zo[+ImpactDirection::NoImpact]);

                  ATLASSERT(0 <= S);
                  theta_max = alpha + sign * sqrt(S);
               }
               theta_max = ::ForceIntoRange(-THETA_MAX, theta_max, THETA_MAX);
               results.ThetaMax[+impact][+wind] = theta_max;
               ATLASSERT(::BinarySign(results.ThetaEq[+impact][+wind]) == ::BinarySign(theta_max));

               Float64 Mr = Ktheta * (theta_max - alpha); // resisting moment
               Float64 Ma = im * Wg * ((im * results.Zo[+ImpactDirection::NoImpact] * theta_max + Zt) * (1 + 2.5 * fabs(theta_max)) + results.Dra[+ImpactDirection::NoImpact] * theta_max + ei) + Mot; // acting moment
               Float64 FSf = IsLE(Ma, 0.0) ? Float64_Max : Mr / Ma;
               results.FsFailure[+impact][+wind] = FSf;
            }

            // if FSf < FScr then FSf = FScr (if the girder doesn't crack, it doesn't fail)
            results.AdjFsFailure[+impact][+wind] = Max(results.FsFailure[+impact][+wind], results.MinFScr);

            if (::IsLT(results.AdjFsFailure[+impact][+wind], results.MinAdjFsFailure))
            {
               results.MinFsFailure = results.FsFailure[+impact][+wind];
               results.MinAdjFsFailure = results.AdjFsFailure[+impact][+wind];
               results.FSfImpactDirection = impact;
               results.FSfWindDirection = wind;
            }

            ////////////////////////////////////////
            // Factor of Safety Against Rollover
            ////////////////////////////////////////
            
            // critical angle at rollover (this is the angle when the truck is just about to overturn)
            Float64 sign = (results.ThetaEq[+impact][+wind] < 0 ? -1 : 1); // let equilibrium angle determine direction of failure mode
            Float64 Zmax = Wcc / 2;
            Float64 Wro = windSign * results.Wwind;

            Float64 Mro = Wro * (Hrs + sign * Zmax * alpha);
            
            // if the rollover moment from the lateral loads exceeds the resisting moment from the vertical
            // reaction at the tire then there is no capacity left to take the K(theta-alpha) moment from
            // the girder above. consider this to be unstable for rollover
            Float64 mr = im * Rseat * (Zmax - sign * Hrs * alpha);
            Float64 ma = sign * Mro;

            results.bRolloverStability[+impact][+wind] = (mr < ma ? false : true);
            if (results.bRolloverStability[+impact][+wind])
            {
               Float64 Ma = mr - ma;
               Float64 theta_roll = sign * Ma / Ktheta + alpha;
               results.ThetaRollover[+impact][+wind] = theta_roll;
               ATLASSERT(::BinarySign(results.ThetaEq[+impact][+wind]) == ::BinarySign(theta_roll));

               Float64 Mr = Ktheta * (theta_roll - alpha);
               Ma = im * Wg * ((Zt + im * results.Zo[+ImpactDirection::NoImpact] * theta_roll) * (1 + 2.5 * fabs(theta_roll)) + results.Dra[+ImpactDirection::NoImpact] * theta_roll + ei) + Mot;
               Float64 FSr = IsZero(Ma) ? Float64_Max : Mr / Ma;
               results.FsRollover[+impact][+wind] = FSr;
            }
            else
            {
               // there is a rollover instability... rollover will happen so take the FS to be 0
               results.ThetaRollover[+impact][+wind] = 0;
               results.FsRollover[+impact][+wind] = 0;
            }

            if (::IsLT(results.FsRollover[+impact][+wind], results.MinFsRollover))
            {
               results.MinFsRollover = results.FsRollover[+impact][+wind];
               results.FSroImpactDirection = impact;
               results.FSroWindDirection = wind;
            }
         } // if  stable
      } // next wind direction
   } // next impact
}

void StabilityEngineer::AnalyzeHauling(const IGirder* pGirder,const IHaulingStabilityProblem* pStabilityProblem,HaulingResults& results) const
{
   CComPtr<IFem2dModel> model;
   Analyze(pGirder,pStabilityProblem,results,&model);

   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);

   CComPtr<IRebarLayout> rebarLayout;
   if ( segment )
   {
      // only need the rebar model if we are checking tension with rebar, and that can only happen
      // if the girder is modeled with an ISegment object
      GetRebarLayout(pGirder,&rebarLayout);
   }

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   results.ZoCF = results.Zo[+ImpactDirection::NoImpact]*results.Wcf/Wg;

   HaulingImpact impactUsage = pStabilityProblem->GetImpactUsage();
   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   std::array<Float64, 3> IM = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
   pGirder->GetSectionProperties(Lg / 2, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);
   if (::IsLT(Max(Wtop, Wbot) / 2,Xleft))
   {
      // we generally assume the girder tilts to the left. this is how the equations are developed in Mast and PCI.
      // however, we have a case where the CG is to the right of the centerline of the girder. this makes the
      // natural tendency of the girder to roll to the right.
      results.AssumedTiltDirection = GirderSide::Right;
   }


   const auto& concrete = pStabilityProblem->GetConcrete();
   Float64 fr = concrete.GetFlexureFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();
   Float64 Ktheta = pStabilityProblem->GetRotationalStiffness();
   Float64 crownSlope = pStabilityProblem->GetSupportSlope();
   Float64 superelevation = pStabilityProblem->GetSuperelevation();
   Float64 Hrs = pStabilityProblem->GetHeightOfRollAxis();
   Float64 Wcc = pStabilityProblem->GetSupportWidth();

   Float64 cfSign = (pStabilityProblem->GetCentrifugalForceType() == CFType::Adverse ? 1 : -1);

   // overturning moment due to wind and cf applied toward the left
   // Ywind and Dra are a function of impact because of impact forces in the horizontal
   // component of the lifting cable. Since this is a hauling case, such force effects
   // do not exist so we can just use the no impact case.
   results.MotWind = results.Wwind*results.Ywind[+ImpactDirection::NoImpact];
   results.MotCF   = results.Wcf*results.Dra[+ImpactDirection::NoImpact];

   for (int s = 0; s < 2; s++)
   {
      HaulingSlope slope = (HaulingSlope)s;
      for ( int i = 0; i < 3; i++ )
      {
         ImpactDirection impact = (ImpactDirection)i;

         Float64 alpha = (slope == HaulingSlope::CrownSlope ? crownSlope : superelevation);
         
         Float64 im = 1.0;
         if ( impactUsage == HaulingImpact::Both ||
             (impactUsage == HaulingImpact::NormalCrown && slope == HaulingSlope::CrownSlope) ||
             (impactUsage == HaulingImpact::MaxSuper    && slope == HaulingSlope::Superelevation)
            )
         {
            im = IM[+impact];
         }
      
         for ( int w = 0; w < 2; w++ )
         {
            WindDirection wind = (WindDirection)w;

            Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

            Float64 Zt = windSign*results.ZoWind[+impact];
            Float64 Mot = windSign*results.MotWind;
            if (slope == HaulingSlope::Superelevation)
            {
               Zt += cfSign*results.ZoCF;
               Mot += cfSign*results.MotCF;
            }

            Float64 ei = results.EccLateralSweep[+impact];

            results.ThetaEq[+slope][+impact][+wind] = (Ktheta*alpha + im*Wg*(ei + Zt) + Mot)/(Ktheta - im*Wg*(results.Dra[+impact] + im*results.Zo[+ImpactDirection::NoImpact]));
            // if ThetaEq < 0, then girder is rolling to the right

            if (results.ThetaEq[+slope][+impact][+wind] < -THETA_MAX || THETA_MAX < results.ThetaEq[+slope][+impact][+wind])
            {
               // if the equilibrium angle is excessive the rotational spring stiffness is probably too small...
               // consider this an unstable condition
               results.bRotationalStability[+slope][+impact][+wind] = false;
               results.FsRollover[+slope][+impact][+wind] = 0;
               results.MinFsRollover[+slope] = 0;
               results.MinFScr[+slope] = 0;
            }
         } // next wind
      } // next impact
   } // next slope

   PoiIDType poiID = 0;
   CComQIPtr<IFem2dModelResults> femResults(model);
   const auto& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   IndexType analysisPointIdx = 0;
   for( const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 X = pAnalysisPoint->GetLocation();

      HaulingSectionResult sectionResult;

      sectionResult.AnalysisPointIndex = analysisPointIdx++;

      CComPtr<IRebarSection> rebarSection;
      CComPtr<IShape> shape;
      if (segment)
      {
         rebarLayout->CreateRebarSection(X, INVALID_INDEX, &rebarSection);
         segment->get_GirderShape(X, sbLeft, cstGirder, &shape); // this is in girder section coordinates

         // position the shape in centroidal/stress point coordinates
         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         CComPtr<IPoint2d> pntCG;
         props->get_Centroid(&pntCG);
         Float64 x, y;
         pntCG->Location(&x, &y);
         CComQIPtr<IXYPosition> position(shape);
         position->Offset(-x, -y);
      }

      // Get forces from external loads
      Float64 fx,fy,mz;
      femResults->ComputePOIForces(LCID_GIRDER,poiID,mftLeft,lotMember,&fx,&fy,&mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mg = mz;

      femResults->ComputePOIForces(LCID_WIND,poiID,mftLeft,lotMember,&fx,&fy,&mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mw = mz;

      femResults->ComputePOIForces(LCID_CF,poiID,mftLeft,lotMember,&fx,&fy,&mz);
      ATLASSERT(IsZero(fx));
      mz = IsZero(mz) ? 0 : mz;
      sectionResult.Mcf = mz;

      Float64 Hg,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Wbf,Wtf;
      pGirder->GetSectionProperties(X,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wtf,&Wbf);

      Float64 D = Ixx*Iyy - Ixy*Ixy;

      std::array<Point, 4> pntStress;
      pGirder->GetStressPoints(X, &pntStress[+Corner::TopLeft], &pntStress[+Corner::TopRight], &pntStress[+Corner::BottomLeft], &pntStress[+Corner::BottomRight]);

      // stress due to prestressing
      std::vector<LPCTSTR> vNames = pStabilityProblem->GetPrestressNames();
      for(const auto strName : vNames)
      {
         Float64 Fpe, Xps, Yps;
         pStabilityProblem->GetFpe(strName,X,&Fpe,&Xps,&Yps);
         Float64 eyps = Ytop - Yps; // eccentricity of strands (positive values means ps force is below CG)
         Float64 exps = Xleft - Xps; // lateral eccentricity of strands (positive values means ps force is left of the CG)

         Float64 Mxps = -Fpe*eyps;
         Float64 Myps = -Fpe*exps;

         for (int c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            Float64 f = ((Myps*Ixx + Mxps*Ixy)*pntStress[+corner].X() - (Mxps*Iyy + Myps*Ixy)*pntStress[+corner].Y()) / D - (Fpe / Ag);
            sectionResult.fps[+corner] += f;
         }
      }

      Float64 MxCF = 0;
      Float64 MyCF = sectionResult.Mcf;
      Float64 MxGirder = sectionResult.Mg;
      Float64 MyGirder = 0;
      Float64 MxWind = 0;
      Float64 MyWind = -sectionResult.Mw;
      for (int c = 0; c < 4; c++)
      {
         Corner corner = (Corner)c;

         // stress due to plumb girder (no impact)
         sectionResult.fg[+corner] = ((MyGirder*Ixx + MxGirder*Ixy)*pntStress[+corner].X() - (MxGirder*Iyy + MyGirder*Ixy)*pntStress[+corner].Y()) / D;

         // stress due to wind towards the left
         sectionResult.fw[+corner] = ((MyWind*Ixx + MxWind*Ixy)*pntStress[+corner].X() - (MxWind*Iyy + MyWind*Ixy)*pntStress[+corner].Y()) / D;

         // stress due to centrifugal forces
         sectionResult.fcf[+corner] = ((MyCF*Ixx + MxCF*Ixy)*pntStress[+corner].X() - (MxCF*Iyy + MyCF*Ixy)*pntStress[+corner].Y()) / D;
      } // next corner

      for (int s = 0; s < 2; s++)
      {
         HaulingSlope slope = (HaulingSlope)s;

         for ( int i = 0; i < 3; i++ )
         {
            ImpactDirection impact = (ImpactDirection)i;
      
            Float64 im = 1.0;
            if (impactUsage == HaulingImpact::Both ||
               (impactUsage == HaulingImpact::NormalCrown && slope == HaulingSlope::CrownSlope) ||
               (impactUsage == HaulingImpact::MaxSuper    && slope == HaulingSlope::Superelevation)
               )
            {
               im = IM[+impact];
            }

            for (int cn = 0; cn < 4; cn++)
            {
               Corner corner = (Corner)cn;

               GirderFace face = GetFace(corner);
               Float64 b = (face == GirderFace::Top ? Wtf : Wbf);

               Float64 cornerSign = (corner == Corner::TopLeft || corner == Corner::BottomLeft ? 1 : -1);

               // stress due to direct loads (plumb girder)
               sectionResult.fDirect[+slope][+impact][+corner] = sectionResult.fps[+corner] + im*sectionResult.fg[+corner];

               // keep track of the max direct stress at this section including the corner where it occurs
               if (::IsLT(sectionResult.fMaxDirect[+slope][+face], sectionResult.fDirect[+slope][+impact][+corner]))
               {
                  sectionResult.fMaxDirect[+slope][+face] = sectionResult.fDirect[+slope][+impact][+corner];
                  sectionResult.MaxDirectStressImpactDirection[+slope][+face] = impact;
                  sectionResult.MaxDirectStressCorner[+slope][+face] = corner;
               }

               // keep track of the min direct stress at this section including the corner where it occurs
               if (::IsLT(sectionResult.fDirect[+slope][+impact][+corner], sectionResult.fMinDirect[+slope][+face]))
               {
                  sectionResult.fMinDirect[+slope][+face] = sectionResult.fDirect[+slope][+impact][+corner];
                  sectionResult.MinDirectStressImpactDirection[+slope][+face] = impact;
                  sectionResult.MinDirectStressCorner[+slope][+face] = corner;
               }

               // keep track of the max direct stress of ALL sections including the corner where it occurs
               if (::IsLT(results.MaxDirectStress[+slope], sectionResult.fDirect[+slope][+impact][+corner]))
               {
                  results.MaxDirectStress[+slope] = sectionResult.fDirect[+slope][+impact][+corner];
                  results.MaxDirectStressAnalysisPointIndex[+slope] = sectionResult.AnalysisPointIndex;
                  results.MaxDirectStressImpactDirection[+slope] = impact;
                  results.MaxDirectStressCorner[+slope] = corner;
               }

               // keep track of the min direct stress of ALL sections including the corner where it occurs
               if (::IsLT(sectionResult.fDirect[+slope][+impact][+corner], results.MinDirectStress[+slope]))
               {
                  results.MinDirectStress[+slope] = sectionResult.fDirect[+slope][+impact][+corner];
                  results.MinDirectStressAnalysisPointIndex[+slope] = sectionResult.AnalysisPointIndex;
                  results.MinDirectStressImpactDirection[+slope] = impact;
                  results.MinDirectStressCorner[+slope] = corner;
               }

               for ( int w = 0; w < 2; w++ )
               {
                  WindDirection wind = (WindDirection)w;

                  if (results.bRotationalStability[+slope][+impact][+wind])
                  {
                     Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

                     Float64 Zt = windSign*im*results.ZoWind[+ImpactDirection::NoImpact]; // using NoImpact because we scale by IM here
                     Float64 Mot = windSign*results.MotWind;
                     if (slope == HaulingSlope::Superelevation)
                     {
                        Mot += cfSign*results.MotCF;
                        Zt += cfSign*results.ZoCF;
                     }

                     Float64 ei = results.EccLateralSweep[+impact];

                     // stress due to lateral loads caused by the girder being tilted
                     //Float64 Mx = 0;
                     Float64 My = -1 * im * sectionResult.Mg*results.ThetaEq[+slope][+impact][+wind]; // this sign of ThetaEq will take care of the girder rolling to the right
                     Float64 f = ((My*Ixx/* + Mx*Ixy*/)*pntStress[+corner].X() - (/*Mx*Iyy + */My*Ixy)*pntStress[+corner].Y()) / D;
                     if (results.AssumedTiltDirection == GirderSide::Right)
                     {
                        // girder is tilted to the right so flip the sign
                        // f is computed assuming tilt to the left
                        f *= -1;
                     }
                     sectionResult.fTilt[+slope][+impact][+wind][+corner] = f;

                     // total stress
                     sectionResult.f[+slope][+impact][+wind][+corner] = sectionResult.fDirect[+slope][+impact][+corner] + sectionResult.fTilt[+slope][+impact][+wind][+corner] + windSign*sectionResult.fw[+corner];
                     if (slope == HaulingSlope::Superelevation)
                     {
                        sectionResult.f[+slope][+impact][+wind][+corner] -= cfSign*sectionResult.fcf[+corner];
                     }

                     // keep track of max stress at this section including the corner where it occurs
                     if (::IsLT(sectionResult.fMax[+slope][+face], sectionResult.f[+slope][+impact][+wind][+corner]))
                     {
                        sectionResult.fMax[+slope][+face] = sectionResult.f[+slope][+impact][+wind][+corner];
                        sectionResult.MaxStressImpactDirection[+slope][+face] = impact;
                        sectionResult.MaxStressWindDirection[+slope][+face] = wind;
                        sectionResult.MaxStressCorner[+slope][+face] = corner;
                     }

                     // keep track of min stress at this section including the corner where it occurs
                     if (::IsLT(sectionResult.f[+slope][+impact][+wind][+corner], sectionResult.fMin[+slope][+face]))
                     {
                        sectionResult.fMin[+slope][+face] = sectionResult.f[+slope][+impact][+wind][+corner];
                        sectionResult.MinStressImpactDirection[+slope][+face] = impact;
                        sectionResult.MinStressWindDirection[+slope][+face] = wind;
                        sectionResult.MinStressCorner[+slope][+face] = corner;
                     }

                     // keep track of max stress of ALL sections including the corner where it occurs
                     if (::IsLT(results.MaxStress[+slope], sectionResult.f[+slope][+impact][+wind][+corner]))
                     {
                        results.MaxStressAnalysisPointIndex[+slope] = sectionResult.AnalysisPointIndex;
                        results.MaxStress[+slope] = sectionResult.f[+slope][+impact][+wind][+corner];
                        results.MaxStressImpactDirection[+slope] = impact;
                        results.MaxStressWindDirection[+slope] = wind;
                        results.MaxStressCorner[+slope] = corner;
                     }

                     // keep track of min stress of ALL sections including the corner where it occurs
                     if (::IsLT(sectionResult.f[+slope][+impact][+wind][+corner], results.MinStress[+slope]))
                     {
                        results.MinStressAnalysisPointIndex[+slope] = sectionResult.AnalysisPointIndex;
                        results.MinStress[+slope] = sectionResult.f[+slope][+impact][+wind][+corner];
                        results.MinStressImpactDirection[+slope] = impact;
                        results.MinStressWindDirection[+slope] = wind;
                        results.MinStressCorner[+slope] = corner;
                     }

                     // compute cracking moment and cracking factor of safety
                     Float64 mcr = 0; // if the direct stress exceeds the modulus of rupture, the beam is cracked before it is tilted...
                     Float64 fscr = 0; // ... and the FScr is 0.
                     Float64 theta_crack = 0;
                     Float64 f_direct = sectionResult.fDirect[+slope][+impact][+corner] + windSign*sectionResult.fw[+corner];
                     if (slope == HaulingSlope::Superelevation)
                     {
                        f_direct -= cfSign*sectionResult.fcf[+corner];
                     }

                     if (f_direct < fr)
                     {
                        // the direct stress is less than the modulus of rupture, therefore there needs to be additional moment applied to cause cracking
                        mcr = (f_direct - fr)*D / (Ixx*pntStress[+corner].X() - Ixy*pntStress[+corner].Y());

                        Float64 m = im*sectionResult.Mg;

                        theta_crack = (IsZero(m) ? ::BinarySign(results.ThetaEq[+slope][+impact][+wind])*THETA_MAX : mcr / m);

                        if (results.AssumedTiltDirection == GirderSide::Right)
                        {
                           // girder is tilted to the right so flip the sign of the cracking angle
                           theta_crack *= -1;
                        }

                        theta_crack = ::ForceIntoRange(-THETA_MAX, theta_crack, THETA_MAX);

                        if (theta_crack < 0)
                        {
                           // the lateral moment due to girder self-weight must reverse direction in order to crack this flange tip
                           // that's impossible
                           fscr = Float64_Max;
                        }
                        else
                        {
                           Float64 alpha = (slope == HaulingSlope::CrownSlope ? crownSlope : superelevation);
                           Float64 Mr = Ktheta*(theta_crack - alpha);
                           Float64 Ma = im*Wg*((results.Dra[+ImpactDirection::NoImpact] + im*results.Zo[+ImpactDirection::NoImpact])*theta_crack + ei + Zt) + Mot;
                           fscr = IsZero(Ma) ? Float64_Max : Mr / Ma;
                           fscr = Max(fscr, 0.0); // can't be less than zero... theta_crack-alpha < 0 means the slope of alpha alone will crack the girder
                        }
                     }

                     sectionResult.Mcr[+slope][+impact][+wind][+corner] = mcr;
                     sectionResult.ThetaCrack[+slope][+impact][+wind][+corner] = theta_crack;
                     sectionResult.FScr[+slope][+impact][+wind][+corner] = fscr;

                     // keep track of minimum FScr at this section
                     if (::IsLT(fscr, sectionResult.FScrMin[+slope]))
                     {
                        sectionResult.FScrMin[+slope] = fscr;
                        sectionResult.FScrImpactDirection[+slope] = impact;
                        sectionResult.FScrWindDirection[+slope] = wind;
                        sectionResult.FScrCorner[+slope] = corner;
                     }
                  } // if stable

                  // keep track of the minimum FScr for all analysis points
                  if (::IsLT(sectionResult.FScrMin[+slope], results.MinFScr[+slope]))
                  {
                     results.MinFScr[+slope] = sectionResult.FScrMin[+slope];
                     results.FScrAnalysisPointIndex[+slope] = sectionResult.AnalysisPointIndex;
                     results.FScrImpactDirection[+slope] = sectionResult.FScrImpactDirection[+slope];
                     results.FScrWindDirection[+slope] = sectionResult.FScrWindDirection[+slope];
                     results.FScrCorner[+slope] = sectionResult.FScrCorner[+slope];
                  }
               } // next wind direction
            } // next corner

            if (segment && concrete.GetType() != WBFL::Materials::ConcreteType::UHPC)
            {
               gbtAlternativeTensileStressRequirements altTensionRequirements;

               CComPtr<IShapeProperties> sp;
               shape->get_ShapeProperties(&sp);
               sp->get_Ytop(&altTensionRequirements.Ytg);

               altTensionRequirements.shape = shape;
               altTensionRequirements.rebarSection = rebarSection;
               altTensionRequirements.fy = pStabilityProblem->GetRebarYieldStrength();
               altTensionRequirements.fsMax = WBFL::Units::ConvertToSysUnits(30.0, WBFL::Units::Measure::KSI);
               altTensionRequirements.bLimitBarStress = true;
               altTensionRequirements.concreteType = concrete.GetType();
               altTensionRequirements.fc = concrete.GetFc();
               altTensionRequirements.bHasFct = concrete.HasAggSplittingStrength();
               altTensionRequirements.Fct = concrete.GetAggSplittingStrength();
               altTensionRequirements.density = concrete.GetDensity();

#if defined REBAR_FOR_DIRECT_TENSION
               altTensionRequirements.pntTopLeft.Move(    pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.fDirect[+slope][+impact][+Corner::TopLeft]);
               altTensionRequirements.pntTopRight.Move(   pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.fDirect[+slope][+impact][+Corner::TopRight]);
               altTensionRequirements.pntBottomLeft.Move( pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.fDirect[+slope][+impact][+Corner::BottomLeft]);
               altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.fDirect[+slope][+impact][+Corner::BottomRight]);

               gbtComputeAlternativeStressRequirements(&altTensionRequirements);
               sectionResult.altTensionRequirements[+slope][+impact] = altTensionRequirements;
#else
               for (int w = 0; w < 2; w++)
               {
                  WindDirection wind = (WindDirection)w;
                  altTensionRequirements.pntTopLeft.Move(    pntStress[+Corner::TopLeft].X(),     pntStress[+Corner::TopLeft].Y(),     sectionResult.f[+slope][+impact][+wind][+Corner::TopLeft]);
                  altTensionRequirements.pntTopRight.Move(   pntStress[+Corner::TopRight].X(),    pntStress[+Corner::TopRight].Y(),    sectionResult.f[+slope][+impact][+wind][+Corner::TopRight]);
                  altTensionRequirements.pntBottomLeft.Move( pntStress[+Corner::BottomLeft].X(),  pntStress[+Corner::BottomLeft].Y(),  sectionResult.f[+slope][+impact][+wind][+Corner::BottomLeft]);
                  altTensionRequirements.pntBottomRight.Move(pntStress[+Corner::BottomRight].X(), pntStress[+Corner::BottomRight].Y(), sectionResult.f[+slope][+impact][+wind][+Corner::BottomRight]);

                  gbtComputeAlternativeStressRequirements(&altTensionRequirements);
                  sectionResult.altTensionRequirements[+slope][+impact][+wind] = altTensionRequirements;
               }
#endif // REBAR_FOR_DIRECT_TENSION
            } // if segment
         } // next impact
      } // next slope

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure and roll over for all combinations of impact and wind
   for (int s = 0; s < 2; s++)
   {
      HaulingSlope slope = (HaulingSlope)s;

      for ( int i = 0; i < 3; i++ )
      {
         ImpactDirection impact = (ImpactDirection)i;

         for ( int w = 0; w < 2; w++ )
         {
            WindDirection wind = (WindDirection)w;

            Float64 windSign = (wind == WindDirection::Left ? 1 : -1);

            Float64 ei = results.EccLateralSweep[+impact];
            Float64 alpha = (slope == HaulingSlope::CrownSlope ? crownSlope : superelevation);

            Float64 im = 1.0;
            if (impactUsage == HaulingImpact::Both ||
               (impactUsage == HaulingImpact::NormalCrown && slope == HaulingSlope::CrownSlope) ||
               (impactUsage == HaulingImpact::MaxSuper    && slope == HaulingSlope::Superelevation)
               )
            {
               im = IM[+impact];
            }

            Float64 Zt = windSign*im*results.ZoWind[+ImpactDirection::NoImpact];
            Float64 Mot = windSign*results.MotWind;
            if (slope == HaulingSlope::Superelevation)
            {
               Zt += cfSign*results.ZoCF;
               Mot += cfSign*results.MotCF;
            }

            if (results.bRotationalStability[+slope][+impact][+wind])
            {
               ////////////////////////////////////////
               // Factor of Safety Against Failure
               ////////////////////////////////////////

               // This usually doesn't control because rollover will occur at a smaller angle then failure
               // However, we don't know this to be true in all cases so we compute FSf

               // compute theta max... PCI examples use a numerical solver in mathcad, however I derived the closed form solution.
               // (See SupportingDocuments folder for derivation)

               if (0 < results.ThetaEq[+slope][+impact][+wind] && ::IsLE(results.ThetaEq[+slope][+impact][+wind], alpha))
               {
                  // girder is tilted to the left (CCW rotation, but it isn't tilted more than the superelevation
                  // Mr = Ktheta(theta_roll - alpha) which is < 0
                  // the girder is going to fail on the left side if it does not tilt at least equal to the superelevation
                  // In the special case that theta_max = alpha, Mr is 0 and for equilibrium, Ma also must be zero
                  // This is a perfectly balanced case and failure will not occur
                  results.ThetaMax[+slope][+impact][+wind] = 0;
                  results.FsFailure[+slope][+impact][+wind] = Float64_Max;
               }
               else
               {
                  Float64 theta_max;
                  if (IsZero(im*Wg))
                  {
                     theta_max = THETA_MAX;
                  }
                  else
                  {
                     Float64 sign = (results.ThetaEq[+slope][+impact][+wind] < 0 ? -1 : 1); // let equilibrium angle determine direction of failure mode

                     Float64 Z = Zt + ei + Mot / (im*Wg) + (im*results.Zo[+ImpactDirection::NoImpact] + results.Dra[+ImpactDirection::NoImpact] + sign*2.5*Zt)*alpha;
                     Float64 S = alpha*alpha + sign*Z / (2.5 * im*results.Zo[+ImpactDirection::NoImpact]);

                     ATLASSERT(0 <= S);
                     theta_max = alpha + sign*sqrt(S);
                  }
                  theta_max = ::ForceIntoRange(-THETA_MAX, theta_max, THETA_MAX);
                  results.ThetaMax[+slope][+impact][+wind] = theta_max;
                  ATLASSERT(::BinarySign(results.ThetaEq[+slope][+impact][+wind]) == ::BinarySign(theta_max));

                  Float64 Mr = Ktheta*(theta_max - alpha); // resisting moment
                  Float64 Ma = im*Wg*((im*results.Zo[+ImpactDirection::NoImpact] * theta_max + Zt)*(1 + 2.5*fabs(theta_max)) + results.Dra[+ImpactDirection::NoImpact] * theta_max + ei) + Mot; // acting moment
                  Float64 FSf = IsLE(Ma, 0.0) ? Float64_Max : Mr / Ma;
                  results.FsFailure[+slope][+impact][+wind] = FSf;
               }

               // if FSf < FScr then FSf = FScr (if the girder doesn't crack, it doesn't fail)
               results.AdjFsFailure[+slope][+impact][+wind] = Max(results.FsFailure[+slope][+impact][+wind], results.MinFScr[+slope]);

               if (::IsLT(results.AdjFsFailure[+slope][+impact][+wind], results.MinAdjFsFailure[+slope]))
               {
                  results.MinFsFailure[+slope] = results.FsFailure[+slope][+impact][+wind];
                  results.MinAdjFsFailure[+slope] = results.AdjFsFailure[+slope][+impact][+wind];
                  results.FSfImpactDirection[+slope] = impact;
                  results.FSfWindDirection[+slope] = wind;
               }

               ////////////////////////////////////////
               // Factor of Safety Against Rollover
               ////////////////////////////////////////

               // critical angle at rollover (this is the angle when the truck is just about to overturn)
               Float64 sign = (results.ThetaEq[+slope][+impact][+wind] < 0 ? -1 : 1); // let equilibrium angle determine direction of failure mode
               Float64 Zmax = Wcc / 2;
               Float64 Wro = windSign*results.Wwind;
               if (slope == HaulingSlope::Superelevation)
               {
                  Wro += cfSign*results.Wcf;
               }

               Float64 Mro = Wro*(Hrs + sign*Zmax*alpha);
               // if the rollover moment from the lateral loads exceeds the resisting moment from the vertical
               // reaction at the tire then there is no capacity left to take the K(theta-alpha) moment from
               // the girder above. consider this to be unstable for rollover
               Float64 mr = im*Wg*(Zmax - sign*Hrs*alpha);
               Float64 ma = sign*Mro;

               results.bRolloverStability[+slope][+impact][+wind] = (mr < ma ? false : true);
               if (results.bRolloverStability[+slope][+impact][+wind])
               {
                  Float64 Ma = mr - ma;
                  Float64 theta_roll = sign*Ma / Ktheta + alpha;
                  results.ThetaRollover[+slope][+impact][+wind] = theta_roll;
                  ATLASSERT(::BinarySign(results.ThetaEq[+slope][+impact][+wind]) == ::BinarySign(theta_roll));

                  Float64 Mr = Ktheta*(theta_roll - alpha);
                  Ma = im*Wg*((Zt + im*results.Zo[+ImpactDirection::NoImpact] * theta_roll)*(1 + 2.5*fabs(theta_roll)) + results.Dra[+ImpactDirection::NoImpact] * theta_roll + ei) + Mot;
                  Float64 FSr = IsZero(Ma) ? Float64_Max : Mr / Ma;
                  results.FsRollover[+slope][+impact][+wind] = FSr;
               }
               else
               {
                  // there is a rollover instability... rollover will happen so take the FS to be 0
                  results.ThetaRollover[+slope][+impact][+wind] = 0;
                  results.FsRollover[+slope][+impact][+wind] = 0;
               }

               if (::IsLT(results.FsRollover[+slope][+impact][+wind], results.MinFsRollover[+slope]))
               {
                  results.MinFsRollover[+slope] = results.FsRollover[+slope][+impact][+wind];
                  results.FSroImpactDirection[+slope] = impact;
                  results.FSroWindDirection[+slope] = wind;
               }
            } // if  stable
         } // next wind direction
      } // next impact
   } // next slope type
}

void StabilityEngineer::BuildModel(const IGirder* pGirder,const IStabilityProblem* pStabilityProblem,Results& results,IFem2dModel** ppModel) const
{
   if (*ppModel)
   {
      (*ppModel)->Clear();
   }
   else
   {
      CComPtr<IFem2dModel> model;
      model.CoCreateInstance(CLSID_Fem2dModel);
      model.CopyTo(ppModel);
   }

   Float64 Lg = pGirder->GetGirderLength();

   Float64 tolerance = Lg / 10000.0; // This is the same tolerance as used by the LBAM

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   // Very small elements will crash the LBAM. Get rid of them
   Ll = IsZero(Ll, tolerance) ? 0.0 : Ll;
   Lr = IsZero(Lr, tolerance) ? 0.0 : Lr;

   // this builds a model with unequal overhangs (if Ll != Lr)
   Float64 leftSupportLoc  = Ll;
   Float64 rightSupportLoc = Lg - Lr;

   // fill up a vector of joint locations
   // joints occur at each section change
   Float64 X = 0;
   std::vector<Float64> vX;
   IndexType nSections = pGirder->GetSectionCount();
   ATLASSERT(0 < nSections);
   for ( IndexType sectIdx = 0; sectIdx < nSections; sectIdx++ )
   {
      Float64 L = pGirder->GetSectionLength(sectIdx);
      vX.push_back(X);
      X += L;
   }
   vX.push_back(X); // joint at right end of beam

   // add joints at support locations
   vX.push_back(leftSupportLoc);
   vX.push_back(rightSupportLoc);

   // eliminate duplicates - carefully
   std::sort(vX.begin(),vX.end());

   std::vector<Float64>::iterator righty(vX.begin());
   std::vector<Float64>::iterator lefty(righty++);
   while(righty != vX.end())
   {
      bool didErase = false;
      // POI's are very close, blast one
      if (IsEqual(*lefty,*righty))
      {
         vX.erase(lefty);
         didErase = true;
      }
      else if (IsEqual(*lefty,*righty,tolerance))
      {
         // within tolerance - delete non-supports and non-ends if an option
         if (*lefty==leftSupportLoc || *lefty==0.0)
         {
            vX.erase(righty);
            didErase = true;
         }
         else if (*righty==rightSupportLoc || *righty==Lg)
         {
            vX.erase(lefty);
            didErase = true;
         }
         else
         {
            vX.erase(righty);
            didErase = true;
         }
      }

      if (didErase)
      {
         lefty = vX.begin(); // inefficient, but have to restart to recoup left iterator in proper order
         righty = lefty;
         righty++;
      }
      else
      {
         lefty++;
         righty++;
      }
   }

   // Layout joints
   JointIDType jntID = 0;
   JointIDType leftSupportJntID = INVALID_ID;
   JointIDType rightSupportJntID = INVALID_ID;
   CComPtr<IFem2dJointCollection> joints;
   (*ppModel)->get_Joints(&joints);
   for(const auto& X : vX)
   {
      CComPtr<IFem2dJoint> jnt;
      joints->Create(jntID,X,0,&jnt);

      if ( leftSupportJntID==INVALID_ID && IsEqual(X,leftSupportLoc,tolerance) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtFx);
         jnt->ReleaseDof(jrtMz);
         leftSupportJntID = jntID;
      }
      else if (rightSupportJntID==INVALID_ID &&  IsEqual(X,rightSupportLoc,tolerance) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtMz);
         rightSupportJntID = jntID;
      }

      jntID++;
   }

   ATLASSERT(leftSupportJntID != INVALID_ID && rightSupportJntID != INVALID_ID); // missing support. we will crash
                                                                                 
   // Create FEM members

   const auto& concrete = pStabilityProblem->GetConcrete();
   Float64 Ec = concrete.GetE();

   // use middle of girder section properties for EA and EI
   Float64 Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
   pGirder->GetSectionProperties(Lg / 2, &Ag, &Ixx, &Iyy, &Ixy, &Xleft, &Ytop, &Hg, &Wtop, &Wbot);
   Float64 EA = Ec*Ag;
   Float64 EI = Ec*(Ixx*Iyy - Ixy*Ixy) / Iyy;

   CComPtr<IFem2dMemberCollection> members;
   (*ppModel)->get_Members(&members);

   jntID = 1;
   MemberIDType mbrID = 0;
   CComPtr<IFem2dMember> member;
   auto prevIter(vX.begin());
   auto iter = prevIter + 1;
   auto end(vX.end());
   for (; iter != end; iter++, jntID++, mbrID++)
   {
      member.Release();
      members->Create(mbrID, jntID - 1, jntID, EA, EI, &member);
   }

   // Apply Loads

   CComPtr<IFem2dLoadingCollection> loadings;
   (*ppModel)->get_Loadings(&loadings);

   CComPtr<IFem2dLoading> swLoading;
   loadings->Create(LCID_GIRDER,&swLoading);

   CComPtr<IFem2dLoading> cfLoading;
   loadings->Create(LCID_CF,&cfLoading);

   CComPtr<IFem2dLoading> windLoading;
   loadings->Create(LCID_WIND,&windLoading);

   CComPtr<IFem2dLoading> liftLoading;
   loadings->Create(LCID_LIFT,&liftLoading);

   CComPtr<IFem2dDistributedLoadCollection> swDistributedLoads;
   swLoading->get_DistributedLoads(&swDistributedLoads);

   CComPtr<IFem2dPointLoadCollection> swPointLoads;
   swLoading->get_PointLoads(&swPointLoads);

   CComPtr<IFem2dDistributedLoadCollection> cfDistributedLoads;
   cfLoading->get_DistributedLoads(&cfDistributedLoads);

   CComPtr<IFem2dDistributedLoadCollection> windDistributedLoads;
   windLoading->get_DistributedLoads(&windDistributedLoads);

   CComPtr<IFem2dJointLoadCollection> liftJointLoads;
   liftLoading->get_JointLoads(&liftJointLoads);

   CComPtr<IFem2dDistributedLoad> distLoad;



   Float64 g = WBFL::Units::System::GetGravitationalAcceleration();
   Float64 density = concrete.GetDensityForWeight();
   Float64 unitWeight = density*g;


   WindType windLoadType;
   Float64 windLoad;
   pStabilityProblem->GetWindLoading(&windLoadType,&windLoad);
   Float64 WindPressure;
   if ( windLoadType == WindType::Pressure )
   {
      WindPressure = windLoad;
   }
   else
   {
      Float64 Cd = pGirder->GetDragCoefficient();
      WindPressure = ComputePz(windLoad,Cd);
   }
   results.WindPressure = WindPressure;
   
   Float64 CFfactor = 0;
   const IHaulingStabilityProblem* pHaulingProblem = dynamic_cast<const IHaulingStabilityProblem*>(pStabilityProblem);
   if ( pHaulingProblem )
   {
      Float64 V = pHaulingProblem->GetVelocity();
      Float64 R = pHaulingProblem->GetTurningRadius();
      ATLASSERT(R != 0.0);
      CFfactor = (V*V)/(g*R);
   }

   Float64 eb, Wb;
   pStabilityProblem->GetAppurtenanceLoading(&eb, &Wb);

   Float64 Wg = 0;
   Float64 Wcf = 0;
   Float64 Wwind = 0;
   Float64 Awind = 0;
   Float64 YwindAwind = 0;
   Float64 start = 0;
   LoadIDType loadID = 0;
   for (IndexType sectIdx = 0; sectIdx < nSections; sectIdx++)
   {
      Float64 Ls = pGirder->GetSectionLength(sectIdx);
      Float64 end = start + Ls;
      if (IsZero(Ls))
      {
         continue;
      }

      std::array<Float64, 2> Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtop, Wbot;
      pGirder->GetSectionProperties(sectIdx, Section::Start, &Ag[+Section::Start], &Ixx[+Section::Start], &Iyy[+Section::Start], &Ixy[+Section::Start], &Xleft[+Section::Start], &Ytop[+Section::Start], &Hg[+Section::Start], &Wtop[+Section::Start], &Wbot[+Section::Start]);
      pGirder->GetSectionProperties(sectIdx, Section::End, &Ag[+Section::End], &Ixx[+Section::End], &Iyy[+Section::End], &Ixy[+Section::End], &Xleft[+Section::End], &Ytop[+Section::End], &Hg[+Section::End], &Wtop[+Section::End], &Wbot[+Section::End]);

      MemberIDType mbrIDStart, mbrIDEnd;
      Float64 xStart, xEnd;
      FindMember(*ppModel, start, &mbrIDStart, &xStart);
      FindMember(*ppModel, end, &mbrIDEnd, &xEnd);

      if (mbrIDStart == mbrIDEnd && IsEqual(xStart, xEnd))
      {
         continue;
      }

      // Self-weight load
      Float64 wStart = Ag[+Section::Start] * unitWeight + Wb;
      Float64 wEnd = Ag[+Section::End] * unitWeight + Wb;

      // weight = average force * distance = [(wStart+wEnd)/2]*(Ls)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      Float64 wg = (wStart + wEnd)*Ls;
      Wg += wg;

      // Centrifugal force
      // cumulate the total centrifugal force
      // average force * distance = [(wStart+wEnd)/2]*(Ls)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      Float64 cfStart = wStart*CFfactor;
      Float64 cfEnd = wEnd*CFfactor;
      Wcf += (cfStart + cfEnd)*Ls;

      // Wind
      Float64 windStart = Hg[+Section::Start] * WindPressure;
      Float64 windEnd = Hg[+Section::End] * WindPressure;
      // cumulate the total wind load
      // average wind load * distance = [(wStart+wEnd)/2]*(Ls)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      Float64 w_wind = (windStart + windEnd)*Ls;
      Wwind += w_wind;

      // the location of the resultant wind force is Sum(ExposedArea*DepthToCGofExposedArea)/(Total Exposed Area)
      // NOTE: if we use WindForce = (ExposedArea*WindPressure) and WindPressure is 0, Ywind = 0... but we really want 
      // the location of the wind force if there was one
      // Assuming sections that taper linearly in depth, the DepthToCGofExposedArea for each segment is the centroid of a trapezoid
      // y = (a^2 + ab + b^2)/(3(a+b))
      // Exposed Area = (a+b)L/2
      // Where we are doing the summation. The negative is because we are measuring down from the top which is what we need for
      // girder section coordinates
      Float64 a = Hg[+Section::Start];
      Float64 b = Hg[+Section::End];
      Float64 a_wind = (a + b)*Ls;
      Float64 y_wind = (a*a + a*b + b*b) / (3 * (a + b));
      Awind += a_wind;
      YwindAwind += -y_wind*a_wind;

      // NOTE: Wind and CF is applied in the same direction as gravity
      // We have a 2D, plane frame model, not a 3D space frame. Our FEM engine does not support out of plane loading
      // Technically, this is incorrect, however the moments and shears are the same for loads applied transverse to the girder
      // Deflections will be incorrect. Deflections from the FEM model will need to be scaled by Ix/Iy

      if (mbrIDStart == mbrIDEnd)
      {
         // load is contained on a single member
         distLoad.Release();
         swDistributedLoads->Create(loadID, mbrIDStart, loadDirFy, xStart, xEnd, -wStart, -wEnd, lotMember, &distLoad);

         distLoad.Release();
         cfDistributedLoads->Create(loadID, mbrIDStart, loadDirFy, xStart, xEnd, -cfStart, -cfEnd, lotMember, &distLoad);

         distLoad.Release();
         windDistributedLoads->Create(loadID, mbrIDStart, loadDirFy, xStart, xEnd, -windStart, -windEnd, lotMember, &distLoad);

         loadID++;
      }
      else
      {
         // load straddles two or more members
         CComPtr<IFem2dMember> mbr;
         CComPtr<IFem2dJoint> jntStart, jntEnd;
         for (MemberIDType mbrID = mbrIDStart; mbrID <= mbrIDEnd; mbrID++)
         {
            Float64 w1self, w2self; // start and end load intensity on this member
            Float64 w1cf, w2cf;
            Float64 w1wind, w2wind;
            Float64 x1, x2; // start and end load location from the start of this member

            Float64 Lmbr;
            mbr.Release();
            members->Find(mbrID, &mbr);
            mbr->get_Length(&Lmbr);

            JointIDType jntIDStart, jntIDEnd;
            mbr->get_StartJoint(&jntIDStart);
            mbr->get_EndJoint(&jntIDEnd);

            jntStart.Release();
            jntEnd.Release();
            joints->Find(jntIDStart, &jntStart);
            joints->Find(jntIDEnd, &jntEnd);

            Float64 xMbrStart, xMbrEnd;
            jntStart->get_X(&xMbrStart);
            jntEnd->get_X(&xMbrEnd);

            if (mbrID == mbrIDStart)
            {
               w1self = wStart;
               w1cf = cfStart;
               w1wind = windStart;
               x1 = xStart;
            }
            else
            {
               w1self = ::LinInterp(xMbrStart - start, wStart, wEnd, end - start);
               w1cf = ::LinInterp(xMbrStart - start, cfStart, cfEnd, end - start);
               w1wind = ::LinInterp(xMbrStart - start, windStart, windEnd, end - start);
               x1 = 0; // start of member
            }

            if (mbrID == mbrIDEnd)
            {
               w2self = wEnd;
               w2cf = cfEnd;
               w2wind = windEnd;
               x2 = xEnd;
            }
            else
            {
               w2self = ::LinInterp(xMbrEnd - start, wStart, wEnd, end - start);
               w2cf = ::LinInterp(xMbrEnd - start, cfStart, cfEnd, end - start);
               w2wind = ::LinInterp(xMbrEnd - start, windStart, windEnd, end - start);
               x2 = Lmbr; // end of member
            }

            if (!IsEqual(x1, x2))
            {
               // no need to add the load if its length is 0
               distLoad.Release();
               swDistributedLoads->Create(loadID, mbrID, loadDirFy, x1, x2, -w1self, -w2self, lotMember, &distLoad);

               distLoad.Release();
               cfDistributedLoads->Create(loadID, mbrID, loadDirFy, x1, x2, -w1cf, -w2cf, lotMember, &distLoad);

               distLoad.Release();
               windDistributedLoads->Create(loadID, mbrID, loadDirFy, x1, x2, -w1wind, -w2wind, lotMember, &distLoad);

               loadID++;
            }
         }
      }

      start = end;
   }

   results.Wg = Wg / 2;

   // divide by 2 to get total wind load (see note above)
   results.Wwind = Wwind / 2;
   YwindAwind /= 2; // divide by 2 because the wind part should have been above, but we didn't
   Awind /= 2;
   results.Ywind[+ImpactDirection::NoImpact] = ::IsZero(Awind) ? 0 : YwindAwind / Awind; // this now holds the location of the resultant wind force measured from the top of the girder

   if (pHaulingProblem)
   {
      HaulingResults* pHaulingResults = static_cast<HaulingResults*>(&results);
      ATLASSERT(pHaulingResults != nullptr);
      pHaulingResults->Wcf = Wcf / 2;
   }

   // Apply self weight point loads
   LoadIDType ptLoadID = 0;
   Wg = 0;
   std::vector<std::pair<Float64,Float64>> vPointLoads = pGirder->GetAdditionalLoads();
   for ( const auto& ptLoad : vPointLoads )
   {
      Float64 X = ptLoad.first;
      Float64 P = ptLoad.second;
      MemberIDType mbrID = 0;
      Float64 Xmbr;

      // search for the member where this point is located
      // get the member ID and the location measured from the start of the member
      std::vector<Float64>::iterator jntIter(vX.begin());
      std::vector<Float64>::iterator jntIterEnd(vX.end());
      Float64 Xprev = *jntIter;
      jntIter++;
      for ( ; jntIter != jntIterEnd; jntIter++, mbrID++ )
      {
         Float64 Xcurr = *jntIter;
         if ( ::InRange(Xprev,X,Xcurr) )
         {
            Xmbr = X - Xprev;
            break;
         }

         Xprev = Xcurr;
      }

      CComPtr<IFem2dPointLoad> ptLoad;
      swPointLoads->Create(ptLoadID++,mbrID,Xmbr,0,P,0,lotMember,&ptLoad);

      Wg += -P;
   }

   // adjust total weight and vertical center of mass for point loads
   results.Wg += Wg;

   // Apply point loads due to lifting
   const ILiftingStabilityProblem* pLiftingProblem = dynamic_cast<const ILiftingStabilityProblem*>(pStabilityProblem);
   if ( pLiftingProblem )
   {
      // We don't know the horizontal component of the lift force here, so we will just use a unit force
      // and then scale the results later
      Float64 Ph = 1.0;

      Float64 Yrc = pStabilityProblem->GetYRollAxis();

      Float64 Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf;
      pGirder->GetSectionProperties(leftSupportLoc,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wtf,&Wbf);
      Float64 Mleft = -Ph*(Ytop + Yrc);

      pGirder->GetSectionProperties(rightSupportLoc,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wtf,&Wbf);
      Float64 Mright = Ph*(Ytop + Yrc);

      CComPtr<IFem2dJointLoad> leftJntLoad,rightJntLoad;
      liftJointLoads->Create(0,leftSupportJntID,0.0,0.0,Mleft,&leftJntLoad);
      liftJointLoads->Create(1,rightSupportJntID,0.0,0.0,Mright,&rightJntLoad);
   }


   // Layout POIs
   // there is a 1 to 1 mapping between analysis points and poi IDs so there is no
   // need to keep an actual map
   CComPtr<IFem2dPOICollection> pois;
   (*ppModel)->get_POIs(&pois);
   PoiIDType poiID = 0;

   Float64 Xms = 0.5*(Lg + Ll - Lr); // mid-span location
   m_MidSpanPoi = INVALID_ID;
   const auto& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   for( const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 Xpoi = pAnalysisPoint->GetLocation();
      MemberIDType mbrID = 0;
      Float64 Xmbr;

      // search for the member where this point is located
      // get the member ID and the location measured from the start of the member
      std::vector<Float64>::iterator jntIter(vX.begin());
      std::vector<Float64>::iterator jntIterEnd(vX.end());
      Float64 Xprev = *jntIter;
      jntIter++;
      for ( ; jntIter != jntIterEnd; jntIter++, mbrID++ )
      {
         Float64 Xcurr = *jntIter;
         if ( ::InRange(Xprev,Xpoi,Xcurr) )
         {
            Xmbr = Xpoi - Xprev;

            if ( IsEqual(Xpoi,Xms) )
            {
               m_MidSpanPoi = poiID;
            }

            break;
         }

         Xprev = Xcurr;
      }

      CComPtr<IFem2dPOI> poi;
      pois->Create(poiID++,mbrID,Xmbr,&poi);
   }

   // put a poi at the start. it is used, along with the mid-span poi to compute deflections relative to the girder ends
   CComPtr<IFem2dPOI> poi;
   m_StartPoi = poiID;
   pois->Create(poiID++,0,0,&poi);


   if (m_MidSpanPoi == INVALID_ID) 
   {
      // analysis list does not include the mid-point
      MemberIDType mbrID = 0;
      Float64 Xmbr;

      // search for the member where this point is located
      // get the member ID and the location measured from the start of the member
      std::vector<Float64>::iterator jntIter(vX.begin());
      std::vector<Float64>::iterator jntIterEnd(vX.end());
      Float64 Xprev = *jntIter;
      jntIter++;
      for ( ; jntIter != jntIterEnd; jntIter++, mbrID++ )
      {
         Float64 Xcurr = *jntIter;
         if ( ::InRange(Xprev,Xms,Xcurr) )
         {
            Xmbr = Xms - Xprev;
            break;
         }

         Xprev = Xcurr;
      }

      m_MidSpanPoi = poiID;

      CComPtr<IFem2dPOI> poi;
      pois->Create(poiID++,mbrID,Xmbr,&poi);
   }

   ATLASSERT(m_MidSpanPoi != INVALID_ID);

   GetZoComputationMethod(pGirder,pStabilityProblem,*ppModel,results);
   if ( results.ZoMethod == CalculationMethod::Approximate )
   {
      // Create special POI for computing Zo
      // Need several closely spaced POI for accurate results
      // plus need poi at support locations and locations of point loads
      IndexType nPoi = 250; // this is the number of analysis points required to exactly match zo in PCI Examples
      // This could be reduced if we come up with a better numerical integration method
      m_vPoi.clear();
      for ( IndexType i = 0; i <= nPoi; i++ )
      {
         Float64 x = i*Lg/nPoi;
         m_vPoi.push_back(x);
      }

      // need poi at the supports
      m_vPoi.push_back(leftSupportLoc);
      m_vPoi.push_back(rightSupportLoc);

      // need poi at the additional load points
      std::vector<std::pair<Float64,Float64>> vPointLoads = pGirder->GetAdditionalLoads();
      std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIter(vPointLoads.begin());
      std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIterEnd(vPointLoads.end());
      for ( ; ptLoadIter != ptLoadIterEnd; ptLoadIter++ )
      {
         Float64 X = ptLoadIter->first;
         m_vPoi.push_back(X);
      }

      // eliminate duplicates
      std::sort(m_vPoi.begin(),m_vPoi.end());
      m_vPoi.erase(std::unique(m_vPoi.begin(),m_vPoi.end()),m_vPoi.end());

      // create the POI in the FEM model
      m_FirstPoi = -2;
      poiID = m_FirstPoi;
      for( const auto& Xpoi : m_vPoi)
      {
         MemberIDType mbrID = 0;
         Float64 Xmbr;

         // search for the member where this point is located
         // get the member ID and the location measured from the start of the member
         std::vector<Float64>::iterator jntIter(vX.begin());
         std::vector<Float64>::iterator jntIterEnd(vX.end());
         Float64 Xprev = *jntIter;
         jntIter++;
         for ( ; jntIter != jntIterEnd; jntIter++, mbrID++ )
         {
            Float64 Xcurr = *jntIter;
            if ( ::InRange(Xprev,Xpoi,Xcurr) )
            {
               Xmbr = Xpoi - Xprev;
               break;
            }

            Xprev = Xcurr;
         }

         CComPtr<IFem2dPOI> poi;
         pois->Create(poiID--,mbrID,Xmbr,&poi);
      }

      poiID++;
      m_LastPoi = poiID;
   }

   // capture girder dead load reactions
   CComQIPtr<IFem2dModelResults> fem_results(*ppModel);
   Float64 Rx, Rleft, Rright, Rz;
   fem_results->ComputeReactions(LCID_GIRDER, leftSupportJntID, &Rx, &Rleft, &Rz);
   fem_results->ComputeReactions(LCID_GIRDER, rightSupportJntID, &Rx, &Rright, &Rz);
   results.Rl = Rleft;
   results.Rr = Rright;
}

Float64 StabilityEngineer::ComputeXcg(const IGirder* pGirder, const IStabilityProblem* pStabilityProblem, Results& results) const
{
   // Location of CG with respect to the roll axis, assuming the roll axis is at the middle of the girder (Wtop/2)
   SectionIndexType nSections = pGirder->GetSectionCount();
   if (nSections == 1)
   {
      Float64 Ag1, Ixx1, Iyy1, Ixy1, Xcg1, Ycg1, Hg1, Wtop1, Wbot1;
      Float64 Ag2, Ixx2, Iyy2, Ixy2, Xcg2, Ycg2, Hg2, Wtop2, Wbot2;
      pGirder->GetSectionProperties(0, Section::Start, &Ag1, &Ixx1, &Iyy1, &Ixy1, &Xcg1, &Ycg1, &Hg1, &Wtop1, &Wbot1);
      pGirder->GetSectionProperties(0, Section::End, &Ag2, &Ixx2, &Iyy2, &Ixy2, &Xcg2, &Ycg2, &Hg2, &Wtop2, &Wbot2);
      if (IsEqual(Max(Wtop1,Wbot1),Max(Wtop2,Wbot2)) && IsEqual(Xcg1, Xcg2))
      {
         results.XcgMethod = CalculationMethod::Exact;
         results.Xleft = fabs(Xcg1 - Max(Wtop1,Wbot2) / 2);
      }
      else
      {
         results.XcgMethod = CalculationMethod::Approximate;
         Float64 Xbar1 = fabs(Xcg1 - Max(Wtop1,Wbot1) / 2);
         Float64 Xbar2 = fabs(Xcg2 - Max(Wtop2,Wbot2) / 2);

         Float64 g = WBFL::Units::System::GetGravitationalAcceleration();
         const auto& concrete = pStabilityProblem->GetConcrete();
         Float64 density = concrete.GetDensityForWeight();
         Float64 unitWeight = density*g;

         Float64 dL = pGirder->GetSectionLength(0);
         Float64 Wg = unitWeight*dL*0.5*(Ag1 + Ag2);

         results.Xleft = 0.5*(unitWeight*Ag1*Xbar1 + unitWeight*Ag2*Xbar2) / Wg;
      }
   }
   else
   {
      results.XcgMethod = CalculationMethod::Approximate;
      Float64 xcg_wg = 0;
      Float64 Wg = 0;

      Float64 g = WBFL::Units::System::GetGravitationalAcceleration();
      const auto& concrete = pStabilityProblem->GetConcrete();
      Float64 density = concrete.GetDensityForWeight();
      Float64 unitWeight = density*g;

      for (SectionIndexType sectIdx = 0; sectIdx < nSections; sectIdx++)
      {
         Float64 Ag1, Ixx1, Iyy1, Ixy1, Xcg1, Ycg1, Hg1, Wtop1, Wbot1;
         pGirder->GetSectionProperties(sectIdx, Section::Start, &Ag1, &Ixx1, &Iyy1, &Ixy1, &Xcg1, &Ycg1, &Hg1, &Wtop1, &Wbot1);
         Float64 Xbar1 = fabs(Xcg1 - Max(Wtop1,Wbot1) / 2);

         Float64 Ag2, Ixx2, Iyy2, Ixy2, Xcg2, Ycg2, Hg2, Wtop2, Wbot2;
         pGirder->GetSectionProperties(sectIdx, Section::End, &Ag2, &Ixx2, &Iyy2, &Ixy2, &Xcg2, &Ycg2, &Hg2, &Wtop2, &Wbot2);
         Float64 Xbar2 = fabs(Xcg2 - Max(Wtop2,Wbot2) / 2);

         Float64 Xleft = (unitWeight*Ag1*Xbar1 + unitWeight*Ag2*Xbar2);

         Float64 dL = pGirder->GetSectionLength(sectIdx);
         xcg_wg += Xleft*dL;

         Float64 wg = unitWeight*dL*(Ag1 + Ag2);
         Wg += wg;
      }

      results.Xleft = xcg_wg / Wg;
   }

   return results.Xleft;
}

void StabilityEngineer::GetZoComputationMethod(const IGirder* pGirder,const IStabilityProblem* pStabilityProblem,IFem2dModel* pModel,Results& results) const
{
   if ( pGirder->GetSectionCount() == 1 )
   {
      Float64 Ag1,Ixx1,Iyy1,Ixy1,Xcg1,Ycg1,Hg1,Wtop1,Wbot1;
      Float64 Ag2,Ixx2,Iyy2,Ixy2,Xcg2,Ycg2,Hg2,Wtop2,Wbot2;
      pGirder->GetSectionProperties(0,Section::Start,&Ag1,&Ixx1,&Iyy1,&Ixy1,&Xcg1,&Ycg1,&Hg1,&Wtop1,&Wbot1);
      pGirder->GetSectionProperties(0,Section::End,  &Ag2,&Ixx2,&Iyy2,&Ixy2,&Xcg2,&Ycg2,&Hg2,&Wtop2,&Wbot2);

      std::vector<std::pair<Float64,Float64>> vLoads = pGirder->GetAdditionalLoads();
      if ( IsEqual(Ag1,Ag2) && IsEqual(Ixx1,Ixx2) && IsEqual(Iyy1,Iyy2) && IsEqual(Ixy1,Ixy2) && IsEqual(Xcg1,Xcg2) && IsEqual(Ycg1,Ycg2) && IsEqual(Hg1,Hg2) && IsEqual(Wtop1,Wtop2) && IsEqual(Wbot1,Wbot2) && vLoads.size() == 0)
      {
         results.ZoMethod = CalculationMethod::Exact;
      }
      else
      {
         results.ZoMethod = CalculationMethod::Approximate;
      }
   }
   else
   {
      results.ZoMethod = CalculationMethod::Approximate;
   }
}

Float64 StabilityEngineer::ComputeZo(const IGirder* pGirder,const IStabilityProblem* pStabilityProblem,IFem2dModel* pModel,Results& results) const
{
   Float64 Zo;
   if ( results.ZoMethod == CalculationMethod::Exact )
   {
      Float64 Ec = pStabilityProblem->GetConcrete().GetE();
      Float64 Lg = pGirder->GetGirderLength();
      Float64 Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wt,Wb;
      pGirder->GetSectionProperties(Lg/2,&Ag,&Ixx,&Iyy,&Ixy,&Xleft,&Ytop,&Hg,&Wt,&Wb);
      Float64 W = results.Wg;
      Float64 l = results.Ls;
      Float64 Ll, Lr;
      pStabilityProblem->GetSupportLocations(&Ll, &Lr);
      Float64 a = Min(Ll, Lr);
      Float64 b = Max(Ll, Lr);

      Float64 EI = Ec*(Ixx*Iyy - Ixy*Ixy)/Ixx;
      // unequal overhangs (a < b)
      Zo = (W / (24 * EI * Lg * Lg)) * ((l * l * l * l * l) / 5. - (a * a + b * b) * (l * l * l) + 2 * ((a * a * a * a) + (a * a * b * b) + (b * b * b * b)) * l + 6. * ((a * a * a * a * a) + (b * b * b * b * b)) / 5.);
#if defined _DEBUG
      if (IsEqual(a, b))
      {
         Float64 _zo = (W/(12*EI*Lg*Lg))*(l*l*l*l*l/10. - a*a*l*l*l + 3.*a*a*a*a*l + 6.*a*a*a*a*a/5.); // equal overhangs
         ATLASSERT(IsEqual(Zo, _zo));
      }
#endif
   }
   else
   {
      ATLASSERT(m_FirstPoi - m_LastPoi + 1 == m_vPoi.size());
      CComQIPtr<IFem2dModelResults> femResults(pModel);
      Float64 g = WBFL::Units::System::GetGravitationalAcceleration();

      const auto& concrete = pStabilityProblem->GetConcrete();
      Float64 density = concrete.GetDensityForWeight();
      Float64 unitWeight = density*g;

      PoiIDType poiID1 = m_FirstPoi;
      PoiIDType poiID2 = m_FirstPoi-1;
      std::vector<Float64>::const_iterator iter1(m_vPoi.begin());
      std::vector<Float64>::const_iterator iter2 = iter1+1;
      std::vector<Float64>::const_iterator end(m_vPoi.end());
      Zo = 0;
      for ( ; iter2 != end; iter1++, iter2++, poiID1--, poiID2-- )
      {
         Float64 x1 = *iter1;
         Float64 x2 = *iter2;

         Float64 Ag1,Ixx1,Iyy1,Ixy1,Xleft,Ytop,Hg,Wtop,Wbot;
         Float64 Ag2,Ixx2,Iyy2,Ixy2;
         pGirder->GetSectionProperties(x1,&Ag1,&Ixx1,&Iyy1,&Ixy1,&Xleft,&Ytop,&Hg,&Wtop,&Wbot);
         pGirder->GetSectionProperties(x2,&Ag2,&Ixx2,&Iyy2,&Ixy2,&Xleft,&Ytop,&Hg,&Wtop,&Wbot);

         Float64 w1 = Ag1*unitWeight;
         Float64 w2 = Ag2*unitWeight;

         // this is vertical deflection based on Ix...
         Float64 dx,dy1,dy2,rz;
         femResults->ComputePOIDeflections(LCID_GIRDER,poiID1,lotMember,&dx,&dy1,&rz);
         femResults->ComputePOIDeflections(LCID_GIRDER,poiID2,lotMember,&dx,&dy2,&rz);

         // we want lateral deflection based on Iy...
         dy1 *= Ixx1/Iyy1;
         dy2 *= Ixx2/Iyy2;

         Float64 zo = 0.5*(w1*dy1 + w2*dy2)*(x2 - x1);
         Zo += zo;
      }

      ATLASSERT(poiID1 == m_LastPoi);

      Float64 Wg = results.Wg;
      Zo /= -Wg;
   }
   return Zo;
}

void StabilityEngineer::GetRebarLayout(const IGirder* pGirder,IRebarLayout** ppRebarLayout) const
{
   CComPtr<ISegment> segment;
   pGirder->GetSegment(&segment);
   ATLASSERT(segment);

   CComQIPtr<IItemData> itemData(segment);
   CComPtr<IUnknown> punk;
   itemData->GetItemData(CComBSTR("Precast Girder"),&punk);
   CComQIPtr<IPrecastGirder> gdr(punk);
   gdr->get_RebarLayout(ppRebarLayout);
}

Float64 StabilityEngineer::ComputePz(Float64 velocity,Float64 Cd) const
{
   // LRFD 3.8.1.2
   // Kz and G = 1.0 for Service I
   Float64 V = WBFL::Units::ConvertFromSysUnits(velocity,WBFL::Units::Measure::MilePerHour);
   Float64 Pz = (2.56e-6)*V*V*Cd;
   Pz = WBFL::Units::ConvertToSysUnits(Pz,WBFL::Units::Measure::KSF);
   return Pz;
}

void StabilityEngineer::FindMember(IFem2dModel* pModel, Float64 distFromStartOfModel, MemberIDType* pMbrID, Float64* pDistFromStartOfMbr) const
{
   CComPtr<IFem2dMemberCollection> members;
   pModel->get_Members(&members);

   CollectionIndexType mbrcnt;
   members->get_Count(&mbrcnt);

   CComPtr<IFem2dJointCollection> joints;
   pModel->get_Joints(&joints);

   CComPtr<IFem2dEnumMember> enumMembers;
   members->get__EnumElements(&enumMembers);

   CollectionIndexType idx = 0;
   CComPtr<IFem2dJoint> j1, j2;
   CComPtr<IFem2dMember> mbr;
   while (enumMembers->Next(1, &mbr, nullptr) != S_FALSE)
   {
      JointIDType jntID1, jntID2;
      mbr->get_StartJoint(&jntID1);
      mbr->get_EndJoint(&jntID2);

      j1.Release();
      j2.Release();
      joints->Find(jntID1, &j1);
      joints->Find(jntID2, &j2);

      Float64 x1, x2;
      j1->get_X(&x1);
      j2->get_X(&x2);

      if (InRange(x1, distFromStartOfModel, x2))
      {
         mbr->get_ID(pMbrID);
         *pDistFromStartOfMbr = distFromStartOfModel - x1;
         return;
      }
      else if (idx == 0 && distFromStartOfModel<x1) // next cases are for short cantilevers where fem model is not generated
      {
         mbr->get_ID(pMbrID);
         *pDistFromStartOfMbr = 0.0;
         return;
      }
      else if ((idx == mbrcnt - 1) && (x2 < distFromStartOfModel))
      {
         mbr->get_ID(pMbrID);
         *pDistFromStartOfMbr = x2 - x1;
         return;
      }

      mbr.Release();
      idx++;
   }

   ATLASSERT(false); // didn't find a solution
}
