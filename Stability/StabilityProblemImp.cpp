///////////////////////////////////////////////////////////////////////
// Stability
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

#include <Stability\StabilityLib.h>
#include <Stability\StabilityProblemImp.h>
#include <UnitMgt\UnitMgt.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool operator<(const stbFpe& a,const stbFpe& b) { return a.X < b.X; }

stbGirder::stbGirder()
{
   m_pSegment = nullptr;

   m_DragCoefficient = 2.2; // default for I-Beams

   m_bLengthNeedsUpdate = true;
}

stbGirder::~stbGirder()
{
}

bool stbGirder::operator==(const stbGirder& other) const
{
   if ( m_pSegment && other.m_pSegment && m_pSegment != other.m_pSegment )
      return false;

   if ( m_pSegment == nullptr && m_vSectionProperties != other.m_vSectionProperties )
      return false;

   if ( m_vPointLoads != other.m_vPointLoads )
      return false;

   if ( !IsEqual(m_DragCoefficient,other.m_DragCoefficient) )
      return false;

   return true;
}

bool stbGirder::operator!=(const stbGirder& other) const
{
   return !(*this == other);
}

void stbGirder::SetSegment(ISegment* pSegment)
{
   m_pSegment = pSegment;
}

void stbGirder::GetSegment(ISegment** ppSegment) const
{
   (*ppSegment) = m_pSegment;
   if ( m_pSegment )
   {
      (*ppSegment)->AddRef();
   }
}

void stbGirder::ClearSections()
{
   m_vSectionProperties.clear();
}

void stbGirder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf)
{
   SetSectionProperties(sectIdx,Length,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf);
}

void stbGirder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2)
{
   stbSectionProperties& props = m_vSectionProperties[sectIdx];
   props.L = Length;
   props.Ag[stbTypes::Start] = Ag;
   props.Ix[stbTypes::Start] = Ix;
   props.Iy[stbTypes::Start] = Iy;
   props.Yt[stbTypes::Start] = Yt;
   props.Hg[stbTypes::Start] = Hg;
   props.Wtf[stbTypes::Start] = Wtf;
   props.Wbf[stbTypes::Start] = Wbf;

   props.Ag[stbTypes::End] = Ag2;
   props.Ix[stbTypes::End] = Ix2;
   props.Iy[stbTypes::End] = Iy2;
   props.Yt[stbTypes::End] = Yt2;
   props.Hg[stbTypes::End] = Hg2;
   props.Wtf[stbTypes::End] = Wtf2;
   props.Wbf[stbTypes::End] = Wbf2;

   m_bLengthNeedsUpdate = true;
}

void stbGirder::AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf)
{
   AddSection(Length,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf);
}

void stbGirder::AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2)
{
   stbSectionProperties props;
   props.Ag[stbTypes::Start] = Ag;
   props.Ag[stbTypes::End]   = Ag2;

   props.Ix[stbTypes::Start] = Ix;
   props.Ix[stbTypes::End]   = Ix2;

   props.Iy[stbTypes::Start] = Iy;
   props.Iy[stbTypes::End]   = Iy2;

   props.Yt[stbTypes::Start] = Yt;
   props.Yt[stbTypes::End]   = Yt2;

   props.Hg[stbTypes::Start] = Hg;
   props.Hg[stbTypes::End]   = Hg2;

   props.Wtf[stbTypes::Start] = Wtf;
   props.Wtf[stbTypes::End]   = Wtf2;

   props.Wbf[stbTypes::Start] = Wbf;
   props.Wbf[stbTypes::End]   = Wbf2;

   props.L = Length;

   m_vSectionProperties.push_back(props);

   m_bLengthNeedsUpdate = true;
}

void stbGirder::ClearPointLoads()
{
   m_vPointLoads.clear();
}

void stbGirder::AddPointLoad(Float64 X,Float64 P)
{
   m_vPointLoads.push_back(std::make_pair(X,P));
}

Float64 stbGirder::GetGirderLength() const
{
   UpdateLength();
   return m_L;
}

