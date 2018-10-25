///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// PSPowerFormula.cpp : Implementation of CPSPowerFormula
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "PSPowerFormula.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSPowerFormula

STDMETHODIMP CPSPowerFormula::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IPowerFormula,
		&IID_IStressStrain,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPSPowerFormula::FinalConstruct()
{
   HRESULT hr = m_UnitServer.CoCreateInstance(CLSID_UnitServer);
   if ( FAILED(hr) )
      return hr;

   SetupUnits();

   m_MinStrain = -0.035;
   m_MaxStrain =  0.035;

   return S_OK;
}

void CPSPowerFormula::FinalRelease()
{
   ClearUnits();
}

void CPSPowerFormula::ClearUnits()
{
   m_ksiUnit.Release();
   m_Convert.Release();
   m_UnitServer.Release();
}

void CPSPowerFormula::SetupUnits()
{
   CComPtr<IUnitTypes> unitTypes;
   m_UnitServer->get_UnitTypes(&unitTypes);

   CComPtr<IUnitType> unitType;
   unitTypes->get_Item(CComVariant("Pressure"),&unitType);

   CComPtr<IUnits> units;
   unitType->get_Units(&units);

   units->get_Item(CComVariant("ksi"),&m_ksiUnit);

   m_UnitServer.QueryInterface(&m_Convert);
}

STDMETHODIMP CPSPowerFormula::get_Grade(StrandGradeType* grade)
{
   CHECK_RETVAL(grade);
   *grade = m_StrandGrade;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_Grade(StrandGradeType grade)
{
   m_StrandGrade = grade;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_ProductionMethod(ProductionMethodType* type)
{
   CHECK_RETVAL(type);
   *type = m_ProductionMethod;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_ProductionMethod(ProductionMethodType type)
{
   m_ProductionMethod = type;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::put_Name(BSTR name)
{
   m_bstrName = name;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_Name(BSTR *name)
{
   CHECK_RETSTRING(name);
   *name = m_bstrName.Copy();
   return S_OK;
}


STDMETHODIMP CPSPowerFormula::ComputeStress(Float64 strain,Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 sign = BinarySign(strain);
   strain = fabs(strain);

   Float64 fps;

   if ( m_StrandGrade == sgtGrade270 )
   {
      if ( m_ProductionMethod == pmtLowRelaxation )
      {
         // from PCI Bridge Design Manual
         fps = strain*(887. + 27613./pow((1+pow(112.4*strain,7.36)),1./7.36));

         if ( 270.0 < fps )
            fps = 270.0;
      }
      else
      {
         // from Collins and Mitchell text book
         fps = strain*(885. + 27645./pow((1+pow(118*strain,6)),1./6));

         if ( 270.0 < fps )
            fps = 270.0;
      }
   }
   else
   {
      // Grade 250
      if (m_ProductionMethod == pmtLowRelaxation )
      {
         // from PCI Bridge Design Manual
         if (strain < 0.0076)
            fps = strain*m_Eps;
         else
            fps = 250 - 0.04/(strain - 0.00640239520958);

         if ( 250.0 < fps )
            fps = 250.0;
      }
      else
      {
         // ################ NOTE ############
         // This is the formula for low relaxation strands
         // since I don't have one for stress relieved this is going to have to do for now


         // from PCI Bridge Design Manual
         if (strain < 0.0076)
            fps = strain*m_Eps;
         else
            fps = 250 - 0.04/(strain - 0.00640239520958);

         if ( 250.0 < fps )
            fps = 250.0;
      }
   }

   // The stress is in KSI, convert it to base units because that is what the caller expects
   m_Convert->ConvertToBaseUnits(fps,m_ksiUnit,&fps);

   *pVal = sign*fps;

   return S_OK;
}

STDMETHODIMP CPSPowerFormula::StrainLimits(Float64* minStrain,Float64* maxStrain)
{
   CHECK_RETVAL(minStrain);
   CHECK_RETVAL(maxStrain);

   *minStrain = m_MinStrain;
   *maxStrain = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_StrainAtPeakStress(Float64* strain)
{
   CHECK_RETVAL(strain);
   (*strain) = m_MaxStrain;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_YieldStrain(Float64* pey)
{
   CHECK_RETVAL(pey);
   *pey = 0.9*m_Fpu/m_Eps;
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_ModulusOfElasticity(Float64* pE)
{
   CHECK_RETVAL(pE);
   m_Convert->ConvertToBaseUnits(m_Eps,m_ksiUnit,pE);
   return S_OK;
}

STDMETHODIMP CPSPowerFormula::get_UnitServer(IUnitServer** ppVal )
{
   CHECK_RETOBJ(ppVal);

   (*ppVal) = m_UnitServer;
   (*ppVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CPSPowerFormula::putref_UnitServer(IUnitServer* pNewVal )
{
   CHECK_IN(pNewVal);

   ClearUnits();
   m_UnitServer = pNewVal;
   SetupUnits();

   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CPSPowerFormula::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PSPowerFormula"),1.0);

   pSave->put_Property(CComBSTR("ProductionMethod"),CComVariant(m_ProductionMethod));
   pSave->put_Property(CComBSTR("Grade"),CComVariant(m_StrandGrade));

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPSPowerFormula::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PSPowerFormula"));

   ProductionMethodType m_ProductionMethod;
   StrandGradeType m_StrandGrade;

   if ( FAILED(pLoad->get_Property(CComBSTR("ProductionMethod"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_ProductionMethod = (ProductionMethodType)var.lVal;

   if ( FAILED(pLoad->get_Property(CComBSTR("Grade"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   m_StrandGrade = (StrandGradeType)var.lVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}

// IPersist
STDMETHODIMP CPSPowerFormula::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}
