///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysNumericFormatTool
****************************************************************************/

#include <System\NumericFormatTool.h>
#include <System\EngNotation.h>
#include <System\SectionValue.h>
#include <sstream>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Helper function prototypes
Uint16 get_width_demand(Float64 value,Uint16 precision);
void apply_stream_manipulators( std::_tostream* pOS, sysNumericFormatTool::Format format,Uint16 width,Uint16 precision);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysNumericFormatTool::sysNumericFormatTool(Format format, Uint16 width, Uint16 precision) :
m_Format( format ),
m_Width( width ),
m_Precision( precision )
{
}

sysNumericFormatTool::sysNumericFormatTool(const sysNumericFormatTool& rOther)
{
   MakeCopy(rOther);
}

sysNumericFormatTool::~sysNumericFormatTool()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
std::_tstring sysNumericFormatTool::AsString(Float64 value) const
{
   std::_tostringstream os;

   if ( !IsZero(value) )
   {
      if ( IsEqual(fabs(value)/Float64_Max,1.0) )
      {
         if ( value > 0 )
         {
            return _T("INF");
         }
         else 
         {
            return _T("-INF");
         }
      }
   }

   //
   // Setup stream for floating point format, width, and precision
   //

   Format format = m_Format;
   
   // Check if the specified width is adequate
   // Only applies to Automatic and Fixed formatting
   if ( (m_Width > 0) &&
        (format == Automatic || format == Fixed ) &&
        (get_width_demand( value, m_Precision ) > m_Width) )
   {
      // The specified with is insufficient, use scientific notation
      //WARN( true, "Switching to scientific notation : " << value);
      format = Scientific;
   }

   apply_stream_manipulators( &os, format, m_Width, m_Precision );

   if ( format == Engineering )
   {
      os << eng_notation(value,m_Width,m_Precision);
   }
   else
   {
      os << value;
   }


   return os.str();
}

std::_tstring sysNumericFormatTool::AsString(const sysSectionValue& value) const
{
   std::_tostringstream os;
   
   Float64 left_value  = value.Left();
   Float64 right_value = value.Right();

   if ( IsEqual( left_value, right_value ) )
   {
      return AsString( left_value );
   }

   //
   // Setup stream for floating point format, width, and precision
   //

   Format format = m_Format;
   
   // Check if the specified with is adequate
   if ( (m_Width > 0) &&
        (format != Scientific || format != Engineering ) &&
        ( (get_width_demand( left_value, m_Precision ) > m_Width) || (get_width_demand(right_value, m_Precision) > m_Width) )
      )
   {
      // The specified with is insufficient, use scientific notation
      //WARN( true, "Switching to scientific notation : " << value);
      format = Scientific;
   }

   apply_stream_manipulators( &os, format, m_Width, m_Precision );

   if ( format == Engineering )
   {
      os << eng_notation(left_value,m_Width,m_Precision);
      if ( !IsEqual(left_value, right_value) )
      {
         os << "/" << eng_notation(right_value,m_Width,m_Precision);
      }
   }
   else
   {
      os << left_value;
      if ( !IsEqual(left_value, right_value) )
      {
         os << "/" << right_value;
      }
   }

   os << std::endl;

   return os.str();
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
sysNumericFormatTool& sysNumericFormatTool::operator= (const sysNumericFormatTool& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void sysNumericFormatTool::MakeCopy(const sysNumericFormatTool& rOther)
{
   m_Format = rOther.m_Format;
   m_Width = rOther.m_Width;
   m_Precision = rOther.m_Precision;
}

void sysNumericFormatTool::MakeAssignment(const sysNumericFormatTool& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Uint16 get_width_demand(Float64 value,Uint16 precision)
{
   Float64 dLeft = log(fabs(value))/log(10.);
   if ( dLeft > (Uint16_Max - 2 - precision))
   {
      return Uint16_Max;
   }

   Uint16 left = Uint16( dLeft ) + 1;

   // Need room for +/- sign and the decimal point
   Uint16 demand = 1 + left + 1 + precision;

   return demand;
}

void apply_stream_manipulators( std::_tostream* pOS, sysNumericFormatTool::Format format,Uint16 width,Uint16 precision)
{
   switch ( format )
   {
   case sysNumericFormatTool::Engineering:
      // Do nothing.
      // std::ios does not support scientific notation so we
      // will have to roll our own with a custom manipulator

      //**************************************
      //*** DROP THROUGH to Automatic
      //**************************************

   case sysNumericFormatTool::Automatic:
      pOS->setf( !std::ios::scientific, std::ios::floatfield );
      pOS->setf( !std::ios::fixed,      std::ios::floatfield );
      break;

   case sysNumericFormatTool::Fixed:
      pOS->setf( std::ios::fixed,      std::ios::floatfield );
      break;

   case sysNumericFormatTool::Scientific:
      {
      pOS->setf( std::ios::scientific, std::ios::floatfield );

      Int16 max_precision = width - 8;
      if ( pOS->precision() > max_precision )
      {
         //WARN( max_precision <= pOS->precision(), "Scientific precision set too high to fit in width, using maximum available precision");
         pOS->precision( max_precision );
      } // end if
      } // end case
      break;

   default:
        CHECK(false);
   }

   // Width
   pOS->width( width );

   // Precision
   pOS->precision( precision );
}
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