IndexType stbGirder::GetSectionCount() const
{
   return m_vSectionProperties.size();
}

void stbGirder::GetSectionProperties(IndexType sectIdx,stbTypes::Section section,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   const stbSectionProperties& props = m_vSectionProperties[sectIdx];
   *pAg = props.Ag[section];
   *pIx = props.Ix[section];
   *pIy = props.Iy[section];
   *pYt = props.Yt[section];
   *pHg = props.Hg[section];
   *pWtop = props.Wtf[section];
   *pWbot = props.Wbf[section];
}

Float64 stbGirder::GetSectionLength(IndexType sectIdx) const
{
   return m_vSectionProperties[sectIdx].L;
}

void stbGirder::GetSectionProperties(Float64 X,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   ATLASSERT(m_vSectionProperties.size() != 0);

   if ( m_vSectionProperties.size() == 1 )
   {
      const stbSectionProperties& props = m_vSectionProperties.front();
      *pAg = ::LinInterp(X,props.Ag[stbTypes::Start],props.Ag[stbTypes::End],props.L);
      *pIx = ::LinInterp(X,props.Ix[stbTypes::Start],props.Ix[stbTypes::End],props.L);
      *pIy = ::LinInterp(X,props.Iy[stbTypes::Start],props.Iy[stbTypes::End],props.L);
      *pYt = ::LinInterp(X,props.Yt[stbTypes::Start],props.Yt[stbTypes::End],props.L);
      *pHg = ::LinInterp(X,props.Hg[stbTypes::Start],props.Hg[stbTypes::End],props.L);
      *pWtop = ::LinInterp(X,props.Wtf[stbTypes::Start],props.Wtf[stbTypes::End],props.L);
      *pWbot = ::LinInterp(X,props.Wbf[stbTypes::Start],props.Wbf[stbTypes::End],props.L);
      return;
   }

   Float64 Xstart = 0;
   std::vector<stbSectionProperties>::const_iterator iter(m_vSectionProperties.begin());
   std::vector<stbSectionProperties>::const_iterator end(m_vSectionProperties.end());
   for ( ; iter != end; iter++ )
   {
      Float64 Xend = Xstart + iter->L;
      if ( ::InRange(Xstart,X,Xend) )
      {
         *pAg = ::LinInterp(X-Xstart,iter->Ag[stbTypes::Start],iter->Ag[stbTypes::End],Xend-Xstart);
         *pIx = ::LinInterp(X-Xstart,iter->Ix[stbTypes::Start],iter->Ix[stbTypes::End],Xend-Xstart);
         *pIy = ::LinInterp(X-Xstart,iter->Iy[stbTypes::Start],iter->Iy[stbTypes::End],Xend-Xstart);
         *pYt = ::LinInterp(X-Xstart,iter->Yt[stbTypes::Start],iter->Yt[stbTypes::End],Xend-Xstart);
         *pHg = ::LinInterp(X-Xstart,iter->Hg[stbTypes::Start],iter->Hg[stbTypes::End],Xend-Xstart);
         *pWtop = ::LinInterp(X-Xstart,iter->Wtf[stbTypes::Start],iter->Wtf[stbTypes::End],Xend-Xstart);
         *pWbot = ::LinInterp(X-Xstart,iter->Wbf[stbTypes::Start],iter->Wbf[stbTypes::End],Xend-Xstart);
         return;
      }
      Xstart = Xend;
   }

   ATLASSERT(false); // should never get here.... is X out of range?
}

void stbGirder::SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads)
{
   m_vPointLoads = vLoads;
}

std::vector<std::pair<Float64,Float64>> stbGirder::GetAdditionalLoads() const
{
   return m_vPointLoads;
}

Float64 stbGirder::GetDragCoefficient() const
{
   return m_DragCoefficient;
}

void stbGirder::SetDragCoefficient(Float64 Cd)
{
   m_DragCoefficient = Cd;
}

