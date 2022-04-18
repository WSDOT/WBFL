///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// EAFComponentInfo.h : header file
//

// EAFComponentInfo - Objects that implement this interface provide information about an
// EAF Application component. An application component is an abstract idea that represents
// an installable piece of the overall application. A component could be an EAFAppPlugin object
// or it could be a collection of 3rd party Extension Agent objects that extend the capabilities
// of an application.

// {4962EEC7-5D25-48c7-8D4E-9F285DF05C34}
DEFINE_GUID(IID_IEAFComponentInfo, 
0x4962eec7, 0x5d25, 0x48c7, 0x8d, 0x4e, 0x9f, 0x28, 0x5d, 0xf0, 0x5c, 0x34);
struct __declspec(uuid("{4962EEC7-5D25-48c7-8D4E-9F285DF05C34}")) IEAFComponentInfo;// for __uuidof

class CEAFApp;

interface IEAFComponentInfo : IUnknown
{
   /// Called by the application framework to initialize this object
   /// This is a good place to validate license keys for 3rd party components
   virtual BOOL Init(CEAFApp* pApp) = 0;

   /// Called by the application framework to do any clean up while terminating
   virtual void Terminate() = 0;

   /// Return the name of your component
   virtual CString GetName() = 0;

   /// Return a description of the component
   virtual CString GetDescription() = 0;

   /// The icon returned goes in the About dialog
   virtual HICON GetIcon() = 0;

   /// Return true if there is additional information to be displayed about the componenet
   virtual bool HasMoreInfo() = 0;

   /// When this function is called, display more detailed information
   /// about your component
   virtual void OnMoreInfo() = 0;
};
