///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <Stability/StabilityProblemImp.h>
#include <WBFLGenericBridge.h> // for ISegment
#include <Units\Units.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Stability;

Girder::Girder()
{
}

Girder::~Girder()
{
}

bool Girder::operator==(const Girder& other) const
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

   if (!IsEqual(m_exb, other.m_exb))
      return false;

   if (!IsEqual(m_Wb, other.m_Wb))
      return false;

   return true;
}

bool Girder::operator!=(const Girder& other) const
{
   return !(*this == other);
}

void Girder::SetSegment(ISegment* pSegment)
{
   m_pSegment = pSegment;
}

void Girder::GetSegment(ISegment** ppSegment) const
{
   (*ppSegment) = m_pSegment;
   if ( m_pSegment )
   {
      (*ppSegment)->AddRef();
   }
}

void Girder::ClearSections()
{
   m_vSectionProperties.clear();
}

IndexType Girder::AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf)
{
   return AddSection(Length, Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf, Ag, Ixx, Iyy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf);
}

IndexType Girder::AddSection(Float64 Length, Float64 Ag, Float64 Ixx, Float64 Iyy, Float64 Ixy, Float64 Xleft, Float64 Ytop, Float64 Hg, Float64 Wtf, Float64 Wbf, Float64 Ag2, Float64 Ixx2, Float64 Iyy2, Float64 Ixy2, Float64 Xcg2, Float64 Ycg2, Float64 Hg2, Float64 Wtf2, Float64 Wbf2)
{
   SectionProperties props;
   props.Ag[+Section::Start] = Ag;
   props.Ag[+Section::End] = Ag2;

   props.Ixx[+Section::Start] = Ixx;
   props.Ixx[+Section::End] = Ixx2;

   props.Iyy[+Section::Start] = Iyy;
   props.Iyy[+Section::End] = Iyy2;

   props.Ixy[+Section::Start] = Ixy;
   props.Ixy[+Section::End] = Ixy2;

   props.Xleft[+Section::Start] = Xleft;
   props.Xleft[+Section::End] = Xcg2;

   props.Ytop[+Section::Start] = Ytop;
   props.Ytop[+Section::End] = Ycg2;

   props.Hg[+Section::Start] = Hg;
   props.Hg[+Section::End] = Hg2;

   props.Wtf[+Section::Start] = Wtf;
   props.Wtf[+Section::End] = Wtf2;

   props.Wbf[+Section::Start] = Wbf;
   props.Wbf[+Section::End] = Wbf2;

   props.L = Length;

   IndexType index = m_vSectionProperties.size();
   m_vSectionProperties.push_back(props);

   m_bLengthNeedsUpdate = true;

   return index;
}

void Girder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy,Float64 Xleft,Float64 Ytop,Float64 Hg,Float64 Wtf,Float64 Wbf)
{
   SetSectionProperties(sectIdx,Length,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf,Ag,Ixx,Iyy,Ixy,Xleft,Ytop,Hg,Wtf,Wbf);
}

void Girder::SetSectionProperties(IndexType sectIdx,Float64 Length,Float64 Ag,Float64 Ixx,Float64 Iyy,Float64 Ixy,Float64 Xleft,Float64 Ytop,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ixx2,Float64 Iyy2,Float64 Ixy2,Float64 Xcg2,Float64 Ycg2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2)
{
   SectionProperties& props = m_vSectionProperties[sectIdx];
   props.L = Length;
   props.Ag[+Section::Start] = Ag;
   props.Ixx[+Section::Start] = Ixx;
   props.Iyy[+Section::Start] = Iyy;
   props.Ixy[+Section::Start] = Ixy;
   props.Xleft[+Section::Start] = Xleft;
   props.Ytop[+Section::Start] = Ytop;
   props.Hg[+Section::Start] = Hg;
   props.Wtf[+Section::Start] = Wtf;
   props.Wbf[+Section::Start] = Wbf;

   props.Ag[+Section::End] = Ag2;
   props.Ixx[+Section::End] = Ixx2;
   props.Iyy[+Section::End] = Iyy2;
   props.Ixy[+Section::End] = Ixy2;
   props.Xleft[+Section::End] = Xcg2;
   props.Ytop[+Section::End] = Ycg2;
   props.Hg[+Section::End] = Hg2;
   props.Wtf[+Section::End] = Wtf2;
   props.Wbf[+Section::End] = Wbf2;

   m_bLengthNeedsUpdate = true;
}

