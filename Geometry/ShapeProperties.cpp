///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// ShapeProperties.cpp : Implementation of CShapeProperties
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "ShapeProperties.h"
#include "Helper.h"
#include <WBFLTools.h> // for Mohr's Circle
#include <MathEx.h>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShapeProperties


STDMETHODIMP CShapeProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IShapeProperties,
      &IID_IStructuredStorage2
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CShapeProperties::FinalConstruct()
{
   m_Area = 0.00;
   m_Ixx  = 0.00;
   m_Iyy  = 0.00;
   m_Ixy  = 0.00;

   m_CoordType = csCentroidal;
   m_Orientation = 0.00;

   m_CurrIxx = 0.00;
   m_CurrIyy = 0.00;
   m_CurrIxy = 0.00;

   CreatePoint(0.00,0.00,nullptr,&m_pCentroid);
   CreatePoint(0.00,0.00,nullptr,&m_pOrigin);
   CreatePoint(0.00,0.00,nullptr,&m_pCurrCentroid);

   m_Xleft   = 0.00;
   m_Xright  = 0.00;
   m_Ytop    = 0.00;
   m_Ybottom = 0.00;

   return S_OK;
}

void CShapeProperties::UpdateOrientation()
{
   switch (m_CoordType)
   {
   case (csCentroidal):
      {
         // in centroidal system = just copy values
         CopyPoint(m_pCurrCentroid,m_pCentroid);
         m_CurrIxx      = m_Ixx;
         m_CurrIyy      = m_Iyy;
         m_CurrIxy      = m_Ixy;
         break;
      }
   default:
      {
         // not centroidal - need to rotate into orientation
         // first rotate about centroid
         Float64 ixx, iyy, ixy;
         CComPtr<IMohrCircle> pMohrCircle;
         pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
         pMohrCircle->put_Sii( m_Ixx );
         pMohrCircle->put_Sjj( m_Iyy );
         pMohrCircle->put_Sij( m_Ixy );
         pMohrCircle->ComputeState(m_Orientation,&ixx,&iyy,&ixy);

         // next need to transform into origin coord's
         Float64 cx, cy;
         Float64 ox, oy;
         GetCoordinates(m_pCentroid,&cx,&cy);
         GetCoordinates(m_pOrigin,&ox,&oy);

         CComPtr<IPoint2d> pDelta;
         CreatePoint( cx-ox, cy-oy, nullptr, &pDelta );
         pDelta->Rotate(0.00,0.00,-m_Orientation);

         Float64 dx, dy;
         GetCoordinates(pDelta,&dx,&dy);
         
         // use parallel axis theorem to put properties into new system
         CopyPoint(m_pCurrCentroid,pDelta);
         m_CurrIxx      = ixx + m_Area * dy * dy;
         m_CurrIyy      = iyy + m_Area * dx * dx;
         m_CurrIxy      = ixy + m_Area * dx * dy;
         break;
      }
   }
}

