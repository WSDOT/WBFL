///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// UnitServerImp.cpp : Implementation of CUnitServerImp
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "UnitServerImp.h"
#include "UnitType.h"
#include "Helper.h"
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class RollBack
{
public:
   RollBack(IUnit** ppUnit) :
      m_ppUnit( ppUnit )
      {
         m_pUnit = *ppUnit;
         bRollback = true;
      }

   ~RollBack()
   {
      if ( *m_ppUnit )
         (*m_ppUnit)->Release();

      if ( bRollback )
      {
         *m_ppUnit = m_pUnit;
      }
   }

   void Commit()
   {
      bRollback = false;
   }


private:
   IUnit** m_ppUnit;
   CComPtr<IUnit> m_pUnit;
   bool bRollback;
};

/////////////////////////////////////////////////////////////////////////////
// CUnitServerImp

HRESULT check_dimensionality( IUnitType* pFromUnitType, IUnitType* pToUnitType );

HRESULT CUnitServerImp::GetUnitType(BSTR bstrLabel,IUnitType** ppUnitType)
{
   return m_pUnitTypes->get_Item(CComVariant(bstrLabel),ppUnitType);
}

HRESULT CUnitServerImp::GetUnit(BSTR bstrType,BSTR bstrTag,IUnit** ppUnit)
{
   HRESULT hr = S_OK;

   CComPtr<IUnitType> pUnitType;
   hr = GetUnitType(bstrType,&pUnitType);
   ATLASSERT( SUCCEEDED(hr) );

   CComPtr<IUnits> pUnits;
   pUnitType->get_Units( &pUnits );
   CComVariant var_tag(bstrTag);
   return pUnits->get_Item( var_tag, ppUnit );
}

HRESULT CUnitServerImp::GetUnit(BSTR bstrTag,IUnit** ppUnit)
{
   HRESULT hr;

   CollectionIndexType cUnitTypes;
   m_pUnitTypes->get_Count( &cUnitTypes );
   for (CollectionIndexType i = 0; i < cUnitTypes; i++)
   {
      CComPtr<IUnitType> pUnitType;
      hr = m_pUnitTypes->get_Item(CComVariant(i),&pUnitType);
      if ( FAILED(hr) )
         return hr;

      CComBSTR bstrLabel;
      pUnitType->get_Label( &bstrLabel );

      hr = GetUnit( bstrLabel, bstrTag, ppUnit );
      if ( SUCCEEDED(hr) )
         return hr;
   }

   return E_INVALIDARG;
}

HRESULT CUnitServerImp::FinalConstruct()
{
   HRESULT hr;
   CComObject<CUnitTypes>* pUnitTypes;
   hr = CComObject<CUnitTypes>::CreateInstance( &pUnitTypes );
   if ( FAILED(hr) )
      return hr;

   m_pUnitTypes = pUnitTypes; // Assignment operator calls AddRef();

   pUnitTypes->SetUnitServer( this );
   if (FAILED(pUnitTypes->InitDefaultUnits()))
   {
      m_pUnitTypes.Release();
      return E_FAIL;
   }

   // Hookup to the connection point
   hr = m_pUnitTypes.Advise( GetUnknown(), IID_IUnitTypesEventSink, &m_Cookie );
   ATLASSERT( SUCCEEDED(hr) );
   // This just created a circular reference. decrement ref count to break it
   InternalRelease(); 

   // Initalize the base units
   if ( FAILED(GetUnit(CComBSTR("Mass"),CComBSTR("kg"),&m_pMass)) )
      return E_FAIL;
   m_pMass->Release(); // make reference week

   if ( FAILED(GetUnit(CComBSTR("Length"),CComBSTR("m"),&m_pLength)) )
      return E_FAIL;
   m_pLength->Release();

   if ( FAILED(GetUnit(CComBSTR("Time"),CComBSTR("sec"),&m_pTime)) )
      return E_FAIL;
   m_pTime->Release();

   if ( FAILED(GetUnit(CComBSTR("Temperature"),CComBSTR("C"),&m_pTemp)) )
      return E_FAIL;
   m_pTemp->Release();

   if ( FAILED(GetUnit(CComBSTR("Angle"),CComBSTR("rad"),&m_pAngle)) )
      return E_FAIL;
   m_pAngle->Release();


   if ( FAILED(CComObject<CUnit>::CreateInstance( &m_pFromUnit )) )
      return E_FAIL;

   m_pFromUnit->AddRef();
   m_pToUnit = m_pFromUnit; // don't AddRef to m_pToUnit (weak/strong reference issue)

   if ( FAILED(CComObject<CUnit>::CreateInstance( &m_pConvUnit )) )
      return E_FAIL;

   m_pConvUnit->AddRef();

   return S_OK;
}

