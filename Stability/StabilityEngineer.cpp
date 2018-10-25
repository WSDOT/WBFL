///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <algorithm>
#include <UnitMgt\UnitMgt.h>
#include <LRFD\ConcreteUtil.h>
#include <Math\CubicSolver.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LCID_GIRDER 0
#define LCID_WIND   1
#define LCID_CF     2
#define LCID_LIFT   3

stbStabilityEngineer::stbStabilityEngineer()
{
}

stbLiftingResults stbStabilityEngineer::AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem) const
{
   stbLiftingResults results;
   PrepareResults(pGirder,pStabilityProblem,results);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = pGirder->GetGirderWeight();

   // compute critical buckling load
   Float64 Ag,Ix,Iy,Yt,Hg,Wtop,Wbot;
   pGirder->GetSectionProperties(Lg/2,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtop,&Wbot);
   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);
   Float64 Ec = pStabilityProblem->GetEc();
   results.Pcrit = M_PI*M_PI*Ec*Iy/((Lg - Ll - Lr)*(Lg - Ll - Lr));

   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[3] = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   // horizontal component of force due to inclined lifting cables
   // negative value because it causes compression
   results.Plift = -(Wg/2)*tan(PI_OVER_2 - pStabilityProblem->GetLiftAngle());
   results.Plift = ::IsZero(results.Plift) ? 0.0 : results.Plift;

   ATLASSERT( !IsZero(pStabilityProblem->GetLiftAngle()) );
   for ( IndexType impact = 0; impact < 3; impact++ )
   {
      Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);

      // compute lateral deflection multiplier
      if ( results.Plift < 0 )
      {
         // inclined cables cause compression
         results.emag[impact] = 1/(1 - fabs(im*results.Plift/results.Pcrit)); // lateral deflection multiplier
      }
      else
      {
         // inclined cables cause tension which will straighten the girder
         results.emag[impact] = 1.0;
      }

      // adjust eccentricity of CG of girder due to lateral sweep
      results.EccLateralSweep[impact] *= results.emag[impact];
   }

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

stbLiftingCheckArtifact stbStabilityEngineer::CheckLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,const stbCriteria& criteria) const
{
   stbLiftingResults results = AnalyzeLifting(pGirder,pStabilityProblem);
   stbLiftingCheckArtifact artifact(results,criteria);
   return artifact;
}

stbHaulingCheckArtifact stbStabilityEngineer::CheckHauling(const stbIGirder* pGirder,const stbIHaulingStabilityProblem* pStabilityProblem,const stbCriteria& criteria) const
{
   stbHaulingResults results = AnalyzeHauling(pGirder,pStabilityProblem);
   stbHaulingCheckArtifact artifact(results,criteria);
   return artifact;
}

void stbStabilityEngineer::PrepareResults(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results) const
{
   // Compute girder weight and length of girder by adding up contribution of each section based on the section properties
   Float64 Ll,Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);
   Float64 Lg = pGirder->GetGirderLength();

   results.Ls = Lg - Ll - Lr;
   Float64 span_ratio = results.Ls/Lg;

#pragma Reminder("OFFSET FACTOR assumes equal overhang?")
   results.OffsetFactor = (span_ratio)*(span_ratio) - 1./3.;
   results.OffsetFactor = IsZero(results.OffsetFactor) ? 0 : results.OffsetFactor;
   results.LateralSweep = pStabilityProblem->GetSweepTolerance()*Lg;

   for ( IndexType impact = 0; impact < 3; impact++ )
   {
      results.EccLateralSweep[impact] = results.OffsetFactor*results.LateralSweep + pStabilityProblem->GetSupportPlacementTolerance();
   }
}

