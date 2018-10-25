///////////////////////////////////////////////////////////////////////
// LBAM Utility - Longitindal Bridge Analysis Model
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


#if !defined INCLUDED_UTILITYUTILS_H_
#define INCLUDED_UTILITYUTILS_H_

#include "ComException.h"

// macros to help error processing
// short-hand version if consistent naming conventions are used
#define THROW_LBAMU(errNam) { ATLASSERT(0); throw CComException(_T(__FILE__),__LINE__, IDS_E_##errNam, LBAMU_E_##errNam, IDH_E_##errNam);}
#define THROW_LBAMU_MSG(errNam, msg) { ATLASSERT(0); throw CComException(_T(__FILE__),__LINE__, msg, LBAMU_E_##errNam, IDH_E_##errNam);}

inline CComBSTR GetHelpFile()
{
   return CComBSTR("WBFLLBAM.chm");
}

#endif 