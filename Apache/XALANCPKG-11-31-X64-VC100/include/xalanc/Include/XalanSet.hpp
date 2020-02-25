/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the  "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if !defined(XALANSET_HEADER_GUARD_1357924680)
#define XALANSET_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/Include/XalanMap.hpp>



#include <xalanc/Include/XalanMemoryManagement.hpp>



XALAN_CPP_NAMESPACE_BEGIN



template <class Value, class MapIterator>
struct XalanSetIterator
{
    typedef Value   value_type;

    typedef Value&  reference;
    typedef Value*  pointer;

    typedef ptrdiff_t                                       difference_type;
    typedef XALAN_STD_QUALIFIER bidirectional_iterator_tag  iterator_category;

    XalanSetIterator(const MapIterator&     iter) :
        m_mapIterator(iter)
    {
    }

    reference operator*() const
    {
        return m_mapIterator->first;
    };

    bool operator==(const XalanSetIterator& theRhs) const
    {
        return theRhs.m_mapIterator == m_mapIterator;
    }

    bool operator!=(const XalanSetIterator& theRhs) const
    {
        return !(theRhs == *this);
    }

    XalanSetIterator operator++()
    {
        ++m_mapIterator;

        return *this;
    }

    XalanSetIterator operator++(int)
    {
        XalanSetIterator orig(m_mapIterator);

        ++(*this);

        return orig;
    }

protected:

    MapIterator     m_mapIterator;
};


/**
 * Xalan set implementation.
 *
 * Set relies on the XalanMap hashtable.  Users must ensure the right key
 * traits specialization is aviable to define the proper hash functor.
 */
template <class Value>
class XalanSet
{
public:

    typedef Value   value_type;

    typedef size_t  size_type;

    typedef XalanMap<value_type, bool>  SetMapType;

    typedef XalanSetIterator<value_type, typename SetMapType::iterator>             iterator;
    typedef XalanSetIterator<const value_type, typename SetMapType::const_iterator> const_iterator;

    XalanSet(MemoryManager&     theMemoryManager) :
        m_map(theMemoryManager)
    {
    }

    XalanSet(
            const XalanSet&    other,
            MemoryManager&     theMemoryManager) :
        m_map(other.m_map, theMemoryManager)
    {
    }

    MemoryManager&
    getMemoryManager()
    {
        return m_map.getMemoryManager();
    }

    const_iterator
    begin() const
    {
        return m_map.begin();
    }

    const_iterator
    end() const
    {
        return m_map.end();
    }

    size_type
    size() const {
        return m_map.size();
    }

    size_type
    count(const value_type&     value) const 
    {
        return find(value) != end() ? 1 : 0;
    }

    const_iterator
    find(const value_type&  value) const
    {
        return m_map.find(value);
    }

    void
    insert(const value_type&    value)
    {
        m_map.insert(value, true);
    }

    size_type
    erase(const value_type&     value)
    {
        return m_map.erase(value);
    }

    void
    clear()
    {
        m_map.clear();
    }

private:

    SetMapType  m_map;
};



XALAN_CPP_NAMESPACE_END

#endif  // XALANSET_HEADER_GUARD_1357924680
