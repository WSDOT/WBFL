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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\StabilityProblem.h>
#include <set>

struct STABILITYCLASS stbFpe
{
   Float64 X;
   Float64 fpeStraight;
   Float64 YpsStraight;
   Float64 fpeHarped;
   Float64 YpsHarped;
   Float64 fpeTemporary;
   Float64 YpsTemporary;

   bool operator==(const stbFpe& other) const
   {
      if ( !IsEqual(X,other.X) )
         return false;

      if ( !IsEqual(fpeStraight,other.fpeStraight) )
         return false;

      if ( !IsEqual(YpsStraight,other.YpsStraight) )
         return false;

      if ( !IsEqual(fpeHarped,other.fpeHarped) )
         return false;

      if ( !IsEqual(YpsHarped,other.YpsHarped) )
         return false;

      if ( !IsEqual(fpeTemporary,other.fpeTemporary) )
         return false;

      if ( !IsEqual(YpsTemporary,other.YpsTemporary) )
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

   void SetSegment(ISegment* pSegment);
   virtual void GetSegment(ISegment** ppSegment) const override;

   void ClearSections();
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf);
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2);
   void AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf);
   void AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2);

   void ClearPointLoads();
   void AddPointLoad(Float64 X,Float64 P);

   IndexType GetSectionCount() const;
   Float64 GetSectionLength(IndexType sectIdx) const;
   void GetSectionProperties(IndexType sectIdx,stbTypes::Section section,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const;
   void GetSectionProperties(Float64 X,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const;

   Float64 GetGirderLength() const;
   Float64 GetStrandLocation(stbTypes::StrandType strandType,Float64 X) const;

   void SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads);
   std::vector<std::pair<Float64,Float64>> GetAdditionalLoads() const;

   virtual Float64 GetDragCoefficient() const;
   void SetDragCoefficient(Float64 Cd);

protected:
   ISegment* m_pSegment; // weak refernce
   std::vector<stbSectionProperties> m_vSectionProperties;

   std::vector<std::pair<Float64,Float64>> m_vPointLoads; // additional point loads (used for items precast with the girder such as internal diaphragms)
                                                        // first parameter is location from left end of girder, second parameter is the load magnitude. Positive loads are up

   Float64 m_DragCoefficient;

   void UpdateLength() const;
   mutable bool m_bLengthNeedsUpdate;
   mutable Float64 m_L;
};

class STABILITYCLASS stbStabilityProblemImp
{
public:
   stbStabilityProblemImp();
   stbStabilityProblemImp(const stbStabilityProblemImp& other);
   virtual ~stbStabilityProblemImp();

   stbStabilityProblemImp& operator=(const stbStabilityProblemImp& other);

   bool operator==(const stbStabilityProblemImp& other) const;
   bool operator!=(const stbStabilityProblemImp& other) const;

   // Effective prestress for can vary along the girder
   // Define Fpe for straight, harped, and temporary strands at differnet locations
   // along the girder. Fpe will be linerally interpolated between locations.
   // If Fpe is requested before the first or after the last defined point, the first/last values will be used
   // For constant Fpe, define a Fpe at a single location
   IndexType GetFpeCount() const;
   void ClearFpe();
   void AddFpe(Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp);
   void SetFpe(IndexType fpeIdx,Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp);
   void GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pYpsStraight,Float64* pFpeHarped,Float64* pYpsHarped,Float64* pFpeTemp,Float64* pYpsTemp) const;

   // Prestress transfer length... 
   // Linearly interpolates Fpe from zero at the ends of the girder to its full value
   // over this length
   bool AdjustForXferLength() const;
   void AdjustForXferLength(bool bAdjust);
   void SetXferLength(Float64 xferLength,Float64 Lg);
   Float64 GetXferLength() const;

   void SetCamber(bool bDirectCamber,Float64 camber);

   virtual const matConcreteEx& GetConcrete() const;
   virtual matConcreteEx& GetConcrete();
   void SetConcrete(const matConcreteEx& concrete);

   virtual Float64 GetRebarYieldStrength() const;
   void SetRebarYieldStrength(Float64 fy);

   void SetSupportLocations(Float64 Ll,Float64 Lr);
   void SetYRollAxis(Float64 Yra);
   void SetSweepTolerance(Float64 sweepTolerance);
   void SetSupportPlacementTolerance(Float64 spt);
   void SetImpact(Float64 up,Float64 down);

   virtual void GetFpe(stbTypes::StrandType strandType,Float64 X,Float64* pFpe,Float64* pYps) const;

   void GetCamber(bool* pbDirectCamber,Float64* pCamber) const;
   void SetCamberMultiplier(Float64 m);
   Float64 GetCamberMultiplier() const;

   Float64 GetEc() const;
   Float64 GetFr() const;

   void GetSupportLocations(Float64* pLeft,Float64* pRight) const;
   Float64 GetYRollAxis() const;
   
   Float64 GetSweepTolerance() const;
   Float64 GetSupportPlacementTolerance() const;

   void GetImpact(Float64* pIMup,Float64* pIMdown) const;

   virtual void GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const;
   void SetWindLoading(stbTypes::WindType type,Float64 load);

   void ClearAnalysisPoints();
   void AddAnalysisPoint(stbIAnalysisPoint* pAnalysisPoint);
   const std::vector<stbIAnalysisPoint*>& GetAnalysisPoints() const;
   virtual const stbIAnalysisPoint* GetAnalysisPoint(IndexType idx) const;

