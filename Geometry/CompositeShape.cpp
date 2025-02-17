///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// CompositeShape.cpp : Implementation of CCompositeShape
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CompositeShape.h"
#include "CompositeShapeItem.h"
#include "ShapeProperties.h"
#include "Helper.h"
#include <float.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeShape

STDMETHODIMP CCompositeShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompositeShape,
      &IID_IShape,
      &IID_IXYPosition
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCompositeShape::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CCompositeShape::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IXYPosition, (void**)pVal);
}

STDMETHODIMP CCompositeShape::AddShapeEx(ICompositeShapeItem *ShapeItem)
{
   return Add(ShapeItem);
}

STDMETHODIMP CCompositeShape::AddShape(IShape* shape, VARIANT_BOOL bVoid)
{
   CHECK_IN(shape);

   CComObject<CCompositeShapeItem>* item;
   CComObject<CCompositeShapeItem>::CreateInstance(&item);
   item->putref_Shape(shape);
   item->put_Void(bVoid);

   return AddShapeEx(item);
}

STDMETHODIMP CCompositeShape::ReplaceEx(IndexType idx,ICompositeShapeItem* pShapeItem)
{
   if ( idx < 0 || (IndexType)m_coll.size() <= idx )
      return E_INVALIDARG;

   m_coll[idx].second.m_T = pShapeItem;
   return S_OK;
}

STDMETHODIMP CCompositeShape::Replace(IndexType idx,IShape* pShape)
{
   if ( idx < 0 || (IndexType)m_coll.size() <= idx )
      return E_INVALIDARG;

   CComPtr<ICompositeShapeItem> shapeItem = m_coll[idx].second.m_T;
   shapeItem->putref_Shape(pShape);

   return S_OK;
}


///////////////////////////////////////////////
// IShape
//
STDMETHODIMP CCompositeShape::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CHECK_IN(line);
   CHECK_RETVAL(pVal);

   if ( m_coll.size() == 0 )
   {
      *pVal = 0;
      return S_OK;
   }

   Float64 distance = -DBL_MAX;

   for(auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      Float64 this_distance;
      shape->FurthestDistance(line,&this_distance);
      distance = Max(distance,this_distance);
   }

   *pVal = distance;

   return S_OK;
}

STDMETHODIMP CCompositeShape::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CHECK_IN(line);
   CHECK_RETOBJ(ppPoint);
   CHECK_RETVAL(dist);

   if (m_coll.size() == 0)
   {
      CreatePoint(WBFL::Geometry::Point2d(0, 0), ppPoint);
      *dist = 0;
      return S_OK;
   }

   Float64 distance = -DBL_MAX;
   CComPtr<IPoint2d> furthestPoint;
   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IPoint2d> pnt;
      Float64 this_distance;
      shape->FurthestPoint(line, &pnt, &this_distance);
      if (distance < this_distance)
      {
         distance = this_distance;
         furthestPoint = pnt;
      }
   }

   *dist = distance;
   furthestPoint.CopyTo(ppPoint);

   return S_OK;
}

STDMETHODIMP CCompositeShape::get_Perimeter(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( m_coll.size() == 0 )
   {
      *pVal = 0;
      return S_OK;
   }

   CComPtr<ICompositeShapeItem> item;
   get_Item(0,&item);

   CComPtr<IShape> shape;
   item->get_Shape(&shape);

   return shape->get_Perimeter(pVal);
}

STDMETHODIMP CCompositeShape::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CHECK_RETOBJ(ppPolyPoints);

   if ( m_coll.size() == 0 )
      return S_OK;

   CComPtr<ICompositeShapeItem> item;
   get_Item(0,&item);

   CComPtr<IShape> shape;
   item->get_Shape(&shape);

   return shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CCompositeShape::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   VARIANT_BOOL bIsInSolid = VARIANT_FALSE; // Point has to be in a solid shape to have a chance.
                                            // If it is in a void, it's all over.
   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      VARIANT_BOOL isVoid;
      item->get_Void(&isVoid);
      if (isVoid != VARIANT_FALSE)
      {
         CComPtr<IShape> shape;
         item->get_Shape(&shape);

         VARIANT_BOOL isInVoid;
         shape->PointInShape(pPoint, &isInVoid);

         // If point is in a void, it is not in the composite shape. We're out of here
         if (isInVoid != VARIANT_FALSE)
         {
            *pbResult = VARIANT_FALSE;
            return S_OK;
         }
      }
      else if (bIsInSolid == VARIANT_FALSE) // No use testing more solids if point was already in one
      {
         // Shape is a solid. See if we are in.
         CComPtr<IShape> shape;
         item->get_Shape(&shape);

         shape->PointInShape(pPoint, &bIsInSolid);
      }
   }

   *pbResult = bIsInSolid;

   return S_OK;
}

