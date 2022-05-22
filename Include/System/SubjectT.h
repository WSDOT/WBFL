///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#pragma once

#include <WbflTypes.h>
#include <set>

namespace WBFL
{
   namespace System
   {
      /// A template class to aid in building subject-observer relationships.
      ///
      /// This class allows you to marry any subject to any observer class which 
      /// has an Update(Subject&, Int32 hint) member function. Simply create the Observer class
      /// and then derive the subject class from this template class.
      template <class TObserver, class TSubject> 
      class SubjectT
      {
      public:
         /// Attaches an observer to the subject. The observer will be notified
         // when the subject changes. Returns true if successful.
         virtual bool Attach(TObserver& observer) const
         {
            m_Observers.emplace_back(observer);
            return true;
         }

         /// Detaches an observer from the subject. The observer will no longer be notified. Returns true if successful.
         virtual bool Detach(TObserver& observer) const
         {
            auto result = std::find_if(std::begin(m_Observers), std::end(m_Observers), [&observer](TObserver& a) { return &a == &observer; });
            return result == m_Observers.end() ? false : true;
         }

         /// Notify all observers that the subjected changed.
         virtual void Notify(Int32 hint = 0)
         {
            TSubject* pts = dynamic_cast<TSubject*>(this);
            CHECK(pts);

            std::for_each(std::begin(m_Observers), std::end(m_Observers), [&](TObserver& observer) {observer.Update(*pts, hint); });
         }

      private:
         mutable std::vector<std::reference_wrapper<TObserver>> m_Observers;
      };
   };
};
