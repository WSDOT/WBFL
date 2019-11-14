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

#if !defined(XALANNLSMESSAGELOADER_HEADER_GUARD_1357924680)
#define XALANNLSMESSAGELOADER_HEADER_GUARD_1357924680

#ifdef XALAN_NLS_MSG_LOADER

#include <xalanc/PlatformSupport/XalanMessageLoader.hpp>

#include <nl_types.h>

XALAN_CPP_NAMESPACE_BEGIN

class XALAN_PLATFORMSUPPORT_EXPORT XalanNLSMessageLoader : public XalanMessageLoader 

{
public:

    XalanNLSMessageLoader(MemoryManager& theManager);

    virtual
    ~XalanNLSMessageLoader();

protected:

    // -----------------------------------------------------------------------
    //  Implementation of the virtual message loader API
    // -----------------------------------------------------------------------
    virtual bool
    loadMsg(
            XalanMessages::Codes    msgToLoad,
            XalanDOMChar*           toFill,
            XalanSize_t             maxChars
    );

private:

    XalanNLSMessageLoader(const XalanNLSMessageLoader&);

    XalanNLSMessageLoader&
    operator=(const XalanNLSMessageLoader&);

 
    nl_catd     m_catalogHandle;
    
    MemoryManager& m_memoryManager;
};

XALAN_CPP_NAMESPACE_END

#endif // XALAN_NLS_MSG_LOADER

#endif // XALANNLSMESSAGELOADER_HEADER_GUARD_1357924680
