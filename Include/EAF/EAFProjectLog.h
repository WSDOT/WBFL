///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#pragma once

/*****************************************************************************
INTERFACE
   IEAFProjectLog

   Interface for project wide message/error logging.

DESCRIPTION
   Interface for project wide message/error logging.
*****************************************************************************/
// {95DE8B60-2D53-11d2-8EB4-006097DF3C68}
DEFINE_GUID(IID_IEAFProjectLog,
0x95DE8B60, 0x2D53, 0x11d2, 0x8E, 0xB4, 0x00, 0x60, 0x97, 0xDF, 0x3C, 0x68);
interface IEAFProjectLog : IUnknown
{
   //------------------------------------------------------------------------
   // Returns the name of the log file
   virtual CString GetName() = 0;

   //------------------------------------------------------------------------
   // Writes a message to the log file
   virtual void LogMessage( LPCTSTR lpszMsg ) = 0;

   //------------------------------------------------------------------------
   // Destroys the log file.
   virtual void Destroy() = 0;
};
