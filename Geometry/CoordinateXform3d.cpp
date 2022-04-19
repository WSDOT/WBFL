///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// CoordinateXform3d.cpp : Implementation of CCoordinateXform3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CoordinateXform3d.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// REFERENCES
// HP-41 Advantage Advanced Solutions Pac
// Hewlett Packard, July 1985
// pp 117-125

/////////////////////////////////////////////////////////////////////////////
// CCoordinateXform3d
HRESULT CCoordinateXform3d::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICoordinateXform3d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCoordinateXform3d::get_NewOrigin(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Xform.GetNewOrigin(), pVal);
}

STDMETHODIMP CCoordinateXform3d::put_NewOrigin(IPoint3d *newVal)
{
   CHECK_IN(newVal);
   m_Xform.SetNewOrigin(GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::get_RotationAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Xform.GetRotationAngle();
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::put_RotationAngle(Float64 newVal)
{
   m_Xform.SetRotationAngle(newVal);
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::get_RotationVector(IVector3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreateVector(m_Xform.GetRotationVector(), pVal);
}

STDMETHODIMP CCoordinateXform3d::put_RotationVector(IVector3d *newVal)
{
   CHECK_IN(newVal);
   try 
   {
      m_Xform.SetRotationVector(GetVector(newVal));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_ICoordinateXform3d, GEOMETRY_E_ZEROMAGNITUDE);
   }  
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::Xform(IPoint3d** point, XformType type)
{
   CHECK_INOUT(point);

   WBFL::Geometry::Point3d p;
   (*point)->Location(&p.X(), &p.Y(), &p.Z());
   try
   {
      m_Xform.Xform(p, type == xfrmOldToNew ? WBFL::Geometry::CoordinateXform3d::Type::OldToNew : WBFL::Geometry::CoordinateXform3d::Type::NewToOld);
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_ICoordinateXform3d, GEOMETRY_E_ZEROMAGNITUDE);
   }
   (*point)->Move(p.X(), p.Y(), p.Z());
   return S_OK;
}

STDMETHODIMP CCoordinateXform3d::XformEx(IPoint3d* point, XformType type, IPoint3d** result)
{
   CHECK_IN(point);
   CHECK_RETOBJ(result);

   CreatePoint(point,result);
   return Xform(result,type);
}
