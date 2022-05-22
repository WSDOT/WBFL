///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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
         XEntryNotFoundT(const K& key,LPCTSTR file, Int16 line) :
             WBFL::System::XBase(file,line),
             m_Key( key )
             {
             }

         XEntryNotFoundT(const XEntryNotFoundT&) = default;

         XEntryNotFoundT& operator=(const XEntryNotFoundT& rOther) = default;

         virtual void Throw() const override
         { throw *static_cast<const XEntryNotFoundT*>(this); }

         virtual Int32 GetReason() const noexcept override
         {
            return 0;
         };

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
         LibraryT()
         {
            // WARNING
            // If this dummy line of code does not exist in release builds
            // m_Map does not get initialized correctly and the program
            // crashes out.  I don't know what's going on, but if this line
            // (or presumably any other code that calls a m_Map member function)
            // does not exist, the Release builds don't work.
            CollectionIndexType size = m_Map.size();
         }

         LibraryT(const LibraryT&) = default;

         virtual ~LibraryT()
         {
         }

         LibraryT& operator = (const LibraryT&) = default;

         void AddEntry(const K& key, const V& value)
         {
            m_Map.insert( std::make_pair(key,value) );
         }

         void RemoveEntry(const K& key)
         {
            m_Map.erase( key );
         }

         V& GetEntry(const K& key)
         {
            std::map<K,V>::iterator i = m_Map.find( key );
            if ( i == m_Map.end() )
            {
               throw XEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
            }
      
            return (*i).second;
         }

         V GetEntry(const K& key) const
         {
            std::map<K,V>::const_iterator i = m_Map.find( key );
            if ( i == m_Map.end() )
            {
               throw XEntryNotFoundT<K,V>( key, _T(__FILE__), __LINE__ );
            }
      
            return (*i).second;
         }

         bool Contains(const K& key) const
         {
            std::map<K,V>::const_iterator i = m_Map.find( key );
            return ( i == m_Map.end() );
         }

      private:
         std::map<K,V> m_Map;
      };
   };
};
