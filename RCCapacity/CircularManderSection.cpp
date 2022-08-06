///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// CircularManderSection.cpp : Implementation of CCircularManderSection
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "CircularManderSection.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircularManderSection

HRESULT CCircularManderSection::FinalConstruct()
{
   return S_OK;
}

void CCircularManderSection::FinalRelease()
{
}

STDMETHODIMP CCircularManderSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircularManderSection,
      &IID_IManderModelSection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IManderModelSection
STDMETHODIMP CCircularManderSection::put_TransvYieldStrength(Float64 fyh)
{
   m_Section->SetTransvYieldStrength(fyh);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_TransvYieldStrength(Float64* fyh)
{
   CHECK_RETVAL(fyh);
   *fyh = m_Section->GetTransvYieldStrength();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_TransvReinforcementRuptureStrain(Float64 esu)
{
   m_Section->SetTransvReinforcementRuptureStrian(esu);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_TransvReinforcementRuptureStrain(Float64* esu)
{
   CHECK_RETVAL(esu);
   *esu = m_Section->GetTransvReinforcementRuptureStrain();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_TransvReinforcementRatio(Float64* ps)
{
   CHECK_RETVAL(ps);
   *ps = m_Section->GetTransvReinforcementRatio();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_ConfinementEffectivenessCoefficient(Float64* ke)
{
   CHECK_RETVAL(ke);
   *ke = m_Section->GetConfinementEffectivenessCoefficient();
   return S_OK;
}

// ICircularManderSection
STDMETHODIMP CCircularManderSection::put_TransvReinforcementType(TransvReinforcementType trt)
{
   m_Section->SetTransvReinforcemenType((WBFL::Materials::TransvReinforcementType)trt);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_TransvReinforcementType(TransvReinforcementType* trt)
{
   CHECK_RETVAL(trt);
   *trt = (TransvReinforcementType)(m_Section->GetTransvReinforcementType());
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_Asp(Float64 asp)
{
   m_Section->SetAsp(asp);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_Asp(Float64* asp)
{
   CHECK_RETVAL(asp);
   *asp = m_Section->GetAsp();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_As(Float64 as)
{
   m_Section->SetAs(as);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_As(Float64* as)
{
   CHECK_RETVAL(as);
   *as = m_Section->GetAs();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_db(Float64 db)
{
   m_Section->Set_db(db);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_db(Float64* db)
{
   CHECK_RETVAL(db);
   *db = m_Section->Get_db();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_S(Float64 s)
{
   m_Section->SetS(s);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_S(Float64* s)
{
   CHECK_RETVAL(s);
   *s = m_Section->GetS();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_Diameter(Float64 d)
{
   m_Section->SetDiameter(d);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_Diameter(Float64* d)
{
   CHECK_RETVAL(d);
   *d = m_Section->GetDiameter();
   return S_OK;
}

STDMETHODIMP CCircularManderSection::put_Cover(Float64 c)
{
   m_Section->SetCover(c);
   return S_OK;
}

STDMETHODIMP CCircularManderSection::get_Cover(Float64* c)
{
   CHECK_RETVAL(c);
   *c = m_Section->GetCover();
   return S_OK;
}
