///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// FShapeBarrier.cpp : Implementation of CFShapeBarrier
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "FShapeBarrier.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFShapeBarrier
HRESULT CFShapeBarrier::FinalConstruct()
{
   m_Material.CoCreateInstance(CLSID_Material);
   return S_OK;
}

void CFShapeBarrier::FinalRelease()
{
}

STDMETHODIMP CFShapeBarrier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFShapeBarrier,
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


STDMETHODIMP CFShapeBarrier::Clone(IBarrier** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CFShapeBarrier>* pClone;
   CComObject<CFShapeBarrier>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->put_Shape(m_BarrierShape);
   (*clone)->putref_Material(m_Material);

   return S_OK;
}

STDMETHODIMP CFShapeBarrier::get_Shape(IShape** shape)
{
   CHECK_RETOBJ(shape);

   CComQIPtr<IShape> s(m_BarrierShape);
   s->Clone(shape);

   return S_OK;
}

STDMETHODIMP CFShapeBarrier::put_Shape(ITrafficBarrier* barrier)
{
   if ( m_BarrierShape.IsEqualObject(barrier) )
      return S_OK;

   m_BarrierShape.Release();
   CComQIPtr<IShape> shape(barrier);
   CComPtr<IShape> clone_shape;
   shape->Clone(&clone_shape);
   clone_shape.QueryInterface(&(m_BarrierShape));

   return S_OK;
}

STDMETHODIMP CFShapeBarrier::get_Material(IMaterial** material)
{
   CHECK_RETOBJ(material);
   (*material) = m_Material;
   (*material)->AddRef();
   return S_OK;
}

STDMETHODIMP CFShapeBarrier::putref_Material(IMaterial* material)
{
   CHECK_IN(material);
   m_Material = material;
   return S_OK;
}

STDMETHODIMP CFShapeBarrier::get_CurbLocation(Float64* width)
{
   CHECK_RETVAL(width);

   *width = 0;
   return S_OK;
}

STDMETHODIMP CFShapeBarrier::get_BarrierToeLocations(Float64* interiorToe,Float64* exteriorToe)
{
   CHECK_RETVAL(interiorToe);
   CHECK_RETVAL(exteriorToe);

   if ( m_BarrierShape == nullptr )
   {
      *interiorToe = 0.0;
      *exteriorToe = 0.0;
      return S_OK;
   }

   m_BarrierShape->get_X1(exteriorToe);
   m_BarrierShape->get_X2(interiorToe);
   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CFShapeBarrier::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("FShapeBarrier"));

#pragma Reminder("IMPLEMENT: CFShapeBarrier::Load")
//   load->get_Property(CComBSTR("E"),&var);
//   m_E = var.dblVal;
//
//   load->get_Property(CComBSTR("Density"),&var);
//   m_Density = var.dblVal;

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CFShapeBarrier::Save(IStructuredSave2* save)
{
#pragma Reminder("IMPLEMENT: CFShapeBarrier::Save")
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("FShapeBarrier"),1.0);

//   save->put_Property(CComBSTR("E"),CComVariant(m_E));
//   save->put_Property(CComBSTR("Density"),CComVariant(m_Density));

   save->EndUnit();

   return S_OK;
}
