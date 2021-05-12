///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// DragDataImpl.h: interface for the CDragDataImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGDATAIMPL_H__791A55EF_E8D7_11D4_8B85_006097C68A9C__INCLUDED_)
#define AFX_DRAGDATAIMPL_H__791A55EF_E8D7_11D4_8B85_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#include <afxadv.h>
#include <map>

class ATL_NO_VTABLE CDragDataSourceImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDragDataSourceImpl, &CLSID_DragDataSource>,
   public iDragDataSource
{
public:
	CDragDataSourceImpl();
	virtual ~CDragDataSourceImpl();


DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DRAGDATASOURCE)

BEGIN_COM_MAP(CDragDataSourceImpl)
	COM_INTERFACE_ENTRY(iDragDataSource)
END_COM_MAP()

   // iDragDataSource Implementation
   STDMETHOD_(void,SetDataObject)(COleDataObject* pDataObj) override;
   STDMETHOD_(void,PrepareFormat)(UINT cfFormat) override;
   STDMETHOD_(UINT,Read)(UINT format,void* pBuf,UINT nMax) override;

private:
   class DataSource
   {
   public:
      CArchive* m_pArchive;
      CMemFile* m_pMemFile;
      HGLOBAL m_hGlobal;

      DataSource(HGLOBAL hMem);
      ~DataSource();
   };

   COleDataObject* m_pDataObj;
   std::map<UINT,DataSource*> m_Sources;
};

class ATL_NO_VTABLE CDragDataSinkImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDragDataSinkImpl, &CLSID_DragDataSink>,
   public iDragDataSink
{
public:
	CDragDataSinkImpl();
	virtual ~CDragDataSinkImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DRAGDATASINK)

BEGIN_COM_MAP(CDragDataSinkImpl)
	COM_INTERFACE_ENTRY(iDragDataSink)
END_COM_MAP()

   // iDragDataSink Implementation
   STDMETHOD_(void,CreateFormat)(UINT cfFormat) override;
   STDMETHOD_(BOOL,Write)(UINT cfFormat,void* pBuf,UINT nMax) override;

   // Puts the data onto the clipboard
   void CacheGlobalData(COleDataSource* pODS);

private:
   class DataSink
   {
   public:
      CArchive* m_pArchive;
      CSharedFile* m_pSharedFile;

      DataSink();
     ~DataSink();
   };
   std::map<UINT,DataSink*> m_Sinks;
};

#endif // !defined(AFX_DRAGDATAIMPL_H__791A55EF_E8D7_11D4_8B85_006097C68A9C__INCLUDED_)
