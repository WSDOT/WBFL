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

// RCBeam.h : Declaration of the CRCBeam

#ifndef __RCBEAM_H_
#define __RCBEAM_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <WBFLTools.h>

/////////////////////////////////////////////////////////////////////////////
// CRCBeam
class ATL_NO_VTABLE CRCBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRCBeam, &CLSID_RCBeam>,
	public ISupportErrorInfo,
	public IRCBeam,
	public ISupportUnitServer,
   public IStructuredStorage2
{
public:
	CRCBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_RCBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRCBeam)
	COM_INTERFACE_ENTRY(IRCBeam)
	COM_INTERFACE_ENTRY(ISupportUnitServer)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   Float64 m_FcBeam;
   Float64 m_FcSlab;
   Float64 m_Fpy;
   Float64 m_Fpu;
   Float64 m_Fy;
   Float64 m_Aps;
   Float64 m_As;
   Float64 m_hf;
   Float64 m_h;
   Float64 m_b;
   Float64 m_bw;
   Float64 m_ds;
   Float64 m_dps;
   Float64 m_Fpe;
   Float64 m_Es;
   Float64 m_Eps;

   CComPtr<IUnitServer> m_UnitServer;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRCBeam
public:
	STDMETHOD(get_Es)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Es)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Eps)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Eps)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_h)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_h)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fpe)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fpe)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_dps)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_dps)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_ds)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_ds)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_FcBeam)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_FcBeam)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_FcSlab)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_FcSlab)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fpy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fpy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fpu)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fpu)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Aps)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Aps)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_fy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_fy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_As)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_As)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_hf)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_hf)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_bw)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_bw)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_b)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_b)(/*[in]*/ Float64 newVal);

// ISupportUnitServer
public:
		STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal );
		STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal );

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__RCBEAM_H_
