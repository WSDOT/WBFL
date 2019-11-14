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
#if !defined(XSTRINGADAPTER_HEADER_GUARD_1357924680)
#define XSTRINGADAPTER_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



// Base class header file.
#include <xalanc/XPath/XStringBase.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_XPATH_EXPORT XStringAdapter : public XStringBase
{
public:

    typedef XStringBase     ParentType;

    /**
     * Create a string XObject that will adapt another XObject to
     * behave like a string.  The XObject holds a reference to the
     * other XObject.
     *
     * @param theValue  value used to create object  
     * @param theManager The MemoryManager instance to use
     * @param theExecutionContext The current XPathExecutionContext
     */
    XStringAdapter(
            const XObjectPtr&       val,
            MemoryManager&          theManager,
            XPathExecutionContext&  theExecutionContext);

    XStringAdapter(
            const XStringAdapter&   source,
            MemoryManager&          theManager);

    virtual
    ~XStringAdapter();


    // These methods are inherited from XObject ...

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

protected:

    virtual eObjectType
    getRealType() const;

private:

    // Not implemented
    XStringAdapter(const XStringAdapter&    source);

    XStringAdapter();

    const XObjectPtr    m_value;
};



XALAN_CPP_NAMESPACE_END



#endif  // XSTRINGADAPTER_HEADER_GUARD_1357924680
