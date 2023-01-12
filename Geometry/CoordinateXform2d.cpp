///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// CoordinateXform2d.cpp : Implementation of CCoordinateXform2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CoordinateXform2d.h"
#include "Helper.h"
#include "Point2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoordinateXform2d

HRESULT CCoordinateXform2d::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICoordinateXform2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCoordinateXform2d::get_NewOrigin(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Xform.GetNewOrigin(), pVal);
}

STDMETHODIMP CCoordinateXform2d::put_NewOrigin(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_Xform.SetNewOrigin(GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::get_RotationAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Xform.GetRotationAngle();
   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::put_RotationAngle(Float64 newVal)
{
   m_Xform.SetRotationAngle(newVal);
   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::Xform(IPoint2d** point,XformType type)
{
   CHECK_INOUT(point);

   WBFL::Geometry::Point2d p;
   (*point)->Location(&p.X(), &p.Y());
    m_Xform.Xform(p, type == xfrmOldToNew ? WBFL::Geometry::CoordinateXform2d::Type::OldToNew : WBFL::Geometry::CoordinateXform2d::Type::NewToOld);
   (*point)->Move(p.X(), p.Y());

   return S_OK;
}

STDMETHODIMP CCoordinateXform2d::XformEx(IPoint2d* point, XformType type, IPoint2d** result)
{
   CHECK_IN(point);
   CHECK_RETOBJ(result);
   CreatePoint(point,result);
   return Xform(result,type);
}
