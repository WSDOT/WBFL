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
#if !defined(ATTRIBUTESIMPL_HEADER_GUARD_1357924680)
#define ATTRIBUTESIMPL_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/PlatformSupport/PlatformSupportDefinitions.hpp>



#include <xalanc/Include/XalanVector.hpp>



#include <xercesc/sax2/Attributes.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class AttributeVectorEntryExtended;



typedef XERCES_CPP_NAMESPACE_QUALIFIER Attributes   AttributesType;



class XALAN_PLATFORMSUPPORT_EXPORT AttributesImpl : public AttributesType
{
public:

    explicit
    AttributesImpl(MemoryManager&      theManager XALAN_DEFAULT_MEMMGR);

    virtual
    ~AttributesImpl();

    AttributesImpl(const AttributesImpl&    theSource,
                    MemoryManager&      theManager);

    AttributesImpl(const AttributesType&    theSource,
                    MemoryManager&      theManager);

    AttributesImpl&
    operator=(const AttributesImpl&     theRHS);

    AttributesImpl&
    operator=(const AttributesType&     theRHS);

    // These are inherited from Attributes
    virtual XalanSize_t
    getLength() const;

    virtual const XMLCh*
    getURI(const XalanSize_t    index) const;

    virtual const XMLCh*
    getLocalName(const XalanSize_t  index) const;

    virtual const XMLCh*
    getQName(const XalanSize_t  index) const;

    virtual const XMLCh*
    getType(const XalanSize_t   index) const;

    virtual const XMLCh*
    getValue(const XalanSize_t  index) const;

    virtual bool
    getIndex(
            const XMLCh* const  uri,
            const XMLCh* const  localPart,
            XalanSize_t&        index) const;

    virtual int
    getIndex(
            const XMLCh* const  uri,
            const XMLCh* const  localPart) const;

    virtual bool
    getIndex(
            const XMLCh* const  qName,
            XalanSize_t&        index) const;

    virtual int
    getIndex(const XMLCh* const     qname) const;

    virtual const XMLCh*
    getType(const XMLCh* const qname) const;

    virtual const XMLCh*
    getType(
            const XMLCh* const  uri,
            const XMLCh* const  localName) const;

    virtual const XMLCh*
    getValue(const XMLCh* const qname) const;

    virtual const XMLCh*
    getValue(
            const XMLCh* const  uri,
            const XMLCh* const  localName) const;

    MemoryManager&
    getMemoryManager()
    {
        return m_attributesVector.getMemoryManager();
    }

    // The mutators are new to this class.

    /**
     * Remove all attributes from the list
     */
    virtual void
    clear();

    /**
     * Adds an attribute to the attribute list.  Does not check for
     * duplicates.
     *
     * @param  qname   attribute qname
     * @param type   attribute type, "CDATA," for example
     * @param value  attribute value
     */
    void
    addAttribute(
            const XMLCh*    qname,
            const XMLCh*    type,
            const XMLCh*    value)
    {
        const XMLCh     theDummy = 0;

        addAttribute(&theDummy, &theDummy, qname, type, value);
    }

    /**
     * Adds an attribute to the attribute list.  Does not check for
     * duplicates.
     *
     * @param uri attribute namespace URI
     * @param localName attribute local name
     * @param qname attribute qname
     * @param type attribute type, "CDATA," for example
     * @param value attribute value
     */
    void
    addAttribute(
            const XMLCh*    uri,
            const XMLCh*    localName,
            const XMLCh*    qname,
            const XMLCh*    type,
            const XMLCh*    value);

    /**
     * Removes an attribute from the attribute list
     *
     * @param  qname   attribute qname
     */
    virtual bool
    removeAttribute(const XMLCh*    qname);

    /**
     * Swap the contents of two instances.  This must _never_
     * throw an exception.
     *
     * @param thOther The instance with which to swap.
     */
    void
    swap(AttributesImpl&        theOther)
    {
        m_attributesVector.swap(theOther.m_attributesVector);
    }

    /**
     * Reserve room for the given number of
     * attributes.
     *
     * @param theCount The number to reserve
     */
    void
    reserve(XalanSize_t     theCount)
    {
        m_attributesVector.reserve(theCount);
    }

    // This vector will hold the entries.
    typedef XalanVector<AttributeVectorEntryExtended*>      AttributesVectorType;

private:

    // This is not implemented.
    bool
    operator==(const AttributesImpl&) const;

    // Default vector allocation size.
    enum
    {
        eDefaultVectorSize = 5
    };

    AttributeVectorEntryExtended*
    getNewEntry(
            const XMLCh*    qname,
            const XMLCh*    type,
            const XMLCh*    value,
            const XMLCh*    uri = 0,
            const XMLCh*    localName = 0);

    // Helper function to delete entries...
    static void
    deleteEntries(AttributesVectorType&     theVector);

    AttributesVectorType    m_attributesVector;

    AttributesVectorType    m_cacheVector;
};



XALAN_CPP_NAMESPACE_END



#endif  // ATTRIBUTESIMPL_HEADER_GUARD_1357924680
