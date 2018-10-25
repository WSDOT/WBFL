///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_DROPSITE_H_
#define INCLUDED_DROPSITE_H_
#pragma once

interface iDisplayObject;

interface iDropSite : public IUnknown
{
   STDMETHOD_(DROPEFFECT,CanDrop)(COleDataObject* pDataObject,DWORD dwKeyState,IPoint2d* point) PURE;
   STDMETHOD_(void,OnDropped)(COleDataObject* pDataObject,DROPEFFECT dropEffect,IPoint2d* point) PURE;

   STDMETHOD_(void,SetDisplayObject)(iDisplayObject* pDO) PURE;
   STDMETHOD_(void,GetDisplayObject)(iDisplayObject** dispObj) PURE;

   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) PURE;
};

#endif // INCLUDED_DROPSITE_H_