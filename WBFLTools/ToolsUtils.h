///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2010  Washington State Department of Transportation
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

#if !defined WBFLTOOLS_UTILS_H_
#define WBFLTOOLS_UTILS_H_

#include <string>

inline CComBSTR CreateErrorMsgStr1(UINT nid, BSTR someStr)
{
   USES_CONVERSION;
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   CComBSTR bs(someStr);
   int cOut = _stprintf_s( msg, str, OLE2T(bs));
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline CComBSTR CreateErrorMsgStr2(UINT nid, BSTR someStr1, BSTR someStr2)
{
   USES_CONVERSION;
   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nid, str, 256);
   TCHAR msg[256];
   CComBSTR bs1(someStr1);
   CComBSTR bs2(someStr2);
   int cOut = _stprintf_s( msg, str, OLE2T(bs1),OLE2T(bs2));
   ATLASSERT( cOut < 256 );
   return CComBSTR(msg);
}

inline LPCOLESTR GetHelpFile()
{
   USES_CONVERSION;
   return OLESTR("WBFLTools.chm");
}

inline bool find_replace_all(std::_tstring* ptarget, const std::_tstring& find, const std::_tstring& replace)
{
   bool ret=false;
   std::_tstring::size_type spos=0;
   std::_tstring::size_type epos;
   
   while ( (epos=ptarget->find(find,spos)) != std::_tstring::npos)
   {
      ret=true;
      ptarget->replace(epos,find.size(),replace);
      spos = epos+1;
   }

   return ret;
}

inline void GetTypeNameFromVariant(VARIANT& rvar, _bstr_t* name)
{

   switch ( rvar.vt)
   {
   case VT_BSTR:
      *name = _bstr_t("VT_BSTR");
      break;
   case VT_R4:
      *name = _bstr_t("VT_R4");
      break;
   case VT_R8:
      *name = _bstr_t("VT_R8");
      break;
   case VT_I2:
      *name = _bstr_t("VT_I2");
      break;
   case VT_I4:
      *name = _bstr_t("VT_I4");
      break;
   case VT_I8:
      *name = _bstr_t("VT_I8");
      break;
   case VT_BOOL:
      *name = _bstr_t("VT_BOOL");
      break;
   case VT_UI2:
      *name = _bstr_t("VT_UI2");
      break;
   case VT_UI4:
      *name = _bstr_t("VT_UI4");
      break;
   case VT_INT:
      *name = _bstr_t("VT_INT");
      break;
   case VT_UINT:
      *name = _bstr_t("VT_UINT");
      break;
   case VT_UNKNOWN:
      *name = _bstr_t("VT_UNKNOWN");
      break;
   case VT_DISPATCH:
      *name = _bstr_t("VT_DISPATCH");
      break;

   default:
      // all other kinds not supported
      *name = _bstr_t("VT_EMPTY");
      break;
   }
}


#endif // WBFLTOOLS_UTILS_H_
