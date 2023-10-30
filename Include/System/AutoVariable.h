///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

namespace WBFL
{
   namespace System
   {
      /// This template class can be used to automatically restore a variable
      /// to it's previous value when this object goes out of scope.
      /// 
      /// Example
      /// \code
      /// void Function()
      /// {
      ///    AutoVariable a(&m_MyVariable,500); // assigns 500 to m_MyVariable
      ///    ... do some stuff with m_MyVariable
      ///    if(bad) throw; // m_MyVariable returns to it's original value
      /// 
      ///    ... do some more stuff
      /// } // m_MyVariable returns to it's original value
      /// \endcode
      template <class T> class AutoVariable
      {
      public:
         AutoVariable(T* pValue, const T& newValue)
         {
            m_pValue = pValue; // hang onto the pointer so we set the value back to the old value in the destructor
            m_OldValue = *m_pValue; // save the current value so we can restore it
            *m_pValue = newValue; // set the new value
         }

         ~AutoVariable()
         {
            // we are going out of scope, restore the original value
            *m_pValue = m_OldValue;
         }

      private:
         T* m_pValue;
         T m_OldValue;
      };
   };
};
