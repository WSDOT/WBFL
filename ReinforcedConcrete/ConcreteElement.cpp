///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <ReinforcedConcrete\ConcreteElement.h>

#include <ReinforcedConcrete\CapacityProblem.h>
#include <GeomModel\Properties.h>
#include <Material\Concrete.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rcaConcreteElement
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rcaConcreteElement::rcaConcreteElement(const gmIShape& rShape, CollectionIndexType concreteKey, 
                                       Float64 nFactor,
                                       const rcaCapacityProblem& rProblem):
m_pShape(rShape.CreateClone()),
m_ConcreteKey(concreteKey),
m_N(nFactor),
m_IsNSpecified(true),
m_pProblem(&rProblem)
{
   PRECONDITION(nFactor>0);
}

rcaConcreteElement::rcaConcreteElement(const gmIShape& rShape, CollectionIndexType concreteKey, 
                                       const rcaCapacityProblem& rProblem):
m_pShape(rShape.CreateClone()),
m_ConcreteKey(concreteKey),
m_N(0.0),
m_IsNSpecified(false),
m_pProblem(&rProblem)
{
}

rcaConcreteElement::rcaConcreteElement(const rcaConcreteElement& rOther)
{
   MakeCopy(rOther);
}

rcaConcreteElement::~rcaConcreteElement()
{
}

//======================== OPERATORS  =======================================
rcaConcreteElement& rcaConcreteElement::operator= (const rcaConcreteElement& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

const rcaCapacityProblem& rcaConcreteElement::GetProblem() const
{
   ASSERTVALID;
   return *m_pProblem;
}

void rcaConcreteElement::GetForces(Float64* pFz,
                       Float64* pMx,
                       Float64* pMy,
                       gpPoint2d* cg) const
{
   ASSERTVALID;
   // get compression block boundary and clip shape to bound
   gpLine2d comp_bound;
   m_pProblem->GetCompressionBlockBoundary(&comp_bound);

   // see if we support the IShapeEx interface
   Float64 area=0.0;
   gmIShapeEx* pex;
   pex = dynamic_cast<gmIShapeEx*>(m_pShape.get());
   if (pex!=0)
   {
      pex->ComputeClippedArea(comp_bound,gpLine2d::Right,&area,cg);
   }
   else
   {
   std::auto_ptr<gmIShape> clip(m_pShape->CreateClippedShape(comp_bound,gpLine2d::Right));
   if (clip.get()!=0)
   {
      gmProperties prop;
      clip->GetProperties(&prop);
         area = prop.Area();
         *cg  = prop.Centroid();
      }
   }

   if (area!=0.0)
   {
      *pFz = -area * m_N * 0.85 * GetFc();
      *pMx = 0;
      *pMy = 0;
   }
   else
   {
      *pFz = 0;
      *pMx = 0;
      *pMy = 0;
   }
}

Float64 rcaConcreteElement::GetClippedArea(const gpLine2d& clipLine, gpLine2d::Side side) const
{
//   std::auto_ptr<gmIShape> clip(m_pShape->CreateClippedShape(clipLine, gpLine2d::Right));
   std::auto_ptr<gmIShape> clip(m_pShape->CreateClippedShape(clipLine, side));
   if (clip.get() != 0)
   {
      gmProperties prop;
      clip->GetProperties(&prop);
      return prop.Area()* m_N;
   }

   return 0;
}

Float64 rcaConcreteElement::GetArea() const
{
   gmProperties prop;
   m_pShape->GetProperties( &prop );
   return prop.Area() * m_N;
}

const gmIShape& rcaConcreteElement::GetShape() const
{
   ASSERTVALID;
   return *m_pShape;
}

Float64 rcaConcreteElement::GetFc() const
{
   ASSERTVALID;
   return m_pProblem->GetConcrete(m_ConcreteKey).GetFc();
}

CollectionIndexType rcaConcreteElement::GetConcreteIdx() const
{
   ASSERTVALID;
   return m_ConcreteKey;
}

Float64 rcaConcreteElement::GetN() const
{
   ASSERTVALID;
   if (!m_IsNSpecified)
   {
      // n not specified - must get it from capacity problem's materials
      CollectionIndexType base_mat = m_pProblem->GetBaseConcreteMaterial();
      if (base_mat!=m_ConcreteKey)
      {
         Float64 Eme = m_pProblem->GetConcrete(m_ConcreteKey).GetE();
         Float64 Ebs = m_pProblem->GetConcrete(base_mat).GetE();
         PRECONDITION(Ebs>0.0);
         m_N = Eme/Ebs;
      }
      else
      {
         m_N = 1.0;
      }

      m_IsNSpecified = true;
   }

   return m_N;
}

gpRect2d rcaConcreteElement::GetBoundingBox() const
{
   ASSERTVALID;
   return m_pShape->GetBoundingBox();
}

void rcaConcreteElement::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   ASSERTVALID;
   m_pShape->Draw(hDC, mapper);
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rcaConcreteElement::AssertValid() const
{
   if (m_pShape.get()==0) return false;
   if (m_pProblem==0) return false;
   return true;
}

void rcaConcreteElement::Dump(dbgDumpContext& os) const
{
   os << "Dump for rcaConcreteElement" << endl;
   os << "   m_ConcreteKey = " << m_ConcreteKey << endl;
   os << "   m_N = " <<  m_N << endl;
   os << "   m_pShape:" << endl;
   m_pShape->Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool rcaConcreteElement::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rcaConcreteElement");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rcaConcreteElement");
   TESTME_EPILOG("rcaConcreteElement");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rcaConcreteElement::MakeCopy(const rcaConcreteElement& rOther)
{
   m_ConcreteKey  = rOther.m_ConcreteKey;
   m_IsNSpecified = rOther.m_IsNSpecified;
   m_N            = rOther.m_N;
   m_pShape       = std::auto_ptr<gmIShape>(rOther.m_pShape->CreateClone());
   m_pProblem     = rOther.m_pProblem;

   ASSERTVALID;
}

void rcaConcreteElement::MakeAssignment(const rcaConcreteElement& rOther)
{
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


