///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// ProfilePoint.h : Declaration of the CProfilePoint

#ifndef __PROFILEPOINT_H_
#define __PROFILEPOINT_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CProfilePoint
class ATL_NO_VTABLE CProfilePoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfilePoint, &CLSID_ProfilePoint>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfilePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CProfilePoint>,
	public CProxyDProfilePointEvents< CProfilePoint >,
   public IProfilePoint,
   public IStructuredStorage2,
   public IPersistImpl<CProfilePoint>
{
public:
	CProfilePoint()
	{
      m_pProfile = nullptr;
      m_Station = 0;
      m_Elevation = 0;
	}

   	HRESULT FinalConstruct();


DECLARE_REGISTRY_RESOURCEID(IDR_PROFILEPOINT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfilePoint)
	COM_INTERFACE_ENTRY(IProfilePoint)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CProfilePoint)
CONNECTION_POINT_ENTRY(IID_IProfilePointEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfilePoint
public:
   STDMETHOD(get_Profile)(IProfile* *pVal) override;
   STDMETHOD(putref_Profile)(IProfile* newVal) override;
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
	STDMETHOD(get_Station)(/*[out, retval]*/ IStation* *station) override;
	STDMETHOD(put_Station)(/*[in]*/ VARIANT varStation) override;
	STDMETHOD(get_Elevation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Elevation)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IProfilePoint* *clone) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   IProfile* m_pProfile; // weak reference
   CComPtr<IStation> m_Station;
   Float64 m_Elevation;

   HRESULT ValidateStation(IStation* station);
};

#endif //__PROFILEPOINT_H_
