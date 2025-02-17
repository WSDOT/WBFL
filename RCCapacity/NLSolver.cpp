///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// NLSolver.cpp : Implementation of CNLSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "NLSolver.h"
#include "RCSolution.h"
#include "RCSolutionEx.h"
#include "RCBeam2Ex.h"
#include "UnconfinedConcrete.h"
#include "PSPowerFormula.h"
#include "RebarModel.h"
#include "Helper.h"
#include <WBFLTools.h>
#include <MathEx.h>
#include <float.h>
#include <WBFLGeometry.h>
#include <xutility>

#include "CrackedSectionSolution.h"
#include "CrackedSectionSlice.h"

#if defined _DEBUG_LOGGING
#include <sstream>
#include <iomanip>
#include <Units\Units.h>

#define VALUE(_x_) (IsZero(_x_)  ? 0 : _x_)
#define LENGTH(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch))
#define AREA(_x_)   (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::Inch2))
#define STRESS(_x_) (WBFL::Units::ConvertFromSysUnits(_x_, WBFL::Units::Measure::KSI))
#endif // _DEBUG_LOGGING

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNLSolver
HRESULT CNLSolver::FinalConstruct()
{
   m_ClippingRect.CoCreateInstance(CLSID_Rect2d);
   return S_OK;
}

STDMETHODIMP CNLSolver::put_Slices(long nSlices)
{
   if ( nSlices < 1 )
   {
      return E_INVALIDARG;
   }

   m_nSlices = nSlices;
   return S_OK;
}

STDMETHODIMP CNLSolver::get_Slices(long* nSlices)
{
   CHECK_RETVAL(nSlices);

   *nSlices = m_nSlices;
   return S_OK;
}

STDMETHODIMP CNLSolver::put_Tolerance(Float64 tolerance)
{
   m_Tolerance = fabs(tolerance);
   return S_OK;
}

STDMETHODIMP CNLSolver::get_Tolerance(Float64* tolerance)
{
   CHECK_RETVAL(tolerance);
   *tolerance = m_Tolerance;
   return S_OK;
}

