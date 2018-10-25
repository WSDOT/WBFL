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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\StabilityProblem.h>
#include <set>

#define LOCATION_START    0
#define LOCATION_LEFT_HP  1
#define LOCATION_RIGHT_HP 2
#define LOCATION_END      3

struct STABILITYCLASS stbFpe
{
   Float64 X;
   Float64 fpeStraight;
   Float64 fpeHarped;
   Float64 fpeTemporary;

   bool operator==(const stbFpe& other) const
   {
      if ( !IsEqual(X,other.X) )
         return false;

      if ( !IsEqual(fpeStraight,other.fpeStraight) )
         return false;

      if ( !IsEqual(fpeHarped,other.fpeHarped) )
         return false;

      if ( !IsEqual(fpeTemporary,other.fpeTemporary) )
         return false;

      return true;
   }
};

bool STABILITYFUNC operator<(const stbFpe& a,const stbFpe& b);


class STABILITYCLASS stbSectionProperties
{
public:
   Float64 Ag[2]; // area of girder
   Float64 Ix[2]; // strong axis moment of inertia
   Float64 Iy[2]; // weak axis moment of inertia
   Float64 Yt[2]; // centroid from top of girder
   Float64 Hg[2];
   Float64 Wtf[2];
   Float64 Wbf[2];
   Float64 L; // distance over which these properties apply

   bool operator==(const stbSectionProperties& other) const
   {
      if ( !IsEqual(L,other.L) )
         return false;
     
      for ( int i = 0; i < 2; i++ )
      {
         if ( !IsEqual(Ag[i],other.Ag[i]) )
            return false;

         if ( !IsEqual(Ix[i],other.Ix[i]) )
            return false;

         if ( !IsEqual(Iy[i],other.Iy[i]) )
            return false;

         if ( !IsEqual(Yt[i],other.Yt[i]) )
            return false;

         if ( !IsEqual(Hg[i],other.Hg[i]) )
            return false;

         if ( !IsEqual(Wtf[i],other.Wtf[i]) )
            return false;

         if ( !IsEqual(Wbf[i],other.Wbf[i]) )
            return false;
      }

      return true;
   }
};

class STABILITYCLASS stbGirder : public stbIGirder
{
public:
   stbGirder();
   virtual ~stbGirder();

   bool operator==(const stbGirder& other) const;
   bool operator!=(const stbGirder& other) const;

   void ClearSections();
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf);
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2);
   void AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf);
   void AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2);
   void SetStraightStrandLocation(Float64 Yps);
   void SetTemporaryStrandLocation(Float64 Yps);
   void SetHarpedStrandLocation(Float64 X1,Float64 Y1,Float64 X2,Float64 Y2,Float64 X3,Float64 Y3,Float64 X4,Float64 Y4);
   Float64 GetStraightStrandLocation() const;
   Float64 GetTemporaryStrandLocation() const;
   void GetHarpedStrandLocation(Float64* pX1,Float64* pY1,Float64* pX2,Float64* pY2,Float64* pX3,Float64* pY3,Float64* pX4,Float64* pY4);
   void SetDensity(Float64 density);
   void ClearPointLoads();
   void AddPointLoad(Float64 X,Float64 P);

   IndexType GetSectionCount() const;
   Float64 GetSectionLength(IndexType sectIdx) const;
   void GetSectionProperties(IndexType sectIdx,int face,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const;
   void GetSectionProperties(Float64 X,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const;

   Float64 GetGirderLength() const;
   Float64 GetGirderWeight() const;
   Float64 GetStrandLocation(int strandType,Float64 X) const;
   Float64 GetDensity() const;

   void SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads);
   std::vector<std::pair<Float64,Float64>> GetAdditionalLoads() const;

protected:
   std::vector<stbSectionProperties> m_vSectionProperties;

   Float64 m_Density; // density of concrete including allowance for reinforcement

   std::vector<std::pair<Float64,Float64>> m_vPointLoads; // additional point loads (used for items precast with the girder such as internal diaphragms)
                                                        // first parameter is location from left end of girder, second parameter is the load magnitude. Positive loads are up

   // Prestressing configuration
   Float64 m_Ystraight;
   Float64 m_Yharp[4]; // location of harp strands, measured from top of girder (use LOCATION_xxx constants to access array)
   Float64 m_Xharp[4]; // location of angle points in harp strands, measured along girder (use LOCATION_xxx constants to access array)
   Float64 m_Ytemp; // location of temporary strands, measured from top of girder

   void Update() const;
   mutable bool m_bNeedsUpdate;
   mutable Float64 m_L;
   mutable Float64 m_Wg;
};

