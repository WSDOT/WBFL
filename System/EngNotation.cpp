///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

#include <System\EngNotation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void StreamEngNotation(std::ios_base& os,sysEngNotationData data)
{
   char buf[51];
   char* buffer;
   int decPos;
   int negative;
   int nDigits;
   int endOfBuf;

   nDigits = (data.sigDigits) ? data.nDigits : 4+data.nDigits;

   char tempBuffer[50];
   _ecvt_s(tempBuffer,50,data.value,nDigits,&decPos,&negative);

   buffer = buf;

   if (negative)
   {
      *buffer++ = '-';
   }

   strcpy_s(buffer,51,tempBuffer);

   int shift = decPos % 3;

   int exponent = decPos - shift;
   if (shift == 0 || decPos < 0)
      {
      if ( data.value == 0. )
      {
         shift += 1;
         exponent = 0;
      }
      else
      {
         shift += 3;
         exponent -= 3;
      }

      }

   memmove(&buffer[shift+1],&buffer[shift],strlen(&buffer[shift])+1);

   buffer[shift] = '.';

   endOfBuf = (data.sigDigits) ? (int)strlen(buffer) : shift + data.nDigits + 1;

   buffer[endOfBuf++] = 'e';

   buffer[endOfBuf++] = (exponent < 0) ? '-' : '+';

   if (_abs64(exponent) < 10)
      buffer[endOfBuf++] = '0';

   _i64toa_s(_abs64(exponent),&buffer[endOfBuf],50-endOfBuf,10);

   if (negative)
      buffer--;

   USES_CONVERSION;
   dynamic_cast<std::_tostream&>(os) << A2T(buffer);
}

eng_notation_manip eng_notation(Float64 value,int nDigits,int sigDigits)
{
   sysEngNotationData data;
   data.value = value;
   data.nDigits = nDigits;
   data.sigDigits = sigDigits;
   return eng_notation_manip(StreamEngNotation,data);
}


