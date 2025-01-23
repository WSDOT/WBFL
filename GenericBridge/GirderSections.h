///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

// GirderSections.h 

#ifndef INCLUDED_GIRDERSECTIONS_H_
#define INCLUDED_GIRDERSECTIONS_H_

#include "resource.h"       // main symbols
#include <GenericBridge\GirderSectionImpl.h>
#include <GenericBridge\Helpers.h>
#include <xutility>
#include <algorithm>
#include <functional>

class CFlangedBeam;
using CFlangedBeamImpl = CGirderSectionImpl<CFlangedBeam, &CLSID_FlangedGirderSection, IFlangedGirderSection, &IID_IFlangedGirderSection, IPrecastBeam, &CLSID_PrecastBeam>;

class CFlangedBeam : 
   public CFlangedBeamImpl,
   public IFlangedEndBlockSection
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDBEAM)

   BEGIN_COM_MAP(CFlangedBeam)
      COM_INTERFACE_ENTRY(IFlangedEndBlockSection)
      COM_INTERFACE_ENTRY_CHAIN(CFlangedBeamImpl)
   END_COM_MAP()
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = Min(t1,t2);
      return S_OK;
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D4(tFlange);
   }

// IFlangedEndBlockSection
public:
   STDMETHODIMP GetWebWidth(Float64* pT1, Float64* pT2) override
   {
      m_Beam->get_T1(pT1);
      m_Beam->get_T2(pT2);
      return S_OK;
   }

   STDMETHODIMP CreateEndBlockSection(Float64 Wt, Float64 Wb, IFlangedEndBlockSection** ppEndBlockSection) override
   {
      CComPtr<IShape> clone;
      Clone(&clone);

      CComQIPtr<IFlangedGirderSection> flanged_girder_section(clone);
      CComPtr<IPrecastBeam> beam;
      flanged_girder_section->get_Beam(&beam);

      AdjustForEndBlocks(beam, Wt, Wb);

      flanged_girder_section.QueryInterface(ppEndBlockSection);

      return S_OK;
   }

// IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      ATLASSERT(false); // should never get here... the top flange is not a riding surface
      return S_FALSE;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW,IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_D7(&D7);
      m_Beam->get_T1(&T1);
      m_Beam->get_T2(&T2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);
      m_Beam->get_W4(&W4);

      Float64 H = D1 + D2 + D3 + D4 + D5 + D6 + D7;

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      // put values in a vector, then we can sort and eliminate duplicate values
      std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

      if (IsZero(D3) && IsZero(W2))
      {
         vWebSections.emplace_back(-D1, T1 + 2 * (W1 + W2), _T("Top Flange"));
      }

      if (!IsZero(D3))
      {
         vWebSections.emplace_back(-(D1+D2), T1 + 2 * W2, _T("Top Flange - Fillet"));
      }

      vWebSections.emplace_back(-(D1 + D2 + D3), T1, IsZero(D3) ? _T("Top Flange - Web") : _T("Top Fillet - Web"));
      vWebSections.emplace_back(-H + D4 + D5 + D6,T2,IsZero(D6) ? _T("Bottom Flange - Web") : _T("Bottom Fillet - Web"));

      if (!IsZero(D6))
      {
         vWebSections.emplace_back(-H + D4 + D5, T2 + 2 * W4, _T("Bottom Flange - Fillet"));
      }

      if (IsZero(D6) && IsZero(W4))
      {
         vWebSections.emplace_back(-H + D4, T2 + 2 * (W3+W4), _T("Bottom Flange"));
      }

      // sort and remove duplicates at same elevation
      std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
      auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
      vWebSections.erase(new_end_iter, std::end(vWebSections));

      for (auto& webSection : vWebSections)
      {
         (*ppY)->Add(std::get<0>(webSection));
         (*ppW)->Add(std::get<1>(webSection));
         (*ppDesc)->Add(std::get<2>(webSection));
      }

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
   {
      CHECK_RETOBJ(ppArray);

      Float64 D1, D2, D3, D4, D5, D6, D7, T2;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_D7(&D7);
      m_Beam->get_T2(&T2);

      Float64 H = D1 + D2 + D3 + D4 + D5 + D6 + D7;

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T2 / 2, T2 / 2, -H, -H + D4 + D5 + D6);

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }
};

class CFlangedBeam2;
using CFlangedBeam2Impl = CGirderSectionImpl<CFlangedBeam2, &CLSID_FlangedGirderSection2, IFlangedGirderSection2, &IID_IFlangedGirderSection2, IPrecastBeam2, &CLSID_PrecastBeam2>;

class CFlangedBeam2 :
   public CFlangedBeam2Impl,
   public IFlangedEndBlockSection
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDBEAM2)

   BEGIN_COM_MAP(CFlangedBeam2)
      COM_INTERFACE_ENTRY(IFlangedEndBlockSection)
      COM_INTERFACE_ENTRY_CHAIN(CFlangedBeam2Impl)
   END_COM_MAP()

   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      Float64 t1, t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = Min(t1, t2);
      return S_OK;
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D6(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      return m_Beam->get_D6(tFlange);
   }


// IFlangedEndBlockSection
public:
   STDMETHODIMP GetWebWidth(Float64* pT1, Float64* pT2) override
   {
      m_Beam->get_T1(pT1);
      m_Beam->get_T2(pT2);
      return S_OK;
   }

   STDMETHODIMP CreateEndBlockSection(Float64 Wt, Float64 Wb, IFlangedEndBlockSection** ppEndBlockSection) override
   {
      CComPtr<IShape> clone;
      Clone(&clone);

      CComQIPtr<IFlangedGirderSection2> flanged_girder_section(clone);
      CComPtr<IPrecastBeam2> beam;
      flanged_girder_section->get_Beam(&beam);

      AdjustForEndBlocks(beam, Wt, Wb);

      flanged_girder_section.QueryInterface(ppEndBlockSection);

      return S_OK;
   }

// IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      ATLASSERT(false); // should never get here... the top flange is not a riding surface
      return S_FALSE;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_H(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, D6, H, T1, T2, W1, W2, W3, W4, W5;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_H(&H);
      m_Beam->get_T1(&T1);
      m_Beam->get_T2(&T2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);
      m_Beam->get_W4(&W4);
      m_Beam->get_W5(&W5);

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      // put values in a vector, then we can sort and eliminate duplicate values
      std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

      if (IsZero(D3) && IsZero(W3))
      {
         vWebSections.emplace_back(-D1, T1 + 2 * (W1 + W2 + W3), _T("Top Flange"));
      }

      if (!IsZero(D3))
      {
         vWebSections.emplace_back(-(D1 + D2), T1 + 2 * W3, _T("Top Flange - Fillet"));
      }

      vWebSections.emplace_back(-(D1 + D2 + D3), T1, IsZero(D3) ? _T("Top Flange - Web") : _T("Top Fillet - Web"));
      vWebSections.emplace_back(-H + D4 + D5 + D6, T2, IsZero(D4) ? _T("Bottom Flange - Web") : _T("Bottom Fillet - Web"));

      if (!IsZero(D4))
      {
         vWebSections.emplace_back(-H + D5 + D6, T2 + 2 * W4, _T("Bottom Flange - Fillet"));
      }

      if (IsZero(D4) && IsZero(W5))
      {
         vWebSections.emplace_back(-H + D6, T2 + 2 * (W4 + W5), _T("Bottom Flange"));
      }

      // sort and remove duplicates at same elevation
      std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
      auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
      vWebSections.erase(new_end_iter, std::end(vWebSections));

      for (auto& webSection : vWebSections)
      {
         (*ppY)->Add(std::get<0>(webSection));
         (*ppW)->Add(std::get<1>(webSection));
         (*ppDesc)->Add(std::get<2>(webSection));
      }

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
   {
      CHECK_RETOBJ(ppArray);

      Float64 D1, D2, D3, D4, D5, D6, H, T2;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_H(&H);
      m_Beam->get_T2(&T2);

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T2 / 2, T2 / 2, -H, -H + D4 + D5 + D6);

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }
};

class CBulbTeeSection;
using CBulbTeeSectionBase = CGirderSectionImpl<CBulbTeeSection, &CLSID_BulbTeeSection, IBulbTeeSection, &IID_IBulbTeeSection, IBulbTee2, &CLSID_BulbTee2>;
class CBulbTeeSection : 
   public CBulbTeeSectionBase,
   public IAsymmetricSection,
   public IFlangePoints,
   public IFlangedDeckedSection
{
BEGIN_COM_MAP(CBulbTeeSection)
   COM_INTERFACE_ENTRY(IAsymmetricSection)
   COM_INTERFACE_ENTRY(IJointedSection)
   COM_INTERFACE_ENTRY(IFlangePoints)
   COM_INTERFACE_ENTRY(IFlangedDeckedSection)
   COM_INTERFACE_ENTRY_CHAIN(CBulbTeeSectionBase)
END_COM_MAP()

protected:
   CComPtr<IShape> m_LeftJoint, m_RightJoint;

public:
   DECLARE_REGISTRY_RESOURCEID(IDR_BULBTEE)

// IGirderSection
   STDMETHODIMP get_WorkPoint(IPoint2d** ppWorkPoint)
   {
      CComQIPtr<IXYPosition> position(m_Beam);
      CComPtr<IPoint2d> pntHookPoint; // hook point is at bottom center of shape (not bottom center of bounding box)
      position->get_LocatorPoint(lpHookPoint, &pntHookPoint);

      // compute the location of the top center point without rotation
      // this is just the hook point offset vertically by the height of the beam shape
      Float64 Hmin, H, Hmax;
      GetHeight(&Hmin, &H, &Hmax);

      CComPtr<IPoint2d> pntUnRotatedTopCenter;
      pntHookPoint->Clone(&pntUnRotatedTopCenter);
      pntUnRotatedTopCenter->Offset(0, H);

      // the unrotated top center is also the unrotated work point
      pntUnRotatedTopCenter->Clone(ppWorkPoint);

      // apply the rotation to the work point
      (*ppWorkPoint)->RotateEx(pntHookPoint, m_Rotation);

      return S_OK;
   }

   STDMETHODIMP get_TopWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);
      m_Beam->get_W5(pLeft);
      m_Beam->get_W6(pRight);
      return S_OK;
   }

// IAsymmetricSection
   STDMETHODIMP GetTopWidth(Float64* pLeft, Float64* pRight) override
   {
      return get_TopWidth(pLeft, pRight);
   }

   STDMETHODIMP GetHeight(Float64* pHmin, Float64* pHcl, Float64* pHmax) override
   {
      CHECK_RETVAL(pHmin);
      CHECK_RETVAL(pHcl);
      CHECK_RETVAL(pHmax);

      m_Beam->get_MinHeight(pHmin);
      m_Beam->get_CLHeight(pHcl);
      m_Beam->get_MaxHeight(pHmax);

      return S_OK;
   }

   STDMETHODIMP GetStressPoints(StressPointType spType, IPoint2dCollection** ppPoints) override
   {
      CHECK_RETOBJ(ppPoints);
      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      if (spType == spTop)
      {
         CComPtr<IPoint2d> leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
         m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);
         points->Add(leftTop);
         points->Add(topCentral);
         points->Add(rightTop);
      }
      else
      {
         CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
         m_Beam->GetBottomFlangePoints(&leftTop, &leftBottom, &rightTop, &rightBottom);

         //                |   |
         //         +------+   +-------+
         //         |                  |
         //         |   Bot Flange     |
         // leftTop |                  | rightTop
         //         \------------------/  <-------------- chamfer
         //       leftBottom          rightBottom
         //         |       Wbf        |
         //         |<---------------->|

         // we want to use the fictitious corner at the projection of the vertical face
         // of the bottom flange and the bottom of the bottom flange (engineers will typically
         // hand check stresses using (+/-Wbf/2,Yb) so the chamfers are ignored

         Float64 x, y, dummy;
         leftTop->Location(&x, &dummy); // left side at top of chamfer
         leftBottom->Location(&dummy, &y); // left side, at right edge of chamfer

         CComPtr<IPoint2d> pntLeft(leftTop);
         pntLeft->Move(x, y);
         points->Add(pntLeft);

         rightTop->Location(&x, &dummy); // right side at top of chamfer
         rightBottom->Location(&dummy, &y); // right side at left edge of chamfer

         CComPtr<IPoint2d> pntRight(rightTop);
         pntRight->Move(x, y);
         points->Add(pntRight);
      }

      return points.CopyTo(ppPoints);
   }

   STDMETHODIMP IgnoreBiaxialBending(BOOL* pIgnoreBiaxial) override
   {
      CHECK_RETVAL(pIgnoreBiaxial);
      *pIgnoreBiaxial = false;
      return S_OK;
   }

