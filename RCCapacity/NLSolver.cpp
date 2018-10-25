///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

#if defined _DEBUG_
#include <sstream>
#endif // _DEBUG_

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNLSolver
STDMETHODIMP CNLSolver::put_Slices(long nSlices)
{
   if ( nSlices < 1 )
      return E_INVALIDARG;

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

   if ( model != NULL )
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
      (*model)->AddRef();

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_BeamConcreteModel(IStressStrain* model)
{
   m_BeamConcreteModel.Release();
   m_bUserBeamConcrete = false;

   if ( model != NULL )
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
      (*model)->AddRef();

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_StrandModel(IStressStrain* model)
{
   m_bUserStrandModel = false;
   m_StrandModel.Release();

   if ( model != NULL )
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
      (*model)->AddRef();

   return S_OK;
}

STDMETHODIMP CNLSolver::putref_RebarModel(IStressStrain* model)
{
   m_bUserRebarModel = false;
   m_RebarModel.Release();

   if ( model != NULL )
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
      (*model)->AddRef();

   return S_OK;
}

STDMETHODIMP CNLSolver::put_RebarDevLengthFactor(Float64 devLengthFactor)
{
   if ( !InRange(0.0,devLengthFactor,1.0) )
      return E_INVALIDARG;

   m_RebarDevLengthFactor = devLengthFactor;
   return S_OK;
}

STDMETHODIMP CNLSolver::get_RebarDevLengthFactor(Float64* devLengthFactor)
{
   CHECK_RETVAL(devLengthFactor);
   *devLengthFactor = m_RebarDevLengthFactor;
   return S_OK;
}

STDMETHODIMP CNLSolver::put_StrandDevLengthFactor(Float64 devLengthFactor)
{
   if ( !InRange(0.0,devLengthFactor,1.0) )
      return E_INVALIDARG;

   m_StrandDevLengthFactor = devLengthFactor;
   return S_OK;
}

STDMETHODIMP CNLSolver::get_StrandDevLengthFactor(Float64* devLengthFactor)
{
   CHECK_RETVAL(devLengthFactor);
   *devLengthFactor = m_StrandDevLengthFactor;
   return S_OK;
}

HRESULT CNLSolver::InitConcreteModel(IStressStrain** model,IUnitServer* unitServer,Float64 fc)
{
   CComObject<CUnconfinedConcrete>* pConcreteModel;
   CComObject<CUnconfinedConcrete>::CreateInstance(&pConcreteModel);

   (*model) = pConcreteModel;
   (*model)->AddRef();

   CComQIPtr<IUnconfinedConcrete> ucc(*model);

   CComQIPtr<ISupportUnitServer> sus(ucc);
   sus->putref_UnitServer(unitServer);

   if ( FAILED(ucc->put_fc(fc)) )
   {
      return CComCoClass<CNLSolver>::Error(IDS_E_INITCONCRETE,IID_INLSolver,RC_E_INITCONCRETE);
   }

   return S_OK;
}

void CNLSolver::InitStrandModel(IStressStrain** model,IUnitServer* unitServer)
{
   CComObject<CPSPowerFormula>* pStrandModel;
   CComObject<CPSPowerFormula>::CreateInstance(&pStrandModel);

   (*model) = pStrandModel;
   (*model)->AddRef();

   CComQIPtr<ISupportUnitServer> sus(*model);
   sus->putref_UnitServer(unitServer);
}

void CNLSolver::InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es)
{
   CComObject<CRebarModel>* pRebarModel;
   CComObject<CRebarModel>::CreateInstance(&pRebarModel);

   (*model) = pRebarModel;
   (*model)->AddRef();

   CComQIPtr<IRebarModel> rebar_model(*model);

   rebar_model->Init(fy,Es,0.11);
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
      return hr;

   CopySolution(solution_ex,solution);
   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2* rcbeam,IRCSolution* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeam2ToRCBeam2Ex(rcbeam,&rcbeam2);

   CComPtr<IRCSolutionEx> solution_ex;
	HRESULT hr = Solve(rcbeam2,&solution_ex);
   if ( FAILED(hr) )
      return hr;

   CopySolution(solution_ex,solution);
   return S_OK;
}

STDMETHODIMP CNLSolver::Solve(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution)
{
//   return SolveBisectionMethod(rcbeam,solution);
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

   Float64 h;
   h = hbeam + hf; // overall height

    // determine approximate slice height
   Float64 approx_slice_height = h / m_nSlices;

   // want to use slice heights that are basically uniform.
   // want to use slices that exactly fit the slab

   // for this height, how may slices are required for the slab
   Uint32 nMinSlabSlices = (IsZero(hf) ? 0 : 5); // use no fewer than 5 slices in the slab
   Uint32 nSlabSlices = (Uint32)floor(hf / approx_slice_height);
   nSlabSlices = _cpp_max(nMinSlabSlices,nSlabSlices);
   Float64 hSlabSlice = hf / nSlabSlices;

   // determine height of beam slices
   Uint32 nBeamSlices = m_nSlices - nSlabSlices;
   if ( nBeamSlices < 0 )
      nBeamSlices = m_nSlices;

   Float64 hBeamSlice = hbeam/nBeamSlices;



   //
   // slice slab
   //

   // no need to do real clipping because it is a rectangle, area and cg are easy to determine
   for ( Uint32 sliceIdx = 0; sliceIdx < nSlabSlices; sliceIdx++ )
   {
      Float64 top = h - sliceIdx*hSlabSlice;
      Float64 bot = top - hSlabSlice;
      Float64 y_cg = (top + bot)/2;
      Float64 area = b*hSlabSlice;

      SLICEINFO slice_info;
      slice_info.top = top;
      slice_info.bot = bot;
      slice_info.y_cg = y_cg;
      slice_info.area = area;
      slice_info.bSlabSlice = true;

      m_Slices.push_back(slice_info);
   }

   //
   // slice beam
   //

   // Create the clipping rectangle (set its size later)
   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );

   // set width of clipping rectangle (make it 2bw wide)
   clipRect->put_Left( -bw );
   clipRect->put_Right( bw );

   for ( Uint32 sliceIdx = 0; sliceIdx < nBeamSlices; sliceIdx++ )
   {
      Float64 top = hbeam - sliceIdx*hBeamSlice;
      Float64 bot = top - hBeamSlice;

      clipRect->put_Top(top);
      clipRect->put_Bottom(bot);

      CComPtr<IShape> clipShape;
      CComQIPtr<IShape> beamShape(beam);

      beamShape->ClipIn(clipRect,&clipShape);

      CComPtr<IShapeProperties> props;

      SLICEINFO slice_info;
      slice_info.top = top;
      slice_info.bot = bot;
      slice_info.bSlabSlice = false;
      if ( clipShape == NULL )
      {
         // this hapens when the slice is so small that it get's squashed down to nothing
         slice_info.area = 0;
         slice_info.y_cg = (top + bot)/2;
      }
      else
      {
         clipShape->get_ShapeProperties(&props);
         props->get_Area(&slice_info.area);

         CComPtr<IPoint2d> centroid;
         props->get_Centroid(&centroid);
         centroid->get_Y(&slice_info.y_cg);

         slice_info.slice_shape = clipShape;
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
      top = slice.top;
      slice_bottom = slice.bot;
      Y = slice.y_cg;
      area = slice.area;

      bool bClippingSlab = slice.bSlabSlice;

      Float64 na = h - c_guess; // location of neutral axis measured from bottom
      if ( slice.bot <= na && na < slice.top )
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

            if ( clipShape == NULL )
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
         m_SlabConcreteModel->ComputeStress(ec,&fc);
      else
         m_BeamConcreteModel->ComputeStress(ec,&fc);

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
   CollectionIndexType nRebarLayers = 0;
   rcbeam->get_RebarLayerCount(&nRebarLayers);
   Float64 TotalAs = 0;
   Ft = 0;
   Mt = 0;
   fs->Clear();
   for (CollectionIndexType rebar = 0; rebar < nRebarLayers; rebar++ )
   {
      Float64 ds, As, devFactor;
      rcbeam->GetRebarLayer(rebar,&ds,&As,&devFactor);
      Float64 es = GetStrain(m_ec,ds,c_guess,0,Es);
      Float64 stress;
      m_RebarModel->ComputeStress(es,&stress);

      if ( devFactor < 1.0 )
      {
         // bar is not fully developed therefore it will pull out before it can yield
         // determine the maximum stress the bar can carry
         Float64 maxRebarStress = devFactor * fy;
         if ( maxRebarStress < stress )
            stress = maxRebarStress;
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

   CollectionIndexType nStrandLayers = 0;
   rcbeam->get_StrandLayerCount(&nStrandLayers);
   fps->Clear();
   for ( CollectionIndexType strand = 0; strand < nStrandLayers; strand++ )
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
            stress = maxStrandStress;
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

   Float64 fcSlab, fcBeam;
   Float64 b,h,hf;
   CComPtr<IShape> beam;

   rcbeam->get_FcSlab(&fcSlab);
   rcbeam->get_FcBeam(&fcBeam);

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);

   rcbeam->get_Beam(&beam);
   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);
   Float64 Ixy;
   beam_props->get_Ixy(&Ixy);
   if ( !IsZero(Ixy) )
      return Error(IDS_E_BEAMNOTSYMMETRIC,IID_INLSolver,RC_E_BEAMNOTSYMMETRIC);

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

   if ( !m_bUserSlabConcrete )
   {
      m_SlabConcreteModel.Release();
      hr = InitConcreteModel(&m_SlabConcreteModel,unitServer,fcSlab);
      if ( FAILED(hr) )
         return hr;
   }
   if ( !m_bUserBeamConcrete )
   {
      m_BeamConcreteModel.Release();
      hr = InitConcreteModel(&m_BeamConcreteModel,unitServer,fcBeam);
      if ( FAILED(hr) )
         return hr;
   }

   if ( !m_bUserStrandModel )
   {
      m_StrandModel.Release();
      InitStrandModel(&m_StrandModel,unitServer);
   }

   if ( !m_bUserRebarModel )
   {
      m_RebarModel.Release();
      InitRebarModel(&m_RebarModel,fy,Es);
   }

   hr = SliceSection(rcbeam);
   if ( FAILED(hr) )
      return hr;

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
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_INLSolver,RC_E_SOLUTIONNOTFOUND);

   c = c_guess;

   // check for over-reinforced section
   Float64 Mn = (Mflange+Mbeam) - Mt;

   Float64 Yflange, Ybeam;

   if ( IsZero(Cflange) )
      Yflange = 0;
   else
      Yflange = h - Mflange/Cflange;

   if ( IsZero(Cbeam) )
      Ybeam = 0;
   else
      Ybeam   = h - Mbeam/Cbeam;

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

   Float64 fy, Es;
   rcbeam->get_fy(&fy);
   rcbeam->get_Es(&Es);

   Float64 fcSlab, fcBeam;
   Float64 b,h,hf;
   CComPtr<IShape> beam;

   rcbeam->get_FcSlab(&fcSlab);
   rcbeam->get_FcBeam(&fcBeam);

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);

   rcbeam->get_Beam(&beam);
   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);
   Float64 Ixy;
   beam_props->get_Ixy(&Ixy);
   if ( !IsZero(Ixy) )
      return Error(IDS_E_BEAMNOTSYMMETRIC,IID_INLSolver,RC_E_BEAMNOTSYMMETRIC);

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

   if ( !m_bUserSlabConcrete )
   {
      m_SlabConcreteModel.Release();
      hr = InitConcreteModel(&m_SlabConcreteModel,unitServer,fcSlab);
      if ( FAILED(hr) )
         return hr;
   }
   if ( !m_bUserBeamConcrete )
   {
      m_BeamConcreteModel.Release();
      hr = InitConcreteModel(&m_BeamConcreteModel,unitServer,fcBeam);
      if ( FAILED(hr) )
         return hr;
   }

   if ( !m_bUserStrandModel )
   {
      m_StrandModel.Release();
      InitStrandModel(&m_StrandModel,unitServer);
   }

   if ( !m_bUserRebarModel )
   {
      m_RebarModel.Release();
      InitRebarModel(&m_RebarModel,fy,Es);
   }

   hr = SliceSection(rcbeam);
   if ( FAILED(hr) )
      return hr;

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
         break;

      c_guess = (fa*cmax - fb*cmin)/(fa-fb);

      hr = AnalyzeSection(rcbeam,c_guess,&Mflange,&Mbeam,&Mt,fs,fps,&Cflange,&Cbeam,&Ft);

      fr = (Cflange+Cbeam-Ft);

      if ( fr*fb > 0 )
      {
         cmax = c_guess;
         fb = fr;

         if (side == -1 )
            fa /= 2;

         side = -1;
      }
      else if ( fa*fr > 0 )
      {
         cmin = c_guess;
         fa = fr;

         if ( side == 1 )
            fb /= 2;

         side = 1;
      }
      else
         break;
   }

   // After max_iterations, a solution could not be found
   if ( max_iterations <= current_iteration )
      return Error(IDS_E_SOLUTIONNOTFOUND,IID_INLSolver,RC_E_SOLUTIONNOTFOUND);

   c = c_guess;

   // check for over-reinforced section
   Float64 Mn = (Mflange+Mbeam) - Mt;

   Float64 Yflange, Ybeam;

   if ( IsZero(Cflange) )
      Yflange = 0;
   else
      Yflange = h - Mflange/Cflange;

   if ( IsZero(Cbeam) )
      Ybeam = 0;
   else
      Ybeam   = h - Mbeam/Cbeam;

   CreateSolution(Mn,c,fs,fps,Cflange,Cbeam,Ft,Yflange,Ybeam,solution);


	return S_OK;
}
