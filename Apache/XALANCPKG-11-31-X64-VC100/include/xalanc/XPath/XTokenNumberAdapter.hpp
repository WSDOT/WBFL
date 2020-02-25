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
#if !defined(XTOKENNUMBERADAPTER_HEADER_GUARD_1357924680)
#define XTOKENNUMBERADAPTER_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



#include <xalanc/XalanDOM/XalanDOMString.hpp>



// Base class header file.
#include <xalanc/XPath/XNumberBase.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XToken;



class XALAN_XPATH_EXPORT XTokenNumberAdapter : public XNumberBase
{
public:

    /**
     * Create an XTokenNumberAdapter from an XToken.
     *
     * @param theXToken The XToken instance to adapt
     * @param theMemoryManager The MemoryManager instance.
     */
    XTokenNumberAdapter(
            const XToken&   theToken,
            MemoryManager&  theMemoryManager);

    /**
     * Create an XTokenNumberAdapter from another one.
     *
     * @param source The XTokenNumberAdapter instance to copy
     * @param theMemoryManager The MemoryManager instance.
     */
    XTokenNumberAdapter(
            const XTokenNumberAdapter&  source,
            MemoryManager&              theMemoryManager);

    virtual
    ~XTokenNumberAdapter();

    // These methods are inherited from XObject ...

    virtual double
    num(XPathExecutionContext&  executionContext) const;

    virtual double
    num() const;

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

    // XToken instance that we're adapting...
    const XToken&   m_value;
};



XALAN_CPP_NAMESPACE_END



#endif  // XTOKENNUMBERADAPTER_HEADER_GUARD_1357924680