// IJointedSection
public:
   STDMETHODIMP SetJointShapes(IShape* pLeftJoint, IShape* pRightJoint) override
   {
      m_LeftJoint = pLeftJoint;
      m_RightJoint = pRightJoint;
      return S_OK;
   }

   STDMETHODIMP GetJointShapes(IShape** ppLeftJoint, IShape** ppRightJoint) override
   {
      CHECK_RETOBJ(ppLeftJoint);
      CHECK_RETOBJ(ppRightJoint);

      if (m_LeftJoint)
      {
         m_LeftJoint->Clone(ppLeftJoint);
      }

      if (m_RightJoint)
      {
         m_RightJoint->Clone(ppRightJoint);
      }

      return S_OK;
   }

// IFlangePoints
public:
   STDMETHODIMP GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCL, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetTopFlangePoints(ppLeftTop, ppLeftBottom, ppTopCL, ppTopCentral, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetBottomFlangePoints(ppLeftTop, ppLeftBottom, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP get_OverallHeight(Float64* height) override
   {
      return m_Beam->get_MaxHeight(height);
   }

   STDMETHODIMP get_NominalHeight(Float64* height) override
   {
      // for bulb-tee girders, use the CL Web height as the nomainl girder height
      return m_Beam->get_CLHeight(height);
   }

   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = Min(t1,t2);
      return S_OK;
   }

	STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface) override
   {
      // total width is the width of our mating surface profile
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts-1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      *wMatingSurface = xe - xs;

      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* pLocation) override
   {
      // total width is the width of our mating surface profile. Profile can be offset from center on exterior beams
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts-1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      Float64 msglocation = (xs + xe) / 2.0; // in bridge coords

      CComPtr<IPoint2d> topCenter;
      get_LocatorPoint(lpTopCenter, &topCenter);
      Float64 tcloc;
      topCenter->get_X(&tcloc);

      Float64 location = msglocation - tcloc;

      *pLocation = location;


      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile) override
   {
      // overide the base class implentation with this
      CHECK_RETOBJ(ppProfile);

      CComPtr<IPoint2d> leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
      m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);

      if (bGirderOnly == VARIANT_FALSE)
      {
         if (m_LeftJoint)
         {
            leftTop.Release();
            CComQIPtr<IPolyShape> shape(m_LeftJoint);
            shape->get_Point(0, &leftTop);
         }

         if (m_RightJoint)
         {
            rightTop.Release();
            CComQIPtr<IPolyShape> shape(m_RightJoint);
            shape->get_Point(3, &rightTop);
         }
      }

      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      points->Add(leftTop);
      points->Add(topCentral);
      points->Add(rightTop);

      return points.CopyTo(ppProfile);
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D5(tFlange);
   }


   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      // location < 0 means the CL of the flange is to the left of the CL of the beam bounding box
      Float64 w5, w6;
      m_Beam->get_W5(&w5);
      m_Beam->get_W6(&w6);
      *location = 0.5*(w5 - w6);

      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      return get_TopFlangeLocation(idx, location);
   }

   // IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      Float64 D1;
      m_Beam->get_D1(&D1);
      ATLASSERT(sacDepth < D1);
      D1 -= sacDepth;
      m_Beam->put_D1(D1);

      if (m_LeftJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_LeftJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      if (m_RightJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_RightJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      return S_OK;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_CLHeight(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, D6, D7, T1, T2, W1, W2, W3, W4;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_D7(&D7);
      m_Beam->get_T1(&T1);
      m_Beam->get_T2(&T2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);
      m_Beam->get_W4(&W4);

      Float64 H = D1 + D2 + D3 + D4 + D5 + D6 + D7;

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      // put values in a vector, then we can sort and eliminate duplicate values
      std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

      if (IsZero(D3) && IsZero(W2))
      {
         vWebSections.emplace_back(-D1, T1 + 2 * (W1 + W2), _T("Top Flange"));
      }

      if (!IsZero(D3))
      {
         vWebSections.emplace_back(-(D1 + D2), T1 + 2 * W2, _T("Top Flange - Fillet"));
      }

      vWebSections.emplace_back(-(D1 + D2 + D3), T1, IsZero(D3) ? _T("Top Flange - Web") : _T("Top Fillet - Web"));
      vWebSections.emplace_back(-H + D4 + D5 + D6, T2, IsZero(D6) ? _T("Bottom Flange - Web") : _T("Bottom Fillet - Web"));

      if (!IsZero(D6))
      {
         vWebSections.emplace_back(-H + D4 + D5, T2 + 2 * W4, _T("Bottom Flange - Fillet"));
      }

      if (IsZero(D6) && IsZero(W4))
      {
         vWebSections.emplace_back(-H + D4, T2 + 2 * (W3 + W4), _T("Bottom Flange"));
      }

      // sort and remove duplicates at same elevation
      std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
      auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
      vWebSections.erase(new_end_iter, std::end(vWebSections));

      for (auto& webSection : vWebSections)
      {
         (*ppY)->Add(std::get<0>(webSection));
         (*ppW)->Add(std::get<1>(webSection));
         (*ppDesc)->Add(std::get<2>(webSection));
      }

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray) override
   {
      CHECK_RETOBJ(ppArray);

      Float64 D1, D2, D3, D4, D5, D6, D7, T2;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_D7(&D7);
      m_Beam->get_T2(&T2);

      Float64 H = D1 + D2 + D3 + D4 + D5 + D6 + D7;

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T2 / 2, T2 / 2, -H, -H + D4 + D5 + D6);

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }

   // IFlangedDeckedSection
   STDMETHODIMP GetOverhangs(Float64* pLeft, Float64* pRight)
   {
      m_Beam->get_W5(pLeft);
      m_Beam->get_W6(pRight);
      return S_OK;
   }
   STDMETHODIMP GetCrown(Float64* pC) override
   {
      return m_Beam->get_C2(pC);
   }
   STDMETHODIMP GetCrownSlopes(Float64* pLeft, Float64* pRight) override
   {
      m_Beam->get_n1(pLeft);
      m_Beam->get_n2(pRight);
      return S_OK;
   }
   STDMETHODIMP GetMaxHeight(Float64* pH) override
   {
      return m_Beam->get_MaxHeight(pH);
   }
   STDMETHODIMP GetCLHeight(Float64* pCL) override
   {
      return m_Beam->get_CLHeight(pCL);
   }
   STDMETHODIMP GetBottomCLPoint(IPoint2d** ppPoint) override
   {
      CHECK_RETOBJ(ppPoint);
      return m_Beam->get_HookPoint(ppPoint);
   }
   STDMETHODIMP AddTopFlangeThickening(Float64 topFlangeThickening) override
   {
      Float64 D1;
      m_Beam->get_D1(&D1);
      D1 += topFlangeThickening;
      m_Beam->put_D1(D1);
      return S_OK;
   }

};