void stbGirder::UpdateLength() const
{
   if ( m_bLengthNeedsUpdate )
   {
      Float64 L = 0;
      std::vector<stbSectionProperties>::const_iterator iter(m_vSectionProperties.begin());
      std::vector<stbSectionProperties>::const_iterator end(m_vSectionProperties.end());
      for ( ; iter != end; iter++ )
      {
         const stbSectionProperties& sp(*iter);
         L += sp.L;
      }
      m_L = L;
      m_bLengthNeedsUpdate = false;
   }
}

/////////////////////////////////////////////////////
stbStabilityProblemImp::stbStabilityProblemImp()
{
   m_fy = 0;

   m_bAdjustForXferLength = false;
   m_XferLength = 0;

   m_bDirectCamber = true;
   m_Camber = 0;
   m_CamberMultiplier = 1.0;

   m_Ll = 0;
   m_Lr = 0;

   m_SweepTolerance = 0;
   m_SupportPlacementTolerance = 0;

   m_Yra = 0;

   m_ImpactUp = 0;
   m_ImpactDown = 0;

   m_WindLoadType = stbTypes::Speed;
   m_WindLoad = 0.;
}

stbStabilityProblemImp::stbStabilityProblemImp(const stbStabilityProblemImp& other)
{
   MakeCopy(other);
}

stbStabilityProblemImp::~stbStabilityProblemImp()
{
   ClearAnalysisPoints();
}

stbStabilityProblemImp& stbStabilityProblemImp::operator=(const stbStabilityProblemImp& other)
{
   if( this != &other )
   {
      MakeAssignment(other);
   }

   return *this;
}

bool stbStabilityProblemImp::operator==(const stbStabilityProblemImp& other) const
{
   if ( m_Concrete != other.m_Concrete )
      return false;

   if ( !IsEqual(m_fy,other.m_fy) )
      return false;

   if ( !CompareAnalysisPoints(other) )
      return false;

   if ( !IsEqual(m_XferLength,other.m_XferLength) )
      return false;

   if ( !IsEqual(m_Lg,other.m_Lg) )
      return false;

   if ( m_vFpe != other.m_vFpe )
      return false;

   if ( m_bDirectCamber != other.m_bDirectCamber )
      return false;

   if ( !IsEqual(m_Camber,other.m_Camber) )
      return false;

   if (m_bDirectCamber && !IsEqual(m_CamberMultiplier, other.m_CamberMultiplier))
      return false;

   if ( !IsEqual(m_Ll,other.m_Ll) )
      return false;

   if ( !IsEqual(m_Lr,other.m_Lr) )
      return false;

   if ( !IsEqual(m_SweepTolerance,other.m_SweepTolerance) )
      return false;

   if ( !IsEqual(m_SupportPlacementTolerance,other.m_SupportPlacementTolerance) )
      return false;

   if ( !IsEqual(m_Yra,other.m_Yra) )
      return false;

   if ( !IsEqual(m_ImpactUp,other.m_ImpactUp) )
      return false;

   if ( !IsEqual(m_ImpactDown,other.m_ImpactDown) )
      return false;

   if ( m_WindLoadType != other.m_WindLoadType )
      return false;

   if ( !IsEqual(m_WindLoad,other.m_WindLoad) )
      return false;

   return true;
}

bool stbStabilityProblemImp::operator!=(const stbStabilityProblemImp& other) const
{
   return !(*this == other);
}

IndexType stbStabilityProblemImp::GetFpeCount() const
{
   // if effective prestress is not defined, pretend like we have a single value
   return Max((int)m_vFpe.size(),(int)1);
}

void stbStabilityProblemImp::ClearFpe()
{
   m_vFpe.clear();
}

void stbStabilityProblemImp::AddFpe(Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp)
{
   stbFpe fpe;
   fpe.X = X;
   fpe.fpeStraight = FpeStraight;
   fpe.YpsStraight = YpsStraight;

   fpe.fpeHarped = FpeHarped;
   fpe.YpsHarped = YpsHarped;

   fpe.fpeTemporary = FpeTemp;
   fpe.YpsTemporary = YpsTemp;

   m_vFpe.insert(fpe);
}

