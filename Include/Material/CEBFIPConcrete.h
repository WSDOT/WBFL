///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2018  Washington State Department of Transportation
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


struct MATCLASS matCEBFIPConcreteShrinkageDetails : public matConcreteBaseShrinkageDetails
{
   matCEBFIPConcreteShrinkageDetails() : matConcreteBaseShrinkageDetails(), 
      h(0),BetaSC(0),BetaSRH(0),BetaRH(0),BetaS(0), es(0), ecso(0) {}
   Float64 h;
   Float64 BetaSC;
   Float64 BetaSRH;
   Float64 BetaRH;
   Float64 BetaS;
   Float64 es;
   Float64 ecso;
};

struct MATCLASS matCEBFIPConcreteCreepDetails : public matConcreteBaseCreepDetails
{
   matCEBFIPConcreteCreepDetails() : matConcreteBaseCreepDetails(),
      Yo(0), Bc(0), Yrh(0), Bfc(0), Bt(0), Bh(0), h(0) {}
   Float64 Yo;
   Float64 Bc;
   Float64 Yrh;
   Float64 Bfc;
   Float64 Bt;
   Float64 Bh;
   Float64 h;
};

/*****************************************************************************
CLASS 
   matCEBFIPConcrete

   Time-dependent concrete model based on CEB-FIP Model Code 1990
*****************************************************************************/

class MATCLASS matCEBFIPConcrete : public matConcreteBase
{
public:
   typedef enum CementType 
   {
      RS, // rapid hardening, high strength
      N,  // normal hardining
      R,  // rapid hardening
      SL  // slow hardening
   } CementType;

   static LPCTSTR GetCementType(CementType type);
   static void GetModelParameters(CementType cement,Float64* pS,Float64* pBetaSC);

   // Computes what the 28 day strength needs to be for a concrete strength
   // fc occuring at concrete age for the specified cement type
   static Float64 ComputeFc28(Float64 fc,Float64 age,CementType type);
   static Float64 ComputeEc28(Float64 Ec,Float64 age,CementType type);

   matCEBFIPConcrete(LPCTSTR name = _T("Unknown"));

   // Set/Get the s parameter
   void SetS(Float64 s);
   Float64 GetS() const;

   // Set/Get the betaSc parameter
   void SetBetaSc(Float64 betaSc);
   Float64 GetBetaSc() const;

   // Set/Get the 28 day concrete strength
   void SetFc28(Float64 fc);
   Float64 GetFc28() const;

   // Sets the 28 day strength by computing what it needs to be
   // based on the current values of s for
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
   // based on the current values of s for the given
   // value of Ec and the time that that modulus occurs
   void SetEc28(Float64 Ec,Float64 t);

   // Computes what the 28 day strength needs to be for a concrete strength
   // fc occuring at concrete age with parameter s
   static Float64 ComputeFc28(Float64 fc,Float64 age,Float64 s);
   static Float64 ComputeEc28(Float64 ec,Float64 age,Float64 s);

   // Computes the value for S giving a concrete strength (fc1) at at age of t1,
   // and a later strength (fc2) at age t2. (fc1,fc2 are in system units, t1 and t2 are in days)
   static void ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pS);

   // Returns the compressive strength of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFc(Float64 t) const override;

   // Returns the secant modulus of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetEc(Float64 t) const override;

   // Returns the modulus of rupture for shear calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetShearFr(Float64 t) const override;

   // Returns the modulus of rupture for flexure calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFlexureFr(Float64 t) const override;

   // Returns the total free shrinkage that has occured from time at casting
   // to the time specified
   virtual Float64 GetFreeShrinkageStrain(Float64 t) const override;
   virtual std::shared_ptr<matConcreteBaseShrinkageDetails> GetFreeShrinkageStrainDetails(Float64 t) const override;

   // Returns the creep coefficient at time t for a loading applied at time tla
   virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const override;
   virtual std::shared_ptr<matConcreteBaseCreepDetails> GetCreepCoefficientDetails(Float64 t,Float64 tla) const override;

   Float64 GetH() const;

   // Shrinkage Parameters
   Float64 GetBetaSRH() const; // if return value is < 0, this parameter is not applicable to the computations
   Float64 GetBetaRH() const;
   Float64 GetEpsilonS() const;
   Float64 GetNotionalShrinkageCoefficient() const;

   // Creep Parameters
   Float64 GetPhiRH() const;
   Float64 GetBetaFcm() const;
   Float64 GetBetaH() const;

   // Creates a clone of this object
   virtual matConcreteBase* CreateClone() const override;

protected:
   // prevent copying and assignment (use CreateClone instead)
   matCEBFIPConcrete(const matCEBFIPConcrete& rOther);
   matCEBFIPConcrete& operator = (const matCEBFIPConcrete& rOther);

   virtual void OnChanged() override;

private:
   Float64 m_Fc28;
   Float64 m_Ec28;
   Float64 m_S;
   Float64 m_BetaSc;   // Beta-SC for use in CEB-FIP Eqn. 2.1-76
   bool m_bUserEc;

   mutable Float64 m_Ec; // this is the validated Ec28 (could be user input or could be computed)

   mutable bool m_bIsValid;
   void Validate() const;

   Float64 GetFr(Float64 t) const;
   Float64 ModE(Float64 fc,Float64 density) const;
};