void stbStabilityEngineer::Analyze(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel,PoiIDType* pMidSpanPoiID) const
{
   BuildModel(pGirder,pStabilityProblem,results,ppModel,pMidSpanPoiID);

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = pGirder->GetGirderWeight();

#pragma Reminder("WORKING HERE - is this correct for haunched spliced girder segments? or uniform taper length segments?")
   Float64 A,Ix,Iy,Ycg,Hg,Wtf,Wbf;
   pGirder->GetSectionProperties(Lg/2,&A,&Ix,&Iy,&Ycg,&Hg,&Wtf,&Wbf);

#pragma Reminder("WORKING HERE - need vertical CG of wind load action... assuming constant depth girder") // may be at a different location for variable depth girders
   Float64 Yra = pStabilityProblem->GetYRollAxis();
   Float64 y = Yra + Hg/2; // location from the mid-height of the girder (location where the resultant wind force acts) to the roll axis (positive means roll center is above CG)
   Float64 Ywind = fabs(y);

   // adjust for camber
   bool bDirectCamber;
   Float64 Camber;
   pStabilityProblem->GetCamber(&bDirectCamber,&Camber);
   if ( bDirectCamber )
   {
      Ywind -= ::BinarySign(y)*results.OffsetFactor*Camber;
   }
   else
   {
      Ywind *= (1. - ::BinarySign(y)*Camber);
   }
   // additional effects due to impact adjusted force of inclined lifting cable will be added later
   results.Ywind[IMPACT_NONE] = Ywind;
   results.Ywind[IMPACT_UP]   = Ywind;
   results.Ywind[IMPACT_DOWN] = Ywind;

   results.Yr = Yra - Ycg; // location from the center of gravity from the roll axis (positive means roll center is above CG)
   Float64 Dra = fabs(results.Yr);  // adjusted distance between CG and roll axis (using fabs because distance is an absolute value)
   if ( bDirectCamber )
   {
      Dra -= ::BinarySign(results.Yr)*results.OffsetFactor*Camber;
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
   results.Dra[IMPACT_NONE] = Dra;
   results.Dra[IMPACT_UP]   = Dra;
   results.Dra[IMPACT_DOWN] = Dra;

   // lateral deflection due to full load applied laterally
   //Float64 g = unitSysUnitsMgr::GetGravitationalAcceleration();
   //Float64 Ec = pStabilityProblem->GetEc();
   //Float64 density = pGirder->GetDensity();
   //Float64 w = A*density*g;
   //Float64 l = results.Ls;
   //Float64 a = (Lg-l)/2; // assuming equal overhangs
   //Float64 zo = (w/(12*Ec*Iy*Lg))*(l*l*l*l*l/10. - a*a*l*l*l + 3.*a*a*a*a*l + 6.*a*a*a*a*a/5.);
   Float64 zo = ComputeZo(pGirder,*ppModel); // performed using numerical integration

   Float64 ImpactUp, ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[] = { 1.0, 1.0 - ImpactUp, 1.0 + ImpactDown };
   for ( IndexType impact = 0; impact < 3; impact++ )
   {
      Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);
      results.Zo[impact] = im*zo;
      results.ZoWind[impact] = results.Zo[impact]*results.Wwind/(im*Wg);
   }

   results.ZoCF = zo*results.Wcf/Wg;
}

void stbStabilityEngineer::AnalyzeLifting(const stbIGirder* pGirder,const stbILiftingStabilityProblem* pStabilityProblem,stbLiftingResults& results) const
{
   PoiIDType midSpanPoiID;
   CComPtr<IFem2dModel> model;
   Analyze(pGirder,pStabilityProblem,results,&model,&midSpanPoiID);

   // Get deflection due to horizontal component of lifting cable force
   CComQIPtr<IFem2dModelResults> femResults(model);
   // recall that the deflection is based on a unit force, so scale the value from the fem model by the actual force
   Float64 dx,dy1,dy2,rz;
   femResults->ComputePOIDeflections(LCID_LIFT,0,lotMember,&dx,&dy1,&rz);
   femResults->ComputePOIDeflections(LCID_LIFT,midSpanPoiID,lotMember,&dx,&dy2,&rz);
   results.dLift = results.Plift*(dy2 - dy1); // does not include impact... measured relative to the ends of the girder

   Float64 Wg = pGirder->GetGirderWeight();
   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[3] = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};
   for ( IndexType impact = 0; impact < 3; impact++ )
   {
      // magnify lateral deflections due to horizontal component of lifting cable force
      results.Zo[impact]     *= results.emag[impact]; // emag includes impact
      results.ZoWind[impact] *= results.emag[impact];

      // add the deflection due to the horiztonal component of the lifting cable force
      // to the location of the resultant gravity and wind forces
      Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);
      results.Dra[impact]   -= results.OffsetFactor*im*results.dLift;
      results.Ywind[impact] -= results.OffsetFactor*im*results.dLift;

      // compute the lateral eccentricity of the girder self-weight due to the wind load
      results.EccWind[impact] = results.Wwind*results.Ywind[impact]/(im*Wg);

      // if the roll axis is below the center of mass for a hanging girder, it is unstable.
      // the girder will have to turn completely over to acheive equilibrium
      results.bIsStable[impact] = (results.Dra[impact] < 0 ? false : true);
   }

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   results.MinFScr      = DBL_MAX;
   results.MinFsFailure = DBL_MAX;
   results.MaxStress    = -DBL_MAX;
   results.MinStress    = DBL_MAX;

   Float64 Lg = pGirder->GetGirderLength();

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   Float64 fr = pStabilityProblem->GetFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();

