///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_UNITMGT_LIBRARYT_H_
#define INCLUDED_UNITMGT_LIBRARYT_H_
#pragma once

#include <System\Exception.h>
#include <map>
#include <UnitMgt\UnitMgtExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
template <class K,class V> class unitmgtLibraryT;
template <class K,class V> class unitmgtLibraryIterT;
template <class K,class V> class unitmgtConstLibraryIterT;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   unitmgtXEntryNotFoundT

   Template class for an XEntryNotFound exception.


DESCRIPTION
   Template class for an XEntryNotFound exception.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.09.1997 : Created file
*****************************************************************************/

template <class K, class V>
class unitmgtXEntryNotFoundT : public sysXBase
{
public:
   // GROUP: LIFECYCLE
   unitmgtXEntryNotFoundT(const K& key,LPCTSTR file, Int16 line) :
       sysXBase(file,line),
       m_Key( key )
       {
       }

   //------------------------------------------------------------------------
   unitmgtXEntryNotFoundT(const unitmgtXEntryNotFoundT& rOther) :
      sysXBase( rOther ),
      m_Key( rOther.m_Key )
   {
   }

   //------------------------------------------------------------------------
   ~unitmgtXEntryNotFoundT()
   {}

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitmgtXEntryNotFoundT& operator=(const unitmgtXEntryNotFoundT& rOther)
   {
      if ( this != &rOther )
         m_Key = rOther.m_Key;

      return *this;
   }

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   virtual void Throw() const
   { throw *static_cast<const unitmgtXEntryNotFoundT*>(this); }

   virtual Int32 GetReason() const
   {
      return 0;
   };

   //------------------------------------------------------------------------
   K GetOffendingKey() const
   { return m_Key; }

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   K m_Key;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   unitmgtLibraryT

   Template class for a unit library.


DESCRIPTION
   Template class for a unit library.  This class provides library services
   that can be used to categorize indirect units of measure.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.09.1997 : Created file
*****************************************************************************/

template <class K, class V>
class unitmgtLibraryT
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitmgtLibraryT()
   {
      // WARNING
      // If this dummy line of code does not exist in release builds
      // m_Map does not get initialized correctly and the program
      // crashes out.  I don't know what's going on, but if this line
      // (or presumably any other code that calls a m_Map member function)
      // does not exist, the Release builds don't work.
      CollectionIndexType size = m_Map.size();
   }

   //------------------------------------------------------------------------
   // Copy constructor
   unitmgtLibraryT(const unitmgtLibraryT& rOther)
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitmgtLibraryT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitmgtLibraryT& operator = (const unitmgtLibraryT& rOther)
   {
      if ( this != &rOther )
      {
         MakeAssignment( rOther );
      }

      return *this;
   }

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   void AddEntry(const K& key, const V& value)
   {
      m_Map.insert( std::make_pair(key,value) );
   }

   //------------------------------------------------------------------------
   void RemoveEntry(const K& key)
   {
      m_Map.erase( key );
   }

   //------------------------------------------------------------------------
   V& GetEntry(const K& key)
   {
      std::map<K,V>::iterator i = m_Map.find( key );
      if ( i == m_Map.end() )
      {
         throw unitmgtXEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
      }
      
      return (*i).second;
   }

   //------------------------------------------------------------------------
   V GetEntry(const K& key) const
   {
      std::map<K,V>::const_iterator i = m_Map.find( key );
      if ( i == m_Map.end() )
      {
         throw unitmgtXEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
      }
      
      return (*i).second;
   }

   //------------------------------------------------------------------------
   bool Contains(const K& key) const
   {
      std::map<K,V>::const_iterator i = m_Map.find( key );
      return ( i == m_Map.end() );
   }

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitmgtLibraryT& rOther)
   {
      m_Map = rOther.m_Map;
   }

   //------------------------------------------------------------------------
   void MakeAssignment(const unitmgtLibraryT& rOther)
   {
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::map<K,V> m_Map;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   friend unitmgtLibraryIterT<K,V>;
   friend unitmgtConstLibraryIterT<K,V>;
};


/*****************************************************************************
CLASS 
   unitmgtLibraryIterT

   Template iterator class for a unit library.


DESCRIPTION
   Template iterator class for a unit library.  Use this class to iterator
   through the elements in the library.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.09.1997 : Created file
*****************************************************************************/