class CNUGirderSection : 
   public CGirderSectionImpl<CNUGirderSection,&CLSID_NUGirderSection,
                             INUGirderSection,&IID_INUGirderSection,
                             INUBeam,&CLSID_NUBeam>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_NUGIRDERSECTION)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      return m_Beam->get_T(tWeb);
   }
	   
   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D5(tf); // NUBeam
   } 

   STDMETHODIMP get_TopFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D5(tFlange);
   }

// IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      ATLASSERT(false); // should never get here... the top flange is not a riding surface
      return S_FALSE;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, R1, R2, W1, W2, T;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_R1(&R1);
      m_Beam->get_R2(&R2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_T(&T);

      Float64 H = D1 + D2 + D3 + D4 + D5;

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      Float64 delta = atan2((W1 - T), 2 * D2);
      (*ppY)->Add(-(D1 + D2 + R1*tan(delta / 2)));
      (*ppW)->Add(T);
      (*ppDesc)->Add(CComBSTR(_T("Top Flange - Web")));

      delta = atan2((W2 - T), 2 * D4);
      (*ppY)->Add(-H + D4 + D5 + R2*tan(delta / 2));
      (*ppW)->Add(T);
      (*ppDesc)->Add(CComBSTR(_T("Bottom Flange - Web")));

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
   {
      CHECK_RETOBJ(ppArray);

      Float64 D1, D2, D3, D4, D5, R1, R2, W1, W2, T;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_R1(&R1);
      m_Beam->get_R2(&R2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_T(&T);

      Float64 H = D1 + D2 + D3 + D4 + D5;

      Float64 delta = atan2((W2 - T), 2 * D4);

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T / 2, T / 2, -H, -H + D4 + D5 + R2*tan(delta / 2));

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }
};

