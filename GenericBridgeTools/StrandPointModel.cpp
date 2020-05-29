///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StrandPointModel.cpp : Implementation of CStrandPointModel
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "StrandPointModel.h"
#include "Helpers.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// In Girder Section Coordinates (anytime we cut a section through the girder)
// the elevation of strands with a Linear profile need to adjusted by -precamber.
// 
// In Girder Profile Coordinates (anytime we are getting profile or side view information)
// the elevation of strands with a FollowGirder profile need to be adjusted by +precamber.
// Also, the position of harp point grids need to be adjusted by precamber. These
// grids are not anchored to the ends of the girder like straight and temporary strands.
/////////////////////////////////////////////////////////////////////////////

// CStrandPointModel
HRESULT CStrandPointModel::FinalConstruct()
{
   // reserve space for strands
   for (int i = 0; i < 3; i++)
   {
      m_Strands[i].reserve(50);
   }

   return S_OK;
}

void CStrandPointModel::FinalRelease()
{
}

STDMETHODIMP CStrandPointModel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IStrandPointModel
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStrandPointModel::GetStrandRowCount(StrandType strandType, Float64 Xs, RowIndexType* nRows)
{
   CHECK_RETVAL(nRows);
   auto& rows = GetStrandRows(strandType, Xs);
   *nRows = (RowIndexType)(rows.size());
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetNumStrandsInRow(StrandType strandType, Float64 Xs, RowIndexType rowIdx, StrandIndexType* nStrands)
{
   CHECK_RETVAL(nStrands);
   auto& rows = GetStrandRows(strandType, Xs);
   auto iter = rows.begin();
   std::advance(iter, rowIdx);
   *nStrands = (StrandIndexType)(iter->Strands.size());
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetUnadjustedStrandRowElevation(StrandType strandType, Float64 Xs, RowIndexType rowIdx, Float64 * fElevation)
{
   CHECK_RETVAL(fElevation);
   auto& rows = GetStrandRows(strandType, Xs);
   auto iter = rows.begin();
   std::advance(iter, rowIdx);
   *fElevation = iter->Y;
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStrandsInRow(StrandType strandType, Float64 Xs, RowIndexType rowIdx, IIndexArray** ppStrandIndicies)
{
   CHECK_RETOBJ(ppStrandIndicies);

   CComPtr<IIndexArray> idxArray;
   idxArray.CoCreateInstance(CLSID_IndexArray);

   auto& rows = GetStrandRows(strandType, Xs);
   auto iter = rows.begin();
   std::advance(iter, rowIdx);

   for (auto& strandIdx : iter->Strands)
   {
      idxArray->Add(strandIdx);
   }

   idxArray.CopyTo(ppStrandIndicies);

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStrandPositions(StrandType strandType, Float64 Xs, IPoint2dCollection** ppPoints)
{
   // strand position in Girder Section coordinates (relative to top center of girder)
   CHECK_RETOBJ(ppPoints);
   HRESULT hr = S_OK;

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   StrandIndexType nStrands = m_Strands[strandType].size();
   for (StrandIndexType strandIdx = 0; strandIdx < nStrands; strandIdx++)
   {
      CComPtr<IPoint2d> point;
      GetStrandPosition(strandType, strandIdx, Xs, &point);
      points->Add(point);
   }

   points.CopyTo(ppPoints);

   return hr;
}

STDMETHODIMP CStrandPointModel::GetStrandCount(StrandType strandType, StrandIndexType* pStrands)
{
   CHECK_RETVAL(pStrands);
   *pStrands = m_Strands[strandType].size();
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStrandCG(StrandType strandType, Float64 Xs, IPoint2d** pntCG)
{
   CHECK_RETVAL(pntCG);
   
   // check the cache first.. we may have already computed this
   const auto found = m_CGs[strandType].find(Xs);
   if (found != m_CGs[strandType].end())
   {
      // we found the CG we want in our cache.
      // return it.
      return found->second.CopyTo(pntCG);
   }
   
   // Get the location of all the strands at Xs
   CComPtr<IPoint2dCollection> points;
   GetStrandPositions(strandType, Xs, &points);

   // Remove any strands that are debonded at Xs...
   // these strands don't contribute to the CG
   RemoveDebondedStrandPositions(strandType, Xs, points);

   // Compute the CG from the remaining points
   GetCGFromPoints(points, pntCG);
   
   // cache the results
   auto result = m_CGs[strandType].insert(std::make_pair(Xs, *pntCG));
   ATLASSERT(result.second == true);

   return S_OK;
}

STDMETHODIMP CStrandPointModel::ComputeMaxHarpedStrandSlope(Float64 Xs,Float64* slope)
{
   CHECK_RETVAL(slope);

   StrandIndexType nStrands;
   GetStrandCount(Harped, &nStrands);
   if (nStrands == 0)
   {
      *slope = DBL_MAX;
      return S_OK;
   }

#if defined _DEBUG
   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);
   ATLASSERT(0.0 <= Xs  && Xs <= gdrLength);
#endif

   // slope is 1:n where n = run/rise. Max slope is the one with the minimum n value
   // since n is signed, we want the min absolute value
   Float64 n_min = DBL_MAX;
   Float64 sign = 1;
   for (const auto& strandRecord : m_Strands[Harped])
   {
      Float64 n = GetStrandSlope(Xs, Harped, strandRecord);
      if (fabs(n) < n_min)
      {
         // we have a new max slope
         n_min = fabs(n);
         sign = BinarySign(n);
      }
   }

   *slope = sign*n_min;

   return S_OK;
}

STDMETHODIMP CStrandPointModel::ComputeAvgHarpedStrandSlope(Float64 Xs, Float64* slope)
{
   CHECK_RETVAL(slope);

   StrandIndexType nStrands;
   GetStrandCount(Harped, &nStrands);
   if (nStrands == 0)
   {
      *slope = DBL_MAX;
      return S_OK;
   }

   Float64 Lg;
   m_pGirder->get_GirderLength(&Lg);
   ATLASSERT(0.0 <= Xs  && Xs <= Lg);

   ZoneType zone = GetZone(Xs, Harped);

   std::array<Float64, 4> Xhp;
   GetHarpPointLocations(Xhp[ZoneBreakType::Start], Xhp[ZoneBreakType::LeftBreak], Xhp[ZoneBreakType::RightBreak], Xhp[ZoneBreakType::End]);

   Float64 Xl, Xr;
   switch (zone)
   {
   case ZoneType::LeftStraight:
      Xl = 0.0;
      Xr = Xhp[ZoneBreakType::Start];
      break;

   case ZoneType::LeftSlope:
      Xl = Xhp[ZoneBreakType::Start];
      Xr = Xhp[ZoneBreakType::LeftBreak];
      break;

   case ZoneType::MidStraight:
      Xl = Xhp[ZoneBreakType::LeftBreak];
      Xr = Xhp[ZoneBreakType::RightBreak];
      break;

   case ZoneType::RightSlope:
      Xl = Xhp[ZoneBreakType::RightBreak];
      Xr = Xhp[ZoneBreakType::End];
      break;

   case ZoneType::RightStraight:
      Xl = Xhp[ZoneBreakType::End];
      Xr = Lg;
      break;

   default:
      ATLASSERT(false);
   }

   CComPtr<IPoint2d> pntCG;
   GetStrandCG(Harped, Xl, &pntCG);
   Float64 Yl;
   pntCG->get_Y(&Yl);

   pntCG.Release();
   GetStrandCG(Harped, Xr, &pntCG);
   Float64 Yr;
   pntCG->get_Y(&Yr);

   Float64 lPrecamber, rPrecamber;
   m_pSegment->ComputePrecamber(Xl, &lPrecamber);
   m_pSegment->ComputePrecamber(Xr, &rPrecamber);

   Yl += lPrecamber;
   Yr += rPrecamber;

   if ( !::IsEqual(Yl, Yr) )
   {
      *slope = (Xr - Xl) / (Yr - Yl);
   }
   else
   {
      *slope = DBL_MAX;
   }

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStrandProfile(StrandType strandType, StrandIndexType strandIdx, IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);
   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   if (m_Strands[strandType].size() <= strandIdx)
   {
      return E_INVALIDARG;
   }

   Float64 Ls;
   m_pSegment->get_Length(&Ls);
   
   std::vector<Float64> vPoints;
   vPoints.reserve(18);

   vPoints.push_back(0.0);
   vPoints.push_back(Ls);

   std::array<Float64, 4> Xhp;
   if (strandType == Harped)
   {
      // add the harping points for harped strands
      GetHarpPointLocations(Xhp[ZoneBreakType::Start], Xhp[ZoneBreakType::LeftBreak], Xhp[ZoneBreakType::RightBreak],Xhp[ZoneBreakType::End]);
      vPoints.insert(vPoints.end(), Xhp.begin(), Xhp.end());
   }

   // add debond locations
   const auto& strandRecord(m_Strands[strandType][strandIdx]);
   if (!IsZero(strandRecord.Debond[etStart]))
   {
      vPoints.push_back(strandRecord.Debond[etStart]);
   }

   if (!IsEqual(Ls,strandRecord.Debond[etEnd]))
   {
      vPoints.push_back(strandRecord.Debond[etEnd]);
   }


   std::sort(vPoints.begin(), vPoints.end());
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end());

   Float64 xMin = vPoints.front();
   Float64 xMax = vPoints.back();

   Float64 precamber;
   m_pSegment->get_Precamber(&precamber);
   bool bHasPrecamber = !IsZero(precamber);
   if (bHasPrecamber)
   {
      // if the straight or temporary strands follow the profile of the girder
      // add extra points so the profile isn't modeled as a straight line
      // between two points... instead the profile is a bunch of straight
      // chords that follow the profile of the girder.
      if (
         (strandType == Straight  && m_StraightStrandProfileType  == FollowGirder) || 
         (strandType == Temporary && m_TemporaryStrandProfileType == FollowGirder) 
         )
      {
         int nPoints = 11;
         for (int i = 0; i < nPoints; i++)
         {
            Float64 Xs = i*Ls / (nPoints - 1);
            if (xMin < Xs && Xs < xMax)
            {
               vPoints.push_back(Xs);
            }
         }
      }
   }

   std::sort(vPoints.begin(), vPoints.end());
   vPoints.erase(std::unique(vPoints.begin(), vPoints.end()), vPoints.end());

   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   Float64 thickening = 0;
   if (strandType == Harped && thickenedSegment)
   {
      ThickeningType thickeningType;
      thickenedSegment->get_FlangeThickeningType(&thickeningType);
      if (thickeningType == ttEnds)
      {
         thickenedSegment->get_FlangeThickening(&thickening);
      }
   }

   for (const auto& x : vPoints)
   {
      CComPtr<IPoint2d> strandPoint;
      GetStrandPosition(strandType, strandIdx, x, &strandPoint);

      Float64 y;
      strandPoint->get_Y(&y);

      // strand point is in Girder Section coordinates. This is a cross-section coordinate system. Because of precamber
      // and top flange thickening, the elevation of the Girder Section Coordinate system can change at each cross section.
      // Adjust the strand point elevation for precamber and top flange thickening
      Float64 precamber = 0.0;
      m_pSegment->ComputePrecamber(x, &precamber);
      y += precamber;

      if (strandType == Harped && thickenedSegment)
      {
         Float64 tft = 0;
         thickenedSegment->get_TopFlangeThickening(x, &tft);
         y += tft - thickening;
      }

      CComPtr<IPoint2d> profilePoint;
      profilePoint.CoCreateInstance(CLSID_Point2d);
      profilePoint->Move(x, y);
      profilePoints->Add(profilePoint);
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStrandCGProfile(VARIANT_BOOL bIncludeTempStrands, IPoint2dCollection** ppProfilePoints)
{
   CHECK_RETOBJ(ppProfilePoints);
   CComPtr<IPoint2dCollection> profilePoints;
   profilePoints.CoCreateInstance(CLSID_Point2dCollection);

   // get the number of each type of strands
   StrandIndexType Ns, Nh, Nt(0);
   GetStrandCount(Straight, &Ns);
   GetStrandCount(Harped, &Nh);
   if (bIncludeTempStrands == VARIANT_TRUE)
   {
      GetStrandCount(Temporary, &Nt);
   }

   StrandIndexType nStrands = Ns + Nh + Nt;

   if (nStrands != 0)
   {
      Float64 Ls;
      m_pSegment->get_Length(&Ls);

      // get all points where strand can change slope. these are the control points of the profile
      std::set<Float64> Z; // locations where strands are defined

      Z.insert(0.0);
      Z.insert(Ls);

      if (0 < Nh)
      {
         std::array<Float64, 4> Xhp;
         GetHarpPointLocations(Xhp[ZoneBreakType::Start], Xhp[ZoneBreakType::LeftBreak], Xhp[ZoneBreakType::RightBreak], Xhp[ZoneBreakType::End]);
         
         for (int j = 0; j < 4; j++)
         {
            Z.insert(Xhp[j]);
         }
      }

      // if there is precamber and the straight/temporary strand following the shape of precamber, add points
      // in between so the profile has the curve
      Float64 precamber;
      m_pSegment->get_Precamber(&precamber);
      if (!IsZero(precamber) && ((0 < Ns && m_StraightStrandProfileType == FollowGirder) || (0 < Nt && m_TemporaryStrandProfileType == FollowGirder)))
      {
         int nPoints = 11;
         for (int i = 0; i < nPoints; i++)
         {
            Float64 x = i*Ls / (nPoints - 1);
            Z.insert(x);
         }
      }

      // add debonding points... add a point just before and just after
      // the point where bond begins so we see the "jump" in the strand cg profile
      StrandIndexType nDebonded;
      GetStraightStrandDebondCount(WDebondLocationType::wdblLeft, &nDebonded);
      if (0 < Ns && nDebonded != 0)
      {
         for (StrandIndexType strandIdx = 0; strandIdx < Ns; strandIdx++)
         {
            Float64 X, Y, l1, l2;
            GetStraightStrandDebondLengthByPositionIndex(0.0, strandIdx, &X, &Y, &l1, &l2);
            if (0 < l1)
            {
               Z.insert(l1 - 0.001);
            }

            Z.insert(l1);
            Z.insert(Ls - l2);

            if (0 < l2)
            {
               Z.insert(Ls - l2 + 0.001);
            }
         }
      }

      // at each control point, compute the CG of the strands
      CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
      Float64 thickening = 0;
      if (thickenedSegment)
      {
         ThickeningType thickeningType;
         thickenedSegment->get_FlangeThickeningType(&thickeningType);
         if (thickeningType == ttEnds)
         {
            thickenedSegment->get_FlangeThickening(&thickening);
         }
      }

      for (auto z : Z)
      {
         CComPtr<IPoint2d> pntCGStraight;
         Float64 cgXstraight(0), cgYstraight(0);

         Float64 precamber;
         m_pSegment->ComputePrecamber(z, &precamber);

         if (0 < Ns)
         {
            GetStrandCG(Straight, z, &pntCGStraight);
            pntCGStraight->Location(&cgXstraight, &cgYstraight);

            if (m_StraightStrandProfileType == FollowGirder)
            {
               cgYstraight += precamber;
            }
         }

         CComPtr<IPoint2d> pntCGHarped;
         Float64 cgXharped(0), cgYharped(0);
         if (0 < Nh)
         {
            GetStrandCG(Harped, z, &pntCGHarped);
            pntCGHarped->Location(&cgXharped, &cgYharped);

            cgYharped += precamber;

            if (thickenedSegment)
            {
               Float64 tft;
               thickenedSegment->get_TopFlangeThickening(z, &tft);
               cgYharped += tft - thickening;
            }
         }

         Float64 cgXtemp(0), cgYtemp(0);
         if (bIncludeTempStrands == VARIANT_TRUE && 0 < Nt)
         {
            CComPtr<IPoint2d> pntCGTemp;
            GetStrandCG(Temporary, z, &pntCGTemp);
            pntCGTemp->Location(&cgXtemp, &cgYtemp);

            if (m_TemporaryStrandProfileType == FollowGirder)
            {
               cgYtemp += precamber;
            }
         }

         //Float64 cgx = (Ns*cgXstraight + Nh*cgXharped + Nt*cgXtemp) / nStrands;
         Float64 cgy = (Ns*cgYstraight + Nh*cgYharped + Nt*cgYtemp) / nStrands;

         CComPtr<IPoint2d> pntCG;
         pntCG.CoCreateInstance(CLSID_Point2d);
         pntCG->Move(z, cgy);

         profilePoints->Add(pntCG);
      }
   }

   // put the strand profiles in the same longitudinal coordinate system as the girder profile
   CComPtr<IGirderLine> girderLine;
   m_pSegment->get_GirderLine(&girderLine);

   Float64 brgOffset, endDist;
   girderLine->get_BearingOffset(etStart, &brgOffset);
   girderLine->get_EndDistance(etStart, &endDist);
   Float64 offset = brgOffset - endDist;

   profilePoints->Offset(offset, 0);

   profilePoints.CopyTo(ppProfilePoints);
   return S_OK;
}

// Compute bounding boxes of harped and straight strands accounting for vertical offsets for harped strands
STDMETHODIMP CStrandPointModel::StraightStrandBoundingBox(EndType endType, IRect2d** box)
{
   int i = (endType == etStart ? ZoneBreakType::Start : ZoneBreakType::End);
   return GetStrandBoundingBox(Straight, i, box);
}

STDMETHODIMP CStrandPointModel::HarpedEndStrandBoundingBox(EndType endType, IRect2d** box)
{
   int i = (endType == etStart ? ZoneBreakType::Start : ZoneBreakType::End);
   return GetStrandBoundingBox(Harped, i, box);
}

STDMETHODIMP CStrandPointModel::HarpedHpStrandBoundingBox(EndType endType, IRect2d** box)
{
   int i = (endType == etStart ? ZoneBreakType::LeftBreak : ZoneBreakType::RightBreak);
   return GetStrandBoundingBox(Harped, i, box);
}

STDMETHODIMP CStrandPointModel::GetStraightStrandDebondLengthByPositionIndex(Float64 Xs, StrandIndexType positionIndex, Float64* XCoord, Float64* YCoord, Float64* l1, Float64* l2)
{
   CHECK_RETVAL(XCoord);
   CHECK_RETVAL(YCoord);
   CHECK_RETVAL(l1);
   CHECK_RETVAL(l2);

   Float64 Lg;
   m_pGirder->get_GirderLength(&Lg);

   const auto& strandRecord = m_Strands[Straight][positionIndex];
   *XCoord = strandRecord.X;

   Float64 Y1 = strandRecord.Y[ZoneBreakType::Start];
   Float64 Y2 = strandRecord.Y[ZoneBreakType::End];

   *YCoord = ::LinInterp(Xs, Y1, Y2, Lg);
   *l1 = strandRecord.Debond[etStart];
   *l2 = Lg - strandRecord.Debond[etEnd];

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandsDebondedByPositionIndex(Float64 Xs, IIndexArray** positionIndexes)
{
   CHECK_RETOBJ(positionIndexes);

   CComPtr<IIndexArray> idxArray;
   idxArray.CoCreateInstance(CLSID_IndexArray);

   StrandIndexType idx = 0;
   for (const auto& strandRecord : m_Strands[Straight])
   {
      if ( Xs < strandRecord.Debond[etStart] || strandRecord.Debond[etEnd] < Xs)
      {
         // Xs is in the ends of the girder where this strand is not bonded
         // save the index
         idxArray->Add(idx);
      }

      idx++;
   }

   idxArray.CopyTo(positionIndexes);

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandDebondCount( WDebondLocationType loc,  StrandIndexType* count)
{
   CHECK_RETVAL(count);

   Float64 Lg;
   m_pGirder->get_GirderLength(&Lg);

   StrandIndexType nStart(0), nEnd(0);
   for (const auto& strandRecord : m_Strands[Straight])
   {
      nStart += (IsZero(strandRecord.Debond[etStart]) ? 0 : 1);
      nEnd   += (IsEqual(strandRecord.Debond[etEnd],Lg) ? 0 : 1);
   }

   switch (loc)
   {
   case wdblEither:
      *count = Max(nStart, nEnd);
      break;
      
   case wdblLeft:
      *count = nStart;
      break;
      
   case wdblRight:
      *count = nEnd;
      break;
      
   default:
      ATLASSERT(false);
      *count = 0;
   }

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetDebondingLocations(StrandType strandType, IDblArray** arrLeft, IDblArray** arrRight)
{
   CHECK_RETOBJ(arrLeft);
   CHECK_RETOBJ(arrRight);

   std::array<CComPtr<IDblArray>, 2> locations;
   locations[etStart].CoCreateInstance(CLSID_DblArray);
   for (const auto& dbSection : m_DebondSections[etStart][strandType])
   {
      locations[etStart]->Add(dbSection.Z);
   }

   locations[etEnd].CoCreateInstance(CLSID_DblArray);
   auto iter = m_DebondSections[etEnd][strandType].rbegin();
   auto end = m_DebondSections[etEnd][strandType].rend();
   for (; iter != end; iter++)
   {
      const auto& dbSection(*iter);
      locations[etEnd]->Add(dbSection.Z);
   }

   locations[etStart].CopyTo(arrLeft);
   locations[etEnd].CopyTo(arrRight);

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetDebondedStrandsAtSection(EndType endType, StrandType strandType, SectionIndexType sectionIdx, IIndexArray** pstnIndexes)
{
   CHECK_RETOBJ(pstnIndexes);
   CComPtr<IIndexArray> indexes;
   indexes.CoCreateInstance(CLSID_IndexArray);
   auto iter = m_DebondSections[endType][strandType].begin();
   std::advance(iter, sectionIdx);
   const auto& dbSection = *iter;
   for (const auto& strandIdx : dbSection.Strands)
   {
      indexes->Add(strandIdx);
   }

   indexes.CopyTo(pstnIndexes);
   return S_OK;
}

STDMETHODIMP CStrandPointModel::get_StraightStrandDebondInRow(Float64 Xs, RowIndexType rowIdx,StrandIndexType* nStrands)
{
   CHECK_RETVAL(nStrands);

   auto& rows = GetStrandRows(Straight, Xs);

   if (rows.size() <= rowIdx)
   {
      return E_INVALIDARG;
   }

   auto& iter = std::cbegin(rows);
   std::advance(iter, rowIdx);
   const auto& vStrands = iter->Strands;

   Float64 Lg;
   m_pGirder->get_GirderLength(&Lg);

   *nStrands = 0;
   for (const auto& strandIdx : vStrands)
   {
      const auto& strandRecord(m_Strands[Straight][strandIdx]);
      if (0 < strandRecord.Debond[etStart] || strandRecord.Debond[etEnd] < Lg)
      {
         // this strand has debonding
         (*nStrands)++;
      }
   }

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandBondedLengthByPositionIndex(StrandIndexType positionIndex, Float64 Xs, Float64* XCoord, Float64* YCoord, Float64* leftBond, Float64* rightBond)
{
   CComPtr<IPoint2dCollection> points;
   GetStrandPositions(Straight, Xs, &points);

   CComPtr<IPoint2d> pnt;
   points->get_Item(positionIndex, &pnt);
   pnt->Location(XCoord, YCoord);

   const auto& strandRecord = m_Strands[Straight][positionIndex];

   // StrandRecord has debond/bond location measured from left end of girder
   if (Xs < strandRecord.Debond[etStart] || strandRecord.Debond[etEnd] < Xs)
   {
      // Xs is before the point bonding begins at left end
      // or after the point debonding begins at the right end
      *leftBond = 0.0;
      *rightBond = 0.0;
   }
   else
   {
      // Xs is somewhere along the bonded length of the strand
      *leftBond = Xs - strandRecord.Debond[etStart];
      *rightBond = strandRecord.Debond[etEnd] - Xs;
   }
   return S_OK;
}

STDMETHODIMP CStrandPointModel::IsExteriorStraightStrandDebondedInRow(Float64 Xs, RowIndexType rowIdx,VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   auto& rows = GetStrandRows(Straight, Xs);

   if (rows.size() <= rowIdx)
   {
      return E_INVALIDARG;
   }

   auto& iter = std::cbegin(rows);
   std::advance(iter, rowIdx);
   const auto& vStrands = iter->Strands;

   // find the records with the smallest and larget X values... these are the "exterior" strands
   const StrandRecord* pLeft = nullptr;
   const StrandRecord* pRight = nullptr;
   for (const auto& strandIdx : vStrands)
   {
      const auto& strandRecord(m_Strands[Straight][strandIdx]);
      if (pLeft == nullptr)
      {
         pLeft = &strandRecord;
      }
      else
      {
         if (strandRecord.X < pLeft->X)
         {
            // this record is further to the left... capture it
            pLeft = &strandRecord;
         }
      }

      if (pRight == nullptr)
      {
         pRight = &strandRecord;
      }
      else
      {
         if (pRight->X < strandRecord.X)
         {
            // this record is further to the right... capture it
            pRight = &strandRecord;
         }
      }
   }

   ATLASSERT(pLeft != nullptr && pRight != nullptr);

   Float64 Lg;
   m_pGirder->get_GirderLength(&Lg);

   *bResult = VARIANT_FALSE;
   if ((0 < pLeft->Debond[etStart]  || pLeft->Debond[etEnd]  < Lg) ||
       (0 < pRight->Debond[etStart] || pRight->Debond[etEnd] < Lg)
      )
   {
      // the left most or right most strand has debonding
      *bResult = VARIANT_TRUE;
   }
   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandDebondedConfigurationCountByRow(Float64 Xs, RowIndexType rowIdx, IndexType* pConfigCount)
{
   CHECK_RETVAL(pConfigCount);

   std::vector<STRANDDEBONDRECORD> debondConfigs = GetStraightStrandDebondedConfigurations(rowIdx);

   *pConfigCount = debondConfigs.size();

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandDebondConfigurationByRow(Float64 Xs, RowIndexType rowIdx, IndexType configIdx, Float64* pXstart, Float64* pBondedLength, Float64* pCgX, Float64* pCgY, IndexType* pnStrands)
{
   std::vector<STRANDDEBONDRECORD> debondConfigs = GetStraightStrandDebondedConfigurations(rowIdx);

   STRANDDEBONDRECORD& record(debondConfigs[configIdx]);

   Float64 gdr_length;
   m_pGirder->get_GirderLength(&gdr_length);

   *pXstart = record.LdbStart;
   *pBondedLength = gdr_length - record.LdbStart - record.LdbEnd;
   *pnStrands = record.nStrands;

   // CG's
   if (0 < record.nStrands)
   {
      *pCgX = record.XSum / record.nStrands;
      *pCgY = record.YSum / record.nStrands;
   }
   else
   {
      *pCgX = 0.0; // for lack of better value
      *pCgY = 0.0;
   }

   return S_OK;
}

STDMETHODIMP CStrandPointModel::GetStraightStrandDebondedRows(Float64 Xs, IIndexArray** ppRowIndexes)
{
   CHECK_RETOBJ(ppRowIndexes);

   CComPtr<IIndexArray> array;
   array.CoCreateInstance(CLSID_IndexArray);
   auto& rows = GetStrandRows(Straight, Xs);
   RowIndexType rowIdx = 0;
   for (const auto& strandRow : rows)
   {
      for (const auto& strandIdx : strandRow.Strands)
      {
         const auto& strandRecord = m_Strands[Straight][strandIdx];
         if (0 < strandRecord.Debond[etStart] && 0 < strandRecord.Debond[etEnd])
         {
            array->Add(rowIdx);
            break;
         }
      }

      rowIdx++;
   }

   return array.CopyTo(ppRowIndexes);
}

void CStrandPointModel::RemoveDebondedStrandPositions(StrandType strandType,Float64 Xs, IPoint2dCollection* pPoints)
{
   // If the strand is debonded at Xs, remove it from pPoints
   IndexType nPoints;
   pPoints->get_Count(&nPoints);
   // work backrwards so removing an item doesn't mess up the iteration
   for (IndexType strandIdx = nPoints - 1; 0 <= strandIdx && strandIdx != INVALID_INDEX; strandIdx--)
   {
      const auto& strandRecord(m_Strands[strandType][strandIdx]);
      if (Xs < strandRecord.Debond[etStart] || strandRecord.Debond[etEnd] < Xs)
      {
         // Xs is in the debonded region, remove this strand from the point collection
         pPoints->Remove(strandIdx);
      }
   }
}

STDMETHODIMP CStrandPointModel::AddStraightStrand(Float64 X, Float64 Ys, Float64 Ye, VARIANT_BOOL vbExtendedLeft, VARIANT_BOOL vbExtendedRight, Float64 debondLeft, Float64 debondRight)
{
   return AddStrand(Straight, X, Ys, Ys, Ye, Ye, vbExtendedLeft, vbExtendedRight, debondLeft, debondRight);
}

STDMETHODIMP CStrandPointModel::AddHarpedStrand(Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye)
{
   return AddStrand(Harped, X, Ys, Yhp1, Yhp2, Ye, VARIANT_FALSE, VARIANT_FALSE, 0.0, 0.0);
}

STDMETHODIMP CStrandPointModel::AddTemporaryStrand(Float64 X, Float64 Ys, Float64 Ye)
{
   return AddStrand(Temporary, X, Ys, Ys, Ye, Ye, VARIANT_FALSE, VARIANT_FALSE, 0.0, 0.0);
}

CStrandPointModel::StrandRecord::StrandRecord(Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye, VARIANT_BOOL vbExtendedLeft, VARIANT_BOOL vbExtendedRight, Float64 debondLeft, Float64 debondRight)
{
   this->X = X;
   this->Y[ZoneBreakType::Start] = Ys;
   this->Y[ZoneBreakType::LeftBreak] = Yhp1;
   this->Y[ZoneBreakType::RightBreak] = Yhp2;
   this->Y[ZoneBreakType::End] = Ye;

   this->Extended[etStart] = vbExtendedLeft;
   this->Extended[etEnd] = vbExtendedRight;

   this->Debond[etStart] = debondLeft;
   this->Debond[etEnd] = debondRight;
}

HRESULT CStrandPointModel::AddStrand(StrandType strandType,Float64 X, Float64 Ys, Float64 Yhp1, Float64 Yhp2, Float64 Ye, VARIANT_BOOL vbExtendedLeft, VARIANT_BOOL vbExtendedRight, Float64 debondLeft, Float64 debondRight)
{
   Float64 gdrLength;
   m_pGirder->get_GirderLength(&gdrLength);
   m_Strands[strandType].emplace_back(X, Ys, Yhp1, Yhp2, Ye, vbExtendedLeft, vbExtendedRight, debondLeft, gdrLength-debondRight);

   StrandIndexType strandIdx = (StrandIndexType)(m_Strands[strandType].size());

   // create debond section records... these are actually the sections
   // where bonding begins
   for (int i = 0; i < 2; i++)
   {
      EndType endType = (EndType)(i);
      DebondSectionRecord dsRecord;
      dsRecord.Z = (endType == etStart ? debondLeft : debondRight);
      if (IsZero(dsRecord.Z))
      {
         // the debonded length is zero meaning this strand is bonded at the current end
         continue;
      }

      auto found_dbSection = m_DebondSections[endType][strandType].find(dsRecord);
      if (found_dbSection == m_DebondSections[endType][strandType].end())
      {
         // this is a new section
         dsRecord.Strands.push_back(strandIdx);
         m_DebondSections[endType][strandType].insert(dsRecord);
      }
      else
      {
         // this is an existing section
         const DebondSectionRecord& existing_record = *found_dbSection;
         const_cast<DebondSectionRecord*>(&existing_record)->Strands.push_back(strandIdx);
      }
   }

   m_CGs[strandType].clear(); // cached values are no longer valid
   return S_OK;
}

HRESULT CStrandPointModel::GetStrandBoundingBox(StrandType strandType, int location, IRect2d** ppBoundingBox)
{
   Float64 left = DBL_MAX;
   Float64 right = -DBL_MAX;
   Float64 top = -DBL_MAX;
   Float64 bottom = DBL_MAX;
   for (const auto& strandRecord : m_Strands[strandType])
   {
      Float64 X = strandRecord.X;
      Float64 Y = strandRecord.Y[location];
      left = Min(left, X);
      right = Max(right, X);
      top = Max(top, Y);
      bottom = Min(bottom, Y);
   }

   CComPtr<IRect2d> box;
   box.CoCreateInstance(CLSID_Rect2d);
   box->SetBounds(left, right, bottom, top);
   box.CopyTo(ppBoundingBox);
   return S_OK;
}

ZoneType CStrandPointModel::GetZone(Float64 Xs,StrandType strandType) const
{
   ZoneType zone;
   if (strandType == Harped)
   {
      std::array<Float64, 4> Xhp;
      GetHarpPointLocations(Xhp[ZoneBreakType::Start], Xhp[ZoneBreakType::LeftBreak], Xhp[ZoneBreakType::RightBreak], Xhp[ZoneBreakType::End]);
      zone = ::GetZone(Xs, Xhp);
   }
   else
   {
      zone = ZoneType::MidStraight;
   }
   return zone;
}

void CStrandPointModel::GetStrandControlPoints(Float64 Xs, StrandType strandType, const StrandRecord& strandRecord, Float64* pZ1, Float64* pY1, Float64* pZ2, Float64* pY2,ZoneType* pZone) const
{
   Float64 Z1, Y1, Z2, Y2;

   if (strandType == Harped)
   {
      Float64 Lg;
      m_pGirder->get_GirderLength(&Lg);
      
      std::array<Float64, 4> Xhp;
      GetHarpPointLocations(Xhp[ZoneBreakType::Start], Xhp[ZoneBreakType::LeftBreak], Xhp[ZoneBreakType::RightBreak], Xhp[ZoneBreakType::End]);

      *pZone = GetControlPoints(Xs, Lg, Xhp, strandRecord.Y, &Z1, &Y1, &Z2, &Y2);
   }
   else
   {
      Z1 = 0;
      Y1 = strandRecord.Y[ZoneBreakType::Start];

      Float64 Lg;
      m_pGirder->get_GirderLength(&Lg);
      Z2 = Lg;
      Y2 = strandRecord.Y[ZoneBreakType::End];

      *pZone = ZoneType::MidStraight;
   }

   *pZ1 = Z1;
   *pY1 = Y1;
   *pZ2 = Z2;
   *pY2 = Y2;

   ATLASSERT(*pZone == GetZone(Xs,strandType));
}

Float64 CStrandPointModel::GetStrandSlope(Float64 Xs, StrandType strandType, const StrandRecord& strandRecord) const
{
   // slope is usually represented as rise/run, however we are representing it as 1:n
   // where n = run/rise... this method returns n
   // for a flat slope, n is infinity, represented as DBL_MAX

   Float64 Z1, Y1, Z2, Y2;
   ZoneType zone;
   GetStrandControlPoints(Xs, strandType, strandRecord, &Z1, &Y1, &Z2, &Y2, &zone);

   Float64 precamber;
   m_pSegment->ComputePrecamber(Z1, &precamber);
   Y1 += precamber;

   m_pSegment->ComputePrecamber(Z2, &precamber);
   Y2 += precamber;

   Float64 run = Z2 - Z1;
   Float64 rise = Y2 - Y1;

   Float64 n = (IsZero(rise) ? DBL_MAX : run / rise);
   return n;
}

std::vector<CStrandPointModel::STRANDDEBONDRECORD> CStrandPointModel::GetStraightStrandDebondedConfigurations(RowIndexType rowIdx)
{
   std::vector<STRANDDEBONDRECORD> debondConfigs;

   Float64 Xs = 0.0;

   CComPtr<IIndexArray> positionIndexes;
   GetStrandsInRow(Straight, Xs, rowIdx, &positionIndexes);

   CComPtr<IEnumIndexArray> enum_array;
   positionIndexes->get__EnumElements(&enum_array);
   IndexType positionIdx;
   while (enum_array->Next(1, &positionIdx, nullptr) != S_FALSE)
   {
      Float64 Xcoord, Ycoord, LdbStart, LdbEnd;
      GetStraightStrandDebondLengthByPositionIndex(Xs, positionIdx, &Xcoord, &Ycoord, &LdbStart, &LdbEnd);

      if (!IsZero(LdbStart) || !IsZero(LdbEnd))
      {
         STRANDDEBONDRECORD record;
         record.LdbStart = LdbStart;
         record.LdbEnd = LdbEnd;
         record.XSum = Xcoord;
         record.YSum = Ycoord;
         record.nStrands = 1;

         auto& found = std::find_if(debondConfigs.begin(), debondConfigs.end(), [record](const auto& config) {return IsEqual(record.LdbStart, config.LdbStart) && IsEqual(record.LdbEnd, config.LdbEnd);});
         if (found == debondConfigs.end())
         {
            debondConfigs.push_back(record);
         }
         else
         {
            found->nStrands++;
            found->XSum += Xcoord;
            found->YSum += Ycoord;
         }
      }
   }

   return debondConfigs;
}

std::set<CStrandPointModel::RowRecord>& CStrandPointModel::GetStrandRows(StrandType strandType, Float64 Xs)
{
   auto& found = m_StrandRows[strandType].find(Xs);
   if (found == m_StrandRows[strandType].end())
   {
      // strand row not found so create and cache it
      CComPtr <IPoint2dCollection> points;
      GetStrandPositions(strandType, Xs, &points);

      std::set<RowRecord> rows;
      IndexType nStrands;
      points->get_Count(&nStrands);
      for (IndexType strandIdx = 0; strandIdx < nStrands; strandIdx++)
      {
         CComPtr<IPoint2d> pnt;
         points->get_Item(strandIdx, &pnt);

         Float64 Y;
         pnt->get_Y(&Y);
         if (strandIdx == 0)
         {
            RowRecord row;
            row.Y = Y;
            row.Strands.push_back(strandIdx);
            rows.insert(row);
         }
         else
         {
            RowRecord row;
            row.Y = Y;
            auto found_row = rows.find(row);
            if (found_row == rows.end())
            {
               // this is a new row
               row.Strands.push_back(strandIdx);
               rows.insert(row);
            }
            else
            {
               const auto& existing_row = *found_row;
               // cast off const... we aren't changing the key so this is ok to do
               const_cast<RowRecord*>(&existing_row)->Strands.push_back(strandIdx);
            }
         }
      }

      auto result = m_StrandRows[strandType].insert(std::make_pair(Xs, rows));
      ATLASSERT(result.second == true);
      found = result.first;
   }

   return *(&(found->second));
}

Float64 CStrandPointModel::GetSectionHeight(Float64 Xs) const
{
   Float64 Hg;
   CComPtr<IShape> shape;
   m_pSegment->get_PrimaryShape(Xs, sbLeft, cstGirder, &shape);
   CComPtr<IRect2d> bbox;
   shape->get_BoundingBox(&bbox);
   bbox->get_Height(&Hg);
   return Hg;
}

HRESULT CStrandPointModel::GetStrandPosition(StrandType strandType, StrandIndexType strandIdx, Float64 Xs, IPoint2d** ppPoint) const
{
   // strand position in Girder Section coordinates (relative to top center of girder)
   const auto& strandRecord = m_Strands[strandType][strandIdx];

   Float64 Z1, Y1, Z2, Y2;
   ZoneType zone;
   GetStrandControlPoints(Xs, strandType, strandRecord, &Z1, &Y1, &Z2, &Y2, &zone);

   CComQIPtr<IThickenedFlangeSegment> thickenedFlangeSegment(m_pSegment);
   if (thickenedFlangeSegment)
   {
      // Y1 and Y2 are measured down from the top of the girder
      // With top flange thickening, these may not be at the same elevation
      // Adjust Y1 and Y2 so they are on the same elevation basis
      //
      //     +                                                   +
      //  ---|....                                           ....|
      //   ^ |    ........                           ........    |
      // Y1| |            ...........................            |
      //   v |                        | Y2                       |
      //  ---+---------------------------------------------------+

      Float64 Yadj1 = GetGirderDepthAdjustment(Z1); // elevation of end relative to elevation at Z1...if > 0, girder is taller at end
      Float64 Yadj2 = GetGirderDepthAdjustment(Z2);

      Y1 -= Yadj1;
      Y2 -= Yadj2;
   }

   Float64 Y = ::LinInterp(Xs - Z1, Y1, Y2, Z2 - Z1);
   Float64 X = strandRecord.X;

   if (strandType == Harped && (zone == ZoneType::LeftStraight || zone == ZoneType::MidStraight || zone == ZoneType::RightStraight ) )
   {
      Float64 pc1, pc2;
      m_pSegment->ComputePrecamber(Z1, &pc1);
      m_pSegment->ComputePrecamber(Z2, &pc2);
      Float64 pc = ::LinInterp(Xs - Z1, pc1, pc2, Z2 - Z1);

      Float64 py;
      m_pSegment->ComputePrecamber(Xs, &py);
      Y -= py-pc;
   }

   Float64 Xadj = GetGirderWidthAdjustment(Xs);
   X += Xadj;

   if (thickenedFlangeSegment)
   {
      Float64 Yadj = GetGirderDepthAdjustment(Xs);
      Y += Yadj;
   }

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(X, Y);

   return point.CopyTo(ppPoint);
}

Float64 CStrandPointModel::GetGirderDepthAdjustment(Float64 Xs) const
{
   Float64 Yadj = 0;
   CComQIPtr<ITaperedGirderSegment> taperedSegment(m_pSegment);
   CComQIPtr<IThickenedFlangeSegment> thickenedSegment(m_pSegment);
   if (taperedSegment || thickenedSegment)
   {
      Float64 Lg;
      m_pGirder->get_GirderLength(&Lg);

      Float64 Hstart, Hend;
      Hstart = GetSectionHeight(0.0);
      Hend = GetSectionHeight(Lg);

      Float64 H = ::LinInterp(Xs, Hstart, Hend, Lg);

      // Get actual height of section at distFromStart
      Float64 Hg = GetSectionHeight(Xs);

      // amount to vertically adjust the elevation of the strands
      Yadj = H - Hg;
   }

   return Yadj;
}
