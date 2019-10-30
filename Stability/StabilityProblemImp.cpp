///////////////////////////////////////////////////////////////////////
// Stability
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

   m_Precamber = 0.0;

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

   if (!IsEqual(m_Precamber, other.m_Precamber))
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

IndexType stbGirder::AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf)
{
   return AddSection(Length, Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf, Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf);
}

IndexType stbGirder::AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf, Float64 Ag2, Float64 Ixx2, Float64 Iyy2, Float64 Ixy2, Float64 Xcg2, Float64 Ycg2, Float64 Hg2, Float64 Wtf2, Float64 Wbf2)
{
   stbSectionProperties props;
   props.Ag[stbTypes::Start] = Ag;
   props.Ag[stbTypes::End] = Ag2;

   props.Ixx[stbTypes::Start] = Ixx;
   props.Ixx[stbTypes::End] = Ixx2;

   props.Iyy[stbTypes::Start] = Iyy;
   props.Iyy[stbTypes::End] = Iyy2;

   props.Ixy[stbTypes::Start] = Ixy;
   props.Ixy[stbTypes::End] = Ixy2;

   props.Xleft[stbTypes::Start] = Xleft;
   props.Xleft[stbTypes::End] = Xcg2;

   props.Ytop[stbTypes::Start] = Ytop;
   props.Ytop[stbTypes::End] = Ycg2;

   props.Hg[stbTypes::Start] = Hg;
   props.Hg[stbTypes::End] = Hg2;

   props.Wtf[stbTypes::Start] = Wtf;
   props.Wtf[stbTypes::End] = Wtf2;

   props.Wbf[stbTypes::Start] = Wbf;
   props.Wbf[stbTypes::End] = Wbf2;

   props.L = Length;

   IndexType index = m_vSectionProperties.size();
   m_vSectionProperties.push_back(props);

   m_bLengthNeedsUpdate = true;

   return index;
}

void stbGirder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy,Float64 Xleft,Float64 Ytop,Float64 Hg,Float64 Wtf,Float64 Wbf)
{
   SetSectionProperties(sectIdx,Length,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf);
}

void stbGirder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy,Float64 Xleft,Float64 Ytop,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ixx2,Float64 Iyy2,Float64 Ixy2,Float64 Xcg2,Float64 Ycg2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2)
{
   stbSectionProperties& props = m_vSectionProperties[sectIdx];
   props.L = Length;
   props.Ag[stbTypes::Start] = Ag;
   props.Ixx[stbTypes::Start] = Ixx;
   props.Iyy[stbTypes::Start] = Iyy;
   props.Ixy[stbTypes::Start] = Ixy;
   props.Xleft[stbTypes::Start] = Xleft;
   props.Ytop[stbTypes::Start] = Ytop;
   props.Hg[stbTypes::Start] = Hg;
   props.Wtf[stbTypes::Start] = Wtf;
   props.Wbf[stbTypes::Start] = Wbf;

   props.Ag[stbTypes::End] = Ag2;
   props.Ixx[stbTypes::End] = Ixx2;
   props.Iyy[stbTypes::End] = Iyy2;
   props.Ixy[stbTypes::End] = Ixy2;
   props.Xleft[stbTypes::End] = Xcg2;
   props.Ytop[stbTypes::End] = Ycg2;
   props.Hg[stbTypes::End] = Hg2;
   props.Wtf[stbTypes::End] = Wtf2;
   props.Wbf[stbTypes::End] = Wbf2;

   m_bLengthNeedsUpdate = true;
}

// Assigns stress point values to a section. 
void stbGirder::SetStressPoints(IndexType sectIdx, const gpPoint2d& pntTL, const gpPoint2d& pntTR, const gpPoint2d& pntBL, const gpPoint2d& pntBR)
{
   SetStressPoints(sectIdx, pntTL, pntTR, pntBL, pntBR, pntTL, pntTR, pntBL, pntBR);
}

