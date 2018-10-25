///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_UNITMGT_LIBRARY_H_
#define INCLUDED_UNITMGT_LIBRARY_H_
#pragma once

// SYSTEM INCLUDES
//
#include <UnitMgt\LibraryT.h>
#include <UnitMgt\IndirectMeasure.h>
#include <UnitMgt\UnitMgtExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// :WARNING: Order is important here.
// unitmgtLibraryT uses unitmgtXEntryNotFoundT.  If the library is
// instantiated first, it will cause the exception to be instantiated
// as well.  The exception must be instantiated first so that it is
// declared as exported.

UNITMGTTPL unitmgtXEntryNotFoundT<  std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure>;
UNITMGTTPL unitmgtLibraryT<         std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure>;
UNITMGTTPL unitmgtLibraryIterT<     std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure>;
UNITMGTTPL unitmgtConstLibraryIterT<std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure>;

typedef unitmgtLibraryT<         std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure> unitmgtLibrary;
typedef unitmgtLibraryIterT<     std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure> unitmgtLibraryIter;
typedef unitmgtConstLibraryIterT<std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure> unitmgtConstLibraryIter;
typedef unitmgtXEntryNotFoundT<  std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >, unitmgtIndirectMeasure> unitmgtEntryNotFound;

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_UNITMGT_LIBRARY_H_