void stbStabilityProblemImp::SetFpe(IndexType fpeIdx,Float64 X,Float64 FpeStraight,Float64 YpsStraight,Float64 FpeHarped,Float64 YpsHarped,Float64 FpeTemp,Float64 YpsTemp)
{
   ATLASSERT(fpeIdx < m_vFpe.size());

   std::set<stbFpe>::iterator iter(m_vFpe.begin());
   for ( IndexType i = 0; i < fpeIdx; i++)
   {
      iter++;
   }
   stbFpe& fpe(const_cast<stbFpe&>(*iter));

   fpe.fpeStraight  = FpeStraight;
   fpe.YpsStraight  = YpsStraight;
   fpe.fpeHarped    = FpeHarped;
   fpe.YpsHarped    = YpsHarped;
   fpe.fpeTemporary = FpeTemp;
   fpe.YpsTemporary = YpsTemp;
}

void stbStabilityProblemImp::GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pYpsStraight,Float64* pFpeHarped,Float64* pYpsHarped,Float64* pFpeTemp,Float64* pYpsTemp) const
{
   if ( m_vFpe.size() == 0 )
   {
      *pX = 0;
      *pFpeStraight = 0;
      *pYpsStraight = 0;

      *pFpeHarped = 0;
      *pYpsHarped = 0;

      *pFpeTemp = 0;
      *pYpsTemp = 0;
   }
   else
   {
      std::set<stbFpe>::const_iterator iter(m_vFpe.begin());
      for ( IndexType i = 0; i < fpeIdx; i++)
      {
         iter++;
      }

      *pX = iter->X;
      *pFpeStraight = iter->fpeStraight;
      *pYpsStraight = iter->YpsStraight;

      *pFpeHarped   = iter->fpeHarped;
      *pYpsHarped   = iter->YpsHarped;

      *pFpeTemp     = iter->fpeTemporary;
      *pYpsTemp     = iter->YpsTemporary;
   }
}

bool stbStabilityProblemImp::AdjustForXferLength() const
{
   return m_bAdjustForXferLength;
}

void stbStabilityProblemImp::AdjustForXferLength(bool bAdjust)
{
   m_bAdjustForXferLength = bAdjust;
}

void stbStabilityProblemImp::SetXferLength(Float64 xferLength,Float64 Lg)
{
   m_XferLength = xferLength;
   m_Lg = Lg;
}

Float64 stbStabilityProblemImp::GetXferLength() const
{
   return m_XferLength;
}

void stbStabilityProblemImp::SetCamber(bool bDirectCamber,Float64 camber)
{
   m_bDirectCamber = bDirectCamber;
   m_Camber = camber;
}

void stbStabilityProblemImp::SetCamberMultiplier(Float64 m)
{
   m_CamberMultiplier = m;
}

Float64 stbStabilityProblemImp::GetCamberMultiplier() const
{
   return m_CamberMultiplier;
}

const matConcreteEx& stbStabilityProblemImp::GetConcrete() const
{
   return m_Concrete;
}

matConcreteEx& stbStabilityProblemImp::GetConcrete()
{
   return m_Concrete;
}

void stbStabilityProblemImp::SetConcrete(const matConcreteEx& concrete)
{
   m_Concrete = concrete;
}

Float64 stbStabilityProblemImp::GetRebarYieldStrength() const
{
   return m_fy;
}

void stbStabilityProblemImp::SetRebarYieldStrength(Float64 fy)
{
   m_fy = fy;
}

void stbStabilityProblemImp::SetSupportLocations(Float64 Ll,Float64 Lr)
{
   m_Ll = Ll;
   m_Lr = Lr;
}

void stbStabilityProblemImp::SetYRollAxis(Float64 Yra)
{
   m_Yra = Yra;
}

void stbStabilityProblemImp::SetSweepTolerance(Float64 sweepTolerance)
{
   m_SweepTolerance = sweepTolerance;
}

void stbStabilityProblemImp::SetSupportPlacementTolerance(Float64 spt)
{
   m_SupportPlacementTolerance = spt;
}