void stbGirder::SetStressPoints(IndexType sectIdx, const gpPoint2d& pntTL, const gpPoint2d& pntTR, const gpPoint2d& pntBL, const gpPoint2d& pntBR, const gpPoint2d& pntTL2, const gpPoint2d& pntTR2, const gpPoint2d& pntBL2, const gpPoint2d& pntBR2)
{
   stbSectionProperties& props = m_vSectionProperties[sectIdx];
   if (props.m_pStressPoints == nullptr)
   {
      // stress points have not yet been assigned
      props.m_pStressPoints = std::make_shared<stbStressPoints>();
   }
   props.m_pStressPoints->pntTL[stbTypes::Start] = pntTL;
   props.m_pStressPoints->pntTR[stbTypes::Start] = pntTR;
   props.m_pStressPoints->pntBL[stbTypes::Start] = pntBL;
   props.m_pStressPoints->pntBR[stbTypes::Start] = pntBR;

   props.m_pStressPoints->pntTL[stbTypes::End] = pntTL2;
   props.m_pStressPoints->pntTR[stbTypes::End] = pntTR2;
   props.m_pStressPoints->pntBL[stbTypes::End] = pntBL2;
   props.m_pStressPoints->pntBR[stbTypes::End] = pntBR2;
}

void stbGirder::ClearPointLoads()
{
   m_vPointLoads.clear();
}

