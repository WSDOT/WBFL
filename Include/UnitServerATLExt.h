///////////////////////////////////////////////////////////////////////
// UnitServerATLExt.h - ATL Extensions for implementing UnitServer interfaces
// Copyright © 1999-2022  Washington State Department of Transportation
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_UNITSERVERATLEXT_H_
#define INCLUDED_UNITSERVERATLEXT_H_

#include <ATLExt.h>

// Implementation of the ISupportUnitServer interface
//
// To use this implementation of ISupportUnitServer, do the following
// 1. Derive you class from ISupportUnitServerImpl
// 2. Add ISupportUnitServer to your interface map and add an entry for the dispatch interface
//
// Example
//
// class ATL_NO_VTABLE CMyClass : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMyClass, &CLSID_MyClass>,
// public ISupportUnitServerImpl<CMyClass,&LIBID_MyLib>,
//	public ... Other base classes
// {
//    BEGIN_COM_MAP(MyClass)
//	      COM_INTERFACE_ENTRY(... Other interfaces)
//       COM_INTERFACE_ENTRY(ISupportUnitServer)
//	      COM_INTERFACE_ENTRY2(IDispatch,ISupportUnitServer)
//	      COM_INTERFACE_ENTRY(... Other interfaces)
//    END_COM_MAP()
//
//    Other declarations
//
// };


#include <WBFLUnitServer.h>
template <class T, const GUID* plibid = &CComModule::m_libid>
class ATL_NO_VTABLE ISupportUnitServerImpl :
	public IDispatchImpl<ISupportUnitServer, &IID_ISupportUnitServer, plibid>
{
public:
   ISupportUnitServerImpl() { m_bIsUnitServerSet = false; }

private:
   bool m_bIsUnitServerSet;

protected:
   CComPtr<IUnitServer> m_pUnitServer;

// ISupportUnitServer
public:
   STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** pVal )
   {
      CHECK_RETOBJ(pVal);
      m_pUnitServer.QueryInterface(pVal);
      return S_OK;
   }

   STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* newVal )
   {
      CHECK_IN(newVal);

      if ( m_bIsUnitServerSet )
         return CComCoClass<T>::Error(_T("Unit Server already set"),IID_ISupportUnitServer,UNITS_E_UNITSERVERSET);

      m_pUnitServer = newVal;
      m_bIsUnitServerSet = true;

      return S_OK;
   }
};

#endif // INCLUDED_UNITSERVERATLEXT_H_