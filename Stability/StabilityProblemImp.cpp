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
#include <Stability\StabilityProblemImp.h>
#include <UnitMgt\UnitMgt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool operator<(const stbFpe& a,const stbFpe& b) { return a.X < b.X; }

stbGirder::stbGirder()
{
   m_Density = 0;
   m_Ystraight = 0;
   for ( int i = 0; i < 4; i++ )
   {
      m_Yharp[i] = 0;
      m_Xharp[i] = 0;
   }
   m_Ytemp = 0; // location of temporary strands, measured from top of girder

   m_bNeedsUpdate = true;
}

stbGirder::~stbGirder()
{
}

bool stbGirder::operator==(const stbGirder& other) const
{
   if ( m_vSectionProperties != other.m_vSectionProperties )
      return false;

   if ( m_vPointLoads != other.m_vPointLoads )
      return false;

   if ( !IsEqual(m_Density,other.m_Density) )
      return false;

   if ( !IsEqual(m_Ystraight,other.m_Ystraight) )
      return false;

   if ( !IsEqual(m_Ytemp,other.m_Ytemp) )
      return false;

   for ( int i = 0; i < 4; i++ )
   {
      if ( !IsEqual(m_Yharp[i],other.m_Yharp[i]) )
         return false;

      if ( !IsEqual(m_Xharp[i],other.m_Xharp[i]) )
         return false;
   }

   return true;
}

bool stbGirder::operator!=(const stbGirder& other) const
{
   return !(*this == other);
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
   props.Ag[SECTION_START] = Ag;
   props.Ix[SECTION_START] = Ix;
   props.Iy[SECTION_START] = Iy;
   props.Yt[SECTION_START] = Yt;
   props.Hg[SECTION_START] = Hg;
   props.Wtf[SECTION_START] = Wtf;
   props.Wbf[SECTION_START] = Wbf;

   props.Ag[SECTION_END] = Ag2;
   props.Ix[SECTION_END] = Ix2;
   props.Iy[SECTION_END] = Iy2;
   props.Yt[SECTION_END] = Yt2;
   props.Hg[SECTION_END] = Hg2;
   props.Wtf[SECTION_END] = Wtf2;
   props.Wbf[SECTION_END] = Wbf2;

   m_bNeedsUpdate = true;
}

void stbGirder::AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf)
{
   AddSection(Length,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf,Ag,Ix,Iy,Yt,Hg,Wtf,Wbf);
}

void stbGirder::AddSection(Float64 Length,Float64 Ag,Float64 Ix,Float64 Iy,Float64 Yt,Float64 Hg,Float64 Wtf,Float64 Wbf,Float64 Ag2,Float64 Ix2,Float64 Iy2,Float64 Yt2,Float64 Hg2,Float64 Wtf2,Float64 Wbf2)
{
   stbSectionProperties props;
   props.Ag[SECTION_START] = Ag;
   props.Ag[SECTION_END]   = Ag2;

   props.Ix[SECTION_START] = Ix;
   props.Ix[SECTION_END]   = Ix2;

   props.Iy[SECTION_START] = Iy;
   props.Iy[SECTION_END]   = Iy2;

   props.Yt[SECTION_START] = Yt;
   props.Yt[SECTION_END]   = Yt2;

   props.Hg[SECTION_START] = Hg;
   props.Hg[SECTION_END]   = Hg2;

   props.Wtf[SECTION_START] = Wtf;
   props.Wtf[SECTION_END]   = Wtf2;

   props.Wbf[SECTION_START] = Wbf;
   props.Wbf[SECTION_END]   = Wbf2;

   props.L = Length;

   m_vSectionProperties.push_back(props);

   m_bNeedsUpdate = true;
}

void stbGirder::SetStraightStrandLocation(Float64 Yps)
{
   m_Ystraight = Yps;
}

void stbGirder::SetTemporaryStrandLocation(Float64 Yps)
{
   m_Ytemp = Yps;
}