STDMETHODIMP CShapeProperties::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Area;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Area(Float64 newVal)
{
   m_Area = newVal;
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Centroid(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint(m_pCurrCentroid,nullptr,pVal);
}

STDMETHODIMP CShapeProperties::put_Centroid(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Float64 x,y;
   newVal->get_X(&x);
   newVal->get_Y(&y);

   m_pCentroid->put_X(x);
   m_pCentroid->put_Y(y);
   
   UpdateOrientation();

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_I11(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 angle;
   Float64 ixx, iyy, ixy;
   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( m_CurrIxx );
   pMohrCircle->put_Sjj( m_CurrIyy );
   pMohrCircle->put_Sij( m_CurrIxy );
   pMohrCircle->get_PrincipleDirection( &angle );
   pMohrCircle->ComputeState(angle,&ixx,&iyy,&ixy);

   *pVal = ixx;
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_I22(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 angle;
   Float64 ixx, iyy, ixy;
   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( m_CurrIxx );
   pMohrCircle->put_Sjj( m_CurrIyy );
   pMohrCircle->put_Sij( m_CurrIxy );
   pMohrCircle->get_PrincipleDirection( &angle );
   pMohrCircle->ComputeState(angle,&ixx,&iyy,&ixy);

   *pVal = iyy;
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_I12Max(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( m_CurrIxx );
   pMohrCircle->put_Sjj( m_CurrIyy );
   pMohrCircle->put_Sij( m_CurrIxy );
   pMohrCircle->get_Tmax( pVal );

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_I12Min(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   Float64 val;
   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( m_CurrIxx );
   pMohrCircle->put_Sjj( m_CurrIyy );
   pMohrCircle->put_Sij( m_CurrIxy );
   pMohrCircle->get_Tmax( &val );
   *pVal = -val;

	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ixx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_CurrIxx;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ixx(Float64 newVal)
{
   m_Ixx = newVal;
   UpdateOrientation();
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Iyy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_CurrIyy;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Iyy(Float64 newVal)
{
   m_Iyy = newVal;
   UpdateOrientation();
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ixy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_CurrIxy;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ixy(Float64 newVal)
{
   m_Ixy = newVal;
   UpdateOrientation();
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_Xleft(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Xleft;
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Xleft(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Xleft = newVal;
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Xright(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Xright;
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Xright(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Xright = newVal;
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ytop(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Ytop;
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ytop(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Ytop = newVal;
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Ybottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Ybottom;
   return S_OK;
}

STDMETHODIMP CShapeProperties::put_Ybottom(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Ybottom = newVal;
   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Origin(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint( m_pOrigin, nullptr, pVal );
}

STDMETHODIMP CShapeProperties::put_Origin(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Float64 x,y;
   newVal->get_X(&x);
   newVal->get_Y(&y);

   m_pOrigin->Move(x,y);

   m_CoordType = csUser;
   UpdateOrientation();

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_Orientation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Orientation;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_Orientation(Float64 newVal)
{
   m_Orientation = newVal;
   m_CoordType = csUser;
   UpdateOrientation();
	return S_OK;
}

STDMETHODIMP CShapeProperties::get_CoordinateSystem(CoordinateSystemType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_CoordType;
	return S_OK;
}

STDMETHODIMP CShapeProperties::put_CoordinateSystem(CoordinateSystemType newVal)
{
   if ( m_CoordType == newVal )
      return S_OK; // Nothing is changing, so why do the work.

   switch(newVal)
   {
      case csCentroidal:
      {
         m_CoordType = newVal;
         CopyPoint(m_pOrigin,m_pCentroid); // from centroid to origin
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case csGlobal:
      {
         m_CoordType = newVal;
         m_pOrigin->put_X(0.00);
         m_pOrigin->put_Y(0.00);
         m_Orientation = 0;
         UpdateOrientation();
         break;
      }
      case csPrinciple:
      {
         // first have to get principal orientation angle
         put_CoordinateSystem(csCentroidal);
         get_PrincipleDirection( &m_Orientation );
         m_CoordType = newVal;
         UpdateOrientation();
         break;
      }
      case csUser:
      {
         m_CoordType = newVal;
         UpdateOrientation();
         break;
      }
      default:
         ATLASSERT(false); // Bad coordinate system type
   }

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_PrincipleDirection(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IMohrCircle> pMohrCircle;
   pMohrCircle.CoCreateInstance( CLSID_MohrCircle );
   pMohrCircle->put_Sii( m_CurrIxx );
   pMohrCircle->put_Sjj( m_CurrIyy );
   pMohrCircle->put_Sij( m_CurrIxy );
   pMohrCircle->get_PrincipleDirection( pVal );
   return S_OK;
}

/////////////////////////////////////////////////////
// IShapePropertiesEx
STDMETHODIMP CShapeProperties::AddProperties(IShapeProperties* props)
{
   CHECK_IN(props);

   // Keep the current coordinate system so we can make sure
   // we put things back there way they were when we started
   CoordinateSystemType currCoordinateSystem = m_CoordType;

   // Transform both this and the incoming properties to global coordinates
   put_CoordinateSystem(csGlobal);
   props->put_CoordinateSystem(csGlobal);

   // Get basic section properties
   Float64 area1;
   Float64 ixx1, iyy1, ixy1;
   Float64 area2;
   Float64 ixx2, iyy2, ixy2;

   get_Area(&area1);
   get_Ixx(&ixx1);
   get_Iyy(&iyy1);
   get_Ixy(&ixy1);

   props->get_Area(&area2);
   props->get_Ixx(&ixx2);
   props->get_Iyy(&iyy2);
   props->get_Ixy(&ixy2);

   // Update the centroid
   Float64 cx1,cy1;
   Float64 cx2,cy2;
   m_pCentroid->get_X(&cx1);
   m_pCentroid->get_Y(&cy1);
   
   CComPtr<IPoint2d> cg2;
   props->get_Centroid(&cg2);
   cg2->get_X(&cx2);
   cg2->get_Y(&cy2);

   Float64 AX = area1*cy1 + area2*cy2;
   Float64 AY = area1*cx1 + area2*cx2;

   Float64 A = area1 + area2;
   Float64 cgx = 0;
   Float64 cgy = 0;
   if ( !IsZero(A) )
   {
      cgx = AY/A;
      cgy = AX/A;
   }

   //
   // Update the distance from the edges to the centroid
   Float64 l2,r2,t2,b2;
   props->get_Xleft(&l2);
   props->get_Xright(&r2);
   props->get_Ytop(&t2);
   props->get_Ybottom(&b2);

   Float64 l,r,t,b; // distance from the global axes to the extreme edges
   l = Min(cx1-m_Xleft,cx2-l2);
   r = Max(cx1+m_Xright,cx2+r2);
   t = Max(cy1+m_Ytop,cy2+t2);
   b = Min(cy1-m_Ybottom,cy2-b2);

   Float64 xleft, xright, ytop, ybottom;
   xleft   = cgx - l;
   xright  = r - cgx;
   ytop    = t - cgy;
   ybottom = cgy - b;

   // Update section properties
   Float64 IXX, IYY, IXY;
   IXX = ixx1 + ixx2;
   IYY = iyy1 + iyy2;
   IXY = ixy1 + ixy2;

   // Assign these properties in global coordinates back to this object
   // Do it via the main interface so things don't get messed up
   m_Area = A;
   m_Ixx = IXX - A*cgy*cgy;
   m_Iyy = IYY - A*cgx*cgx;
   m_Ixy = IXY - A*cgx*cgy;
   m_Xleft   = xleft;
   m_Xright  = xright;
   m_Ytop    = ytop;
   m_Ybottom = ybottom;
   m_pCentroid->Move(cgx,cgy);
   m_pOrigin->Move(0,0);

   // Transform properties back to original coordinate system
   put_CoordinateSystem(currCoordinateSystem);

   return S_OK;
}

STDMETHODIMP CShapeProperties::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CShapeProperties::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CShapeProperties::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("ShapeProperties"),1.0);
   pSave->put_Property(CComBSTR("Area"),CComVariant(m_Area));
   pSave->put_Property(CComBSTR("Ixx"),CComVariant(m_Ixx));
   pSave->put_Property(CComBSTR("Ixy"),CComVariant(m_Ixy));
   pSave->put_Property(CComBSTR("Iyy"),CComVariant(m_Iyy));
   pSave->put_Property(CComBSTR("Centroid"),CComVariant(m_pCentroid));
   pSave->put_Property(CComBSTR("Xleft"),CComVariant(m_Xleft));
   pSave->put_Property(CComBSTR("Xright"),CComVariant(m_Xright));
   pSave->put_Property(CComBSTR("Ytop"),CComVariant(m_Ytop));
   pSave->put_Property(CComBSTR("Ybottom"),CComVariant(m_Ybottom));
   pSave->put_Property(CComBSTR("CurrIxx"),CComVariant(m_CurrIxx));
   pSave->put_Property(CComBSTR("CurrIxy"),CComVariant(m_CurrIxy));
   pSave->put_Property(CComBSTR("CurrIyy"),CComVariant(m_CurrIyy));
   pSave->put_Property(CComBSTR("CurrCentroid"),CComVariant(m_pCurrCentroid));
   pSave->put_Property(CComBSTR("Orientation"),CComVariant(m_Orientation));
   pSave->put_Property(CComBSTR("CoordSysType"),CComVariant(m_CoordType));
   pSave->put_Property(CComBSTR("Origin"),CComVariant(m_pOrigin));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CShapeProperties::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("ShapeProperties"));
   
   pLoad->get_Property(CComBSTR("Area"),&var);
   m_Area = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Ixx"),&var);
   m_Ixx = var.dblVal;

   pLoad->get_Property(CComBSTR("Ixy"),&var);
   m_Ixy = var.dblVal;

   pLoad->get_Property(CComBSTR("Iyy"),&var);
   m_Iyy = var.dblVal;

   pLoad->get_Property(CComBSTR("Centroid"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pCentroid,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   pLoad->get_Property(CComBSTR("Xleft"),&var);
   m_Xleft = var.dblVal;

   pLoad->get_Property(CComBSTR("Xright"),&var);
   m_Xright = var.dblVal;

   pLoad->get_Property(CComBSTR("Ytop"),&var);
   m_Ytop = var.dblVal;

   pLoad->get_Property(CComBSTR("Ybottom"),&var);
   m_Ybottom = var.dblVal;

   pLoad->get_Property(CComBSTR("CurrIxx"),&var);
   m_CurrIxx = var.dblVal;

   pLoad->get_Property(CComBSTR("CurrIxy"),&var);
   m_CurrIxy = var.dblVal;

   pLoad->get_Property(CComBSTR("CurrIyy"),&var);
   m_CurrIyy = var.dblVal;

   pLoad->get_Property(CComBSTR("CurrCentroid"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pCurrCentroid,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   pLoad->get_Property(CComBSTR("Orientation"), &var);
   m_Orientation = var.dblVal;

   pLoad->get_Property(CComBSTR("CoordSysType"),&var);
   m_CoordType = (CoordinateSystemType)var.iVal;

   pLoad->get_Property(CComBSTR("Origin"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pOrigin,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
