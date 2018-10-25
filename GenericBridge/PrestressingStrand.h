///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// PrestressingStrand.h : Declaration of the CPrestressingStrand

#ifndef __PRESTRESSINGSTRAND_H_
#define __PRESTRESSINGSTRAND_H_

#include "resource.h"       // main symbols
//#include "GenericBridgeCP.h"

#include <LRFD\StrandPool.h>

/////////////////////////////////////////////////////////////////////////////
// CPrestressingStrand
class ATL_NO_VTABLE CPrestressingStrand : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPrestressingStrand,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPrestressingStrand, &CLSID_PrestressingStrand>,
	public ISupportErrorInfo,
	public IPrestressingStrand,
   public IMaterial,
   public IStructuredStorage2,
//   public CProxyDPrestressingStrandEvents< CPrestressingStrand >,
//   public IPrestressingStrandPointContainerImpl<CPrestressingStrand>,
   public IObjectSafetyImpl<CPrestressingStrand,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CPrestressingStrand() :
      m_bstrName("Unknown")
	{
      m_Grade = Grade270;
      m_Type = LowRelaxation;
      m_Coating = None;
      m_Size = D5000;
	
      m_InstallationStageIdx = 0;
   }

   HRESULT FinalConstruct();
   void FinalRelease();
   
   const matPsStrand* GetStrand();

DECLARE_REGISTRY_RESOURCEID(IDR_PRESTRESSINGSTRAND)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrestressingStrand)
	COM_INTERFACE_ENTRY(IPrestressingStrand)
	COM_INTERFACE_ENTRY(IMaterial)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//   COM_INTERFACE_ENTRY_IMPL(IPrestressingStrandPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPrestressingStrand)
//	CONNECTION_POINT_ENTRY(IID_IPrestressingStrandEvents)
END_CONNECTION_POINT_MAP()

private:
   CComBSTR m_bstrName;
   StrandGrade m_Grade;
   StrandType m_Type;
   StrandCoating m_Coating;
   StrandSize m_Size;
   StageIndexType m_InstallationStageIdx;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPrestressingStrand
public:
   STDMETHOD(get_Name)(/*[out,retval]*/ BSTR* name) override;
	STDMETHOD(put_Name)(/*[in]*/ BSTR name) override;
	STDMETHOD(get_Grade)(/*[out,retval]*/ StrandGrade* grade) override;
	STDMETHOD(put_Grade)(/*[in]*/ StrandGrade grade) override;
	STDMETHOD(get_Type)(/*[out,retval]*/ StrandType* type) override;
	STDMETHOD(put_Type)(/*[in]*/ StrandType type) override;
	STDMETHOD(get_Coating)(/*[out,retval]*/ StrandCoating* coating) override;
	STDMETHOD(put_Coating)(/*[in]*/ StrandCoating coating) override;
	STDMETHOD(get_Size)(/*[out,retval]*/ StrandSize* size) override;
	STDMETHOD(put_Size)(/*[in]*/ StrandSize size) override;
   STDMETHOD(put_InstallationStage)(StageIndexType stageIdx) override;
   STDMETHOD(get_InstallationStage)(StageIndexType* pStageIdx) override;
	STDMETHOD(get_NominalDiameter)(/*[out,retval]*/Float64* dps) override;
	STDMETHOD(get_NominalArea)(/*[out,retval]*/Float64* aps) override;
	STDMETHOD(get_UltimateStrength)(/*[out,retval]*/Float64* fpu) override;
	STDMETHOD(get_YieldStrength)(/*[out,retval]*/Float64* fpy) override;
	STDMETHOD(get_ModulusE)(/*[out,retval]*/Float64* e) override;

// IMaterial
public:
   STDMETHOD(get_E)(StageIndexType stageIdx,Float64* E) override;
	STDMETHOD(put_E)(StageIndexType stageIdx,Float64 E) override;
	STDMETHOD(get_Density)(StageIndexType stageIdx,Float64* w) override;
	STDMETHOD(put_Density)(StageIndexType stageIdx,Float64 w) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__PRESTRESSINGSTRAND_H_
