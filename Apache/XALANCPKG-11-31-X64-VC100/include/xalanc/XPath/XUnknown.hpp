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
#if !defined(XUKNOWN_HEADER_GUARD_1357924680)
#define XUKNOWN_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



#include <xalanc/XalanDOM/XalanDOMString.hpp>



// Base class header file.
#include <xalanc/XPath/XObject.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_XPATH_EXPORT XUnknown : public XObject
{
public:

    typedef XObject     ParentType;

    /**
     * Perform static initialization.  See class XPathInit.
     */
    static void
    initialize(MemoryManager& theManager);

    /**
     * Perform static shut down.  See class XPathInit.
     */
    static void
    terminate();

    /**
     * Construct an XUnknown object from a string.
     * 
     * @param name The source string.
     * @param theMemoryManager The MemoryManager instance.
     */
    XUnknown(
                const XalanDOMString&   name,
                MemoryManager&          theMemoryManager);

    /**
     * Construct an XUnknown from another one.
     *
     * @param source The XUnknown instance to copy.
     * @param theMemoryManager The MemoryManager instance.
     */
    XUnknown(
                const XUnknown&     source,
                MemoryManager&      theMemoryManager);

    /**
     * Create an XUnknown object from a string.
     * 
     * @param name the source string.
     * @param theMemoryManager The MemoryManager instance.
     */
    static XUnknown*
    create(
            const XalanDOMString&   name,
            MemoryManager&          theMemoryManager);

    virtual
    ~XUnknown();

    // These methods are inherited from XObject ...
    virtual const XalanDOMString&
    getTypeString() const;
  
    virtual double
    num(XPathExecutionContext&  executionContext) const;

    virtual double
    num() const;

    virtual bool
    boolean(XPathExecutionContext&  executionContext) const;

    virtual const XalanDOMString&
    str(XPathExecutionContext&  executionContext) const;

    virtual const XalanDOMString&
    str() const;

    virtual void
    str(
            XPathExecutionContext&  executionContext,
            FormatterListener&      formatterListener,
            MemberFunctionPtr       function) const;

    virtual void
    str(
            FormatterListener&      formatterListener,
            MemberFunctionPtr       function) const;

    virtual void
    str(
            XPathExecutionContext&  executionContext,
            XalanDOMString&         theBuffer) const;

    virtual void
    str(XalanDOMString&     theBuffer) const;

    virtual double
    stringLength(XPathExecutionContext&     executionContext) const;

    virtual void
    ProcessXObjectTypeCallback(XObjectTypeCallback&     theCallbackObject);

    virtual void
    ProcessXObjectTypeCallback(XObjectTypeCallback&     theCallbackObject) const;

private:
    // undefined
    XUnknown(const XUnknown&    source);
    XUnknown();

    XalanDOMString  m_value;

    static XalanDOMString   s_unknownString;
};



XALAN_CPP_NAMESPACE_END



#endif  // XUKNOWN_HEADER_GUARD_1357924680
