///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <BridgeModeling\BridgeModelingLib.h>

#include <BridgeModeling\Girder.h>
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Pier.h>
#include <BridgeModeling\Connection.h>
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ROUND_OFF(x) ((Int32)(((x) * 1000.) + 0.5))/1000.


///////
bmfGirder::bmfGirder(bmfGirderTemplate* pTpl )
{
   m_pTemplate = pTpl;
   m_pGirderPath = 0;
   m_pSpan = 0;
}

bmfGirder::bmfGirder(const bmfGirder& rOther)
{
   MakeCopy( rOther );
}

bmfGirder::~bmfGirder()
{
}

bmfGirder& bmfGirder::operator = (const bmfGirder& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

void bmfGirder::PlanView(HDC hDC,const grlibPointMapper& mapper) const
{
   // Does nothing be default
}

Float64 bmfGirder::GetSpanLength() const
{
   // Girder Path length is the length between the points of bearing.
   // and this is my span length
   return ROUND_OFF( m_pGirderPath->Length() );
}

Float64 bmfGirder::GetLength() const
{
   return GetSpanLength() + GetLeftEndSize() + GetRightEndSize();
}

void bmfGirder::Associate( const bmfSpan* pSpan, const bmfGirderPath* pGirderPath )
{
   PRECONDITION( pSpan != 0 );
   PRECONDITION( pGirderPath != 0 );

   m_pSpan = pSpan;
   m_pGirderPath = pGirderPath;

   OnGirderPathChanged();
}

const bmfSpan* bmfGirder::GetSpan() const
{
   return m_pSpan;
}

const bmfGirderPath* bmfGirder::GetGirderPath() const
{
   return m_pGirderPath;
}

void bmfGirder::OnGirderPathChanged()
{
   // Does nothing by default.
}

const bmfGirderTemplate* bmfGirder::GetTemplate() const
{
   return m_pTemplate;
}

bmfGirderTemplate* bmfGirder::GetTemplate()
{
   return m_pTemplate;
}

void bmfGirder::MakeCopy(const bmfGirder& rOther)
{
   m_pTemplate   = rOther.m_pTemplate;
   m_pSpan       = rOther.m_pSpan;
   m_pGirderPath = rOther.m_pGirderPath;
}

void bmfGirder::MakeAssignment(const bmfGirder& rOther)
{
   MakeCopy( rOther );
}

Float64 bmfGirder::GetLeftEndSize() const
{
   CHECKX( m_pSpan != 0, "This call only valid after the girder has been inserted into a span" );

   const bmfConnection* pConnection = m_pSpan->GetStartPier()->GetConnection();
   Float64 end_size = pConnection->GetGirderEndSize();
   if ( pConnection->GetHowGirderEndSizeIsMeasured() == NormalToLine )
   {
      // correct for skew
      CComPtr<IAngle> angle;
      m_pSpan->GetStartPier()->GetSkewAngle(&angle);
      Float64 value;
      angle->get_Value(&value);
      end_size /=  cos ( fabs(value) );
   }

   // Round to 1 mm accuracy
   end_size = ROUND_OFF( end_size );
   return end_size;
}

Float64 bmfGirder::GetRightEndSize() const
{
   CHECKX( m_pSpan != 0, "This call only valid after the girder has been inserted into a span" );

   const bmfConnection* pConnection = m_pSpan->GetEndPier()->GetConnection();
   Float64 end_size = pConnection->GetGirderEndSize();
   if ( pConnection->GetHowGirderEndSizeIsMeasured() == NormalToLine )
   {
      // correct for skew
      CComPtr<IAngle> angle;
      m_pSpan->GetStartPier()->GetSkewAngle(&angle);
      Float64 value;
      angle->get_Value(&value);
      end_size /=  cos ( fabs(value) );
   }

   end_size = ROUND_OFF( end_size );
   return end_size;
}

Float64 bmfGirder::GetLeftBearingOffset() const
{
   CHECKX( m_pSpan != 0, "This call only valid after the girder has been inserted into a span" );

   const bmfConnection* pConnection = m_pSpan->GetStartPier()->GetConnection();
   Float64 offset = pConnection->GetBearingOffset();
   if ( pConnection->GetHowBearingOffSetIsMeasured() == NormalToLine )
   {
      // correct for skew
      CComPtr<IAngle> angle;
      m_pSpan->GetStartPier()->GetSkewAngle(&angle);
      Float64 value;
      angle->get_Value(&value);
      offset /=  cos ( fabs(value) );
   }

   // Round to 1 mm accuracy
   offset = ROUND_OFF( offset );
   return offset;
}

Float64 bmfGirder::GetRightBearingOffset() const
{
   CHECKX( m_pSpan != 0, "This call only valid after the girder has been inserted into a span" );

   const bmfConnection* pConnection = m_pSpan->GetEndPier()->GetConnection();
   Float64 offset = pConnection->GetBearingOffset();
   if ( pConnection->GetHowBearingOffSetIsMeasured() == NormalToLine )
   {
      // correct for skew
      CComPtr<IAngle> angle;
      m_pSpan->GetStartPier()->GetSkewAngle(&angle);
      Float64 value;
      angle->get_Value(&value);
      offset /=  cos ( fabs(value) );
   }

   offset = ROUND_OFF( offset );
   return offset;
}

#if defined _DEBUG
void bmfGirder::Dump(std::ostream& os)
{
   os << "Girder " << m_pTemplate->GetName() << std::endl;
}
#endif // _DEBUG