void stbStabilityProblemImp::SetImpact(Float64 up,Float64 down)
{
   m_ImpactUp = up;
   m_ImpactDown = down;
}

void stbStabilityProblemImp::GetFpe(stbTypes::StrandType strandType,Float64 X,Float64* pFpe,Float64* pYps) const
{
   if ( m_vFpe.size() == 0 )
   {
      *pFpe = 0;
      *pYps = 0;
      return;
   }

   Float64 Xfer = 1.0;
   if ( m_bAdjustForXferLength )
   {
      if ( X < m_XferLength )
      {
         Xfer = X/m_XferLength;
      }
      else if (m_Lg-m_XferLength < X)
      {
         Float64 x = m_Lg - X;
         Xfer = x/m_XferLength;
      }
   }

   // before the start
   if ( ::IsLE(X,m_vFpe.begin()->X) )
   {
      if ( strandType == stbTypes::Straight )
      {
         *pFpe = m_vFpe.begin()->fpeStraight;
         *pYps = m_vFpe.begin()->YpsStraight;
      }
      else if ( strandType == stbTypes::Harped )
      {
         *pFpe = m_vFpe.begin()->fpeHarped;
         *pYps = m_vFpe.begin()->YpsHarped;
      }
      else
      {
         *pFpe = m_vFpe.begin()->fpeTemporary;
         *pYps = m_vFpe.begin()->YpsTemporary;
      }

      *pFpe *= Xfer;

      return;
   }

   if ( ::IsLE(m_vFpe.rbegin()->X,X) )
   {
      // after end
      if ( strandType == stbTypes::Straight )
      {
         *pFpe = m_vFpe.rbegin()->fpeStraight;
         *pYps = m_vFpe.rbegin()->YpsStraight;
      }
      else if ( strandType == stbTypes::Harped )
      {
         *pFpe = m_vFpe.rbegin()->fpeHarped;
         *pYps = m_vFpe.rbegin()->YpsHarped;
      }
      else
      {
         *pFpe = m_vFpe.rbegin()->fpeTemporary;
         *pYps = m_vFpe.rbegin()->YpsTemporary;
      }

      *pFpe *= Xfer;

      return;
   }

   // somewhere in the middle
   ATLASSERT(2 <= m_vFpe.size());
   std::set<stbFpe>::const_iterator iter1(m_vFpe.begin());
   std::set<stbFpe>::const_iterator iter2(iter1);
   iter2++;
   std::set<stbFpe>::const_iterator end(m_vFpe.end());
   for ( ; iter2 != end; iter1++, iter2++ )
   {
      Float64 Xstart = iter1->X;
      Float64 Xend   = iter2->X;
      if (::InRange(Xstart,X,Xend) )
      {
         Float64 FpeStart,FpeEnd;
         Float64 YpsStart,YpsEnd;
         if ( strandType == stbTypes::Straight )
         {
            FpeStart = iter1->fpeStraight;
            YpsStart = iter1->YpsStraight;
            FpeEnd   = iter2->fpeStraight;
            YpsEnd   = iter2->YpsStraight;
         }
         else if ( strandType == stbTypes::Harped )
         {
            FpeStart = iter1->fpeHarped;
            YpsStart = iter1->YpsHarped;
            FpeEnd   = iter2->fpeHarped;
            YpsEnd   = iter2->YpsHarped;
         }
         else
         {
            FpeStart = iter1->fpeTemporary;
            YpsStart = iter1->YpsTemporary;
            FpeEnd   = iter2->fpeTemporary;
            YpsEnd   = iter2->YpsTemporary;
         }

         Float64 fpe = ::LinInterp(X-Xstart,FpeStart,FpeEnd,Xend-Xstart);
         Float64 yps = ::LinInterp(X-Xstart,YpsStart,YpsEnd,Xend-Xstart);
         *pFpe = fpe;
         *pYps = yps;

         *pFpe *= Xfer;

         return;
      }
   }

   ATLASSERT(false); // should never get here
}

