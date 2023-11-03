///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <ReportManager\ReportManagerExp.h>

namespace WBFL
{
   namespace Reporting
   {
      class REPORTMANAGERCLASS IReportView
      {
      public:
         virtual BOOL Create(
            LPCTSTR lpszWindowName,
            DWORD dwStyle,
            const RECT& rect,
            HWND hwndParent,
            UINT nID) = 0;

         virtual void FitToParent() = 0;
         virtual void Move(POINT topLeft) = 0;
         virtual void Size(SIZE size) = 0;
         virtual void Print(bool bPrompt) = 0;
         virtual void Find() = 0;
         virtual void SelectAll() = 0;
         virtual void Copy() = 0;
         virtual void Refresh() = 0;
         virtual void ViewSource() = 0;
         virtual void Back() = 0;
         virtual void Forward() = 0;
         virtual void Navigate(LPCTSTR uri) = 0;
      };
   };
};