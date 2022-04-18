///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_DRAGDATA_H_
#define INCLUDED_DRAGDATA_H_
#pragma once

interface iDisplayObject;

interface iDragDataSource : public IUnknown
{
   STDMETHOD_(void,SetDataObject)(COleDataObject* pDataObj) PURE;
   STDMETHOD_(void,PrepareFormat)(UINT cfFormat) PURE;
   STDMETHOD_(UINT,Read)(UINT cfFormat,void* pBuf,UINT nMax) PURE;
};

interface iDragDataSink : public IUnknown
{
   STDMETHOD_(void,CreateFormat)(UINT cfFormat) PURE;
   STDMETHOD_(BOOL,Write)(UINT cfFormat,void* pBuf,UINT nMax) PURE;
};

// Implemented by client applications to provide data to
// be used in OLE data transfer
interface iDragData : public IUnknown
{
   // Returns an integer that identifies the data format
   STDMETHOD_(UINT,Format)() PURE;

   // Called by the framework just before a drag/drop is about to
   // begin. Write what ever data you want to be included in the 
   // data transfer to the DragDataSink.
   STDMETHOD_(BOOL,PrepareForDrag)(iDisplayObject* pDO,iDragDataSink* pSink) PURE;

   // Called by the framework when the display object is dropped.
   // This is your opportunity to read the data you stored in PrepareForDrag
   STDMETHOD_(void,OnDrop)(iDisplayObject* pDO,iDragDataSource* pSource) PURE;
};

#endif // INCLUDED_DRAGDATA_H_