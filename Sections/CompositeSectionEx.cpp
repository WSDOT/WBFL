///////////////////////////////////////////////////////////////////////
// Sections - Model bridge member cross sections
// Copyright © 1999-2019  Washington State Department of Transportation
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

// CompositeSectionEx.cpp : Implementation of CCompositeSectionEx
#include "stdafx.h"
#include "WBFLSections.h"
#include "CompositeSectionEx.h"
#include "CompositeSectionItemEx.h"
#include "ElasticProperties.h"
#include "MassProperties.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeSectionEx

STDMETHODIMP CCompositeSectionEx::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeSectionEx,
      &IID_ISection,
      &IID_IXYPosition,
		&IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeSectionEx::AddSectionEx(ICompositeSectionItemEx *sectionItem)
{
   return Add(sectionItem);
}

STDMETHODIMP CCompositeSectionEx::AddSection(IShape* shape, Float64 Efg,Float64 Ebg, Float64 Dfg, Float64 Dbg, VARIANT_BOOL bStructural)
{
   CHECK_IN(shape);
   if ( Efg < 0 || Ebg < 0 )
      return E_INVALIDARG;

   if ( Dfg < 0 || Dbg < 0 )
      return E_INVALIDARG;

   CComObject<CCompositeSectionItemEx>* item;
   CComObject<CCompositeSectionItemEx>::CreateInstance(&item);
   item->putref_Shape(shape);
   item->put_Dfg(Dfg);
   item->put_Dbg(Dbg);
   item->put_Efg(Efg);
   item->put_Ebg(Ebg);
   item->put_Structural(bStructural);

   return AddSectionEx(item);
}
//
//STDMETHODIMP CCompositeSectionEx::Remove(long idx)
//{
//   if ( idx < 0 || m_coll.size() <= idx )
//      return E_INVALIDARG;
//
//   m_coll.erase( m_coll.begin() + idx );
//
//	return S_OK;
//}
//
STDMETHODIMP CCompositeSectionEx::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
	return S_OK;
}
//
////STDMETHODIMP CCompositeSectionEx::get__NewEnum(IUnknown **pVal)
////{
////}
//
//STDMETHODIMP CCompositeSectionEx::get_Item(long idx, ICompositeSectionItemEx **pVal)
//{
//   CHECK_RETOBJ(pVal);
//
//   if ( idx < 0 || m_coll.size() <= idx )
//      return E_INVALIDARG;
//
//   // In order to support Visual Basic's For Each construct, we have a
//   // collection of variants. Get the variant for this Index by using
//   // ICollectionOnSTLImpl implementation. Then, get the real interface.
//   CComVariant var;
//   HRESULT hr = ICompositeSectionCollection::get_Item(idx+1,&var); //+1 because ATL uses 1-based index
//   if (FAILED(hr) )
//      return hr;
//
//   var.pdispVal->QueryInterface( pVal );
//   return S_OK;
//}

STDMETHODIMP CCompositeSectionEx::get_Section(ISection **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_ISection, (void**)pVal );
}

STDMETHODIMP CCompositeSectionEx::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

STDMETHODIMP CCompositeSectionEx::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