class CNUDeckedBulbTeeSection;
using CNUDeckedBulbTeeSectionBase = CGirderSectionImpl<CNUDeckedBulbTeeSection, &CLSID_NUDeckedBulbTeeSection, INUDeckedBulbTeeSection, &IID_INUDeckedBulbTeeSection, INUDeckedIBeam, &CLSID_NUDeckedIBeam>;
class CNUDeckedBulbTeeSection :
   public CNUDeckedBulbTeeSectionBase,
   //public IAsymmetricSection,
   public IFlangePoints,
   public IFlangedDeckedSection
{
   BEGIN_COM_MAP(CNUDeckedBulbTeeSection)
      //COM_INTERFACE_ENTRY(IAsymmetricSection)
      COM_INTERFACE_ENTRY(IJointedSection)
      COM_INTERFACE_ENTRY(IFlangePoints)
      COM_INTERFACE_ENTRY(IFlangedDeckedSection)
      COM_INTERFACE_ENTRY_CHAIN(CNUDeckedBulbTeeSectionBase)
   END_COM_MAP()

protected:
   CComPtr<IShape> m_LeftJoint, m_RightJoint;

public:
   DECLARE_REGISTRY_RESOURCEID(IDR_NUDECKEDBULBTEESECTION)

   // IGirderSection
   STDMETHODIMP get_WorkPoint(IPoint2d** ppWorkPoint)
   {
      CComPtr<IPoint2d> pntLeftTop, pntLeftBottom, pntTopCL, pntRightTop, pntRightBottom;
      m_Beam->GetTopFlangePoints(&pntLeftTop, &pntLeftBottom, &pntTopCL, ppWorkPoint, &pntRightTop, &pntRightBottom);
      return S_OK;
   }

   STDMETHODIMP get_TopWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);

      Float64 w1, w2, w3;
      m_Beam->get_W1(&w1);
      m_Beam->get_W2(&w2);
      m_Beam->get_W3(&w3);
      Float64 width = w1 + 2 * (w2 + w3);
      *pLeft = width / 2;
      *pRight = *pLeft;
      return S_OK;
   }

   //// IAsymmetricSection
   //STDMETHODIMP GetTopWidth(Float64* pLeft, Float64* pRight) override
   //{
   //    return get_TopWidth(pLeft, pRight);
   //}

   //STDMETHODIMP GetHeight(Float64* pHmin, Float64* pHcl, Float64* pHmax) override
   //{
   //    CHECK_RETVAL(pHmin);
   //    CHECK_RETVAL(pHcl);
   //    CHECK_RETVAL(pHmax);

   //    m_Beam->get_MinHeight(pHmin);
   //    m_Beam->get_CLHeight(pHcl);
   //    m_Beam->get_MaxHeight(pHmax);

   //    return S_OK;
   //}

   //STDMETHODIMP GetStressPoints(StressPointType spType, IPoint2dCollection** ppPoints) override
   //{
   //    CHECK_RETOBJ(ppPoints);
   //    CComPtr<IPoint2dCollection> points;
   //    points.CoCreateInstance(CLSID_Point2dCollection);

   //    if (spType == spTop)
   //    {
   //        CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
   //        m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCentral, &rightTop, &rightBottom);
   //        points->Add(leftTop);
   //        points->Add(topCentral);
   //        points->Add(rightTop);
   //    }
   //    else
   //    {
   //        CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
   //        m_Beam->GetBottomFlangePoints(&leftTop, &leftBottom, &rightTop, &rightBottom);

   //        //                |   |
   //        //         +------+   +-------+
   //        //         |                  |
   //        //         |   Bot Flange     |
   //        // leftTop |                  | rightTop
   //        //         \------------------/  <-------------- chamfer
   //        //       leftBottom          rightBottom
   //        //         |       Wbf        |
   //        //         |<---------------->|

   //        // we want to use the fictitious corner at the projection of the vertical face
   //        // of the bottom flange and the bottom of the bottom flange (engineers will typically
   //        // hand check stresses using (+/-Wbf/2,Yb) so the chamfers are ignored

   //        Float64 x, y, dummy;
   //        leftTop->Location(&x, &dummy); // left side at top of chamfer
   //        leftBottom->Location(&dummy, &y); // left side, at right edge of chamfer

   //        CComPtr<IPoint2d> pntLeft(leftTop);
   //        pntLeft->Move(x, y);
   //        points->Add(pntLeft);

   //        rightTop->Location(&x, &dummy); // right side at top of chamfer
   //        rightBottom->Location(&dummy, &y); // right side at left edge of chamfer

   //        CComPtr<IPoint2d> pntRight(rightTop);
   //        pntRight->Move(x, y);
   //        points->Add(pntRight);
   //    }

   //    return points.CopyTo(ppPoints);
   //}

   //STDMETHODIMP IgnoreBiaxialBending(BOOL* pIgnoreBiaxial) override
   //{
   //    CHECK_RETVAL(pIgnoreBiaxial);
   //    *pIgnoreBiaxial = false;
   //    return S_OK;
   //}

   // IJointedSection
public:
   STDMETHODIMP SetJointShapes(IShape* pLeftJoint, IShape* pRightJoint) override
   {
      m_LeftJoint = pLeftJoint;
      m_RightJoint = pRightJoint;
      return S_OK;
   }

   STDMETHODIMP GetJointShapes(IShape** ppLeftJoint, IShape** ppRightJoint) override
   {
      CHECK_RETOBJ(ppLeftJoint);
      CHECK_RETOBJ(ppRightJoint);

      if (m_LeftJoint)
      {
         m_LeftJoint->Clone(ppLeftJoint);
      }

      if (m_RightJoint)
      {
         m_RightJoint->Clone(ppRightJoint);
      }

      return S_OK;
   }

   // IFlangePoints
