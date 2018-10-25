///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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

// ZoomRectTask.h: interface for the CZoomRectTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOOMRECTTASK_H__5D499BF4_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_ZOOMRECTTASK_H__5D499BF4_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

interface iZoomRectTask : public IUnknown
{
	STDMETHOD_(void,FSMError)(LPCTSTR t,LPCTSTR s) PURE;
	STDMETHOD_(void,ZoomRect)() PURE;
   STDMETHOD_(void,RecordFirstPoint)() PURE;
   STDMETHOD_(void,ClearRect)() PURE;
	STDMETHOD_(void,TrackRect)() PURE;
	STDMETHOD_(void,InitTask)() PURE;
   STDMETHOD_(void,Cancel)() PURE;
};

#endif // !defined(AFX_ZOOMRECTTASK_H__5D499BF4_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