void CUnitServerImp::FinalRelease()
{
   m_pFromUnit->Release();
   m_pConvUnit->Release();

   // Increment refcount to counteract the Release in FinalConstruct
   InternalAddRef();

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( m_pUnitTypes );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IUnitTypesEventSink, &pCP );
   pCP->Unadvise( m_Cookie );

   m_pUnitTypes.Release();
}

STDMETHODIMP CUnitServerImp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUnitServer,
		&IID_IUnitConvert,
		&IID_IUnitConvert2,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CUnitServerImp::BadUnitTagError(BSTR name)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), IDS_E_BADUNITTAG, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, 256, str, W2T(name) );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return Error(oleMsg,IDH_E_BADUNITTAG, GetHelpFile(), IID_IUnitServer, UNITS_E_BADUNITTAG);
}

STDMETHODIMP CUnitServerImp::SetBaseUnits(BSTR bstrMass, BSTR bstrLength, BSTR bstrTime, BSTR bstrTemp, BSTR bstrAngle)
{
   CHECK_IN(bstrMass);
   CHECK_IN(bstrLength);
   CHECK_IN(bstrTime);
   CHECK_IN(bstrTemp);
   CHECK_IN(bstrAngle);

   // Base units can only be set once. If they have been previously set,
   // return with an error.
   if (m_bIsLocked)
      return Error( IDS_E_BASEUNITSSET,IDH_E_BASEUNITSSET, GetHelpFile(), IID_IUnitServer, UNITS_E_BASEUNITSSET );

   // If any of the fundamental base units can't be set, this entire method
   // must roll back. The RollBack object is like a smart pointer. Unless you
   // call xxx.commit(), the unit will rollback at when this method exits.
   RollBack mass(&m_pMass);
   RollBack length(&m_pLength);
   RollBack time(&m_pTime);
   RollBack temp(&m_pTemp);
   RollBack angle(&m_pAngle);

   HRESULT hr;

   // Don't call release because of weak referencing
   m_pMass = 0;
   m_pLength = 0;
   m_pTime = 0;
   m_pTemp = 0;
   m_pAngle = 0;

   hr = GetUnit( CComBSTR("Mass"), bstrMass, &m_pMass );
   if ( FAILED(hr) )
      return BadUnitTagError( bstrMass );

   hr = GetUnit( CComBSTR("Length"), bstrLength, &m_pLength );
   if ( FAILED(hr) )
      return BadUnitTagError( bstrLength );

   hr = GetUnit( CComBSTR("Time"), bstrTime, &m_pTime );
   if ( FAILED(hr) )
      return BadUnitTagError( bstrTime );

   hr = GetUnit( CComBSTR("Temperature"), bstrTemp,  &m_pTemp );
   if ( FAILED(hr) )
      return BadUnitTagError( bstrTemp );

   hr = GetUnit( CComBSTR("Angle"), bstrAngle, &m_pAngle );
   if ( FAILED(hr) )
      return BadUnitTagError( bstrAngle );

   mass.Commit();
   length.Commit();
   time.Commit();
   temp.Commit();
   angle.Commit();

   m_bIsLocked = true;

	return S_OK;
}