public:
   STDMETHODIMP GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCL, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetTopFlangePoints(ppLeftTop, ppLeftBottom, ppTopCL, ppTopCentral, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetBottomFlangePoints(ppLeftTop, ppLeftBottom, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP get_OverallHeight(Float64* height) override
   {
      return m_Beam->get_H(height);
   }

   STDMETHODIMP get_NominalHeight(Float64* height) override
   {
      // for bulb-tee girders, use the CL Web height as the nomainl girder height
      return m_Beam->get_H(height);
   }

   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      m_Beam->get_T(tWeb);
      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* wMatingSurface) override
   {
      // total width is the width of our mating surface profile
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts - 1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      *wMatingSurface = xe - xs;

      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* pLocation) override
   {
      *pLocation = 0;
      return S_OK;
      //// total width is the width of our mating surface profile. Profile can be offset from center on exterior beams
      //CComPtr<IPoint2dCollection> points;
      //get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      //IndexType npts;
      //points->get_Count(&npts);
      //CComPtr<IPoint2d> ps, pe;
      //points->get_Item(0, &ps);
      //points->get_Item(npts - 1, &pe);

      //Float64 xs, xe;
      //ps->get_X(&xs);
      //pe->get_X(&xe);

      //Float64 msglocation = (xs + xe) / 2.0; // in bridge coords

      //CComPtr<IPoint2d> topCenter;
      //get_LocatorPoint(lpTopCenter, &topCenter);
      //Float64 tcloc;
      //topCenter->get_X(&tcloc);

      //Float64 location = msglocation - tcloc;

      //*pLocation = location;


      //return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile) override
   {
      // overide the base class implentation with this
      CHECK_RETOBJ(ppProfile);

      CComPtr<IPoint2d> leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
      m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);

      if (bGirderOnly == VARIANT_FALSE)
      {
         if (m_LeftJoint)
         {
            leftTop.Release();
            CComQIPtr<IPolyShape> shape(m_LeftJoint);
            shape->get_Point(0, &leftTop);
         }

         if (m_RightJoint)
         {
            rightTop.Release();
            CComQIPtr<IPolyShape> shape(m_RightJoint);
            shape->get_Point(3, &rightTop);
         }
      }

      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      points->Add(leftTop);
      points->Add(topCentral);
      points->Add(rightTop);

      return points.CopyTo(ppProfile);
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D5(tFlange);
   }


   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      // location < 0 means the CL of the flange is to the left of the CL of the beam bounding box
      *location = 0.0;
      //Float64 w5, w6;
      //m_Beam->get_W5(&w5);
      //m_Beam->get_W6(&w6);
      //*location = 0.5 * (w5 - w6);

      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      return get_TopFlangeLocation(idx, location);
   }

   // IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      Float64 D1;
      m_Beam->get_D1(&D1);
      ATLASSERT(sacDepth < D1);
      D1 -= sacDepth;
      m_Beam->put_D1(D1);

      if (m_LeftJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_LeftJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      if (m_RightJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_RightJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      return S_OK;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_H(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, D6, H, T, R1, R2, W1, W2, W3, W4;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_H(&H);
      m_Beam->get_T(&T);
      m_Beam->get_R1(&R1);
      m_Beam->get_R2(&R2);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);
      m_Beam->get_W4(&W4);

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      // put values in a vector, then we can sort and eliminate duplicate values
      std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

      vWebSections.emplace_back(-(D3 + R1), T, _T("Top Flange - Web"));

      Float64 delta = atan2(W4 - T, 2 * (D5 - D6));
      vWebSections.emplace_back(-(H - D5 - R2 * tan(delta / 2)), T, _T("Bottom Flange - Web"));

      // sort and remove duplicates at same elevation
      std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
      auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
      vWebSections.erase(new_end_iter, std::end(vWebSections));

      for (auto& webSection : vWebSections)
      {
         (*ppY)->Add(std::get<0>(webSection));
         (*ppW)->Add(std::get<1>(webSection));
         (*ppDesc)->Add(std::get<2>(webSection));
      }

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray) override
   {
      CHECK_RETOBJ(ppArray);

      Float64 H, T, D5, D6, R2, W4;
      m_Beam->get_H(&H);
      m_Beam->get_T(&T);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_R2(&R2);
      m_Beam->get_W4(&W4);

      Float64 delta = atan2(W4 - T, 2 * (D5 - D6));

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T / 2, T / 2, -H, -H + D5 + R2 * tan(delta / 2));

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }

   // IFlangedDeckedSection
   STDMETHODIMP GetOverhangs(Float64* pLeft, Float64* pRight)
   {
      Float64 W1, W2, W3;
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);

      Float64 overhang = W1 / 2 + W2 + W3;

      *pLeft = overhang;
      *pRight = overhang;

      return S_OK;
   }

   STDMETHODIMP GetCrown(Float64* pC) override
   {
      return GetOverhangs(pC, pC);
   }

   STDMETHODIMP GetCrownSlopes(Float64* pLeft, Float64* pRight) override
   {
      *pLeft = 0;
      *pRight = 0;
      return S_OK;
   }
   STDMETHODIMP GetMaxHeight(Float64* pH) override
   {
      return m_Beam->get_H(pH);
   }

   STDMETHODIMP GetCLHeight(Float64* pCL) override
   {
      return m_Beam->get_H(pCL);
   }

   STDMETHODIMP GetBottomCLPoint(IPoint2d** ppPoint) override
   {
      CHECK_RETOBJ(ppPoint);
      return m_Beam->get_HookPoint(ppPoint);
   }

   STDMETHODIMP AddTopFlangeThickening(Float64 topFlangeThickening) override
   {
      Float64 D1;
      m_Beam->get_D1(&D1);
      D1 += topFlangeThickening;
      m_Beam->put_D1(D1);
      return S_OK;
   }

};

