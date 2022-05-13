///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// CrackedSectionSolver.cpp : Implementation of CCrackedSectionSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "CrackedSectionSolver.h"
#include "CrackedSectionSolution.h"
#include "CrackedSectionSlice.h"
#include <WBFLGeometry.h>
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined _DEBUG_LOGGING
#include <sstream>
#include <iomanip>
#include <Units\Units.h>

#define VALUE(_x_) (IsZero(_x_)  ? 0 : _x_)
#define LENGTH(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch))
#define AREA(_x_)   (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch2))
#define STRESS(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KSI))
#endif // _DEBUG_LOGGING

/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSolver
HRESULT CCrackedSectionSolver::FinalConstruct()
{
   m_CGTolerance = 0.01;
   m_MaxIter = 50;

   m_ClippingRect.CoCreateInstance(CLSID_Rect2d);

   return S_OK;
}

void CCrackedSectionSolver::FinalRelease()
{
}


STDMETHODIMP CCrackedSectionSolver::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrackedSectionSolver,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ICrackedSectionSolver
STDMETHODIMP CCrackedSectionSolver::put_CGTolerance(Float64 tolerance)
{
   m_CGTolerance = tolerance;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::get_CGTolerance(Float64* tolerance)
{
   CHECK_RETVAL(tolerance);
   *tolerance = m_CGTolerance;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::put_MaxIterations(long maxIter)
{
   m_MaxIter = maxIter;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::get_MaxIterations(long* maxIter)
{
   CHECK_RETVAL(maxIter);
   *maxIter = m_MaxIter;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::put_Slices(long nSlices)
{
   m_nSlices = nSlices;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::get_Slices(long* nSlices)
{
   CHECK_RETVAL(nSlices);
   *nSlices = m_nSlices;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::put_SliceGrowthFactor(Float64 sliceGrowthFactor)
{
   m_SliceGrowthFactor = sliceGrowthFactor;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::get_SliceGrowthFactor(Float64* sliceGrowthFactor)
{
   CHECK_RETVAL(sliceGrowthFactor);
   *sliceGrowthFactor = m_SliceGrowthFactor;

   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::putref_Section(IGeneralSection* pSection)
{
   CHECK_IN(pSection);
   m_Section = pSection;
   m_bDecomposed = false;

   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::get_Section(IGeneralSection** pSection)
{
   CHECK_RETOBJ(pSection);
   (*pSection) = m_Section;
   if ( *pSection )
      (*pSection)->AddRef();

   return S_OK;
}

STDMETHODIMP CCrackedSectionSolver::Solve(Float64 naAngle,ICrackedSectionSolution** solution)
{
#if defined _DEBUG_LOGGING
   m_Log.CoCreateInstance(CLSID_WBFLErrorLog);
   m_Log->Open(CComBSTR("CrackedSectionSolver.log"),&m_dwCookie);
#endif // _DEBUG_LOGGING

   HRESULT hr;

   // solve with method of false position (aka regula falsi method)
   // http://en.wikipedia.org/wiki/False_position_method
   // http://mathworld.wolfram.com/MethodofFalsePosition.html

   if ( m_Section == nullptr )
      return E_FAIL;

   m_Angle = naAngle;

   DecomposeSection();

   Float64 Ylower = m_Ybottom;
   Float64 Yupper = m_Ytop;

   CComPtr<IPoint2d> pntCG;
   pntCG.CoCreateInstance(CLSID_Point2d);
   
   CComPtr<IUnkArray> slices;
   slices.CoCreateInstance(CLSID_UnkArray);


   Float64 result_lower;
   hr = AnalyzeSection(Ylower,slices,pntCG);
   if ( FAILED(hr) )
      return hr;
   
   Float64 resultY;
   pntCG->get_Y(&resultY);
   result_lower = Ylower - resultY;

   Float64 result_upper;
   slices->Clear();
   hr = AnalyzeSection(Yupper,slices,pntCG);
   if ( FAILED(hr) )
      return hr;

   pntCG->get_Y(&resultY);
   result_upper = Yupper - resultY;

   Float64 Y = Ylower;
   Float64 result = result_lower;

   int side = 0;
   long iter = 0;
   for ( iter = 0; iter < m_MaxIter; iter++ )
   {
      if ( IsZero(result,m_CGTolerance) && IsZero(result_lower,m_CGTolerance) && IsZero(result_upper,m_CGTolerance) )
         break; // converged

      // guess next value
      Y = (result_upper*Ylower - result_lower*Yupper) / ( result_upper - result_lower );

      slices->Clear();
      hr = AnalyzeSection(Y,slices,pntCG);
      if ( FAILED(hr) )
         return hr;

      pntCG->get_Y(&resultY);
      result = Y - resultY;

      if ( result*result_upper > 0 )
      {
         Yupper = Y;
         result_upper = result;
         if ( side == -1 )
            result_lower /= 2;

         side = -1;
      }
      else if ( result_lower*result > 0 )
      {
         Ylower = Y;
         result_lower = result;
         if ( side == 1 )
            result_upper /= 2;

         side = 1;
      }
      else
      {
         break;
      }
   }

   if ( m_MaxIter <= iter )
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_ICrackedSectionSolver,RC_E_SOLUTIONNOTFOUND);

   CComObject<CCrackedSectionSolution>* pSolution;
   CComObject<CCrackedSectionSolution>::CreateInstance(&pSolution);

   (*solution) = pSolution;
   (*solution)->AddRef();

   (*solution)->InitSolution(pntCG,slices);

#if defined _DEBUG_LOGGING
   m_Log->Close(m_dwCookie);
   m_Log.Release();
#endif // _DEBUG_LOGGING

   return S_OK;
}

HRESULT CCrackedSectionSolver::AnalyzeSection(Float64 Yguess,IUnkArray* slices,IPoint2d* pntCG)
{
   HRESULT hr;

   // Summations for first moment of area
   Float64 EA = 0;
   Float64 EAx = 0;
   Float64 EAy = 0;

#if defined _DEBUG_LOGGING
   std::_tostringstream os;
   os << "Yguess: " << LENGTH(Yguess) << std::endl;
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "FG, " << std::setw(20) << "BG" << std::endl;
#endif // _DEBUG_LOGGING

   std::vector<SLICEINFO>::iterator iter;
   for ( iter = m_SliceInfo.begin(); iter != m_SliceInfo.end(); iter++ )
   {
      SLICEINFO& slice = *iter;

      if ( (slice.Bottom < Yguess) && (Yguess < slice.Top) )
      {
         // this slice spans the guess location... 
         // need to clip again 
         SHAPEINFO shape_info;
         shape_info.BgMaterial = slice.BgMaterial;
         shape_info.FgMaterial = slice.FgMaterial;
         shape_info.Shape      = slice.SliceShape;

         SLICEINFO top_slice;
         hr = SliceShape(shape_info,slice.Top,Yguess,top_slice);
         if ( SUCCEEDED(hr) && hr != S_FALSE )
         {
            Float64 ea,eax,eay,Efg,Ebg;
            hr = AnalyzeSlice(Yguess,top_slice,ea,eax,eay,Efg,Ebg);
            if ( FAILED(hr) )
               return hr;

            EA  += ea;
            EAx += eax;
            EAy += eay;

            CComObject<CCrackedSectionSlice>* pSlice;
            CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
            pSlice->InitSlice(top_slice.SliceShape,top_slice.Area,top_slice.Xcg,top_slice.Ycg,Efg,Ebg);
            CComPtr<IUnknown> punk;
            pSlice->QueryInterface(&punk);
            slices->Add(punk);

#if defined _DEBUG_LOGGING
            os << std::setw(10) << AREA(top_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(top_slice.Top) << ", " << std::setw(10) << LENGTH(top_slice.Bottom) << ", " << std::setw(20) << LENGTH(top_slice.Xcg) << ", " << std::setw(20) << LENGTH(top_slice.Ycg) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
         }

         SLICEINFO bottom_slice;
         hr = SliceShape(shape_info,Yguess,slice.Bottom,bottom_slice);
         if ( SUCCEEDED(hr) && hr != S_FALSE )
         {
            Float64 ea, eax, eay, Efg, Ebg;
            hr = AnalyzeSlice(Yguess,bottom_slice,ea,eax,eay,Efg,Ebg);
            if ( FAILED(hr) )
               return hr;

            EA  += ea;
            EAx += eax;
            EAy += eay;

            CComObject<CCrackedSectionSlice>* pSlice;
            CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
            pSlice->InitSlice(bottom_slice.SliceShape,bottom_slice.Area,bottom_slice.Xcg,bottom_slice.Ycg,Efg,Ebg);
            CComPtr<IUnknown> punk;
            pSlice->QueryInterface(&punk);
            slices->Add(punk);

#if defined _DEBUG_LOGGING
            os << std::setw(10) << AREA(bottom_slice.Area) << ", " << std::setw(10) << "C, " << std::setw(10) << LENGTH(bottom_slice.Top) << ", " << std::setw(10) << LENGTH(bottom_slice.Bottom) << ", " << std::setw(20) << LENGTH(bottom_slice.Xcg) << ", " << std::setw(20) << LENGTH(bottom_slice.Ycg) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
         }
      }
      else
      {
         Float64 ea, eax, eay, Efg, Ebg;
         hr = AnalyzeSlice(Yguess,slice,ea,eax,eay,Efg,Ebg);
         if ( FAILED(hr) )
            return hr;

         EA  += ea;
         EAx += eax;
         EAy += eay;

         CComObject<CCrackedSectionSlice>* pSlice;
         CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
         pSlice->InitSlice(slice.SliceShape,slice.Area,slice.Xcg,slice.Ycg,Efg,Ebg);
         CComPtr<IUnknown> punk;
         pSlice->QueryInterface(&punk);
         slices->Add(punk);

#if defined _DEBUG_LOGGING
         char cSide = (slice.Ycg > Yguess ? 'C' : 'T');
         os << std::setw(10) << AREA(slice.Area) << ", " << std::setw(10) << cSide << ", " << std::setw(10) << LENGTH(slice.Top) << ", " << std::setw(10) << LENGTH(slice.Bottom) << ", " << std::setw(20) << LENGTH(slice.Xcg) << ", " << std::setw(20) << LENGTH(slice.Ycg) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
#endif // _DEBUG_LOGGING
      }
   } // next slice

   // locate centroid of the cracked section
   Float64 x = IsZero(EA) ? 0 : EAx/EA;
   Float64 y = IsZero(EA) ? 0 : EAy/EA;

   pntCG->Move(x,y);

#if defined _DEBUG_LOGGING
   os << std::setw(10) << "Area, " << std::setw(10) << "Side, " << std::setw(10) << "Top, " << std::setw(10) << "Bottom, " << std::setw(20) << "Xcg, " << std::setw(20) << "Ycg, " << std::setw(20) << "FG, " << std::setw(20) << "BG" << std::endl;
   os << std::endl;
   os << "Y = " << LENGTH(y) << std::endl;
   os << "Yguess - Y = " << LENGTH(Yguess - y) << std::endl;
   m_Log->LogMessage(m_dwCookie,CComBSTR(os.str().c_str()));
#endif // _DEBUG_LOGGING

   return S_OK;
}

void CCrackedSectionSolver::DecomposeSection()
{
   HRESULT hr;

   if ( m_bDecomposed )
      return; // section is decomposed and NA direction hasn't changed... analysis is good to go

   // We are going to need a bounding box
   CComPtr<IRect2d> bounding_box;

   // ... and something to hold the rotated shapes in
   std::vector<SHAPEINFO> shapes;

   // Rotate the shapes and determine the overall size of the section (bounding box)
   CollectionIndexType nShapes;
   m_Section->get_ShapeCount(&nShapes);
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
   {
      CComPtr<IShape> original_shape;
      m_Section->get_Shape(shapeIdx,&original_shape);

      CComPtr<IStressStrain> fgMaterial;
      CComPtr<IStressStrain> bgMaterial;
      m_Section->get_ForegroundMaterial(shapeIdx,&fgMaterial);
      m_Section->get_BackgroundMaterial(shapeIdx,&bgMaterial);

      CComPtr<IShape> shape;
      hr = original_shape->Clone(&shape);

      CComQIPtr<IXYPosition> position(shape);
      position->Rotate(0,0,-m_Angle);

      CComPtr<IRect2d> bndbox;
      shape->get_BoundingBox(&bndbox);

      if ( shapeIdx == 0 )
         bounding_box = bndbox;
      else
         bounding_box->Union(bndbox);

      SHAPEINFO shapeinfo;
      shapeinfo.Shape = shape;
      shapeinfo.FgMaterial = fgMaterial;
      shapeinfo.BgMaterial = bgMaterial;
      shapes.push_back( shapeinfo );
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
   m_SliceInfo.clear();
   nShapes = shapes.size();
   for ( CollectionIndexType shapeIdx = 0; shapeIdx < nShapes; shapeIdx++ )
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
         if ( sliceIdx == 0 )
            slice_top += slice_height/2;

         if ( sliceIdx == m_nSlices-1 )
            slice_bottom -= slice_height/2;

         SLICEINFO slice_info;
         hr = SliceShape(shape_info,slice_top,slice_bottom,slice_info);

         slice_top = slice_bottom; // top of next slice

         if ( hr == S_FALSE )
            continue; // go to next slice 

         m_SliceInfo.push_back(slice_info);

         // once the top of the slicer is below the shape... stop slicing
         if ( shape_bottom > slice_top )
            sliceIdx = m_nSlices;
      }
   }

   bounding_box->get_Top(&m_Ytop);
   bounding_box->get_Bottom(&m_Ybottom);

   std::sort(m_SliceInfo.begin(),m_SliceInfo.end());
   m_bDecomposed = true;
}

HRESULT CCrackedSectionSolver::AnalyzeSlice(Float64 Yguess,SLICEINFO& slice,Float64& EA,Float64& EAx,Float64& EAy,Float64& Efg,Float64& Ebg)
{
   if ( slice.Ycg < Yguess )
   {
      // Slice is on the tension side of the assumed neutral axis
      // Get a realistic tension strain to determine if material has tension capacity

      // assume material doesn't have any tension capacity
      EA  = 0;
      EAx = 0;
      EAy = 0;
      Efg = 0;
      Ebg = 0;

      if ( !slice.FgMaterial )
         return S_OK;

      Float64 minStrain,maxStrain;
      slice.FgMaterial->StrainLimits(&minStrain,&maxStrain);

      Float64 stress;
      slice.FgMaterial->ComputeStress(maxStrain,&stress);
      if ( stress == 0 )
      {
         return S_OK;
      }
   }

   if ( slice.FgMaterial )
      slice.FgMaterial->get_ModulusOfElasticity(&Efg);
   else
      Efg = 0;

   if ( slice.BgMaterial )
      slice.BgMaterial->get_ModulusOfElasticity(&Ebg);
   else
      Ebg = 0;

   Float64 E = (Efg - Ebg);

   EA  = E*slice.Area;
   EAx = EA*slice.Xcg;
   EAy = EA*slice.Ycg;
   return S_OK;
}

HRESULT CCrackedSectionSolver::SliceShape(const SHAPEINFO& shapeInfo,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo)
{
   HRESULT hr;

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

   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);
   cg->get_X(&sliceInfo.Xcg);
   cg->get_Y(&sliceInfo.Ycg);

   sliceInfo.FgMaterial = shapeInfo.FgMaterial;
   sliceInfo.BgMaterial = shapeInfo.BgMaterial;

   return S_OK;
}
