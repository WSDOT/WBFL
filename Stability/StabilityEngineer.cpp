///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <Stability\StabilityLib.h>
#include <Stability\StabilityEngineer.h>

#include <WBFLFem2d_i.c>

#if defined _DEBUG
#define _DUMP_FEM_MODEL
#endif

#if defined _DUMP_FEM_MODEL
#include <WBFLTools_i.c>
#endif

#include <algorithm>
#include <UnitMgt\UnitMgt.h>
#include <LRFD\ConcreteUtil.h>
#include <LRFD\AlternativeTensileStressCalculator.h>
#include <Math\CubicSolver.h>

#include <WBFLGenericBridge.h>
#include <WBFLGenericBridge_i.c>
#include <WBFLGenericBridgeTools.h>
#include <WBFLGenericBridgeTools_i.c>
#include <WBFLGeometry_i.c>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LCID_GIRDER 0
#define LCID_WIND   1
#define LCID_CF     2
#define LCID_LIFT   3

#define THETA_MAX 0.4

stbStabilityEngineer::stbStabilityEngineer(IUnitConvert* pUnitConvert)
{
   m_pUnitConvert = pUnitConvert;
}

stbLiftingResults stbStabilityEngineer::AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem) const
{
   stbLiftingResults results;
   PrepareResults(pGirder,pStabilityProblem,results);
   AnalyzeLifting(pGirder,pStabilityProblem,results);

   return results;
}

stbHaulingResults stbStabilityEngineer::AnalyzeHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem) const
{
   stbHaulingResults results;
   PrepareResults(pGirder,pStabilityProblem,results);
   AnalyzeHauling(pGirder,pStabilityProblem,results);
   return results;
}

stbLiftingCheckArtifact stbStabilityEngineer::CheckLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,const stbLiftingCriteria& criteria) const
{
   stbLiftingResults results = AnalyzeLifting(pGirder,pStabilityProblem);
   stbLiftingCheckArtifact artifact(results,criteria,pStabilityProblem->EvaluateStressesAtEquilibriumAngle());
   return artifact;
}

stbHaulingCheckArtifact stbStabilityEngineer::CheckHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbHaulingCriteria& criteria) const
{
   stbHaulingResults results = AnalyzeHauling(pGirder,pStabilityProblem);
   stbHaulingCheckArtifact artifact(results,criteria,pStabilityProblem->EvaluateStressesAtEquilibriumAngle(stbTypes::CrownSlope), pStabilityProblem->EvaluateStressesAtEquilibriumAngle(stbTypes::Superelevation));
   return artifact;
}

void stbStabilityEngineer::PrepareResults(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results) const
{
   // Compute girder weight and length of girder by adding up contribution of each section based on the section properties
   Float64 Ll,Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);
   Float64 Lg = pGirder->GetGirderLength();

   results.Ll = Ll;
   results.Lr = Lr;

   results.Ls = Lg - Ll - Lr;

   // for purposes of computing the CG offset factor, assume equal overhangs using the least overhang
   // this will put the CG furthest from the roll axis which is concervative
   Float64 span_ratio = (Lg - 2*Min(Ll,Lr))/Lg;
   results.OffsetFactor = (span_ratio)*(span_ratio) - 1./3.;
   results.OffsetFactor = IsZero(results.OffsetFactor) ? 0 : results.OffsetFactor;

   results.LateralSweep = pStabilityProblem->GetSweepTolerance()*Lg;

   for ( IndexType i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      results.EccLateralSweep[impact] = results.OffsetFactor*results.LateralSweep + pStabilityProblem->GetSupportPlacementTolerance();
   }
}

void stbStabilityEngineer::Analyze(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel) const
{
   BuildModel(pGirder,pStabilityProblem,results,ppModel);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   // BuildModel sets results.Ywind[stbTypes::NoImpact] equal to the location of the resultant wind force measured from the top of the girder in girder section coordinates
   // we need to get it from the roll axis
   Float64 Yra = pStabilityProblem->GetYRollAxis();
   Float64 y = Yra + results.Ywind[stbTypes::NoImpact];
   Float64 Ywind = fabs(y);

   // adjust for camber
   bool bDirectCamber;
   Float64 Camber;
   pStabilityProblem->GetCamber(&bDirectCamber,&Camber);
   if ( bDirectCamber )
   {
      Float64 m = pStabilityProblem->GetCamberMultiplier();
      Ywind += ::BinarySign(y)*results.OffsetFactor*m*Camber;
   }
   else
   {
      Ywind *= (1. - ::BinarySign(y)*Camber);
   }
   // additional effects due to impact adjusted force of inclined lifting cable will be added later
   results.Ywind[stbTypes::NoImpact]   = Ywind;
   results.Ywind[stbTypes::ImpactUp]   = Ywind;
   results.Ywind[stbTypes::ImpactDown] = Ywind;

   results.Yr = Yra - results.Ycg; // location from the center of gravity from the roll axis (positive means roll center is above CG)

   Float64 Dra = fabs(results.Yr);  // adjusted distance between CG and roll axis (using fabs because distance is an absolute value)
   if ( bDirectCamber )
   {
      Float64 m = pStabilityProblem->GetCamberMultiplier();
      Dra -= ::BinarySign(results.Yr)*results.OffsetFactor*m*Camber;
      results.CamberOffsetFactor = 1.0; // not applicable, but set it to a nice number
   }
   else
   {
      // this is Mast's "adjust by 2% to allow for camber" approach
      // for lifting the Camber should be less than zero because the
      // camber causes cg of the girder to get closer to the roll axis thereby reducing the distance
      // for hauling Camber should be greater than zero because camber causes the cg to move
      // further away from the roll axis
      ATLASSERT(::InRange(0.0,fabs(Camber),1.0)); // must be a fraction, not an actual percentage
      results.CamberOffsetFactor = 1.0 - ::BinarySign(results.Yr)*Camber;
      Dra *= results.CamberOffsetFactor;
   }
   // additional effects due to impact adjusted force of inclined lifting cable will be added later
   results.Dra[stbTypes::NoImpact]   = Dra;
   results.Dra[stbTypes::ImpactUp]   = Dra;
   results.Dra[stbTypes::ImpactDown] = Dra;

   // lateral deflection due to full load applied laterally
   Float64 zo = ComputeZo(pGirder,pStabilityProblem,*ppModel,results);

   Float64 ImpactUp, ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[] = { 1.0, 1.0 - ImpactUp, 1.0 + ImpactDown };
   for ( IndexType i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      results.Zo[impact] = IM[impact]*zo;
      results.ZoWind[impact] = results.Zo[impact]*results.Wwind/(IM[impact]*Wg);
   }
}