STDMETHODIMP CCompositeShape::get_BoundingBox(IRect2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IRect2d> totalBox;
   totalBox.CoCreateInstance(CLSID_Rect2d);

   ContainerIteratorType iter = m_coll.begin();
   ContainerIteratorType end = m_coll.end();
   for (; iter != end; iter++)
   {
      StoredType& value = *iter;
      CComPtr<ICompositeShapeItem> item(value.second);

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

STDMETHODIMP CCompositeShape::get_ShapeProperties(IShapeProperties* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IShapeProperties> shapeProps;

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      VARIANT_BOOL bVoid;
      item->get_Void(&bVoid);
      Float64 sign = (bVoid == VARIANT_TRUE) ? -1 : 1;

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

      CComObject<CShapeProperties>* objSP;
      CComObject<CShapeProperties>::CreateInstance(&objSP);
      CComPtr<IShapeProperties> sp(objSP);

      sp->put_Area(sign*area);
      sp->put_Ixx(sign*ixx);
      sp->put_Ixy(sign*ixy);
      sp->put_Iyy(sign*iyy);
      sp->put_Centroid(cg);
      sp->put_Xleft(xl);
      sp->put_Xright(xr);
      sp->put_Ytop(yt);
      sp->put_Ybottom(yb);

      if ( shapeProps == nullptr )
         shapeProps = sp; // first time through the loop
      else
         shapeProps->AddProperties(sp);
   }

   // if shapeProps is still nullptr, then there was nothing in the collection
   // create a default set of properties
   if ( shapeProps == nullptr )
   {
      CComObject<CShapeProperties>* objShapeProps;
      CComObject<CShapeProperties>::CreateInstance(&objShapeProps);
      objShapeProps->QueryInterface(&shapeProps);
   }

   (*pVal) = shapeProps;
   (*pVal)->AddRef();

	return S_OK;
}


STDMETHODIMP CCompositeShape::ClipIn(IRect2d* rect,IShape** Shape)
{
   CHECK_IN(rect);
   CHECK_RETOBJ(Shape);

   CComObject<CCompositeShape>* clipShape;
   CComObject<CCompositeShape>::CreateInstance(&clipShape);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShape> clippedShape;
      shape->ClipIn(rect,&clippedShape);

      if (clippedShape)
      {
         VARIANT_BOOL bVoid;

         item->get_Void(&bVoid);

         clipShape->AddShape(clippedShape,bVoid);
      }
   }

   IndexType nShapes;
   CComPtr<ICompositeShape> compShape(clipShape);
   compShape->get_Count(&nShapes);
   if (0 < nShapes)
   {
      clipShape->QueryInterface(Shape);
   }

	return S_OK;
}

STDMETHODIMP CCompositeShape::ClipWithLine(ILine2d* line,IShape** Shape)
{
   CHECK_IN(line);
   CHECK_RETOBJ(Shape);

   CComObject<CCompositeShape>* clipShape;
   CComObject<CCompositeShape>::CreateInstance(&clipShape);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComPtr<IShape> clippedShape;
      shape->ClipWithLine(line,&clippedShape);

      if (clippedShape)
      {
         VARIANT_BOOL bVoid;

         item->get_Void(&bVoid);

         clipShape->AddShape(clippedShape,bVoid);
      }
   }

   IndexType nShapes;
   CComPtr<ICompositeShape> compShape(clipShape);
   compShape->get_Count(&nShapes);
   if (0 < nShapes)
   {
      clipShape->QueryInterface(Shape);
   }


	return S_OK;
}

STDMETHODIMP CCompositeShape::Clone(IShape** clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCompositeShape>* cloneShape;
   CComObject<CCompositeShape>::CreateInstance(&cloneShape);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);
      CComPtr<IShape> clonedShape;
      shape->Clone(&clonedShape);

      VARIANT_BOOL bVoid;

      item->get_Void(&bVoid);

      cloneShape->AddShape(clonedShape,bVoid);
   }

   cloneShape->QueryInterface(clone);

	return S_OK;
}

///////////////////////////////////////////////
// IXYPosition
//
STDMETHODIMP CCompositeShape::Offset(Float64 dx,Float64 dy)
{
   if (IsZero(dx) && IsZero(dy))
   {
      return S_OK;
   }

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);
      position->Offset(dx,dy);
   }

	return S_OK;
}

STDMETHODIMP CCompositeShape::OffsetEx(ISize2d* pSize)
{
   CHECK_IN(pSize);
   Float64 dx, dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx, dy);
}

STDMETHODIMP CCompositeShape::get_LocatorPoint(LocatorPointType lp, IPoint2d** point)
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
         CComPtr<ICompositeShapeItem> item;
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

STDMETHODIMP CCompositeShape::put_LocatorPoint(LocatorPointType lp, IPoint2d* point)
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

STDMETHODIMP CCompositeShape::MoveEx(IPoint2d* pFrom, IPoint2d* pTo)
{
   CHECK_IN(pFrom);
   CHECK_IN(pTo);

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->MoveEx(pFrom,pTo);
   }

	return S_OK;
}

STDMETHODIMP CCompositeShape::RotateEx(IPoint2d* pPoint, Float64 angle)
{
   CHECK_IN(pPoint);
   if (IsZero(angle))
   {
      return S_OK;
   }

   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->RotateEx(pPoint,angle);
   }

	return S_OK;
}

STDMETHODIMP CCompositeShape::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   for (auto& value : m_coll)
   {
      CComPtr<ICompositeShapeItem> item(value.second);

      CComPtr<IShape> shape;
      item->get_Shape(&shape);

      CComQIPtr<IXYPosition> position(shape);

      position->Rotate(cx,cy,angle);
   }

	return S_OK;
}
