///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_IDATASET2D_H_
#define INCLUDED_IDATASET2D_H_
#pragma once

interface IPoint2d;

// {3E920A2D-BE1E-4e85-B4A5-A1875B387CF7}
DEFINE_GUID(IID_iDataSet2d, 
0x3e920a2d, 0xbe1e, 0x4e85, 0xb4, 0xa5, 0xa1, 0x87, 0x5b, 0x38, 0x7c, 0xf7);
struct __declspec(uuid("{3E920A2D-BE1E-4e85-B4A5-A1875B387CF7}")) iDataSet2d;

interface iDataSet2d : public IUnknown
{
   STDMETHOD_(HRESULT,get_Item)(CollectionIndexType idx, IPoint2d** pVal) PURE;
   STDMETHOD_(void,get_Count)(CollectionIndexType *pVal) PURE;
   STDMETHOD_(void,Add)(IPoint2d *pVal) PURE;
   STDMETHOD_(HRESULT,Insert)(CollectionIndexType index, IPoint2d *pVal) PURE;
   STDMETHOD_(HRESULT,Remove)(CollectionIndexType index) PURE;
   STDMETHOD_(void,Clear)() PURE;
};

#endif // INCLUDED_IDATASET2D_H_