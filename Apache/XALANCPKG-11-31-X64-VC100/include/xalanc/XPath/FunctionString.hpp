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
#if !defined(FUNCTIONSTRING_HEADER_GUARD_1357924680)
#define FUNCTIONSTRING_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



#include <vector>



// Base class header file...
#include <xalanc/XPath/Function.hpp>



#include <xalanc/XPath/NodeRefListBase.hpp>



XALAN_CPP_NAMESPACE_BEGIN



/**
 * XPath implementation of "string" function.
 */
class XALAN_XPATH_EXPORT FunctionString : public Function
{
public:

    typedef Function    ParentType;

    FunctionString();

    virtual
    ~FunctionString();

    // These methods are inherited from Function ...

    virtual XObjectPtr
    execute(
            XPathExecutionContext&  executionContext,
            XalanNode*              context,
            const Locator*          locator) const;

    virtual XObjectPtr
    execute(
            XPathExecutionContext&  executionContext,
            XalanNode*              context,
            const XObjectPtr        arg1,
            const Locator*          locator) const;

    using ParentType::execute;

#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
    virtual Function*
#else
    virtual FunctionString*
#endif
    clone(MemoryManager& theManager) const;

protected:

    virtual const XalanDOMString&
    getError(XalanDOMString& theResult) const;

private:

    // Not implemented...
    FunctionString&
    operator=(const FunctionString&);

    bool
    operator==(const FunctionString&) const;
};



XALAN_CPP_NAMESPACE_END



#endif  // FUNCTIONSTRING_HEADER_GUARD_1357924680
