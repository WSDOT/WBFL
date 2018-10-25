///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_SUBJECTT_H_
#define INCLUDED_SYSTEM_SUBJECTT_H_
#pragma once

#include <WbflTypes.h>
#include <set>
//
/*****************************************************************************
CLASS 
   sysSubjectT

   A helper template class to aid in building subject-observer relationships.


DESCRIPTION
   This class allows you to marry any subject to any observer class which 
   has a Notify(Subject *) member function. Simply create the Observer class
   and then derive the subject class from this template class.

   About the only tricky thing here is that the TSubject parameter is the type
   of the subject class. This may seem strange when you think about it at first
   (conjures up thoughts of chickens and eggs...), but it works.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 10.06.1998 : Created file
*****************************************************************************/

template <class TObserver, class TSubject> class sysSubjectT
{
public:

   //------------------------------------------------------------------------
   // Description: Attaches an observer.
   // Return:      None
   virtual void Attach(TObserver* pObserver) const
   {
      m_ObserverList.insert(pObserver);
   }

   //------------------------------------------------------------------------
   // Description: Detaches an observer.
   // Return:      None   
   virtual void Detach(TObserver* pObserver) const
   {
      m_ObserverList.erase(pObserver);
   }

   //------------------------------------------------------------------------
   // Notify all observers that we changed.
   virtual void Notify(Int32 hint=0)
   {
      TSubject* pts = dynamic_cast<TSubject*>(this);
      CHECK(pts);

      for (SetIterator it=m_ObserverList.begin(); it!=m_ObserverList.end(); it++)
      {
         (*it)->Update(pts, hint);
      }
   }

private:
   mutable std::set<TObserver*> m_ObserverList;
   typedef typename std::set<TObserver*>::iterator SetIterator;
};

#endif // INCLUDED_SYSTEM_SUBJECTT_H_