///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <array>
#include <GeometricPrimitives\GeometricPrimitives.h>

struct STABILITYCLASS stbFpe
{
   Float64 X;
   Float64 fpe;
   Float64 Xps;
   Float64 Yps;

   bool operator==(const stbFpe& other) const
   {
      if ( !IsEqual(X,other.X) )
         return false;

      if ( !IsEqual(fpe,other.fpe) )
         return false;

      if (!IsEqual(Xps, other.Xps))
         return false;

      if (!IsEqual(Yps, other.Yps))
         return false;

      return true;
   }
};

bool STABILITYFUNC operator<(const stbFpe& a,const stbFpe& b);

struct STABILITYCLASS stbStressPoints
{
   std::array<gpPoint2d, 2> pntTL;
   std::array<gpPoint2d, 2> pntTR;
   std::array<gpPoint2d, 2> pntBL;
   std::array<gpPoint2d, 2> pntBR;

   bool operator==(const stbStressPoints& other) const
   {
      for (int i = 0; i < 2; i++)
      {
         if (pntTL[i] != other.pntTL[i])
         {
            return false;
         }

         if (pntTR[i] != other.pntTR[i])
         {
            return false;
         }

         if (pntBL[i] != other.pntBL[i])
         {
            return false;
         }

         if (pntBR[i] != other.pntBR[i])
         {
            return false;
         }
      }
      return true;
   }

   bool operator!=(const stbStressPoints& other) const
   {
      return !operator==(other);
   }
};

struct STABILITYCLASS stbSectionProperties
{
   std::array<Float64, 2> Ag; // area of girder
   std::array<Float64, 2> Ixx; // strong axis moment of inertia
   std::array<Float64, 2> Iyy; // weak axis moment of inertia
   std::array<Float64, 2> Ixy;
   std::array<Float64, 2> Ytop; // center of mass (centroid) from top of girder
   std::array<Float64, 2> Xleft; // center of mass from roll center
   std::array<Float64, 2> Hg;
   std::array<Float64, 2> Wtf;
   std::array<Float64, 2> Wbf;
   Float64 L; // distance over which these properties apply

   std::shared_ptr<stbStressPoints> m_pStressPoints;

   bool operator==(const stbSectionProperties& other) const
   {
      if ( !IsEqual(L,other.L) )
         return false;
     
      for ( int i = 0; i < 2; i++ )
      {
         if ( !IsEqual(Ag[i],other.Ag[i]) )
            return false;

         if ( !IsEqual(Ixx[i],other.Ixx[i]) )
            return false;

         if (!IsEqual(Iyy[i], other.Iyy[i]))
            return false;

         if (!IsEqual(Ixy[i], other.Ixy[i]))
            return false;

         if (!IsEqual(Ytop[i], other.Ytop[i]))
            return false;

         if (!IsEqual(Xleft[i], other.Xleft[i]))
            return false;

         if ( !IsEqual(Hg[i],other.Hg[i]) )
            return false;

         if ( !IsEqual(Wtf[i],other.Wtf[i]) )
            return false;

         if ( !IsEqual(Wbf[i],other.Wbf[i]) )
            return false;
      }

      if ((m_pStressPoints == nullptr && other.m_pStressPoints != nullptr) ||
         (m_pStressPoints != nullptr && other.m_pStressPoints == nullptr))
      {
         return false;
      }
      else if (m_pStressPoints != nullptr)
      {
         if (*m_pStressPoints != *other.m_pStressPoints)
         {
            return false;
         }
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

   void ClearSections(); // clears sections and stress points

   // Adds a new section to the girder. Returns the section index. 
   IndexType AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf);
   IndexType AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf, Float64 Ag2, Float64 Ixx2, Float64 Iyy2, Float64 Ixy2, Float64 Xcg2, Float64 Ycg2, Float64 Hg2, Float64 Wtf2, Float64 Wbf2);