class STABILITYCLASS stbStabilityProblemImp
{
public:
   stbStabilityProblemImp();
   virtual ~stbStabilityProblemImp();

   bool operator==(const stbStabilityProblemImp& other) const;
   bool operator!=(const stbStabilityProblemImp& other) const;

   // Effective prestress for can vary along the girder
   // Define Fpe for straight, harped, and temporary strands at differnet locations
   // along the girder. Fpe will be linerally interpolated between locations.
   // If Fpe is requested before the first or after the last defined point, the first/last values will be used
   // For constant Fpe, define a Fpe at a single location
   IndexType GetFpeCount() const;
   void ClearFpe();
   void AddFpe(Float64 X,Float64 FpeStraight,Float64 FpeHarped,Float64 FpeTemp);
   void GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pFpeHarped,Float64* pFpeTemp) const;

   // Prestress transfer length... only used for constant Fpe
   // Linearly interpolates Fpe from zero at the ends of the girder to its full value
   // over this length
   void SetXferLength(Float64 xferLength,Float64 Lg);
   Float64 GetXferLength() const;

   void SetCamber(bool bDirectCamber,Float64 camber);

   void SetFc(Float64 fc);
   Float64 GetFc() const;

   void SetEc(Float64 ec);
   void SetFr(Float64 fr);
   void SetSupportLocations(Float64 Ll,Float64 Lr);
   void SetYRollAxis(Float64 Yra);
   void SetSweepTolerance(Float64 sweepTolerance);
   void SetSupportPlacementTolerance(Float64 spt);
   void SetImpact(Float64 up,Float64 down);
   void SetWindPressure(Float64 wp);

   Float64 GetFpe(int strandType,Float64 X) const;

   void GetCamber(bool* pbDirectCamber,Float64* pCamber) const;

   Float64 GetEc() const;
   Float64 GetFr() const;

   void GetSupportLocations(Float64* pLeft,Float64* pRight) const;
   Float64 GetYRollAxis() const;
   
   Float64 GetSweepTolerance() const;
   Float64 GetSupportPlacementTolerance() const;

   void GetImpact(Float64* pIMup,Float64* pIMdown) const;

   void ApplyImpactToTiltedGirder(bool bApplyImpact);
   virtual bool ApplyImpactToTiltedGirder() const;

   Float64 GetWindPressure() const;

   void ClearAnalysisPoints();
   void AddAnalysisPoint(Float64 X);
   const std::vector<Float64>& GetAnalysisPoints() const;

protected:
   std::vector<Float64> m_vAnalysisPoints; // locations where moments, stresses, etc. are computed

   Float64 m_XferLength;
   Float64 m_Lg; // length of girder

   std::set<stbFpe> m_vFpe;
   
   bool m_bDirectCamber; // if true, a camber value has been input, otherwise, camber is estimated by increasing the height from the CG to the roll center by a percentage
   Float64 m_Camber; // direct camber value if bDirectCamber is true, otherwise camber estimate parameter

   Float64 m_fc; // concrete strength
   Float64 m_fr; // modulus of rupture
   Float64 m_Ec; // modulus of elasticity (computed using AASHTO equations)

   Float64 m_Ll; // location of left support, measured from the left end of the girder
   Float64 m_Lr; // location of right support, measured from the right end of the girder

   Float64 m_SweepTolerance;
   Float64 m_SupportPlacementTolerance;

   Float64 m_Yra; // location of the roll axis, measured from the top of the girder

   Float64 m_ImpactUp;
   Float64 m_ImpactDown;

   bool m_bApplyImpactToTiltedGirder;

   Float64 m_WindPressure;
};

