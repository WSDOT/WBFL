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
#if !defined(XALAN_TraceListenerDefault_HEADER_GUARD)
#define XALAN_TraceListenerDefault_HEADER_GUARD 



// Base include file.  Must be first.
#include <xalanc/XSLT/XSLTDefinitions.hpp>



// Base class header file...
#include <xalanc/XSLT/TraceListener.hpp>

#include <xalanc/Include/XalanMemoryManagement.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class DOMSupport;
class ElemTemplateElement;
class ExecutionContext;
class NodeRefListBase;
class PrintWriter;
class XPathExecutionContext;



class XALAN_XSLT_EXPORT TraceListenerDefault : public TraceListener
{
public:

    TraceListenerDefault(
            PrintWriter&            thePrintWriter,
            MemoryManager&          theManager,
            bool                    traceTemplates = false,
            bool                    traceElements = false,
            bool                    traceGeneration = false,
            bool                    traceSelection = false);

    TraceListenerDefault(
            XPathExecutionContext&  theExecutionContext,
            PrintWriter&            thePrintWriter,
            MemoryManager&          theManager,
            bool                    traceTemplates = false,
            bool                    traceElements = false,
            bool                    traceGeneration = false,
            bool                    traceSelection = false);

    virtual
    ~TraceListenerDefault();

    virtual void
    trace(const TracerEvent&    ev);

    virtual void
    selected(const SelectionEvent&  ev);

    virtual void
    generated(const GenerateEvent&  ev);

    bool
    getTraceTemplates() const
    {
        return m_traceTemplates;
    }

    void
    setTraceTemplates(bool  b)
    {
        m_traceTemplates = b;
    }

    bool
    getTraceElement() const
    {
        return m_traceElements;
    }

    void
    setTraceElements(bool   b)
    {
        m_traceElements = b;
    }

    bool
    getTraceGeneration() const
    {
        return m_traceGeneration;
    }

    void
    setTraceGeneration(bool     b)
    {
        m_traceGeneration = b;
    }

    bool
    getTraceSelection() const
    {
        return m_traceSelection;
    }

    void
    setTraceSelection(bool  b)
    {
        m_traceSelection = b;
    }

private:

    void
    processNodeList(const NodeRefListBase&  nl);

    void
    printNodeInfo(const ElemTemplateElement&    node);


    // Data members...
    XPathExecutionContext*  m_executionContext;

    PrintWriter&            m_printWriter;

    bool                    m_traceTemplates;

    bool                    m_traceElements;

    bool                    m_traceGeneration;

    bool                    m_traceSelection;

    MemoryManager&          m_memoryManager;
};



XALAN_CPP_NAMESPACE_END



#endif //XALAN_TraceListenerDefault_HEADER_GUARD 
