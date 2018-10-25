///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2010  Washington State Department of Transportation
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

// RebarFactory.cpp : Implementation of CRebarFactory
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "RebarFactory.h"
#include "Rebar.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarFactory
HRESULT CRebarFactory::FinalConstruct()
{
   return S_OK;
}

void CRebarFactory::FinalRelease()
{
}

STDMETHODIMP CRebarFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRebarFactory,
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
// IRebarFactory implementation
STDMETHODIMP CRebarFactory::CreateRebar(MaterialSpec spec,RebarGrade grade,BarSize size,IUnitConvert* pConvert,IRebar** rebar)
{
   CHECK_RETOBJ(rebar);

   // at this point, spec doesn't matter because only 1 is supported

   Float64 fu, fy;
   switch( grade )
   {
   case Grade40:
      fu = 60;
      fy = 40;
      break;

   case Grade60:
      fu = 90;
      fy = 60;
      break;

   case Grade75:
      fu = 100;
      fy = 75;
      break;
   }

   pConvert->ConvertToBaseUnits(fu,CComBSTR("ksi"),&fu);
   pConvert->ConvertToBaseUnits(fy,CComBSTR("ksi"),&fy);

   CComBSTR bstrName;
   Float64 as, db;
   switch ( size )
   {
   case bs3:   bstrName = "#3";  as = 0.11; db = 0.375;  break;
   case bs4:   bstrName = "#4";  as = 0.20; db = 0.500;  break;
   case bs5:   bstrName = "#5";  as = 0.31; db = 0.625;  break;
   case bs6:   bstrName = "#6";  as = 0.44; db = 0.750;  break;
   case bs7:   bstrName = "#7";  as = 0.60; db = 0.875;  break;
   case bs8:   bstrName = "#8";  as = 0.79; db = 1.000;  break;
   case bs9:   bstrName = "#9";  as = 1.00; db = 1.128;  break;
   case bs10:  bstrName = "#10"; as = 1.27; db = 1.270;  break;
   case bs11:  bstrName = "#11"; as = 1.56; db = 1.410;  break;
   case bs14:  bstrName = "#14"; as = 2.25; db = 1.693;  break;
   case bs18:  bstrName = "#18"; as = 4.00; db = 2.257;  break;
   }

   pConvert->ConvertToBaseUnits(as,CComBSTR("in^2"),&as);
   pConvert->ConvertToBaseUnits(db,CComBSTR("in"),  &db);

   Float64 weight = 490;
   pConvert->ConvertToBaseUnits(weight,CComBSTR("pcf"),&weight);

   Float64 E = 29000;
   pConvert->ConvertToBaseUnits(E,CComBSTR("ksi"),&E);

   CComObject<CRebar>* pRebar;
   CComObject<CRebar>::CreateInstance(&pRebar);

   (*rebar) = pRebar;
   (*rebar)->AddRef();

   (*rebar)->Init(bstrName,E,weight,fu,fy,db,as);

   return S_OK;
}

/////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CRebarFactory::Load(IStructuredLoad2* load)
{
   CHECK_IN(load);

   CComVariant var;
   load->BeginUnit(CComBSTR("RebarFactory"));

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);

   return S_OK;
}

STDMETHODIMP CRebarFactory::Save(IStructuredSave2* save)
{
   CHECK_IN(save);

   save->BeginUnit(CComBSTR("RebarFactory"),1.0);


   save->EndUnit();

   return S_OK;
}
