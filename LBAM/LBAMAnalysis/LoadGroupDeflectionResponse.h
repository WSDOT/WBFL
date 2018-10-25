///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LoadGroupDeflectionResponse.h : Declaration of the CLoadGroupDeflectionResponse

#ifndef __LOADGROUPDEFLECTIONRESPONSE_H_
#define __LOADGROUPDEFLECTIONRESPONSE_H_

#include "resource.h"       // main symbols
#include "LoadGroupResponse.h"
#include "LBAMAnalysisCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadGroupDeflectionResponse
class ATL_NO_VTABLE CLoadGroupDeflectionResponse : 
	public CComCoClass<CLoadGroupDeflectionResponse, &CLSID_LoadGroupDeflectionResponse>,
   public CLoadGroupResponse,
   public IObjectSafetyImpl<CLoadGroupDeflectionResponse,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IConnectionPointContainerImpl<CLoadGroupDeflectionResponse>
{
public:
   CLoadGroupDeflectionResponse()
	{
      // internal model will calculate response based on deflection properties
      m_ForForces=false;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADGROUPDEFLECTIONRESPONSE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadGroupDeflectionResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(CLoadGroupResponse)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadGroupDeflectionResponse)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadGroupDeflectionResponse
public:

protected:
   virtual HRESULT DealWithMyExceptions()
   {
      //try
      //{
         // Assume that whatever got thrown means that our model and results are no good
         ClearModels();
      //}
      //catch(...)
      //{
      //   ATLASSERT(false); // ClearModels should not throw
      //} // just make sure no exceptions escape 

      return DealWithExceptions(this, IID_ILoadGroupResponse);
   }

};

#endif //__LOADGROUPDEFLECTIONRESPONSE_H_
