///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2019  Washington State Department of Transportation
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

// stdafx.cpp : source file that includes just the standard includes
// Core.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


bool operator<(REFIID a,REFIID b)
{
   /*
   typedef struct _GUID {
      unsigned long  Data1;
      unsigned short Data2;
      unsigned short Data3;
      unsigned char  Data4[8];} GUID;
    */

    if ( a.Data1 > b.Data1 )
       return false;
    if ( a.Data1 < b.Data1 )
       return true;

    if ( a.Data2 > b.Data2 )
       return false;
    if ( a.Data2 < b.Data2 )
       return true;

    if ( a.Data3 > b.Data3 )
       return false;
    if ( a.Data3 < b.Data3 )
       return true;

    for ( int i = 0; i < 8; i++ )
    {
       if ( a.Data4[i] > b.Data4[i] )
          return false;
       if ( a.Data4[i] < b.Data4[i] )
          return true;
    }

    return false;
}
