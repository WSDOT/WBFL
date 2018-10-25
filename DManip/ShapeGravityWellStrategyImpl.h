///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2012  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ShapeGravityWellStrategyImpl.h: interface for the CShapeGravityWellStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEGRAVITYWELLSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_SHAPEGRAVITYWELLSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CShapeGravityWellStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShapeGravityWellStrategyImpl, &CLSID_ShapeGravityWellStrategy>,
   public iShapeGravityWellStrategy
{
public:
	CShapeGravityWellStrategyImpl();
	virtual ~CShapeGravityWellStrategyImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SHAPEGRAVITYWELLSTRATEGY)

BEGIN_COM_MAP(CShapeGravityWellStrategyImpl)
   COM_INTERFACE_ENTRY(iGravityWellStrategy)
   COM_INTERFACE_ENTRY(iShapeGravityWellStrategy)
END_COM_MAP()

   // iGravityWellStrategy Implementation
   STDMETHOD_(void,GetGravityWell)(iDisplayObject* pDO,CRgn* pRgn);

   // iShapeGravityWellStrategy Implementation
   STDMETHOD_(void,SetShape)(IShape* pShape);
   STDMETHOD_(void,GetShape)(IShape** ppShape);

private:
   CComPtr<IShape> m_Shape;
   CComPtr<ICompositeShape> m_CompositeShape;
};

#endif // !defined(AFX_SHAPEGRAVITYWELLSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