void stbStabilityEngineer::AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,stbLiftingResults& results) const
{
   CComPtr<IFem2dModel> model;
   Analyze(pGirder,pStabilityProblem,results,&model);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   // compute critical buckling load
   Float64 Ag,Ix,Iy,Yt,Hg,Wtop,Wbot;
   pGirder->GetSectionProperties(Lg/2,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtop,&Wbot);
   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   const matConcreteEx& concrete = pStabilityProblem->GetConcrete();

   Float64 Ec = concrete.GetE();
   results.Pcrit = M_PI*M_PI*Ec*Iy/((Lg - Ll - Lr)*(Lg - Ll - Lr));

   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[3] = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   // horizontal component of force due to inclined lifting cables
   // negative value because it causes compression
   results.Plift = -(Wg/2)*tan(PI_OVER_2 - pStabilityProblem->GetLiftAngle());
   results.Plift = ::IsZero(results.Plift) ? 0.0 : results.Plift;

   ATLASSERT( !IsZero(pStabilityProblem->GetLiftAngle()) );
   for ( IndexType i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;

      // compute lateral deflection multiplier
      if ( results.Plift < 0 )
      {
         // inclined cables cause compression
         results.emag[impact] = 1/(1 - fabs(IM[impact]*results.Plift/results.Pcrit)); // lateral deflection multiplier
      }
      else
      {
         // inclined cables cause tension which will straighten the girder
         results.emag[impact] = 1.0;
      }

      // adjust eccentricity of CG of girder due to lateral sweep
      results.EccLateralSweep[impact] *= results.emag[impact];
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
   results.dLift = results.Plift*(dy2 - dy1); // does not include impact... measured relative to the ends of the girder

   for ( IndexType i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;

      // magnify lateral deflections due to horizontal component of lifting cable force
      results.Zo[impact]     *= results.emag[impact]; // emag includes impact
      results.ZoWind[impact] *= results.emag[impact];

      // add the deflection due to the horiztonal component of the lifting cable force
      // to the location of the resultant gravity and wind forces
      results.Dra[impact]   -= results.OffsetFactor*IM[impact]*results.dLift;
      results.Ywind[impact] -= results.OffsetFactor*IM[impact]*results.dLift;

      // compute the lateral eccentricity of the girder self-weight due to the wind load
      results.EccWind[impact] = results.Wwind*results.Ywind[impact]/(IM[impact]*Wg);

      // if the roll axis is below the center of mass for a hanging girder, it is unstable.
      // the girder will have to turn completely over to acheive equilibrium
      results.bIsStable[impact] = (results.Dra[impact] < 0 ? false : true);

      // Compute tilt equilibrium angle
      for ( IndexType w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         Float64 windSign = (wind == stbTypes::Left ? 1 : -1);
         results.ThetaEq[impact][wind] = (results.EccLateralSweep[impact] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact])/(results.Dra[impact] - results.Zo[impact]);
      } // next wind direction
   } // next impact direction

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   results.MinFScr         =  DBL_MAX;
   results.MinFsFailure    =  DBL_MAX;
   results.MaxStress       = -DBL_MAX;
   results.MinStress       =  DBL_MAX;
   results.MaxDirectStress = -DBL_MAX;
   results.MinDirectStress =  DBL_MAX;

   Float64 fr = concrete.GetFlexureFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();

   // this parameter is used to compute the moment arm for the horizontal force in the inclined
   // lift cable measured transversely from the laterally deflected beam.
   // we are conservative to assume equal overhangs based on the smallest overhang
   // this puts the force furthest from the arc which is concervative
   Float64 a = Min(Ll,Lr);

   bool bDirectCamber;
   Float64 Camber;
   pStabilityProblem->GetCamber(&bDirectCamber,&Camber);


   PoiIDType poiID = 0;
   IndexType analysisPointIdx = 0;
   std::vector<stbIAnalysisPoint*>& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   for( const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 X = pAnalysisPoint->GetLocation();

      stbLiftingSectionResult sectionResult;

      sectionResult.AnalysisPointIndex = analysisPointIdx++;

      sectionResult.fMin[stbTypes::Top]    =  Float64_Max;
      sectionResult.fMin[stbTypes::Bottom] =  Float64_Max;
      sectionResult.fMax[stbTypes::Top]    = -Float64_Max;
      sectionResult.fMax[stbTypes::Bottom] = -Float64_Max;

      sectionResult.fMinDirect[stbTypes::Top]    =  Float64_Max;
      sectionResult.fMinDirect[stbTypes::Bottom] =  Float64_Max;
      sectionResult.fMaxDirect[stbTypes::Top]    = -Float64_Max;
      sectionResult.fMaxDirect[stbTypes::Bottom] = -Float64_Max;

      sectionResult.FScrMin = Float64_Max;

      CComPtr<IRebarSection> rebarSection;
      CComPtr<IShape> shape;
      if ( segment )
      {
         rebarLayout->CreateRebarSection(X,0,&rebarSection);
         segment->get_PrimaryShape(X,sbLeft,&shape);
      }

      // eccentricity of horizontal load due to inclined cable at X
      sectionResult.OffsetFactor = pow((Lg - 2*a)/Lg,2) - pow((Lg - 2*X)/Lg,2);

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

      Float64 Hg,Ag,Ix,Iy,Yt,Wtf,Wbf;
      pGirder->GetSectionProperties(X,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);

      // stress due to prestressing
      sectionResult.fps[stbTypes::Top]    = 0;
      sectionResult.fps[stbTypes::Bottom] = 0;
      for ( int s = 0; s < 3; s++ )
      {
         stbTypes::StrandType strandType = (stbTypes::StrandType)s;

         Float64 Fpe, Y;
         pStabilityProblem->GetFpe(strandType,X,&Fpe,&Y);
         Float64 eps = Y - Yt; // eccentricity of strands (positive values means ps force is above CG)

         Float64 ft = -Fpe/Ag + Fpe*eps*Yt/Ix;
         Float64 fb = -Fpe/Ag + Fpe*eps*(Hg + Yt)/Ix;

         sectionResult.fps[stbTypes::Top]    += ft;
         sectionResult.fps[stbTypes::Bottom] += fb;
      }

      // stress due to inclined lift cable
      Float64 Plift = results.Plift;
      if ( X < Ll || (Lg - Lr) < X )
      {
         Plift = 0; // X is not between the lifting devices so there isn't any axial load due to the inclined cable
      }

      // stress due to inclined lift cables (no impact)
      sectionResult.fcable[stbTypes::Top]    = Plift*(1/Ag - results.Dra[stbTypes::NoImpact]*Yt/Ix);
      sectionResult.fcable[stbTypes::Bottom] = Plift*(1/Ag - results.Dra[stbTypes::NoImpact]*(Hg+Yt)/Ix);

      // stress due to dead load (no impact)
      sectionResult.fg[stbTypes::Top]    = sectionResult.Mg*Yt/Ix;
      sectionResult.fg[stbTypes::Bottom] = sectionResult.Mg*(Hg + Yt)/Ix;

      // stress due to wind towards the left
      sectionResult.fw[stbTypes::TopLeft]     =  sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[stbTypes::TopRight]    = -sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[stbTypes::BottomLeft]  =  sectionResult.Mw*Wbf/(2*Iy);
      sectionResult.fw[stbTypes::BottomRight] = -sectionResult.Mw*Wbf/(2*Iy);

      // analyze the girder for all the combinations of impact and wind
      for ( IndexType i = 0; i < 3; i++ )
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;

         for ( IndexType w = 0; w < 2; w++ )
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

            Float64 windSign = (wind == stbTypes::Left ? 1 : -1);

            sectionResult.FScr[impact][wind] =  Float64_Max;

            if ( IsZero(Plift) )
            {
               // if there isn't a lifting force, the force cannot be eccentric
               sectionResult.eh[impact][wind] = 0;
               sectionResult.Mh[impact][wind] = 0;
            }
            else
            {
               // Because there is lateral deflection of the girder, the force in the inclined lift cable creates a moment about the Y-axis
               // Compute the eccentricty of the force and the moment at this section
               sectionResult.eh[impact][wind] = SupportPlacementTolerance*results.emag[impact]*(1-sectionResult.OffsetFactor) + (results.EccLateralSweep[impact] + windSign*results.ZoWind[impact])*sectionResult.OffsetFactor;
               sectionResult.Mh[impact][wind] = -Plift*sectionResult.eh[impact][wind];
            }

            for ( IndexType c = 0; c < 4; c++ )
            {
               stbTypes::Corner corner = (stbTypes::Corner)c;

               stbTypes::Face face = (corner == stbTypes::TopLeft || corner == stbTypes::TopRight ? stbTypes::Top : stbTypes::Bottom);
               Float64 b = (face == stbTypes::Top ? Wtf : Wbf);

               Float64 cornerSign = (corner == stbTypes::TopLeft || corner == stbTypes::BottomLeft ? 1 : -1);

               // stress due to direct loads
               sectionResult.fDirect[impact][wind][corner] = sectionResult.fps[face] + IM[impact]*(sectionResult.fcable[face] + sectionResult.fg[face]) + windSign*sectionResult.fw[corner];

               if ( ::IsLT(sectionResult.fMaxDirect[face],sectionResult.fDirect[impact][wind][corner]) )
               {
                  sectionResult.fMaxDirect[face] = sectionResult.fDirect[impact][wind][corner];
                  sectionResult.MaxDirectStressImpactDirection[face] = impact;
                  sectionResult.MaxDirectStressWindDirection[face] = wind;
                  sectionResult.MaxDirectStressCorner[face] = corner;
               }

               if ( ::IsLT(sectionResult.fDirect[impact][wind][corner],sectionResult.fMinDirect[face]) )
               {
                  sectionResult.fMinDirect[face] = sectionResult.fDirect[impact][wind][corner];
                  sectionResult.MinDirectStressImpactDirection[face] = impact;
                  sectionResult.MinDirectStressWindDirection[face] = wind;
                  sectionResult.MinDirectStressCorner[face] = corner;
               }

               // Overall max direct stress
               if ( ::IsLT(results.MaxDirectStress,sectionResult.fDirect[impact][wind][corner]) )
               {
                  results.MaxDirectStress = sectionResult.fDirect[impact][wind][corner];
                  results.MaxDirectStressAnalysisPointIndex = (IndexType)poiID;
                  results.MaxDirectStressImpactDirection = impact;
                  results.MaxDirectStressWindDirection = wind;
                  results.MaxDirectStressCorner = corner;
               }

               // Overall min direct stress
               if ( ::IsLT(sectionResult.fDirect[impact][wind][corner],results.MinDirectStress) )
               {
                  results.MinDirectStress = sectionResult.fDirect[impact][wind][corner];
                  results.MinDirectStressAnalysisPointIndex = (IndexType)poiID;
                  results.MinDirectStressImpactDirection = impact;
                  results.MinDirectStressWindDirection = wind;
                  results.MinDirectStressCorner = corner;
               }

               // stress due to lateral loads caused by the girder being tilted
               sectionResult.fTilt[impact][wind][corner] = cornerSign*(IM[impact]*(sectionResult.Mg - Plift*results.Zo[impact])*results.ThetaEq[impact][wind] + sectionResult.Mh[impact][wind])*b/(2*Iy);

               // total stress
               sectionResult.f[impact][wind][corner] = sectionResult.fDirect[impact][wind][corner] + sectionResult.fTilt[impact][wind][corner];

               if ( ::IsLT(sectionResult.fMax[face],sectionResult.f[impact][wind][corner]) )
               {
                  sectionResult.fMax[face] = sectionResult.f[impact][wind][corner];
                  sectionResult.MaxStressImpactDirection[face] = impact;
                  sectionResult.MaxStressWindDirection[face] = wind;
                  sectionResult.MaxStressCorner[face] = corner;
               }

               if ( ::IsLT(sectionResult.f[impact][wind][corner],sectionResult.fMin[face]) )
               {
                  sectionResult.fMin[face] = sectionResult.f[impact][wind][corner];
                  sectionResult.MinStressImpactDirection[face] = impact;
                  sectionResult.MinStressWindDirection[face] = wind;
                  sectionResult.MinStressCorner[face] = corner;
               }

               if ( ::IsLT(results.MaxStress,sectionResult.f[impact][wind][corner]) )
               {
                  results.MaxStress = sectionResult.f[impact][wind][corner];
                  results.MaxStressAnalysisPointIndex = (IndexType)poiID;
                  results.MaxStressImpactDirection = impact;
                  results.MaxStressWindDirection = wind;
                  results.MaxStressCorner = corner;
               }

               if ( ::IsLT(sectionResult.f[impact][wind][corner],results.MinStress) )
               {
                  results.MinStress = sectionResult.f[impact][wind][corner];
                  results.MinStressAnalysisPointIndex = (IndexType)poiID;
                  results.MinStressImpactDirection = impact;
                  results.MinStressWindDirection = wind;
                  results.MinStressCorner = corner;
               }

               // compute cracking moment and cracking factor of safety
               Float64 mcr = (fr - sectionResult.fDirect[impact][wind][corner])*2*Iy/b - sectionResult.Mh[impact][wind];
               mcr = Max(mcr,0.0); // if mcr is less than zero, the beam cracks even if it is not tilted... there isn't a lateral moment to cause cracking since it is already cracked
               Float64 m = fabs(IM[impact]*sectionResult.Mg - Plift*results.Zo[impact]);

               Float64 theta_crack = (IsZero(m) ? THETA_MAX : mcr/m);
               theta_crack = ::ForceIntoRange(0.0,theta_crack,THETA_MAX);
               sectionResult.Mcr[impact][wind][corner] = mcr;
               sectionResult.ThetaCrack[impact][wind][corner] = theta_crack;

               Float64 fscr = (results.Dra[impact]*theta_crack)/(results.Zo[impact]*theta_crack + results.EccLateralSweep[impact] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact]);
               
               if ( !results.bIsStable[impact] )
               {
                  fscr = 0;
               }

               if ( ::IsLT(fscr,sectionResult.FScr[impact][wind]) )
               {
                  // capture governing condition and related parameters
                  sectionResult.CrackedFlange[impact][wind] = corner;
                  sectionResult.FScr[impact][wind] = fscr;
               }

               if ( ::IsLT(fscr,sectionResult.FScrMin) )
               {
                  sectionResult.FScrMin = fscr;
                  sectionResult.FScrImpactDirection = impact;
                  sectionResult.FScrWindDirection = wind;
                  sectionResult.FScrCorner = corner;
               }
            } // next corner

            // keep track of the minimum FScr for all analysis points
            if ( ::IsLT(sectionResult.FScr[impact][wind],results.MinFScr) )
            {
               results.FScrAnalysisPointIndex = (IndexType)poiID; // poiIDs exactly match the analysis point indicies
               results.FScrImpactDirection = impact;
               results.FScrWindDirection = wind;
               results.FScrCorner = sectionResult.CrackedFlange[impact][wind];
               results.MinFScr = sectionResult.FScr[impact][wind];
            }

            if ( segment )
            {
               CComPtr<IShape> shape;
               segment->get_PrimaryShape(X,sbLeft,&shape);

               CComPtr<IRebarSection> rebarSection;
               rebarLayout->CreateRebarSection(X,INVALID_INDEX,&rebarSection);

               Float64 fy = pStabilityProblem->GetRebarYieldStrength();
               Float64 fsMax = ::ConvertToSysUnits(30.0,unitMeasure::KSI);
               lrfdAlternativeTensileStressCalculator altCalc(concrete,fy,true,fsMax);

               Float64 Yna, NAslope, AreaTension,T,AsProvided,AsRequired;
               bool bIsAdequateRebar;
               if ( pStabilityProblem->EvaluateStressesAtEquilibriumAngle() )
               {
                  altCalc.ComputeAlternativeStressRequirements(shape, rebarSection,
                     Wtf, Wbf,
                     sectionResult.f[impact][wind][stbTypes::TopLeft],
                     sectionResult.f[impact][wind][stbTypes::TopRight],
                     sectionResult.f[impact][wind][stbTypes::BottomLeft],
                     sectionResult.f[impact][wind][stbTypes::BottomRight],
                     &Yna, &NAslope, &AreaTension, &T, &AsProvided, &AsRequired, &bIsAdequateRebar);
               }
               else
               {
                  altCalc.ComputeAlternativeStressRequirements(shape, rebarSection,
                     Wtf, Wbf,
                     sectionResult.fDirect[impact][wind][stbTypes::TopLeft],
                     sectionResult.fDirect[impact][wind][stbTypes::TopRight],
                     sectionResult.fDirect[impact][wind][stbTypes::BottomLeft],
                     sectionResult.fDirect[impact][wind][stbTypes::BottomRight],
                     &Yna, &NAslope, &AreaTension, &T, &AsProvided, &AsRequired, &bIsAdequateRebar);
               }

               sectionResult.bSectionHasRebar[impact][wind] = bIsAdequateRebar;
               sectionResult.Yna[impact][wind] = Yna;
               sectionResult.NAslope[impact][wind] = NAslope;
               sectionResult.AreaTension[impact][wind] = AreaTension;
               sectionResult.T[impact][wind] = T;
               sectionResult.AsProvided[impact][wind] = AsProvided;
               sectionResult.AsRequired[impact][wind] = AsRequired;
            }
         } // next wind direction
      } // next impact

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure for all combinations of impact and wind
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

         Float64 windSign = (wind == stbTypes::Left ? 1 : -1);

         Float64 zo = results.Zo[impact];

         results.ThetaMax[impact][wind] = sqrt((results.EccLateralSweep[impact] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact])/(2.5*zo));

         results.ThetaMax[impact][wind] = ::ForceIntoRange(0.0,results.ThetaMax[impact][wind],THETA_MAX);

         Float64 FSf = (results.Dra[impact]*results.ThetaMax[impact][wind])/((1+2.5*results.ThetaMax[impact][wind])*(zo*results.ThetaMax[impact][wind] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact]) + results.EccLateralSweep[impact]);
         if ( !results.bIsStable[impact] )
         {
            FSf = 0;
         }
         results.FsFailure[impact][wind] = FSf;
         
         // if FSf < FScr then FSf = FScr (if the girder doesn't crack, it doesn't fail)
         results.AdjFsFailure[impact][wind] = Max(results.FsFailure[impact][wind],results.MinFScr);

         if ( ::IsLT(results.FsFailure[impact][wind],results.MinFsFailure) )
         {
            results.MinFsFailure = results.FsFailure[impact][wind];
            results.MinAdjFsFailure = results.AdjFsFailure[impact][wind];
            results.FSfImpactDirection = impact;
            results.FSfWindDirection = wind;
         }
      } // next wind direction
   } // next impact
}

