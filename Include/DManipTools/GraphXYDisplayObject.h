///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_IGRAPHXYDISPLAYOBJECT_H_
#define INCLUDED_IGRAPHXYDISPLAYOBJECT_H_
#pragma once

#include "DManipToolsTypes.h"

interface IPoint2d;
interface iDataSet2d;

// {12761816-B9BD-4f41-9BFB-8713C252C3DB}
DEFINE_GUID(IID_iDataPointFactory, 
0x12761816, 0xb9bd, 0x4f41, 0x9b, 0xfb, 0x87, 0x13, 0xc2, 0x52, 0xc3, 0xdb);
struct __declspec(uuid("{12761816-B9BD-4f41-9BFB-8713C252C3DB}")) iDataPointFactory;
interface iDataPointFactory : public IUnknown
{
   // creates a data point at the specified location. 
   // The object created must also support the  iConnectable interface
   STDMETHOD_(HRESULT,CreateDataPoint)(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY, iDisplayObject** dataPoint) PURE;

   // get color for lines between data points
   STDMETHOD_(COLORREF,get_Color)() PURE;
};

// {460711D6-1BC2-4545-99F5-EBF249AF8417}
DEFINE_GUID(IID_iGraphXyDataProvider, 
0x460711d6, 0x1bc2, 0x4545, 0x99, 0xf5, 0xeb, 0xf2, 0x49, 0xaf, 0x84, 0x17);
struct __declspec(uuid("{460711D6-1BC2-4545-99F5-EBF249AF8417}")) iGraphXyDataProvider;
interface iGraphXyDataProvider : public IUnknown
{
   STDMETHOD_(void,put_DataSet)(iDataSet2d* dataSet) PURE;
   STDMETHOD_(void,get_DataSet)(iDataSet2d** dataSet) PURE;

   STDMETHOD_(void,put_DataPointFactory)(iDataPointFactory* factory) PURE;
   STDMETHOD_(void,get_DataPointFactory)(iDataPointFactory** factory) PURE;
};

// {F1FA6B3B-08E7-46f0-A350-BD6D2BEDCF01}
DEFINE_GUID(IID_iGraphXyDisplayObject, 
0xf1fa6b3b, 0x8e7, 0x46f0, 0xa3, 0x50, 0xbd, 0x6d, 0x2b, 0xed, 0xcf, 0x1);
struct __declspec(uuid("{F1FA6B3B-08E7-46f0-A350-BD6D2BEDCF01}")) iGraphXyDisplayObject;
interface iGraphXyDisplayObject : public IUnknown
{
   STDMETHOD_(void,get_GraphBounds)( IRect2d* *pVal) PURE;
   STDMETHOD_(void,put_GraphBounds)(IRect2d* newVal) PURE;
   STDMETHOD_(void,get_Title)(BSTR *pVal) PURE;
   STDMETHOD_(void,put_Title)(BSTR newVal) PURE;
   STDMETHOD_(void,DataCount)(CollectionIndexType *pVal) PURE;
   STDMETHOD_(void,AddData)(iGraphXyDataProvider* data) PURE;
   STDMETHOD_(HRESULT,GetData)(CollectionIndexType idx, iGraphXyDataProvider** data) PURE;
   STDMETHOD_(HRESULT,Commit)() PURE;
   STDMETHOD_(HRESULT,ClearData)() PURE;
   STDMETHOD_(void,get_NumberOfMajorIncrements)(CollectionIndexType *pVal) PURE;
   STDMETHOD_(HRESULT,put_NumberOfMajorIncrements)(CollectionIndexType newVal) PURE;
   STDMETHOD_(void,get_DoDisplayAxisValues)(BOOL *pVal) PURE;
   STDMETHOD_(void,put_DoDisplayAxisValues)(BOOL newVal) PURE;
   STDMETHOD_(void,get_DoDisplayGrid)(BOOL *pVal) PURE;
   STDMETHOD_(void,put_DoDisplayGrid)(BOOL newVal) PURE;
};

#endif 