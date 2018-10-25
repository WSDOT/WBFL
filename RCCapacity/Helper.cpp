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

#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "Helper.h"
#include "RCBeam2Ex.h"
#include "PCISolutionEx.h"
#include "LRFDSolution.h"
#include "LRFDSolutionEx.h"
#include <MathEx.h>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Float64 Alpha1(Float64 fc,IUnitServer* pUnitServer,SpecUnitType unitType)
{
   // convert fc to proper units
   CComPtr<IUnitConvert> convert;
   pUnitServer->get_UnitConvert(&convert);
   convert->ConvertFromBaseUnits(fc,unitType == suSI ? CComBSTR("MPa") : CComBSTR("psi"),&fc);

   Float64 fc_limit = (unitType == suSI ? 69. : 10000.);
   Float64 fc_step  = (unitType == suSI ?  7. : 1000.);
   
   Float64 alpha1;
   if ( fc < fc_limit )
   {
      alpha1 = 0.85;
   }
   else
   {
      alpha1 = 0.85 - 0.02*((fc - fc_limit)/fc_step);
      alpha1 = Max(alpha1,0.75);
   }

   return alpha1;
}

Float64 Beta1(Float64 fc,IUnitServer* pUnitServer,SpecUnitType unitType)
{
   // convert fc to proper units
   CComPtr<IUnitConvert> convert;
   pUnitServer->get_UnitConvert(&convert);
   convert->ConvertFromBaseUnits(fc,unitType == suSI ? CComBSTR("MPa") : CComBSTR("psi"),&fc);

   Float64 fc_limit = (unitType == suSI ? 28. : 4000.);
   Float64 fc_step  = (unitType == suSI ?  7. : 1000.);
   
   Float64 beta1;
   if ( fc < fc_limit )
   {
      beta1 = 0.85;
   }
   else
   {
      beta1 = 0.85 - 0.05*((fc - fc_limit)/fc_step);
      beta1 = (beta1 < 0.65) ? 0.65 : beta1;
   }

   return beta1;
}

Float64 GetStrain(Float64 ec,Float64 d,Float64 c,Float64 fpe,Float64 Eps)
{
   Float64 eps = ec*(d/c - 1.0) + (fpe/Eps);
   return eps;
}

void CreateSolution(Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bIsOverReinforced,IRCSolution** solution)
{
   CComObject<CRCSolution>* pSolution;
   CComObject<CRCSolution>::CreateInstance(&pSolution);

   pSolution->InitSolution(Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bIsOverReinforced);

   (*solution) = pSolution;
   (*solution)->AddRef();
}

void CreateSolution(Float64 alpha1,Float64 beta1,Float64 Mn,Float64 c,Float64 fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,VARIANT_BOOL bIsOverReinforced,IRCSolution** solution)
{
   CComObject<CLRFDSolution>* pSolution;
   CComObject<CLRFDSolution>::CreateInstance(&pSolution);

   pSolution->InitLRFDSolution(alpha1,beta1,Mn,c,fps,Cflange,Cweb,T,Yflange,Yweb,bIsOverReinforced);

   (*solution) = pSolution;
   (*solution)->AddRef();
}

void CreateSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cbeam,Float64 T,Float64 Yflange,Float64 Yweb,IRCSolutionEx** solution)
{
   CComObject<CRCSolutionEx>* pSolution;
   CComObject<CRCSolutionEx>::CreateInstance(&pSolution);

   pSolution->InitSolution(Mn,c,fs,fps,Cflange,Cbeam,T,Yflange,Yweb);
   
   (*solution) = pSolution;
   (*solution)->AddRef();
}

void CreateSolution(Float64 alpha1,Float64 beta1,Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cbeam,Float64 T,Float64 Yflange,Float64 Yweb,IRCSolutionEx** solution)
{
   CComObject<CLRFDSolutionEx>* pSolution;
   CComObject<CLRFDSolutionEx>::CreateInstance(&pSolution);

   pSolution->InitLRFDSolution(alpha1,beta1,Mn,c,fs,fps,Cflange,Cbeam,T,Yflange,Yweb);
   
   (*solution) = pSolution;
   (*solution)->AddRef();
}

void CreateSolution(Float64 Mn,Float64 c,IDblArray* fs,IDblArray* fps,Float64 Cflange,Float64 Cweb,Float64 T,Float64 Yflange,Float64 Yweb,Float64 beta1,IRCSolutionEx** solution)
{
   CComObject<CPCISolutionEx>* pSolution;
   CComObject<CPCISolutionEx>::CreateInstance(&pSolution);

   pSolution->InitSolution(Mn,c,fs,fps,Cflange,Cweb,T,Yflange,Yweb,beta1);

   (*solution) = pSolution;
   (*solution)->AddRef();
}


void CopySolution(IRCSolutionEx* solution_ex,IRCSolution** solution)
{
   Float64 Mn, c, Cflange, Cweb, Ft, Yflange, Yweb;

   solution_ex->get_Mn(&Mn);
   solution_ex->get_NeutralAxisDepth(&c);
   solution_ex->get_Cflange(&Cflange);
   solution_ex->get_Cweb(&Cweb);
   solution_ex->get_T(&Ft);
   solution_ex->get_Yflange(&Yflange);
   solution_ex->get_Yweb(&Yweb);

   CComPtr<IDblArray> arrFps;
   solution_ex->get_fps(&arrFps);

   CollectionIndexType count;
   arrFps->get_Count(&count);

   Float64 fps = 0;
   if ( count == 1 )
      arrFps->get_Item(0,&fps);

   CreateSolution(Mn,c,fps,Cflange,Cweb,Ft,Yflange,Yweb,VARIANT_FALSE,solution);
}