void stbStabilityEngineer::AnalyzeHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,stbHaulingResults& results) const
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

   // we will be finding the minimum value for all analysis points considered
   // initialize to Float64_Max
   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
      results.MinFScr[slope]         =  Float64_Max;
      results.MinFsFailure[slope]    =  Float64_Max;
      results.MinFsRollover[slope]   =  Float64_Max;
      results.MaxStress[slope]       = -Float64_Max;
      results.MinStress[slope]       =  Float64_Max;
      results.MaxDirectStress[slope] = -Float64_Max;
      results.MinDirectStress[slope] =  Float64_Max;
   }

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = results.Wg;

   results.ZoCF = results.Zo[stbTypes::NoImpact]*results.Wcf/Wg;

   stbTypes::HaulingImpact impactUsage = pStabilityProblem->GetImpactUsage();
   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[3] = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   const matConcreteEx& concrete = pStabilityProblem->GetConcrete();
   Float64 fr = concrete.GetFlexureFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();
   Float64 Ktheta = pStabilityProblem->GetTruckRotationalStiffness();
   Float64 CrownSlope = pStabilityProblem->GetCrownSlope();
   Float64 Superelevation = pStabilityProblem->GetSuperelevation();
   Float64 Hrs = pStabilityProblem->GetHeightOfRollAxisAboveRoadway();
   Float64 Wcc = pStabilityProblem->GetWheelLineSpacing();

   Float64 cfSign = (pStabilityProblem->GetCentrifugalForceType() == stbTypes::Adverse ? 1 : -1);

   // overturning moment due to wind and cf applied toward the left
   // Ywind and Dra are a function of impact because of impact forces in the horizontal
   // component of the lifting cable. Since this is a hauling case, such force effects
   // do not exist so we can just use the no impact case.
   results.MotWind = results.Wwind*results.Ywind[stbTypes::NoImpact];
   results.MotCF   = results.Wcf*results.Dra[stbTypes::NoImpact];

   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for ( int s = 0; s < 2; s++ )
      {
         stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

         Float64 alpha = (slope == stbTypes::CrownSlope ? CrownSlope : Superelevation);
         
         Float64 im = 1.0;
         if ( impactUsage == stbTypes::Both ||
             (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) ||
             (impactUsage == stbTypes::MaxSuper    && slope == stbTypes::Superelevation) 
            )
         {
            im = IM[impact];
         }
      
         for ( int w = 0; w < 2; w++ )
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

            Float64 windSign = (wind == stbTypes::Left ? 1 : -1);

            Float64 Zt = windSign*im*results.ZoWind[stbTypes::NoImpact] + cfSign*results.ZoCF;
            Float64 ei = results.EccLateralSweep[impact];
            Float64 Mot = windSign*results.MotWind + cfSign*results.MotCF;

            results.ThetaEq[slope][impact][wind] = (Ktheta*alpha + im*Wg*(Zt + ei) + Mot)/(Ktheta - im*Wg*(im*results.Zo[stbTypes::NoImpact] + results.Dra[stbTypes::NoImpact]));
         }
      }
   }

   PoiIDType poiID = 0;
   CComQIPtr<IFem2dModelResults> femResults(model);
   std::vector<stbIAnalysisPoint*>& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   IndexType analysisPointIdx = 0;
   for( const auto& pAnalysisPoint : vAnalysisPoints)
   {
      Float64 X = pAnalysisPoint->GetLocation();

      stbHaulingSectionResult sectionResult;

      sectionResult.AnalysisPointIndex = analysisPointIdx++;

      for ( int s = 0; s < 2; s++ )
      {
         stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

         sectionResult.fMinDirect[slope][stbTypes::Top]    =  Float64_Max;
         sectionResult.fMinDirect[slope][stbTypes::Bottom] =  Float64_Max;
         sectionResult.fMaxDirect[slope][stbTypes::Top]    = -Float64_Max;
         sectionResult.fMaxDirect[slope][stbTypes::Bottom] = -Float64_Max;

         sectionResult.fMin[slope][stbTypes::Top]    =  Float64_Max;
         sectionResult.fMin[slope][stbTypes::Bottom] =  Float64_Max;
         sectionResult.fMax[slope][stbTypes::Top]    = -Float64_Max;
         sectionResult.fMax[slope][stbTypes::Bottom] = -Float64_Max;

         sectionResult.FScrMin[slope] = Float64_Max;
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

      Float64 Hg,Ag,Ix,Iy,Yt,Wbf,Wtf;
      pGirder->GetSectionProperties(X,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);

      // stress due to prestressing
      sectionResult.fps[stbTypes::Top]    = 0;
      sectionResult.fps[stbTypes::Bottom] = 0;
      for ( int s = 0; s < 3; s++ )
      {
         stbTypes::StrandType strandType = (stbTypes::StrandType)s;

         Float64 Fpe, Y;
         pStabilityProblem->GetFpe(strandType,X,&Fpe,&Y);
         Float64 eps = Y - Yt; // eccentricity of strands (positive values means ps force is above CG)

         Float64 ft = -Fpe/Ag + Fpe*eps*Yt/Ix;
         Float64 fb = -Fpe/Ag + Fpe*eps*(Hg + Yt)/Ix;

         sectionResult.fps[stbTypes::Top]    += ft;
         sectionResult.fps[stbTypes::Bottom] += fb;
      }

      // stress due to dead load
      sectionResult.fg[stbTypes::Top]    = sectionResult.Mg*Yt/Ix;
      sectionResult.fg[stbTypes::Bottom] = sectionResult.Mg*(Hg + Yt)/Ix;

      // stress due to wind towards the left
      sectionResult.fw[stbTypes::TopLeft]     =  sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[stbTypes::TopRight]    = -sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[stbTypes::BottomLeft]  =  sectionResult.Mw*Wbf/(2*Iy);
      sectionResult.fw[stbTypes::BottomRight] = -sectionResult.Mw*Wbf/(2*Iy);

      // stress due to centrifugal
      sectionResult.fcf[stbTypes::TopLeft]     =  cfSign*sectionResult.Mcf*Wtf/(2*Iy);
      sectionResult.fcf[stbTypes::TopRight]    = -cfSign*sectionResult.Mcf*Wtf/(2*Iy);
      sectionResult.fcf[stbTypes::BottomLeft]  =  cfSign*sectionResult.Mcf*Wbf/(2*Iy);
      sectionResult.fcf[stbTypes::BottomRight] = -cfSign*sectionResult.Mcf*Wbf/(2*Iy);

      for ( int i = 0; i < 3; i++ )
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      
         for ( int w = 0; w < 2; w++ )
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

            Float64 windSign = (wind == stbTypes::Left ? 1 : -1);

            for ( int s = 0; s < 2; s++ )
            {
               stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
               sectionResult.FScr[slope][impact][wind] = Float64_Max;

               Float64 im = 1.0;
               if ( impactUsage == stbTypes::Both ||
                   (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) ||
                   (impactUsage == stbTypes::MaxSuper    && slope == stbTypes::Superelevation) 
                  )
               {
                  im = IM[impact];
               }

               Float64 Zt = windSign*im*results.ZoWind[stbTypes::NoImpact];
               Float64 ei = results.EccLateralSweep[impact];
               Float64 MotWind = windSign*results.MotWind;
               Float64 MotCF   = cfSign*results.MotCF; // only used below if we are in the max super case

               Float64 Mot = MotWind;
               if ( slope == stbTypes::MaxSuper )
               {
                  Mot += MotCF;
                  Zt  += cfSign*results.ZoCF;
               }

               for ( int cn = 0; cn < 4; cn++ )
               {
                  stbTypes::Corner corner = (stbTypes::Corner)cn;

                  stbTypes::Face face = (corner == stbTypes::TopLeft || corner == stbTypes::TopRight ? stbTypes::Top : stbTypes::Bottom);
                  Float64 b = (face == stbTypes::Top ? Wtf : Wbf);

                  Float64 cornerSign = (corner == stbTypes::TopLeft || corner == stbTypes::BottomLeft ? 1 : -1);

                  // stress due to direct loads (plumb girder)
                  sectionResult.fDirect[slope][impact][wind][corner] = sectionResult.fps[face] + im*sectionResult.fg[face] + windSign*sectionResult.fw[corner];
                  if ( slope == stbTypes::Superelevation )
                  {
                     sectionResult.fDirect[slope][impact][wind][corner] += sectionResult.fcf[corner];
                  }

                  if ( ::IsLT(sectionResult.fMaxDirect[slope][face],sectionResult.fDirect[slope][impact][wind][corner]) )
                  {
                     sectionResult.fMaxDirect[slope][face] = sectionResult.fDirect[slope][impact][wind][corner];
                     sectionResult.MaxDirectStressImpactDirection[slope][face] = impact;
                     sectionResult.MaxDirectStressWindDirection[slope][face] = wind;
                     sectionResult.MaxDirectStressCorner[slope][face] = corner;
                  }

                  if ( ::IsLT(sectionResult.fDirect[slope][impact][wind][corner],sectionResult.fMinDirect[slope][face]) )
                  {
                     sectionResult.fMinDirect[slope][face] = sectionResult.fDirect[slope][impact][wind][corner];
                     sectionResult.MinDirectStressImpactDirection[slope][face] = impact;
                     sectionResult.MinDirectStressWindDirection[slope][face] = wind;
                     sectionResult.MinDirectStressCorner[slope][face] = corner;
                  }

                  // Overall max direct stress
                  if ( ::IsLT(results.MaxDirectStress[slope],sectionResult.fDirect[slope][impact][wind][corner]) )
                  {
                     results.MaxDirectStress[slope] = sectionResult.fDirect[slope][impact][wind][corner];
                     results.MaxDirectStressAnalysisPointIndex[slope] = (IndexType)poiID;
                     results.MaxDirectStressImpactDirection[slope] = impact;
                     results.MaxDirectStressWindDirection[slope] = wind;
                     results.MaxDirectStressCorner[slope] = corner;
                  }

                  // Overall min direct stress
                  if ( ::IsLT(sectionResult.fDirect[slope][impact][wind][corner],results.MinDirectStress[slope]) )
                  {
                     results.MinDirectStress[slope] = sectionResult.fDirect[slope][impact][wind][corner];
                     results.MinDirectStressAnalysisPointIndex[slope] = (IndexType)poiID;
                     results.MinDirectStressImpactDirection[slope] = impact;
                     results.MinDirectStressWindDirection[slope] = wind;
                     results.MinDirectStressCorner[slope] = corner;
                  }

                  // stress due to lateral loads caused by the girder being tilted
                  sectionResult.fTilt[slope][impact][wind][corner] = cornerSign*(im*sectionResult.Mg*results.ThetaEq[slope][impact][wind])*b/(2*Iy);
               
                  // total stress
                  sectionResult.f[slope][impact][wind][corner] = sectionResult.fDirect[slope][impact][wind][corner] + sectionResult.fTilt[slope][impact][wind][corner];

                  if ( ::IsLT(sectionResult.fMax[slope][face],sectionResult.f[slope][impact][wind][corner]) )
                  {
                     sectionResult.fMax[slope][face] = sectionResult.f[slope][impact][wind][corner];
                     sectionResult.MaxStressImpactDirection[slope][face] = impact;
                     sectionResult.MaxStressWindDirection[slope][face] = wind;
                     sectionResult.MaxStressCorner[slope][face] = corner;
                  }

                  if ( ::IsLT(sectionResult.f[slope][impact][wind][corner],sectionResult.fMin[slope][face]) )
                  {
                     sectionResult.fMin[slope][face] = sectionResult.f[slope][impact][wind][corner];
                     sectionResult.MinStressImpactDirection[slope][face] = impact;
                     sectionResult.MinStressWindDirection[slope][face] = wind;
                     sectionResult.MinStressCorner[slope][face] = corner;
                  }

                  // Overall max stress (all analysis points)
                  if ( ::IsLT(results.MaxStress[slope],sectionResult.f[slope][impact][wind][corner]) )
                  {
                     results.MaxStress[slope] = sectionResult.f[slope][impact][wind][corner];
                     results.MaxStressAnalysisPointIndex[slope] = (IndexType)poiID;
                     results.MaxStressImpactDirection[slope] = impact;
                     results.MaxStressWindDirection[slope] = wind;
                     results.MaxStressCorner[slope] = corner;
                  }

                  // Overall min stress (all analysis points)
                  if ( ::IsLT(sectionResult.f[slope][impact][wind][corner],results.MinStress[slope]) )
                  {
                     results.MinStress[slope] = sectionResult.f[slope][impact][wind][corner];
                     results.MinStressAnalysisPointIndex[slope] = (IndexType)poiID;
                     results.MinStressImpactDirection[slope] = impact;
                     results.MinStressWindDirection[slope] = wind;
                     results.MinStressCorner[slope] = corner;
                  }

                  // compute cracking moment and cracking factor of safety
                  Float64 mcr = (fr - sectionResult.fDirect[slope][impact][wind][corner])*2*Iy/b;
                  mcr = Max(mcr,0.0); // if mcr is less than zero, the beam cracks even if it is not tilted... there isn't a lateral moment to cause cracking since it is already cracked
                  Float64 m = fabs(im*sectionResult.Mg);
                  Float64 theta_crack = (IsZero(m) ? THETA_MAX : mcr/m);
                  theta_crack = ::ForceIntoRange(0.0,theta_crack,THETA_MAX);
                  sectionResult.Mcr[slope][impact][wind][corner] = mcr;
                  sectionResult.ThetaCrack[slope][impact][wind][corner] = theta_crack;
                  Float64 alpha = (slope == stbTypes::CrownSlope ? CrownSlope : Superelevation);
                  Float64 fscr = (Ktheta*(theta_crack - alpha))/(im*Wg*((im*results.Zo[stbTypes::NoImpact] + results.Dra[stbTypes::NoImpact])*theta_crack + Zt + ei) + Mot);
                  fscr = Max(fscr,0.0); // can't be less than zero... theta_crack-alpha < 0 means a slope of alpha alone will crack the girder

                  if ( ::IsLT(fscr,sectionResult.FScr[slope][impact][wind]) )
                  {
                     // capture governing condition and related parameters
                     sectionResult.CrackedFlange[slope][impact][wind] = corner;
                     sectionResult.FScr[slope][impact][wind] = fscr;
                  }

                  if ( ::IsLT(fscr,sectionResult.FScrMin[slope]) )
                  {
                     sectionResult.FScrMin[slope] = fscr;
                     sectionResult.FScrImpactDirection[slope] = impact;
                     sectionResult.FScrWindDirection[slope] = wind;
                     sectionResult.FScrCorner[slope] = corner;
                  }
               } // next slope type
            } // next corner

            // keep track of the minimum FScr for all analysis points
            for ( int s = 0; s < 2; s++ )
            {
               stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
               if ( ::IsLT(sectionResult.FScr[slope][impact][wind],results.MinFScr[slope]) )
               {
                  results.MinFScr[slope] = sectionResult.FScr[slope][impact][wind];
                  results.FScrAnalysisPointIndex[slope] = (IndexType)poiID; // poiIDs exactly match the analysis point indicies
                  results.FScrImpactDirection[slope] = impact;
                  results.FScrWindDirection[slope] = wind;
               }

               if ( segment )
               {
                  CComPtr<IShape> shape;
                  segment->get_PrimaryShape(X,sbLeft,&shape);

                  CComPtr<IRebarSection> rebarSection;
                  rebarLayout->CreateRebarSection(X,INVALID_INDEX,&rebarSection);

                  Float64 fy = pStabilityProblem->GetRebarYieldStrength();
                  Float64 fsMax = ::ConvertToSysUnits(30.0,unitMeasure::KSI);
                  lrfdAlternativeTensileStressCalculator altCalc(concrete,fy,true,fsMax);

                  Float64 Yna, NAslope, AreaTension,T,AsProvided,AsRequired;
                  bool bIsAdequateRebar;
                  altCalc.ComputeAlternativeStressRequirements(shape,rebarSection,
                     Wtf,Wbf,
                     sectionResult.f[slope][impact][wind][stbTypes::TopLeft],
                     sectionResult.f[slope][impact][wind][stbTypes::TopRight],
                     sectionResult.f[slope][impact][wind][stbTypes::BottomLeft],
                     sectionResult.f[slope][impact][wind][stbTypes::BottomRight],
                     &Yna,&NAslope,&AreaTension,&T,&AsProvided,&AsRequired,&bIsAdequateRebar);

                     sectionResult.bSectionHasRebar[slope][impact][wind] = bIsAdequateRebar;

                     sectionResult.Yna[slope][impact][wind] = Yna;
                     sectionResult.NAslope[slope][impact][wind] = NAslope;
                     sectionResult.AreaTension[slope][impact][wind] = AreaTension;
                     sectionResult.T[slope][impact][wind] = T;
                     sectionResult.AsProvided[slope][impact][wind] = AsProvided;
                     sectionResult.AsRequired[slope][impact][wind] = AsRequired;
               }
            } // next slope
         } // next wind direction
      } // next impact

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure and roll over for all combinations of impact and wind
   for ( int i = 0; i < 3; i++ )
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;

      for ( int w = 0; w < 2; w++ )
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

         Float64 windSign = (wind == stbTypes::Left ? 1 : -1);

         for ( int s = 0; s < 2; s++ )
         {
            stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

            Float64 im = 1.0;
            if ( impactUsage == stbTypes::Both ||
                (impactUsage == stbTypes::NormalCrown && slope == stbTypes::CrownSlope) ||
                (impactUsage == stbTypes::MaxSuper    && slope == stbTypes::Superelevation) 
               )
            {
               im = IM[impact];
            }

            Float64 Zt = windSign*im*results.ZoWind[stbTypes::NoImpact];
            Float64 ei = results.EccLateralSweep[impact];
            Float64 Mot = windSign*results.MotWind;
            if ( slope == stbTypes::MaxSuper )
            {
               Zt  += cfSign*results.ZoCF;
               Mot += cfSign*results.MotCF;
            }

            // FS Failure

            // compute theta max... PCI examples use a numerical solver in mathcad, however I derived the closed form solution.
            // (See SupportingDocuments folder for derivation)
            Float64 alpha = (slope == stbTypes::CrownSlope ? CrownSlope : Superelevation);
            Float64 theta_max = IsZero(im*Wg) ? THETA_MAX : alpha + sqrt(alpha*alpha + (ei + Mot/(im*Wg) + (im*results.Zo[stbTypes::NoImpact] + Zt + results.Dra[stbTypes::NoImpact])*alpha)/(2.5*(im*results.Zo[stbTypes::NoImpact] + Zt)));
            theta_max = ::ForceIntoRange(0.0,theta_max,THETA_MAX);
            results.ThetaMax[slope][impact][wind] = theta_max;

            Float64 Mr = Ktheta*(theta_max - alpha); // resisting moment
            Float64 zo = im*results.Zo[stbTypes::NoImpact]*(1.0 + 2.5*theta_max);
            Float64 Ma = im*Wg*((zo + results.Dra[stbTypes::NoImpact])*theta_max + ei + Zt*theta_max*(1 + 2.5*theta_max)) + Mot; // acting moment
            Float64 FSf = IsLE(Ma,0.0) ? Float64_Max : Mr/Ma;
            results.FsFailure[slope][impact][wind] = FSf;
         
            // if FSf < FScr then FSf = FScr (if the girder doesn't crack, it doesn't fail)
            results.AdjFsFailure[slope][impact][wind] = Max(results.FsFailure[slope][impact][wind],results.MinFScr[slope]);

            if ( ::IsLT(results.FsFailure[slope][impact][wind],results.MinFsFailure[slope]) )
            {
               results.MinFsFailure[slope] = results.FsFailure[slope][impact][wind];
               results.MinAdjFsFailure[slope] = results.AdjFsFailure[slope][impact][wind];
               results.FSfImpactDirection[slope] = impact;
               results.FSfWindDirection[slope] = wind;
            }

            // FS Rollover
            results.MroWind = results.Wwind*Hrs + results.MotWind;
            results.MroCF   = results.Wcf*Hrs   + results.MotCF;
            Float64 Mro = windSign*results.MroWind;
            if ( slope == stbTypes::MaxSuper )
            {
               Mro += cfSign*results.MroCF;
            }

            Float64 theta_roll = (im*Wg*(Wcc/2 - Hrs*alpha - SupportPlacementTolerance) + Mro)/Ktheta + alpha;
            results.ThetaRollover[slope][impact][wind] = theta_roll;

            Mr = Ktheta*(theta_roll - alpha); // resisting moment
            zo = im*results.Zo[stbTypes::NoImpact]*(1.0 + 2.5*theta_roll);
            Ma = im*Wg*((zo + results.Dra[stbTypes::NoImpact])*theta_roll + ei + Zt*(1 + 2.5*theta_roll)) + Mro; // acting moment
            Float64 FSr = IsLE(Ma,0.0) ? Float64_Max : Mr/Ma;
            results.FsRollover[slope][impact][wind] = FSr;

            if ( ::IsLT(results.FsRollover[slope][impact][wind],results.MinFsRollover[slope]) )
            {
               results.MinFsRollover[slope] = results.FsRollover[slope][impact][wind];
               results.FSroImpactDirection[slope] = impact;
               results.FSroWindDirection[slope] = wind;
            }
         } // next slope type
      } // next wind direction
   } // next impact
}