// Assigns stress point values to a section. 
void Girder::SetStressPoints(IndexType sectIdx, const Point& pntTL, const Point& pntTR, const Point& pntBL, const Point& pntBR)
{
   SetStressPoints(sectIdx, pntTL, pntTR, pntBL, pntBR, pntTL, pntTR, pntBL, pntBR);
}

void Girder::SetStressPoints(IndexType sectIdx, const Point& pntTL, const Point& pntTR, const Point& pntBL, const Point& pntBR, const Point& pntTL2, const Point& pntTR2, const Point& pntBL2, const Point& pntBR2)
{
   SectionProperties& props = m_vSectionProperties[sectIdx];
   if (props.m_pStressPoints == nullptr)
   {
      // stress points have not yet been assigned
      props.m_pStressPoints = std::make_shared<StressPoints>();
   }
   props.m_pStressPoints->pntTL[+Section::Start] = pntTL;
   props.m_pStressPoints->pntTR[+Section::Start] = pntTR;
   props.m_pStressPoints->pntBL[+Section::Start] = pntBL;
   props.m_pStressPoints->pntBR[+Section::Start] = pntBR;

   props.m_pStressPoints->pntTL[+Section::End] = pntTL2;
   props.m_pStressPoints->pntTR[+Section::End] = pntTR2;
   props.m_pStressPoints->pntBL[+Section::End] = pntBL2;
   props.m_pStressPoints->pntBR[+Section::End] = pntBR2;
}

void Girder::ClearPointLoads()
{
   m_vPointLoads.clear();
}

void Girder::AddPointLoad(Float64 X,Float64 P)
{
   m_vPointLoads.emplace_back(X,P);
}

Float64 Girder::GetGirderLength() const
{
   UpdateLength();
   return m_L;
}

IndexType Girder::GetSectionCount() const
{
   return m_vSectionProperties.size();
}

Float64 Girder::GetSectionLength(IndexType sectIdx) const
{
   return m_vSectionProperties[sectIdx].L;
}

void Girder::GetSectionProperties(IndexType sectIdx,Section section,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   const SectionProperties& props = m_vSectionProperties[sectIdx];
   *pAg = props.Ag[+section];
   *pIxx = props.Ixx[+section];
   *pIyy = props.Iyy[+section];
   *pIxy = props.Ixy[+section];
   *pXleft = props.Xleft[+section];
   *pYtop = props.Ytop[+section];
   *pHg = props.Hg[+section];
   *pWtop = props.Wtf[+section];
   *pWbot = props.Wbf[+section];
}

void Girder::GetSectionProperties(Float64 X,Float64* pAg,Float64* pIxx,Float64* pIyy,Float64* pIxy,Float64* pXleft,Float64* pYtop,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   ATLASSERT(m_vSectionProperties.size() != 0);

   if ( m_vSectionProperties.size() == 1 )
   {
      const SectionProperties& props = m_vSectionProperties.front();
      *pAg = ::LinInterp(X,props.Ag[+Section::Start],props.Ag[+Section::End],props.L);
      *pIxx = ::LinInterp(X,props.Ixx[+Section::Start],props.Ixx[+Section::End],props.L);
      *pIyy = ::LinInterp(X,props.Iyy[+Section::Start],props.Iyy[+Section::End],props.L);
      *pIxy = ::LinInterp(X, props.Ixy[+Section::Start], props.Ixy[+Section::End], props.L);
      *pXleft = ::LinInterp(X, props.Xleft[+Section::Start], props.Xleft[+Section::End], props.L);
      *pYtop = ::LinInterp(X, props.Ytop[+Section::Start], props.Ytop[+Section::End], props.L);
      *pHg = ::LinInterp(X,props.Hg[+Section::Start],props.Hg[+Section::End],props.L);
      *pWtop = ::LinInterp(X,props.Wtf[+Section::Start],props.Wtf[+Section::End],props.L);
      *pWbot = ::LinInterp(X,props.Wbf[+Section::Start],props.Wbf[+Section::End],props.L);
      return;
   }

   Float64 Xstart = 0;
   for (const auto& properties : m_vSectionProperties)
   {
      Float64 Xend = Xstart + properties.L;
      if ( ::InRange(Xstart,X,Xend) )
      {
         *pAg = ::LinInterp(X-Xstart,properties.Ag[+Section::Start],properties.Ag[+Section::End],properties.L);
         *pIxx = ::LinInterp(X-Xstart,properties.Ixx[+Section::Start],properties.Ixx[+Section::End],properties.L);
         *pIyy = ::LinInterp(X - Xstart, properties.Iyy[+Section::Start], properties.Iyy[+Section::End], properties.L);
         *pIxy = ::LinInterp(X - Xstart, properties.Ixy[+Section::Start], properties.Ixy[+Section::End], properties.L);
         *pXleft = ::LinInterp(X - Xstart, properties.Xleft[+Section::Start], properties.Xleft[+Section::End], properties.L);
         *pYtop = ::LinInterp(X - Xstart, properties.Ytop[+Section::Start], properties.Ytop[+Section::End], properties.L);
         *pHg = ::LinInterp(X-Xstart,properties.Hg[+Section::Start],properties.Hg[+Section::End],properties.L);
         *pWtop = ::LinInterp(X-Xstart,properties.Wtf[+Section::Start],properties.Wtf[+Section::End],properties.L);
         *pWbot = ::LinInterp(X-Xstart,properties.Wbf[+Section::Start],properties.Wbf[+Section::End],properties.L);
         return;
      }
      Xstart = Xend;
   }

   ATLASSERT(false); // should never get here.... is X out of range?
}

