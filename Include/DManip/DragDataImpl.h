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

#pragma once

#include <DManip/DManipExp.h>
#include <afxadv.h>
#include <afxole.h>
#include <DManip/DragData.h>
#include <map>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A drag data source object implementing the iDragDataSource interface
      class DMANIPCLASS DragDataSource : public iDragDataSource
      {
      protected:
         DragDataSource() = default;

      public:
         static std::shared_ptr<DragDataSource> Create() { return std::shared_ptr<DragDataSource>(new DragDataSource()); }
	      virtual ~DragDataSource();

         // iDragDataSource Implementation
         virtual void SetDataObject(COleDataObject* pDataObj) override;
         virtual void PrepareFormat(UINT cfFormat) override;
         virtual UINT Read(UINT format,void* pBuf,UINT nMax) override;

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

      /// @brief A drag data sink object implementing the iDragDataSink interface
      class DragDataSink : public iDragDataSink
      {
      public:
	      DragDataSink() = default;
	      virtual ~DragDataSink();

         // iDragDataSink Implementation
         virtual void CreateFormat(UINT cfFormat) override;
         virtual bool Write(UINT cfFormat,void* pBuf,UINT nMax) override;

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
   };
};