void stbStabilityProblemImp::GetCamber(bool* pbDirectCamber,Float64* pCamber) const
{
   *pbDirectCamber = m_bDirectCamber;
   *pCamber = m_Camber;
}

void stbStabilityProblemImp::GetSupportLocations(Float64* pLeft,Float64* pRight) const
{
   *pLeft = m_Ll;
   *pRight = m_Lr;
}

Float64 stbStabilityProblemImp::GetYRollAxis() const
{
   return m_Yra;
}

Float64 stbStabilityProblemImp::GetSweepTolerance() const
{
   return m_SweepTolerance;
}

Float64 stbStabilityProblemImp::GetSupportPlacementTolerance() const
{
   return m_SupportPlacementTolerance;
}

void stbStabilityProblemImp::GetImpact(Float64* pIMup,Float64* pIMdown) const
{
   *pIMup   = m_ImpactUp;
   *pIMdown = m_ImpactDown;
}

void stbStabilityProblemImp::GetWindLoading(stbTypes::WindType* pType,Float64* pLoad) const
{
   *pType = m_WindLoadType;
   *pLoad = m_WindLoad;
}

void stbStabilityProblemImp::SetWindLoading(stbTypes::WindType type,Float64 load)
{
   m_WindLoadType = type;
   m_WindLoad = load;
}

void stbStabilityProblemImp::ClearAnalysisPoints()
{
   for( const auto& pAnalysisPoint : m_vAnalysisPoints)
   {
      delete pAnalysisPoint;
   }
   m_vAnalysisPoints.clear();
}

bool SortAnalysisPoints(stbIAnalysisPoint* pA,stbIAnalysisPoint* pB)
{
   return (pA->GetLocation() < pB->GetLocation());
}

void stbStabilityProblemImp::AddAnalysisPoint(stbIAnalysisPoint* pAnalysisPoint)
{
   m_vAnalysisPoints.push_back(pAnalysisPoint);
   std::sort(m_vAnalysisPoints.begin(),m_vAnalysisPoints.end(),SortAnalysisPoints);
   //m_vAnalysisPoints.erase(std::unique(m_vAnalysisPoints.begin(),m_vAnalysisPoints.end(),IsEqual),m_vAnalysisPoints.end());
}

const std::vector<stbIAnalysisPoint*>& stbStabilityProblemImp::GetAnalysisPoints() const
{
   return m_vAnalysisPoints;
}

const stbIAnalysisPoint* stbStabilityProblemImp::GetAnalysisPoint(IndexType idx) const
{
   return m_vAnalysisPoints[idx];
}

bool stbStabilityProblemImp::CompareAnalysisPoints(const stbStabilityProblemImp& other) const
{
   if ( m_vAnalysisPoints.size() != other.m_vAnalysisPoints.size() )
      return false;

   std::vector<stbIAnalysisPoint*>::const_iterator thisIter(m_vAnalysisPoints.begin());
   std::vector<stbIAnalysisPoint*>::const_iterator thisIterEnd(m_vAnalysisPoints.end());
   std::vector<stbIAnalysisPoint*>::const_iterator otherIter(other.m_vAnalysisPoints.begin());
   for ( ; thisIter != thisIterEnd; thisIter++, otherIter++ )
   {
      const stbIAnalysisPoint* pA(*thisIter);
      const stbIAnalysisPoint* pB(*otherIter);
      if ( !::IsEqual(pA->GetLocation(),pB->GetLocation()) )
      {
         return false;
      }
   }

   return true;
}