   // Change the section properties for a section 
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy,Float64 Xleft,Float64 Ytop,Float64 Hg,Float64 Wtf,Float64 Wbf);
   void SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy, Float64 Xleft,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ixx2,Float64 Iyy2, Float64 Ixy2,Float64 Xcg2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2);

   // Assigns stress point values to a section. 
   void SetStressPoints(IndexType sectIdx, const gpPoint2d& pntTL, const gpPoint2d& pntTR, const gpPoint2d& pntBL, const gpPoint2d& pntBR);
   void SetStressPoints(IndexType sectIdx, const gpPoint2d& pntTL, const gpPoint2d& pntTR, const gpPoint2d& pntBL, const gpPoint2d& pntBR, const gpPoint2d& pntTL2, const gpPoint2d& pntTR2, const gpPoint2d& pntBL2, const gpPoint2d& pntBR2);

   void ClearPointLoads();
   void AddPointLoad(Float64 X,Float64 P);

   virtual IndexType GetSectionCount() const override;
   virtual Float64 GetSectionLength(IndexType sectIdx) const override;
   virtual void GetSectionProperties(IndexType sectIdx,stbTypes::Section section,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const override;
   virtual void GetSectionProperties(Float64 X,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const override;
   virtual void GetStressPoints(IndexType sectIdx, stbTypes::Section section, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const override;
   virtual void GetStressPoints(Float64 X, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const override;

   virtual Float64 GetGirderLength() const override;

   void SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads);
   virtual std::vector<std::pair<Float64,Float64>> GetAdditionalLoads() const override;

   virtual Float64 GetDragCoefficient() const override;
   void SetDragCoefficient(Float64 Cd);

   virtual Float64 GetPrecamber() const override;
   void SetPrecamber(Float64 precamber);

protected:
   ISegment* m_pSegment; // weak refernce
   std::vector<stbSectionProperties> m_vSectionProperties;

   std::vector<std::pair<Float64,Float64>> m_vPointLoads; // additional point loads (used for items precast with the girder such as internal diaphragms)
                                                        // first parameter is location from left end of girder, second parameter is the load magnitude. Positive loads are up

   Float64 m_DragCoefficient;

   Float64 m_Precamber;

   void GetStressPoints(const stbSectionProperties& props, stbTypes::Section section, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const;
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
   // Define Fpe at different locations along the girder. Fpe will be linerally interpolated between locations.
   // If Fpe is requested before the first or after the last defined point, the first/last values will be used
   // For constant Fpe, define a Fpe at a single location
   std::vector<LPCTSTR> GetPrestressNames() const;
   IndexType GetFpeCount(LPCTSTR strName) const;
   void ClearFpe();
   void AddFpe(LPCTSTR strName,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps);
   bool SetFpe(LPCTSTR strName,IndexType fpeIdx,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps); // returns false if strName is invalid
   bool GetFpe(LPCTSTR strName,IndexType fpeIdx,Float64* pX,Float64* pFpe,Float64* pXps,Float64* pYps) const;// returns false if strName is invalid

   // Prestress transfer length... 
   // Linearly interpolates Fpe from zero at the ends of the girder to its full value
   // over this length
   bool AdjustForXferLength() const;
   void AdjustForXferLength(bool bAdjust);
   void SetXferLength(Float64 xferLength,Float64 Lg);
   Float64 GetXferLength() const;

   void SetCamber(Float64 camber);
   void SetLateralCamber(Float64 camber);
   void IncludeLateralRollAxisOffset(bool bInclude);

   virtual const matConcreteEx& GetConcrete() const;
   virtual matConcreteEx& GetConcrete();
   void SetConcrete(const matConcreteEx& concrete);

   virtual Float64 GetRebarYieldStrength() const;
   void SetRebarYieldStrength(Float64 fy);

   void SetSupportLocations(Float64 Ll,Float64 Lr);
   void SetYRollAxis(Float64 Yra);
   void SetSweepTolerance(Float64 sweepTolerance);
   void SetSweepGrowth(Float64 sweepGrowth);
   void SetSupportPlacementTolerance(Float64 spt);
   void SetImpact(Float64 up,Float64 down);

   bool GetFpe(LPCTSTR strName,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const;

   Float64 GetCamber() const;
   void SetCamberMultiplier(Float64 m);
   Float64 GetCamberMultiplier() const;

   Float64 GetLateralCamber() const;
   bool IncludeLateralRollAxisOffset() const;

   void GetSupportLocations(Float64* pLeft,Float64* pRight) const;
   Float64 GetYRollAxis() const;
   
   Float64 GetSweepTolerance() const;
   Float64 GetSweepGrowth() const;
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

   // this is not the most efficient data structure because we will be doing
   // lookups by name. however, we don't want the names sorted.
   // since this vector wont be more than 3 to 6 items in length, sequential
   // searching is so bad
   std::vector<std::pair<std::_tstring,std::set<stbFpe>>> m_vFpe;
   IndexType FindFpe(LPCTSTR strName) const; // returns the index into m_vFpe
   
   Float64 m_Camber;
   Float64 m_CamberMultiplier;

   bool m_bIncludeRollAxisLateralOffset;
   Float64 m_LateralCamber;

   matConcreteEx m_Concrete;

   Float64 m_fy;

   Float64 m_Ll; // location of left support, measured from the left end of the girder
   Float64 m_Lr; // location of right support, measured from the right end of the girder

   Float64 m_SweepTolerance;
   Float64 m_SweepGrowth;
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

   IndexType GetFpeCount(LPCTSTR strName) const { return m_Imp.GetFpeCount(strName); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(LPCTSTR strName,Float64 X, Float64 Fpe, Float64 Xps,Float64 Yps) { m_Imp.AddFpe(strName, X, Fpe, Xps, Yps); }
   bool SetFpe(LPCTSTR strName, IndexType fpeIdx, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { return m_Imp.SetFpe(strName, fpeIdx, X, Fpe, Xps, Yps); }
   bool GetFpe(LPCTSTR strName,IndexType fpeIdx, Float64* pX, Float64* pFpe, Float64* pXps, Float64* pYps) const { return m_Imp.GetFpe(strName, fpeIdx, pX, pFpe, pXps, pYps); }

   bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
   void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }
   void SetXferLength(Float64 xferLength, Float64 Lg) { m_Imp.SetXferLength(xferLength, Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

   void SetCamber(Float64 camber) { m_Imp.SetCamber(camber); }
   void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
   Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

   void SetLateralCamber(Float64 camber) { m_Imp.SetLateralCamber(camber); }
   void IncludeLateralRollAxisOffset(bool bInclude) { m_Imp.IncludeLateralRollAxisOffset(bInclude); }

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

   virtual std::vector<LPCTSTR> GetPrestressNames() const override { return m_Imp.GetPrestressNames(); }
   virtual bool GetFpe(LPCTSTR strName,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const override { return m_Imp.GetFpe(strName,X,pFpe,pXps,pYps); }
   virtual Float64 GetCamber() const override {  return m_Imp.GetCamber();   }
   virtual Float64 GetLateralCamber() const override { return m_Imp.GetLateralCamber(); }
   virtual bool IncludeLateralRollAxisOffset() const override { return m_Imp.IncludeLateralRollAxisOffset(); }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const  override { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const  override { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const  override { return m_Imp.GetSupportPlacementTolerance(); }
   virtual void GetImpact(Float64* pIMup,Float64* pIMdown) const  override { m_Imp.GetImpact(pIMup,pIMdown); }

   virtual void GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const  override { m_Imp.GetWindLoading(pType,pLoad); }
   void SetWindLoading(stbTypes::WindType type,Float64 load) { m_Imp.SetWindLoading(type,load); }

   void SetLiftAngle(Float64 liftAngle);
   virtual Float64 GetLiftAngle() const override;

   void SetSweepGrowth(Float64 sweepGrowth) { m_Imp.SetSweepGrowth(sweepGrowth); }
   virtual Float64 GetSweepGrowth() const override { return m_Imp.GetSweepGrowth(); }


   void ClearAnalysisPoints() { m_Imp.ClearAnalysisPoints(); }
   void AddAnalysisPoint(stbIAnalysisPoint* pAnalysisPoint) { m_Imp.AddAnalysisPoint(pAnalysisPoint); }
   virtual std::vector<stbIAnalysisPoint*> GetAnalysisPoints() const  override { return m_Imp.GetAnalysisPoints(); }
   virtual const stbIAnalysisPoint* GetAnalysisPoint(IndexType idx) const  override { return m_Imp.GetAnalysisPoint(idx); }

protected:
   void MakeCopy(const stbLiftingStabilityProblem& other);
   void MakeAssignment(const stbLiftingStabilityProblem& other);

   stbStabilityProblemImp m_Imp;
   Float64 m_LiftAngle;
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

   IndexType GetFpeCount(LPCTSTR strName) const { return m_Imp.GetFpeCount(strName); }
   void ClearFpe() { m_Imp.ClearFpe(); }
   void AddFpe(LPCTSTR strName,Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { m_Imp.AddFpe(strName, X, Fpe, Xps, Yps); }
   bool SetFpe(LPCTSTR strName,IndexType fpeIdx, Float64 X, Float64 Fpe, Float64 Xps, Float64 Yps) { return m_Imp.SetFpe(strName, fpeIdx, X, Fpe, Xps, Yps); }
   bool GetFpe(LPCTSTR strName,IndexType fpeIdx, Float64* pX, Float64* pFpe, Float64* pXps, Float64* pYps) const { return m_Imp.GetFpe(strName, fpeIdx, pX, pFpe, pXps, pYps); }

   bool AdjustForXferLength() const { return m_Imp.AdjustForXferLength(); }
   void AdjustForXferLength(bool bAdjust) { m_Imp.AdjustForXferLength(bAdjust); }
   void SetXferLength(Float64 xferLength,Float64 Lg) { m_Imp.SetXferLength(xferLength,Lg); }
   Float64 GetXferLength() const { return m_Imp.GetXferLength(); }

   void SetCamber(Float64 camber) { m_Imp.SetCamber(camber); }
   void SetCamberMultiplier(Float64 m) { m_Imp.SetCamberMultiplier(m); }
   Float64 GetCamberMultiplier() const { return m_Imp.GetCamberMultiplier(); }

   void SetLateralCamber(Float64 camber) { m_Imp.SetLateralCamber(camber); }
   void IncludeLateralRollAxisOffset(bool bInclude) { m_Imp.IncludeLateralRollAxisOffset(bInclude); }

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

   virtual std::vector<LPCTSTR> GetPrestressNames() const override { return m_Imp.GetPrestressNames(); }
   virtual bool GetFpe(LPCTSTR strName,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const override { return m_Imp.GetFpe(strName,X,pFpe,pXps,pYps); }
   virtual Float64 GetCamber() const override { return m_Imp.GetCamber();   }
   virtual Float64 GetLateralCamber() const override { return m_Imp.GetLateralCamber(); }
   virtual bool IncludeLateralRollAxisOffset() const override { return m_Imp.IncludeLateralRollAxisOffset(); }
   virtual void GetSupportLocations(Float64* pLeft,Float64* pRight) const override { m_Imp.GetSupportLocations(pLeft,pRight); }
   virtual Float64 GetYRollAxis() const override { return m_Imp.GetYRollAxis(); }
   virtual Float64 GetSweepTolerance() const override { return m_Imp.GetSweepTolerance(); }
   virtual Float64 GetSupportPlacementTolerance() const override { return m_Imp.GetSupportPlacementTolerance(); }

   void SetSweepGrowth(Float64 sweepGrowth) { m_Imp.SetSweepGrowth(sweepGrowth); }
   virtual Float64 GetSweepGrowth() const override { return m_Imp.GetSweepGrowth(); }

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
};