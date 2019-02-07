///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2019  Washington State Department of Transportation
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

// Rebar.h : Declaration of the CRebar

#ifndef __Rebar_H_
#define __Rebar_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CRebar
class ATL_NO_VTABLE CRebar : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebar,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebar, &CLSID_Rebar>,
	public ISupportErrorInfo,
	public IRebar,
   public IMaterial,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CRebar,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebar()
	{
      m_Name = "NoName";
      m_E = 0;
      m_Density = 0;
      m_fpu = 0;
      m_fpy = 0;
      m_db = 0;
      m_Ab = 0;

      m_InstallationStageIdx = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_REBAR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebar)
	COM_INTERFACE_ENTRY(IRebar)
	COM_INTERFACE_ENTRY(IMaterial)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   static HRESULT PutE(CRebar* pThis,Float64 E);
   static HRESULT PutDensity(CRebar* pThis,Float64 w);
   static HRESULT PutName(CRebar* pThis,BSTR name);
   static HRESULT PutUltimateStrength(CRebar* pThis,Float64 fpu);
   static HRESULT PutYieldStrength(CRebar* pThis,Float64 fpy);
   static HRESULT PutNominalDiameter(CRebar* pThis,Float64 db);
   static HRESULT PutNominalArea(CRebar* pThis,Float64 Ab);

   Float64 m_E;
   Float64 m_Density;
   CComBSTR m_Name;
   Float64 m_fpu;
   Float64 m_fpy;
   Float64 m_db;
   Float64 m_Ab;
   StageIndexType m_InstallationStageIdx;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRebar
public:
	STDMETHOD(Clone)(/*[out,retval]*/IRebar** clone) override;
   STDMETHOD(Init)(/*[in]*/ BSTR name,/*[in]*/ Float64 Es,/*[in]*/ Float64 density,/*[in]*/ Float64 fpu,/*[in]*/ Float64 fpy,/*[in]*/ Float64 db,/*[in]*/ Float64 Ab,/*[in]*/ StageIndexType stageIdx) override;
   STDMETHOD(get_Name)(/*[out,retval]*/ BSTR* name) override;
   STDMETHOD(put_Name)(/*[in]*/ BSTR name) override;
   STDMETHOD(get_UltimateStrength)(/*[out,retval]*/ Float64* fpu) override;
	STDMETHOD(put_UltimateStrength)(/*[in]*/ Float64 fpu) override;
	STDMETHOD(get_YieldStrength)(/*[out,retval]*/ Float64* fpy) override;
   STDMETHOD(put_YieldStrength)(/*[in]*/ Float64 fpy) override;
	STDMETHOD(get_NominalDiameter)(/*[out,retval]*/ Float64* db) override;
	STDMETHOD(put_NominalDiameter)(/*[in]*/ Float64 db) override;
   STDMETHOD(get_NominalArea)(/*[out,retval]*/ Float64* Ab) override;
	STDMETHOD(put_NominalArea)(/*[in]*/ Float64 Ab) override;
   STDMETHOD(get_InstallationStage)(/*[out,retval]*/ StageIndexType* pStageIdx) override;
	STDMETHOD(put_InstallationStage)(/*[in]*/ StageIndexType stageIdx) override;

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

#endif //__Rebar_H_
