///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// ConnectorImpl.h: interface for the CConnectorImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTORIMPL_H__D88A0196_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
#define AFX_CONNECTORIMPL_H__D88A0196_DCD4_11D4_8B74_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class ATL_NO_VTABLE CConnectorImpl : public iConnector,
                                     public iPlugEvents
{
public:
	CConnectorImpl();
	virtual ~CConnectorImpl();

   HRESULT FinalConstruct();

   // iConnector
   STDMETHOD_(void,GetStartPlug)(iPlug** plug);
   STDMETHOD_(void,GetEndPlug)(iPlug** plug);

   // iPlugListener
   STDMETHOD_(void,Notify)(iPlug* plug);

private:
   CComPtr<iPlug> m_pStart;
   CComPtr<iPlug> m_pEnd;
};

#endif // !defined(AFX_CONNECTORIMPL_H__D88A0196_DCD4_11D4_8B74_006097C68A9C__INCLUDED_)
