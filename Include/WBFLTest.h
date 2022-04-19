#ifndef INCLUDED_WBFLTEST_H_
#define INCLUDED_WBFLTEST_H_

///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


// Macro for reporting test outcomes
// Requires iostream header
#ifndef _IOSTREAM_
#include <iostream>
#endif

inline void _try_test(bool bPassed,const char* file,long line)  {std::cout << file << "(" << line << ")" << " : "; std::cout << ( bPassed ? "Passed" : "***Failed***" ) << std::endl; }
#ifdef UNITTEST_NOASSERT
#define TRY_TEST(x,y) _try_test(x==y,__FILE__,__LINE__)
#else
#define TRY_TEST(x,y) {bool bPassed = (x==y); _try_test(bPassed,__FILE__,__LINE__); ATLASSERT(bPassed);}
#endif

#endif // INCLUDED_WBFLTEST_H_