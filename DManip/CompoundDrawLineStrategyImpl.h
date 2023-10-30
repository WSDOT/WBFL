///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

#ifndef INCLUDED_COMPOUNDDRAWELINESTRATEGYIMPL_H_
#define INCLUDED_COMPOUNDDRAWELINESTRATEGYIMPL_H_
// CompoundDrawLineStrategyImpl.h: interface for the CCompoundDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CCompoundDrawLineStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompoundDrawLineStrategyImpl, &CLSID_CompoundDrawLineStrategy>,
   public iCompoundDrawLineStrategy
{
public:
	CCompoundDrawLineStrategyImpl();
	virtual ~CCompoundDrawLineStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOUNDDRAWLINESTRATEGY)

BEGIN_COM_MAP(CCompoundDrawLineStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawLineStrategy)
   COM_INTERFACE_ENTRY(iCompoundDrawLineStrategy)
END_COM_MAP()

// iLineDrawStrategy
public:
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC) override;
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint) override;
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite) override;
   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box) override;

// iCompoundLineDrawStrategy
public:
   STDMETHOD_(void,AddStrategy)(iDrawLineStrategy* pStrategy) override;
   STDMETHOD_(void,RemoveStrategy)(IndexType index) override;
   STDMETHOD_(void, GetStrategy)(IndexType index, iDrawLineStrategy** ppStrategy) override;
   STDMETHOD_(IndexType,Count)() override;

private:
   using Strategies = std::vector<CComPtr<iDrawLineStrategy>>;
   Strategies m_Strategies;
};

#endif // INCLUDED_COMPOUNDDRAWELINESTRATEGYIMPL_H_