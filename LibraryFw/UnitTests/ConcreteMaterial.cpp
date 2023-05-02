///////////////////////////////////////////////////////////////////////
// LibraryFW - Framework for implementing library features in programs
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <LibraryFw\LibraryFwLib.h>
#include "ConcreteMaterial.h"

#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>
#include <System\XStructuredLoad.h>


/****************************************************************************
CLASS
   libConcreteMaterial
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
libConcreteMaterial::libConcreteMaterial() :
libLibraryEntry(),
m_Fc(0),
m_Ec(0),
m_D(0),
m_AggSize(0)
{
}

libConcreteMaterial::libConcreteMaterial(const libConcreteMaterial& rOther) :
libLibraryEntry(rOther)
{
   MakeCopy(rOther);
}

libConcreteMaterial::~libConcreteMaterial()
{
}

//======================== OPERATORS  =======================================
libConcreteMaterial& libConcreteMaterial::operator= (const libConcreteMaterial& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bool libConcreteMaterial::SaveMe(WBFL::System::IStructuredSave* pSave)
{
   pSave->BeginUnit(_T("ConcreteMaterialEntry"), 1.0);

   pSave->Property(_T("Name"),this->GetName().c_str());
   pSave->Property(_T("Density"), m_D);
   pSave->Property(_T("Fc"), m_Fc);
   pSave->Property(_T("Ec"), m_Ec);
   pSave->Property(_T("AggregateSize"),m_AggSize);

   pSave->EndUnit();

   return false;
}

bool libConcreteMaterial::LoadMe(WBFL::System::IStructuredLoad* pLoad)
{
   if( pLoad->BeginUnit(_T("ConcreteMaterialEntry")) )
   {
      if (pLoad->GetVersion()!=1.0)
         THROW_LOAD(BadVersion,pLoad);

      std::_tstring name;
      if(pLoad->Property(_T("Name"),&name))
         this->SetName(name.c_str());
      else
         THROW_LOAD(InvalidFileFormat,pLoad);

      if(!pLoad->Property(_T("Density"), &m_D))
         THROW_LOAD(InvalidFileFormat,pLoad);

      if(!pLoad->Property(_T("Fc"), &m_Fc))
         THROW_LOAD(InvalidFileFormat,pLoad);

      if(!pLoad->Property(_T("Ec"), &m_Ec))
         THROW_LOAD(InvalidFileFormat,pLoad);

      if(!pLoad->Property(_T("AggregateSize"), &m_AggSize))
         THROW_LOAD(InvalidFileFormat,pLoad);

      if(!pLoad->EndUnit())
         THROW_LOAD(InvalidFileFormat,pLoad);
   }
   else
      return false; // not a concrete entry
   
   return true;
}




//======================== ACCESS     =======================================

void libConcreteMaterial::SetFc(Float64 fc)
{
   m_Fc=fc;
}

Float64 libConcreteMaterial::GetFc() const
{
   return m_Fc;
}

void libConcreteMaterial::SetEc(Float64 ec)
{
   m_Ec = ec;
}

Float64 libConcreteMaterial::GetEc() const
{
   return m_Ec;
}

void libConcreteMaterial::SetWeightDensity(Float64 d)
{
   m_D = d;
}

Float64 libConcreteMaterial::GetWeightDensity() const
{
   return m_D;
}

void libConcreteMaterial::SetAggregateSize(Float64 s)
{
   m_AggSize = s;
}

Float64 libConcreteMaterial::GetAggregateSize()const
{
   return m_AggSize;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void libConcreteMaterial::MakeCopy(const libConcreteMaterial& rOther)
{
   m_Fc      = rOther.m_Fc;
   m_Ec      = rOther.m_Ec;      
   m_D       = rOther.m_D;       
   m_AggSize = rOther.m_AggSize;
}

void libConcreteMaterial::MakeAssignment(const libConcreteMaterial& rOther)
{
   libLibraryEntry::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool libConcreteMaterial::AssertValid() const
{
   return libLibraryEntry::AssertValid();
}

void libConcreteMaterial::Dump(WBFL::Debug::LogContext& os) const
{
   libLibraryEntry::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool libConcreteMaterial::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("libConcreteMaterial");


   TESTME_EPILOG("ConcreteMaterial");
}
#endif // _UNITTEST