void stbStabilityEngineer::BuildModel(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel) const
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

      if ( leftSupportJntID==INVALID_ID && IsEqual(X,leftSupportLoc) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtFx);
         jnt->ReleaseDof(jrtMz);
         leftSupportJntID = jntID;
      }
      else if (rightSupportJntID==INVALID_ID &&  IsEqual(X,rightSupportLoc) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtMz);
         rightSupportJntID = jntID;
      }

      jntID++;
   }

   ATLASSERT(leftSupportJntID != INVALID_ID && rightSupportJntID != INVALID_ID); // missing support. we will crash

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

   MemberIDType mbrID = 0;
   CComPtr<IFem2dMemberCollection> members;
   (*ppModel)->get_Members(&members);

   Float64 g = unitSysUnitsMgr::GetGravitationalAcceleration();

   const matConcreteEx& concrete = pStabilityProblem->GetConcrete();
   Float64 density = concrete.GetDensityForWeight();
   Float64 unitWeight = density*g;

   Float64 Ec = concrete.GetE();

   stbTypes::WindType windLoadType;
   Float64 windLoad;
   pStabilityProblem->GetWindLoading(&windLoadType,&windLoad);
   Float64 WindPressure;
   if ( windLoadType == stbTypes::Pressure )
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
   const stbIHaulingStabilityProblem* pHaulingProblem = dynamic_cast<const stbIHaulingStabilityProblem*>(pStabilityProblem);
   if ( pHaulingProblem )
   {
      Float64 V = pHaulingProblem->GetVelocity();
      Float64 R = pHaulingProblem->GetTurningRadius();
      ATLASSERT(R != 0.0);
      CFfactor = (V*V)/(g*R);
   }


   jntID = 1;
   std::vector<Float64>::iterator prevIter(vX.begin());
   std::vector<Float64>::iterator iter = prevIter+1;
   std::vector<Float64>::iterator end(vX.end());
   Float64 prevA, Ix, Iy, prevYt, prevHg, Wtf, Wbf;
   pGirder->GetSectionProperties(*prevIter,&prevA,&Ix,&Iy,&prevYt,&prevHg,&Wtf,&Wbf);
   LoadIDType loadID = 0;
   Float64 Wg = 0;
   Float64 Wcf = 0;
   Float64 Wwind = 0;
   Float64 YwindWwind = 0;
   Float64 ycgwg = 0;
   for ( ; iter != end; iter++, prevIter++, jntID++, mbrID++, loadID++ )
   {
      Float64 prevX = *prevIter;
      Float64 currX = *iter;
      
      Float64 Ag,Yt,Hg;
      pGirder->GetSectionProperties(currX,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);

      Float64 EA = Ag*Ec;
      Float64 EI = Ix*Ec;

      // create member
      CComPtr<IFem2dMember> member;
      members->Create(mbrID,jntID-1,jntID,EA,EI,&member);

      // load member 
      // Self-weight
      Float64 wStart = prevA*unitWeight;
      Float64 wEnd   =    Ag*unitWeight;
      CComPtr<IFem2dDistributedLoad> swDistLoad;
      swDistributedLoads->Create(loadID,mbrID,loadDirFy,0.0,-1.0,-wStart,-wEnd,lotMember,&swDistLoad);

      Float64 wg = (wStart + wEnd)*(currX - prevX);
      Wg += wg;
      ycgwg += (prevYt + Yt)*wg;

      // NOTE: Wind and CF is applied in the same direction as gravity
      // We have a 2D, plane frame model, not a 3D space frame. Our FEM engine does not support out of plane loading
      // Techincally, this is incorrect, however the moments and shears are the same for loads applied transverse to the girder
      // Deflections will be incorrect. Deflections from the FEM model will need to be scaled by Ix/Iy

      // Centrifugal Force
      wStart *= CFfactor;
      wEnd   *= CFfactor;
      CComPtr<IFem2dDistributedLoad> cfDistLoad;
      cfDistributedLoads->Create(loadID,mbrID,loadDirFy,0.0,-1.0,-wStart,-wEnd,lotMember,&cfDistLoad);

      // cummulate the total centrifugal force
      // average force * distance = [(wStart+wEnd)/2]*(currX-prevX)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      Wcf += (wStart + wEnd)*(currX - prevX);

      // Wind
      CComPtr<IFem2dDistributedLoad> windDistLoad;
      wStart = prevHg*WindPressure;
      wEnd   =     Hg*WindPressure;
      windDistributedLoads->Create(loadID,mbrID,loadDirFy,0.0,-1.0,-wStart,-wEnd,lotMember,&windDistLoad);

      // cummulate the total wind load
      // average wind load * distance = [(wStart+wEnd)/2]*(currX-prevX)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      Float64 w_wind = (wStart + wEnd)*(currX - prevX);
      Wwind += w_wind;

      // the location of the resultant wind force is Sum(ExposedArea*WindPressure*DepthToCGofExposedArea)/(Total Wind Force)
      // Assuming sections that taper linerally in depth, the DepthToCGofExposedArea for each segment is the centroid of a trapazoid
      // y = (a^2 + ab + b^2)/(3(a+b))
      // Where we are doing the summation. The negative is because we are measuring down from the top which is what we need for
      // girder section coordinates
      Float64 a = prevHg;
      Float64 b = Hg;
      Float64 y_wind = (a*a + a*b + b*b)/(3*(a+b));
      YwindWwind += -y_wind*w_wind;

      prevA = Ag;
      prevYt = Yt;
      prevHg = Hg;
   }

   results.Wg = Wg/2;
   ycgwg /= 2;
   results.Ycg = ycgwg/Wg;

   // divide by 2 to get total wind load (see note above)
   results.Wwind = Wwind/2;
   YwindWwind /= 2; // divide by 2 because the wind part should have been above, but we didn't
   results.Ywind[stbTypes::NoImpact] = ::IsZero(results.Wwind) ? 0 : YwindWwind/results.Wwind; // this now holds the location of the resultant wind force measured from the top of the girder

   if ( pHaulingProblem )
   {
      stbHaulingResults* pHaulingResults = static_cast<stbHaulingResults*>(&results);
      ATLASSERT(pHaulingResults != nullptr);
      pHaulingResults->Wcf = Wcf/2;
   }

   // Apply self weight point loads
   LoadIDType ptLoadID = 0;
   Wg = 0;
   ycgwg = 0;
   std::vector<std::pair<Float64,Float64>> vPointLoads = pGirder->GetAdditionalLoads();
   std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIter(vPointLoads.begin());
   std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIterEnd(vPointLoads.end());
   for ( ; ptLoadIter != ptLoadIterEnd; ptLoadIter++ )
   {
      Float64 X = ptLoadIter->first;
      Float64 P = ptLoadIter->second;
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
      Float64 Ag,Ix,Iy,Yt,Hg,Wtf,Wbf;
      pGirder->GetSectionProperties(X,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);
      ycgwg = Yt*P;
   }

   // adjust total weight and vertical center of mass for point loads
   results.Ycg = (results.Wg*results.Ycg + ycgwg)/(results.Wg + Wg);
   results.Wg += Wg;

   // Apply point loads for due to lifting
   const stbILiftingStabilityProblem* pLiftingProblem = dynamic_cast<const stbILiftingStabilityProblem*>(pStabilityProblem);
   if ( pLiftingProblem )
   {
      // We don't know the horizontal component of the lift force here, so we will just use a unit force
      // and then scale the results later
      Float64 Ph = 1.0;

      Float64 Yrc = pStabilityProblem->GetYRollAxis();

      Float64 Ag,Ix,Iy,Yt,Hg,Wtf,Wbf;
      pGirder->GetSectionProperties(leftSupportLoc,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);
      Float64 Mleft = -Ph*(Yt + Yrc);

      pGirder->GetSectionProperties(rightSupportLoc,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);
      Float64 Mright = Ph*(Yt + Yrc);

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
   std::vector<stbIAnalysisPoint*>& vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
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
   if ( results.ZoMethod == stbTypes::Approximate )
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

#if defined _DUMP_FEM_MODEL
   CString strFilename(_T("StabilityModel_Fem2d.xml"));

   CComPtr<IStructuredSave2> save;
   save.CoCreateInstance(CLSID_StructuredSave2);
   save->Open(T2BSTR(strFilename));

   CComQIPtr<IStructuredStorage2> storage(*ppModel);
   storage->Save(save);

   save->Close();
#endif
}

