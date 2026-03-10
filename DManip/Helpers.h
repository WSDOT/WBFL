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

#include <DManip/DManipTypes.h>

void DrawArrowHead(CDC* pDC,WBFL::DManip::ArrowHeadStyleType style,CPoint left,CPoint tip,CPoint right);

/// @brief Draws a point symbol using the current pen and brush
/// @param pDC 
/// @param rect 
/// @param type 
void DrawPointSymbol(CDC* pDC, const RECT& rect, WBFL::DManip::PointType type);


void CreatePen(WBFL::DManip::LineStyleType style, UINT width, COLORREF color, CPen& pen);


#if defined _DEBUG
enum class ObjectType
{
   DO, DL, DM
};

struct ObjectRecord
{
   static Uint64 count; // keeps track of the allocation count

   ObjectRecord(ObjectType type, void* ptr) :type(type) { address = (Uint64)ptr; allocation = count++; }
   ObjectType type;
   Uint64 address;
   Uint64 view_address = 0;
   Uint64 allocation;
};

class CircularRefDebugger
{
public:
   static std::vector<ObjectRecord> ObjectRecords;
   static void Add(ObjectType type, void* ptr) { ObjectRecords.emplace_back(type, ptr); }
   static void Remove(void* ptr) 
   {
      auto iter = std::find_if(ObjectRecords.begin(), ObjectRecords.end(), [ptr](const auto& record) {return record.address == (Uint64)ptr; });
      if (iter != ObjectRecords.end())
         ObjectRecords.erase(iter);
   }

   static ObjectRecord& GetRecord(void* ptr)
   {
      auto iter = std::find_if(ObjectRecords.begin(), ObjectRecords.end(), [ptr](const auto& record) {return record.address == (Uint64)ptr; });
      return *iter;
   }

   static size_t GetRecordCount(Uint64 view_address)
   {
      return std::count_if(ObjectRecords.begin(), ObjectRecords.end(), [view_address](const auto& record) {return record.view_address == view_address; });
   }
};


#endif