#pragma Reminder("WORKING HERE - assuming equal overhangs")
   Float64 l = results.Ls;
   Float64 a = (Lg-l)/2; // assuming equal overhangs

   // Compute tilt equilibrium angle
   for ( IndexType impact = 0; impact < 3; impact++ )
   {
      for ( IndexType wind = 0; wind < 2; wind++ )
      {
         Float64 windSign = (wind == LEFT ? 1 : -1);
         results.ThetaEq[impact][wind] = (results.EccLateralSweep[impact] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact])/(results.Dra[impact] - results.Zo[impact]);
      }
   }

   bool bDirectCamber;
   Float64 Camber;
   pStabilityProblem->GetCamber(&bDirectCamber,&Camber);


   PoiIDType poiID = 0;
   std::vector<Float64> vX = pStabilityProblem->GetAnalysisPoints();
   BOOST_FOREACH(Float64 X,vX)
   {
      stbLiftingSectionResult sectionResult;

      sectionResult.X = X;

      // eccentricity of horizontal load due to inclined cable at X
      // assuming equal overhangs!
#pragma Reminder("WORKING HERE - assuming equal overhangs")
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
      sectionResult.fps[TOP]    = 0;
      sectionResult.fps[BOTTOM] = 0;
      for ( int strandType = 0; strandType < 3; strandType++ )
      {
         Float64 Y = pGirder->GetStrandLocation(strandType,X);
         Float64 eps = Y - Yt; // eccentricity of strands (positive values means ps force is above CG)
         Float64 Fpe = pStabilityProblem->GetFpe(strandType,X);

         Float64 ft = -Fpe/Ag + Fpe*eps*Yt/Ix;
         Float64 fb = -Fpe/Ag + Fpe*eps*(Hg + Yt)/Ix;

         sectionResult.fps[TOP]    += ft;
         sectionResult.fps[BOTTOM] += fb;
      }

      // stress due to inclined lift cable
      Float64 Plift = results.Plift;
      if ( X < Ll || (Lg - Lr) < X )
      {
         Plift = 0; // X is not between the lifting devices so there isn't any axial load due to the inclined cable
      }

      // stress due to inclined lift cables (no impact)
      sectionResult.fcable[TOP]    = Plift*(1/Ag - results.Dra[IMPACT_NONE]*Yt/Ix);
      sectionResult.fcable[BOTTOM] = Plift*(1/Ag - results.Dra[IMPACT_NONE]*(Hg-Yt)/Ix);

      // stress due to dead load (no impact)
      sectionResult.fg[TOP]    = sectionResult.Mg*Yt/Ix;
      sectionResult.fg[BOTTOM] = sectionResult.Mg*(Hg + Yt)/Ix;

      // stress due to wind towards the left
      sectionResult.fw[TOP_LEFT]     =  sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[TOP_RIGHT]    = -sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[BOTTOM_LEFT]  =  sectionResult.Mw*Wbf/(2*Iy);
      sectionResult.fw[BOTTOM_RIGHT] = -sectionResult.Mw*Wbf/(2*Iy);

      // analyze the girder for all the combinations of impact and wind
      for ( int impact = 0; impact < 3; impact++ )
      {
         Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);

         for ( int wind = 0; wind < 2; wind++ )
         {
            Float64 windSign = (wind == LEFT ? 1 : -1);

            sectionResult.fMin[TOP][impact][wind]    =  DBL_MAX;
            sectionResult.fMax[TOP][impact][wind]    = -DBL_MAX;
            sectionResult.fMin[BOTTOM][impact][wind] =  DBL_MAX;
            sectionResult.fMax[BOTTOM][impact][wind] = -DBL_MAX;
            sectionResult.FScr[impact][wind]         =  DBL_MAX;

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


            for ( int corner = 0; corner < 4; corner++ )
            {
               int face = (corner == TOP_LEFT || corner == TOP_RIGHT ? TOP : BOTTOM);
               Float64 b = (face == TOP ? Wtf : Wbf);

               Float64 cornerSign = (corner == TOP_LEFT || corner == BOTTOM_LEFT ? 1 : -1);

               // stress due to direct loads
               sectionResult.fDirect[impact][wind][corner] = sectionResult.fps[face] + IM[impact]*(sectionResult.fcable[face] + sectionResult.fg[face]) + windSign*sectionResult.fw[corner];

               // stress due to lateral loads caused by the girder being tilted
               sectionResult.fTilt[impact][wind][corner] = cornerSign*(im*(sectionResult.Mg + Plift*results.Zo[impact])*results.ThetaEq[impact][wind] + sectionResult.Mh[impact][wind])*b/(2*Iy);

               // total stress
               sectionResult.f[impact][wind][corner] = sectionResult.fDirect[impact][wind][corner] + sectionResult.fTilt[impact][wind][corner];

               if ( !pStabilityProblem->ApplyImpactToTiltedGirder() )
               {
                  // the total stress includes impact applied to the girder dead load, however, 
                  // we don't want this so remove it
                  sectionResult.f[impact][wind][corner] += (im - IM[impact])*(sectionResult.fcable[face] + sectionResult.fg[face]);
               }

               sectionResult.fMax[face][impact][wind] = Max(sectionResult.fMax[face][impact][wind],sectionResult.f[impact][wind][corner]);
               sectionResult.fMin[face][impact][wind] = Min(sectionResult.fMin[face][impact][wind],sectionResult.f[impact][wind][corner]);

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
               if ( !pStabilityProblem->ApplyImpactToTiltedGirder() )
               {
                  // the direct stress has impact applied to the girder self weight... we don't want this for the tilted girder, so remove it
                  mcr -= (im - IM[impact])*(sectionResult.fcable[face] + sectionResult.fg[face])*2*Iy/b;
               }
               mcr = Max(mcr,0.0); // if mcr is less than zero, the beam cracks even if it is not tilted... there isn't a lateral moment to cause cracking since it is already cracked
               Float64 m = fabs(im*sectionResult.Mg - Plift*results.Zo[impact]);
               Float64 theta_crack = (IsZero(m) ? 0.4 : mcr/m);
               theta_crack = ::ForceIntoRange(0.0,theta_crack,0.4);
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
         } // next wind direction
      } // next impact

#pragma Reminder("WORKING HERE - need to determine if there is adequate rebar at this section to use the higher tensile stress limit")

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure for all combinations of impact and wind
   for ( int impact = 0; impact < 3; impact++ )
   {
      for ( int wind = 0; wind < 2; wind++ )
      {
         Float64 windSign = (wind == LEFT ? 1 : -1);
         results.ThetaMax[impact][wind] = sqrt((results.EccLateralSweep[impact] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact])/(2.5*results.Zo[impact]));
         results.ThetaMax[impact][wind] = ::ForceIntoRange(0.0,results.ThetaMax[impact][wind],0.4);
         Float64 FSf = (results.Dra[impact]*results.ThetaMax[impact][wind])/((1+2.5*results.ThetaMax[impact][wind])*(results.Zo[impact]*results.ThetaMax[impact][wind] + windSign*results.ZoWind[impact] - windSign*results.EccWind[impact]) + results.EccLateralSweep[impact]);
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
   PoiIDType midSpanPoiID;
   CComPtr<IFem2dModel> model;
   Analyze(pGirder,pStabilityProblem,results,&model,&midSpanPoiID);

   results.vSectionResults.clear();
   results.vSectionResults.reserve(pStabilityProblem->GetAnalysisPoints().size());

   // we will be finding the minimum value for all analysis points considered
   // initialize to DBL_MAX
   results.MinFScr         =  DBL_MAX;
   results.MinFsFailure    =  DBL_MAX;
   results.MinFsRollover   =  DBL_MAX;
   results.MaxStress       = -DBL_MAX;
   results.MinStress       =  DBL_MAX;
   results.MaxDirectStress = -DBL_MAX;
   results.MinDirectStress =  DBL_MAX;

   Float64 Lg = pGirder->GetGirderLength();
   Float64 Wg = pGirder->GetGirderWeight();

   Float64 ImpactUp,ImpactDown;
   pStabilityProblem->GetImpact(&ImpactUp,&ImpactDown);
   Float64 IM[3] = {1.0, 1.0 - ImpactUp, 1.0 + ImpactDown};

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

   Float64 fr = pStabilityProblem->GetFr();

   Float64 SupportPlacementTolerance = pStabilityProblem->GetSupportPlacementTolerance();
   Float64 Ktheta = pStabilityProblem->GetTruckRotationalStiffness();
   Float64 Superelevation = pStabilityProblem->GetSuperelevation();
   Float64 Hrs = pStabilityProblem->GetHeightOfRollAxisAboveRoadway();
   Float64 Wcc = pStabilityProblem->GetWheelLineSpacing();

#pragma Reminder("WORKING HERE - assuming equal overhangs")
   Float64 l = results.Ls;
   Float64 a = (Lg-l)/2; // assuming equal overhangs

   // overturning moment due to wind and cf applied toward the left
   // Ywind and Dra are a function of impact because of impact forces in the horizontal
   // component of the lifting cable. Since this is a hauling case, such force effects
   // do not exist so we can just use the IMPACT_NONE case.
   results.MotWind = results.Wwind*results.Ywind[IMPACT_NONE];
   results.MotCF   = results.Wcf*results.Dra[IMPACT_NONE];
   for ( int impact = 0; impact < 3; impact++ )
   {
      Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);
   
      for ( int wind = 0; wind < 2; wind++ )
      {
         Float64 windSign = (wind == LEFT ? 1 : -1);

         for ( int cf = 0; cf < 2; cf++ )
         {
            Float64 cfSign = (cf == LEFT ? 1 : -1);

            Float64 Zt = windSign*results.ZoWind[impact] + cfSign*results.ZoCF;
            Float64 ei = results.EccLateralSweep[impact];
            Float64 Mot = windSign*results.MotWind + cfSign*results.MotCF;

            results.ThetaEq[impact][wind][cf] = (Ktheta*Superelevation + im*Wg*(Zt + ei) + Mot)/(Ktheta - im*Wg*(results.Zo[impact] + results.Dra[impact]));
         }
      }
   }

   PoiIDType poiID = 0;
   CComQIPtr<IFem2dModelResults> femResults(model);
   std::vector<Float64> vX = pStabilityProblem->GetAnalysisPoints();
   BOOST_FOREACH(Float64 X,vX)
   {
      stbHaulingSectionResult sectionResult;

      sectionResult.X = X;

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
      sectionResult.fps[TOP]    = 0;
      sectionResult.fps[BOTTOM] = 0;
      for ( int strandType = 0; strandType < 3; strandType++ )
      {
         Float64 Y = pGirder->GetStrandLocation(strandType,X);
         Float64 eps = Y - Yt; // eccentricity of strands (positive values means ps force is above CG)
         Float64 Fpe = pStabilityProblem->GetFpe(strandType,X);

         Float64 ft = -Fpe/Ag + Fpe*eps*Yt/Ix;
         Float64 fb = -Fpe/Ag + Fpe*eps*(Hg + Yt)/Ix;

         sectionResult.fps[TOP]    += ft;
         sectionResult.fps[BOTTOM] += fb;
      }

      // stress due to dead load
      sectionResult.fg[TOP]    = sectionResult.Mg*Yt/Ix;
      sectionResult.fg[BOTTOM] = sectionResult.Mg*(Hg + Yt)/Ix;

      // stress due to wind towards the left
      sectionResult.fw[TOP_LEFT]     =  sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[TOP_RIGHT]    = -sectionResult.Mw*Wtf/(2*Iy);
      sectionResult.fw[BOTTOM_LEFT]  =  sectionResult.Mw*Wbf/(2*Iy);
      sectionResult.fw[BOTTOM_RIGHT] = -sectionResult.Mw*Wbf/(2*Iy);

      // stress due to centrifugal the left
      sectionResult.fcf[TOP_LEFT]     =  sectionResult.Mcf*Wtf/(2*Iy);
      sectionResult.fcf[TOP_RIGHT]    = -sectionResult.Mcf*Wtf/(2*Iy);
      sectionResult.fcf[BOTTOM_LEFT]  =  sectionResult.Mcf*Wbf/(2*Iy);
      sectionResult.fcf[BOTTOM_RIGHT] = -sectionResult.Mcf*Wbf/(2*Iy);

      for ( int impact = 0; impact < 3; impact++ )
      {
         Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);
      
         for ( int wind = 0; wind < 2; wind++ )
         {
            Float64 windSign = (wind == LEFT ? 1 : -1);

            for ( int cf = 0; cf < 2; cf++ )
            {
               Float64 cfSign = (cf == LEFT ? 1 : -1);

               sectionResult.FScr[impact][wind][cf] = DBL_MAX;

               Float64 Zt = windSign*results.ZoWind[impact] + cfSign*results.ZoCF;
               Float64 ei = results.EccLateralSweep[impact];
               Float64 Mot = windSign*results.MotWind + cfSign*results.MotCF;

               for ( int corner = 0; corner < 4; corner++ )
               {
                  int face = (corner == TOP_LEFT || corner == TOP_RIGHT ? TOP : BOTTOM);
                  Float64 b = (face == TOP ? Wtf : Wbf);

                  Float64 cornerSign = (corner == TOP_LEFT || corner == BOTTOM_LEFT ? 1 : -1);

                  // stress due to direct loads (plumb girder)
                  sectionResult.fDirect[impact][wind][cf][corner] = sectionResult.fps[face] + IM[impact]*sectionResult.fg[face] + windSign*sectionResult.fw[corner] + cfSign*sectionResult.fcf[corner];

                  if ( ::IsLT(results.MaxDirectStress,sectionResult.fDirect[impact][wind][cf][corner]) )
                  {
                     results.MaxDirectStress = sectionResult.fDirect[impact][wind][cf][corner];
                     results.MaxDirectStressAnalysisPointIndex = (IndexType)poiID;
                     results.MaxDirectStressImpactDirection = impact;
                     results.MaxDirectStressWindDirection = wind;
                     results.MaxDirectStressCFDirection = cf;
                     results.MaxDirectStressCorner = corner;
                  }

                  if ( ::IsLT(sectionResult.fDirect[impact][wind][cf][corner],results.MinDirectStress) )
                  {
                     results.MinDirectStress = sectionResult.fDirect[impact][wind][cf][corner];
                     results.MinDirectStressAnalysisPointIndex = (IndexType)poiID;
                     results.MinDirectStressImpactDirection = impact;
                     results.MinDirectStressWindDirection = wind;
                     results.MinDirectStressCFDirection = cf;
                     results.MinDirectStressCorner = corner;
                  }

                  // stress due to lateral loads caused by the girder being tilted
                  sectionResult.fTilt[impact][wind][cf][corner] = cornerSign*(im*sectionResult.Mg*results.ThetaEq[impact][wind][cf])*b/(2*Iy);

                  // total stress
                  sectionResult.f[impact][wind][cf][corner] = sectionResult.fDirect[impact][wind][cf][corner] + sectionResult.fTilt[impact][wind][cf][corner];

                  if ( !pStabilityProblem->ApplyImpactToTiltedGirder() )
                  {
                     // the direct stress has impact applied to the girder self weight... we don't want this for the tilted girder, so remove it
                     sectionResult.f[impact][wind][cf][corner] += (im - IM[impact])*sectionResult.fg[face];
                  }

                  if ( ::IsLT(results.MaxStress,sectionResult.f[impact][wind][cf][corner]) )
                  {
                     results.MaxStress = sectionResult.f[impact][wind][cf][corner];
                     results.MaxStressAnalysisPointIndex = (IndexType)poiID;
                     results.MaxStressImpactDirection = impact;
                     results.MaxStressWindDirection = wind;
                     results.MaxStressCFDirection = cf;
                     results.MaxStressCorner = corner;
                  }

                  if ( ::IsLT(sectionResult.f[impact][wind][cf][corner],results.MinStress) )
                  {
                     results.MinStress = sectionResult.f[impact][wind][cf][corner];
                     results.MinStressAnalysisPointIndex = (IndexType)poiID;
                     results.MinStressImpactDirection = impact;
                     results.MinStressWindDirection = wind;
                     results.MinStressCFDirection = cf;
                     results.MinStressCorner = corner;
                  }

                  // compute cracking moment and cracking factor of safety
                  Float64 mcr = (fr - sectionResult.fDirect[impact][wind][cf][corner])*2*Iy/b;
                  if ( !pStabilityProblem->ApplyImpactToTiltedGirder() )
                  {
                     // the direct stress has impact applied to the girder self weight... we don't want this for the tilted girder, so remove it
                     mcr -= (im - IM[impact])*sectionResult.fg[face]*2*Iy/b;
                  }
                  mcr = Max(mcr,0.0); // if mcr is less than zero, the beam cracks even if it is not tilted... there isn't a lateral moment to cause cracking since it is already cracked
                  Float64 m = fabs(im*sectionResult.Mg);
                  Float64 theta_crack = (IsZero(m) ? 0.4 : mcr/m);
                  theta_crack = ::ForceIntoRange(0.0,theta_crack,0.4);
                  Float64 fscr = (Ktheta*(theta_crack - Superelevation))/(im*Wg*((results.Zo[impact] + results.Dra[impact])*theta_crack + Zt + ei) + Mot);
                  fscr = Max(fscr,0.0); // can't be less than zero... theta_crack-Superelevation < 0 means the superelevation alone will crack the girder

                  if ( ::IsLT(fscr,sectionResult.FScr[impact][wind][cf]) )
                  {
                     // capture governing condition and related parameters
                     sectionResult.CrackedFlange[impact][wind][cf] = corner;
                     sectionResult.Mcr[impact][wind][cf] = mcr;
                     sectionResult.ThetaCrack[impact][wind][cf] = theta_crack;
                     sectionResult.FScr[impact][wind][cf] = fscr;
                  }
               } // next corner

               // keep track of the minimum FScr for all analysis points
               if ( ::IsLT(sectionResult.FScr[impact][wind][cf],results.MinFScr) )
               {
                  results.FScrAnalysisPointIndex = (IndexType)poiID; // poiIDs exactly match the analysis point indicies
                  results.FScrImpactDirection = impact;
                  results.FScrWindDirection = wind;
                  results.FScrCFDirection = cf;
                  results.MinFScr = sectionResult.FScr[impact][wind][cf];
               }
            } // next cf
         } // next wind direction
      } // next impact

#pragma Reminder("WORKING HERE - need to determine if there is adequate rebar at this section to use the higher tensile stress limit")

      results.vSectionResults.push_back(sectionResult);
      poiID++;
   } // next analysis point

   // calculate the factor of safety against failure and roll over for all combinations of impact and wind
   for ( int impact = 0; impact < 3; impact++ )
   {
      Float64 im = (pStabilityProblem->ApplyImpactToTiltedGirder() ? IM[impact] : 1.0);

      for ( int wind = 0; wind < 2; wind++ )
      {
         Float64 windSign = (wind == LEFT ? 1 : -1);
         for ( int cf = 0; cf < 2; cf++ )
         {
            Float64 cfSign = (cf == LEFT ? 1 : -1);

            Float64 Zt = windSign*results.ZoWind[impact] + cfSign*results.ZoCF;
            Float64 ei = results.EccLateralSweep[impact];
            Float64 Mot = windSign*results.MotWind + cfSign*results.MotCF;

            // FS Failure

            // compute theta prime max... PCI examples use a numerical solver in mathcad
            // I've drived the closed form solution, similar to that for lifting, however it is
            // a cubic equation so a simple equation is difficult. We'll use the math cubic solver
            // to get our answer.
            // A derivation of the closed form equation is provided in the supporting documents folder
#pragma Reminder("WORKING HERE - graph FS(theta) and this equation to verify derivative and solutions"
            Float64 A = 2.5*results.Zo[impact]*im*Wg;
            Float64 B = im*Wg*(results.Dra[impact] - 4*results.Zo[impact]);
            Float64 C = im*Wg*(ei + Zt + results.Zo[impact]*(5*Superelevation - 1) - results.Dra[impact]) + Mot;
            Float64 D = im*Wg*(results.Zo[impact] + results.Dra[impact])*Superelevation;
            mathCubicSolver solver(A,B,C,D);
            Float64 t[3];
            int nRoots = solver.Solve(&t[0],&t[1],&t[2]);
            Float64 theta_max = (nRoots == 0 ? 0.4 : -DBL_MAX);
            for ( int i = 0; i < nRoots; i++ )
            {
               theta_max = Max(theta_max,t[i]);
            }
            theta_max = ::ForceIntoRange(0.0,theta_max,0.4);
            results.ThetaMax[impact][wind][cf] = theta_max;

            Float64 numerator = Ktheta*(theta_max - Superelevation);
            Float64 zo = results.Zo[impact]*(1.0 + 2.5*theta_max);
            Float64 denominator = im*Wg*((zo + results.Dra[impact])*theta_max + ei + Zt*(1 + 2.5*theta_max)) + Mot;
            Float64 FSf = numerator/denominator;
            results.FsFailure[impact][wind][cf] = FSf;

            if ( ::IsLT(results.FsFailure[impact][wind][cf],results.MinFsFailure) )
            {
               results.MinFsFailure = results.FsFailure[impact][wind][cf];
               results.FSfImpactDirection = impact;
               results.FSfWindDirection = wind;
               results.FSfCFDirection = cf;
            }

            // FS Rollover
            results.MroWind = results.Wwind*Hrs + results.MotWind;
            results.MroCF   = results.Wcf*Hrs   + results.MotCF;
            Float64 Mro = windSign*results.MroWind + cfSign*results.MroCF;

            Float64 theta_roll = (im*Wg*(Wcc/2 - Hrs*Superelevation - SupportPlacementTolerance) + Mro)/(Ktheta) + Superelevation;
            results.ThetaRollover[impact][wind][cf] = theta_roll;

            numerator = Ktheta*(theta_roll - Superelevation);
            zo = results.Zo[impact]*(1.0 + 2.5*theta_roll);
            denominator = im*Wg*((zo + results.Dra[impact])*theta_roll + ei + Zt*(1 + 2.5*theta_roll)) + Mro;
            Float64 FSr = numerator/denominator;
            results.FsRollover[impact][wind][cf] = FSr;

            if ( ::IsLT(results.FsRollover[impact][wind][cf],results.MinFsRollover) )
            {
               results.MinFsRollover = results.FsRollover[impact][wind][cf];
               results.FSroImpactDirection = impact;
               results.FSroWindDirection = wind;
               results.FSroCFDirection = cf;
            }
         } // next cf direction
      } // next wind direction
   } // next impact
}