protected:
   void MakeCopy(const stbStabilityProblemImp& other);
   void MakeAssignment(const stbStabilityProblemImp& other);

   std::vector<stbIAnalysisPoint*> m_vAnalysisPoints; // locations where moments, stresses, etc. are computed
   bool CompareAnalysisPoints(const stbStabilityProblemImp& other) const;

   bool m_bAdjustForXferLength;
   Float64 m_XferLength;
   Float64 m_Lg; // length of girder

   std::set<stbFpe> m_vFpe;
   
   bool m_bDirectCamber; // if true, a camber value has been input, otherwise, camber is estimated by increasing the height from the CG to the roll center by a percentage
   Float64 m_Camber; // direct camber value if bDirectCamber is true, otherwise camber estimate parameter
   Float64 m_CamberMultiplier;

   matConcreteEx m_Concrete;

   Float64 m_fy;

   Float64 m_Ll; // location of left support, measured from the left end of the girder
   Float64 m_Lr; // location of right support, measured from the right end of the girder

   Float64 m_SweepTolerance;
   Float64 m_SupportPlacementTolerance;

   Float64 m_Yra; // location of the roll axis, measured from the top of the girder

   Float64 m_ImpactUp;
   Float64 m_ImpactDown;

   stbTypes::WindType m_WindLoadType;
   Float64 m_WindLoad; // velocity or pressure, depending on m_WindLoadType
};

class STABILITYCLASS stbLiftingStabilityProblem : public stbILiftingStabilityProblem
{
public:
   stbLiftingStabilityProblem();
   stbLiftingStabilityProblem(const stbLiftingStabilityProblem& other);
   virtual ~stbLiftingStabilityProblem();

   stbLiftingStabilityProblem& operator=(const stbLiftingStabilityProblem& other);
   bool operator==(const stbLiftingStabilityProblem& other) const;
   bool operator!=(const stbLiftingStabilityProblem& other) const;

