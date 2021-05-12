///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2021  Washington State Department of Transportation
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

// Direction.h : Declaration of the CDirection

#ifndef __DIRECTION_H_
#define __DIRECTION_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirection
class ATL_NO_VTABLE CDirection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDirection, &CLSID_Direction>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CDirection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IDirection,
   public IStructuredStorage2,
   public IPersistImpl<CDirection>
{
public:
	CDirection()
	{
      m_Direction = 0.0; // Due East
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIRECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDirection)
	COM_INTERFACE_ENTRY(IDirection)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDirection
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
   STDMETHOD(IsEqual)(IDirection* pDirection) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IDirection* *clone) override;
	STDMETHOD(AngleBetween)(/*[in]*/ IDirection* dir,/*[out,retval]*/IAngle** pVal) override;
   STDMETHOD(FromVariant)(/*[in]*/ VARIANT varDirection) override;
   STDMETHOD(FromAzimuth)(/*[in]*/ Float64 azimuth) override;
	STDMETHOD(FromAzimuthEx)(/*[in]*/ long Degree, /*[in]*/ long Minute, /*[in]*/ Float64 Second) override;
	STDMETHOD(FromDMS)(/*[in]*/ NSDirectionType ns,/*[in]*/ long Degree,/*[in]*/ long Minute, /*[in]*/ Float64 Second, /*[in]*/ EWDirectionType ew) override;
	STDMETHOD(FromString)(/*[in]*/ BSTR bstrDir) override;
	STDMETHOD(IncrementBy)(/*[in]*/ VARIANT varAngle) override;
	STDMETHOD(Increment)(/*[in]*/ VARIANT varAngle,/*[out,retval]*/ IDirection* *pVal) override;
	STDMETHOD(get_Second)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Second)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Minute)(/*[out, retval]*/ long *pVal) override;
	STDMETHOD(put_Minute)(/*[in]*/ long newVal) override;
	STDMETHOD(get_Degree)(/*[out, retval]*/ long *pVal) override;
	STDMETHOD(put_Degree)(/*[in]*/ long newVal) override;
	STDMETHOD(get_EWDirection)(/*[out, retval]*/ EWDirectionType *pVal) override;
	STDMETHOD(put_EWDirection)(/*[in]*/ EWDirectionType newVal) override;
	STDMETHOD(get_NSDirection)(/*[out, retval]*/ NSDirectionType *pVal) override;
	STDMETHOD(put_NSDirection)(/*[in]*/ NSDirectionType newVal) override;
	STDMETHOD(get_Value)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Value)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_Azimuth)(/*[out, retval]*/ Float64 *pVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

private:
   HRESULT BadDirectionString();
   HRESULT BadAzimuth();
   HRESULT BadDirection();

	HRESULT UpdateDirection(NSDirectionType nsDir,long deg,long min,Float64 sec,EWDirectionType ewDir);
	Float64 m_Direction;
};

#endif //__DIRECTION_H_
