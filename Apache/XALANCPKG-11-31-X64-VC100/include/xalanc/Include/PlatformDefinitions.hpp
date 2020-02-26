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

#if !defined(PLATFORMDEFINITIONS_HEADER_GUARD_1357924680)
#define PLATFORMDEFINITIONS_HEADER_GUARD_1357924680

#if defined(__cplusplus)
# include "xercesc/util/XercesDefs.hpp"
#else
/* Include xercesc autoconf to define XMLCh when using a 'C' compiler. */
# include "xercesc/util/Xerces_autoconf_config.hpp"
# include "xercesc/util/XercesVersion.hpp"
#endif

#if defined(_MSC_VER)
#include "VCPPDefinitions.hpp"
#elif defined(__GNUC__)
#include "GCCDefinitions.hpp"
#elif defined(_AIX)
#include "AIXDefinitions.hpp"
#elif defined(__hpux)
#include "HPUXDefinitions.hpp"
#elif defined(SOLARIS)
#include "SolarisDefinitions.hpp"
#elif defined(OS390)
#include "OS390Definitions.hpp"
#elif defined(OS400)
#include "OS400Definitions.hpp"
#elif defined(__DECCXX)
#include "TRU64Definitions.hpp"
#elif defined(__INTEL_COMPILER)
#include "IntelDefinitions.hpp"
#elif defined(__IBMCPP__) && defined(__TOS_LINUX__)
// This is for Linux PPC using the IBM xlC compiler.
#include "AIXDefinitions.hpp"
#else
#error Unknown compiler!
#endif

#include "XalanVersion.hpp"

#if defined(__cplusplus)

// ---------------------------------------------------------------------------
// Define namespace symbols if the compiler supports it.
// ---------------------------------------------------------------------------
#if defined(XALAN_HAS_CPP_NAMESPACE)
    #define XALAN_CPP_NAMESPACE_BEGIN namespace XALAN_CPP_NAMESPACE {
    #define XALAN_CPP_NAMESPACE_END  }
    #define XALAN_CPP_NAMESPACE_USE using namespace XALAN_CPP_NAMESPACE;
    #define XALAN_CPP_NAMESPACE_QUALIFIER XALAN_CPP_NAMESPACE::
    #define XALAN_USING(NAMESPACE,NAME) using NAMESPACE :: NAME;
    #define XALAN_DECLARE_CLASS(NAMESPACE,NAME) namespace NAMESPACE { class NAME; }
    #define XALAN_DECLARE_STRUCT(NAMESPACE,NAME) namespace NAMESPACE { struct NAME; }

    namespace XALAN_CPP_NAMESPACE { }
    namespace xalanc = XALAN_CPP_NAMESPACE;
#else
    #if defined(XALAN_CPP_NAMESPACE)
    #undef XALAN_CPP_NAMESPACE
    #endif

    #define XALAN_CPP_NAMESPACE
    #define XALAN_CPP_NAMESPACE_BEGIN
    #define XALAN_CPP_NAMESPACE_END
    #define XALAN_CPP_NAMESPACE_USE
    #define XALAN_CPP_NAMESPACE_QUALIFIER
    #define XALAN_USING(NAMESPACE,NAME)
    #define XALAN_DECLARE_CLASS(NAMESPACE,NAME) class NAME;
    #define XALAN_DECLARE_STRUCT(NAMESPACE,NAME) struct NAME;
    #if !defined(XALAN_NO_STD_NAMESPACE)
        #define XALAN_NO_STD_NAMESPACE
    #endif
#endif


#if defined(XALAN_NO_STD_NAMESPACE)
    #define XALAN_USING_STD(NAME)
    #define XALAN_STD_QUALIFIER 
#else
    #define XALAN_USING_STD(NAME) using std :: NAME;
    #define XALAN_STD_QUALIFIER  std ::
#endif

#define XALAN_DECLARE_XALAN_CLASS(NAME) XALAN_DECLARE_CLASS(XALAN_CPP_NAMESPACE, NAME)
#define XALAN_DECLARE_XALAN_STRUCT(NAME) XALAN_DECLARE_STRUCT(XALAN_CPP_NAMESPACE, NAME)
#define XALAN_USING_XALAN(NAME) XALAN_USING(XALAN_CPP_NAMESPACE, NAME)


#if defined(XERCES_HAS_CPP_NAMESPACE)
    #define XALAN_USING_XERCES(NAME) XALAN_USING(XERCES_CPP_NAMESPACE, NAME)
    #define XALAN_DECLARE_XERCES_CLASS(NAME) XALAN_DECLARE_CLASS(XERCES_CPP_NAMESPACE, NAME)
    #define XALAN_DECLARE_XERCES_STRUCT(NAME) XALAN_DECLARE_STRUCT(XERCES_CPP_NAMESPACE, NAME)
#else
    #define XERCES_CPP_NAMESPACE_QUALIFIER
    #define XERCES_CPP_NAMESPACE_BEGIN
    #define XERCES_CPP_NAMESPACE_END
    #define XERCES_CPP_NAMESPACE_USE
    #define XALAN_USING_XERCES(NAME)
    #define XALAN_DECLARE_XERCES_CLASS(NAME) class NAME;
    #define XALAN_DECLARE_XERCES_STRUCT(NAME) struct NAME;
#endif



#include <cstddef>



XALAN_CPP_NAMESPACE_BEGIN

#if XERCES_VERSION_MAJOR < 3
typedef unsigned int    XalanSize_t;
typedef unsigned int    XalanFilePos;
typedef XMLSSize_t      XalanFileLoc;
#else
typedef XMLSize_t       XalanSize_t;
typedef XMLFilePos      XalanFilePos;
typedef XMLFileLoc      XalanFileLoc;
#endif

typedef XMLCh           XalanDOMChar;
typedef unsigned int    XalanUnicodeChar;
typedef XMLSSize_t      XalanSSize_t;

template<bool value>
struct XalanCompileErrorBoolean
{
    char    foo[value];
};
 
XALAN_CPP_NAMESPACE_END


#if !defined(XALAN_NO_LONG_LONG)
typedef unsigned long long XALAN_UINT64;
typedef long long  XALAN_INT64;
#endif

#define XALAN_STATIC_ASSERT(expr) XALAN_CPP_NAMESPACE_QUALIFIER XalanCompileErrorBoolean<bool(expr)>()



#endif // __cplusplus



#endif  // PLATFORMDEFINITIONS_HEADER_GUARD_1357924680
