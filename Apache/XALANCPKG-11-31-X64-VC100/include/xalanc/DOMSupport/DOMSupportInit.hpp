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

#if !defined(DOMSUPPORTINIT_INCLUDE_GUARD_1357924680)
#define DOMSUPPORTINIT_INCLUDE_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/DOMSupport/DOMSupportDefinitions.hpp>



#include <xalanc/PlatformSupport/PlatformSupportInit.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_DOMSUPPORT_EXPORT DOMSupportInit
{
public:

    explicit
    DOMSupportInit(MemoryManager& theManager);

    ~DOMSupportInit();

private:

    // Not implemented...
    DOMSupportInit(const DOMSupportInit&);

    DOMSupportInit&
    operator=(const DOMSupportInit&);

    
    static void
    initialize(MemoryManager& theManager);

    static void
    terminate();

    const PlatformSupportInit   m_platformSupportInit;

    static unsigned long        s_initCounter;
};



XALAN_CPP_NAMESPACE_END



#endif  // !defined(DOMSUPPORTINIT_INCLUDE_GUARD_1357924680)
