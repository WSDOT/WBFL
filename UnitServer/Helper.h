///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2021  Washington State Department of Transportation
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
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_HELPER_H_
#define INCLUDED_HELPER_H_

#include <UnitServer.hh>

class FindUnitType
{
public:
   FindUnitType(const BSTR& bstr) : m_bstrTarget(bstr) {}
   bool operator()(const CComVariant& var)
   {
      _ASSERT( var.vt == VT_UNKNOWN );
      CComQIPtr<IUnitType,&IID_IUnitType> pUnitType( var.punkVal );
      CComBSTR bstrLabel;
      pUnitType->get_Label( &bstrLabel );
      return (_tcscmp( m_bstrTarget, bstrLabel ) == 0);
   }

private:
   CComBSTR m_bstrTarget;
};

inline LPCOLESTR GetHelpFile()
{
   return _T("WBFLUnitServer.chm");
}

#endif