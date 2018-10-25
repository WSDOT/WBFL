///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
IEAFViewController

Interface for programitically controlling a view.

DESCRIPTION
Interface for programitically controlling a view. This interface provides
the basic functionality such as moving and sizing. Objects with extended
versions of this interface can provide additional functionality.
*****************************************************************************/
// {B44ECBF9-183F-4363-A2BA-7A38E21C085C}
DEFINE_GUID(IID_IEAFViewController,
   0xb44ecbf9, 0x183f, 0x4363, 0xa2, 0xba, 0x7a, 0x38, 0xe2, 0x1c, 0x8, 0x5c);

struct __declspec(uuid("{B44ECBF9-183F-4363-A2BA-7A38E21C085C}")) IEAFViewController;

interface IEAFViewController : IUnknown
{
   // Returns true if the view is open
   virtual bool IsOpen() const = 0;

   // Closes the view
   virtual void Close() = 0;

   // implement later....
   //virtual void Move(INT x, INT y) = 0;
   //virtual void Size(INT x, INT y) = 0;
   //virtual void GetSize() = 0;
   //virtual void GetPosition() = 0;
   //virtual void GetState() = 0;
   virtual void Minimize() = 0;
   virtual void Maximize() = 0;
   virtual void Restore() = 0;
};
