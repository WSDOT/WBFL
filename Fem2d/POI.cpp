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
// POI.cpp : Implementation of CPOI
#include "stdafx.h"
#include "POI.h"
#include "ModelEvents.h"


#define ON_CHANGED() ATLASSERT(m_pModel!=0); \
                               m_pModel->OnPOIChanged(this);

/////////////////////////////////////////////////////////////////////////////
// CPOI
void CPOI::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::POI* pCore)
{
   ATLASSERT(pCore!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // have to save as CModel to get at C++ event handlers
   m_pCore = pCore;
}

STDMETHODIMP CPOI::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dPOI
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPOI::get_ID(PoiIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetID();

	return S_OK;
}

STDMETHODIMP CPOI::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetMemberID();

	return S_OK;
}

STDMETHODIMP CPOI::put_MemberID(MemberIDType newVal)
{
   if (m_pCore->SetMemberID(newVal))
   {
      ON_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPOI::get_Location(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_pCore->GetLocation();

	return S_OK;
}

STDMETHODIMP CPOI::put_Location(Float64 newVal)
{
   try
   {
      if (m_pCore->SetLocation(newVal))
      {
         ON_CHANGED()
      }
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dPOI, IID_IFem2dPOI);
   }
	return S_OK;
}