class STABILITYCLASS stbLiftingStabilityProblem : public stbILiftingStabilityProblem
{
public:
   stbLiftingStabilityProblem();
   virtual ~stbLiftingStabilityProblem();

   bool operator==(const stbLiftingStabilityProblem& other) const;
   bool operator!=(const stbLiftingStabilityProblem& other) const;

   IndexType GetFpeCount() { return m_Imp.GetFpeCount(); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(Float64 X,Float64 FpeStraight,Float64 FpeHarped,Float64 FpeTemp) { m_Imp.AddFpe(X,FpeStraight,FpeHarped,FpeTemp); }
   void GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pFpeHarped,Float64* pFpeTemp) const { return m_Imp.GetFpe(fpeIdx,pX,pFpeStraight,pFpeHarped,pFpeTemp); }
   void SetXferLength(Float64 xferLength,Float64 Lg) { m_Imp.SetXferLength(xferLength,Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }
   void SetCamber(bool bDirectCamber,Float64 camber) { m_Imp.SetCamber(bDirectCamber,camber); }
   
   void SetFc(Float64 fc) { m_Imp.SetFc(fc); }
   Float64 GetFc() const { return m_Imp.GetFc(); }

   void SetEc(Float64 ec) { m_Imp.SetEc(ec); }
   void SetFr(Float64 fr) { m_Imp.SetFr(fr); }
   void SetSupportLocations(Float64 Ll,Float64 Lr) { m_Imp.SetSupportLocations(Ll,Lr); }
   void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }
   void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance);  }
   void SetSupportPlacementTolerance(Float64 spt)  {  m_Imp.SetSupportPlacementTolerance(spt); }
   void SetImpact(Float64 up,Float64 down)  { m_Imp.SetImpact(up,down);   }
   void SetWindPressure(Float64 wp)  { m_Imp.SetWindPressure(wp);  }
   virtual Float64 GetFpe(int strandType,Float64 X) const { return m_Imp.GetFpe(strandType,X); }
   virtual void GetCamber(bool* pbDirectCamber,Float64* pCamber) const  {  return m_Imp.GetCamber(pbDirectCamber,pCamber);   }
   virtual Float64 GetEc() const { return m_Imp.GetEc(); }
   virtual Float64 GetFr() const { return m_Imp.GetFr(); }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const { return m_Imp.GetSupportPlacementTolerance(); }
   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const { m_Imp.GetImpact(pIMup,pIMdown); }
   void ApplyImpactToTiltedGirder(bool bApplyImpact) { m_Imp.ApplyImpactToTiltedGirder(bApplyImpact); }
   virtual bool ApplyImpactToTiltedGirder() const { return m_Imp.ApplyImpactToTiltedGirder(); }
   virtual Float64 GetWindPressure() const { return m_Imp.GetWindPressure(); }

   void SetLiftAngle(Float64 liftAngle);
   virtual Float64 GetLiftAngle() const;

   void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }
   void AddAnalysisPoint(Float64 X) { m_Imp.AddAnalysisPoint(X); }
   virtual std::vector<Float64> GetAnalysisPoints() const { return m_Imp.GetAnalysisPoints(); }


protected:
   stbStabilityProblemImp m_Imp;
   Float64 m_LiftAngle;
};

class STABILITYCLASS stbHaulingStabilityProblem :  public stbIHaulingStabilityProblem
{
public:
   stbHaulingStabilityProblem();
   virtual ~stbHaulingStabilityProblem();

