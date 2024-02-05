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
#include <DManip/InplaceEdit.h>
#include <DManip/DisplayObject.h>

class CDisplayView;
class CInplaceEdit;

namespace WBFL
{
   namespace DManip
   {
      class iTask;

      /// @brief Partial default implementation of iInplaceEditable.
      /// This class primarily provides and implementation for DoInplaceEdit
      class DMANIPCLASS InplaceEditableDefaultImpl : public iInplaceEditable
      {
      public:
         InplaceEditableDefaultImpl() = default;
	      virtual ~InplaceEditableDefaultImpl() = default;

         // Returns the CDisplayView canvas
         virtual CDisplayView* GetDisplayView() = 0;
         virtual CInplaceEdit* GetEditObject() = 0;

         // iInplaceEditable Implementation
         // Simply implements the DoInplaceEdit template method
         // All other methods must be implemented by subclasses
         virtual void DoInplaceEdit() override;
         virtual void EndInplaceEdit() override;

         //virtual void CreateEditControl() = 0;
         //virtual void DestroyEditControl() = 0;
         //virtual void OnTextChanged(LPCTSTR lpszText) = 0;

         virtual void SetParent(std::weak_ptr<iDisplayObject> pParent);
         virtual std::shared_ptr<iDisplayObject> GetParent();


      protected:
         // Abstract methods that must be implemented by subclasses

         // Creates an Inplace Edit task
         virtual std::shared_ptr<iTask> CreateTask();

         /// @brief Returns a shared pointer for an iInplaceEditable
         /// Classes can only inherit from one instance of std::enabled_shared_from_this. Since this is a mix-in class,
         /// the primary class has that responsibility. This function gets the shared this pointer from the primary class
         /// since this class cannot provide a shared_from_this() method.
         /// @return 
         virtual std::shared_ptr<iInplaceEditable> GetInplaceEditable() = 0;

         std::weak_ptr<iDisplayObject> m_pCompositeParent; // weak reference to parent object... typically used when this DO is part of a composite

      };
   };
};
