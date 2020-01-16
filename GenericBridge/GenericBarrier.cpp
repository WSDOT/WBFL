///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// GenericBarrier.cpp : Implementation of CGenericBarrier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "GenericBarrier.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericBarrier
CGenericBarrier::CGenericBarrier():
m_CurbLoc(0.0),
m_InteriorToe(0.0),
m_ExteriorToe(0.0)
{
}


HRESULT CGenericBarrier::FinalConstruct()
{
   m_Material.CoCreateInstance(CLSID_Material);
   return S_OK;
}

void CGenericBarrier::FinalRelease()
{
}

STDMETHODIMP CGenericBarrier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGenericBarrier,
      &IID_IBarrier,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGenericBarrier::Clone(IBarrier** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CGenericBarrier>* pClone;
   CComObject<CGenericBarrier>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->Init(m_BarrierShape,m_CurbLoc,m_InteriorToe,m_ExteriorToe);
   (*clone)->putref_Material(m_Material);

   return S_OK;
}

STDMETHODIMP CGenericBarrier::get_Shape(IShape** shape)
{
   CHECK_RETOBJ(shape);

   m_BarrierShape.CopyTo(shape);

   return S_OK;
}

STDMETHODIMP CGenericBarrier::Init(IShape* shape, Float64 curbLoc, Float64 interiorToe, Float64 exteriorToe)
{
   m_BarrierShape.Release();
   shape->Clone(&m_BarrierShape);

   m_CurbLoc = curbLoc;
   m_InteriorToe = interiorToe;
   m_ExteriorToe = exteriorToe;

   return S_OK;
}

STDMETHODIMP CGenericBarrier::get_Material(IMaterial** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   (*material)->AddRef();
   return S_OK;
}

STDMETHODIMP CGenericBarrier::putref_Material(IMaterial* material)
{
   if ( m_Material.IsEqualObject(material) )
      return S_OK;

   m_Material = material;

   return S_OK;
}

STDMETHODIMP CGenericBarrier::get_CurbLocation(Float64* loc)
{
   CHECK_RETVAL(loc);

   *loc = m_CurbLoc;
   return S_OK;
}

STDMETHODIMP CGenericBarrier::get_BarrierToeLocations(Float64* interiorToe,Float64* exteriorToe)
{
   CHECK_RETVAL(interiorToe);
   CHECK_RETVAL(exteriorToe);

   *interiorToe = m_InteriorToe;
   *exteriorToe = m_ExteriorToe;
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CGenericBarrier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("GenericBarrier"));

#pragma Reminder("IMPLEMENT: CGenericBarrier::Load")
//   load->get_Property(CComBSTR("E"),&var);
//   m_E = var.dblVal;
//
//   load->get_Property(CComBSTR("Density"),&var);
//   m_Density = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CGenericBarrier::Save(IStructuredSave2* save)
{
#pragma Reminder("IMPLEMENT: CGenericBarrier::Save")
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("GenericBarrier"),1.0);

//   save->put_Property(CComBSTR("E"),CComVariant(m_E));
//   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));

   save->EndUnit();

   return S_OK;
}
