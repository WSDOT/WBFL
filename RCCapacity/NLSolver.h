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

// NLSolver.h : Declaration of the CNLSolver

#ifndef __NLSOLVER_H_
#define __NLSOLVER_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CNLSolver
class ATL_NO_VTABLE CNLSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNLSolver, &CLSID_NLSolver>,
	public INLSolver,
	public IRCSolver2,
	public IRCSolver2Ex
{
public:
	CNLSolver()
	{
      m_nSlices = 25;
      m_Tolerance = 0.001;
      m_StrandDevLengthFactor = 1.0;
      m_RebarDevLengthFactor = 1.0;
      m_bCflangeOverhangOnly = VARIANT_FALSE;
      m_ec = 0.003;
      m_bUserSlabConcrete = false;
      m_bUserBeamConcrete = false;
      m_bUserStrandModel  = false;
      m_bUserRebarModel   = false;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_NLSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNLSolver)
	COM_INTERFACE_ENTRY(INLSolver)
	COM_INTERFACE_ENTRY(IRCSolver)
	COM_INTERFACE_ENTRY(IRCSolver2)
	COM_INTERFACE_ENTRY(IRCSolver2Ex)
END_COM_MAP()

private:
   typedef struct SLICEINFO
   {
      Float64 top;
      Float64 bot;
      Float64 area;
      Float64 y_cg;
      bool bSlabSlice;
      CComPtr<IShape> slice_shape;
   } SLICEINFO;

   long m_nSlices;
   Float64 m_Tolerance;
   Float64 m_StrandDevLengthFactor;
   Float64 m_RebarDevLengthFactor;
   Float64 m_ec; // concrete crushing strain
   bool m_bUserSlabConcrete; // keeps track of concrete model origin
   bool m_bUserBeamConcrete; // keeps track of concrete model origin
   bool m_bUserStrandModel;
   bool m_bUserRebarModel;
   VARIANT_BOOL m_bCflangeOverhangOnly;
   CComPtr<IStressStrain> m_SlabConcreteModel;
   CComPtr<IStressStrain> m_BeamConcreteModel;
   CComPtr<IStressStrain> m_StrandModel;
   CComPtr<IStressStrain> m_RebarModel;
   HRESULT InitConcreteModel(IStressStrain** model,IUnitServer* unitServer,Float64 fc);
   void InitStrandModel(IStressStrain** model,IUnitServer* unitServer);
   void InitRebarModel(IStressStrain** model,Float64 fy,Float64 Es);

   HRESULT AnalyzeSection(IRCBeam2Ex* rcbeam,Float64 c_guess,Float64* pMflange,Float64* pMbeam,Float64* pMt,IDblArray* fs,IDblArray* fps,Float64* pCflange,Float64* pCbeam,Float64* pFt);
   HRESULT SliceSection(IRCBeam2Ex* rcbeam);
   std::vector<SLICEINFO> m_Slices;

   HRESULT SolveBisectionMethod(IRCBeam2Ex* beam,IRCSolutionEx* *solution);
   HRESULT SolveFalsePositionMethod(IRCBeam2Ex* rcbeam,IRCSolutionEx* *solution);

// IRCSolver2Ex
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2Ex* beam,/*[out,retval]*/ IRCSolutionEx* *solution);

// IRCSolver2
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam2* beam,/*[out,retval]*/ IRCSolution* *solution);

// IRCSolver
public:
	STDMETHOD(Solve)(/*[in]*/ IRCBeam* beam,/*[out,retval]*/ IRCSolution* *solution);

// INLSolver
public:
	STDMETHOD(get_IsCflangeOverhangOnly)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsCflangeOverhangOnly)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(put_Slices)(/*[in]*/ long nSlices);
   STDMETHOD(get_Slices)(/*[out,retval]*/ long* nSlices);
   STDMETHOD(put_Tolerance)(/*[in]*/ Float64 tolerance);
   STDMETHOD(get_Tolerance)(/*[out,retval]*/ Float64* tolerance);
   STDMETHOD(putref_BeamConcreteModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_BeamConcreteModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(putref_SlabConcreteModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_SlabConcreteModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(putref_StrandModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_StrandModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(putref_RebarModel)(/*[in]*/ IStressStrain* model);
   STDMETHOD(get_RebarModel)(/*[out,retval]*/ IStressStrain* *model);
   STDMETHOD(put_StrandDevLengthFactor)(/*[in]*/ Float64 devLengthFactor);
   STDMETHOD(get_StrandDevLengthFactor)(/*[out,retval]*/ Float64* devLengthFactor);
   STDMETHOD(put_RebarDevLengthFactor)(/*[in]*/ Float64 devLengthFactor);
   STDMETHOD(get_RebarDevLengthFactor)(/*[out,retval]*/ Float64* devLengthFactor);
   STDMETHOD(put_ConcreteCrushingStrain)(/*[in]*/ Float64 ec);
   STDMETHOD(get_ConcreteCrushingStrain)(/*[out,retval]*/ Float64* ec);
};

#endif //__NLSOLVER_H_
