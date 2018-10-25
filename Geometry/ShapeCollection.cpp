///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// ShapeCollection.cpp : Implementation of CShapeCollection
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "ShapeCollection.h"
#include "ShapeProperties.h"
#include "Helper.h"
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShapeCollection

STDMETHODIMP CShapeCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IShapeCollection,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//STDMETHODIMP CShapeCollection::get__NewEnum(IUnknown** retval)
//{
//	// TODO: Add your implementation code here
//	return S_OK;
//}
//

STDMETHODIMP CShapeCollection::get__Enum(IEnumShape** ppenum)
{
   return get__EnumElements(ppenum);
}

STDMETHODIMP CShapeCollection::get_ShapeProperties(IShapeProperties** props)
{
   CHECK_RETOBJ(props);

   CComPtr<IEnumShape> pEnum;
   get__Enum(&pEnum);

   bool bFirst = true;
   CComPtr<IShape> pShape;
   while ( pEnum->Next(1,&pShape,NULL) == S_OK )
   {
      CComPtr<IShapeProperties> prp;
      pShape->get_ShapeProperties(&prp);

      if ( bFirst )
      {
         // first time through, assign the properties of the
         // first shape to the return value
         prp.QueryInterface(props);
         bFirst = false;
      }
      else
      {
         // add the subsequent properties together
         (*props)->AddProperties(prp);
      }

      pShape.Release();
   }

   return S_OK;
}

STDMETHODIMP CShapeCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}
