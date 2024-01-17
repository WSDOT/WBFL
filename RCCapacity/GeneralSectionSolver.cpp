///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// GeneralSectionSolver.cpp : Implementation of CGeneralSectionSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "GeneralSectionSolver.h"
#include "GeneralSectionSolution.h"
#include "GeneralSectionSlice.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#include <algorithm>

#if defined _DEBUG_LOGGING
#include <sstream>
#include <iomanip>
#include <Units\Units.h>

#define VALUE(_x_) (IsZero(_x_)  ? 0 : _x_)
#define LENGTH(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch))
#define AREA(_x_)   (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch2))
#define STRESS(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KSI))
#define FORCE(_x_)  (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Kip))
#define MOMENT(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KipFeet))
#endif // _DEBUG_LOGGING

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSectionSolver
HRESULT CGeneralSectionSolver::FinalConstruct()
{
   m_NeutralAxis.CoCreateInstance(CLSID_Line2d);
   m_TestLine.CoCreateInstance(CLSID_Line2d);
   m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   m_ClippingRect.CoCreateInstance(CLSID_Rect2d);
   return S_OK;
}

void CGeneralSectionSolver::FinalRelease()
{
}


STDMETHODIMP CGeneralSectionSolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSectionSolver,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSectionSolver
STDMETHODIMP CGeneralSectionSolver::putref_Section(IGeneralSection* pSection)
{
   CHECK_IN(pSection);
   m_Section = pSection;

   m_bDecomposed = false;

   return S_OK;
}

