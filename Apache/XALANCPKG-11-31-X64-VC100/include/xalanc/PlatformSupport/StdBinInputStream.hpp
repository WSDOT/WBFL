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

#if !defined(XALAN_STDBININPUTSTREAM_HEADER_GUARD)
#define XALAN_STDBININPUTSTREAM_HEADER_GUARD



// Base include file.  Must be first.
#include <xalanc/PlatformSupport/PlatformSupportDefinitions.hpp>



#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iosfwd>
#endif



#include <xercesc/util/BinInputStream.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_PLATFORMSUPPORT_EXPORT StdBinInputStream : public XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream
{
public:

    typedef XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream   ParentType;

#if defined(XALAN_NO_STD_NAMESPACE)
    typedef istream         StreamType;
#else
    typedef std::istream    StreamType;
#endif


    StdBinInputStream(StreamType&   theStream);

    virtual
    ~StdBinInputStream();

    virtual XalanFilePos
    curPos() const;

    virtual XalanSize_t
    readBytes(
            XMLByte* const      toFill,
            const XalanSize_t   maxToRead);

    virtual const XalanDOMChar*
    getContentType() const;

private:

    // Unimplemented...
    StdBinInputStream(const StdBinInputStream&  theSource);

    bool
    operator==(const StdBinInputStream& theSource) const;

    StdBinInputStream&
    operator=(const StdBinInputStream&  theSource);


    // Data members...
    StreamType&     m_stream;
};



XALAN_CPP_NAMESPACE_END



#endif  // XALAN_STDBININPUTSTREAM_HEADER_GUARD
