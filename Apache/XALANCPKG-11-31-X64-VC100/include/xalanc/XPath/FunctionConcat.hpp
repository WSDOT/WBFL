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
#if !defined(FUNCTIONCONCAT_HEADER_GUARD_1357924680)
#define FUNCTIONCONCAT_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



// Base class header file...
#include <xalanc/XPath/Function.hpp>



XALAN_CPP_NAMESPACE_BEGIN



/**
 * XPath implementation of "concat" function.
 */
class XALAN_XPATH_EXPORT FunctionConcat : public Function
{
public:

    typedef Function    ParentType;

    FunctionConcat();

    virtual
    ~FunctionConcat();  

    // These methods are inherited from Function ...

    virtual XObjectPtr
    execute(
            XPathExecutionContext&          executionContext,
            XalanNode*                      context,
            const XObjectArgVectorType&     args,
            const Locator*                  locator) const;

    XObjectPtr
    execute(
            XPathExecutionContext&      executionContext,
            XalanNode*                  context,
            const XObjectPtr            arg1,
            const XObjectPtr            arg2,
            const Locator*              locator) const;

    XObjectPtr
    execute(
            XPathExecutionContext&      executionContext,
            XalanNode*                  context,            
            const XObjectPtr            arg1,
            const XObjectPtr            arg2,
            const XObjectPtr            arg3,
            const Locator*              locator) const;

    using ParentType::execute;

#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
    virtual Function*
#else
    virtual FunctionConcat*
#endif
    clone(MemoryManager& theManager) const;

protected:

    virtual const XalanDOMString&
    getError(XalanDOMString& theResult) const;

private:

    // Not implemented...
    FunctionConcat&
    operator=(const FunctionConcat&);

    bool
    operator==(const FunctionConcat&) const;
};



XALAN_CPP_NAMESPACE_END



#endif  // FUNCTIONCONCAT_HEADER_GUARD_1357924680
