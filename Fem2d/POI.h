///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;

/////////////////////////////////////////////////////////////////////////////
// CPOI
// Thin COM facade over WBFL::FEA2D::POI.
class ATL_NO_VTABLE CPOI :
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPOI,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dPOI
{
public:
   CPOI():
   m_pModel(0),
   m_pCore(0)
	{
	}

   virtual ~CPOI()
   {}


   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator. The core POI
   // must already exist (location validation happens in Model::CreatePOI).
   void OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::POI* pCore);

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
   ModelEvents* m_pModel; // for sending events back to model
   WBFL::FEA2D::POI* m_pCore; // non-owning; owned by the FEA2D core Model

};

