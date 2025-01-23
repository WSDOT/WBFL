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
#include <DManip/TaskFactory.h>

class CDisplayView;

namespace WBFL
{
   namespace DManip
   {
      class iInplaceEditable;
      class iTask;
      class iDisplayMgr;

      /// @brief A factory object that creates task objects.
      /// When implementing custom tasks, extend this class to create the tasks
      /// and use a customized version of DisplayMgr that knows how to use your
      /// customized task factory.
      class DMANIPCLASS TaskFactory
      {
      public:
	      TaskFactory() = default;
	      virtual ~TaskFactory() = default;

         virtual std::shared_ptr<iTask> CreateInplaceEditTask(CDisplayView* pView,std::shared_ptr<iInplaceEditable> pEditable) const;
         virtual std::shared_ptr<iTask> CreateRectSelectTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const;
         virtual std::shared_ptr<iTask> CreateLocalDragDropTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const;
         virtual std::shared_ptr<iTask> CreateForeignDragDropTask(std::shared_ptr<iDisplayMgr> pDispMgr,const CPoint& startPoint) const;
         virtual std::shared_ptr<iTask> CreateCenterOnPointTask(CDisplayView* pView) const;
         virtual std::shared_ptr<iTask> CreateZoomTask(CDisplayView* pView,HCURSOR hCursor,COLORREF color) const;
      };
   };
};
