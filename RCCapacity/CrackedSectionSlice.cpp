///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// CrackedSectionSlice.cpp : Implementation of CCrackedSectionSlice
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "CrackedSectionSlice.h"


/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSlice
HRESULT CCrackedSectionSlice::FinalConstruct()
{
   return S_OK;
}

void CCrackedSectionSlice::FinalRelease()
{
}


STDMETHODIMP CCrackedSectionSlice::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrackedSectionSlice,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// ICrackedSectionSlice
STDMETHODIMP CCrackedSectionSlice::InitSlice(IShape* pShape,Float64 A,Float64 cgX,Float64 cgY,Float64 Efg,Float64 Ebg)
{
   m_Shape = pShape;
   m_Area = A;
   m_cgX = cgX;
   m_cgY = cgY;
   m_Efg = Efg;
   m_Ebg = Ebg;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSlice::get_Area(Float64* pArea)
{
   CHECK_RETVAL(pArea);
   *pArea = m_Area;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSlice::get_CG(IPoint2d** pCG)
{
   CHECK_RETOBJ(pCG);
   CComPtr<IPoint2d> cg;
   cg.CoCreateInstance(CLSID_Point2d);
   cg->Move(m_cgX,m_cgY);
   (*pCG) = cg;
   (*pCG)->AddRef();
   return S_OK;
}

STDMETHODIMP CCrackedSectionSlice::get_Efg(Float64* pEfg)
{
   CHECK_RETVAL(pEfg);
   *pEfg = m_Efg;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSlice::get_Ebg(Float64* pEbg)
{
   CHECK_RETVAL(pEbg);
   *pEbg = m_Ebg;
   return S_OK;
}

STDMETHODIMP CCrackedSectionSlice::get_Shape(IShape** pShape)
{
   CHECK_RETOBJ(pShape);
   (*pShape) = m_Shape;
   (*pShape)->AddRef();
   return S_OK;
}