///////////////////////////////////////////////
// ISection
//
STDMETHODIMP CCompositeSectionEx::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IRect2d> totalBox;
   totalBox.CoCreateInstance(CLSID_Rect2d);

   ContainerIteratorType iter = m_coll.begin();
   ContainerIteratorType end = m_coll.end();
   for (; iter != end; iter++)
   {
      StoredType& value = *iter;
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IRect2d> box;
      shape->get_BoundingBox(&box);

      if ( iter == m_coll.begin() )
      {
         totalBox = box;
      }
      else
      {
         CComPtr<IRect2d> unionBox;
         totalBox->UnionBy(box,&unionBox);
         totalBox = unionBox;
      }
   }

   *pVal = totalBox;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::get_ElasticProperties(IElasticProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IElasticProperties> elasticProps = nullptr;

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      VARIANT_BOOL bStructural;
      item->get_Structural(&bStructural);

      if ( bStructural == VARIANT_FALSE )
         continue; // Don't included non-structural components in elastic properties


      Float64 Efg, Ebg;
      item->get_Efg(&Efg);
      item->get_Ebg(&Ebg);
      Float64 E = Efg - Ebg;

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShapeProperties> props;
      shape->get_ShapeProperties(&props);

      props->put_CoordinateSystem(csCentroidal);

      Float64 area;
      Float64 ixx;
      Float64 iyy;
      Float64 ixy;
      Float64 xl,xr,yt,yb;
      CComPtr<IPoint2d> cg;
      props->get_Area(&area);
      props->get_Ixx(&ixx);
      props->get_Iyy(&iyy);
      props->get_Ixy(&ixy);
      props->get_Centroid(&cg);
      props->get_Xleft(&xl);
      props->get_Xright(&xr);
      props->get_Ytop(&yt);
      props->get_Ybottom(&yb);

      CComObject<CElasticProperties>* ep;
      CComObject<CElasticProperties>::CreateInstance(&ep);
      CComPtr<IElasticProperties> epThisShape = ep;

      epThisShape->put_EA(E*area);
      epThisShape->put_EIxx(E*ixx);
      epThisShape->put_EIxy(E*ixy);
      epThisShape->put_EIyy(E*iyy);
      epThisShape->put_Centroid(cg);
      epThisShape->put_Xleft(xl);
      epThisShape->put_Xright(xr);
      epThisShape->put_Ytop(yt);
      epThisShape->put_Ybottom(yb);

      if ( elasticProps == nullptr )
         elasticProps = epThisShape; // first time through the loop
      else
         elasticProps->AddProperties(epThisShape);
   }

   // if elasticProps is still nullptr, then there was nothing in the collection
   // create a default set of properties
   if ( elasticProps == nullptr )
   {
      CComObject<CElasticProperties>* ep;
      CComObject<CElasticProperties>::CreateInstance(&ep);
      elasticProps = ep;
   }

   (*pVal) = elasticProps;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::get_MassProperties(IMassProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComObject<CMassProperties>* massProps;
   CComObject<CMassProperties>::CreateInstance(&massProps);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      Float64 Dfg, Dbg;
      item->get_Dfg(&Dfg);
      item->get_Dbg(&Dbg);
      
      Float64 density = Dfg - Dbg;

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShapeProperties> props;
      shape->get_ShapeProperties(&props);

      Float64 area;
      props->get_Area(&area);

      CComObject<CMassProperties>* objMP;
      CComObject<CMassProperties>::CreateInstance(&objMP);

      CComPtr<IMassProperties> mp(objMP);

      mp->put_MassPerLength(density*area);

      massProps->AddProperties(mp);
   }

   (*pVal) = massProps;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::ClipIn(IRect2d* rect,ISection** section)
{
   CHECK_IN(rect);
   CHECK_RETOBJ(section);

   CComObject<CCompositeSectionEx>* clipSection;
   CComObject<CCompositeSectionEx>::CreateInstance(&clipSection);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShape> clipShape;
      shape->ClipIn(rect,&clipShape);

      if ( clipShape )
      {
         Float64 Efg, Ebg;
         Float64 Dfg, Dbg;
         VARIANT_BOOL bStructural;

         item->get_Efg(&Efg);
         item->get_Ebg(&Ebg);
         item->get_Dfg(&Dfg);
         item->get_Dbg(&Dbg);
         item->get_Structural(&bStructural);

         clipSection->AddSection(clipShape,Efg,Ebg,Dfg,Dbg,bStructural);
      }
   }

   clipSection->QueryInterface(section);

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::ClipWithLine(ILine2d* line,ISection** section)
{
   CHECK_IN(line);
   CHECK_RETOBJ(section);

   CComObject<CCompositeSectionEx>* clipSection;
   CComObject<CCompositeSectionEx>::CreateInstance(&clipSection);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShape> clipShape;
      shape->ClipWithLine(line,&clipShape);

      if ( clipShape )
      {
         Float64 Efg, Ebg;
         Float64 Dfg, Dbg;
         VARIANT_BOOL bStructural;

         item->get_Efg(&Efg);
         item->get_Ebg(&Ebg);
         item->get_Dfg(&Dfg);
         item->get_Dbg(&Dbg);
         item->get_Structural(&bStructural);

         clipSection->AddSection(clipShape,Efg,Ebg,Dfg,Dbg,bStructural);
      }
   }

   clipSection->QueryInterface(section);

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::Clone(ISection** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCompositeSectionEx>* cloneSection;
   CComObject<CCompositeSectionEx>::CreateInstance(&cloneSection);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);
      CComPtr<IShape> cloneShape;
      shape->Clone(&cloneShape);

      Float64 Efg, Ebg;
      Float64 Dfg, Dbg;
      VARIANT_BOOL bStructural;

      item->get_Efg(&Efg);
      item->get_Ebg(&Ebg);
      item->get_Dfg(&Dfg);
      item->get_Dbg(&Dbg);
      item->get_Structural(&bStructural);

      cloneSection->AddSection(cloneShape,Efg,Ebg,Dfg,Dbg,bStructural);
   }

   cloneSection->QueryInterface(clone);

	return S_OK;
}

