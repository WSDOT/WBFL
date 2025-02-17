///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright � 1999-2025  Washington State Department of Transportation
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

// GraphXyDisplayObject.h : Declaration of the CGraphXyDisplayObject

#ifndef __GRAPHXYDISPLAYOBJECT_H_
#define __GRAPHXYDISPLAYOBJECT_H_
#pragma once

#include "resource.h"       // main symbols

class GraphMapper;

/////////////////////////////////////////////////////////////////////////////
// CGraphXyDisplayObject
class ATL_NO_VTABLE CGraphXyDisplayObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CGraphXyDisplayObject,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CGraphXyDisplayObject, &CLSID_GraphXyDisplayObject>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGraphXyDisplayObject>,
	public iGraphXyDisplayObject
{
public:
   CGraphXyDisplayObject();

DECLARE_REGISTRY_RESOURCEID(IDR_GRAPHXYDISPLAYOBJECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CGraphXyDisplayObject)
	COM_INTERFACE_ENTRY(iGraphXyDisplayObject)
   // this object is a CompositeDisplayObject
   COM_INTERFACE_ENTRY_AGGREGATE(IID_iDisplayObject, m_pDisplayObject)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_iCompositeDisplayObject, m_pDisplayObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP() 
BEGIN_CONNECTION_POINT_MAP(CGraphXyDisplayObject)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGraphXyDisplayObject
public:
   STDMETHOD_(void,get_GraphBounds)( IRect2d* *pVal) override;
   STDMETHOD_(void,put_GraphBounds)(IRect2d* newVal) override;
   STDMETHOD_(void,get_Title)(BSTR *pVal) override;
   STDMETHOD_(void,put_Title)(BSTR newVal) override;
   STDMETHOD_(void,DataCount)(IndexType *pVal) override;
   STDMETHOD_(void,AddData)(iGraphXyDataProvider* dataSet) override;
   STDMETHOD_(HRESULT,GetData)(IndexType idx, iGraphXyDataProvider** dataSet) override;
   STDMETHOD_(HRESULT,Commit)() override;
   STDMETHOD_(HRESULT,ClearData)() override;
   STDMETHOD_(void,get_NumberOfMajorIncrements)(IndexType *pVal) override;
   STDMETHOD_(HRESULT,put_NumberOfMajorIncrements)(IndexType newVal) override;
   STDMETHOD_(void,get_DoDisplayAxisValues)(BOOL *pVal) override;
   STDMETHOD_(void,put_DoDisplayAxisValues)(BOOL newVal) override;
   STDMETHOD_(void,get_DoDisplayGrid)(BOOL *pVal) override;
   STDMETHOD_(void,put_DoDisplayGrid)(BOOL newVal) override;


   HRESULT FinalConstruct();
   void FinalRelease();

   IUnknown* m_pDisplayObject;

   CComPtr<IRect2d> m_GraphBounds;     // rectangle where graph is displayed in view
   CComBSTR         m_Title;
   BOOL     m_DoDisplayAxisValues;
   BOOL     m_DoDisplayGrid;
   IndexType m_NumberOfMajorIncrements;

   using DataSetHolder = CComPtr<iGraphXyDataProvider>;
   using DataSetCollection = std::vector< DataSetHolder >;
   using DataSetIterator = DataSetCollection::iterator;
   DataSetCollection                     m_DataSets;

private:
   long                                 m_NumDos; // number of display objects

private:
   HRESULT RebuildDisplayObjects();
   void AddMyDisplayObject(iDisplayObject* pdo);
   void ClearDisplayObjects();
   HRESULT DrawAxis(GraphMapper& mapper);
   HRESULT DrawCurves(GraphMapper& mapper);
   HRESULT DrawGraph(Float64 t, Float64 l, Float64 r, Float64 b);
   HRESULT GetCurveBoundary(Float64* t, Float64* l, Float64* r, Float64* b);
   HRESULT DrawAxisLine(Float64 startX, Float64 startY, Float64 endX, Float64 endY, UINT width=1);
   HRESULT DrawString(std::_tstring& string, Float64 wx, Float64 wy, UINT textAlign);
};

#endif //__GRAPHXYDISPLAYOBJECT_H_
