///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TendonCollection.cpp : Implementation of CTendonCollection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "TendonCollection.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTendonCollection
HRESULT CTendonCollection::FinalConstruct()
{
   return S_OK;
}

void CTendonCollection::FinalRelease()
{
}

STDMETHODIMP CTendonCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITendonCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// ITendonCollection
//STDMETHODIMP CTendonCollection::Add(ITendon* tendon)
//{
//}
//
//STDMETHODIMP CTendonCollection::get_Item(long index,ITendon** tendon)
//{
//}
//
//STDMETHODIMP CTendonCollection::Remove(long index)
//{
//}
//
//STDMETHODIMP CTendonCollection::Clear()
//{
//}

STDMETHODIMP CTendonCollection::get_CG(Float64 zLoc,TendonMeasure measure,IPoint3d** cg)
{
   CHECK_RETOBJ(cg);

   iterator iter;
   StrandIndexType nStrands = 0;
   Float64 nsx = 0;
   Float64 nsy = 0;
   Float64 nsz = 0;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendon> tendon = iter->second;
      CComPtr<IPoint3d> tcg;
      tendon->get_CG(zLoc,measure,&tcg);

      StrandIndexType ns;
      tendon->get_StrandCount(&ns);

      Float64 x,y,z;
      tcg->get_X(&x);
      tcg->get_Y(&y);
      tcg->get_Z(&z);

      nsx += ns*x;
      nsy += ns*y;
      nsz += ns*z;

      nStrands += ns;
   }

   Float64 cgx,cgy,cgz;
   cgx = nsx/nStrands;
   cgy = nsy/nStrands;
   cgz = nsz/nStrands;

   CComPtr<IPoint3d> pcg;
   pcg.CoCreateInstance(CLSID_Point3d);
   pcg->put_X(cgx);
   pcg->put_Y(cgy);
   pcg->put_Z(cgz);

   (*cg) = pcg;
   (*cg)->AddRef();

   return S_OK;
}

STDMETHODIMP CTendonCollection::get_Slope(Float64 zLoc,TendonMeasure measure,IVector3d** slope)
{
   CHECK_RETOBJ(slope);

   iterator iter;
   StrandIndexType nStrands = 0;
   Float64 nsx = 0;
   Float64 nsy = 0;
   Float64 nsz = 0;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendon> tendon = iter->second;
      CComPtr<IVector3d> tslope;
      tendon->get_Slope(zLoc,measure,&tslope);

      StrandIndexType ns;
      tendon->get_StrandCount(&ns);

      Float64 x,y,z;
      tslope->get_X(&x);
      tslope->get_Y(&y);
      tslope->get_Z(&z);

      nsx += ns*x;
      nsy += ns*y;
      nsz += ns*z;

      nStrands += ns;
   }

   Float64 cgx,cgy,cgz;
   cgx = nsx/nStrands;
   cgy = nsy/nStrands;
   cgz = nsz/nStrands;

   CComPtr<IVector3d> pslope;
   pslope.CoCreateInstance(CLSID_Vector3d);
   pslope->put_X(cgx);
   pslope->put_Y(cgy);
   pslope->put_Z(cgz);

   (*slope) = pslope;
   (*slope)->AddRef();

   return S_OK;
}

STDMETHODIMP CTendonCollection::Cut(Float64 zLoc,TendonMeasure measure,IPoint3dCollection** points)
{
   CHECK_RETOBJ(points);

   CComPtr<IPoint3dCollection> p;
   p.CoCreateInstance(CLSID_Point3dCollection);

   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      CComPtr<ITendon> tendon = iter->second;
      CComPtr<IPoint3d> cg;
      tendon->get_CG(zLoc,measure,&cg);
      p->Add(cg);
   }

   (*points) = p;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CTendonCollection::get__EnumTendons(IEnumTendons* *enumTendons)
{
	return get__EnumElements(enumTendons);
}

///////////////////////////////////////////////////////
//// IStructuredStorage2 implementation
//STDMETHODIMP CTendonCollection::Load(IStructuredLoad2* load)
//{
//   CHECK_IN(load);
//
//   CComVariant var;
//   load->BeginUnit(CComBSTR("TendonCollection"));
//
//   VARIANT_BOOL bEnd;
//   load->EndUnit(&bEnd);
//
//   return S_OK;
//}
//
//STDMETHODIMP CTendonCollection::Save(IStructuredSave2* save)
//{
//   CHECK_IN(save);
//
//   save->BeginUnit(CComBSTR("TendonCollection"),1.0);
//
//   save->EndUnit();
//
//   return S_OK;
//}
