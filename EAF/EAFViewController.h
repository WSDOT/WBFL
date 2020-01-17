///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

#pragma once

#include <EAF\EAFApp.h>

// {9D3C4CBC-019B-41BA-A6A2-78387ECA8D9D}
DEFINE_GUID(CLSID_EAFViewController,
   0x9d3c4cbc, 0x19b, 0x41ba, 0xa6, 0xa2, 0x78, 0x38, 0x7e, 0xca, 0x8d, 0x9d);

class ATL_NO_VTABLE CEAFViewController :
   public CComObjectRootEx<CComSingleThreadModel>,
   //public CComRefCountTracer<CEAFDocProxyAgent,CComObjectRootEx<CComSingleThreadModel> >,
   public CComCoClass<CEAFViewController, &CLSID_EAFViewController>,
   public IEAFViewController
{
public:
   CEAFViewController();
   virtual ~CEAFViewController();

   void Init(CMDIChildWnd* pFrame);

   BEGIN_COM_MAP(CEAFViewController)
      COM_INTERFACE_ENTRY(IEAFViewController)
   END_COM_MAP()


// IEAFViewController
public:
   virtual bool IsOpen() const override;

   // Closes the view
   virtual void Close() override;

   // implement later....
   //virtual void Move(INT x, INT y) = 0;
   //virtual void Size(INT x, INT y) = 0;
   //virtual void GetSize() = 0;
   //virtual void GetPosition() = 0;
   //virtual void GetState() = 0;
   virtual void Minimize() override;
   virtual void Maximize() override;
   virtual void Restore() override;

protected:
   CMDIChildWnd* m_pFrame;
};
