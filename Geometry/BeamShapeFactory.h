///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// BeamShapeFactory.h : Declaration of the CBeamShapeFactory

#ifndef __BEAMSHAPEFACTORY_H_
#define __BEAMSHAPEFACTORY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveFactory
class ATL_NO_VTABLE CBeamShapeFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBeamShapeFactory, &CLSID_BeamShapeFactory>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CBeamShapeFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IBeamShapeFactory
{
public:
   CBeamShapeFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BEAMSHAPEFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBeamShapeFactory)
	COM_INTERFACE_ENTRY(IBeamShapeFactory)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBeamShapeFactory
public:
	STDMETHOD(CreateShape)(/*[in]*/BeamShapeType type,/*[out]*/IShape** ppShape) override;
};

#endif //__BEAMSHAPEFACTORY_H_
