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

// DragDataImpl.cpp: implementation of the CDragDataImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "DragDataImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDragDataSourceImpl::CDragDataSourceImpl()
{
}

CDragDataSourceImpl::~CDragDataSourceImpl()
{
   std::map<UINT,DataSource*>::iterator iter(m_Sources.begin());
   std::map<UINT,DataSource*>::iterator end(m_Sources.end());
   for ( ; iter != end; iter++ )
   {
      DataSource* pSource = (*iter).second;
      delete pSource;
   }
   m_Sources.clear();
}

STDMETHODIMP_(void) CDragDataSourceImpl::SetDataObject(COleDataObject* pDataObj)
{
   m_pDataObj = pDataObj;
}

STDMETHODIMP_(void) CDragDataSourceImpl::PrepareFormat(UINT cfFormat)
{
   if ( !m_pDataObj->IsDataAvailable(cfFormat) )
      return;

   FORMATETC fe;
   fe.cfFormat = cfFormat;
   fe.tymed = TYMED_HGLOBAL;
   fe.lindex = -1;
   fe.dwAspect = DVASPECT_CONTENT;
   fe.ptd = nullptr;

   HGLOBAL hGlobal = m_pDataObj->GetGlobalData(cfFormat,&fe);
   DataSource* pSource = new DataSource(hGlobal);
   m_Sources.insert(std::make_pair(cfFormat,pSource));
}

STDMETHODIMP_(UINT) CDragDataSourceImpl::Read(UINT cfFormat,void* pBuf,UINT nMax)
{
   std::map<UINT,DataSource*>::iterator found = m_Sources.find(cfFormat);
   if ( found == m_Sources.end() )
      return 0; // Format not found

   DataSource* pSource = (*found).second;
   return pSource->m_pArchive->Read(pBuf,nMax);
}

/////////////////////////////////////////////////////////

CDragDataSinkImpl::CDragDataSinkImpl()
{
}

CDragDataSinkImpl::~CDragDataSinkImpl()
{
   std::map<UINT,DataSink*>::iterator iter(m_Sinks.begin());
   std::map<UINT,DataSink*>::iterator end(m_Sinks.end());
   for ( ; iter != end; iter++ )
   {
      DataSink* pSink = (*iter).second;
      delete pSink;
   }
   m_Sinks.clear();
}

STDMETHODIMP_(void) CDragDataSinkImpl::CreateFormat(UINT cfFormat)
{
   std::map<UINT,DataSink*>::iterator found = m_Sinks.find(cfFormat);
   if ( found != m_Sinks.end() )
      return; // Format was previously created

   DataSink* pSink = new DataSink;
   m_Sinks.insert(std::make_pair(cfFormat,pSink));
}

STDMETHODIMP_(BOOL) CDragDataSinkImpl::Write(UINT cfFormat,void* pBuf,UINT nMax)
{
   std::map<UINT,DataSink*>::iterator found = m_Sinks.find(cfFormat);
   if ( found == m_Sinks.end() )
      return FALSE; // Sink not found

   DataSink* pSink = (*found).second;
   try
   {
      pSink->m_pArchive->Write(pBuf,nMax);
   }
   catch(...)
   {
      return FALSE;
   }

   return TRUE;
}

void CDragDataSinkImpl::CacheGlobalData(COleDataSource* pODS)
{
   std::map<UINT,DataSink*>::iterator iter(m_Sinks.begin());
   std::map<UINT,DataSink*>::iterator end(m_Sinks.end());
   for ( ; iter != end; iter++ )
   {
      UINT cf = (*iter).first;
      DataSink* pSink = (*iter).second;

      pSink->m_pArchive->Close();
      HGLOBAL hGlobal = pSink->m_pSharedFile->Detach();
      pODS->CacheGlobalData(cf,hGlobal);
   }
}


CDragDataSourceImpl::DataSource::DataSource(HGLOBAL hMem)
{
   m_hGlobal = hMem;
   m_pMemFile = new CMemFile((BYTE*)::GlobalLock(m_hGlobal),
                             (UINT)::GlobalSize(m_hGlobal));
   m_pArchive = new CArchive(m_pMemFile,CArchive::load);
}

CDragDataSourceImpl::DataSource::~DataSource()
{
   ::GlobalUnlock(m_hGlobal);
   delete m_pArchive;
   delete m_pMemFile;
}


CDragDataSinkImpl::DataSink::DataSink()
{
   m_pSharedFile = new CSharedFile(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
   m_pArchive = new CArchive(m_pSharedFile,CArchive::store);
}

CDragDataSinkImpl::DataSink::~DataSink()
{
   delete m_pArchive;
   delete m_pSharedFile;
}
