///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#ifndef INCLUDED_COMPOUNDDRAWEPOINTSTRATEGYIMPL_H_
#define INCLUDED_COMPOUNDDRAWEPOINTSTRATEGYIMPL_H_
// CompoundDrawPointStrategyImpl.h: interface for the CCompoundDrawPointStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CCompoundDrawPointStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompoundDrawPointStrategyImpl, &CLSID_CompoundDrawPointStrategy>,
   public iCompoundDrawPointStrategy
{
public:
	CCompoundDrawPointStrategyImpl();
	virtual ~CCompoundDrawPointStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOUNDDRAWPOINTSTRATEGY)

BEGIN_COM_MAP(CCompoundDrawPointStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawPointStrategy)
   COM_INTERFACE_ENTRY(iCompoundDrawPointStrategy)
END_COM_MAP()

// iPointDrawStrategy
public:
   STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC) override;
   STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint) override;
   STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite) override;
   STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO,IRect2d** box) override;

// iCompoundPointDrawStrategy
public:
   STDMETHOD_(void,AddStrategy)(iDrawPointStrategy* pStrategy) override;
   STDMETHOD_(void,RemoveStrategy)(IndexType index) override;
   STDMETHOD_(void, GetStrategy)(IndexType index, iDrawPointStrategy** ppStrategy) override;
   STDMETHOD_(IndexType,Count)() override;

private:
   using Strategies = std::vector<CComPtr<iDrawPointStrategy>>;
   Strategies m_Strategies;
};

#endif // INCLUDED_COMPOUNDDRAWPOINTSTRATEGYIMPL_H_