class CPCIDeckedBulbTeeSection;
using CPCIDeckedBulbTeeSectionBase = CGirderSectionImpl<CPCIDeckedBulbTeeSection, &CLSID_PCIDeckedBulbTeeSection, IPCIDeckedBulbTeeSection, &IID_IPCIDeckedBulbTeeSection, IPCIDeckedIBeam, &CLSID_PCIDeckedIBeam>;
class CPCIDeckedBulbTeeSection :
   public CPCIDeckedBulbTeeSectionBase,
   //public IAsymmetricSection,
   public IFlangePoints,
   public IFlangedDeckedSection
{
   BEGIN_COM_MAP(CPCIDeckedBulbTeeSection)
      //COM_INTERFACE_ENTRY(IAsymmetricSection)
      COM_INTERFACE_ENTRY(IJointedSection)
      COM_INTERFACE_ENTRY(IFlangePoints)
      COM_INTERFACE_ENTRY(IFlangedDeckedSection)
      COM_INTERFACE_ENTRY_CHAIN(CPCIDeckedBulbTeeSectionBase)
   END_COM_MAP()

protected:
   CComPtr<IShape> m_LeftJoint, m_RightJoint;

public:
   DECLARE_REGISTRY_RESOURCEID(IDR_PCIDECKEDBULBTEESECTION)

   // IGirderSection
   STDMETHODIMP get_WorkPoint(IPoint2d** ppWorkPoint)
   {
      CComPtr<IPoint2d> pntLeftTop, pntLeftBottom, pntTopCL, pntRightTop, pntRightBottom;
      m_Beam->GetTopFlangePoints(&pntLeftTop, &pntLeftBottom, &pntTopCL, ppWorkPoint, &pntRightTop, &pntRightBottom);
      return S_OK;
   }

   STDMETHODIMP get_TopWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);

      Float64 w1, w2;
      m_Beam->get_W1(&w1);
      m_Beam->get_W2(&w2);
      Float64 width = w1 + 2 * w2;
      *pLeft = width / 2;
      *pRight = *pLeft;
      return S_OK;
   }

   STDMETHODIMP get_MinTopFlangeThickness(Float64* tf) override
   {
      CHECK_RETVAL(tf);
      return m_Beam->get_D7(tf);
   }

   //// IAsymmetricSection
   //STDMETHODIMP GetTopWidth(Float64* pLeft, Float64* pRight) override
   //{
   //    return get_TopWidth(pLeft, pRight);
   //}

   //STDMETHODIMP GetHeight(Float64* pHmin, Float64* pHcl, Float64* pHmax) override
   //{
   //    CHECK_RETVAL(pHmin);
   //    CHECK_RETVAL(pHcl);
   //    CHECK_RETVAL(pHmax);

   //    m_Beam->get_MinHeight(pHmin);
   //    m_Beam->get_CLHeight(pHcl);
   //    m_Beam->get_MaxHeight(pHmax);

   //    return S_OK;
   //}

   //STDMETHODIMP GetStressPoints(StressPointType spType, IPoint2dCollection** ppPoints) override
   //{
   //    CHECK_RETOBJ(ppPoints);
   //    CComPtr<IPoint2dCollection> points;
   //    points.CoCreateInstance(CLSID_Point2dCollection);

   //    if (spType == spTop)
   //    {
   //        CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
   //        m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCentral, &rightTop, &rightBottom);
   //        points->Add(leftTop);
   //        points->Add(topCentral);
   //        points->Add(rightTop);
   //    }
   //    else
   //    {
   //        CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
   //        m_Beam->GetBottomFlangePoints(&leftTop, &leftBottom, &rightTop, &rightBottom);

   //        //                |   |
   //        //         +------+   +-------+
   //        //         |                  |
   //        //         |   Bot Flange     |
   //        // leftTop |                  | rightTop
   //        //         \------------------/  <-------------- chamfer
   //        //       leftBottom          rightBottom
   //        //         |       Wbf        |
   //        //         |<---------------->|

   //        // we want to use the fictitious corner at the projection of the vertical face
   //        // of the bottom flange and the bottom of the bottom flange (engineers will typically
   //        // hand check stresses using (+/-Wbf/2,Yb) so the chamfers are ignored

   //        Float64 x, y, dummy;
   //        leftTop->Location(&x, &dummy); // left side at top of chamfer
   //        leftBottom->Location(&dummy, &y); // left side, at right edge of chamfer

   //        CComPtr<IPoint2d> pntLeft(leftTop);
   //        pntLeft->Move(x, y);
   //        points->Add(pntLeft);

   //        rightTop->Location(&x, &dummy); // right side at top of chamfer
   //        rightBottom->Location(&dummy, &y); // right side at left edge of chamfer

   //        CComPtr<IPoint2d> pntRight(rightTop);
   //        pntRight->Move(x, y);
   //        points->Add(pntRight);
   //    }

   //    return points.CopyTo(ppPoints);
   //}

   //STDMETHODIMP IgnoreBiaxialBending(BOOL* pIgnoreBiaxial) override
   //{
   //    CHECK_RETVAL(pIgnoreBiaxial);
   //    *pIgnoreBiaxial = false;
   //    return S_OK;
   //}

   // IJointedSection
public:
   STDMETHODIMP SetJointShapes(IShape* pLeftJoint, IShape* pRightJoint) override
   {
      m_LeftJoint = pLeftJoint;
      m_RightJoint = pRightJoint;
      return S_OK;
   }

   STDMETHODIMP GetJointShapes(IShape** ppLeftJoint, IShape** ppRightJoint) override
   {
      CHECK_RETOBJ(ppLeftJoint);
      CHECK_RETOBJ(ppRightJoint);

      if (m_LeftJoint)
      {
         m_LeftJoint->Clone(ppLeftJoint);
      }

      if (m_RightJoint)
      {
         m_RightJoint->Clone(ppRightJoint);
      }

      return S_OK;
   }

   // IFlangePoints