void Girder::GetStressPoints(IndexType sectIdx, Section section, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const
{
   const SectionProperties& props = m_vSectionProperties[sectIdx];
   GetStressPoints(props, section, pTL, pTR, pBL, pBR);
}

void Girder::GetStressPoints(Float64 X, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const
{
   Float64 Xstart = 0;
   for (const auto& props : m_vSectionProperties)
   {
      Float64 Xend = Xstart + props.L;
      if (::InRange(Xstart, X, Xend))
      {
         Point tl1, tr1, bl1, br1;
         GetStressPoints(props, Section::Start, &tl1, &tr1, &bl1, &br1);

         Point tl2, tr2, bl2, br2;
         GetStressPoints(props, Section::End, &tl2, &tr2, &bl2, &br2);

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

void Girder::SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads)
{
   m_vPointLoads = vLoads;
}

std::vector<std::pair<Float64,Float64>> Girder::GetAdditionalLoads() const
{
   return m_vPointLoads;
}

Float64 Girder::GetDragCoefficient() const
{
   return m_DragCoefficient;
}

void Girder::SetDragCoefficient(Float64 Cd)
{
   m_DragCoefficient = Cd;
}

Float64 Girder::GetPrecamber() const
{
   return m_Precamber;
}

void Girder::SetPrecamber(Float64 precamber)
{
   m_Precamber = precamber;
}

void Girder::UpdateLength() const
{
   if ( m_bLengthNeedsUpdate )
   {
      Float64 L = 0;
      std::vector<SectionProperties>::const_iterator iter(m_vSectionProperties.begin());
      std::vector<SectionProperties>::const_iterator end(m_vSectionProperties.end());
      for ( ; iter != end; iter++ )
      {
         const SectionProperties& sp(*iter);
         L += sp.L;
      }
      m_L = L;
      m_bLengthNeedsUpdate = false;
   }
}

/////////////////////////////////////////////////////
StabilityProblemImp::StabilityProblemImp()
{
}

StabilityProblemImp::StabilityProblemImp(const StabilityProblemImp& other)
{
   *this = other;
}

StabilityProblemImp::~StabilityProblemImp()
{
   ClearAnalysisPoints();
}

StabilityProblemImp& StabilityProblemImp::operator=(const StabilityProblemImp& other)
{
   // because analysis points are unique points, we need to do a deep copy
   m_vAnalysisPoints.clear();
   for (auto& analysisPoint : other.m_vAnalysisPoints)
   {
      m_vAnalysisPoints.emplace_back(std::move(analysisPoint->Clone()));
   }

   m_bAdjustForXferLength = other.m_bAdjustForXferLength;
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

   m_eb = other.m_eb;
   m_Wb = other.m_Wb;

   return *this;
}

bool StabilityProblemImp::operator==(const StabilityProblemImp& other) const
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

   if (!IsEqual(m_WindLoad, other.m_WindLoad))
      return false;

   if (!IsEqual(m_eb, other.m_eb))
      return false;

   if (!IsEqual(m_Wb, other.m_Wb))
      return false;

   return true;
}

bool StabilityProblemImp::operator!=(const StabilityProblemImp& other) const
{
   return !(*this == other);
}

IndexType StabilityProblemImp::FindFpe(LPCTSTR lpszName) const
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

std::vector<LPCTSTR> StabilityProblemImp::GetPrestressNames() const
{
   std::vector<LPCTSTR> vNames;
   vNames.reserve(m_vFpe.size());
   std::transform(std::begin(m_vFpe), std::end(m_vFpe), std::back_inserter(vNames), [](const auto& item) {return item.first.c_str(); });
   return vNames;
}

IndexType StabilityProblemImp::GetFpeCount(LPCTSTR strName) const
{
   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
      return 0;

   return m_vFpe[idx].second.size();
}

void StabilityProblemImp::ClearFpe()
{
   m_vFpe.clear();
}

void StabilityProblemImp::AddFpe(LPCTSTR strName,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps)
{
   WBFL::Stability::Fpe fpe;
   fpe.X = X;
   fpe.fpe = Fpe;
   fpe.Xps = Xps;
   fpe.Yps = Yps;

   IndexType idx = FindFpe(strName);
   if (idx == INVALID_INDEX)
   {
      std::set<WBFL::Stability::Fpe> sFpe;
      m_vFpe.push_back(std::make_pair(strName, sFpe));
      idx = (IndexType)m_vFpe.size() - 1;
   }

   m_vFpe[idx].second.insert(fpe);
}

bool StabilityProblemImp::SetFpe(LPCTSTR strName,IndexType fpeIdx,Float64 X,Float64 Fpe,Float64 Xps,Float64 Yps)
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
   // we are only sorting on one element of Fpe and it isn't being changed here
   // cast away const so we can modify the relevant parameters of fpe
   WBFL::Stability::Fpe& fpe(const_cast<WBFL::Stability::Fpe&>(*iter));

   fpe.fpe = Fpe;
   fpe.Xps = Xps;
   fpe.Yps = Yps;

   return true;
}

bool StabilityProblemImp::GetFpe(LPCTSTR strName,IndexType fpeIdx,Float64* pX,Float64* pFpe,Float64* pXps,Float64* pYps) const
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

bool StabilityProblemImp::AdjustForXferLength() const
{
   return m_bAdjustForXferLength;
}

void StabilityProblemImp::AdjustForXferLength(bool bAdjust)
{
   m_bAdjustForXferLength = bAdjust;
}

void StabilityProblemImp::SetXferLength(Float64 xferLength,Float64 Lg)
{
   m_XferLength = xferLength;
   m_Lg = Lg;
}

Float64 StabilityProblemImp::GetXferLength() const
{
   return m_XferLength;
}

void StabilityProblemImp::SetCamber(Float64 camber)
{
   m_Camber = camber;
}

void StabilityProblemImp::SetCamberMultiplier(Float64 m)
{
   m_CamberMultiplier = m;
}

void StabilityProblemImp::SetLateralCamber(Float64 camber)
{
   m_LateralCamber = camber;
}

void StabilityProblemImp::IncludeLateralRollAxisOffset(bool bInclude)
{
   m_bIncludeRollAxisLateralOffset = bInclude;
}

Float64 StabilityProblemImp::GetCamberMultiplier() const
{
   return m_CamberMultiplier;
}

Float64 StabilityProblemImp::GetLateralCamber() const
{
   return m_LateralCamber;
}

bool StabilityProblemImp::IncludeLateralRollAxisOffset() const
{
   return m_bIncludeRollAxisLateralOffset;
}

const WBFL::Materials::SimpleConcrete& StabilityProblemImp::GetConcrete() const
{
   return m_Concrete;
}

WBFL::Materials::SimpleConcrete& StabilityProblemImp::GetConcrete()
{
   return m_Concrete;
}

void StabilityProblemImp::SetConcrete(const WBFL::Materials::SimpleConcrete& concrete)
{
   m_Concrete = concrete;
}

Float64 StabilityProblemImp::GetRebarYieldStrength() const
{
   return m_fy;
}

void StabilityProblemImp::SetRebarYieldStrength(Float64 fy)
{
   m_fy = fy;
}

void StabilityProblemImp::SetSupportLocations(Float64 Ll,Float64 Lr)
{
   m_Ll = Ll;
   m_Lr = Lr;
}

void StabilityProblemImp::SetYRollAxis(Float64 Yra)
{
   m_Yra = Yra;
}

void StabilityProblemImp::SetSweepTolerance(Float64 sweepTolerance)
{
   m_SweepTolerance = sweepTolerance;
}

void StabilityProblemImp::SetSweepGrowth(Float64 sweepGrowth)
{
   m_SweepGrowth = sweepGrowth;
}

void StabilityProblemImp::SetSupportPlacementTolerance(Float64 spt)
{
   m_SupportPlacementTolerance = spt;
}

void StabilityProblemImp::SetImpact(Float64 up,Float64 down)
{
   m_ImpactUp = up;
   m_ImpactDown = down;
}

bool StabilityProblemImp::GetFpe(LPCTSTR strName,Float64 X,Float64* pFpe,Float64* pXps,Float64* pYps) const
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
   std::set<Fpe>::const_iterator iter1(m_vFpe[idx].second.begin());
   std::set<Fpe>::const_iterator iter2(iter1);
   iter2++;
   std::set<Fpe>::const_iterator end(m_vFpe[idx].second.end());
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

Float64 StabilityProblemImp::GetCamber() const
{
   return m_Camber;
}

void StabilityProblemImp::GetSupportLocations(Float64* pLeft,Float64* pRight) const
{
   *pLeft = m_Ll;
   *pRight = m_Lr;
}

Float64 StabilityProblemImp::GetYRollAxis() const
{
   return m_Yra;
}

Float64 StabilityProblemImp::GetSweepTolerance() const
{
   return m_SweepTolerance;
}

Float64 StabilityProblemImp::GetSweepGrowth() const
{
   return m_SweepGrowth;
}

Float64 StabilityProblemImp::GetSupportPlacementTolerance() const
{
   return m_SupportPlacementTolerance;
}

void StabilityProblemImp::GetImpact(Float64* pIMup,Float64* pIMdown) const
{
   *pIMup   = m_ImpactUp;
   *pIMdown = m_ImpactDown;
}

void StabilityProblemImp::GetWindLoading(WindType* pType,Float64* pLoad) const
{
   *pType = m_WindLoadType;
   *pLoad = m_WindLoad;
}

void StabilityProblemImp::SetWindLoading(WindType type,Float64 load)
{
   m_WindLoadType = type;
   m_WindLoad = load;
}

void StabilityProblemImp::SetAppurtenanceLoading(Float64 ex, Float64 W)
{
   m_eb = ex;
   m_Wb = W;
}

void StabilityProblemImp::GetAppurtenanceLoading(Float64* pex, Float64* pW) const
{
   *pex = m_eb;
   *pW = m_Wb;
}

void StabilityProblemImp::ClearAnalysisPoints()
{
   m_vAnalysisPoints.clear();
}

bool SortAnalysisPoints(const std::unique_ptr<IAnalysisPoint>& pA,const std::unique_ptr<IAnalysisPoint>& pB)
{
   return (pA->GetLocation() < pB->GetLocation());
}

void StabilityProblemImp::AddAnalysisPoint(std::unique_ptr<IAnalysisPoint>&& pAnalysisPoint)
{
   m_vAnalysisPoints.emplace_back(std::move(pAnalysisPoint.release()));
   std::sort(m_vAnalysisPoints.begin(),m_vAnalysisPoints.end(),SortAnalysisPoints);
   //m_vAnalysisPoints.erase(std::unique(m_vAnalysisPoints.begin(),m_vAnalysisPoints.end(),IsEqual),m_vAnalysisPoints.end());
}

const std::vector<std::unique_ptr<IAnalysisPoint>>& StabilityProblemImp::GetAnalysisPoints() const
{
   return m_vAnalysisPoints;
}

const std::unique_ptr<IAnalysisPoint>& StabilityProblemImp::GetAnalysisPoint(IndexType idx) const
{
   return m_vAnalysisPoints[idx];
}

bool StabilityProblemImp::CompareAnalysisPoints(const StabilityProblemImp& other) const
{
   if ( m_vAnalysisPoints.size() != other.m_vAnalysisPoints.size() )
      return false;

   auto thisIter(m_vAnalysisPoints.begin());
   auto thisIterEnd(m_vAnalysisPoints.end());
   auto otherIter(other.m_vAnalysisPoints.begin());
   for ( ; thisIter != thisIterEnd; thisIter++, otherIter++ )
   {
      auto& pA(*thisIter);
      auto& pB(*otherIter);
      if ( !::IsEqual(pA->GetLocation(),pB->GetLocation()) )
      {
         return false;
      }
   }

   return true;
}

void Girder::GetStressPoints(const SectionProperties& props, Section section, Point* pTL, Point* pTR, Point* pBL, Point* pBR) const
{
   if (props.m_pStressPoints)
   {
      *pTL = props.m_pStressPoints->pntTL[+section];
      *pTR = props.m_pStressPoints->pntTR[+section];
      *pBL = props.m_pStressPoints->pntBL[+section];
      *pBR = props.m_pStressPoints->pntBR[+section];
   }
   else
   {
      pTL->X() = (props.Wbf[+section] < props.Wtf[+section] ? -props.Xleft[+section] : props.Wbf[+section] / 2 - props.Xleft[+section] - props.Wtf[+section] / 2);
      pTL->Y() = -props.Ytop[+section];

      pTR->X() = (props.Wbf[+section] < props.Wtf[+section] ? props.Wtf[+section] - props.Xleft[+section] : props.Wtf[+section] / 2 - props.Xleft[+section] + props.Wbf[+section] / 2);
      pTR->Y() = -props.Ytop[+section];

      pBL->X() = (props.Wbf[+section] < props.Wtf[+section] ? props.Wtf[+section] / 2 - props.Xleft[+section] - props.Wbf[+section] / 2 : -props.Xleft[+section]);
      pBL->Y() = -(props.Ytop[+section] + props.Hg[+section]);

      pBR->X() = (props.Wbf[+section] < props.Wtf[+section] ? props.Wbf[+section] / 2 - props.Xleft[+section] + props.Wtf[+section] / 2 : props.Wbf[+section] - props.Xleft[+section]);
      pBR->Y() = -(props.Ytop[+section] + props.Hg[+section]);
   }
}

////////////////////////////////

LiftingStabilityProblem::LiftingStabilityProblem()
{
}

LiftingStabilityProblem::~LiftingStabilityProblem()
{
}

bool LiftingStabilityProblem::operator==(const LiftingStabilityProblem& other) const
{
   if ( !IsEqual(m_LiftAngle,other.m_LiftAngle) )
      return false;

   if ( m_Imp != other.m_Imp )
      return false;

   return true;
}

bool LiftingStabilityProblem::operator!=(const LiftingStabilityProblem& other) const
{
   return !(*this == other);
}

void LiftingStabilityProblem::SetLiftAngle(Float64 liftAngle)
{
   m_LiftAngle = liftAngle;
}

Float64 LiftingStabilityProblem::GetLiftAngle() const
{
   return m_LiftAngle;
}

//////////////////////////////////
HaulingStabilityProblem::HaulingStabilityProblem()
{
}

HaulingStabilityProblem::~HaulingStabilityProblem()
{
}

bool HaulingStabilityProblem::operator==(const HaulingStabilityProblem& other) const
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

bool HaulingStabilityProblem::operator!=(const HaulingStabilityProblem& other) const
{
   return !(*this == other);
}

void HaulingStabilityProblem::SetImpactUsage(HaulingImpact impactUsage)
{
   m_ImpactUsage = impactUsage;
}

HaulingImpact HaulingStabilityProblem::GetImpactUsage() const
{
   return m_ImpactUsage;
}

void HaulingStabilityProblem::SetRotationalStiffness(Float64 Ktheta)
{
   m_Ktheta = Ktheta;
}

Float64 HaulingStabilityProblem::GetRotationalStiffness() const
{
   return m_Ktheta;
}

void HaulingStabilityProblem::SetSupportWidth(Float64 Wcc)
{
   m_Wcc = Wcc;
}

Float64 HaulingStabilityProblem::GetSupportWidth() const
{
   return m_Wcc;
}

void HaulingStabilityProblem::SetHeightOfRollAxis(Float64 Hrs)
{
   m_Hrc = Hrs;
}

Float64 HaulingStabilityProblem::GetHeightOfRollAxis() const
{
   return m_Hrc;
}

void HaulingStabilityProblem::SetSupportSlope(Float64 crown)
{
   m_CrownSlope = crown;
}

Float64 HaulingStabilityProblem::GetSupportSlope() const
{
   return m_CrownSlope;
}

void HaulingStabilityProblem::SetSuperelevation(Float64 alpha)
{
   m_Superelevation = alpha;
}

Float64 HaulingStabilityProblem::GetSuperelevation() const
{
   return m_Superelevation;
}

void HaulingStabilityProblem::SetVelocity(Float64 velocity)
{
   m_Velocity = velocity;
}

Float64 HaulingStabilityProblem::GetVelocity() const
{
   return m_Velocity;
}

void HaulingStabilityProblem::SetTurningRadius(Float64 r)
{
   m_Radius = r;
}

Float64 HaulingStabilityProblem::GetTurningRadius() const
{
   return m_Radius;
}

void HaulingStabilityProblem::SetCentrifugalForceType(CFType cfType)
{
   m_CFType = cfType;
}

CFType HaulingStabilityProblem::GetCentrifugalForceType() const
{
   return m_CFType;
}

//////////////////////////////////
OneEndSeatedStabilityProblem::OneEndSeatedStabilityProblem()
{
}

OneEndSeatedStabilityProblem::~OneEndSeatedStabilityProblem()
{
}

bool OneEndSeatedStabilityProblem::operator==(const OneEndSeatedStabilityProblem& other) const
{
   if (m_Imp != other.m_Imp)
      return false;

   if (m_SeatedEnd != other.m_SeatedEnd)
      return false;

   if (!IsEqual(m_Ktheta, other.m_Ktheta))
      return false;

   if (!IsEqual(m_Wcc, other.m_Wcc))
      return false;

   if (!IsEqual(m_Hrc, other.m_Hrc))
      return false;

   if (!IsEqual(m_CrownSlope, other.m_CrownSlope))
      return false;

   if (!IsEqual(m_Kadjust, other.m_Kadjust))
      return false;

   return true;
}

bool OneEndSeatedStabilityProblem::operator!=(const OneEndSeatedStabilityProblem& other) const
{
   return !(*this == other);
}

void OneEndSeatedStabilityProblem::SetRotationalStiffness(Float64 Ktheta)
{
   m_Ktheta = Ktheta;
}

Float64 OneEndSeatedStabilityProblem::GetRotationalStiffness() const
{
   return m_Ktheta;
}

void OneEndSeatedStabilityProblem::SetSupportWidth(Float64 Wcc)
{
   m_Wcc = Wcc;
}

Float64 OneEndSeatedStabilityProblem::GetSupportWidth() const
{
   return m_Wcc;
}

void OneEndSeatedStabilityProblem::SetHeightOfRollAxis(Float64 Hrs)
{
   m_Hrc = Hrs;
}

Float64 OneEndSeatedStabilityProblem::GetHeightOfRollAxis() const
{
   return m_Hrc;
}

void OneEndSeatedStabilityProblem::SetSupportSlope(Float64 crown)
{
   m_CrownSlope = crown;
}

Float64 OneEndSeatedStabilityProblem::GetSupportSlope() const
{
   return m_CrownSlope;
}

void OneEndSeatedStabilityProblem::SetSeatedEnd(GirderSide end)
{
   m_SeatedEnd = end;
}

GirderSide OneEndSeatedStabilityProblem::GetSeatedEnd() const
{
   return m_SeatedEnd;
}

void OneEndSeatedStabilityProblem::SetYRollLiftEnd(Float64 Yroll)
{
   m_YrollLiftEnd = Yroll;
}

Float64 OneEndSeatedStabilityProblem::GetYRollLiftEnd() const
{
   return m_YrollLiftEnd;
}

void OneEndSeatedStabilityProblem::SetLiftPlacementTolerance(Float64 elift)
{
   m_elift = elift;
}

Float64 OneEndSeatedStabilityProblem::GetLiftPlacementTolerance() const
{
   return m_elift;
}

void OneEndSeatedStabilityProblem::SetRotationalStiffnessAdjustmentFactor(Float64 k)
{
   m_Kadjust = k;
}

Float64 OneEndSeatedStabilityProblem::GetRotationalStiffnessAdjustmentFactor() const
{
   return m_Kadjust;
}
