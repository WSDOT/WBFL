// DocUnitSystem.cpp : Implementation of CDocUnitSystem
#include "stdafx.h"
#include "WbflUnitServer.h"
#include "DocUnitSystem.h"
#include "Helper.h"



/////////////////////////////////////////////////////////////////////////////
// CDocUnitSystem

HRESULT CDocUnitSystem::BadDisplayUnitGroupError(BSTR name)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), IDS_E_BADDISPLAYUNITGROUP, str, 256);
   TCHAR msg[256];
   int cOut = _stprintf_s( msg, str, W2T(name) );
   _ASSERTE( cOut < 256 );
   CComBSTR oleMsg(msg);
   return CComCoClass<CDocUnitSystem>::Error(oleMsg,IDH_E_BADDISPLAYUNITGROUP, GetHelpFile(), IID_IDocUnitSystem, UNITS_E_BADDISPLAYUNITGROUP);
}

HRESULT CDocUnitSystem::FinalConstruct()
{
   HRESULT hr = S_OK;

   CComObject<CUnitModeController>* pUMC;
   hr = CComObject<CUnitModeController>::CreateInstance(&pUMC);
   if ( FAILED(hr) )
      return E_FAIL;

   m_pUMC = pUMC;

   m_pUMC.Advise(GetUnknown(),IID_IUnitModeControllerEvents,&m_dwUMCCookie);
   InternalRelease(); // Break strong reference to avoid circular reference
   return S_OK;
}

void CDocUnitSystem::FinalRelease()
{
   InternalAddRef(); // Counteract InternalRelease() in FinalConstruct();

   CComQIPtr<IConnectionPointContainer> pCPC( m_pUMC );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IUnitModeControllerEvents, &pCP );
   pCP->Unadvise( m_dwUMCCookie );
}