   IndexType GetFpeCount() { return m_Imp.GetFpeCount(); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(Float64 X, Float64 FpeStraight, Float64 YpsStraight, Float64 FpeHarped, Float64 YpsHarped, Float64 FpeTemp, Float64 YpsTemp) { m_Imp.AddFpe(X, FpeStraight, YpsStraight, FpeHarped, YpsHarped, FpeTemp, YpsTemp); }
   void GetFpe(IndexType fpeIdx, Float64* pX, Float64* pFpeStraight, Float64* pYpsStraight, Float64* pFpeHarped, Float64* pYpsHarped, Float64* pFpeTemp, Float64* pYpsTemp) const { return m_Imp.GetFpe(fpeIdx, pX, pFpeStraight, pYpsStraight, pFpeHarped, pYpsHarped, pFpeTemp, pYpsTemp); }
   void SetFpe(IndexType fpeIdx, Float64 X, Float64 FpeStraight, Float64 YpsStraight, Float64 FpeHarped, Float64 YpsHarped, Float64 FpeTemp, Float64 YpsTemp) { return m_Imp.SetFpe(fpeIdx, X, FpeStraight, YpsStraight, FpeHarped, YpsHarped, FpeTemp, YpsTemp); }

   bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
   void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }
   void SetXferLength(Float64 xferLength, Float64 Lg) { m_Imp.SetXferLength(xferLength, Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

   void SetCamber(bool bDirectCamber, Float64 camber) { m_Imp.SetCamber(bDirectCamber, camber); }
   void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
   Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

   void SetConcrete(const matConcreteEx& concrete) { m_Imp.SetConcrete(concrete); }
   const matConcreteEx& GetConcrete() const { return m_Imp.GetConcrete(); }
   matConcreteEx& GetConcrete() { return m_Imp.GetConcrete(); }

   virtual Float64 GetRebarYieldStrength() const override { return m_Imp.GetRebarYieldStrength(); }
   void SetRebarYieldStrength(Float64 fy) {m_Imp.SetRebarYieldStrength(fy); }

   void SetSupportLocations(Float64 Ll,Float64 Lr) { m_Imp.SetSupportLocations(Ll,Lr); }
   void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }
   void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance);  }
   void SetSupportPlacementTolerance(Float64 spt)  {  m_Imp.SetSupportPlacementTolerance(spt); }
   void SetImpact(Float64 up,Float64 down)  { m_Imp.SetImpact(up,down);   }
   virtual void GetFpe(stbTypes::StrandType strandType,Float64 X,Float64* pFpe,Float64* pYps) const  override { m_Imp.GetFpe(strandType,X,pFpe,pYps); }
   virtual void GetCamber(bool* pbDirectCamber,Float64* pCamber) const  override {  return m_Imp.GetCamber(pbDirectCamber,pCamber);   }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const  override { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const  override { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const  override { return m_Imp.GetSupportPlacementTolerance(); }
   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const  override { m_Imp.GetImpact(pIMup,pIMdown); }

   virtual void GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const  override { m_Imp.GetWindLoading(pType,pLoad); }
   void SetWindLoading(stbTypes::WindType type,Float64 load) { m_Imp.SetWindLoading(type,load); }

   void SetLiftAngle(Float64 liftAngle);
   virtual Float64 GetLiftAngle() const override;

   void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }
   void AddAnalysisPoint(stbIAnalysisPoint* pAnalysisPoint) { m_Imp.AddAnalysisPoint(pAnalysisPoint); }
   virtual std::vector<stbIAnalysisPoint*> GetAnalysisPoints() const  override { return m_Imp.GetAnalysisPoints(); }
   virtual const stbIAnalysisPoint* GetAnalysisPoint(IndexType idx) const  override { return m_Imp.GetAnalysisPoint(idx); }

   void EvaluateStressesAtEquilibriumAngle(bool bStressesAtEquilibrium) { m_bComputeStressesAtEquilibriumAngle = bStressesAtEquilibrium; }
   virtual bool EvaluateStressesAtEquilibriumAngle() const override { return m_bComputeStressesAtEquilibriumAngle; }

protected:
   void MakeCopy(const stbLiftingStabilityProblem& other);
   void MakeAssignment(const stbLiftingStabilityProblem& other);

   stbStabilityProblemImp m_Imp;
   Float64 m_LiftAngle;

   bool m_bComputeStressesAtEquilibriumAngle;
};

class STABILITYCLASS stbHaulingStabilityProblem :  public stbIHaulingStabilityProblem
{
public:
   stbHaulingStabilityProblem();
   stbHaulingStabilityProblem(const stbHaulingStabilityProblem& other);
   virtual ~stbHaulingStabilityProblem();

   stbHaulingStabilityProblem& operator=(const stbHaulingStabilityProblem& other);
   bool operator==(const stbHaulingStabilityProblem& other) const;
   bool operator!=(const stbHaulingStabilityProblem& other) const;