void stbGirder::SetHarpedStrandLocation(Float64 X1,Float64 Y1,Float64 X2,Float64 Y2,Float64 X3,Float64 Y3,Float64 X4,Float64 Y4)
{
   m_Xharp[LOCATION_START] = X1;
   m_Yharp[LOCATION_START] = Y1;

   m_Xharp[LOCATION_LEFT_HP] = X2;
   m_Yharp[LOCATION_LEFT_HP] = Y2;

   m_Xharp[LOCATION_RIGHT_HP] = X3;
   m_Yharp[LOCATION_RIGHT_HP] = Y3;

   m_Xharp[LOCATION_END] = X4;
   m_Yharp[LOCATION_END] = Y4;
}

Float64 stbGirder::GetStraightStrandLocation() const
{
   return m_Ystraight;
}

Float64 stbGirder::GetTemporaryStrandLocation() const
{
   return m_Ytemp;
}

void stbGirder::GetHarpedStrandLocation(Float64* pX1,Float64* pY1,Float64* pX2,Float64* pY2,Float64* pX3,Float64* pY3,Float64* pX4,Float64* pY4)
{
   *pX1 = m_Xharp[LOCATION_START];
   *pY1 = m_Yharp[LOCATION_START];

   *pX2 = m_Xharp[LOCATION_LEFT_HP];
   *pY2 = m_Yharp[LOCATION_LEFT_HP];

   *pX3 = m_Xharp[LOCATION_RIGHT_HP];
   *pY3 = m_Yharp[LOCATION_RIGHT_HP];

   *pX4 = m_Xharp[LOCATION_END];
   *pY4 = m_Yharp[LOCATION_END];
}

void stbGirder::SetDensity(Float64 density)
{
   m_Density = density;
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
   Update();
   return m_L;
}

Float64 stbGirder::GetGirderWeight() const
{
   Update();
   return m_Wg;
}

IndexType stbGirder::GetSectionCount() const
{
   return m_vSectionProperties.size();
}

void stbGirder::GetSectionProperties(IndexType sectIdx,int face,Float64* pAg,Float64* pIx,Float64* pIy,Float64* pYt,Float64* pHg,Float64* pWtop,Float64* pWbot) const
{
   const stbSectionProperties& props = m_vSectionProperties[sectIdx];
   *pAg = props.Ag[face];
   *pIx = props.Ix[face];
   *pIy = props.Iy[face];
   *pYt = props.Yt[face];
   *pHg = props.Hg[face];
   *pWtop = props.Wtf[face];
   *pWbot = props.Wbf[face];
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
      *pAg = ::LinInterp(X,props.Ag[SECTION_START],props.Ag[SECTION_END],props.L);
      *pIx = ::LinInterp(X,props.Ix[SECTION_START],props.Ix[SECTION_END],props.L);
      *pIy = ::LinInterp(X,props.Iy[SECTION_START],props.Iy[SECTION_END],props.L);
      *pYt = ::LinInterp(X,props.Yt[SECTION_START],props.Yt[SECTION_END],props.L);
      *pHg = ::LinInterp(X,props.Hg[SECTION_START],props.Hg[SECTION_END],props.L);
      *pWtop = ::LinInterp(X,props.Wtf[SECTION_START],props.Wtf[SECTION_END],props.L);
      *pWbot = ::LinInterp(X,props.Wbf[SECTION_START],props.Wbf[SECTION_END],props.L);
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
         *pAg = ::LinInterp(X-Xstart,iter->Ag[SECTION_START],iter->Ag[SECTION_END],Xend-Xstart);
         *pIx = ::LinInterp(X-Xstart,iter->Ix[SECTION_START],iter->Ix[SECTION_END],Xend-Xstart);
         *pIy = ::LinInterp(X-Xstart,iter->Iy[SECTION_START],iter->Iy[SECTION_END],Xend-Xstart);
         *pYt = ::LinInterp(X-Xstart,iter->Yt[SECTION_START],iter->Yt[SECTION_END],Xend-Xstart);
         *pHg = ::LinInterp(X-Xstart,iter->Hg[SECTION_START],iter->Hg[SECTION_END],Xend-Xstart);
         *pWtop = ::LinInterp(X-Xstart,iter->Wtf[SECTION_START],iter->Wtf[SECTION_END],Xend-Xstart);
         *pWbot = ::LinInterp(X-Xstart,iter->Wbf[SECTION_START],iter->Wbf[SECTION_END],Xend-Xstart);
         return;
      }
      Xstart = Xend;
   }

   ATLASSERT(false); // should never get here.... is X out of range?
}

