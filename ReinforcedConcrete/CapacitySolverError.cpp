///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\CapacitySolverError.h>
#include <strstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaXCapacitySolverError
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaXCapacitySolverError::rcaXCapacitySolverError(Reason reason, LPCTSTR file, Int16 line) :
sysXBase(file, line),
m_Reason(reason),
m_ReinterpertMsg( _T("None given") )
{
   Init();
}

rcaXCapacitySolverError::rcaXCapacitySolverError(const std::_tstring &reinterpMsg,Reason reason, LPCTSTR file, Int16 line) :
sysXBase(file,line),
m_Reason(reason),
m_ReinterpertMsg( reinterpMsg )
{
   Init();
}

rcaXCapacitySolverError::rcaXCapacitySolverError(const rcaXCapacitySolverError& rOther) :
sysXBase(rOther)
{
   Init();
   MakeCopy(rOther);
} 

rcaXCapacitySolverError::~rcaXCapacitySolverError()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaXCapacitySolverError& rcaXCapacitySolverError::operator= (const rcaXCapacitySolverError& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void rcaXCapacitySolverError::Throw() const 
{ 
   throw static_cast<rcaXCapacitySolverError>(*this); 
}

// rcaXCapacitySolverError::Reason
Int32 rcaXCapacitySolverError::GetReason() const
{
   return m_Reason;
}

rcaXCapacitySolverError::Reason rcaXCapacitySolverError::GetReasonCode() const
{
   return m_Reason;
}

void rcaXCapacitySolverError::GetErrorMessage(std::_tstring* pMsg,Int32 reserved) const
{
   if ( reserved == 0 )
   {
      switch (m_Reason)
      {
      case ProblemRepError:
         *pMsg = _T("There is an error with the analysis model");
         break;

      case NoTensileCapacity:
         *pMsg = _T("Analysis model has no tensile capacity");
         break;

      case NoCompressiveCapacity:
         *pMsg = _T("Analysis model has no compressive capacity");
         break;

      case TensileCapacityExceeded:
         *pMsg = _T("The applied axial load exceeds the tensile capacity of the model.");
         break;

      case CompressiveCapacityExceeded:
         *pMsg = _T("The applied axial load exceeds the compressive capacity of the model.");
         break;

      case MaxIterExceeded:
         *pMsg = _T("The maximum number of iterations have been exceeded.");
         break;

      case Unknown:
         *pMsg = _T("An unknown error has occured");
         break;

      default:
         CHECK(0);
         *pMsg = _T("Unknown Error Message - Bad Reason Type");
      }
   }
   else
   {
      *pMsg = m_ReinterpertMsg;
   }
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaXCapacitySolverError::AssertValid() const
{
   return true;
}

void rcaXCapacitySolverError::Dump(dbgDumpContext& os) const
{
   os<<"Dump for rcaXCapacitySolverError"<<endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaXCapacitySolverError::MakeCopy(const rcaXCapacitySolverError& rOther)
{
   m_Reason = rOther.m_Reason;
   m_ReinterpertMsg = rOther.m_ReinterpertMsg;
}

void rcaXCapacitySolverError::MakeAssignment(const rcaXCapacitySolverError& rOther)
{
   Clean();
   Init();

   sysXBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaXCapacitySolverError::Init()
{
   // Add initialization code here...
}

void rcaXCapacitySolverError::Clean()
{
   // Add cleanup code here...
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