STDMETHODIMP CNLSolver::putref_SlabConcreteModel(IStressStrain* model)
{
   m_bUserSlabConcrete = false;
   m_SlabConcreteModel.Release();

   if ( model != nullptr )
   {
      m_bUserSlabConcrete = true;
      m_SlabConcreteModel = model;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::get_SlabConcreteModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_SlabConcreteModel;

   if ( m_SlabConcreteModel )
   {
      (*model)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_BeamConcreteModel(IStressStrain* model)
{
   m_BeamConcreteModel.Release();
   m_bUserBeamConcrete = false;

   if ( model != nullptr )
   {
      m_bUserBeamConcrete = true;
      m_BeamConcreteModel = model;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::get_BeamConcreteModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_BeamConcreteModel;

   if ( m_BeamConcreteModel )
   {
      (*model)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_StrandModel(IStressStrain* model)
{
   m_bUserStrandModel = false;
   m_StrandModel.Release();

   if ( model != nullptr )
   {
      m_bUserStrandModel = true;
      m_StrandModel = model;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::get_StrandModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_StrandModel;

   if ( m_StrandModel )
   {
      (*model)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_RebarModel(IStressStrain* model)
{
   m_bUserRebarModel = false;
   m_RebarModel.Release();

   if ( model != nullptr )
   {
      m_bUserRebarModel = true;
      m_RebarModel = model;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::get_RebarModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_RebarModel;

   if ( m_RebarModel )
   {
      (*model)->AddRef();
   }

   return S_OK;
}

HRESULT CNLSolver::InitConcreteModel(IStressStrain** model,IUnitServer* unitServer,Float64 fc)
{
   CComObject<CUnconfinedConcrete>* pConcreteModel;
   CComObject<CUnconfinedConcrete>::CreateInstance(&pConcreteModel);

   (*model) = pConcreteModel;
   (*model)->AddRef();

   CComQIPtr<IUnconfinedConcrete> ucc(*model);

   if ( FAILED(ucc->put_fc(fc)) )
   {
      return CComCoClass<CNLSolver>::Error(IDS_E_INITCONCRETE,IID_INLSolver,RC_E_INITCONCRETE);
   }

   return S_OK;
}

HRESULT CNLSolver::InitStrandModel(IStressStrain** model,IUnitServer* unitServer)
{
   CComObject<CPSPowerFormula>* pStrandModel;
   CComObject<CPSPowerFormula>::CreateInstance(&pStrandModel);

   (*model) = pStrandModel;
   (*model)->AddRef();

   CComQIPtr<ISupportUnitServer> sus(*model);
   sus->putref_UnitServer(unitServer);

   return S_OK;
}

HRESULT CNLSolver::InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es)
{
   CComObject<CRebarModel>* pRebarModel;
   CComObject<CRebarModel>::CreateInstance(&pRebarModel);

   (*model) = pRebarModel;
   (*model)->AddRef();

   CComQIPtr<IRebarModel> rebar_model(*model);

   rebar_model->Init(fy,Es,0.11);

   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam *rcbeam, IRCSolution **solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeamToRCBeam2Ex(rcbeam,&rcbeam2);

   CComPtr<IRCSolutionEx> solution_ex;
	HRESULT hr = Solve(rcbeam2,&solution_ex);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CopySolution(solution_ex,solution);
   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2* rcbeam,IRCSolutionEx* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeam2ToRCBeam2Ex(rcbeam,&rcbeam2);

	HRESULT hr = Solve(rcbeam2,solution);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution)
{
//   return SolveBisectionMethod(rcbeam,solution);
   return SolveFalsePositionMethod(rcbeam,solution);
}

STDMETHODIMP CNLSolver::Solve(IRCBeam* rcbeam,ICrackedSectionSolution* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeamToRCBeam2Ex(rcbeam,&rcbeam2);

	HRESULT hr = Solve(rcbeam2,solution);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2* rcbeam,ICrackedSectionSolution* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeam2ToRCBeam2Ex(rcbeam,&rcbeam2);

	HRESULT hr = Solve(rcbeam2,solution);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2Ex* rcbeam,ICrackedSectionSolution** solution)
{
   //return SolveBisectionMethod(rcbeam,solution);
   return SolveFalsePositionMethod(rcbeam,solution);
}

STDMETHODIMP CNLSolver::get_IsCflangeOverhangOnly(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bCflangeOverhangOnly;
	return S_OK;
}

STDMETHODIMP CNLSolver::put_IsCflangeOverhangOnly(VARIANT_BOOL newVal)
{
   m_bCflangeOverhangOnly = newVal;
	return S_OK;
}

STDMETHODIMP CNLSolver::put_ConcreteCrushingStrain(Float64 ec)
{
   m_ec = ec;
   return S_OK;
}

STDMETHODIMP CNLSolver::get_ConcreteCrushingStrain(Float64* ec)
{
   CHECK_RETVAL(ec);
   *ec = m_ec;
   return S_OK;
}

HRESULT CNLSolver::SliceSection(IRCBeam2Ex* rcbeam)
{
   m_Slices.clear();

   Float64 b,hf;
   CComPtr<IShape> beam;

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);
   rcbeam->get_Beam(&beam);

   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);

   CComPtr<IRect2d> box;
   beam->get_BoundingBox(&box);
   Float64 hbeam;
   box->get_Height(&hbeam);
   Float64 bw; // overall width of beam (assumed to be max at top)
   box->get_Width(&bw);

   box->get_Top(&m_Ytop);
   box->get_Bottom(&m_Ybottom);
   m_Ytop += hf;


   Float64 h;
   h = hbeam + hf; // overall height

    // determine approximate slice height
   Float64 approx_slice_height = h / m_nSlices;

   // want to use slice heights that are basically uniform.
   // want to use slices that exactly fit the slab

   // for this height, how may slices are required for the slab
   Uint32 nMinSlabSlices = (IsZero(hf) ? 0 : 5); // use no fewer than 5 slices in the slab
   Uint32 nSlabSlices = (Uint32)floor(hf / approx_slice_height);
   nSlabSlices = Max(nMinSlabSlices,nSlabSlices);
   Float64 hSlabSlice = (nSlabSlices == 0 ? 0 : hf/nSlabSlices);

   // determine height of beam slices
   Uint32 nBeamSlices = m_nSlices - nSlabSlices;
   if ( nBeamSlices < 0 )
   {
      nBeamSlices = m_nSlices;
   }

   Float64 hBeamSlice = hbeam/nBeamSlices;



   //
   // slice slab
   //

   // no need to do real clipping because it is a rectangle, area and cg are easy to determine
   for ( Uint32 sliceIdx = 0; sliceIdx < nSlabSlices; sliceIdx++ )
   {
      Float64 top = m_Ytop - sliceIdx*hSlabSlice;
      Float64 bot = top - hSlabSlice;
      Float64 y_cg = (top + bot)/2;
      Float64 area = b*hSlabSlice;

      SLICEINFO slice_info;
      slice_info.Top = top;
      slice_info.Bottom = bot;
      slice_info.Xcg = 0;
      slice_info.Ycg = y_cg;
      slice_info.Area = area;
      slice_info.bSlabSlice = true;
      slice_info.FgMaterial = m_SlabConcreteModel;

      m_Slices.push_back(slice_info);
   }

   //
   // slice beam
   //


   // set width of clipping rectangle (make it 2bw wide)
   m_ClippingRect->put_Left( -bw );
   m_ClippingRect->put_Right( bw );

   for ( Uint32 sliceIdx = 0; sliceIdx < nBeamSlices; sliceIdx++ )
   {
      Float64 top = m_Ytop - hf - sliceIdx*hBeamSlice;
      Float64 bot = top - hBeamSlice;

      m_ClippingRect->put_Top(top);
      m_ClippingRect->put_Bottom(bot);

      CComPtr<IShape> clipShape;
      beam->ClipIn(m_ClippingRect,&clipShape);

      CComPtr<IShapeProperties> props;

      SLICEINFO slice_info;
      slice_info.Top = top;
      slice_info.Bottom = bot;
      slice_info.bSlabSlice = false;
      slice_info.FgMaterial = m_BeamConcreteModel;

      if ( clipShape == nullptr )
      {
         // this hapens when the slice is so small that it get's squashed down to nothing
         slice_info.Area = 0;
         slice_info.Xcg = 0;
         slice_info.Ycg = (top + bot)/2;
      }
      else
      {
         clipShape->get_ShapeProperties(&props);
         props->get_Area(&slice_info.Area);

         CComPtr<IPoint2d> centroid;
         props->get_Centroid(&centroid);
         centroid->Location(&slice_info.Xcg,&slice_info.Ycg);

         slice_info.SliceShape = clipShape;
      }

      m_Slices.push_back(slice_info);
   }

   return S_OK;
}


HRESULT CNLSolver::AnalyzeSection(IRCBeam2Ex* rcbeam,Float64 c_guess,Float64* pMflange,Float64* pMbeam,Float64* pMt,IDblArray* fs,IDblArray* fps,Float64* pCflange,Float64* pCbeam,Float64* pFt)
{
#if defined _DEBUG_
   CComPtr<IWBFLErrorLog> log;
   log.CoCreateInstance(CLSID_WBFLErrorLog);
   DWORD cookie;
   log->Open(CComBSTR("NLSolver.log"),&cookie);
   std::_tostringstream os;
#endif

   Float64 Cflange = 0;
   Float64 Cbeam   = 0;
   Float64 Mflange = 0;
   Float64 Mbeam   = 0;
   Float64 Mt      = 0;
   Float64 Ft      = 0;

   Float64 fpu, Eps;
   rcbeam->get_fpu(&fpu);
   rcbeam->get_Eps(&Eps);

   Float64 fy, Es;
   rcbeam->get_fy(&fy);
   rcbeam->get_Es(&Es);

   Float64 fpe;
   rcbeam->get_fpe(&fpe);

   Float64 b,h,hf;
   CComPtr<IShape> beam;

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);

   rcbeam->get_Beam(&beam);

   CComPtr<IRect2d> box;
   beam->get_BoundingBox(&box);
   box->get_Height(&h);
   Float64 bw; // overall width of beam (assumed to be max at top)
   box->get_Width(&bw);

   h += hf; // overall height
   
   // compute Fc
   Cflange   = 0;
   Cbeam     = 0;

   Mflange = 0;
   Mbeam   = 0;

   std::vector<SLICEINFO>::iterator slice_iter;
   for ( slice_iter = m_Slices.begin(); slice_iter != m_Slices.end(); slice_iter++ )
   {
      SLICEINFO& slice = *slice_iter;

      Float64 top, slice_bottom, Y, area;
      top = slice.Top;
      slice_bottom = slice.Bottom;
      Y = slice.Ycg;
      area = slice.Area;

      bool bClippingSlab = slice.bSlabSlice;

      Float64 na = h - c_guess; // location of neutral axis measured from bottom
      if ( slice.Bottom <= na && na < slice.Top )
      {
         // neutral axis is in the middle of this slice
         slice_bottom = na;

         // RESLICE
         if ( bClippingSlab )
         {
            // slab piece
            Y = (top + slice_bottom)/2;
            area = b*(top - slice_bottom);
         }
         else
         {
            // beam piece
            CComPtr<IRect2d> clipRect;
            clipRect.CoCreateInstance( CLSID_Rect2d );

            // set width of clipping rectangle (make it 2bw wide)
            clipRect->put_Left( -bw );
            clipRect->put_Right( bw );
            clipRect->put_Top( top );
            clipRect->put_Bottom( slice_bottom );

            CComPtr<IShape> clipShape;
            CComQIPtr<IShape> beamShape(beam);

            beamShape->ClipIn(clipRect,&clipShape);

            if ( clipShape == nullptr )
            {
               // this can happen if the slice is really thin
               area = 0;
               Y = (top + slice_bottom)/2;
            }
            else
            {
               CComPtr<IShapeProperties> props;
               clipShape->get_ShapeProperties(&props);

               props->get_Area(&area);

               CComPtr<IPoint2d> CG;
               props->get_Centroid(&CG);
               CG->get_Y(&Y);
            }
         }


         // done with slices
         slice_iter = m_Slices.end()-1;
      }

      Float64 ec = GetStrain(m_ec,h - Y,c_guess,0,Eps);
      Float64 fc;
      if ( bClippingSlab )
      {
         m_SlabConcreteModel->ComputeStress(ec,&fc);
      }
      else
      {
         m_BeamConcreteModel->ComputeStress(ec,&fc);
      }

      fc *= -1.0;


      Float64 compression = fc*area;
      Float64 moment = Y*compression;

#if defined _DEBUG_
      os << slice.area << ", " << slice.y_cg << ", " << ec << ", " << fc << ", " << compression << std::endl;
#endif // _DEBUG_

      if ( bClippingSlab )
      {
         if ( m_bCflangeOverhangOnly == VARIANT_TRUE )
         {
            // If Cflange is to be the force in the slab overhang only, then deduct
            // the amount of force from this strip that is directly over the beam from Cflange
            // and put it in Cbeam

            // compute the force in the slab overhang be deducting the force in the slab that
            // is over the beam
            Float64 c_beam = fc*bw*(top - slice_bottom);
            Float64 c_flange = compression - c_beam;
            Cflange += c_flange;
            Mflange += Y*c_flange;

            Cbeam += c_beam;
            Mbeam += Y*c_beam;
         }
         else
         {
            Cflange += compression;
            Mflange += moment;
         }
      }
      else
      {
         Cbeam += compression;
         Mbeam += moment;
      }
   }

   // Compute Ft
   IndexType nRebarLayers = 0;
   rcbeam->get_RebarLayerCount(&nRebarLayers);
   Float64 TotalAs = 0;
   Ft = 0;
   Mt = 0;
   fs->Clear();
   for (IndexType rebarLayerIdx = 0; rebarLayerIdx < nRebarLayers; rebarLayerIdx++ )
   {
      Float64 ds, As, devFactor;
      rcbeam->GetRebarLayer(rebarLayerIdx,&ds,&As,&devFactor);
      Float64 es = GetStrain(m_ec,ds,c_guess,0,Es);
      Float64 stress;
      m_RebarModel->ComputeStress(es,&stress);

      if ( devFactor < 1.0 )
      {
         // bar is not fully developed therefore it will pull out before it can yield
         // determine the maximum stress the bar can carry
         Float64 maxRebarStress = devFactor * fy;
         if ( maxRebarStress < stress )
         {
            stress = maxRebarStress;
         }
      }

      Float64 T = As*stress;
      Ft += T;
      Mt += T*(h - ds);
      fs->Add(stress);

      TotalAs += devFactor*As;

#if defined _DEBUG_
      os << As << ", " << ds << ", " << es << ", " << stress << ", " << T << std::endl;
#endif // _DEBUG_
   }

   IndexType nStrandLayers = 0;
   rcbeam->get_StrandLayerCount(&nStrandLayers);
   fps->Clear();
   for ( IndexType strand = 0; strand < nStrandLayers; strand++ )
   {
      Float64 dps, Aps, devFactor;
      rcbeam->GetStrandLayer(strand,&dps,&Aps,&devFactor);

      Float64 eps = GetStrain(m_ec,dps,c_guess,fpe,Eps);
      Float64 stress;
      m_StrandModel->ComputeStress(eps,&stress);

      if ( devFactor < 1.0 )
      {
         // strand is not fully developed, therefore it will slip before it can reach full strength
         // determine the maximum stress the strand can carry
         Float64 maxStrandStress = devFactor * fpu;
         if ( maxStrandStress < stress )
         {
            stress = maxStrandStress;
         }
      }

      Float64 T = Aps*stress;
      Ft += T;
      Mt += T*(h - dps);
      fps->Add(stress);

      TotalAs += devFactor*Aps;

#if defined _DEBUG_
      os << Aps << ", " << dps << ", " << eps << ", " << stress << ", " << T << std::endl;
#endif // _DEBUG_
   }

   // There is no (effective) strand and rebar... there is no solution
   // bail out of here
   if ( IsZero(TotalAs) )
   {
      fs->Clear();
      fps->Clear();
      *pMflange = 0;
      *pCflange = 0;
      *pMbeam = 0;
      *pCbeam = 0;
      *pMt = 0;
      *pFt = 0;
      return S_FALSE;
   }

   *pMflange = Mflange;
   *pCflange = Cflange;
   *pMbeam = Mbeam;
   *pCbeam = Cbeam;
   *pMt = Mt;
   *pFt = Ft;

#if defined _DEBUG_
   os << Cflange + Cbeam - Ft << std::endl;
   log->LogMessage(cookie,CComBSTR(os.str().c_str()));
   log->Close(cookie);
#endif // _DEBUG_

   return S_OK;
}

HRESULT CNLSolver::SolveBisectionMethod(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution)
{
   HRESULT hr = S_OK;

   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   Float64 Ft;
   Float64 Mt;

   CComPtr<IDblArray> fs, fps;
   fs.CoCreateInstance(CLSID_DblArray);
   fps.CoCreateInstance(CLSID_DblArray);

   Float64 fy, Es;
   rcbeam->get_fy(&fy);
   rcbeam->get_Es(&Es);

   Float64 b,h,hf;
   CComPtr<IShape> beam;

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);

   rcbeam->get_Beam(&beam);
   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);
   Float64 Ixy;
   beam_props->get_Ixy(&Ixy);
   if ( !IsZero(Ixy) )
   {
      return Error(IDS_E_BEAMNOTSYMMETRIC,IID_INLSolver,RC_E_BEAMNOTSYMMETRIC);
   }

   CComPtr<IRect2d> box;
   beam->get_BoundingBox(&box);
   box->get_Height(&h);
   Float64 bw; // overall width of beam (assumed to be max at top)
   box->get_Width(&bw);

   h += hf; // overall height

   // make sure the beam shape is correctly located beneath the slab
   CComQIPtr<IXYPosition> position(beam);
   CComPtr<IPoint2d> locator_point;
   position->get_LocatorPoint(lpTopCenter,&locator_point);
   locator_point->Move(0,h-hf);
   position->put_LocatorPoint(lpTopCenter,locator_point);

   hr = InitMaterials(rcbeam);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = SliceSection(rcbeam);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Uint32 max_iterations = 100;
   Uint32 current_iteration = 0;

   Float64 cmin, c, cmax;
   Float64 c_guess;
   c = -1;
   cmin = 0.00001;
   cmax = h;

   Float64 Cflange = 0;
   Float64 Cbeam   = 0;
   Float64 Mflange = 0;
   Float64 Mbeam   = 0;
   bool bDone = false;
   do
   {
      c_guess = (cmin+cmax)/2;
      hr = AnalyzeSection(rcbeam,c_guess,&Mflange,&Mbeam,&Mt,fs,fps,&Cflange,&Cbeam,&Ft);

      if ( hr == S_FALSE )
      {
         // There is no (effective) strand and rebar... there is no solution
         // bail out of here
         CreateSolution(0,0,fs,fps,0,0,0,0,0,solution);
         return S_OK;
      }

      if ( FAILED(hr) )
         return hr;

      // Check equilibrium
      Float64 Fc = Cflange + Cbeam;
      if ( fabs(Fc-Ft) < m_Tolerance )
      {
         // equilibrium was found... done
         bDone = true;
      }
      else
      {
         // update guess for c
         if ( Ft < Fc )
         {
            // too much compression
            cmax = c_guess;
         }
         else
         {
            // too much tension
            cmin = c_guess;
         }
      }

      // If this happens, the solution will never converge
      if ( IsZero(cmin-cmax,1e-17) && m_Tolerance < fabs(Fc-Ft))
      {
         return Error(IDS_E_SOLUTIONNOTFOUND,IID_INLSolver,RC_E_SOLUTIONNOTFOUND);
      }

   } while ( !bDone && (current_iteration++ < max_iterations) );
   
   // After max_iterations, a solution could not be found
   if ( max_iterations <= current_iteration )
   {
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_INLSolver,RC_E_SOLUTIONNOTFOUND);
   }

   c = c_guess;

   // check for over-reinforced section
   Float64 Mn = (Mflange+Mbeam) - Mt;

   Float64 Yflange, Ybeam;

   if ( IsZero(Cflange) )
   {
      Yflange = 0;
   }
   else
   {
      Yflange = h - Mflange/Cflange;
   }

   if ( IsZero(Cbeam) )
   {
      Ybeam = 0;
   }
   else
   {
      Ybeam   = h - Mbeam/Cbeam;
   }

   CreateSolution(Mn,c,fs,fps,Cflange,Cbeam,Ft,Yflange,Ybeam,solution);


	return S_OK;
}

HRESULT CNLSolver::SolveFalsePositionMethod(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution)
{
   HRESULT hr = S_OK;

   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   Float64 Ft;
   Float64 Mt;

   CComPtr<IDblArray> fs, fps;
   fs.CoCreateInstance(CLSID_DblArray);
   fps.CoCreateInstance(CLSID_DblArray);

   Float64 b,h,hf;
   CComPtr<IShape> beam;
   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);
   rcbeam->get_Beam(&beam);

   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);
   Float64 Ixy;
   beam_props->get_Ixy(&Ixy);
   if ( !IsZero(Ixy) )
   {
      return Error(IDS_E_BEAMNOTSYMMETRIC,IID_INLSolver,RC_E_BEAMNOTSYMMETRIC);
   }

   CComPtr<IRect2d> box;
   beam->get_BoundingBox(&box);
   box->get_Height(&h);
   Float64 bw; // overall width of beam (assumed to be max at top)
   box->get_Width(&bw);

   h += hf; // overall height

   // make sure the beam shape is correctly located beneath the slab
   CComQIPtr<IXYPosition> position(beam);
   CComPtr<IPoint2d> locator_point;
   position->get_LocatorPoint(lpTopCenter,&locator_point);
   locator_point->Move(0,h-hf);
   position->put_LocatorPoint(lpTopCenter,locator_point);

   hr = InitMaterials(rcbeam);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = SliceSection(rcbeam);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Uint32 max_iterations = 100;
   Uint32 current_iteration = 0;

   Float64 cmin, c, cmax;
   Float64 c_guess;
   c = -1;
   cmin = 0.00001;
   cmax = h - cmin;

   Float64 Cflange = 0;
   Float64 Cbeam   = 0;
   Float64 Mflange = 0;
   Float64 Mbeam   = 0;

   hr = AnalyzeSection(rcbeam,cmin,&Mflange,&Mbeam,&Mt,fs,fps,&Cflange,&Cbeam,&Ft);
   if ( hr == S_FALSE )
   {
      // There is no (effective) strand and rebar... there is no solution
      // bail out of here
      CreateSolution(0,0,fs,fps,0,0,0,0,0,solution);
      return S_OK;
   }
   Float64 fa = (Cflange+Cbeam-Ft);
   
   hr = AnalyzeSection(rcbeam,cmax,&Mflange,&Mbeam,&Mt,fs,fps,&Cflange,&Cbeam,&Ft);
   Float64 fb = (Cflange+Cbeam-Ft);

   int side = 0;
   Float64 fr = 0;
   for ( ; current_iteration < max_iterations; current_iteration++ )
   {
      if ( IsZero(fr,m_Tolerance) && IsZero(fa,m_Tolerance) && IsZero(fb,m_Tolerance) )
      {
         break;
      }

      c_guess = (fa*cmax - fb*cmin)/(fa-fb);

      hr = AnalyzeSection(rcbeam,c_guess,&Mflange,&Mbeam,&Mt,fs,fps,&Cflange,&Cbeam,&Ft);

      fr = (Cflange+Cbeam-Ft);

      if ( 0 < fr*fb )
      {
         cmax = c_guess;
         fb = fr;

         if (side == -1 )
         {
            fa /= 2;
         }

         side = -1;
      }
      else if ( 0 < fa*fr )
      {
         cmin = c_guess;
         fa = fr;

         if ( side == 1 )
         {
            fb /= 2;
         }

         side = 1;
      }
      else
      {
         break;
      }
   }

   // After max_iterations, a solution could not be found
   if ( max_iterations <= current_iteration )
   {
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_INLSolver,RC_E_SOLUTIONNOTFOUND);
   }

   c = c_guess;

   // check for over-reinforced section
   Float64 Mn = (Mflange+Mbeam) - Mt;

   Float64 Yflange, Ybeam;

   if ( IsZero(Cflange) )
   {
      Yflange = 0;
   }
   else
   {
      Yflange = h - Mflange/Cflange;
   }

   if ( IsZero(Cbeam) )
   {
      Ybeam = 0;
   }
   else
   {
      Ybeam   = h - Mbeam/Cbeam;
   }

   CreateSolution(Mn,c,fs,fps,Cflange,Cbeam,Ft,Yflange,Ybeam,solution);


	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CNLSolver::AnalyzeSection(IRCBeam2Ex* beam,Float64 Yguess,IUnkArray* slices,IPoint2d* pntCG)
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
   for ( iter = m_Slices.begin(); iter != m_Slices.end(); iter++ )
   {
      SLICEINFO& slice = *iter;

      if ( (slice.Bottom < Yguess) && (Yguess < slice.Top) )
      {
         // this slice spans the guess location... 
         // need to clip again 
         SHAPEINFO shape_info;
         shape_info.FgMaterial = slice.FgMaterial;
         shape_info.BgMaterial = slice.BgMaterial;
         shape_info.Shape      = slice.SliceShape;

         SLICEINFO top_slice;
         hr = SliceShape(shape_info,slice.Top,Yguess,top_slice);
         if ( SUCCEEDED(hr) && hr != S_FALSE )
         {
            Float64 ea,eax,eay,Efg,Ebg;
            hr = AnalyzeSlice(Yguess,top_slice,ea,eax,eay,Efg,Ebg);
            if ( FAILED(hr) )
            {
               return hr;
            }

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

//         SLICEINFO bottom_slice;
//         hr = SliceShape(shape_info,Yguess,slice.Bottom,bottom_slice);
//         if ( SUCCEEDED(hr) && hr != S_FALSE )
//         {
//            Float64 ea, eax, eay, Efg, Ebg;
//            hr = AnalyzeSlice(Yguess,bottom_slice,ea,eax,eay,Efg,Ebg);
//            if ( FAILED(hr) )
//            {
//               return hr;
//            }
//
//            EA  += ea;
//            EAx += eax;
//            EAy += eay;
//
//            CComObject<CCrackedSectionSlice>* pSlice;
//            CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
//            pSlice->InitSlice(bottom_slice.SliceShape,bottom_slice.Area,bottom_slice.Xcg,bottom_slice.Ycg,Efg,Ebg);
//            CComPtr<IUnknown> punk;
//            pSlice->QueryInterface(&punk);
//            slices->Add(punk);
//
//#if defined _DEBUG_LOGGING
//            os << std::setw(10) << AREA(bottom_slice.Area) << ", " << std::setw(10) << "T, " << std::setw(10) << LENGTH(bottom_slice.Top) << ", " << std::setw(10) << LENGTH(bottom_slice.Bottom) << ", " << std::setw(20) << LENGTH(bottom_slice.Xcg) << ", " << std::setw(20) << LENGTH(bottom_slice.Ycg) << ", " << std::setw(20) << STRESS(Efg) << ", " << std::setw(20) << STRESS(Ebg) << std::endl;
//#endif // _DEBUG_LOGGING
//         }
      }
      else
      {
         Float64 ea, eax, eay, Efg, Ebg;
         hr = AnalyzeSlice(Yguess,slice,ea,eax,eay,Efg,Ebg);
         if ( FAILED(hr) )
         {
            return hr;
         }

         if ( slice.Ycg < Yguess )
         {
            // slice is on the cracked side so it doesn't contribute
            continue;
         }

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

   // Rebar
   Float64 Es;
   beam->get_Es(&Es);
   IndexType nRebarLayers = 0;
   beam->get_RebarLayerCount(&nRebarLayers);
   for ( IndexType rebarLayerIdx = 0; rebarLayerIdx < nRebarLayers; rebarLayerIdx++ )
   {
      Float64 ds, As, devFactor;
      beam->GetRebarLayer(rebarLayerIdx,&ds,&As,&devFactor);

      // ds is measured down from the top... we need it in section coordinates
      ds = m_Ytop - ds;

      CComPtr<IGenericShape> barShape;
      barShape.CoCreateInstance(CLSID_GenericShape);
      barShape->put_Area(devFactor*As);
      
      CComPtr<IPoint2d> cg;
      barShape->get_Centroid(&cg);
      cg->Move(0,ds);

      CComQIPtr<IShape> shape(barShape);

      CComObject<CCrackedSectionSlice>* pSlice;
      CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
      pSlice->InitSlice(shape,devFactor*As,0.0,ds,Es,0);
      CComPtr<IUnknown> punk;
      pSlice->QueryInterface(&punk);
      slices->Add(punk);


      Float64 ea = devFactor*As*Es;
      Float64 eay = ea*ds;
      Float64 eax = ea*0.0;
      
      EA  += ea;
      EAy += eay;
      EAx += eax;
   }

   // Strand
   Float64 Eps;
   beam->get_Eps(&Eps);
   IndexType nStrandLayers;
   beam->get_StrandLayerCount(&nStrandLayers);
   for ( IndexType strandLayerIdx = 0; strandLayerIdx < nStrandLayers; strandLayerIdx++ )
   {
      Float64 dps, Aps, devFactor;
      beam->GetStrandLayer(strandLayerIdx,&dps,&Aps,&devFactor);

      CComPtr<IGenericShape> strandShape;
      strandShape.CoCreateInstance(CLSID_GenericShape);
      strandShape->put_Area(devFactor*Aps);
      
      CComPtr<IPoint2d> cg;
      strandShape->get_Centroid(&cg);
      cg->Move(0,dps);

      CComQIPtr<IShape> shape(strandShape);

      CComObject<CCrackedSectionSlice>* pSlice;
      CComObject<CCrackedSectionSlice>::CreateInstance(&pSlice);
      pSlice->InitSlice(shape,devFactor*Aps,0.0,dps,Eps,0);
      CComPtr<IUnknown> punk;
      pSlice->QueryInterface(&punk);
      slices->Add(punk);

      Float64 ea = devFactor*Aps*Eps;
      Float64 eay = ea*dps;
      Float64 eax = ea*0.0;
      
      EA  += ea;
      EAy += eay;
      EAx += eax;
   }

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

HRESULT CNLSolver::AnalyzeSlice(Float64 Yguess,SLICEINFO& slice,Float64& EA,Float64& EAx,Float64& EAy,Float64& Efg,Float64& Ebg)
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
      {
         return S_OK;
      }
   }

   if ( slice.FgMaterial )
   {
      slice.FgMaterial->get_ModulusOfElasticity(&Efg);
   }
   else
   {
      Efg = 0;
   }

   if ( slice.BgMaterial )
   {
      slice.BgMaterial->get_ModulusOfElasticity(&Ebg);
   }
   else
   {
      Ebg = 0;
   }

   Float64 E = (Efg - Ebg);

   EA  = E*slice.Area;
   EAx = EA*slice.Xcg;
   EAy = EA*slice.Ycg;
   return S_OK;
}

HRESULT CNLSolver::SliceShape(const SHAPEINFO& shapeInfo,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo)
{
   HRESULT hr;

   m_ClippingRect->put_Top(sliceTop);
   m_ClippingRect->put_Bottom(sliceBottom);

   CComPtr<IShape> clipped_shape;
   hr = shapeInfo.Shape->ClipIn(m_ClippingRect,&clipped_shape);

   // sometimes the shape isn't even in the clipping box so
   // the result is nullptr... go to next slice
   if ( clipped_shape == nullptr )
   {
      return S_FALSE;
   }

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

HRESULT CNLSolver::SolveBisectionMethod(IRCBeam2Ex* beam,ICrackedSectionSolution* *solution)
{
   ATLASSERT(false);
   return E_NOTIMPL;
}

HRESULT CNLSolver::SolveFalsePositionMethod(IRCBeam2Ex* rcbeam,ICrackedSectionSolution* *solution)
{
#if defined _DEBUG_LOGGING
   m_Log.CoCreateInstance(CLSID_WBFLErrorLog);
   m_Log->Open(CComBSTR("CrackedSectionSolver.log"),&m_dwCookie);
#endif // _DEBUG_LOGGING

   HRESULT hr;

   // solve with method of false position (aka regula falsi method)
   // http://en.wikipedia.org/wiki/False_position_method
   // http://mathworld.wolfram.com/MethodofFalsePosition.html

   if ( rcbeam == nullptr )
   {
      return E_FAIL;
   }

   InitMaterials(rcbeam);

   SliceSection(rcbeam);

   Float64 Ylower = m_Ybottom;
   Float64 Yupper = m_Ytop;

   CComPtr<IPoint2d> pntCG;
   pntCG.CoCreateInstance(CLSID_Point2d);
   
   CComPtr<IUnkArray> slices;
   slices.CoCreateInstance(CLSID_UnkArray);


   Float64 result_lower;
   hr = AnalyzeSection(rcbeam,Ylower,slices,pntCG);
   if ( FAILED(hr) )
   {
      return hr;
   }
   
   Float64 resultY;
   pntCG->get_Y(&resultY);
   result_lower = Ylower - resultY;

   Float64 result_upper;
   slices->Clear();
   hr = AnalyzeSection(rcbeam,Yupper,slices,pntCG);
   if ( FAILED(hr) )
   {
      return hr;
   }

   pntCG->get_Y(&resultY);
   result_upper = Yupper - resultY;

   Float64 Y = Ylower;
   Float64 result = result_lower;

   int side = 0;
   long iter = 0;
   for ( iter = 0; iter < m_MaxIter; iter++ )
   {
      if ( IsZero(result,m_CGTolerance) && IsZero(result_lower,m_CGTolerance) && IsZero(result_upper,m_CGTolerance) )
      {
         break; // converged
      }

      // guess next value
      Y = (result_upper*Ylower - result_lower*Yupper) / ( result_upper - result_lower );

      slices->Clear();
      hr = AnalyzeSection(rcbeam,Y,slices,pntCG);
      if ( FAILED(hr) )
      {
         return hr;
      }

      pntCG->get_Y(&resultY);
      result = Y - resultY;

      if ( 0 < result*result_upper )
      {
         Yupper = Y;
         result_upper = result;
         if ( side == -1 )
         {
            result_lower /= 2;
         }

         side = -1;
      }
      else if ( 0 < result_lower*result )
      {
         Ylower = Y;
         result_lower = result;
         if ( side == 1 )
         {
            result_upper /= 2;
         }

         side = 1;
      }
      else
      {
         break;
      }
   }

   if ( m_MaxIter <= iter )
   {
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_ICrackedSectionSolver,RC_E_SOLUTIONNOTFOUND);
   }

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
  
HRESULT CNLSolver::InitMaterials(IRCBeam2Ex* rcbeam)
{
   Float64 fy, Es;
   rcbeam->get_fy(&fy);
   rcbeam->get_Es(&Es);

   Float64 fcSlab, fcBeam;
   rcbeam->get_FcSlab(&fcSlab);
   rcbeam->get_FcBeam(&fcBeam);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   if ( !m_bUserSlabConcrete )
   {
      m_SlabConcreteModel.Release();
      HRESULT hr = InitConcreteModel(&m_SlabConcreteModel,unitServer,fcSlab);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }
   if ( !m_bUserBeamConcrete )
   {
      m_BeamConcreteModel.Release();
      HRESULT hr = InitConcreteModel(&m_BeamConcreteModel,unitServer,fcBeam);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   if ( !m_bUserStrandModel )
   {
      m_StrandModel.Release();
      HRESULT hr = InitStrandModel(&m_StrandModel,unitServer);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   if ( !m_bUserRebarModel )
   {
      m_RebarModel.Release();
      HRESULT hr = InitRebarModel(&m_RebarModel,fy,Es);
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   return S_OK;
}