Float64 stbGirder::GetStrandLocation(int strandType,Float64 X) const
{
   if ( strandType == STRAIGHT )
   {
      return m_Ystraight;
   }
   else if ( strandType == TEMPORARY )
   {
      return m_Ytemp;
   }
   else
   {
      if ( ::InRange(0.0,X,m_Xharp[LOCATION_START]) )
      {
         return m_Yharp[LOCATION_START];
      }
      else if ( ::InRange(m_Xharp[LOCATION_START],X,m_Xharp[LOCATION_LEFT_HP]) )
      {
         return ::LinInterp(X - m_Xharp[LOCATION_START],m_Yharp[LOCATION_START],m_Yharp[LOCATION_LEFT_HP],m_Xharp[LOCATION_LEFT_HP] - m_Xharp[LOCATION_START]);
      }
      else if ( ::InRange(m_Xharp[LOCATION_LEFT_HP],X,m_Xharp[LOCATION_RIGHT_HP]) )
      {
         return ::LinInterp(X - m_Xharp[LOCATION_LEFT_HP],m_Yharp[LOCATION_LEFT_HP],m_Yharp[LOCATION_RIGHT_HP],m_Xharp[LOCATION_RIGHT_HP] - m_Xharp[LOCATION_LEFT_HP]);
      }
      else if ( ::InRange(m_Xharp[LOCATION_RIGHT_HP],X,m_Xharp[LOCATION_END]) )
      {
         return ::LinInterp(X - m_Xharp[LOCATION_RIGHT_HP],m_Yharp[LOCATION_RIGHT_HP],m_Yharp[LOCATION_END],m_Xharp[LOCATION_END] - m_Xharp[LOCATION_RIGHT_HP]);
      }
      else
      {
         return m_Yharp[LOCATION_END];
      }
   }
   ATLASSERT(false); // should never get here
}

Float64 stbGirder::GetDensity() const
{
   return m_Density;
}

void stbGirder::SetAdditionalLoads(const std::vector<std::pair<Float64,Float64>>& vLoads)
{
   m_vPointLoads = vLoads;
}

std::vector<std::pair<Float64,Float64>> stbGirder::GetAdditionalLoads() const
{
   return m_vPointLoads;
}

void stbGirder::Update() const
{
   if ( m_bNeedsUpdate )
   {
      Float64 L = 0;
      Float64 W = 0;
      Float64 g = unitSysUnitsMgr::GetGravitationalAcceleration();
      std::vector<stbSectionProperties>::const_iterator iter(m_vSectionProperties.begin());
      std::vector<stbSectionProperties>::const_iterator end(m_vSectionProperties.end());
      for ( ; iter != end; iter++ )
      {
         const stbSectionProperties& sp(*iter);
         Float64 area = (sp.Ag[SECTION_START] + sp.Ag[SECTION_END])/2;
         Float64 w = area * m_Density * g;

         L += sp.L;
         W += w*sp.L;
      }
      m_L = L;
      m_Wg = W;
      m_bNeedsUpdate = false;

      std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIter(m_vPointLoads.begin());
      std::vector<std::pair<Float64,Float64>>::const_iterator ptLoadIterEnd(m_vPointLoads.end());
      for ( ; ptLoadIter != ptLoadIterEnd; ptLoadIter++ )
      {
         Float64 P = ptLoadIter->second;
         m_Wg += P;
      }
   }
}

