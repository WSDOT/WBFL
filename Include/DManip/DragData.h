///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

namespace WBFL
{
   namespace DManip
   {
      class iDisplayObject;

      /// @brief Application specific data for a drag/drop operation is stored in a data source. 
      /// After a drag/drop operation completes an iDragData object is given a DragDataSource object from which it will extract relavent data.
      class DMANIPCLASS iDragDataSource
      {
      public:
         /// @brief Called by the framework to associated an MFC COleDataObject with the drag data source. Client applications need not call this method
         virtual void SetDataObject(COleDataObject* pDataObj) = 0;

         /// @brief Call this method to prepare the data source for reading data. Call this method before reading data from a specifed source.
         /// @param cfFormat 
         virtual void PrepareFormat(UINT cfFormat) = 0;

         /// @brief Reads data from the source. Returns the number of bytes read.
         virtual UINT Read(UINT cfFormat,void* pBuf,UINT nMax) = 0;
      };

      /// @brief A place to store application specific data for a drag/drop operation. Before writing to the data sink, call the CreateFormat method.
      class iDragDataSink
      {
      public:
         /// @brief Call this method to create a storage area in the data sink for your clipboard format
         virtual void CreateFormat(UINT cfFormat) = 0;

         /// @brief Write raw data into the data sink. Returns true if successful.
         virtual bool Write(UINT cfFormat,void* pBuf,UINT nMax) = 0;
      };

      /// @brief Implemented by client applications to provide data to be used in OLE data transfer
      class iDragData
      {
      public:
         /// @brief Returns an integer that identifies the data format
         virtual UINT Format() = 0;

         /// @brief Called by the framework just before a drag/drop is about to
         /// begin. Write what ever data you want to be included in the 
         /// data transfer to the DragDataSink.
         virtual bool PrepareForDrag(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSink> pSink) = 0;

         /// @brief Called by the framework when the display object is dropped.
         /// This is your opportunity to read the data you stored in PrepareForDrag
         virtual void OnDrop(std::shared_ptr<iDisplayObject> pDO,std::shared_ptr<iDragDataSource> pSource) = 0;
      };
   };
};
