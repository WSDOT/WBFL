///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/DragDataImpl.h>

using namespace WBFL::DManip;

DragDataSource::~DragDataSource()
{
   std::for_each(m_Sources.begin(), m_Sources.end(), [](auto& p) {delete p.second; });
   m_Sources.clear();
}

void DragDataSource::SetDataObject(COleDataObject* pDataObj)
{
   m_pDataObj = pDataObj;
}

void DragDataSource::PrepareFormat(UINT cfFormat)
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

UINT DragDataSource::Read(UINT cfFormat,void* pBuf,UINT nMax)
{
   std::map<UINT,DataSource*>::iterator found = m_Sources.find(cfFormat);
   if ( found == m_Sources.end() )
      return 0; // Format not found

   DataSource* pSource = (*found).second;
   return pSource->m_pArchive->Read(pBuf,nMax);
}

/////////////////////////////////////////////////////////

DragDataSink::~DragDataSink()
{
   std::for_each(m_Sinks.begin(), m_Sinks.end(), [](auto& p) {delete p.second; });
   m_Sinks.clear();
}

void DragDataSink::CreateFormat(UINT cfFormat)
{
   std::map<UINT,DataSink*>::iterator found = m_Sinks.find(cfFormat);
   if ( found != m_Sinks.end() )
      return; // Format was previously created

   DataSink* pSink = new DataSink;
   m_Sinks.insert(std::make_pair(cfFormat,pSink));
}

bool DragDataSink::Write(UINT cfFormat,void* pBuf,UINT nMax)
{
   std::map<UINT,DataSink*>::iterator found = m_Sinks.find(cfFormat);
   if (found == m_Sinks.end())
   {
      CHECK(false);
      return false; // Sink not found
   }

   DataSink* pSink = (*found).second;
   try
   {
      pSink->m_pArchive->Write(pBuf,nMax);
   }
   catch(...)
   {
      CHECK(false); // something went wrong
      return false;
   }

   return true;
}

void DragDataSink::CacheGlobalData(COleDataSource* pODS)
{
   for(auto& [cf,pSink] : m_Sinks)
   {
      pSink->m_pArchive->Close();
      HGLOBAL hGlobal = pSink->m_pSharedFile->Detach();
      pODS->CacheGlobalData(cf,hGlobal);
   }
}

//////////////////////////////////

DragDataSource::DataSource::DataSource(HGLOBAL hMem)
{
   m_hGlobal = hMem;
   m_pMemFile = new CMemFile((BYTE*)::GlobalLock(m_hGlobal),
                             (UINT)::GlobalSize(m_hGlobal));
   m_pArchive = new CArchive(m_pMemFile,CArchive::load);
}

DragDataSource::DataSource::~DataSource()
{
   ::GlobalUnlock(m_hGlobal);
   delete m_pArchive;
   delete m_pMemFile;
}


DragDataSink::DataSink::DataSink()
{
   m_pSharedFile = new CSharedFile(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
   m_pArchive = new CArchive(m_pSharedFile,CArchive::store);
}

DragDataSink::DataSink::~DataSink()
{
   delete m_pArchive;
   delete m_pSharedFile;
}