void stbStabilityEngineer::GetZoComputationMethod(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,IFem2dModel* pModel,stbResults& results) const
{
   if ( pGirder->GetSectionCount() == 1 )
   {
      Float64 Ag1,Ix1,Iy1,Yt1,Hg1,Wtop1,Wbot1;
      Float64 Ag2,Ix2,Iy2,Yt2,Hg2,Wtop2,Wbot2;
      pGirder->GetSectionProperties(0,stbTypes::Start,&Ag1,&Ix1,&Iy1,&Yt1,&Hg1,&Wtop1,&Wbot1);
      pGirder->GetSectionProperties(0,stbTypes::End,  &Ag2,&Ix2,&Iy2,&Yt2,&Hg2,&Wtop2,&Wbot2);
      Float64 Ll, Lr;
      pStabilityProblem->GetSupportLocations(&Ll,&Lr);
      std::vector<std::pair<Float64,Float64>> vLoads = pGirder->GetAdditionalLoads();
      if ( IsEqual(Ag1,Ag2) && IsEqual(Ix1,Ix2) && IsEqual(Iy1,Iy2) && IsEqual(Yt1,Yt2) && IsEqual(Hg1,Hg2) && IsEqual(Wtop1,Wtop2) && IsEqual(Wbot1,Wbot2) && IsEqual(Ll,Lr) && vLoads.size() == 0)
      {
         results.ZoMethod = stbTypes::Exact;
      }
      else
      {
         results.ZoMethod = stbTypes::Approximate;
      }
   }
   else
   {
      results.ZoMethod = stbTypes::Approximate;
   }
}