///////////////////////////////////////////////
// IXYPosition
//
STDMETHODIMP CCompositeSectionEx::Offset(Float64 dx,Float64 dy)
{
   if (IsZero(dx) && IsZero(dy))
   {
      return S_OK;
   }

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);
      position->Offset(dx,dy);
   }

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);
   Float64 dx, dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx, dy);
}

STDMETHODIMP CCompositeSectionEx::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
{
   CHECK_RETOBJ(point);
   if ( m_coll.size() == 0 )
   {
      // If the collection is empty, just return a point at (0,0)
      ::CoCreateInstance(CLSID_Point2d,nullptr,CLSCTX_ALL,IID_IPoint2d,(void**)point);
      (*point)->Move(0,0);
      return S_OK;
   }
   else
   {
      // If the hook point is requested, return the hook point for the first shape, otherwise
      // figure out the locator point
      if ( lp == lpHookPoint )
      {
         CComPtr<ICompositeSectionItemEx> item;
         get_Item(0,&item);

         CComPtr<IShape> shape;
         item->get_Shape(&shape);

         CComQIPtr<IXYPosition> position(shape);
         return position->get_LocatorPoint(lp,point);
      }
      else
      {
         CComPtr<IRect2d> box;
         get_BoundingBox(&box);
         switch(lp)
         {
         case lpTopLeft:
            box->get_TopLeft(point);
            break;

         case lpTopCenter:
            box->get_TopCenter(point);
            break;

         case lpTopRight:
            box->get_TopRight(point);
            break;

         case lpCenterLeft:
            box->get_CenterLeft(point);
            break;

         case lpCenterCenter:
            box->get_CenterCenter(point);
            break;

         case lpCenterRight:
            box->get_CenterRight(point);
            break;

         case lpBottomLeft:
            box->get_BottomLeft(point);
            break;

         case lpBottomCenter:
            box->get_BottomCenter(point);
            break;

         case lpBottomRight:
            box->get_BottomRight(point);
            break;
         }
      }
   }

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
{
   CHECK_IN(point);

   CComPtr<IPoint2d> locPoint;
   get_LocatorPoint(lp,&locPoint);

   Float64 x1,y1;
   Float64 x2,y2;

   point->get_X(&x1);
   point->get_Y(&y1);

   locPoint->get_X(&x2);
   locPoint->get_Y(&y2);

   Float64 dx, dy;
   dx = x1 - x2;
   dy = y1 - y2;

   return Offset(dx,dy);
}

STDMETHODIMP CCompositeSectionEx::MoveEx(IPoint2d* pFrom, IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->MoveEx(pFrom,pTo);
   }

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::RotateEx(IPoint2d* pPoint, Float64 angle)
{
   CHECK_IN(pPoint);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->RotateEx(pPoint,angle);
   }

	return S_OK;
}

STDMETHODIMP CCompositeSectionEx::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   for (auto& value : m_coll)
   {
      CComPtr<ICompositeSectionItemEx> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->Rotate(cx,cy,angle);
   }

	return S_OK;
}

