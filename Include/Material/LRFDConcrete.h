///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#pragma once

#include <Material\MaterialExp.h>
#include <Material\ConcreteBase.h>
#include <Material\ConcreteEx.h>


/*****************************************************************************
CLASS 
   matLRFDConcrete

   Pseudo Time-dependent concrete model based on AASHTO LRFD. This is a
   step function that uses f'ci and Eci until a specified time and then
   f'c and Ec. This class is an adaptor for matConcreteEx
*****************************************************************************/

class MATCLASS matLRFDConcrete : public matConcreteBase
{
public:
   matLRFDConcrete(LPCTSTR name = _T("Unknown"));
   virtual ~matLRFDConcrete();

   void SetConcreteModels(const matConcreteEx& initial,const matConcreteEx& final);
   const matConcreteEx& GetInitialConcreteModel() const;
   const matConcreteEx& GetFinalConcreteModel() const;

   void SetStepTime(Float64 t);
   Float64 GetStepTime() const;

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
   matLRFDConcrete(const matLRFDConcrete& rOther);
   matLRFDConcrete& operator = (const matLRFDConcrete& rOther);

private:
   matConcreteEx m_InitialConcrete, m_FinalConcrete;
   Float64 m_StepTime;
};