STDMETHODIMP CDocUnitSystem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDocUnitSystem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDocUnitSystem::get_UnitMode(UnitModeType *pVal)
{
   CHECK_RETVAL(pVal);
   HRESULT hr = m_pUMC->get_UnitMode(pVal);
   if ( FAILED(hr) )
      return hr;

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::put_UnitMode(UnitModeType newVal)
{
   HRESULT hr = m_pUMC->put_UnitMode(newVal);
   if ( FAILED(hr) )
      return hr;

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::get_UnitModeController(IUnitModeController **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_pUMC;
   (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::get_AppUnitSystem(IAppUnitSystem **pVal)
{
   CHECK_RETOBJ(pVal);

   (*pVal) = m_pAppUnitSys;

   // If this DocUnitSystem hasn't been associated with an AppUnitSystem
   // yet, a call to AddRef on m_pAppUnitSys (a nullptr pointer) will cause
   // an access violation. Check the pointer first.
   if ( *pVal )
      (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::putref_AppUnitSystem(IAppUnitSystem *newVal)
{
   CHECK_IN(newVal);
   m_pAppUnitSys = newVal;

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::ConvertToDisplayUnits(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result)
{
   // Helper method to make it easy for users to convert a value from base units
   // to display units
   CHECK_IN(group);
   CHECK_RETVAL(result);

   if ( m_pAppUnitSys == nullptr )
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_APPUNITSYSNOTSET,IDH_E_APPUNITSYSNOTSET, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_APPUNITSYSNOTSET);

   CComPtr<IDisplayUnitMgr2> pDUM;
   m_pAppUnitSys->get_DisplayUnitMgr(&pDUM);

   CComPtr<IDisplayUnitGroup> pGroup;
   HRESULT hr = pDUM->get_Item(group,&pGroup);
   if (FAILED(hr))
      return BadDisplayUnitGroupError(group);

   UnitModeType um;
   m_pUMC->get_UnitMode(&um);
   CComPtr<IDisplayUnit> pDispUnit;
   hr = pGroup->get_Default(um,&pDispUnit);
   if (FAILED(hr))
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_DEFAULTNOTFOUND,IDH_E_DEFAULTNOTFOUND, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_DEFAULTNOTFOUND);

   CComPtr<IUnit> pUnit;
   pDispUnit->get_Unit(&pUnit);
   ATLASSERT( SUCCEEDED(hr) && pUnit != 0 );

   CComPtr<IUnitServer> pUnitServer;
   pUnit->get_UnitServer(&pUnitServer);

   CComQIPtr<IUnitConvert2> pConv(pUnitServer);
   pConv->ConvertFromBaseUnits(value,pUnit,result);

   return S_OK;
}

STDMETHODIMP CDocUnitSystem::ConvertFromDisplayUnits(/*[in]*/ Float64 value,/*[in]*/ BSTR group,/*[out,retval]*/Float64* result)
{
   // Helper method to make it easy for users to convert a value from display units
   // to base units
   CHECK_IN(group);
   CHECK_RETVAL(result);

   if ( m_pAppUnitSys == nullptr )
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_APPUNITSYSNOTSET,IDH_E_APPUNITSYSNOTSET, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_APPUNITSYSNOTSET);

   CComPtr<IDisplayUnitMgr2> pDUM;
   m_pAppUnitSys->get_DisplayUnitMgr(&pDUM);

   CComPtr<IDisplayUnitGroup> pGroup;
   HRESULT hr = pDUM->get_Item(group,&pGroup);
   if (FAILED(hr))
      return BadDisplayUnitGroupError(group);

   UnitModeType um;
   m_pUMC->get_UnitMode(&um);
   CComPtr<IDisplayUnit> pDispUnit;
   hr = pGroup->get_Default(um,&pDispUnit);
   if (FAILED(hr))
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_DEFAULTNOTFOUND,IDH_E_DEFAULTNOTFOUND, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_DEFAULTNOTFOUND);

   CComPtr<IUnit> pUnit;
   pDispUnit->get_Unit(&pUnit);
   ATLASSERT( SUCCEEDED(hr) && pUnit != 0 );

   CComPtr<IUnitServer> pUnitServer;
   pUnit->get_UnitServer(&pUnitServer);

   CComQIPtr<IUnitConvert2> pConv(pUnitServer);
   pConv->ConvertToBaseUnits(value,pUnit,result);

   return S_OK;
}

STDMETHODIMP CDocUnitSystem::get_Tag(BSTR group,BSTR* tag)
{
   // Helper method to make it easy for users to get the tag of the
   // default unit
   CHECK_IN(group);
   CHECK_RETSTRING(tag);

   if ( m_pAppUnitSys == nullptr )
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_APPUNITSYSNOTSET,IDH_E_APPUNITSYSNOTSET, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_APPUNITSYSNOTSET);

   CComPtr<IDisplayUnitMgr2> pDUM;
   m_pAppUnitSys->get_DisplayUnitMgr(&pDUM);

   CComPtr<IDisplayUnitGroup> pGroup;
   HRESULT hr = pDUM->get_Item(group,&pGroup);
   if (FAILED(hr))
      return BadDisplayUnitGroupError(group);

   UnitModeType um;
   m_pUMC->get_UnitMode(&um);
   CComPtr<IDisplayUnit> pDispUnit;
   hr = pGroup->get_Default(um,&pDispUnit);
   if (FAILED(hr))
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_DEFAULTNOTFOUND,IDH_E_DEFAULTNOTFOUND, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_DEFAULTNOTFOUND);

   CComPtr<IDisplayUnitFormatter> pFormatter;
   hr = pDispUnit->get_Formatter(&pFormatter);
   ATLASSERT( SUCCEEDED(hr) && pFormatter != 0 );
   VARIANT_BOOL bUsesTag;
   pFormatter->get_UsesTag(&bUsesTag);
   if ( bUsesTag == VARIANT_FALSE )
   {
      *tag = 0; // Null is value for representing empty strings
      return S_OK;
   }

   CComPtr<IUnit> pUnit;
   pDispUnit->get_Unit(&pUnit);
   ATLASSERT( SUCCEEDED(hr) && pUnit != 0 );
   pUnit->get_Tag(tag);

	return S_OK;
}

STDMETHODIMP CDocUnitSystem::Format(Float64 val,BSTR bstrGroup,VARIANT_BOOL bShowUnitTag,BSTR* fmtString)
{
   // Helper method to make it easy for users to create formatted unit strings.
   // Creates a format string for the default display unit for the current unit mode,
   //   for the specifed display unit group. The alternative to this method is for
   //   the user to get the DisplayUnitGroup object and then find the default unit
   //   manually. This is such a common operation, it is implemented on the display
   //   unit manager.
   CHECK_IN(bstrGroup);
   CHECK_RETSTRING(fmtString);

   if ( m_pAppUnitSys == nullptr )
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_APPUNITSYSNOTSET,IDH_E_APPUNITSYSNOTSET, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_APPUNITSYSNOTSET);

   CComPtr<IDisplayUnitMgr2> pDUM;
   m_pAppUnitSys->get_DisplayUnitMgr(&pDUM);

   CComPtr<IDisplayUnitGroup> pGroup;
   HRESULT hr = pDUM->get_Item(bstrGroup,&pGroup);
   if (FAILED(hr))
      return BadDisplayUnitGroupError(bstrGroup);

   UnitModeType um;
   m_pUMC->get_UnitMode(&um);
   CComPtr<IDisplayUnit> pDispUnit;
   hr = pGroup->get_Default(um,&pDispUnit);
   if (FAILED(hr))
      return CComCoClass<CDocUnitSystem>::Error(IDS_E_DEFAULTNOTFOUND,IDH_E_DEFAULTNOTFOUND, GetHelpFile(),IID_IDocUnitSystem,UNITS_E_DEFAULTNOTFOUND);

   pDispUnit->Format(val,bShowUnitTag,fmtString);

	return S_OK;
}