   IndexType GetFpeCount() { return m_Imp.GetFpeCount(); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp) { m_Imp.AddFpe(X,FpeStraight,YpsStraight,FpeHarped,YpsHarped,FpeTemp,YpsTemp); }
   void GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pYpsStraight,Float64* pFpeHarped,Float64* pYpsHarped,Float64* pFpeTemp,Float64* pYpsTemp) const { return m_Imp.GetFpe(fpeIdx,pX,pFpeStraight,pYpsStraight,pFpeHarped,pYpsHarped,pFpeTemp,pYpsTemp); }
   void SetFpe(IndexType fpeIdx,Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp) { return m_Imp.SetFpe(fpeIdx,X,FpeStraight,YpsStraight,FpeHarped,YpsHarped,FpeTemp,YpsTemp); }

   bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
   void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }
   void SetXferLength(Float64 xferLength,Float64 Lg) { m_Imp.SetXferLength(xferLength,Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

   void SetCamber(bool bDirectCamber,Float64 camber) { m_Imp.SetCamber(bDirectCamber,camber); }
   void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
   Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

   void SetConcrete(const matConcreteEx& concrete) { m_Imp.SetConcrete(concrete); }
   const matConcreteEx& GetConcrete() const { return m_Imp.GetConcrete(); }
   matConcreteEx& GetConcrete() { return m_Imp.GetConcrete(); }

   virtual Float64 GetRebarYieldStrength() const  override { return m_Imp.GetRebarYieldStrength(); }
   void SetRebarYieldStrength(Float64 fy) {m_Imp.SetRebarYieldStrength(fy); }

   void SetSupportLocations(Float64 Ll,Float64 Lr) { m_Imp.SetSupportLocations(Ll,Lr); }
   void SetYRollAxis(Float64 Yra) { m_Imp.SetYRollAxis(Yra); }
   void SetSweepTolerance(Float64 sweepTolerance) { m_Imp.SetSweepTolerance(sweepTolerance);  }
   void SetSupportPlacementTolerance(Float64 spt)  {  m_Imp.SetSupportPlacementTolerance(spt); }
   void SetImpact(Float64 up,Float64 down)  { m_Imp.SetImpact(up,down);   }
   virtual void GetFpe(stbTypes::StrandType strandType,Float64 X,Float64* pFpe,Float64* pYps) const  override { m_Imp.GetFpe(strandType,X,pFpe,pYps); }
   virtual void GetCamber(bool* pbDirectCamber,Float64* pCamber) const  override {   return m_Imp.GetCamber(pbDirectCamber,pCamber);   }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const override { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const override { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const override { return m_Imp.GetSupportPlacementTolerance(); }

   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const override { m_Imp.GetImpact(pIMup,pIMdown); }

   void SetImpactUsage(stbTypes::HaulingImpact impactUsage);
   virtual stbTypes::HaulingImpact GetImpactUsage() const override;

   virtual void GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const override { m_Imp.GetWindLoading(pType,pLoad); }
   void SetWindLoading(stbTypes::WindType type,Float64 load) { m_Imp.SetWindLoading(type,load); }

   void SetTruckRotationalStiffness(Float64 Ktheta);
   virtual Float64 GetTruckRotationalStiffness() const override;

   void SetWheelLineSpacing(Float64 Wcc);
   virtual Float64 GetWheelLineSpacing() const override;

   void SetHeightOfRollAxisAboveRoadway(Float64 Drs);
   virtual Float64 GetHeightOfRollAxisAboveRoadway() const override;

   void SetCrownSlope(Float64 crown);
   virtual Float64 GetCrownSlope() const override;

   void SetSuperelevation(Float64 superelevation);
   virtual Float64 GetSuperelevation() const override;

   void SetVelocity(Float64 velocity);
   virtual Float64 GetVelocity() const override;

   void SetTurningRadius(Float64 r);
   virtual Float64 GetTurningRadius() const override;

   void SetCentrifugalForceType(stbTypes::CFType cfType);
   virtual stbTypes::CFType GetCentrifugalForceType() const override;

   void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }
   void AddAnalysisPoint(stbIAnalysisPoint* pAnalysisPoint) { m_Imp.AddAnalysisPoint(pAnalysisPoint); }
   virtual std::vector<stbIAnalysisPoint*> GetAnalysisPoints() const  { return m_Imp.GetAnalysisPoints(); }
   virtual const stbIAnalysisPoint* GetAnalysisPoint(IndexType idx) const override { return m_Imp.GetAnalysisPoint(idx); }

   void EvaluateStressesAtEquilibriumAngle(stbTypes::HaulingSlope slope,bool bStressesAtEquilibrium) { m_bComputeStressesAtEquilibriumAngle[slope] = bStressesAtEquilibrium; }
   virtual bool EvaluateStressesAtEquilibriumAngle(stbTypes::HaulingSlope slope) const override { return m_bComputeStressesAtEquilibriumAngle[slope]; }

protected:
   void MakeCopy(const stbHaulingStabilityProblem& other);
   void MakeAssignment(const stbHaulingStabilityProblem& other);

   stbStabilityProblemImp m_Imp;

   stbTypes::HaulingImpact m_ImpactUsage;

   Float64 m_Ktheta; // Truck rotational stiffness
   Float64 m_Wcc; // center-center spacing between truck wheels
   Float64 m_Hrc; // height of roll axis above roadway
   Float64 m_CrownSlope; // normal crown slope
   Float64 m_Superelevation; // maximum superelevation rate
   
   Float64 m_Velocity;
   Float64 m_Radius;
   stbTypes::CFType m_CFType;

   bool m_bComputeStressesAtEquilibriumAngle[2];
};