template <class K, class V>
class unitmgtLibraryIterT
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitmgtLibraryIterT(unitmgtLibraryT<K,V>& lib)
   {
      m_Begin   = lib.m_Map.begin();
      m_Current = lib.m_Map.begin();
      m_End     = lib.m_Map.end();
      
      m_Last = m_End;
      m_Last--;
   }

   //------------------------------------------------------------------------
   // Copy constructor
   unitmgtLibraryIterT(const unitmgtLibraryIterT& rOther)
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitmgtLibraryIterT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitmgtLibraryIterT& operator = (const unitmgtLibraryIterT& rOther)
   {
      if ( this != &rOther )
      {
         MakeAssignment( rOther );
      }

      return *this;
   }

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void First()
   {
      m_Current = m_Begin;
   }

   //------------------------------------------------------------------------
   void Last()
   {
      m_Current = m_End;
   }

   //------------------------------------------------------------------------
   bool Next()
   {
      if ( IsDone() )
         return false;

      m_Current++;
      return true;
   }

   //------------------------------------------------------------------------
   const K& CurrentKey() const
   {
      if ( IsDone() )
      {
         return (*m_Last).first;
      }
      else
      {
         return (*m_Current).first;
      }
   }

   //------------------------------------------------------------------------
   V& CurrentValue() const
   {
      if ( IsDone() )
      {
         return (*m_Last).second;
      }
      else
      {
         return (*m_Current).second;
      }
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   bool IsDone() const
   {
      return ( m_Current == m_End );
   }
   
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitmgtLibraryIterT& rOther)
   {
      m_Begin   = rOther.m_Begin;
      m_Current = rOther.m_Current;
      m_End     = rOther.m_End;
      m_Last    = rOther.m_Last;
   }

   //------------------------------------------------------------------------
   void MakeAssignment(const unitmgtLibraryIterT& rOther)
   {
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   typename std::map<K,V>::iterator m_Begin;
   typename std::map<K,V>::iterator m_Current;
   typename std::map<K,V>::iterator m_End;
   typename std::map<K,V>::iterator m_Last;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};



/*****************************************************************************
CLASS 
   unitmgtConstLibraryIterT

   Template iterator class for a unit library.


DESCRIPTION
   Template iterator class for a unit library.  Use this class to iterator
   through the elements in the library.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.09.1997 : Created file
*****************************************************************************/

template <class K, class V>
class unitmgtConstLibraryIterT
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   unitmgtConstLibraryIterT(const unitmgtLibraryT<K,V>& lib)
   {
      m_Begin   = lib.m_Map.begin();
      m_Current = lib.m_Map.begin();
      m_End     = lib.m_Map.end();

      m_Last = m_End;
      m_Last--;
   }

   //------------------------------------------------------------------------
   // Copy constructor
   unitmgtConstLibraryIterT(const unitmgtConstLibraryIterT& rOther)
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~unitmgtConstLibraryIterT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   unitmgtConstLibraryIterT& operator = (const unitmgtConstLibraryIterT& rOther)
   {
      if ( this != &rOther )
      {
         MakeAssignment( rOther );
      }

      return *this;
   }

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   void First()
   {
      m_Current = m_Begin;
   }

   //------------------------------------------------------------------------
   void Last()
   {
      m_Current = m_End;
   }

   //------------------------------------------------------------------------
   bool Next()
   {
      if ( IsDone() )
         return false;

      m_Current++;
      return true;
   }

   //------------------------------------------------------------------------
   const K& CurrentKey() const
   {
      if ( IsDone() )
      {
         return (*m_Last).first;
      }
      else
      {
         return (*m_Current).first;
      }
   }

   //------------------------------------------------------------------------
   const V& CurrentValue() const
   {
      if ( IsDone() )
      {
         return (*m_Last).second;
      }
      else
      {
         return (*m_Current).second;
      }
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   bool IsDone() const
   {
      return ( m_Current == m_End );
   }
   
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const unitmgtConstLibraryIterT& rOther)
   {
      m_Begin   = rOther.m_Begin;
      m_Current = rOther.m_Current;
      m_End     = rOther.m_End;
      m_Last    = rOther.m_Last;
   }

   //------------------------------------------------------------------------
   void MakeAssignment(const unitmgtConstLibraryIterT& rOther)
   {
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   typename std::map<K,V>::const_iterator m_Begin;
   typename std::map<K,V>::const_iterator m_Current;
   typename std::map<K,V>::const_iterator m_Last;
   typename std::map<K,V>::const_iterator m_End;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITMGT_LIBRARYT_H_
