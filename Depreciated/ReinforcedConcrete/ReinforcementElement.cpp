///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#include <ReinforcedConcrete\ReinfConcLib.h>
#include <ReinforcedConcrete\ReinforcementElement.h>

#include <ReinforcedConcrete\CapacityProblem.h>
#include <GeomModel/ShapeProperties.h>
#include <Material\YieldStressStrainCurve.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaReinforcementElement
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaReinforcementElement::rcaReinforcementElement(const WBFL::Geometry::Shape& rShape,
                           const matYieldStressStrainCurve& rMaterialModel, 
                           const rcaCapacityProblem& rProblem, 
                           Float64 initStrain):
m_pProblem(&rProblem),
m_pCurve(&rMaterialModel),
m_InitialStrain(initStrain)
{
   m_pShape = rShape.CreateClone();
}

rcaReinforcementElement::rcaReinforcementElement(const rcaReinforcementElement& rOther)
{
   Init();
   MakeCopy(rOther);
}

rcaReinforcementElement::~rcaReinforcementElement()
{
   Clean();
}

//======================== OPERATORS  =======================================
rcaReinforcementElement& rcaReinforcementElement::operator= (const rcaReinforcementElement& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void rcaReinforcementElement::SetProblem(const rcaCapacityProblem& rProblem)
{
   ASSERTVALID;
   m_pProblem = &rProblem;
}

const rcaCapacityProblem& rcaReinforcementElement::GetProblem() const
{
   ASSERTVALID;
   return *m_pProblem;
}


void rcaReinforcementElement::GetForces(Float64* pFz,
                                        Float64* pMx,
                                        Float64* pMy,
                                        WBFL::Geometry::Point2d* pCg) const
{
   // first need area and cg of rebar shape
   Float64 area=0.0;
   
   WBFL::Geometry::ShapeProperties prop = m_pShape->GetProperties();
   area = prop.GetArea();
   *pCg  = prop.GetCentroid();

   // need to determine the strain at the c.g.
   Float64 strain = m_pProblem->GetStrain(*pCg);
   Float64 stress;
   matStressStrainCurve::StrainState ss = m_pCurve->GetStress(strain+m_InitialStrain, &stress);

   // emulate perfectly plastic behavior
   if (ss == matStressStrainCurve::Crushed )
      stress = m_pCurve->GetCompUltStress();
   else if (ss == matStressStrainCurve::Fractured )
      stress = m_pCurve->GetTensUltStress();

   *pFz = area * stress;
   *pMx = 0;
   *pMy = 0;
}

const WBFL::Geometry::Shape& rcaReinforcementElement::GetShape() const
{
   ASSERTVALID;
   return *m_pShape;
}

Float64 rcaReinforcementElement::GetInitialStrain() const
{
   ASSERTVALID;
   return m_InitialStrain;
}

const matYieldStressStrainCurve& rcaReinforcementElement::GetStressStrainCurve() const
{
   ASSERTVALID;
   return *m_pCurve;
}

WBFL::Geometry::Rect2d rcaReinforcementElement::GetBoundingBox() const
{
   ASSERTVALID;
   return m_pShape->GetBoundingBox();
}

void rcaReinforcementElement::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   ASSERTVALID;
   //m_pShape->Draw(hDC, mapper);
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaReinforcementElement::AssertValid() const
{
   if ( m_pShape   == 0 ) return false;
   if ( m_pProblem == 0 ) return false;
   if ( m_pCurve   == 0 ) return false;
   return true;
}

void rcaReinforcementElement::Dump(dbgDumpContext& os) const
{
   os << "Dump for rcaReinforcementElement" << endl;
   os << "================================" << endl;
   os << "Initial strain = " << m_InitialStrain << endl;
   os << "Stress-Strain Curve = " << m_pCurve->GetName() << endl;
   os << "Dumping reinforcement element shape" << endl;
   m_pShape->Dump(os);
   os << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool rcaReinforcementElement::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaReinforcementElement");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaReinforcementElement");
   TESTME_EPILOG("rcaReinforcementElement");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaReinforcementElement::MakeCopy(const rcaReinforcementElement& rOther)
{
   m_InitialStrain = rOther.m_InitialStrain;
   m_pShape = rOther.m_pShape->CreateClone();
   m_pProblem = rOther.m_pProblem;
   m_pCurve   = rOther.m_pCurve;
}

void rcaReinforcementElement::MakeAssignment(const rcaReinforcementElement& rOther)
{
   Clean();
   Init();

   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaReinforcementElement::Init()
{
   m_pShape = 0;
   m_InitialStrain = 0;
}

void rcaReinforcementElement::Clean()
{
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