void stbGirder::AddPointLoad(Float64 X,Float64 P)
{
   m_vPointLoads.emplace_back(X,P);
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

Float64 stbGirder::GetSectionLength(IndexType sectIdx) const
{
   return m_vSectionProperties[sectIdx].L;
}

void stbGirder::GetSectionProperties(IndexType sectIdx,stbTypes::Section section,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   const stbSectionProperties& props = m_vSectionProperties[sectIdx];
   *pAg = props.Ag[section];
   *pIxx = props.Ixx[section];
   *pIyy = props.Iyy[section];
   *pIxy = props.Ixy[section];
   *pXleft = props.Xleft[section];
   *pYtop = props.Ytop[section];
   *pHg = props.Hg[section];
   *pWtop = props.Wtf[section];
   *pWbot = props.Wbf[section];
}

void stbGirder::GetSectionProperties(Float64 X,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   ATLASSERT(m_vSectionProperties.size() != 0);

   if ( m_vSectionProperties.size() == 1 )
   {
      const stbSectionProperties& props = m_vSectionProperties.front();
      *pAg = ::LinInterp(X,props.Ag[stbTypes::Start],props.Ag[stbTypes::End],props.L);
      *pIxx = ::LinInterp(X,props.Ixx[stbTypes::Start],props.Ixx[stbTypes::End],props.L);
      *pIyy = ::LinInterp(X,props.Iyy[stbTypes::Start],props.Iyy[stbTypes::End],props.L);
      *pIxy = ::LinInterp(X, props.Ixy[stbTypes::Start], props.Ixy[stbTypes::End], props.L);
      *pXleft = ::LinInterp(X, props.Xleft[stbTypes::Start], props.Xleft[stbTypes::End], props.L);
      *pYtop = ::LinInterp(X, props.Ytop[stbTypes::Start], props.Ytop[stbTypes::End], props.L);
      *pHg = ::LinInterp(X,props.Hg[stbTypes::Start],props.Hg[stbTypes::End],props.L);
      *pWtop = ::LinInterp(X,props.Wtf[stbTypes::Start],props.Wtf[stbTypes::End],props.L);
      *pWbot = ::LinInterp(X,props.Wbf[stbTypes::Start],props.Wbf[stbTypes::End],props.L);
      return;
   }

   Float64 Xstart = 0;
   for (const auto& properties : m_vSectionProperties)
   {
      Float64 Xend = Xstart + properties.L;
      if ( ::InRange(Xstart,X,Xend) )
      {
         *pAg = ::LinInterp(X-Xstart,properties.Ag[stbTypes::Start],properties.Ag[stbTypes::End],properties.L);
         *pIxx = ::LinInterp(X-Xstart,properties.Ixx[stbTypes::Start],properties.Ixx[stbTypes::End],properties.L);
         *pIyy = ::LinInterp(X - Xstart, properties.Iyy[stbTypes::Start], properties.Iyy[stbTypes::End], properties.L);
         *pIxy = ::LinInterp(X - Xstart, properties.Ixy[stbTypes::Start], properties.Ixy[stbTypes::End], properties.L);
         *pXleft = ::LinInterp(X - Xstart, properties.Xleft[stbTypes::Start], properties.Xleft[stbTypes::End], properties.L);
         *pYtop = ::LinInterp(X - Xstart, properties.Ytop[stbTypes::Start], properties.Ytop[stbTypes::End], properties.L);
         *pHg = ::LinInterp(X-Xstart,properties.Hg[stbTypes::Start],properties.Hg[stbTypes::End],properties.L);
         *pWtop = ::LinInterp(X-Xstart,properties.Wtf[stbTypes::Start],properties.Wtf[stbTypes::End],properties.L);
         *pWbot = ::LinInterp(X-Xstart,properties.Wbf[stbTypes::Start],properties.Wbf[stbTypes::End],properties.L);
         return;
      }
      Xstart = Xend;
   }

   ATLASSERT(false); // should never get here.... is X out of range?
}

void stbGirder::GetStressPoints(IndexType sectIdx, stbTypes::Section section, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const
{
   const stbSectionProperties& props = m_vSectionProperties[sectIdx];
   GetStressPoints(props, section, pTL, pTR, pBL, pBR);
}

void stbGirder::GetStressPoints(Float64 X, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const
{
   Float64 Xstart = 0;
   for (const auto& props : m_vSectionProperties)
   {
      Float64 Xend = Xstart + props.L;
      if (::InRange(Xstart, X, Xend))
      {
         gpPoint2d tl1, tr1, bl1, br1;
         GetStressPoints(props, stbTypes::Start, &tl1, &tr1, &bl1, &br1);

         gpPoint2d tl2, tr2, bl2, br2;
         GetStressPoints(props, stbTypes::End, &tl2, &tr2, &bl2, &br2);

         pTL->X() = ::LinInterp(X - Xstart, tl1.X(), tl2.X(), props.L);
         pTL->Y() = ::LinInterp(X - Xstart, tl1.Y(), tl2.Y(), props.L);

         pTR->X() = ::LinInterp(X - Xstart, tr1.X(), tr2.X(), props.L);
         pTR->Y() = ::LinInterp(X - Xstart, tr1.Y(), tr2.Y(), props.L);

         pBL->X() = ::LinInterp(X - Xstart, bl1.X(), bl2.X(), props.L);
         pBL->Y() = ::LinInterp(X - Xstart, bl1.Y(), bl2.Y(), props.L);

         pBR->X() = ::LinInterp(X - Xstart, br1.X(), br2.X(), props.L);
         pBR->Y() = ::LinInterp(X - Xstart, br1.Y(), br2.Y(), props.L);

         return;
      }
      Xstart = Xend;
   }
   ATLASSERT(false); // should never get here... is X out of range?
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

Float64 stbGirder::GetPrecamber() const
{
   return m_Precamber;
}

void stbGirder::SetPrecamber(Float64 precamber)
{
   m_Precamber = precamber;
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

   m_Camber = 0;
   m_CamberMultiplier = 1.0;

   m_bIncludeRollAxisLateralOffset = false;
   m_LateralCamber = 0.0;

   m_Ll = 0;
   m_Lr = 0;

   m_SweepTolerance = 0;
   m_SweepGrowth = 0.0;
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

   if (m_vFpe != other.m_vFpe)
      return false;

   if ( !IsEqual(m_Camber,other.m_Camber) )
      return false;

   if (!IsEqual(m_CamberMultiplier, other.m_CamberMultiplier))
      return false;

   if (m_bIncludeRollAxisLateralOffset != other.m_bIncludeRollAxisLateralOffset)
      return false;

   if (!IsEqual(m_LateralCamber, other.m_LateralCamber))
      return false;

   if ( !IsEqual(m_Ll,other.m_Ll) )
      return false;

   if ( !IsEqual(m_Lr,other.m_Lr) )
      return false;

   if ( !IsEqual(m_SweepTolerance,other.m_SweepTolerance) )
      return false;

   if (!IsEqual(m_SweepGrowth, other.m_SweepGrowth))
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

IndexType stbStabilityProblemImp::FindFpe(LPCTSTR lpszName) const
{
   std::_tstring strName(lpszName);
   IndexType index = 0;
   auto iter  = std::begin(m_vFpe);
   const auto end = std::end(m_vFpe);
   for (; iter != end; iter++, index++)
   {
      if (iter->first == strName)
      {
         return index;
      }
   }
   return INVALID_INDEX;
}

std::vector<LPCTSTR> stbStabilityProblemImp::GetPrestressNames() const
{
   std::vector<LPCTSTR> vNames;
   vNames.reserve(m_vFpe.size());
   std::transform(std::begin(m_vFpe), std::end(m_vFpe), std::back_inserter(vNames), [](const auto& item) {return item.first.c_str(); });
   return vNames;
}

IndexType stbStabilityProblemImp::GetFpeCount(LPCTSTR strName) const
{
   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
      return 0;

   return m_vFpe[idx].second.size();
}

void stbStabilityProblemImp::ClearFpe()
{
   m_vFpe.clear();
}

void stbStabilityProblemImp::AddFpe(LPCTSTR strName,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps)
{
   stbFpe fpe;
   fpe.X = X;
   fpe.fpe = Fpe;
   fpe.Xps = Xps;
   fpe.Yps = Yps;

   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
   {
      std::set<stbFpe> sFpe;
      m_vFpe.push_back(std::make_pair(strName, sFpe));
      idx = (IndexType)m_vFpe.size() - 1;
   }

   m_vFpe[idx].second.insert(fpe);
}

bool stbStabilityProblemImp::SetFpe(LPCTSTR strName,IndexType fpeIdx,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps)
{
   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
   {
      // strName is not in the container
      ATLASSERT(false);
      return false;
   }

   ATLASSERT(fpeIdx < m_vFpe[idx].second.size());

   auto iter(m_vFpe[idx].second.begin());
   for ( IndexType i = 0; i < fpeIdx; i++)
   {
      iter++;
   }

   // set values can't be modified because it could change the sort order... however
   // we are only sorting on one element of stbFpe and it isn't being changed here
   // cast away const so we can modify the relavent paramenters of fpe
   stbFpe& fpe(const_cast<stbFpe&>(*iter));

   fpe.fpe = Fpe;
   fpe.Xps = Xps;
   fpe.Yps = Yps;

   return true;
}

bool stbStabilityProblemImp::GetFpe(LPCTSTR strName,IndexType fpeIdx,Float64* pX,Float64* pFpe,Float64* pXps,Float64* pYps) const
{
   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
   {
      // strName is not in the container
      ATLASSERT(false);
      *pX = 0;
      *pFpe = 0;
      *pXps = 0;
      *pYps = 0;
      return false;
   }

   ATLASSERT(fpeIdx < m_vFpe[idx].second.size());

   auto iter(m_vFpe[idx].second.begin());
   for (IndexType i = 0; i < fpeIdx; i++)
   {
      iter++;
   }

   *pX = iter->X;
   *pFpe = iter->fpe;
   *pXps = iter->Xps;
   *pYps = iter->Yps;

   return true;
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

void stbStabilityProblemImp::SetCamber(Float64 camber)
{
   m_Camber = camber;
}

void stbStabilityProblemImp::SetCamberMultiplier(Float64 m)
{
   m_CamberMultiplier = m;
}

void stbStabilityProblemImp::SetLateralCamber(Float64 camber)
{
   m_LateralCamber = camber;
}

void stbStabilityProblemImp::IncludeLateralRollAxisOffset(bool bInclude)
{
   m_bIncludeRollAxisLateralOffset = bInclude;
}

Float64 stbStabilityProblemImp::GetCamberMultiplier() const
{
   return m_CamberMultiplier;
}

Float64 stbStabilityProblemImp::GetLateralCamber() const
{
   return m_LateralCamber;
}

bool stbStabilityProblemImp::IncludeLateralRollAxisOffset() const
{
   return m_bIncludeRollAxisLateralOffset;
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

void stbStabilityProblemImp::SetSweepGrowth(Float64 sweepGrowth)
{
   m_SweepGrowth = sweepGrowth;
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

bool stbStabilityProblemImp::GetFpe(LPCTSTR strName,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const
{
   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
   {
      // strName is not in the container
      ATLASSERT(false);
      *pFpe = 0;
      *pXps = 0;
      *pYps = 0;
      return false;
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
   auto first = m_vFpe[idx].second.begin();
   if ( ::IsLE(X,first->X) )
   {
      *pFpe = first->fpe;
      *pXps = first->Xps;
      *pYps = first->Yps;

      // adjust for prestress transfer
      *pFpe *= Xfer;

      return true;
   }

   auto last = m_vFpe[idx].second.rbegin();
   if ( ::IsLE(last->X,X) )
   {
      // after end
      *pFpe = last->fpe;
      *pXps = last->Xps;
      *pYps = last->Yps;

      // adjust for prestress transfer
      *pFpe *= Xfer;

      return true;
   }

   // somewhere in the middle
   ATLASSERT(2 <= m_vFpe[idx].second.size());
   std::set<stbFpe>::const_iterator iter1(m_vFpe[idx].second.begin());
   std::set<stbFpe>::const_iterator iter2(iter1);
   iter2++;
   std::set<stbFpe>::const_iterator end(m_vFpe[idx].second.end());
   for ( ; iter2 != end; iter1++, iter2++ )
   {
      Float64 Xstart = iter1->X;
      Float64 Xend   = iter2->X;
      if (::InRange(Xstart,X,Xend) )
      {
         Float64 FpeStart = iter1->fpe;
         Float64 XpsStart = iter1->Xps;
         Float64 YpsStart = iter1->Yps;

         Float64 FpeEnd   = iter2->fpe;
         Float64 XpsEnd   = iter2->Xps;
         Float64 YpsEnd   = iter2->Yps;

         Float64 fpe = ::LinInterp(X-Xstart,FpeStart,FpeEnd,Xend-Xstart);
         Float64 xps = ::LinInterp(X - Xstart, XpsStart, XpsEnd, Xend - Xstart);
         Float64 yps = ::LinInterp(X - Xstart, YpsStart, YpsEnd, Xend - Xstart);
         *pFpe = fpe;
         *pXps = xps;
         *pYps = yps;

         // adjust for prestress transfer
         *pFpe *= Xfer;

         return true;
      }
   }

   ATLASSERT(false); // should never get here
   return false;
}

Float64 stbStabilityProblemImp::GetCamber() const
{
   return m_Camber;
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

Float64 stbStabilityProblemImp::GetSweepGrowth() const
{
   return m_SweepGrowth;
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
   m_XferLength = other.m_XferLength;
   m_Lg = other.m_Lg;

   m_vFpe = other.m_vFpe;
   
   m_Camber = other.m_Camber;
   m_CamberMultiplier = other.m_CamberMultiplier;

   m_bIncludeRollAxisLateralOffset = other.m_bIncludeRollAxisLateralOffset;
   m_LateralCamber = other.m_LateralCamber;

   m_Concrete = other.m_Concrete;

   m_fy = other.m_fy;

   m_Ll = other.m_Ll;
   m_Lr = other.m_Lr;

   m_SweepTolerance = other.m_SweepTolerance;
   m_SweepGrowth = other.m_SweepGrowth;
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

void stbGirder::GetStressPoints(const stbSectionProperties& props, stbTypes::Section section, gpPoint2d* pTL, gpPoint2d* pTR, gpPoint2d* pBL, gpPoint2d* pBR) const
{
   if (props.m_pStressPoints)
   {
      *pTL = props.m_pStressPoints->pntTL[section];
      *pTR = props.m_pStressPoints->pntTR[section];
      *pBL = props.m_pStressPoints->pntBL[section];
      *pBR = props.m_pStressPoints->pntBR[section];
   }
   else
   {
      pTL->X() = (props.Wbf[section] < props.Wtf[section] ? -props.Xleft[section] : props.Wbf[section] / 2 - props.Xleft[section] - props.Wtf[section] / 2);
      pTL->Y() = -props.Ytop[section];

      pTR->X() = (props.Wbf[section] < props.Wtf[section] ? props.Wtf[section] - props.Xleft[section] : props.Wtf[section] / 2 - props.Xleft[section] + props.Wbf[section] / 2);
      pTR->Y() = -props.Ytop[section];

      pBL->X() = (props.Wbf[section] < props.Wtf[section] ? props.Wtf[section] / 2 - props.Xleft[section] - props.Wbf[section] / 2 : -props.Xleft[section]);
      pBL->Y() = -(props.Ytop[section] + props.Hg[section]);

      pBR->X() = (props.Wbf[section] < props.Wtf[section] ? props.Wbf[section] / 2 - props.Xleft[section] + props.Wtf[section] / 2 : props.Wbf[section] - props.Xleft[section]);
      pBR->Y() = -(props.Ytop[section] + props.Hg[section]);
   }
}

////////////////////////////////


stbLiftingStabilityProblem::stbLiftingStabilityProblem()
{
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

void stbLiftingStabilityProblem::MakeCopy(const stbLiftingStabilityProblem& other)
{
   m_Imp = other.m_Imp;
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
   m_Radius = Float64_Max;
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