void RCBeamToRCBeam2Ex(IRCBeam* rcbeam,IRCBeam2Ex** rcbeam2)
{
   CComObject<CRCBeam2Ex>* pRCBeam;
   CComObject<CRCBeam2Ex>::CreateInstance(&pRCBeam);

   (*rcbeam2) = pRCBeam;
   (*rcbeam2)->AddRef();

   Float64 fpy;
   Float64 fpu;
   Float64 fy;
   rcbeam->get_fpy(&fpy);
   rcbeam->get_fpu(&fpu);
   rcbeam->get_fy(&fy);

   (*rcbeam2)->put_fpy(fpy);
   (*rcbeam2)->put_fpu(fpu);
   (*rcbeam2)->put_fy(fy);

   Float64 As, Aps;
   Float64 fpe;
   Float64 ds, dps;
   Float64 fcSlab, fcBeam;
   Float64 b,bw,hf,h;

   rcbeam->get_ds(&ds);
   rcbeam->get_As(&As);
   (*rcbeam2)->AddRebarLayer(ds,As,1.0);

   rcbeam->get_dps(&dps);
   rcbeam->get_Aps(&Aps);
   (*rcbeam2)->AddStrandLayer(dps,Aps,1.0);

   rcbeam->get_fpe(&fpe);
   (*rcbeam2)->put_fpe(fpe);

   rcbeam->get_FcSlab(&fcSlab);
   (*rcbeam2)->put_FcSlab(fcSlab);

   rcbeam->get_FcBeam(&fcBeam);
   (*rcbeam2)->put_FcBeam(fcBeam);

   rcbeam->get_b(&b);
   (*rcbeam2)->put_b(b);

   rcbeam->get_hf(&hf);
   (*rcbeam2)->put_hf(hf);

   rcbeam->get_bw(&bw);
   rcbeam->get_h(&h);
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(h-hf);
   beam->put_Width(bw);

   CComQIPtr<IShape> shape(beam);
   (*rcbeam2)->putref_Beam(shape);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   CComQIPtr<ISupportUnitServer> sus2((*rcbeam2));
   sus2->putref_UnitServer(unitServer);
}

void RCBeam2ToRCBeam2Ex(IRCBeam2* rcbeam,IRCBeam2Ex** rcbeam2)
{
   CComObject<CRCBeam2Ex>* pRCBeam;
   CComObject<CRCBeam2Ex>::CreateInstance(&pRCBeam);

   (*rcbeam2) = pRCBeam;
   (*rcbeam2)->AddRef();

   Float64 fpy;
   Float64 fpu;
   Float64 fy;
   rcbeam->get_fpy(&fpy);
   rcbeam->get_fpu(&fpu);
   rcbeam->get_fy(&fy);

   (*rcbeam2)->put_fpy(fpy);
   (*rcbeam2)->put_fpu(fpu);
   (*rcbeam2)->put_fy(fy);

   Float64 fpe;
   Float64 fcSlab, fcBeam;
   Float64 b,bw,hf,h;

   CollectionIndexType nRebarLayers;
   rcbeam->get_RebarLayerCount(&nRebarLayers);
   for ( CollectionIndexType rebar = 0; rebar < nRebarLayers; rebar++ )
   {
      Float64 ds,As,devFactor;
      rcbeam->GetRebarLayer(rebar,&ds,&As,&devFactor);
      (*rcbeam2)->AddRebarLayer(ds,As,devFactor);
   }

   CollectionIndexType nStrandLayers;
   rcbeam->get_StrandLayerCount(&nStrandLayers);
   for ( CollectionIndexType strand = 0; strand < nStrandLayers; strand++ )
   {
      Float64 dps, Aps, devFactor;
      rcbeam->GetStrandLayer(strand,&dps,&Aps,&devFactor);
      (*rcbeam2)->AddStrandLayer(dps,Aps,devFactor);
   }

   rcbeam->get_fpe(&fpe);
   (*rcbeam2)->put_fpe(fpe);

   rcbeam->get_FcSlab(&fcSlab);
   (*rcbeam2)->put_FcSlab(fcSlab);

   rcbeam->get_FcBeam(&fcBeam);
   (*rcbeam2)->put_FcBeam(fcBeam);

   rcbeam->get_b(&b);
   (*rcbeam2)->put_b(b);

   rcbeam->get_hf(&hf);
   (*rcbeam2)->put_hf(hf);

   rcbeam->get_bw(&bw);
   rcbeam->get_h(&h);
   CComPtr<IRectangle> beam;
   beam.CoCreateInstance(CLSID_Rect);
   beam->put_Height(h-hf);
   beam->put_Width(bw);

   CComQIPtr<IShape> shape(beam);
   (*rcbeam2)->putref_Beam(shape);

   CComQIPtr<ISupportUnitServer> sus(rcbeam);
   CComPtr<IUnitServer> unitServer;
   sus->get_UnitServer(&unitServer);

   CComQIPtr<ISupportUnitServer> sus2((*rcbeam2));
   sus2->putref_UnitServer(unitServer);
}