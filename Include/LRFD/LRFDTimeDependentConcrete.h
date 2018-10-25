///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2014  Washington State Department of Transportation
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

/*****************************************************************************
CLASS 
   lrfdLRFDTimeDependentConcrete

   Time-dependent concrete model based on the LRFD specifications. Since
   the LRFD specifications don't have a time-dependent model for f'c and Ec
   we will use the ACI 209 model
*****************************************************************************/

class LRFDCLASS lrfdLRFDTimeDependentConcrete : public matConcreteBase
{
public:
   enum CementType { TypeI, TypeII };
   static void GetModelParameters(CureMethod cure,CementType cement,Float64* pA,Float64* pBeta);

   lrfdLRFDTimeDependentConcrete(LPCTSTR name = _T("Unknown"));

   // Set/Get the a parameter (days)
   void SetA(Float64 a);
   Float64 GetA() const;

   // Set/Get the beta parameter
   void SetBeta(Float64 b);
   Float64 GetBeta() const;

   // Set/Get the 28 day concrete strength
   void SetFc28(Float64 fc);
   Float64 GetFc28() const;

   // Sets the 28 day strength by computing what it needs to be
   // based on the current values of alpha and beta for
   // a given concrete strength and the time that strength occurs
   void SetFc28(Float64 fc,Float64 t);

   // Indiciates if a user value for Ec is used. If not, it is comptued
   // from Fc28
   void UserEc28(bool bUserEc);
   bool UserEc28() const;

   // Set/Get the 28 day secant modulus
   void SetEc28(Float64 Ec);
   Float64 GetEc28() const;

   // Sets the 28 day scent modulus by compute what it need to be
   // based on the current values of alpha and beta for the given
   // value of Ec and the time that that modulus occurs
   void SetEc28(Float64 Ec,Float64 t);

   // Computes what the 28 day strength needs to be for a concrete strength
   // fc occuring at concrete age with parameters a (alpha, days) and b (beta)
   static Float64 ComputeFc28(Float64 fc,Float64 age,Float64 a,Float64 b);
   static Float64 ComputeEc28(Float64 ec,Float64 age,Float64 a,Float64 b);

   // Computes the values for Alpha and Beta giving a concrete strength (fc1) at at age of t1,
   // and a later strength (fc2) at age t2. (fc1,fc2 are in system units, t1 and t2 are in days,
   // Alpha is in system units, Beta is unitless
   static void ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pA,Float64* pB);

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

   // Returns the total free shrinkage that has occured from time at casting
   // to the time specified
   virtual Float64 GetFreeShrinkageStrain(Float64 t) const;

   // Returns the creep coefficient at time t for a loading applied at time tla
   virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const;

   // Creates a clone of this object
   virtual matConcreteBase* CreateClone() const;

   // Set/Get ultimate shrinkage strain
   void SetUltimateShrinkageStrain(Float64 eu);
   Float64 GetUltimateShrinkageStrain() const;

   // Set/Get ultimate creep coefficient
   void SetUltimateCreepCoefficient(Float64 cu);
   Float64 GetUltimateCreepCoefficient() const;

   // Set/Get modulus of rupture coefficient for shear (k*sqrt(f'c))
   void SetShearModulusOfRuptureCoefficient(Float64 k);
   Float64 GetShearModulusOfRuptureCoefficient() const;

   // Set/Get modulus of rupture coefficient for flexure (k*sqrt(f'c))
   void SetFlexureModulusOfRuptureCoefficient(Float64 k);
   Float64 GetFlexureModulusOfRuptureCoefficient() const;

   Float64 GetRelativeHumidityFactorCreep() const;
   Float64 GetRelativeHumidityFactorShrinkage() const;
   Float64 GetSizeFactorCreep(Float64 t,Float64 tla) const;
   Float64 GetSizeFactorShrinkage(Float64 t) const;
   Float64 GetConcreteStrengthFactor() const;


protected:
   // prevent copying and assignment (use CreateClone instead)
   lrfdLRFDTimeDependentConcrete(const lrfdLRFDTimeDependentConcrete& rOther);
   lrfdLRFDTimeDependentConcrete& operator = (const lrfdLRFDTimeDependentConcrete& rOther);

private:
   Float64 m_Eshu; // ultimate shrinkage strain
   Float64 m_Cu;   // ultimate creep coefficient
   Float64 m_Fc28;
   Float64 m_Ec28;
   Float64 m_A; // in system units
   mutable Float64 m_Alpha; // convert to days
   Float64 m_Beta; // unitless
   bool m_bUserEc;

   Float64 m_ShearFrCoefficient;
   Float64 m_FlexureFrCoefficient;

   Float64 m_EcK1;
   Float64 m_EcK2;
   Float64 m_CreepK1;
   Float64 m_CreepK2;
   Float64 m_ShrinkageK1;
   Float64 m_ShrinkageK2;

   mutable Float64 m_Ec; // this is the validated Ec28 (could be user input or could be computed)

   mutable Float64 m_khs; // relative humidity factor for shrinkage
   mutable Float64 m_khc; // relative humidity factor for creep
   mutable Float64 m_kf;  // concrete strength factor

   mutable bool m_bIsValid;
   void Validate() const;

   Float64 ModE(Float64 fc,Float64 density) const;

   Float64 GetFreeShrinkageStrainBefore2005(Float64 t) const;
   Float64 GetFreeShrinkageStrain2005(Float64 t) const;
   Float64 GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const;
   Float64 GetCreepCoefficient2005(Float64 t,Float64 tla) const;
};