STDMETHODIMP CUnitServerImp::get_Mass(BSTR* pMass)
{
   CHECK_RETVAL( pMass );
   m_pMass->get_Tag( pMass );
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_Length(BSTR* pLength)
{
   CHECK_RETVAL( pLength );
   m_pLength->get_Tag( pLength );
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_Time(BSTR* pTime)
{
   CHECK_RETVAL( pTime );
   m_pTime->get_Tag( pTime );
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_Temperature(BSTR* pTemperature)
{
   CHECK_RETVAL( pTemperature );
   m_pTemp->get_Tag( pTemperature );
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_Angle(BSTR* pAngle)
{
   CHECK_RETVAL( pAngle );
   m_pAngle->get_Tag( pAngle );
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_UnitTypes(IUnitTypes** ppUnitTypes)
{
   CHECK_RETOBJ(ppUnitTypes);

   *ppUnitTypes = m_pUnitTypes;
   (*ppUnitTypes)->AddRef();
   return S_OK;
}

STDMETHODIMP CUnitServerImp::get_UnitConvert(IUnitConvert** convert)
{
   CHECK_RETOBJ(convert);
   return QueryInterface(IID_IUnitConvert,(void**)convert);
}

STDMETHODIMP CUnitServerImp::get_UnitConvert2(IUnitConvert2** convert)
{
   CHECK_RETOBJ(convert);
   return QueryInterface(IID_IUnitConvert2,(void**)convert);
}

/////////////////////////////////////////////////////////////////////////////
// IUnitConvert

STDMETHODIMP CUnitServerImp::Convert( Float64 from, BSTR fromUnit, BSTR toUnit, Float64* pTo)
{
   CHECK_IN(fromUnit);
   CHECK_IN(toUnit);
   CHECK_RETVAL(pTo);

   CComPtr<IUnit> pFromUnit;
   CComPtr<IUnit> pToUnit;

   HRESULT hr;
   hr = GetUnit( fromUnit, &pFromUnit );
   if ( FAILED(hr) )
      return BadUnitTagError(fromUnit);

   hr = GetUnit( toUnit, &pToUnit );
   if ( FAILED(hr) )
      return BadUnitTagError(toUnit);

   hr = Convert( from, pFromUnit, pToUnit, pTo );

   return hr;
}

STDMETHODIMP CUnitServerImp::ConvertToBaseUnits( Float64 val, BSTR fromUnit, Float64* pConvVal)
{
   CHECK_IN(fromUnit);
   CHECK_RETVAL(pConvVal);

   CComPtr<IUnit> pFromUnit;
   HRESULT hr;
   hr = GetUnit( fromUnit, &pFromUnit );
   if ( FAILED(hr) )
      return BadUnitTagError(fromUnit);

   hr = ConvertToBaseUnits( val, pFromUnit, pConvVal );

   return hr;
}

STDMETHODIMP CUnitServerImp::ConvertFromBaseUnits( Float64 val, BSTR toUnit, Float64* pConvVal)
{
   CHECK_IN(toUnit);
   CHECK_RETVAL(pConvVal);

   CComPtr<IUnit> pToUnit;
   HRESULT hr;

   hr = GetUnit( toUnit, &pToUnit );
   if ( FAILED(hr) )
      return BadUnitTagError(toUnit);

   hr = ConvertFromBaseUnits( val, pToUnit, pConvVal );

   return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IUnitConvert2
STDMETHODIMP CUnitServerImp::Convert( Float64 from, IUnit* pFromUnit, IUnit* pToUnit, Float64* pTo)
{
   CHECK_IN(pFromUnit);
   CHECK_IN(pToUnit);
   CHECK_RETVAL(pTo);

	// TODO: Add your implementation code here
   Float64 pre1, cf1, post1;
   Float64 pre2, cf2, post2;

   CComPtr<IUnitType> pFromUnitType;
   pFromUnit->get_UnitType( &pFromUnitType );

   CComPtr<IUnitType> pToUnitType;
   pToUnit->get_UnitType( &pToUnitType );

   if ( FAILED( check_dimensionality( pFromUnitType, pToUnitType ) ) )
   {
      return Error( IDS_E_UNITTYPEMISMATCH,IDH_E_UNITTYPEMISMATCH, GetHelpFile(), IID_IUnitServer, UNITS_E_UNITTYPEMISMATCH );
   }

   pFromUnit->get_PreTerm( &pre1 );
   pFromUnit->get_ConvFactor( &cf1 );
   pFromUnit->get_PostTerm( &post1 );
   _ASSERTE( !IsZero(cf1,1e-20) );

   pToUnit->get_PreTerm( &pre2 );
   pToUnit->get_ConvFactor( &cf2 );
   pToUnit->get_PostTerm( &post2 );
   _ASSERTE( !IsZero(cf2,1e-20) );

   // if there is not exactly one dimensionality that is exactly equal to 1,
   // then zero out the pre and post terms. (I don't know why, but it works)

   Float64 m,l,t,k,a;
   pFromUnitType->get_Mass(&m);
   pFromUnitType->get_Length(&l);
   pFromUnitType->get_Time(&t);
   pFromUnitType->get_Temperature(&k);
   pFromUnitType->get_Angle(&a);
   short cOnes = 0; // Number of dimensionalities are equal to 1
   cOnes += IsEqual(m,1.0,1e-10) ? 1 : 0;
   cOnes += IsEqual(l,1.0,1e-10) ? 1 : 0;
   cOnes += IsEqual(t,1.0,1e-10) ? 1 : 0;
   cOnes += IsEqual(k,1.0,1e-10) ? 1 : 0;
   cOnes += IsEqual(a,1.0,1e-10) ? 1 : 0;
   
   if ( cOnes != 1 )
   {
      pre1  = 0.0;
      post1 = 0.0;

      pre2  = 0.0;
      post2 = 0.0;
   }
   
   Float64 temp;

   temp = ( from + pre1 ) * cf1 + post1;
   temp = ( temp - post2 ) / cf2 - pre2;

   *pTo = temp;

	return S_OK;
}

STDMETHODIMP CUnitServerImp::ConvertToBaseUnits( Float64 val, IUnit* pFromUnit, Float64* pConvVal)
{
   HRESULT hr = S_OK;

   CComPtr<IUnitType> pUnitType;
   pFromUnit->get_UnitType( &pUnitType );

   // convert to UnitServer internal units (kg,m,s,C,rad) from the input units
   m_pToUnit->Init(this,pUnitType,0.0,1.0,0.0,CComBSTR(""),unitsSI);
   Convert( val, pFromUnit, m_pToUnit, &val );

   // Now convert to user defined base units
   Float64 dim;
   Float64 pre, cf, post;
   pUnitType->get_Mass(&dim);
   if ( !IsZero(dim) )
   {
      m_pMass->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pToUnit, m_pConvUnit, &val);
   }

   pUnitType->get_Length(&dim);
   if ( !IsZero(dim) )
   {
      m_pLength->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pToUnit, m_pConvUnit, &val);
   }

   pUnitType->get_Time(&dim);
   if ( !IsZero(dim) )
   {
      m_pTime->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pToUnit, m_pConvUnit, &val);
   }

   pUnitType->get_Angle(&dim);
   if ( !IsZero(dim) )
   {
      m_pAngle->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pToUnit, m_pConvUnit, &val);
   }

   pUnitType->get_Temperature(&dim);
   if ( !IsZero(dim) )
   {
      m_pTemp->get_PreTerm(&pre);
      m_pTemp->get_ConvFactor(&cf);
      m_pTemp->get_PostTerm(&post);
      m_pConvUnit->Init(this,pUnitType,pre,pow(cf,dim),post,CComBSTR(""),unitsSI);
      Convert(val, m_pToUnit, m_pConvUnit, &val);
   }

   *pConvVal = val;

	return S_OK;
}

STDMETHODIMP CUnitServerImp::ConvertFromBaseUnits( Float64 val, IUnit* pToUnit, Float64* pConvVal)
{
   HRESULT hr = S_OK;

   CComPtr<IUnitType> pUnitType;
   pToUnit->get_UnitType( &pUnitType );

   // convert to UnitServer internal units (kg,m,s,C,rad) from the user defined base units
   m_pFromUnit->Init(this,pUnitType,0.0,1.0,0.0,CComBSTR(""),unitsSI);
   Convert( val, m_pFromUnit, pToUnit, &val );

   // Now convert to user defined base units
   Float64 dim;
   Float64 pre, cf, post;
   pUnitType->get_Mass(&dim);
   if ( !IsZero(dim) )
   {
      m_pMass->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pConvUnit, m_pFromUnit, &val);
   }

   pUnitType->get_Length(&dim);
   if ( !IsZero(dim) )
   {
      m_pLength->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pConvUnit, m_pFromUnit, &val);
   }

   pUnitType->get_Time(&dim);
   if ( !IsZero(dim) )
   {
      m_pTime->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pConvUnit, m_pFromUnit, &val);
   }

   pUnitType->get_Angle(&dim);
   if ( !IsZero(dim) )
   {
      m_pAngle->get_ConvFactor(&cf);
      m_pConvUnit->Init(this,pUnitType,0.0,pow(cf,dim),0.0,CComBSTR(""),unitsSI);
      Convert(val, m_pConvUnit, m_pFromUnit, &val);
   }

   pUnitType->get_Temperature(&dim);
   if ( !IsZero(dim) )
   {
      m_pTemp->get_PreTerm(&pre);
      m_pTemp->get_ConvFactor(&cf);
      m_pTemp->get_PostTerm(&post);
      m_pConvUnit->Init(this,pUnitType,pre,pow(cf,dim),post,CComBSTR(""),unitsSI);
      Convert(val, m_pConvUnit, m_pFromUnit, &val);
   }

   *pConvVal = val;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helper methods

HRESULT check_dimensionality( IUnitType* pFromUnitType, IUnitType* pToUnitType )
{
   Float64 m1, l1, t1, k1, a1;
   Float64 m2, l2, t2, k2, a2;

   pFromUnitType->get_Mass(&m1);
   pFromUnitType->get_Length(&l1);
   pFromUnitType->get_Time(&t1);
   pFromUnitType->get_Temperature(&k1);
   pFromUnitType->get_Angle(&a1);

   pToUnitType->get_Mass(&m2);
   pToUnitType->get_Length(&l2);
   pToUnitType->get_Time(&t2);
   pToUnitType->get_Temperature(&k2);
   pToUnitType->get_Angle(&a2);

   if ( m1 != m2 )
      return E_FAIL;
   if ( l1 != l2 )
      return E_FAIL;
   if ( t1 != t2 )
      return E_FAIL;
   if ( k1 != k2 )
      return E_FAIL;
   if ( a1 != a2 )
      return E_FAIL;

   return S_OK;
}
