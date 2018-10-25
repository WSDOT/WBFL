///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Material\ConcreteBase.h>
#include <Material\ConcreteEx.h>


/*****************************************************************************
CLASS 
   lrfdLRFDConcrete

   Pseudo Time-dependent concrete model based on AASHTO LRFD. This is a
   step function that uses f'ci and Eci until a specified time and then
   f'c and Ec. This class is an adaptor for matConcreteEx
*****************************************************************************/

class LRFDCLASS lrfdLRFDConcrete : public matConcreteBase
{
public:
   lrfdLRFDConcrete(LPCTSTR name = _T("Unknown"));
   virtual ~lrfdLRFDConcrete();

   void SetConcreteModels(const matConcreteEx& initial,const matConcreteEx& final);
   const matConcreteEx& GetInitialConcreteModel() const;
   const matConcreteEx& GetFinalConcreteModel() const;

   void SetStartTime(Float64 t);
   Float64 GetStartTime() const;

   void SetStepTime(Float64 t);
   Float64 GetStepTime() const;

   // aggregate correction and bounding factors.
   // see NCHRP Report 496
   void SetEcCorrectionFactors(Float64 K1,Float64 K2);
   void GetEcCorrectionFactors(Float64* pK1,Float64* pK2) const;
   void SetCreepCorrectionFactors(Float64 K1,Float64 K2);
   void GetCreepCorrectionFactors(Float64* pK1,Float64* pK2) const;
   void SetShrinkageCorrectionFactors(Float64 K1,Float64 K2);
   void GetShrinkageCorrectionFactors(Float64* pK1,Float64* pK2) const;


   // Returns the compressive strength of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFc(Float64 t) const;

   // Returns the secant modulus of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetEc(Float64 t) const;

   // Returns the modulus of rupture for shear calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetShearFr(Float64 t) const;

   // Returns the modulus of rupture for flexure calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFlexureFr(Float64 t) const;

   virtual Float64 GetFreeShrinkageStrain(Float64 t) const;
   virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const;

   // Creates a clone of this object
   virtual matConcreteBase* CreateClone() const;

protected:
   // prevent copying and assignment (use CreateClone instead)
   lrfdLRFDConcrete(const lrfdLRFDConcrete& rOther);
   lrfdLRFDConcrete& operator = (const lrfdLRFDConcrete& rOther);

   Float64 GetFreeShrinkageStrainBefore2005(Float64 t) const;
   Float64 GetFreeShrinkageStrain2005(Float64 t) const;
   Float64 GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const;
   Float64 GetCreepCoefficient2005(Float64 t,Float64 tla) const;

private:
   matConcreteEx m_InitialConcrete, m_FinalConcrete;
   Float64 m_StartTime;
   Float64 m_StepTime;
   Float64 m_EcK1;
   Float64 m_EcK2;
   Float64 m_CreepK1;
   Float64 m_CreepK2;
   Float64 m_ShrinkageK1;
   Float64 m_ShrinkageK2;
};
