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
#if !defined(XALAN_PROBLEMLISTENERDEFAULT_HEADER_GUARD)
#define XALAN_PROBLEMLISTENERDEFAULT_HEADER_GUARD



// Base include file.  Must be first.
#include "XSLTDefinitions.hpp"



// Xalan header files.
#include <xalanc/XSLT/ProblemListener.hpp>



XALAN_DECLARE_XERCES_CLASS(MemoryManager)



XALAN_CPP_NAMESPACE_BEGIN



XALAN_USING_XERCES(MemoryManager)



/**
 * The implementation of the default error handling for Xalan.
 */
class XALAN_XSLT_EXPORT ProblemListenerDefault : public ProblemListener
{
public:

    ProblemListenerDefault(
            MemoryManager&  theManager, 
            PrintWriter*    pw = 0);

    virtual
    ~ProblemListenerDefault();


    // These methods are inherited from ProblemListener ...

    virtual void
    setPrintWriter(PrintWriter*     pw);

    virtual void
    problem(
            eSource                 source,
            eClassification         classification,
            const XalanDOMString&   msg,
            const Locator*          locator,
            const XalanNode*        sourceNode);

    virtual void
    problem(
            eSource                 source,
            eClassification         classification,
            const XalanDOMString&   msg,
            const XalanNode*        sourceNode);

    virtual void
    problem(
            eSource                     source,
            eClassification             classification, 
            const XalanNode*            sourceNode,
            const ElemTemplateElement*  styleNode,
            const XalanDOMString&       msg,
            const XalanDOMChar*         uri,
            XalanFileLoc                lineNo,
            XalanFileLoc                charOffset);

    // These methods are new...

    PrintWriter*
    getPrintWriter() const
    {
        return m_pw;
    }

    static void
    defaultFormat(
            PrintWriter&            pw,
            eSource                 source,
            eClassification         classification,
            const XalanDOMString&   msg,
            const Locator*          locator,
            const XalanNode*        sourceNode)
    {
        ProblemListenerBase::defaultFormat(
            pw,
            source,
            classification,
            msg,
            locator,
            sourceNode);
    }

    static void
    defaultFormat(
            PrintWriter&            pw,
            eSource                 source,
            eClassification         classification,
            const XalanDOMString&   msg,
            const XalanNode*        sourceNode)
    {
        ProblemListenerBase::defaultFormat(
            pw,
            source,
            classification,
            msg,
            sourceNode);
    }

    static void
    defaultFormat(
            PrintWriter&                pw,
            eSource                     source,
            eClassification             classification,
            const XalanNode*            sourceNode,
            const ElemTemplateElement*  styleNode,
            const XalanDOMString&       msg,
            const XalanDOMChar*         uri,
            XalanFileLoc                lineNo,
            XalanFileLoc                charOffset);

private:

    MemoryManager&  m_memoryManager;

    PrintWriter*    m_pw;
};



XALAN_CPP_NAMESPACE_END



#endif  // XALAN_PROBLEMLISTENERDEFAULT_HEADER_GUARD