void stbStabilityProblemImp::MakeCopy(const stbStabilityProblemImp& other)
{
   ClearAnalysisPoints();
   for( const auto& pAnalysisPoint : other.m_vAnalysisPoints)
   {
      AddAnalysisPoint(pAnalysisPoint->Clone());
   }

   m_bAdjustForXferLength = other.m_bAdjustForXferLength;;
   m_XferLength = other.m_XferLength;;
   m_Lg = other.m_Lg;

   m_vFpe = other.m_vFpe;
   
   m_bDirectCamber = other.m_bDirectCamber;
   m_Camber = other.m_Camber;
   m_CamberMultiplier = other.m_CamberMultiplier;

   m_Concrete = other.m_Concrete;

   m_fy = other.m_fy;

   m_Ll = other.m_Ll;
   m_Lr = other.m_Lr;

   m_SweepTolerance = other.m_SweepTolerance;
   m_SupportPlacementTolerance = other.m_SupportPlacementTolerance;

   m_Yra = other.m_Yra;

   m_ImpactUp = other.m_ImpactUp;
   m_ImpactDown = other.m_ImpactDown;

   m_WindLoadType = other.m_WindLoadType;
   m_WindLoad = other.m_WindLoad;
}

void stbStabilityProblemImp::MakeAssignment(const stbStabilityProblemImp& other)
{
   MakeCopy(other);
}

////////////////////////////////


stbLiftingStabilityProblem::stbLiftingStabilityProblem()
{
   m_bPlumbGirderStresses = false;
   m_LiftAngle = PI_OVER_2;
}

stbLiftingStabilityProblem::stbLiftingStabilityProblem(const stbLiftingStabilityProblem& other)
{
   MakeCopy(other);
}

stbLiftingStabilityProblem::~stbLiftingStabilityProblem()
{
}

stbLiftingStabilityProblem& stbLiftingStabilityProblem::operator=(const stbLiftingStabilityProblem& other)
{
   if( this != &other )
   {
      MakeAssignment(other);
   }

   return *this;
}

bool stbLiftingStabilityProblem::operator==(const stbLiftingStabilityProblem& other) const
{
   if ( m_bPlumbGirderStresses != other.m_bPlumbGirderStresses )
      return false;

   if ( !IsEqual(m_LiftAngle,other.m_LiftAngle) )
      return false;

   if ( m_Imp != other.m_Imp )
      return false;

   return true;
}

bool stbLiftingStabilityProblem::operator!=(const stbLiftingStabilityProblem& other) const
{
   return !(*this == other);
}

void stbLiftingStabilityProblem::SetLiftAngle(Float64 liftAngle)
{
   m_LiftAngle = liftAngle;
}

Float64 stbLiftingStabilityProblem::GetLiftAngle() const
{
   return m_LiftAngle;
}

void stbLiftingStabilityProblem::EvaluateStressesForPlumbGirder(bool bPlumbStresses)
{
   m_bPlumbGirderStresses = bPlumbStresses;
}

bool stbLiftingStabilityProblem::EvaluateStressesForPlumbGirder() const
{
   return m_bPlumbGirderStresses;
}

void stbLiftingStabilityProblem::MakeCopy(const stbLiftingStabilityProblem& other)
{
   m_Imp = other.m_Imp;
   m_bPlumbGirderStresses = other.m_bPlumbGirderStresses;
   m_LiftAngle = other.m_LiftAngle;
}

void stbLiftingStabilityProblem::MakeAssignment(const stbLiftingStabilityProblem& other)
{
   MakeCopy(other);
}

//////////////////////////////////
stbHaulingStabilityProblem::stbHaulingStabilityProblem()
{
   m_ImpactUsage = stbTypes::Both;

   m_Ktheta = 0;
   m_Wcc = 0;
   m_Hrc = 0;
   m_Superelevation = 0;
   m_CrownSlope = 0;
   
   m_Velocity = 0;
   m_Radius = DBL_MAX;
   m_CFType = stbTypes::Favorable;
}

stbHaulingStabilityProblem::stbHaulingStabilityProblem(const stbHaulingStabilityProblem& other)
{
   MakeCopy(other);
}

stbHaulingStabilityProblem::~stbHaulingStabilityProblem()
{
}

stbHaulingStabilityProblem& stbHaulingStabilityProblem::operator=(const stbHaulingStabilityProblem& other)
{
   if( this != &other )
   {
      MakeAssignment(other);
   }

   return *this;
}

