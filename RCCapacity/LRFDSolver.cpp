///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// LRFDSolver.cpp : Implementation of CLRFDSolver
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "LRFDSolver.h"
#include "RCSolution.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolver

STDMETHODIMP CLRFDSolver::put_UnitMode(SpecUnitType unitMode)
{
   m_UnitMode = unitMode;
   return S_OK;
}

STDMETHODIMP CLRFDSolver::get_UnitMode(SpecUnitType* unitMode)
{
   CHECK_RETVAL(unitMode);
   *unitMode = m_UnitMode;
   return S_OK;
}

STDMETHODIMP CLRFDSolver::Solve(IRCBeam *beam, IRCSolution **solution)
{
   CHECK_IN(beam);
   CHECK_RETOBJ(solution);

   CComQIPtr<ISupportUnitServer> sus(beam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   Float64 fpy;
   Float64 fpu;
   Float64 fs;
   beam->get_fpy(&fpy);
   beam->get_fpu(&fpu);
   beam->get_fy(&fs);

   Float64 k = 2.0*(1.04 - fpy/fpu);

   Float64 As, Aps;
   Float64 ds, dps;
   Float64 fc;
   Float64 b,bw,hf;

   beam->get_As(&As);
   beam->get_Aps(&Aps);

   beam->get_ds(&ds);
   beam->get_dps(&dps);

   beam->get_FcSlab(&fc);

   beam->get_b(&b);
   beam->get_bw(&bw);
   beam->get_hf(&hf);

   // If there is no reinforcedment, then there is no capacity
   if (IsZero(As) && IsZero(Aps) )
   {
      CreateSolution(0,0,0,0,0,0,0,0,VARIANT_FALSE,solution);
      return S_OK;
   }

   Float64 beta1 = Beta1(fc,unitServer,m_UnitMode);

   // compute c to determine if we have a rectangular or t-beam
   // assume T-section behavior
   Float64 c;

   c = Aps*fpu + As*fs - 0.85*fc*(b-bw)*beta1*hf;
   c /= 0.85*fc*bw*beta1 + k*Aps*fpu/dps;

   Float64 Mn;
   VARIANT_BOOL bIsOverReinforced = VARIANT_FALSE;
   Float64 Cflange, Cweb;
   Float64 Yflange, Yweb;
   Float64 fps;
   Float64 de;

   if ( c < hf )
   {
      // rectangular behavior
      c = Aps*fpu + As*fs;
      c /= 0.85*fc*beta1*b + k*Aps*fpu/dps;

      Float64 a = beta1 * c;
      
      fps = fpu*(1.0 - k*c/dps);

      if ( m_bCflangeOverhangOnly == VARIANT_TRUE )
      {
         Cflange = 0.85*fc*(b-bw)*a;
         Yflange = a/2;
         Cweb    = 0.85*fc*bw*a;
         Yweb    = a/2;
      }
      else
      {
         Cflange = 0.85*fc*b*a;
         Yflange = a/2;
         Cweb    = 0;
         Yweb    = 0;
      }

      Mn = Aps*fps*(dps - a/2) + As*fs*(ds - a/2);
   }
   else
   {
      Float64 a = beta1 * c;

      fps = fpu*(1.0 - k*c/dps);
      
      Cflange = 0.85*fc*(b-bw)*beta1*hf;
      Yflange = hf/2;
      Cweb    = 0.85*fc*bw*a;
      Yweb    = a/2;
      Mn = Aps*fps*(dps - a/2) + As*fs*(ds - a/2) + Cflange*(a/2- beta1*hf/2);
   }

   de = (Aps*fps*dps + As*fs*ds)/(Aps*fps + As*fs);

   Float64 T = Aps*fps + As*fs;

   // check for over-reinforced section
   if ( 0.42 < c/de )
   {
      // over reinforced section
      bIsOverReinforced = VARIANT_TRUE;
      Cflange = -1;
      Cweb    = -1;
      T       = -1;
      Yflange = -1;
      Yweb    = -1;
      Mn = (0.36*beta1 - 0.08*beta1*beta1)*fc*bw*de*de + 0.85*beta1*fc*(b-bw)*hf*(de - 0.5*hf);
   }


   CreateSolution(Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bIsOverReinforced,solution);

	return S_OK;
}

STDMETHODIMP CLRFDSolver::get_IsCflangeOverhangOnly(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_bCflangeOverhangOnly;
	return S_OK;
}

STDMETHODIMP CLRFDSolver::put_IsCflangeOverhangOnly(VARIANT_BOOL newVal)
{
   m_bCflangeOverhangOnly = newVal;
	return S_OK;
}
