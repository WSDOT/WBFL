///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2018  Washington State Department of Transportation
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

// POI.h : Declaration of the CPOI

#ifndef __POI_H_
#define __POI_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;

/////////////////////////////////////////////////////////////////////////////
// CPOI
class ATL_NO_VTABLE CPOI : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPOI,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dPOI
{
public:
   CPOI():
   m_ID(0),
   m_MemberID(0),
   m_Location(0.0)
	{
	}

   virtual ~CPOI()
   {}


   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator.
   HRESULT OnCreate(IFem2dModel* pModel, ModelEvents* pEvents, PoiIDType ID, MemberIDType memberID=-1, Float64 location=0.0);

   // IStructuredStorage - sort of
   HRESULT Load(IStructuredLoad2 *load);
   HRESULT Save(IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOI)
	COM_INTERFACE_ENTRY(IFem2dPOI)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dPOI
public:
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Location)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ PoiIDType *pVal) override;

private:
   PoiIDType m_ID;
   MemberIDType m_MemberID;
   Float64 m_Location;

   ModelEvents* m_pModel; // for sending events back to model

};

#endif //__POI_H_
