///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_FLAGS_H_
#define INCLUDED_SYSTEM_FLAGS_H_
#pragma once

#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysFlags

   Utility class for manipulating bit flags.


DESCRIPTION
   Utility class for manipulating bit flags.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.15.1997 : Created file
*****************************************************************************/

template <class T>
class sysFlags
{
public:
   //------------------------------------------------------------------------
   // Sets the bits defined by mask in flag.
   static void Set(T* flag,T mask);

   //------------------------------------------------------------------------
   // Clears the bits defined by mask in flag.
   static void Clear(T* flag,T mask);

   //------------------------------------------------------------------------
   // Clears all the bits in flag.
   static void ClearAll(T* flag);

   //------------------------------------------------------------------------
   // Returns true if the bits defined by mask are set in flag.
   static bool IsSet(T flag,T mask);

   //------------------------------------------------------------------------
   // Returns true if the bits defined by mask are clear in flag.
   static bool IsClear(T flag,T mask);
};

// INLINE METHODS
//
template <class T>
void sysFlags<T>::Set(T* flag,T mask)
{
   (*flag) |= mask;
}

template <class T>
void sysFlags<T>::Clear(T* flag,T mask)
{
   (*flag) &= ~mask;
}

template <class T>
void sysFlags<T>::ClearAll(T* flag)
{
   *flag = 0;
}

template <class T>
bool sysFlags<T>::IsSet(T flag,T mask)
{
   return (flag & mask) ? true : false;
}

template <class T>
bool sysFlags<T>::IsClear(T flag,T mask)
{
   return !IsSet(flag,mask);
}

#endif // INCLUDED_SYSTEM_FLAGS_H_
