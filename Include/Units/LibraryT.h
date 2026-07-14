///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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

#include <System\Exception.h>
#include <map>
#include <Units\UnitsExp.h>

namespace WBFL
{
   namespace Units
   {
      /// Template class for an XEntryNotFound exception.
      template <class K, class V>
      class XEntryNotFoundT : public WBFL::System::XBase
      {
      public:
         /// Constructs the exception for the entry that could not be found, identified by key. file and
         /// line should be the source file and line number where the exception is being thrown, typically
         /// _T(__FILE__) and __LINE__.
         XEntryNotFoundT(const K& key, const std::_tstring& file, Uint32 line) :
             WBFL::System::XBase(file,line),
             m_Key( key )
             {
             }

         XEntryNotFoundT(const XEntryNotFoundT&) = default;

         XEntryNotFoundT& operator=(const XEntryNotFoundT& rOther) = default;

         /// Throws this exception object.
         virtual void Throw() const override
         { throw *static_cast<const XEntryNotFoundT*>(this); }

         /// Returns 0; this exception has only one reason (an entry was not found).
         virtual Int32 GetReason() const noexcept override
         {
            return 0;
         };

         /// Returns the key that could not be found in the library.
         K GetOffendingKey() const
         { return m_Key; }


      private:
         K m_Key;
      };

      /// Template class for a unit library.
      ///
      /// This class provides library services that can be used to categorize indirect units of measure.
      template <class K, class V>
      class LibraryT
      {
      public:
         /// Constructs an empty library.
         LibraryT()
         {
            // WARNING
            // If this dummy line of code does not exist in release builds
            // m_Map does not get initialized correctly and the program
            // crashes out.  I don't know what's going on, but if this line
            // (or presumably any other code that calls a m_Map member function)
            // does not exist, the Release builds don't work.
            IndexType size = m_Map.size();
         }

         LibraryT(const LibraryT&) = default;

         virtual ~LibraryT()
         {
         }

         LibraryT& operator = (const LibraryT&) = default;

         /// Adds value to the library, keyed by key. If key is already in use, its entry is silently
         /// replaced (std::map::insert semantics mean the existing entry is kept and this call is a no-op;
         /// this is a bit surprising and worth confirming if you rely on overwrite-on-duplicate behavior).
         void AddEntry(const K& key, const V& value)
         {
            m_Map.insert( std::make_pair(key,value) );
         }

         /// Removes the entry keyed by key, if present. Does nothing if key is not in the library.
         void RemoveEntry(const K& key)
         {
            m_Map.erase( key );
         }

         /// Returns the entry keyed by key. Throws XEntryNotFoundT<K,V> if key is not in the library.
         V& GetEntry(const K& key)
         {
            auto i = m_Map.find( key );
            if ( i == m_Map.end() )
            {
               throw XEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
            }

            return (*i).second;
         }

         /// Returns a copy of the entry keyed by key. Throws XEntryNotFoundT<K,V> if key is not in the
         /// library.
         V GetEntry(const K& key) const
         {
            auto i = m_Map.find( key );
            if ( i == m_Map.end() )
            {
               throw XEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
            }

            return (*i).second;
         }

         /// Returns true if key is in the library.
         bool Contains(const K& key) const
         {
            auto i = m_Map.find( key );
            return ( i != m_Map.end() );
         }

      private:
         std::map<K,V> m_Map;
      };
   };
};