void stbStabilityEngineer::BuildModel(const stbIGirder* pGirder,const stbIStabilityProblem* pStabilityProblem,stbResults& results,IFem2dModel** ppModel,PoiIDType* pMidSpanPoiID) const
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

   Float64 Ll, Lr;
   pStabilityProblem->GetSupportLocations(&Ll,&Lr);

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

   // eliminate duplicates
   std::sort(vX.begin(),vX.end());
   vX.erase(std::unique(vX.begin(),vX.end()),vX.end());

   // Layout joints
   JointIDType jntID = 0;
   JointIDType leftSupportJntID = INVALID_ID;
   JointIDType rightSupportJntID = INVALID_ID;
   CComPtr<IFem2dJointCollection> joints;
   (*ppModel)->get_Joints(&joints);
   BOOST_FOREACH(Float64 X,vX)
   {
      CComPtr<IFem2dJoint> jnt;
      joints->Create(jntID,X,0,&jnt);

      if ( IsEqual(X,leftSupportLoc) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtFx);
         jnt->ReleaseDof(jrtMz);
         leftSupportJntID = jntID;
      }
      else if ( IsEqual(X,rightSupportLoc) )
      {
         jnt->Support();
         jnt->ReleaseDof(jrtMz);
         rightSupportJntID = jntID;
      }

      jntID++;
   }

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
   Float64 density = pGirder->GetDensity();
   Float64 unitWeight = density*g;

   Float64 Ec = pStabilityProblem->GetEc();

   Float64 WindPressure = pStabilityProblem->GetWindPressure();

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
   Float64 prevA, Ix, Iy, Yt, prevHg, Wtf, Wbf;
   pGirder->GetSectionProperties(*prevIter,&prevA,&Ix,&Iy,&Yt,&prevHg,&Wtf,&Wbf);
   LoadIDType loadID = 0;
   results.Wcf = 0;
   results.Wwind = 0;
   for ( ; iter != end; iter++, prevIter++, jntID++, mbrID++, loadID++ )
   {
      Float64 prevX = *prevIter;
      Float64 currX = *iter;
      
      Float64 Ag,Hg;
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
      results.Wcf += (wStart + wEnd)*(currX - prevX);

      // Wind
      CComPtr<IFem2dDistributedLoad> windDistLoad;
      wStart = prevHg*WindPressure;
      wEnd   =     Hg*WindPressure;
      windDistributedLoads->Create(loadID,mbrID,loadDirFy,0.0,-1.0,-wStart,-wEnd,lotMember,&windDistLoad);

      // cummulate the total wind load
      // average wind load * distance = [(wStart+wEnd)/2]*(currX-prevX)
      // to save on doing the divide by 2 operation, we'll skip it here
      // and do it once after the this loop.
      results.Wwind += (wStart + wEnd)*(currX - prevX);

      prevA = Ag;
      prevHg = Hg;
   }

   // divide by 2 to get total wind load (see note above)
   results.Wwind /= 2;
   results.Wcf   /= 2;

   // Apply self weight point loads
   LoadIDType ptLoadID = 0;
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
   }

   // Apply point loads for due to lifting
   const stbILiftingStabilityProblem* pLiftingProblem = dynamic_cast<const stbILiftingStabilityProblem*>(pStabilityProblem);
   if ( pLiftingProblem )
   {
      // We don't know the horizontal component of the lift force here, so we will just use a unit force
      // and then scale the results later
      Float64 Ph = 1.0;

      Float64 Ag,Ix,Iy,Yt,Hg,Wtf,Wbf;
      pGirder->GetSectionProperties(leftSupportLoc,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);
      Float64 Mleft = -Ph*Yt;

      pGirder->GetSectionProperties(rightSupportLoc,&Ag,&Ix,&Iy,&Yt,&Hg,&Wtf,&Wbf);
      Float64 Mright = Ph*Yt;

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
   *pMidSpanPoiID = INVALID_ID;
   std::vector<Float64> vAnalysisPoints = pStabilityProblem->GetAnalysisPoints();
   BOOST_FOREACH(Float64 Xpoi,vAnalysisPoints)
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

            if ( IsEqual(Xpoi,Xms) )
            {
               *pMidSpanPoiID = poiID;
            }

            break;
         }

         Xprev = Xcurr;
      }

      CComPtr<IFem2dPOI> poi;
      pois->Create(poiID++,mbrID,Xmbr,&poi);
   }

   if (*pMidSpanPoiID == INVALID_ID) 
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

      CComPtr<IFem2dPOI> poi;
      pois->Create(poiID,mbrID,Xmbr,&poi);
      *pMidSpanPoiID = poiID++;
   }

   ATLASSERT(*pMidSpanPoiID != INVALID_ID);

   // Create special POI for computing Zo
   // Need several closely spaced POI for accurate results
   // plus need poi at support locations
   IndexType nPoi = 250; // this is the number of analysis points required to exactly match zo in PCI Examples
   // This could be reduced if we come up with a better numerical integration method
   m_vPoi.clear();
   for ( IndexType i = 0; i <= nPoi; i++ )
   {
      Float64 x = i*Lg/nPoi;
      m_vPoi.push_back(x);
   }
   m_vPoi.push_back(leftSupportLoc);
   m_vPoi.push_back(rightSupportLoc);
   std::sort(m_vPoi.begin(),m_vPoi.end());
   m_vPoi.erase(std::unique(m_vPoi.begin(),m_vPoi.end()),m_vPoi.end());
   m_FirstPoi = -2;
   poiID = m_FirstPoi;
   BOOST_FOREACH(Float64 Xpoi,m_vPoi)
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

Float64 stbStabilityEngineer::ComputeZo(const stbIGirder* pGirder,IFem2dModel* pModel) const
{
   ATLASSERT(m_FirstPoi - m_LastPoi + 1 == m_vPoi.size());
   CComQIPtr<IFem2dModelResults> femResults(pModel);
   Float64 g = unitSysUnitsMgr::GetGravitationalAcceleration();
   Float64 density = pGirder->GetDensity();
   Float64 unitWeight = density*g;
   PoiIDType poiID1 = m_FirstPoi;
   PoiIDType poiID2 = m_FirstPoi-1;
   std::vector<Float64>::const_iterator iter1(m_vPoi.begin());
   std::vector<Float64>::const_iterator iter2 = iter1+1;
   std::vector<Float64>::const_iterator end(m_vPoi.end());
   Float64 Zo = 0;
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

   Float64 Wg = pGirder->GetGirderWeight();
   Zo /= -Wg;

   return Zo;
}
