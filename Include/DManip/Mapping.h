///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_MAPPING_H_
#define INCLUDED_MAPPING_H_
#pragma once

interface iMapping : public IUnknown
{
   // Set up text scaling factors in the DC
   // this method should be called from OnPrepareDC in your view
   // and it must be cleaned up after drawing by calling CleanUpDC
   STDMETHOD_(void,PrepareDC)(CDC* dc) PURE;
   STDMETHOD_(void,CleanUpDC)(CDC* dc) PURE;
   // Print DC's must be cleaned up by this call from CView::OnEndPrinting
   STDMETHOD_(void,CleanUpPrintDC)(CDC* dc) PURE;

   // Set up world extents. mapping is to logical extents,
   STDMETHOD_(void,SetWorldExt)(Float64 wx,Float64 wy) PURE;
   STDMETHOD_(void,SetWorldExt)(ISize2d* wExt) PURE;
   STDMETHOD_(void,GetWorldExt)(Float64* wx,Float64* wy) PURE;
   STDMETHOD_(void,GetWorldExt)(ISize2d* *wExt) PURE;

   STDMETHOD_(void,SetWorldOrg)(Float64 wx,Float64 wy) PURE;
   STDMETHOD_(void,SetWorldOrg)(IPoint2d* wOrg) PURE;
   STDMETHOD_(void,GetWorldOrg)(Float64* wx,Float64* wy) PURE;
   STDMETHOD_(void,GetWorldOrg)(IPoint2d* *wOrg) PURE;

   STDMETHOD_(void,SetLogicalOrg)(LONG lx,LONG ly) PURE;
   STDMETHOD_(void,GetLogicalOrg)(LONG* lx,LONG* ly) PURE;
   STDMETHOD_(void,SetLogicalExt)(LONG lx,LONG ly) PURE;
   STDMETHOD_(void,GetLogicalExt)(LONG* lx,LONG* ly) PURE;
   STDMETHOD_(void,GetAdjustedLogicalExt)(LONG* lx,LONG* ly) PURE;
   STDMETHOD_(void,GetAdjustedWorldExt)(Float64* dx,Float64* dy) PURE;

   STDMETHOD_(void,SetMappingMode)(DManip::MapMode mm) PURE;
   STDMETHOD_(DManip::MapMode,GetMappingMode)() PURE;

   STDMETHOD_(void,SetRotation)(Float64 cx,Float64 cy,Float64 angle) PURE;
   STDMETHOD_(void,SetRotation)(IPoint2d* c,Float64 angle) PURE;
   STDMETHOD_(void,GetRotation)(Float64* cx,Float64* cy,Float64* angle) PURE;
};

#endif // INCLUDED_MAPPING_H_