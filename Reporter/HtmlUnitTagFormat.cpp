///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include "HtmlUnitTagFormat.h"

/****************************************************************************
CLASS
   rptHtmlUnitTagFormat
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
std::_tstring rptHtmlUnitTagFormat::Format(const std::_tstring& tag)
{
   std::_tostringstream stm;
   std::_tstring fmt;
   bool bSupOn = false;
   bool bSubOn = false;
   IndexType len = tag.length();
   for ( IndexType i = 0; i < len; i++ )
   {
      if ( tag[i] == _T('^') )
      {
         // ^ = start of superscript or end of subscript
         if ( !bSupOn && !bSubOn )
         {
            // neither in a super or subscript block... start a superscript
            stm << _T("<SUP>");
            bSupOn = true;
         }
         else if ( bSubOn )
         {
            // currently in a subscript block... end it
            stm << _T("</SUB>");
            bSubOn = false;
         }
      }
      else if ( tag[i] == _T('_') )
      {
         // _ = start of subscript or end of superscript
         if ( !bSupOn && !bSubOn )
         {
            // neither in a sub or superscript block... start a subscript
            stm << _T("<SUB>");
            bSubOn = true;
         }
         else if ( bSupOn )
         {
            // currently in a superscript block... end it
            stm << _T("</SUP>");
            bSupOn = false;
         }
      }
      else if ( bSupOn && (tag[i] == _T('/') || tag[i] == _T(' ') ) )
      {
         stm << _T("</SUP>") << tag[i];
         bSupOn = false;
      }
      else if ( bSubOn && tag[i] == _T(' ') )
      {
         stm << _T("</SUB>") << tag[i];
         bSubOn = false;
      }
      else
      {
         stm << tag[i];
      }
   }

   // if super got left on, turn it off now.
   if ( bSupOn )
   {
      stm << _T("</SUP>");
      bSupOn = false;
   }

   // if subscript got left on, turn it off now.
   if ( bSubOn )
   {
      stm << _T("</SUB>");
      bSubOn = false;
   }

   return stm.str();
}