/////////////////////////////////////////////////////
stbStabilityProblemImp::stbStabilityProblemImp()
{
   m_XferLength = 0;

   m_bDirectCamber = true;
   m_Camber = 0;

   m_fc = 0;
   m_fr = 0;
   m_Ec = 0;

   m_Ll = 0;
   m_Lr = 0;

   m_SweepTolerance = 0;
   m_SupportPlacementTolerance = 0;

   m_Yra = 0;

   m_ImpactUp = 0;
   m_ImpactDown = 0;
   m_bApplyImpactToTiltedGirder = false;

   m_WindPressure = 0;
}

stbStabilityProblemImp::~stbStabilityProblemImp()
{
}

bool stbStabilityProblemImp::operator==(const stbStabilityProblemImp& other) const
{
   if ( m_vAnalysisPoints != other.m_vAnalysisPoints )
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

   if ( !IsEqual(m_fc,other.m_fc) )
      return false;

   if ( !IsEqual(m_fr,other.m_fr) )
      return false;

   if ( !IsEqual(m_Ec,other.m_Ec) )
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

   if ( m_bApplyImpactToTiltedGirder != other.m_bApplyImpactToTiltedGirder )
      return false;

   if ( !IsEqual(m_WindPressure,other.m_WindPressure) )
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

void stbStabilityProblemImp::AddFpe(Float64 X,Float64 FpeStraight,Float64 FpeHarped,Float64 FpeTemp)
{
   stbFpe fpe;
   fpe.X = X;
   fpe.fpeStraight = FpeStraight;
   fpe.fpeHarped = FpeHarped;
   fpe.fpeTemporary = FpeTemp;
   m_vFpe.insert(fpe);
}

void stbStabilityProblemImp::GetFpe(IndexType fpeIdx,Float64* pX,Float64* pFpeStraight,Float64* pFpeHarped,Float64* pFpeTemp) const
{
   if ( m_vFpe.size() == 0 )
   {
      *pX = 0;
      *pFpeStraight = 0;
      *pFpeHarped = 0;
      *pFpeTemp = 0;
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
      *pFpeHarped   = iter->fpeHarped;
      *pFpeTemp     = iter->fpeTemporary;
   }
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

void stbStabilityProblemImp::SetFc(Float64 fc)
{
   m_fc = fc;
}

Float64 stbStabilityProblemImp::GetFc() const
{
   return m_fc;
}

void stbStabilityProblemImp::SetEc(Float64 ec)
{
   m_Ec = ec;
}

void stbStabilityProblemImp::SetFr(Float64 fr)
{
   m_fr = fr;
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

void stbStabilityProblemImp::SetWindPressure(Float64 wp)
{
   m_WindPressure = wp;
}

Float64 stbStabilityProblemImp::GetFpe(int strandType,Float64 X) const
{
   if ( m_vFpe.size() == 0 )
   {
      return 0;
   }

   if ( m_vFpe.size() == 1 || ::IsLE(X,m_vFpe.begin()->X) )
   {
      Float64 Fpe;
      if ( strandType == STRAIGHT )
      {
         Fpe =  m_vFpe.begin()->fpeStraight;
      }
      else if ( strandType == HARPED )
      {
         Fpe =  m_vFpe.begin()->fpeHarped;
      }
      else
      {
         Fpe = m_vFpe.begin()->fpeTemporary;
      }

      if ( m_vFpe.size() == 1 && !IsZero(m_XferLength) )
      {
         // Fpe is modeled as a constant value... use the transfer length to adjust at the ends of the girder
         if ( X < m_XferLength )
         {
            // X is in a zone where Fpe is reduced due to transfer
            Fpe *= X/m_XferLength;
         }
         else if (m_Lg-m_XferLength < X)
         {
            Float64 x = m_Lg - X;
            Fpe *= x/m_XferLength;
         }
      }

      return Fpe;
   }

   if ( ::IsLE(m_vFpe.rbegin()->X,X) )
   {
      if ( strandType == STRAIGHT )
      {
         return m_vFpe.rbegin()->fpeStraight;
      }
      else if ( strandType == HARPED )
      {
         return m_vFpe.rbegin()->fpeHarped;
      }
      else
      {
         return m_vFpe.rbegin()->fpeTemporary;
      }
   }

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
         if ( strandType == STRAIGHT )
         {
            FpeStart = iter1->fpeStraight;
            FpeEnd   = iter2->fpeStraight;
         }
         else if ( strandType == HARPED )
         {
            FpeStart = iter1->fpeHarped;
            FpeEnd   = iter2->fpeHarped;
         }
         else
         {
            FpeStart = iter1->fpeTemporary;
            FpeEnd   = iter2->fpeTemporary;
         }
         Float64 fpe = ::LinInterp(X-Xstart,FpeStart,FpeEnd,Xend-Xstart);
         return fpe;
      }
   }

   ATLASSERT(false); // should never get here
   return 0;
}

void stbStabilityProblemImp::GetCamber(bool* pbDirectCamber,Float64* pCamber) const
{
   *pbDirectCamber = m_bDirectCamber;
   *pCamber = m_Camber;
}

Float64 stbStabilityProblemImp::GetEc() const
{
   return m_Ec;
}

Float64 stbStabilityProblemImp::GetFr() const
{
   return m_fr;
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

void stbStabilityProblemImp::ApplyImpactToTiltedGirder(bool bApplyImpact)
{
   m_bApplyImpactToTiltedGirder = bApplyImpact;
}

bool stbStabilityProblemImp::ApplyImpactToTiltedGirder() const
{
   return m_bApplyImpactToTiltedGirder;
}

Float64 stbStabilityProblemImp::GetWindPressure() const
{
   return m_WindPressure;
}

void stbStabilityProblemImp::ClearAnalysisPoints()
{
   m_vAnalysisPoints.clear();
}

void stbStabilityProblemImp::AddAnalysisPoint(Float64 X)
{
   m_vAnalysisPoints.push_back(X);
   std::sort(m_vAnalysisPoints.begin(),m_vAnalysisPoints.end());
}

const std::vector<Float64>& stbStabilityProblemImp::GetAnalysisPoints() const
{
   return m_vAnalysisPoints;
}

////////////////////////////////


stbLiftingStabilityProblem::stbLiftingStabilityProblem()
{
   m_LiftAngle = PI_OVER_2;
}

stbLiftingStabilityProblem::~stbLiftingStabilityProblem()
{
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

//////////////////////////////////
stbHaulingStabilityProblem::stbHaulingStabilityProblem()
{
   m_Ktheta = 0;
   m_Wcc = 0;
   m_Hrc = 0;
   m_Superelevation = 0;
   
   m_Velocity = 0;
   m_Radius = DBL_MAX;
}

stbHaulingStabilityProblem::~stbHaulingStabilityProblem()
{
}

bool stbHaulingStabilityProblem::operator==(const stbHaulingStabilityProblem& other) const
{
   if ( m_Imp != other.m_Imp )
      return false;

   if ( !IsEqual(m_Ktheta,other.m_Ktheta) )
      return false;

   if ( !IsEqual(m_Wcc,other.m_Wcc) )
      return false;

   if ( !IsEqual(m_Hrc,other.m_Hrc) )
      return false;

   if ( !IsEqual(m_Superelevation,other.m_Superelevation) )
      return false;

   if ( !IsEqual(m_Velocity,other.m_Velocity) )
      return false;

   if ( !IsEqual(m_Radius,other.m_Radius) )
      return false;

   return true;
}

bool stbHaulingStabilityProblem::operator!=(const stbHaulingStabilityProblem& other) const
{
   return !(*this == other);
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
