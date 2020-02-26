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
#if !defined(EXSLT_DYNAMIC_HEADER_GUARD_1357924680)
#define EXSLT_DYNAMIC_HEADER_GUARD_1357924680



#include <xalanc/XalanEXSLT/XalanEXSLTDefinitions.hpp>



#include <xalanc/XalanExtensions/XalanExtensions.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_EXSLT_EXPORT XalanEXSLTDynamicFunctionsInstaller : public XalanExtensionsInstaller
{
public:

    static void
    installLocal(XPathEnvSupportDefault&    theSupport);

    static void
    installGlobal(MemoryManager& theManager);

    static void
    uninstallLocal(XPathEnvSupportDefault&  theSupport);

    static void
    uninstallGlobal(MemoryManager& theManager);

private:

};



XALAN_CPP_NAMESPACE_END



#endif  // EXSLT_DYNAMIC_HEADER_GUARD_1357924680