Float64 stbStabilityEngineer::ComputeZo(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,IFem2dModel* pModel,stbResults& results) const
{
   Float64 Zo;
   if ( results.ZoMethod == stbTypes::Exact )
   {
      Float64 Ec = pStabilityProblem->GetConcrete().GetE();
      Float64 Lg = pGirder->GetGirderLength();
      Float64 Ag,Ix,Iy,Yt,Hg,Wt,Wb;
      pGirder->GetSectionProperties(Lg/2,&Ag,&Ix,&Iy,&Yt,&Hg,&Wt,&Wb);
      Float64 W = results.Wg;
      Float64 l = results.Ls;
      Float64 a = (Lg-l)/2; // assuming equal overhangs
      Zo = (W/(12*Ec*Iy*Lg*Lg))*(l*l*l*l*l/10. - a*a*l*l*l + 3.*a*a*a*a*l + 6.*a*a*a*a*a/5.);
   }
   else
   {
      ATLASSERT(m_FirstPoi - m_LastPoi + 1 == m_vPoi.size());
      CComQIPtr<IFem2dModelResults> femResults(pModel);
      Float64 g = unitSysUnitsMgr::GetGravitationalAcceleration();

      const matConcreteEx& concrete = pStabilityProblem->GetConcrete();
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

         Float64 Ag1,Ix1,Iy1,Yt,Hg,Wtop,Wbot;
         Float64 Ag2,Ix2,Iy2;
         pGirder->GetSectionProperties(x1,&Ag1,&Ix1,&Iy1,&Yt,&Hg,&Wtop,&Wbot);
         pGirder->GetSectionProperties(x2,&Ag2,&Ix2,&Iy2,&Yt,&Hg,&Wtop,&Wbot);

         Float64 w1 = Ag1*unitWeight;
         Float64 w2 = Ag2*unitWeight;

         // this is vertical deflection based on Ix...
         Float64 dx,dy1,dy2,rz;
         femResults->ComputePOIDeflections(LCID_GIRDER,poiID1,lotMember,&dx,&dy1,&rz);
         femResults->ComputePOIDeflections(LCID_GIRDER,poiID2,lotMember,&dx,&dy2,&rz);
         // we want lateral deflection based on Iy...
         dy1 *= Ix1/Iy1;
         dy2 *= Ix2/Iy2;

         Float64 zo = 0.5*(w1*dy1 + w2*dy2)*(x2 - x1);
         Zo += zo;
      }

      ATLASSERT(poiID1 == m_LastPoi);

      Float64 Wg = results.Wg;
      Zo /= -Wg;
   }
   return Zo;
}

void stbStabilityEngineer::GetRebarLayout(const stbIGirder* pGirder,IRebarLayout** ppRebarLayout) const
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

Float64 stbStabilityEngineer::ComputePz(Float64 velocity,Float64 Cd) const
{
   // LRFD 3.8.1.2
   // Kz and G = 1.0 for Service I
   Float64 V = ::ConvertFromSysUnits(velocity,unitMeasure::MilePerHour);
   Float64 Pz = (2.56e-6)*V*V*Cd;
   Pz = ::ConvertToSysUnits(Pz,unitMeasure::KSF);
   return Pz;
}