public:
   STDMETHODIMP GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCL, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetTopFlangePoints(ppLeftTop, ppLeftBottom, ppTopCL, ppTopCentral, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetBottomFlangePoints(ppLeftTop, ppLeftBottom, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP get_OverallHeight(Float64* height) override
   {
      return m_Beam->get_H(height);
   }

   STDMETHODIMP get_NominalHeight(Float64* height) override
   {
      // for bulb-tee girders, use the CL Web height as the nomainl girder height
      return m_Beam->get_H(height);
   }

   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      m_Beam->get_T(tWeb);
      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* wMatingSurface) override
   {
      // total width is the width of our mating surface profile
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts - 1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      *wMatingSurface = xe - xs;

      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* pLocation) override
   {
      *pLocation = 0;
      return S_OK;
      //// total width is the width of our mating surface profile. Profile can be offset from center on exterior beams
      //CComPtr<IPoint2dCollection> points;
      //get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      //IndexType npts;
      //points->get_Count(&npts);
      //CComPtr<IPoint2d> ps, pe;
      //points->get_Item(0, &ps);
      //points->get_Item(npts - 1, &pe);

      //Float64 xs, xe;
      //ps->get_X(&xs);
      //pe->get_X(&xe);

      //Float64 msglocation = (xs + xe) / 2.0; // in bridge coords

      //CComPtr<IPoint2d> topCenter;
      //get_LocatorPoint(lpTopCenter, &topCenter);
      //Float64 tcloc;
      //topCenter->get_X(&tcloc);

      //Float64 location = msglocation - tcloc;

      //*pLocation = location;


      //return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile) override
   {
      // overide the base class implentation with this
      CHECK_RETOBJ(ppProfile);

      CComPtr<IPoint2d> leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
      m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);

      if (bGirderOnly == VARIANT_FALSE)
      {
         if (m_LeftJoint)
         {
            leftTop.Release();
            CComQIPtr<IPolyShape> shape(m_LeftJoint);
            shape->get_Point(0, &leftTop);
         }

         if (m_RightJoint)
         {
            rightTop.Release();
            CComQIPtr<IPolyShape> shape(m_RightJoint);
            shape->get_Point(3, &rightTop);
         }
      }

      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      points->Add(leftTop);
      points->Add(topCentral);
      points->Add(rightTop);

      return points.CopyTo(ppProfile);
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D9(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D7(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(IndexType idx, Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D5(tFlange);
   }


   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      // location < 0 means the CL of the flange is to the left of the CL of the beam bounding box
      *location = 0.0;
      //Float64 w5, w6;
      //m_Beam->get_W5(&w5);
      //m_Beam->get_W6(&w6);
      //*location = 0.5 * (w5 - w6);

      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      return get_TopFlangeLocation(idx, location);
   }

   // IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      Float64 D1, D2;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      ATLASSERT(sacDepth < D1);
      ATLASSERT(sacDepth < D2);
      D1 -= sacDepth;
      D2 -= sacDepth;
      m_Beam->put_D1(D1);
      m_Beam->put_D2(D2);

      if (m_LeftJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_LeftJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      if (m_RightJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_RightJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      return S_OK;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_H(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }

   STDMETHODIMP GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc) override
   {
      Float64 D1, D2, D3, D4, D5, D6, D7, D8, D9, H, T, R1, R2, R3, W1, W2, W3, W4, W5, W6;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      m_Beam->get_D3(&D3);
      m_Beam->get_D4(&D4);
      m_Beam->get_D5(&D5);
      m_Beam->get_D6(&D6);
      m_Beam->get_D7(&D7);
      m_Beam->get_D8(&D8);
      m_Beam->get_D9(&D9);
      m_Beam->get_H(&H);
      m_Beam->get_T(&T);
      m_Beam->get_R1(&R1);
      m_Beam->get_R2(&R2);
      m_Beam->get_R3(&R3);
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);
      m_Beam->get_W3(&W3);
      m_Beam->get_W4(&W4);
      m_Beam->get_W5(&W5);
      m_Beam->get_W6(&W6);

      CComPtr<IDblArray> y;
      y.CoCreateInstance(CLSID_DblArray);
      y.CopyTo(ppY);

      CComPtr<IDblArray> w;
      w.CoCreateInstance(CLSID_DblArray);
      w.CopyTo(ppW);

      CComPtr<IBstrArray> desc;
      desc.CoCreateInstance(CLSID_BstrArray);
      desc.CopyTo(ppDesc);

      // put values in a vector, then we can sort and eliminate duplicate values
      std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

      vWebSections.emplace_back(-(D6 + R1), T, _T("Top Flange - Web"));

      Float64 delta = atan2(W6 - T, 2 * (D8 - D9));
      vWebSections.emplace_back(-(H - D8 - R2 * tan(delta / 2)), T, _T("Bottom Flange - Web"));

      // sort and remove duplicates at same elevation
      std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
      auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
      vWebSections.erase(new_end_iter, std::end(vWebSections));

      for (auto& webSection : vWebSections)
      {
         (*ppY)->Add(std::get<0>(webSection));
         (*ppW)->Add(std::get<1>(webSection));
         (*ppDesc)->Add(std::get<2>(webSection));
      }

      return S_OK;
   }

   STDMETHODIMP GetWebWidthProjectionsForDebonding(IUnkArray** ppArray) override
   {
      CHECK_RETOBJ(ppArray);

      Float64 H, T, D8, D9, R2, W6;
      m_Beam->get_H(&H);
      m_Beam->get_T(&T);
      m_Beam->get_D8(&D8);
      m_Beam->get_D9(&D9);
      m_Beam->get_R2(&R2);
      m_Beam->get_W6(&W6);

      Float64 delta = atan2(W6 - T, 2 * (D8 - D9));

      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-T / 2, T / 2, -H, -H + D8 + R2 * tan(delta / 2));

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      array->Add(rect);

      array.CopyTo(ppArray);
      return S_OK;
   }

   // IFlangedDeckedSection
   STDMETHODIMP GetOverhangs(Float64* pLeft, Float64* pRight)
   {
      Float64 W1, W2;
      m_Beam->get_W1(&W1);
      m_Beam->get_W2(&W2);

      Float64 overhang = W1 / 2 + W2;

      *pLeft = overhang;
      *pRight = overhang;

      return S_OK;
   }

   STDMETHODIMP GetCrown(Float64* pC) override
   {
      return GetOverhangs(pC, pC);
   }

   STDMETHODIMP GetCrownSlopes(Float64* pLeft, Float64* pRight) override
   {
      *pLeft = 0;
      *pRight = 0;
      return S_OK;
   }
   STDMETHODIMP GetMaxHeight(Float64* pH) override
   {
      return m_Beam->get_H(pH);
   }

   STDMETHODIMP GetCLHeight(Float64* pCL) override
   {
      return m_Beam->get_H(pCL);
   }

   STDMETHODIMP GetBottomCLPoint(IPoint2d** ppPoint) override
   {
      CHECK_RETOBJ(ppPoint);
      return m_Beam->get_HookPoint(ppPoint);
   }

   STDMETHODIMP AddTopFlangeThickening(Float64 topFlangeThickening) override
   {
      Float64 D1, D2;
      m_Beam->get_D1(&D1);
      m_Beam->get_D2(&D2);
      D1 += topFlangeThickening;
      D2 += topFlangeThickening;
      m_Beam->put_D1(D1);
      m_Beam->put_D2(D2);
      return S_OK;
   }

};

#endif //  INCLUDED_GIRDERSECTIONS_H_