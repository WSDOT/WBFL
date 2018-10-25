///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// PathElement.cpp : Implementation of CPathElement
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "PathElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathElement
HRESULT CPathElement::FinalConstruct()
{
   m_Type = petPoint;

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point.QueryInterface(&m_Value);

   Advise();

   return S_OK;
}

void CPathElement::FinalRelease()
{
   Unadvise();
}

STDMETHODIMP CPathElement::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPathElement,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPathElement::get_Type(PathElementType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Type;
	return S_OK;
}

STDMETHODIMP CPathElement::get_Value(IUnknown* *pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Value;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPathElement::putref_Value(IUnknown* newVal)
{
   CHECK_IN(newVal);
   
   CComQIPtr<IPoint2d> point(newVal);
   CComQIPtr<IHorzCurve> hc(newVal);
   CComQIPtr<ILineSegment2d> ls(newVal);
   CComQIPtr<ICubicSpline> spline(newVal);

   if( point == NULL && hc == NULL && ls == NULL && spline == NULL)
      return E_INVALIDARG;

   Unadvise();

   if ( point )
      m_Type = petPoint;
   else if ( hc )
      m_Type = petHorzCurve;
   else if ( ls )
      m_Type = petLineSegment;
   else if ( spline )
      m_Type = petCubicSpline;
   else
      ATLASSERT(false); // should never get here

   m_Value = newVal;
   
   Advise();


   Fire_OnPathElementChanged(this);

	return S_OK;
}

STDMETHODIMP CPathElement::Clone(IPathElement* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CPathElement>* pClone;
   CComObject<CPathElement>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   switch( m_Type )
   {
   case petPoint:
      {
         CComQIPtr<IPoint2d> point(m_Value);
         CComPtr<IPoint2d> clonePoint;
         clonePoint.CoCreateInstance(CLSID_Point2d);
         clonePoint->MoveEx(point);

         CComQIPtr<IUnknown,&IID_IUnknown> disp(clonePoint);
         (*clone)->putref_Value(disp);
      }
      break;

   case petHorzCurve:
      {
         CComQIPtr<IHorzCurve> hc(m_Value);
         CComPtr<IHorzCurve> cloneHC;
         hc->Clone(&cloneHC);

         CComQIPtr<IUnknown,&IID_IUnknown> disp(cloneHC);
         (*clone)->putref_Value(disp);
      }
      break;

   case petLineSegment:
      {
         CComQIPtr<ILineSegment2d> ls(m_Value);
         CComPtr<ILineSegment2d> cloneLS;
         ls->Clone(&cloneLS);

         CComQIPtr<IUnknown,&IID_IUnknown> disp(cloneLS);
         (*clone)->putref_Value(disp);
      }
      break;

   case petCubicSpline:
      {
         CComQIPtr<ICubicSpline> spline(m_Value);
         CComPtr<ICubicSpline> cloneSpline;
         spline->Clone(&cloneSpline);

         CComQIPtr<IUnknown,&IID_IUnknown> disp(cloneSpline);
         (*clone)->putref_Value(disp);
      }
      break;

   default:
      ATLASSERT(false); // should never get here
      break;
   }

   return S_OK;
}

STDMETHODIMP CPathElement::Move(Float64 dist,IDirection* direction)
{
   Float64 angle;
   direction->get_Value(&angle);
   Float64 dx, dy;
   dx = dist*cos(angle);
   dy = dist*sin(angle);

   switch( m_Type )
   {
   case petPoint:
      {
         CComQIPtr<IPoint2d> point(m_Value);
         point->Offset(dx,dy);
      }
      break;

   case petHorzCurve:
      {
         CComQIPtr<IHorzCurve> hc(m_Value);
         hc->Offset(dx,dy);
      }
      break;

   case petLineSegment:
      {
         CComQIPtr<ILineSegment2d> ls(m_Value);
         ls->Offset(dx,dy);
      }
      break;
   }

   return S_OK;
}

STDMETHODIMP CPathElement::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CPathElement::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);
   pSave->BeginUnit(CComBSTR("PathElement"),1.0);
   pSave->put_Property(CComBSTR("Value"),CComVariant(m_Value));
   pSave->EndUnit();
   return S_OK;
}

STDMETHODIMP CPathElement::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PathElement"));
   pLoad->get_Property(CComBSTR("Value"),&var);
   CComPtr<IUnknown> value(var.pdispVal);
   putref_Value(value);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////////////
// Helper methods
void CPathElement::Advise()
{
   HRESULT hr;
   if ( m_Type == petPoint )
      hr = m_Value.Advise(GetUnknown(), IID_IPoint2dEvents, &m_dwCookie );
   else if ( m_Type == petLineSegment )
      hr = m_Value.Advise(GetUnknown(), IID_ILineSegment2dEvents, &m_dwCookie );
   else if ( m_Type == petHorzCurve )
      hr = m_Value.Advise(GetUnknown(), IID_IHorzCurveEvents, &m_dwCookie );
   else if ( m_Type == petCubicSpline )
      hr = m_Value.Advise(GetUnknown(), IID_ICubicSplineEvents, &m_dwCookie );
   else
      ATLASSERT(false); // should never get here


   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with PathElement object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CPathElement::Unadvise()
{
   if ( m_Value == NULL )
      return;

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection ProfilePoint and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( m_Value );
   CComPtr<IConnectionPoint> pCP;

   if ( m_Type == pePoint )
      pCPC->FindConnectionPoint( IID_IPoint2dEvents, &pCP );
   else if ( m_Type == petLineSegment )
      pCPC->FindConnectionPoint( IID_ILineSegment2dEvents, &pCP );
   else if ( m_Type == petHorzCurve )
      pCPC->FindConnectionPoint( IID_IHorzCurveEvents, &pCP );
   else if ( m_Type == petCubicSpline )
      pCPC->FindConnectionPoint( IID_ICubicSplineEvents, &pCP );
   else
      ATLASSERT(false);


   HRESULT hr = pCP->Unadvise( m_dwCookie );
   ATLASSERT(SUCCEEDED(hr));
}
