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

// LRFDSolver2.cpp : Implementation of CLRFDSolver2
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "LRFDSolver2.h"
#include "LRFDPrestressFormula.h"
#include "RebarModel.h"
#include "RCBeam2.h"
#include "Helper.h"
#include <MathEx.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolver2

STDMETHODIMP CLRFDSolver2::put_Tolerance(Float64 tolerance)
{
   m_Tolerance = fabs(tolerance);
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::get_Tolerance(Float64* tolerance)
{
   CHECK_RETVAL(tolerance);
   *tolerance = m_Tolerance;
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::putref_StrandModel(IStressStrain* model)
{
   m_StrandModel = model;
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::get_StrandModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_StrandModel;

   if ( m_StrandModel )
      (*model)->AddRef();

   return S_OK;
}

STDMETHODIMP CLRFDSolver2::putref_RebarModel(IStressStrain* model)
{
   m_RebarModel = model;
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::get_RebarModel(IStressStrain* *model)
{
   CHECK_RETOBJ(model);

   (*model) = m_RebarModel;

   if ( m_RebarModel )
      (*model)->AddRef();

   return S_OK;
}

void CLRFDSolver2::InitStrandModel(IStressStrain** model,Float64 fpu,Float64 Eps)
{
   CComObject<CLRFDPrestressFormula>* pStrandModel;
   CComObject<CLRFDPrestressFormula>::CreateInstance(&pStrandModel);
   pStrandModel->put_Fpu(fpu);
   pStrandModel->put_Eps(Eps);

   (*model) = pStrandModel;
   (*model)->AddRef();
}

void CLRFDSolver2::InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es)
{
   CComObject<CRebarModel>* pRebarModel;
   CComObject<CRebarModel>::CreateInstance(&pRebarModel);

   (*model) = pRebarModel;
   (*model)->AddRef();

   CComQIPtr<IRebarModel> rebar_model(*model);

   rebar_model->Init(fy,Es,0.11);
}

STDMETHODIMP CLRFDSolver2::put_UnitMode(SpecUnitType unitMode)
{
   m_UnitMode = unitMode;
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::get_UnitMode(SpecUnitType* unitMode)
{
   CHECK_RETVAL(unitMode);

   *unitMode = m_UnitMode;
   return S_OK;
}

STDMETHODIMP CLRFDSolver2::Solve(IRCBeam* rcbeam,IRCSolution* *solution)
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

STDMETHODIMP CLRFDSolver2::Solve(IRCBeam2* rcbeam,IRCSolutionEx* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComPtr<IRCBeam2Ex> rcbeam2;
   RCBeam2ToRCBeam2Ex(rcbeam,&rcbeam2);

	HRESULT hr = Solve(rcbeam2,solution);
   if ( FAILED(hr) )
      return hr;

   return S_OK;
}

STDMETHODIMP CLRFDSolver2::Solve(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution)
{
   CHECK_IN(rcbeam);
   CHECK_RETOBJ(solution);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   CComPtr<IDblArray> fs, fps;
   fs.CoCreateInstance(CLSID_DblArray);
   fps.CoCreateInstance(CLSID_DblArray);

   Float64 Fc;
   Float64 Ft;
   Float64 Mt;

   Float64 fpy;
   Float64 fpu;
   Float64 fy;
   rcbeam->get_fpy(&fpy);
   rcbeam->get_fpu(&fpu);
   rcbeam->get_fy(&fy);

   Float64 Es, Eps;
   rcbeam->get_Es(&Es);
   rcbeam->get_Eps(&Eps);

   Float64 k = 2.0*(1.04 - fpy/fpu);

   Float64 fpe;
   Float64 fcSlab, fcBeam;
   Float64 b,hf;

   rcbeam->get_fpe(&fpe);

   rcbeam->get_FcSlab(&fcSlab);
   rcbeam->get_FcBeam(&fcBeam);
   Float64 fc = Min(fcSlab,fcBeam); // assume entire section is made of the weaker material

   rcbeam->get_b(&b);
   rcbeam->get_hf(&hf);

   CComPtr<IShape> beam;
   rcbeam->get_Beam(&beam);
   CComPtr<IShapeProperties> beam_props;
   beam->get_ShapeProperties(&beam_props);
   Float64 Ixy;
   beam_props->get_Ixy(&Ixy);
   if ( !IsZero(Ixy) )
   {
      return Error(IDS_E_BEAMNOTSYMMETRIC,IID_ILRFDSolver2,RC_E_BEAMNOTSYMMETRIC);
   }

   IndexType nRebarLayers, nStrandLayers;
   rcbeam->get_RebarLayerCount(&nRebarLayers);
   rcbeam->get_StrandLayerCount(&nStrandLayers);

   // A quick check to make sure there is actually reinforcement
   Float64 Abar = 0;
   for (IndexType rebar = 0; rebar < nRebarLayers; rebar++ )
   {
      Float64 ds, As, devFactor;
      rcbeam->GetRebarLayer(rebar,&ds,&As,&devFactor);
      Abar += devFactor*As;
   }

   Float64 Astrand = 0;
   for ( IndexType strand = 0; strand < nStrandLayers; strand++ )
   {
      Float64 dps, Aps, devFactor;
      rcbeam->GetStrandLayer(strand,&dps,&Aps,&devFactor);
      Astrand += devFactor*Aps;
   }

   Float64 alpha1 = Alpha1(fc,unitServer,m_UnitMode);
   Float64 beta1  = Beta1(fc,unitServer,m_UnitMode);

   // No reinforcement... no capacity
   if ( IsZero(Abar) && IsZero(Astrand) )
   {
      CreateSolution(alpha1,beta1,0,0,fs,fps,0,0,0,0,0,solution);
      return S_OK;
   }

   CComPtr<IRect2d> box;
   beam->get_BoundingBox(&box);
   Float64 h;
   box->get_Height(&h);
   h += hf; // overall height
   Float64 bw; // assume top flange width to be the width of the beam
   box->get_Width(&bw);

   // make sure the beam shape is correctly located beneath the slab
   CComQIPtr<IXYPosition> position(beam);
   CComPtr<IPoint2d> locator_point;
   position->get_LocatorPoint(lpTopCenter,&locator_point);
   locator_point->Move(0,h-hf);
   position->put_LocatorPoint(lpTopCenter,locator_point);

   Float64 cmin, c, cmax;
   Float64 c_guess;
   c = -1;
   cmin = 0.000001;
   cmax = h;

   if ( !m_StrandModel )
   {
      InitStrandModel(&m_StrandModel,fpu,Eps);
   }

   if ( !m_RebarModel )
   {
      InitRebarModel(&m_RebarModel,fy,Es);
   }

   // setup clipping rectangle for clipping the beam object
   CComPtr<IRect2d> clip_rect;
   clip_rect.CoCreateInstance(CLSID_Rect2d);
   clip_rect->put_Top(h + 100); // put top well above beam
   clip_rect->put_Left(-b-100);
   clip_rect->put_Right(b+100);
   // bottom goes at "a"

   CComPtr<IShape> clipped_beam;
   CComPtr<IShapeProperties> props; // properties of beam/web only
   Float64 clipped_area;

   Float64 a;
   bool bDone = false;
   do
   {
      c_guess = (cmin+cmax)/2;

      // compute Fc
      a = beta1*c_guess;

      if ( a < hf )
      {
         Fc = alpha1*fc*a*b;
      }
      else
      {
         // clip the beam to get the area of the compression block
         clip_rect->put_Bottom(h - a);

         clipped_beam.Release();
         beam->ClipIn(clip_rect,&clipped_beam);

         props.Release();
         clipped_beam->get_ShapeProperties(&props);
         props->get_Area(&clipped_area);

         Fc = alpha1*fc*hf*b + alpha1*fc*clipped_area;
      }

      // compute Ft
      Ft = 0;
      Mt = 0; // moments taken about top of section

      fs->Clear();
      for ( IndexType rebar = 0; rebar < nRebarLayers; rebar++ )
      {
         Float64 ds, As, devFactor;
         rcbeam->GetRebarLayer(rebar,&ds,&As,&devFactor);

         Float64 stress;
         Float64 es  = GetStrain(m_ec,ds,c_guess,0,Es);
         m_RebarModel->ComputeStress(es,&stress);

         Float64 maxRebarStress = devFactor * fy;
         if ( maxRebarStress < stress )
         {
            stress = maxRebarStress;
         }

         Float64 T = As*stress;
         Ft += T;
         Mt += T*ds;
         fs->Add(stress);
      }

      fps->Clear();
      for ( IndexType strand = 0; strand < nStrandLayers; strand++ )
      {
         Float64 dps, Aps, devFactor;
         rcbeam->GetStrandLayer(strand,&dps,&Aps,&devFactor);

         Float64 stress;
         Float64 eps = GetStrain(m_ec,dps,c_guess,fpe,Eps);
         m_StrandModel->ComputeStress(eps,&stress);

         Float64 maxStrandStress = devFactor * fpu;
         if ( maxStrandStress < stress )
         {
            stress = maxStrandStress;
         }

         Float64 T = Aps*stress;
         Ft += T;
         Mt += T*dps;
         fps->Add(stress);
      }

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
   } while ( !bDone );
   
   c = c_guess;

   // check for over-reinforced section
   Float64 Mn = 0;
   Float64 Cflange, Cweb;
   Float64 Yflange, Yweb;
   VARIANT_BOOL bIsOverReinforced;
   bIsOverReinforced = VARIANT_FALSE;
   // compute Mn (moments taken about top of section)
   if ( a < hf )
   {
      // rectangular section
      if ( m_bCflangeOverhangOnly == VARIANT_TRUE )
      {
         Cflange = alpha1*fc*(b-bw)*a;
         Yflange = a/2;
         Cweb    = alpha1*fc*bw*a;
         Yweb    = a/2;
      }
      else
      {
         Cflange = alpha1*fc*b*a;
         Yflange = a/2;
         Cweb    = 0;
         Yweb    = 0;
      }
      Mn = Cflange*Yflange + Cweb*Yweb - Mt;
   }
   else
   {
      // T-section
      if ( m_bCflangeOverhangOnly == VARIANT_TRUE )
      {
         Cflange = alpha1*fc*(b-bw)*hf;
         Yflange = hf/2;
      
         Float64 c_slab = alpha1*fc*bw*hf;
         Float64 c_beam = alpha1*fc*clipped_area;
         Cweb    =  c_slab + c_beam;

         CComPtr<IPoint2d> cg;
         props->get_Centroid(&cg);
         Float64 y;
         cg->get_Y(&y);
         Float64 y_beam = h - y;

         Yweb = (c_slab*(hf/2) + c_beam*y_beam)/Cweb;
      }
      else
      {
         Cflange = alpha1*fc*b*hf;
         Yflange = hf/2;
      
         Cweb    = alpha1*fc*clipped_area;
         CComPtr<IPoint2d> cg;
         props->get_Centroid(&cg);
         Float64 y;
         cg->get_Y(&y);
         Yweb = h - y;
      }

      Mn = Cflange*Yflange + Cweb*Yweb - Mt;
   }

   // Change the sign... this is because moments are take about the top of the section
   Mn *= -1.0;

   CreateSolution(alpha1,beta1,Mn,c,fs,fps,Cflange,Cweb,Ft,Yflange,Yweb,solution);

	return S_OK;
}

STDMETHODIMP CLRFDSolver2::get_IsCflangeOverhangOnly(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bCflangeOverhangOnly;
	return S_OK;
}

STDMETHODIMP CLRFDSolver2::put_IsCflangeOverhangOnly(VARIANT_BOOL newVal)
{
   m_bCflangeOverhangOnly = newVal;
	return S_OK;
}