   bool operator==(const stbHaulingStabilityProblem& other) const;
   bool operator!=(const stbHaulingStabilityProblem& other) const;

   IndexType GetFpeCount() { return m_Imp.GetFpeCount(); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(Float64 X,Float64 FpeStraight,Float64 FpeHarped,Float64 FpeTemp) { m_Imp.AddFpe(X,FpeStraight,FpeHarped,FpeTemp); }
   void GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pFpeHarped,Float64* pFpeTemp) const { return m_Imp.GetFpe(fpeIdx,pX,pFpeStraight,pFpeHarped,pFpeTemp); }
   void SetXferLength(Float64 xferLength,Float64 Lg) { m_Imp.SetXferLength(xferLength,Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }
   void SetCamber(bool bDirectCamber,Float64 camber) { m_Imp.SetCamber(bDirectCamber,camber); }
   void SetFc(Float64 fc) { m_Imp.SetFc(fc); }
   Float64 GetFc() const { return m_Imp.GetFc(); }
   void SetEc(Float64 ec) { m_Imp.SetEc(ec); }
   void SetFr(Float64 fr) { m_Imp.SetFr(fr); }
   void SetSupportLocations(Float64 Ll,Float64 Lr) { m_Imp.SetSupportLocations(Ll,Lr); }
   void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }
   void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance);  }
   void SetSupportPlacementTolerance(Float64 spt)  {  m_Imp.SetSupportPlacementTolerance(spt); }
   void SetImpact(Float64 up,Float64 down)  { m_Imp.SetImpact(up,down);   }
   void SetWindPressure(Float64 wp)  { m_Imp.SetWindPressure(wp);  }
   virtual Float64 GetFpe(int strandType,Float64 X) const { return m_Imp.GetFpe(strandType,X); }
   virtual void GetCamber(bool* pbDirectCamber,Float64* pCamber) const  {   return m_Imp.GetCamber(pbDirectCamber,pCamber);   }
   virtual Float64 GetEc() const { return m_Imp.GetEc(); }
   virtual Float64 GetFr() const { return m_Imp.GetFr(); }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const { return m_Imp.GetSupportPlacementTolerance(); }

   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const { m_Imp.GetImpact(pIMup,pIMdown); }

   void ApplyImpactToTiltedGirder(bool bApplyImpact) { m_Imp.ApplyImpactToTiltedGirder(bApplyImpact); }
   virtual bool ApplyImpactToTiltedGirder() const { return m_Imp.ApplyImpactToTiltedGirder(); }

   virtual Float64 GetWindPressure() const { return m_Imp.GetWindPressure(); }

   void SetTruckRotationalStiffness(Float64 Ktheta);
   virtual Float64 GetTruckRotationalStiffness() const;

   void SetWheelLineSpacing(Float64 Wcc);
   virtual Float64 GetWheelLineSpacing() const;

   void SetHeightOfRollAxisAboveRoadway(Float64 Drs);
   virtual Float64 GetHeightOfRollAxisAboveRoadway() const;

   void SetSuperelevation(Float64 superelevation);
   virtual Float64 GetSuperelevation() const;

   void SetVelocity(Float64 velocity);
   virtual Float64 GetVelocity() const;

   void SetTurningRadius(Float64 r);
   virtual Float64 GetTurningRadius() const;

   void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }
   void AddAnalysisPoint(Float64 X) { m_Imp.AddAnalysisPoint(X); }
   virtual std::vector<Float64> GetAnalysisPoints() const { return m_Imp.GetAnalysisPoints(); }

protected:
   stbStabilityProblemImp m_Imp;

   Float64 m_Ktheta; // Truck rotational stiffness
   Float64 m_Wcc; // center-center spacing between truck wheels
   Float64 m_Hrc; // height of roll axis above roadway
   Float64 m_Superelevation; // maximum superelevation rate
   
   Float64 m_Velocity;
   Float64 m_Radius;
};