bool stbHaulingStabilityProblem::operator==(const stbHaulingStabilityProblem& other) const
{
   if ( m_Imp != other.m_Imp )
      return false;

   if ( m_ImpactUsage != other.m_ImpactUsage )
      return false;

   if ( !IsEqual(m_Ktheta,other.m_Ktheta) )
      return false;

   if ( !IsEqual(m_Wcc,other.m_Wcc) )
      return false;

   if ( !IsEqual(m_Hrc,other.m_Hrc) )
      return false;

   if ( !IsEqual(m_CrownSlope,other.m_CrownSlope) )
      return false;

   if ( !IsEqual(m_Superelevation,other.m_Superelevation) )
      return false;

   if ( !IsEqual(m_Velocity,other.m_Velocity) )
      return false;

   if ( !IsEqual(m_Radius,other.m_Radius) )
      return false;

   if ( m_CFType != other.m_CFType )
      return false;

   return true;
}

bool stbHaulingStabilityProblem::operator!=(const stbHaulingStabilityProblem& other) const
{
   return !(*this == other);
}

void stbHaulingStabilityProblem::SetImpactUsage(stbTypes::HaulingImpact impactUsage)
{
   m_ImpactUsage = impactUsage;
}

stbTypes::HaulingImpact stbHaulingStabilityProblem::GetImpactUsage() const
{
   return m_ImpactUsage;
}

void stbHaulingStabilityProblem::SetTruckRotationalStiffness(Float64 Ktheta)
{
   m_Ktheta = Ktheta;
}

Float64 stbHaulingStabilityProblem::GetTruckRotationalStiffness() const
{
   return m_Ktheta;
}

void stbHaulingStabilityProblem::SetWheelLineSpacing(Float64 Wcc)
{
   m_Wcc = Wcc;
}

Float64 stbHaulingStabilityProblem::GetWheelLineSpacing() const
{
   return m_Wcc;
}

void stbHaulingStabilityProblem::SetHeightOfRollAxisAboveRoadway(Float64 Hrs)
{
   m_Hrc = Hrs;
}

Float64 stbHaulingStabilityProblem::GetHeightOfRollAxisAboveRoadway() const
{
   return m_Hrc;
}

void stbHaulingStabilityProblem::SetCrownSlope(Float64 crown)
{
   m_CrownSlope = crown;
}

Float64 stbHaulingStabilityProblem::GetCrownSlope() const
{
   return m_CrownSlope;
}

void stbHaulingStabilityProblem::SetSuperelevation(Float64 alpha)
{
   m_Superelevation = alpha;
}

Float64 stbHaulingStabilityProblem::GetSuperelevation() const
{
   return m_Superelevation;
}

void stbHaulingStabilityProblem::SetVelocity(Float64 velocity)
{
   m_Velocity = velocity;
}

Float64 stbHaulingStabilityProblem::GetVelocity() const
{
   return m_Velocity;
}

void stbHaulingStabilityProblem::SetTurningRadius(Float64 r)
{
   m_Radius = r;
}

Float64 stbHaulingStabilityProblem::GetTurningRadius() const
{
   return m_Radius;
}

void stbHaulingStabilityProblem::SetCentrifugalForceType(stbTypes::CFType cfType)
{
   m_CFType = cfType;
}

stbTypes::CFType stbHaulingStabilityProblem::GetCentrifugalForceType() const
{
   return m_CFType;
}

void stbHaulingStabilityProblem::MakeCopy(const stbHaulingStabilityProblem& other)
{
   m_Imp = other.m_Imp;

   m_ImpactUsage = other.m_ImpactUsage;
   m_Ktheta = other.m_Ktheta;
   m_Wcc = other.m_Wcc;
   m_Hrc = other.m_Hrc;
   m_CrownSlope = other.m_CrownSlope;
   m_Superelevation = other.m_Superelevation;
   
   m_Velocity = other.m_Velocity;
   m_Radius = other.m_Radius;
   m_CFType = other.m_CFType;
}

void stbHaulingStabilityProblem::MakeAssignment(const stbHaulingStabilityProblem& other)
{
   MakeCopy(other);
}