STDMETHODIMP CGeneralSectionSolver::get_Section(IGeneralSection** pSection)
{
   CHECK_RETOBJ(pSection);
   (*pSection) = m_Section;
   if ( *pSection )
      (*pSection)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSectionSolver::put_Slices(long nSlices)
{
   m_nSlices = nSlices;
   m_bDecomposed = false;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolver::get_Slices(long* nSlices)
{
   CHECK_RETVAL(nSlices);
   *nSlices = m_nSlices;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolver::put_SliceGrowthFactor(Float64 sliceGrowthFactor)
{
   if ( sliceGrowthFactor < 0 )
      return E_INVALIDARG;

   m_SliceGrowthFactor = sliceGrowthFactor;
   return S_OK;
}

STDMETHODIMP CGeneralSectionSolver::get_SliceGrowthFactor(Float64* sliceGrowthFactor)
{
   CHECK_RETVAL(sliceGrowthFactor);
   *sliceGrowthFactor = m_SliceGrowthFactor;
   return S_OK;
}

#define COMPRESSION(_f_)  (_f_ < 0 ? 1 : 0)*(_f_)
#define TENSION(_f_)      (_f_ > 0 ? 1 : 0)*(_f_)

#define COMPRESSION_CG(_p_,_f_,_slice_) {Float64 _Xcg,_Ycg; _slice_.pntCG->Location(&_Xcg,&_Ycg); _p_->Offset( COMPRESSION(_f_)*_Xcg, COMPRESSION(_f_)*_Ycg ); }
#define TENSION_CG(_p_,_f_,_slice_)     {Float64 _Xcg,_Ycg; _slice_.pntCG->Location(&_Xcg,&_Ycg); _p_->Offset( TENSION(_f_)*_Xcg,     TENSION(_f_)*_Ycg ); }

STDMETHODIMP CGeneralSectionSolver::Solve(IPlane3d* incrementalStrainPlane,IGeneralSectionSolution** solution)
{
#if defined _DEBUG_LOGGING
   USES_CONVERSION;
#endif // _DEBUG_LOGGING

   CHECK_IN(incrementalStrainPlane);

   // don't use the regular CHECK_RETOBJ because it is ok if *solution is not nullptr
   // recycling solution objects will be faster than creating new ones each time
   if ( solution == nullptr )
      return E_INVALIDARG;

   HRESULT hr;

   if ( m_Section == nullptr )
      return Error(IDS_E_SECTION,IID_IGeneralSectionSolver,RC_E_SECTION);

   CComPtr<IUnkArray> slices;
   slices.CoCreateInstance(CLSID_UnkArray);

   DecomposeSection(incrementalStrainPlane);

   Float64 C  = 0; // sum of compression forces
   Float64 T  = 0; // sum of tension forces
   CComPtr<IPoint2d> cgC; // cg of compression force
   CComPtr<IPoint2d> cgT; // cg of tension force

   cgC.CoCreateInstance(CLSID_Point2d);
   cgT.CoCreateInstance(CLSID_Point2d);
   cgC->Move(0,0);
   cgT->Move(0,0);

   Float64 p  = 0;
   Float64 mx = 0;
   Float64 my = 0;

   bool bExceededStrainLimits = false;

   // get distance from origin to neutral axis line
   Float64 Yna;
   CComPtr<IVector2d> v;
   m_NeutralAxis->GetImplicit(&Yna,&v);

#if defined _DEBUG_LOGGING
   CComPtr<IWBFLErrorLog> log;
   log.CoCreateInstance(CLSID_WBFLErrorLog);
   DWORD cookie;
   log->Open(CComBSTR("GeneralSectionSolver.log"),&cookie);
   std::_tostringstream os;
   os << "Neutral Axis Location: " << LENGTH(Yna) << std::endl;
   Float64 _dir;
   v->get_Direction(&_dir);
   os << "Neutral Axis Direction: " << VALUE( (_dir-PI_OVER_2)*180./M_PI) << std::endl;
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "initial strain, " << std::setw(20) << "strain, " << std::setw(20) << "fg material, " << std::setw(10) << "fg stress, "  << std::setw(20) << "bg material, " << std::setw(10) << "bg stress, " << std::setw(10) << "stress, " << std::setw(10) << "force" << std::endl;
#endif // _DEBUG_LOGGING

   for(auto& slice : m_Slices)
   {
      Float64 P, Mx, My;
      Float64 fg_stress, bg_stress, stress, incremental_strain, total_strain;
      bool bExceededStrainLimitsThisSlice;
      if ( (slice.Bottom < Yna) && (Yna < slice.Top) )
      {
         // this slice spans the neutral axis... 
         // need to clip again 
         Float64 angle = GetNeutralAxisAngle();

         CComPtr<IPlane3d> initial_strain;
         m_Section->get_InitialStrain(slice.ShapeIdx, &initial_strain);
         SHAPEINFO shape_info(slice.ShapeIdx,slice.SliceShape,slice.FgMaterial,slice.BgMaterial,initial_strain,slice.Le);

         SLICEINFO top_slice;
         CComPtr<IUnknown> pUnkTopSlice;
         hr = SliceShape(shape_info,angle,slice.Top,Yna,top_slice);
         if ( SUCCEEDED(hr) && hr != S_FALSE )
         {
            hr = AnalyzeSlice(top_slice, incrementalStrainPlane,P,Mx,My,fg_stress,bg_stress,stress,incremental_strain,total_strain, bExceededStrainLimitsThisSlice);
            if (FAILED(hr))
            {
               return hr;
            }

            C += COMPRESSION(P);
            T += TENSION(P);

            COMPRESSION_CG(cgC,P,top_slice);
            TENSION_CG(cgT,P,top_slice);

            p  += P;
            mx += Mx;
            my -= My;

            bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

            CComObject<CGeneralSectionSlice>* pSlice;
            CComObject<CGeneralSectionSlice>::CreateInstance(&pSlice);
            Float64 Xcg, Ycg;
            top_slice.pntCG->Location(&Xcg, &Ycg);
            pSlice->InitSlice(top_slice.ShapeIdx,top_slice.SliceShape,top_slice.Area,Xcg,Ycg,top_slice.ei,incremental_strain,total_strain,fg_stress,bg_stress,slice.FgMaterial,slice.BgMaterial, bExceededStrainLimitsThisSlice ? VARIANT_TRUE : VARIANT_FALSE);
            pSlice->QueryInterface(&pUnkTopSlice);

#if defined _DEBUG_LOGGING
            CComBSTR fgName("-");
            CComBSTR bgName("-");
            if ( slice.FgMaterial )
               slice.FgMaterial->get_Name(&fgName);
         
            if ( slice.BgMaterial )
               slice.BgMaterial->get_Name(&bgName);

            os << std::setw(10) << AREA(top_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(top_slice.Top) << ", " << std::setw(10) << LENGTH(top_slice.Bottom) << ", " << std::setw(20) << LENGTH(Xcg) << ", " << std::setw(20) << LENGTH(Ycg) << ", " << std::setw(20) << top_slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << OLE2T(fgName) << ", " << std::setw(10) << STRESS(fg_stress) << ", "  << std::setw(20) << OLE2T(bgName) << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
         }

         SLICEINFO bottom_slice;
         CComPtr<IUnknown> pUnkBottomSlice;
         hr = SliceShape(shape_info,angle,Yna,slice.Bottom,bottom_slice);
         if ( SUCCEEDED(hr) && hr != S_FALSE )
         {
            hr = AnalyzeSlice(bottom_slice, incrementalStrainPlane,P,Mx,My,fg_stress,bg_stress,stress,incremental_strain,total_strain, bExceededStrainLimitsThisSlice);
            if ( FAILED(hr) )
               return hr;

            C += COMPRESSION(P);
            T += TENSION(P);

            COMPRESSION_CG(cgC,P,bottom_slice);
            TENSION_CG(cgT,P,bottom_slice);

            p  += P;
            mx += Mx;
            my -= My;

            bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

            CComObject<CGeneralSectionSlice>* pSlice;
            CComObject<CGeneralSectionSlice>::CreateInstance(&pSlice);
            Float64 Xcg, Ycg;
            bottom_slice.pntCG->Location(&Xcg, &Ycg);
            pSlice->InitSlice(bottom_slice.ShapeIdx,bottom_slice.SliceShape,bottom_slice.Area,Xcg,Ycg, bottom_slice.ei, incremental_strain, total_strain,fg_stress,bg_stress,slice.FgMaterial,slice.BgMaterial, bExceededStrainLimitsThisSlice ? VARIANT_TRUE : VARIANT_FALSE);
            pSlice->QueryInterface(&pUnkBottomSlice);

#if defined _DEBUG_LOGGING
            CComBSTR fgName("-");
            CComBSTR bgName("-");
            if ( slice.FgMaterial )
               slice.FgMaterial->get_Name(&fgName);
         
            if ( slice.BgMaterial )
               slice.BgMaterial->get_Name(&bgName);

            os << std::setw(10) << AREA(bottom_slice.Area) << ", " << std::setw(10) << "T, " <<std::setw(10) << LENGTH(bottom_slice.Top) << ", " << std::setw(10) << LENGTH(bottom_slice.Bottom) << ", " << std::setw(20) << LENGTH(Xcg) << ", " << std::setw(20) << LENGTH(Ycg) << ", " << std::setw(20) << bottom_slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << OLE2T(fgName) << ", " << std::setw(10) << STRESS(fg_stress) << ", "  << std::setw(20) << OLE2T(bgName) << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
         }

            if (PI_OVER_2 <= angle && angle < 3 * PI_OVER_2)
            {
               if (pUnkBottomSlice) slices->Add(pUnkBottomSlice);
               if (pUnkTopSlice) slices->Add(pUnkTopSlice);
            }
            else
            {
	            if (pUnkTopSlice) slices->Add(pUnkTopSlice);
	            if (pUnkBottomSlice) slices->Add(pUnkBottomSlice);
	         }
         }
      else
      {
         hr = AnalyzeSlice(slice, incrementalStrainPlane,P,Mx,My,fg_stress,bg_stress,stress,incremental_strain,total_strain, bExceededStrainLimitsThisSlice);
         if ( FAILED(hr) )
            return hr;

         C += COMPRESSION(P);
         T += TENSION(P);

         COMPRESSION_CG(cgC,P,slice);
         TENSION_CG(cgT,P,slice);

         p  += P;
         mx += Mx;
         my -= My;

         bExceededStrainLimits |= bExceededStrainLimitsThisSlice;

         CComObject<CGeneralSectionSlice>* pSlice;
         CComObject<CGeneralSectionSlice>::CreateInstance(&pSlice);
         Float64 Xcg, Ycg;
         slice.pntCG->Location(&Xcg, &Ycg);
         pSlice->InitSlice(slice.ShapeIdx,slice.SliceShape,slice.Area,Xcg,Ycg, slice.ei, incremental_strain, total_strain,fg_stress,bg_stress,slice.FgMaterial,slice.BgMaterial, bExceededStrainLimitsThisSlice ? VARIANT_TRUE : VARIANT_FALSE);
         CComPtr<IUnknown> punk;
         pSlice->QueryInterface(&punk);
         slices->Add(punk);

#if defined _DEBUG_LOGGING
         CComBSTR fgName("-");
         CComBSTR bgName("-");
         if ( slice.FgMaterial )
            slice.FgMaterial->get_Name(&fgName);
         
         if ( slice.BgMaterial )
            slice.BgMaterial->get_Name(&bgName);

         char cSide = (P < 0 ? 'C' : 'T');
         os << std::setw(10) << AREA(slice.Area) << ", " << std::setw(10) << cSide << ", " <<std::setw(10) << LENGTH(slice.Top) << ", " << std::setw(10) << LENGTH(slice.Bottom) << ", " << std::setw(20) << LENGTH(Xcg) << ", " << std::setw(20) << LENGTH(Ycg) << ", " << std::setw(20) << slice.ei << ", " << std::setw(20) << total_strain << ", " << std::setw(20) << OLE2T(fgName) << ", " << std::setw(10) << STRESS(fg_stress) << ", "  << std::setw(20) << OLE2T(bgName) << ", " << std::setw(10) << STRESS(bg_stress) << ", " << std::setw(10) << STRESS(stress) << ", " << std::setw(10) << FORCE(P) << std::endl;
#endif // _DEBUG_LOGGING
      }
   }

   if ( *solution == nullptr )
   {
      // a solution object was not provided so create a new one
      CComObject<CGeneralSectionSolution>* pSolution;
      CComObject<CGeneralSectionSolution>::CreateInstance(&pSolution);
      (*solution) = pSolution;
      (*solution)->AddRef();
   }

   // locate centroid of resultant compression and tension forces
   // up to this point the cgC and cgT objects contain the sum of Force*CG
   Float64 x,y;
   cgC->Location(&x, &y);
   cgC->Move(x / C, y / C);

   cgT->Location(&x, &y);
   cgT->Move(x / T, y / T);

   CComPtr<ILine2d> neutral_axis;
   neutral_axis.CoCreateInstance(CLSID_Line2d);
   CComPtr<IPoint2d> pnt;
   CComPtr<IVector2d> vec;
   m_NeutralAxis->GetExplicit(&pnt,&vec);
   neutral_axis->SetExplicit(pnt,vec);

   (*solution)->InitSolution(p,mx,my,neutral_axis,cgC,C,cgT,T,slices, bExceededStrainLimits);

#if defined _DEBUG_LOGGING
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "initial strain, " << std::setw(20) << "strain, " << std::setw(20) << "fg material, " << std::setw(10) << "fg stress, "  << std::setw(20) << "bg material, " << std::setw(10) << "bg stress, " << std::setw(10) << "stress, " << std::setw(10) << "force" << std::endl;
   os << std::endl;
   os << "P  = " << FORCE(p)   << std::endl;
   os << "Mx = " << MOMENT(mx) << std::endl;
   os << "My = " << MOMENT(my) << std::endl;
   log->LogMessage(cookie,CComBSTR(os.str().c_str()));

   log->Close(cookie);
#endif // _DEBUG_LOGGING

   return (bExceededStrainLimits ? S_FALSE : S_OK);
}

void CGeneralSectionSolver::DecomposeSection(IPlane3d* incrementalStrainPlane)
{
   HRESULT hr;

   // if neutral axis direction, determined from the strain plane, is different from the last time
   // we need to re-slice the section... slices must by parallel to the neutral axis
   if (m_bDecomposed && IsNeutralAxisParallel(incrementalStrainPlane))
   {
      UpdateNeutralAxis(incrementalStrainPlane, m_NeutralAxis); // update the neutral axis for the current strain plain
      return; // section is decomposed and NA direction hasn't changed... analysis is good to go
   }

   UpdateNeutralAxis(incrementalStrainPlane, m_NeutralAxis);

   // Get neutral axis angle
   Float64 angle = GetNeutralAxisAngle();

   // We are going to need a bounding box
   CComPtr<IRect2d> bounding_box;

   // ... and something to hold the rotated shapes in
   std::vector< SHAPEINFO > shapes;

   // Rotate the shapes and determine the overall size of the section (bounding box)
   IndexType nShapes;
   m_Section->get_ShapeCount(&nShapes);
   for ( IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
   {
      CComPtr<IShape> original_shape;
      m_Section->get_Shape(shapeIdx,&original_shape);

      CComPtr<IStressStrain> fgMaterial;
      CComPtr<IStressStrain> bgMaterial;
      m_Section->get_ForegroundMaterial(shapeIdx,&fgMaterial);
      m_Section->get_BackgroundMaterial(shapeIdx,&bgMaterial);

      CComPtr<IPlane3d> initialStrain;
      m_Section->get_InitialStrain(shapeIdx,&initialStrain);

      Float64 Le;
      m_Section->get_ElongationLength(shapeIdx, &Le);

      CComPtr<IShape> shape;
      hr = original_shape->Clone(&shape);

      // rotate the shape so that its primary axes are aligned with the neutral axis
      // we need to clip parallel to the neutral axis
      CComQIPtr<IXYPosition> position(shape);
      position->Rotate(0,0,-angle);

      CComPtr<IRect2d> bndbox;
      shape->get_BoundingBox(&bndbox);

      if (shapeIdx == 0)
      {
         bounding_box = bndbox;
      }
      else
      {
         bounding_box->Union(bndbox);
      }

      shapes.emplace_back( shapeIdx, shape, fgMaterial, bgMaterial, initialStrain, Le);
   }

   //
   // Determine slice parameters
   //
   Float64 top, height;
   bounding_box->get_Top(&top);
   bounding_box->get_Height(&height);

   // z = 0 + 1 + 2 + 3 + ... + (m_nSlices-1) = ( (m_nSlices-1)^2 + (m_nSlices-1) )/2
   // See http://www.math.com/tables/expansion/power.htm
   long z = ((m_nSlices-1)*(m_nSlices-1) + (m_nSlices-1))/2;

   // get the slice growth factor... if 0, then it wasn't set by the user
   // so set it to the number of slices so that all slices are of a uniform
   // height
   Float64 k;
   Float64 basic_slice_height;
   ATLASSERT( 0 < m_nSlices );
   if ( m_nSlices == 1 )
   {
      k = 0;
      basic_slice_height = height;
   }
   else
   {
      k = (m_SliceGrowthFactor-1)/(m_nSlices-1);
      basic_slice_height = height/(m_nSlices + k*z);
   }
   

   // Setup clipping box

   Float64 left, right;
   bounding_box->get_Left(&left);
   bounding_box->get_Right(&right);

   Float64 width = right-left;
   m_ClippingRect->put_Left(left   - width/2);
   m_ClippingRect->put_Right(right + width/2);

   // Slice each shape
   m_Slices.clear();
   nShapes = shapes.size();
   for ( IndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
   {
      // get shape and related information
      SHAPEINFO& shape_info = shapes[shapeIdx];

      // get the top and bottom of the shape... there is no reason to try to slice
      // if the slicer isn't passing through the shape
      CComPtr<IRect2d> shape_box;
      shape_info.Shape->get_BoundingBox(&shape_box);
      Float64 shape_top, shape_bottom;
      shape_box->get_Top(&shape_top);
      shape_box->get_Bottom(&shape_bottom);

      Float64 slice_top = top;

      for ( long sliceIdx = 0; sliceIdx < m_nSlices; sliceIdx++ )
      {
         Float64 slice_height = (k*sliceIdx + 1)*basic_slice_height;
         Float64 slice_bottom = slice_top - slice_height;

         // expand the depth of the first and last slice just so nothing is missed
         if (sliceIdx == 0)
         {
            slice_top += slice_height / 2;
         }

         if (sliceIdx == m_nSlices - 1)
         {
            slice_bottom -= slice_height / 2;
         }

         SLICEINFO slice_info;
         hr = SliceShape(shape_info,angle,slice_top,slice_bottom,slice_info);

         slice_top = slice_bottom; // top of next slice

         if (hr == S_FALSE)
         {
            continue; // go to next slice 
         }

         m_Slices.push_back(slice_info);

         // once the top of the slicer is below the shape... stop slicing
         if (slice_top < slice_bottom)
         {
            sliceIdx = m_nSlices;
         }
      }
   }

   // sort based on CG elevation
   std::sort(std::begin(m_Slices), std::end(m_Slices), [](auto& sliceA, auto& sliceB) {Float64 YcgA, YcgB; sliceA.pntCG->get_Y(&YcgA); sliceB.pntCG->get_Y(&YcgB); return YcgB < YcgA; });
   m_bDecomposed = true;
}

bool CGeneralSectionSolver::IsNeutralAxisParallel(IPlane3d* incrementalStrainPlane)
{
   CHRException hr;

   UpdateNeutralAxis(incrementalStrainPlane,m_TestLine);
   VARIANT_BOOL bSameDirection;
   hr = m_GeomUtil->IsSameDirection(m_NeutralAxis, m_TestLine, &bSameDirection);

   return bSameDirection == VARIANT_TRUE ? true : false;
}

void CGeneralSectionSolver::UpdateNeutralAxis(IPlane3d* incrementalStrainPlane,ILine2d* line)
{
   HRESULT hr; 

   // get the initial strain plane for the primary shape
   IndexType primaryShapeIdx;
   m_Section->get_PrimaryShapeIndex(&primaryShapeIdx);
   CComPtr<IPlane3d> initial_strain_plane;
   m_Section->get_InitialStrain(primaryShapeIdx, &initial_strain_plane);

   // get three points on the initial strain plane
   CComPtr<IPoint3d> A1, A2, A3;
   A1.CoCreateInstance(CLSID_Point3d);
   A2.CoCreateInstance(CLSID_Point3d);
   A3.CoCreateInstance(CLSID_Point3d);
   Float64 X1 = -100;
   Float64 Y1 = 100;
   Float64 Z1 = 0;
   Float64 X2 = 100;
   Float64 Y2 = 100;
   Float64 Z2 = 0;
   Float64 X3 = -100;
   Float64 Y3 = -100;
   Float64 Z3 = 0;
   if (initial_strain_plane)
   {
      initial_strain_plane->GetZ(X1, Y1, &Z1);
      initial_strain_plane->GetZ(X2, Y2, &Z2);
      initial_strain_plane->GetZ(X3, Y3, &Z3);
   }
   A1->Move(X1, Y1, Z1);
   A2->Move(X2, Y2, Z2);
   A3->Move(X3, Y3, Z3);

   // get the incremental strain on these three points
   // and offset the initial strain by the increment strain
   incrementalStrainPlane->GetZ(X1, Y1, &Z1);
   A1->Offset(0, 0, Z1);
   incrementalStrainPlane->GetZ(X2, Y2, &Z2);
   A2->Offset(0, 0, Z2);
   incrementalStrainPlane->GetZ(X3, Y3, &Z3);
   A3->Offset(0, 0, Z3);

   // create a new plane... the total strain plane through these three points
   CComPtr<IPlane3d> total_strain_plane;
   total_strain_plane.CoCreateInstance(CLSID_Plane3d);
   total_strain_plane->ThroughPoints(A1, A2, A3);
   
   // find the line that passes through z = 0 (z is the strain axis)

   Float64 x1 = -1000;
   Float64 x2 =  1000;
   Float64 z  = 0.00;
   Float64 y1,y2;

   HRESULT hr1 = total_strain_plane->GetY(x1,z,&y1);
   HRESULT hr2 = total_strain_plane->GetY(x2,z,&y2);

   HRESULT hr3 = S_OK;
   HRESULT hr4 = S_OK;
   if ( FAILED(hr1) || FAILED(hr2) )
   {
      y1 = -1000;
      y2 =  1000;
      
      hr3 = total_strain_plane->GetX(y1,z,&x1);
      hr4 = total_strain_plane->GetX(y2,z,&x2);
   }

   if ( FAILED(hr3) || FAILED(hr4) )
   {
      // the plane is parallel to the XY plane.... just pick some values... the direction
      // of the neutral axis doesn't matter
      x1 = -1000;
      y1 = -1000;
      
      x2 = 1000;
      y2 = -1000;
   }

   // create the neutral axis line with compression on the left side on the line
   CComPtr<IPoint2d> p1,p2;
   p1.CoCreateInstance(CLSID_Point2d);
   p2.CoCreateInstance(CLSID_Point2d);

   p1->Move(x1,y1);
   p2->Move(x2,y2);
   hr = line->ThroughPoints(p1, p2);

   // evaluate a point on the left side of the line
   Float64 C;
   CComPtr<IVector2d> vN; // normal vector points to the left hand side of the line
   line->GetImplicit(&C, &vN);
   Float64 dx, dy;
   vN->get_X(&dx);
   vN->get_Y(&dy);

   Float64 Offset = 10; // some offset from the line
   Float64 X = x1 + Offset*dx;
   Float64 Y = y1 + Offset*dy;
   Float64 Z;
   total_strain_plane->GetZ(X,Y,&Z);
   if (0 < Z)
   {
      // tension is on the left side, so reverse the direction the line
      // we want compression on the left side
      hr = line->Reverse();
   }
}

HRESULT CGeneralSectionSolver::AnalyzeSlice(CGeneralSectionSolver::SLICEINFO& slice,IPlane3d* incrementalStrainPlane,Float64& P,Float64& Mx,Float64& My,Float64& fg_stress,Float64& bg_stress,Float64& stress,Float64& incrementalStrain,Float64& totalStrain,bool& bExceededStrainLimits)
{
   Float64 Xcg, Ycg;
   slice.pntCG->Location(&Xcg, &Ycg);
   HRESULT hr = incrementalStrainPlane->GetZ(Xcg,Ycg,&incrementalStrain);
   ATLASSERT(SUCCEEDED(hr));

   incrementalStrain /= slice.Le;

   totalStrain = incrementalStrain + slice.ei;

   fg_stress = 0;
   if ( slice.FgMaterial )
   {
      hr = slice.FgMaterial->ComputeStress(totalStrain,&fg_stress);
      if (FAILED(hr))
      {
         return Error(IDS_E_FGMATERIAL, IID_IGeneralSectionSolver, RC_E_FGMATERIAL);
      }

      bExceededStrainLimits = (hr == S_FALSE ? true : false);
   }

   bg_stress = 0;
   if ( slice.BgMaterial )
   {
      // it doesn't matter if you exceed the strain limit of the background material because it doesn't really exist
      hr = slice.BgMaterial->ComputeStress(totalStrain,&bg_stress);
      //if (FAILED(hr))
      //{
      //   return Error(IDS_E_BGMATERIAL, IID_IGeneralSectionSolver, RC_E_BGMATERIAL);
      //}
   }

   stress = fg_stress - bg_stress;

   P  = slice.Area * stress;
   Mx = slice.Area * stress * Ycg;
   My = slice.Area * stress * Xcg;


   return S_OK;
}

HRESULT CGeneralSectionSolver::SliceShape(const SHAPEINFO& shapeInfo,Float64 angle,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo)
{
   HRESULT hr;

   sliceInfo.ShapeIdx = shapeInfo.ShapeIdx; // record the index of the shape this slice is taken from

   m_ClippingRect->put_Top(sliceTop);
   m_ClippingRect->put_Bottom(sliceBottom);

   CComPtr<IShape> clipped_shape;
   hr = shapeInfo.Shape->ClipIn(m_ClippingRect,&clipped_shape);

   // sometimes the shape isn't even in the clipping box so
   // the result is nullptr... go to next slice
   if ( clipped_shape == nullptr )
      return S_FALSE;

   CComPtr<IShapeProperties> props;
   hr = clipped_shape->get_ShapeProperties(&props);

   sliceInfo.Top = IsZero(sliceTop) ? 0 : sliceTop;
   sliceInfo.Bottom = IsZero(sliceBottom) ? 0 : sliceBottom;
   sliceInfo.SliceShape = clipped_shape;
   props->get_Area(&sliceInfo.Area);

   // rotate the CG point back into the original coordinate system
   props->get_Centroid(&sliceInfo.pntCG);
   sliceInfo.pntCG->Rotate(0.00,0.00,angle);

   // compute the initial strain at the CG of the slice using the shape's initial strain plane
   Float64 cgX, cgY;
   sliceInfo.pntCG->Location(&cgX, &cgY);
   Float64 ei;
   shapeInfo.InitialStrain->GetZ(cgX, cgY, &ei);

   sliceInfo.FgMaterial = shapeInfo.FgMaterial;
   sliceInfo.BgMaterial = shapeInfo.BgMaterial;
   sliceInfo.ei         = ei;
   sliceInfo.Le         = shapeInfo.Le;

   return S_OK;
}

Float64 CGeneralSectionSolver::GetNeutralAxisAngle()
{
   // Get neutral axis angle
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_NeutralAxis->GetExplicit(&p,&v);
   Float64 angle;
   v->get_Direction(&angle);
   return angle;
}