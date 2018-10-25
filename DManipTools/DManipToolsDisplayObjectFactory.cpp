///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2018  Washington State Department of Transportation
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

// DManipToolsDisplayObjectFactory.cpp : Implementation of CDManipToolsDisplayObjectFactory
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "DManipToolsDisplayObjectFactory.h"
#include "LegendDisplayObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDManipToolsDisplayObjectFactory

CDManipToolsDisplayObjectFactory::CDManipToolsDisplayObjectFactory()
{
}


STDMETHODIMP CDManipToolsDisplayObjectFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iDisplayObjectFactory
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
} 

STDMETHODIMP_(void) CDManipToolsDisplayObjectFactory::Create(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj)
{
   if ( cfFormat == CLegendDisplayObject::ms_cfFormat )
   {
      CComPtr<iLegendDisplayObject> legRep;
      legRep.CoCreateInstance(CLSID_LegendDisplayObject);

      if ( pDataObject )
      {
         // Initialize from data object
         CComPtr<iDragDataSource> source;
         ::CoCreateInstance(CLSID_DragDataSource,nullptr,CLSCTX_ALL,IID_iDragDataSource,(void**)&source);
         source->SetDataObject(pDataObject);

         // rebuild the display object from the data source
         CComQIPtr<iDraggable,&IID_iDraggable> draggable(legRep);
         draggable->OnDrop(source);
      }

      legRep.QueryInterface(dispObj);
   }
}
