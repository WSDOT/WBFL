///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEMODELING_ALIGNMENTOBSERVER_H_
#define INCLUDED_BRIDGEMODELING_ALIGNMENTOBSERVER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingLib.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bmfBridge;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bmfAlignmentObserver

   This is a COM class that sinks events on an Alignment object and
   relays those events to a bmfBridge object


DESCRIPTION
   This is a COM class that sinks events on an Alignment object and
   relays those events to a bmfBridge object. bmfBridge was originally
   built for a C++ cogo engine. The new cogo engine is written in COM and
   fires COM-style events. In order to avoid re-writing bmfBridge as a COM
   object (and thus the entire library), this class servers as a private
   adaptor/proxy object.

COPYRIGHT
   Copyright © 2004
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 06.04.2004 : Created class
*****************************************************************************/
class ATL_NO_VTABLE bmfAlignmentObserver :
public CComObjectRootEx<CComSingleThreadModel>,
public IPathEvents
{
public:
   bmfAlignmentObserver()
   {
      m_pBridge = 0;
   }

   void FinalRelease();

   void SetBridge(bmfBridge* pBridge);
   void ReleaseBridge();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(bmfAlignmentObserver)
   COM_INTERFACE_ENTRY(IPathEvents)
END_COM_MAP()

public:
   STDMETHOD(OnPathChanged)(/*[in]*/ IPath* alignment);
	STDMETHOD(OnProfileChanged)(/*[in]*/ IProfile* profile);

private:
   bmfBridge* m_pBridge;
   DWORD m_dwCookie;
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_ALIGNMENTOBSERVER_H_
