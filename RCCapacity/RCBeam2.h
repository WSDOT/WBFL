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

// RCBeam2.h : Declaration of the CRCBeam2

#ifndef __RCBEAM2_H_
#define __RCBEAM2_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CRCBeam2
class ATL_NO_VTABLE CRCBeam2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRCBeam2, &CLSID_RCBeam2>,
	public ISupportErrorInfo,
	public IRCBeam2,
	public ISupportUnitServer,
   public IStructuredStorage2
{
public:
	CRCBeam2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_RCBEAM2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRCBeam2)
	COM_INTERFACE_ENTRY(IRCBeam2)
	COM_INTERFACE_ENTRY(ISupportUnitServer)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   struct Reinforcement
   {
      Reinforcement(Float64 _ds,Float64 _As,Float64 _devFactor)
      { ds = _ds; As = _As; DevFactor = _devFactor; }

      Float64 ds;
      Float64 As;
      Float64 DevFactor;
   };

   Float64 m_FcBeam;
   Float64 m_FcSlab;
   Float64 m_Fpy;
   Float64 m_Fpu;
   Float64 m_Fy;
   Float64 m_hf;
   Float64 m_h;
   Float64 m_b;
   Float64 m_bw;
   Float64 m_Fpe;
   Float64 m_Es;
   Float64 m_Eps;
   std::vector<Reinforcement> m_Rebar;
   std::vector<Reinforcement> m_Strands;

   CComPtr<IUnitServer> m_UnitServer;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRCBeam2
public:
	STDMETHOD(get_Es)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Es)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Eps)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Eps)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_h)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_h)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fpe)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fpe)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_FcBeam)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_FcBeam)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_FcSlab)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_FcSlab)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fpy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fpy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fpu)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fpu)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_hf)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_hf)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_bw)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_bw)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_b)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_b)(/*[in]*/ Float64 newVal) override;

   STDMETHOD(AddRebarLayer)(/*[in]*/ Float64 ds,/*[in]*/ Float64 As,/*[in]*/ Float64 devFactor) override;
   STDMETHOD(get_RebarLayerCount)(/*[out,retval]*/ IndexType * count) override;
   STDMETHOD(get_RebarLayerDepth)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * ds) override;
   STDMETHOD(get_RebarLayerSteel)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * As) override;
   STDMETHOD(get_RebarLayerDevFactor)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * devFactor) override;
   STDMETHOD(GetRebarLayer)(/*[in]*/ IndexType index,/*[out]*/ Float64 * ds, /*[out]*/ Float64 * As, /*[out]*/ Float64 * devFactor) override;
   STDMETHOD(RemoveRebarLayer)(/*[in]*/ IndexType index) override;
   STDMETHOD(ClearRebarLayers)() override;

   STDMETHOD(AddStrandLayer)(/*[in]*/ Float64 dps,/*[in]*/ Float64 Aps,/*[in]*/ Float64 devFactor) override;
   STDMETHOD(get_StrandLayerCount)(/*[out,retval]*/ IndexType * count) override;
   STDMETHOD(get_StrandLayerDepth)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * dps) override;
   STDMETHOD(get_StrandLayerSteel)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * Aps) override;
   STDMETHOD(get_StrandLayerDevFactor)(/*[in]*/ IndexType index,/*[out,retval]*/ Float64 * devFactor) override;
   STDMETHOD(GetStrandLayer)(/*[in]*/ IndexType index,/*[out]*/ Float64 * dps, /*[out]*/ Float64 * Aps, /*[out]*/ Float64 * devFactor) override;
   STDMETHOD(RemoveStrandLayer)(/*[in]*/ IndexType index) override;
   STDMETHOD(ClearStrandLayers)() override;

// ISupportUnitServer
public:
		STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal ) override;
		STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal ) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__RCBEAM2_H_
