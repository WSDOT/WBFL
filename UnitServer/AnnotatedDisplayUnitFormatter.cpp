///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// AnnotatedDisplayUnitFormatter.cpp : Implementation of CAnnotatedDisplayUnitFormatter
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "AnnotatedDisplayUnitFormatter.h"
#include <stdio.h>
#include <xutility>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAnnotatedDisplayUnitFormatter
STDMETHODIMP CAnnotatedDisplayUnitFormatter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
   {
	   &IID_IAnnotatedDisplayUnitFormatter,
	   &IID_IDisplayUnitFormatter,
   };
   for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
   {
	   if (::InlineIsEqualGUID(*arr[i],riid))
		   return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Width(Uint32 *width)
{
   CHECK_RETVAL(width);
   *width = m_Width;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Precision(Uint32 *precision)
{
   CHECK_RETVAL(precision);
   *precision = m_Precision;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Notation(NumericFormatType* notation)
{
   CHECK_RETVAL(notation);
   *notation = m_Notation;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Justification(TextJustificationType* justify)
{
   CHECK_RETVAL(justify);
   *justify = m_Justify;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_ZeroTolerance(Float64* zeroTol)
{
   CHECK_RETVAL(zeroTol);
   *zeroTol = m_ZeroTolerance;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::FormatSpecifiers(Uint32 width,Uint32 precision,TextJustificationType justify,NumericFormatType notation,Float64 zeroTol)
{
   if ( width < 0 || precision < 0 || zeroTol < 0)
      return E_INVALIDARG;

   if ( m_Width != width || m_Precision != precision || m_Notation != notation || m_Justify != justify || !IsEqual(m_ZeroTolerance,zeroTol))
   {
      m_Width         = width;
      m_Precision     = precision;
      m_Notation      = notation;
      m_Justify       = justify;
      m_ZeroTolerance = zeroTol;

      Fire_OnFormatChanged();
   }

   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::put_OffsetDigits(Uint32 nDigits)
{
   if ( nDigits < 0 )
      return E_INVALIDARG;

   if ( m_nDigits != nDigits)
   {
      m_nDigits = nDigits;
      Fire_OnFormatChanged();
   }

   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_OffsetDigits(Uint32* nDigits)
{
   CHECK_RETVAL(nDigits);
   *nDigits = m_nDigits;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::put_Multiplier(Float64 multiplier)
{
   if ( !IsEqual(m_Multiplier,multiplier) )
   {
      m_Multiplier = multiplier;
      Fire_OnFormatChanged();
   }

   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Multiplier(Float64 *multiplier)
{
   CHECK_RETVAL(multiplier);
   *multiplier = m_Multiplier;
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::put_Annotation(BSTR bstrAnnotation)
{
   CHECK_IN(bstrAnnotation);

   // Check if the annotation string is really going to change. If not,
   // just get the heck outta here.
   if ( _tcscmp(m_bstrAnnotation,bstrAnnotation) == 0 )
      return S_OK;

   m_bstrAnnotation = bstrAnnotation;

   m_bstrSeperator = L"";
   m_bstrSuffix    = L"";

   // Parse the annotation string into the seperator and suffix tokens

   OLECHAR* next_token;
   OLECHAR* token = _tcstok_s(CComBSTR(bstrAnnotation),CComBSTR(","),&next_token);
   if ( token )
   {
      // Check if the string leads with a delimeter
      // If so, token is the suffix

      if ( bstrAnnotation[0] == L',' )
      {
         m_bstrSeperator = L"";
         m_bstrSuffix = token;
      }
      else
      {
         m_bstrSeperator = token;
      }

      token = _tcstok_s(NULL,L",",&next_token);

      if ( token )
         m_bstrSuffix = token;
   }

   Fire_OnFormatChanged();

   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_Annotation(BSTR* bstrAnnotation)
{
   CHECK_RETSTRING(bstrAnnotation);
   *bstrAnnotation = m_bstrAnnotation.Copy();
   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::Format(Float64 cv, BSTR tag,BSTR* fmtString)
{
   // Override default implementation
   CHECK_RETSTRING(fmtString);

   if ( IsZero(cv,m_ZeroTolerance) )
      cv = 0.00;

   // This method works with positive values
   // Save the sign (so we can restore it later) and
   // take the absolute value of cv
   int sign = BinarySign(cv);
   cv = fabs(cv);

   USES_CONVERSION;

   // Indicates if the annotations are to be used
   bool bShowTag = ( tag != 0  ? true : false );

   Float64 seperatorLocation = pow(10.0,(Float64)m_nDigits); // Indicates where cv is to be seperated

   long v1 = (long)floor(cv/seperatorLocation); // Value left of the seperator
   Float64 v2 = cv - v1*seperatorLocation; // Value to the right of the seperator
   
   // Check to make sure that v2 is not basically the same as the seperatorLocation
   // i.e. station = 69500.00, sometimes = 694+100.00 instead of 695+00.00 
   if ( IsEqual(v2,seperatorLocation,0.0001) )
   {
      v2 = 0;
      v1++;
   }

   v2 *= m_Multiplier;

   Float64 accuracy = max(1.0/pow(10.0,Float64(m_Precision)),0.0001);
   v2 = RoundOff(v2,accuracy);

   // compute width of character buffer
   Uint32 width = m_Precision; // # of digits after decimal point
   width += (m_Precision > 0) ? 1 : 0; // Add one for the '.' if precision > 0

   // Number of digits before decimal point
   Uint32 vfloor = (Uint32)v2;
   if (vfloor<seperatorLocation)
   {
      width += _cpp_max(m_nDigits, 1);
   }
   else
   {
      Float64 ltmp = log10(v2);
      width += (Uint32)(ltmp) + 1;
   }

   // compute length of character string
   int nChar;
   nChar = (v1 == 0) ? 1 : (int)log10((Float64)v1) + 1;
   nChar += width;
   nChar += _tcslen(m_bstrSeperator);
   nChar += _tcslen(m_bstrSuffix);
   nChar += 1; // add one for the '\n'
   nChar += (sign < 0) ? 1 : 0; // for the "-" if the value is negative

   // Build the string
   const int BUFF_SIZE=32;
   _ASSERT(nChar<BUFF_SIZE);
   nChar = _cpp_min(nChar,BUFF_SIZE); // assert if we blow out buffer, but do this also so we don't crash

   TCHAR pBuffer[BUFF_SIZE];
   if ( tag == NULL )
      _stprintf_s(pBuffer,nChar,_T("%s%d %0*.*f"),sign < 0 ? _T("-") : _T(""),v1,width,m_Precision,v2);
   else
      _stprintf_s(pBuffer,nChar,_T("%s%d%s%0*.*f%s"),sign < 0 ? _T("-") : _T(""),v1,OLE2T(m_bstrSeperator),width,m_Precision,v2,OLE2T(m_bstrSuffix));

   // Write the string into a different buffer so it is the right width and justification
   size_t sizeBuffer2 = _cpp_max((Uint32)_tcslen(pBuffer),m_Width)+1;
   _ASSERT(sizeBuffer2<BUFF_SIZE);
   TCHAR pBuffer2[BUFF_SIZE];

   if ( m_Justify == tjLeft )
      _stprintf_s(pBuffer2,sizeBuffer2,_T("%-*s"),m_Width,pBuffer);
   else
      _stprintf_s(pBuffer2,sizeBuffer2,_T("%*s"),m_Width,pBuffer);


   CComBSTR bstrBuffer(pBuffer2);
   *fmtString = bstrBuffer.Detach();

   return S_OK;
}

STDMETHODIMP CAnnotatedDisplayUnitFormatter::get_UsesTag(VARIANT_BOOL *bUsesTag)
{
   CHECK_RETVAL(bUsesTag);
   *bUsesTag = VARIANT_FALSE;
   return S_OK;
}
