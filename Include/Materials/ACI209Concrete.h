///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Materials/MaterialsExp.h>
#include <Materials/ConcreteBase.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteShrinkageTemplateModel.h>

namespace WBFL
{
   namespace Materials
   {
      /// Shrinkage strain details for the ACI 209 model
      struct MATCLASS ACI209ConcreteShrinkageDetails : public ConcreteBaseShrinkageDetails
      {
         ACI209ConcreteShrinkageDetails() = default;
         Float64 f{ 0 };
         Float64 time_factor{ 0 };
         Float64 curing_factor{ 0 };
         Float64 humidity_factor{ 0 };
         Float64 vs_factor{ 0 };
      };

      /// Creep coefficient details for the ACI 209 model
      struct MATCLASS ACI209ConcreteCreepDetails : public ConcreteBaseCreepDetails
      {
         ACI209ConcreteCreepDetails() = default;
         Float64 time_factor{ 0 };
         Float64 loading_age_factor{ 0 };
         Float64 humidity_factor{ 0 };
         Float64 vs_factor{ 0 };
      };

      /// Time-dependent concrete model based on ACI 209R-92
      class MATCLASS ACI209Concrete : public ConcreteBase
      {
      public:
         static void GetModelParameters(CuringType cure,CementType cement,Float64* pA,Float64* pBeta);

         ACI209Concrete(LPCTSTR name = _T("Unknown"));
         ACI209Concrete(const ACI209Concrete&) = default;
         ACI209Concrete& operator=(const ACI209Concrete&) = default;

         /// Set/Get the a parameter (days)
         void SetA(Float64 a);
         Float64 GetA() const;

         /// Set/Get the beta parameter
         void SetBeta(Float64 b);
         Float64 GetBeta() const;

         /// Set/Get the 28 day concrete strength
         void SetFc28(Float64 fc);
         Float64 GetFc28() const;

         /// Sets the 28 day strength by computing what it needs to be
         /// based on the current values of alpha and beta for
         /// a given concrete strength and the time that strength occurs
         void SetFc28(Float64 fc,Float64 t);

         /// Indiciates if a user value for Ec is used. If not, it is comptued
         /// from Fc28
         void UserEc28(bool bUserEc);
         bool UserEc28() const;

         /// Set/Get the 28 day secant modulus
         void SetEc28(Float64 Ec);
         Float64 GetEc28() const;

         /// Sets the 28 day scent modulus by compute what it need to be
         /// based on the current values of alpha and beta for the given
         /// value of Ec and the time that that modulus occurs
         void SetEc28(Float64 Ec,Float64 t);

         /// Computes what the 28 day strength needs to be for a concrete strength
         /// fc occuring at concrete age with parameters a (alpha, days) and b (beta)
         static Float64 ComputeFc28(Float64 fc,Float64 age,Float64 a,Float64 b);
         static Float64 ComputeEc28(Float64 ec,Float64 age,Float64 a,Float64 b);

         /// Computes the values for Alpha and Beta giving a concrete strength (fc1) at at age of t1,
         /// and a later strength (fc2) at age t2. (fc1,fc2 are in system units, t1 and t2 are in days,
         /// Alpha is in system units, Beta is unitless
         static void ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pA,Float64* pB);

         /// Returns the compressive strength of the concrete at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetFc(Float64 t) const override;

         /// Returns the secant modulus of the concrete at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetEc(Float64 t) const override;

         /// Returns the modulus of rupture for shear calculations at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetShearFr(Float64 t) const override;

         /// Returns the modulus of rupture for flexure calculations at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetFlexureFr(Float64 t) const override;

         /// Returns the total free shrinkage that has occured from time at casting
         /// to the time specified
         virtual Float64 GetFreeShrinkageStrain(Float64 t) const override;
         virtual std::unique_ptr<ConcreteBaseShrinkageDetails> GetFreeShrinkageStrainDetails(Float64 t) const override;

         /// Returns the creep coefficient at time t for a loading applied at time tla
         virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const override;
         virtual std::unique_ptr<ConcreteBaseCreepDetails> GetCreepCoefficientDetails(Float64 t,Float64 tla) const override;

         /// Creates a clone of this object
         virtual std::unique_ptr<ConcreteBase> CreateClone() const override;

         /// Set/Get ultimate shrinkage strain
         void SetUltimateShrinkageStrain(Float64 eu);
         Float64 GetUltimateShrinkageStrain() const;

         /// Set/Get ultimate creep coefficient
         void SetUltimateCreepCoefficient(Float64 cu);
         Float64 GetUltimateCreepCoefficient() const;

         Float64 GetInitialMoistCureFactor() const;
         Float64 GetRelativeHumidityFactorCreep() const;
         Float64 GetRelativeHumidityFactorShrinkage() const;
         Float64 GetSizeFactorCreep() const;
         Float64 GetSizeFactorShrinkage() const;


      protected:
         virtual void OnChanged() override;

      private:
         Float64 m_Eshu; // ultimate shrinkage strain
         Float64 m_Cu;   // ultimate creep coefficient
         Float64 m_Fc28;
         Float64 m_Ec28;
         Float64 m_A; // in system units
         mutable Float64 m_Alpha; // converted to days
         Float64 m_Beta; // unitless
         bool m_bUserEc;

         mutable Float64 m_Ec; // this is the validated Ec28 (could be user input or could be computed)

         mutable Float64 m_CP;  // initial moist cure factor
         mutable Float64 m_RHS; // relative humidity factor for shrinkage
         mutable Float64 m_RHC; // relative humidity factor for creep

         mutable Float64 m_VSC; // size correction factor (V/S method) creep
         mutable Float64 m_VSS; // size correction factor (V/S method) shrinkage

         mutable bool m_bIsValid;
         void Validate() const;

         mutable bool m_bCorrectionFactorsValidated;
         void ValidateCorrectionFactors() const;

         Float64 GetFr(Float64 t) const;
         Float64 ModE(Float64 fc,Float64 density) const;
      };

      /// Models concrete strength based on ACI209
      class MATCLASS ACI209ConcreteStrengthModel : public ConcreteStrengthModel
      {
      public:
         ACI209ConcreteStrengthModel() = default;
         ACI209ConcreteStrengthModel(const ACI209ConcreteStrengthModel&) = default;
         ACI209ConcreteStrengthModel& operator=(const ACI209ConcreteStrengthModel&) = default;

         // Gets the parameters of the concrete strength mode, a and beta
         static void GetModelParameters(CuringType cure, CementType cement, Float64* pA, Float64* pBeta);
         
         /// Computes what the 28 day strength needs to be for a concrete strength
         /// fc occuring at age with parameters a (alpha, days) and b (beta).
         /// Solves Equation 2-1 for (f'c)28
         static Float64 ComputeFc28(Float64 fc, Float64 age, Float64 a, Float64 b);

         /// Computes the values for Alpha and Beta giving a concrete strength (fc1) at at age of t1,
         /// and a later strength (fc2) at age t2. (fc1,fc2 are in system units, t1 and t2 are in days,
         /// Alpha is in system units, Beta is unitless. Solves Eqn 2-1 for Alpha and Beta.
         static void ComputeParameters(Float64 fc1, Float64 t1, Float64 fc2, Float64 t2, Float64* pA, Float64* pB);

         /// Set/Get the a parameter (days)
         void SetA(Float64 a);
         Float64 GetA() const;

         /// Set/Get the beta parameter
         void SetBeta(Float64 b);
         Float64 GetBeta() const;

         /// Set/Get the 28 day concrete strength
         void SetFc28(Float64 fc);
         Float64 GetFc28() const;

         /// Sets the 28 day strength by computing what it needs to be
         /// based on the current values of alpha and beta for
         /// a given concrete strength and the time that strength occurs
         void SetFc28(Float64 fc, Float64 age);

         virtual Float64 GetFc(Float64 age) const override;

      private:
         Float64 m_Fc28{ 0.0 };
         Float64 m_A{ 0.0 }; // in system units
         mutable Float64 m_Alpha{ 0.0 }; // converted to days
         Float64 m_Beta{ 0.0 }; // unitless
      
         mutable bool m_bIsValid{ false };
         void Validate() const;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS ACI209ConcreteSecantModulusModel : public ConcreteSecantModulusModel
      {
      public:
         ACI209ConcreteSecantModulusModel() = default;
         ACI209ConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel, Float64 density);
         ACI209ConcreteSecantModulusModel(const ACI209ConcreteSecantModulusModel&) = default;
         ~ACI209ConcreteSecantModulusModel() = default;
         ACI209ConcreteSecantModulusModel& operator=(const ACI209ConcreteSecantModulusModel&) = default;

         /// Computes what the 28 day secant modulus needs to be for a secant modulus
         /// Ec occuring at age with parameters a (alpha, days) and b (beta).
         /// Solves Equation 2-2 for (f'c)28
         static Float64 ComputeEc28(Float64 Ec, Float64 age, Float64 a, Float64 b);

         void SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel);
         const std::shared_ptr<ConcreteStrengthModel>& GetConcreteStrengthModel() const;

         void SetDensity(Float64 density);
         Float64 GetDensity() const;

         virtual Float64 GetEc(Float64 age) const override;

      private:
         std::shared_ptr<ConcreteStrengthModel> m_FcModel;
         Float64 m_Density{ 0.0 };

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };


      class MATCLASS ACI209CreepVSRatioCorrectionFactorModel : public VSRatioCorrectionFactorModel
      {
      public:
         ACI209CreepVSRatioCorrectionFactorModel() = default;
         ACI209CreepVSRatioCorrectionFactorModel(Float64 vsRatio);
         ACI209CreepVSRatioCorrectionFactorModel(const ACI209CreepVSRatioCorrectionFactorModel& rOther) = default;

         virtual ~ACI209CreepVSRatioCorrectionFactorModel() = default;

         ACI209CreepVSRatioCorrectionFactorModel& operator=(const ACI209CreepVSRatioCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 t) const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS ACI209ShrinkageVSRatioCorrectionFactorModel : public VSRatioCorrectionFactorModel
      {
      public:
         ACI209ShrinkageVSRatioCorrectionFactorModel() = default;
         ACI209ShrinkageVSRatioCorrectionFactorModel(Float64 vsRatio);
         ACI209ShrinkageVSRatioCorrectionFactorModel(const ACI209ShrinkageVSRatioCorrectionFactorModel& rOther) = default;

         virtual ~ACI209ShrinkageVSRatioCorrectionFactorModel() = default;

         ACI209ShrinkageVSRatioCorrectionFactorModel& operator=(const ACI209ShrinkageVSRatioCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 t) const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS ACI209ShrinkageHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         ACI209ShrinkageHumidityCorrectionFactorModel() = default;
         ACI209ShrinkageHumidityCorrectionFactorModel(Float64 h);
         ACI209ShrinkageHumidityCorrectionFactorModel(const ACI209ShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual ~ACI209ShrinkageHumidityCorrectionFactorModel() = default;

         ACI209ShrinkageHumidityCorrectionFactorModel& operator=(const ACI209ShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor() const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS ACI209CreepHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         ACI209CreepHumidityCorrectionFactorModel() = default;
         ACI209CreepHumidityCorrectionFactorModel(Float64 h);
         ACI209CreepHumidityCorrectionFactorModel(const ACI209CreepHumidityCorrectionFactorModel& rOther) = default;

         virtual ~ACI209CreepHumidityCorrectionFactorModel() = default;

         ACI209CreepHumidityCorrectionFactorModel& operator=(const ACI209CreepHumidityCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor() const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      /// Time development correction factor for shrinkage for ACI209. 
      /// 
      /// This class inherits concrete strength at time of loading from the base-class. However that parameters is not used by the ACI209 model.
      /// See Eqns 2-1, 2-9, and 2-10
      class MATCLASS ACI209ShrinkageTimeDevelopmentCorrectionFactorModel : public ConcreteTimeDevelopmentCorrectionFactorModel
      {
      public:
         ACI209ShrinkageTimeDevelopmentCorrectionFactorModel() = default;
         ACI209ShrinkageTimeDevelopmentCorrectionFactorModel(CuringType curingType);
         ACI209ShrinkageTimeDevelopmentCorrectionFactorModel(const ACI209ShrinkageTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual ~ACI209ShrinkageTimeDevelopmentCorrectionFactorModel() = default;

         ACI209ShrinkageTimeDevelopmentCorrectionFactorModel& operator=(const ACI209ShrinkageTimeDevelopmentCorrectionFactorModel& rOther) = default;

         void SetCuringType(CuringType curingType);
         CuringType GetCuringType() const;

         /// \param t concrete maturity in days
         virtual Float64 GetCorrectionFactor(Float64 t) const override;

      private:
         CuringType m_CuringType{ CuringType::Moist };

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      /// Concrete curing correction factor for ACI209 shrinkage strain calculations.
      /// See ACI209 Article 2.5.3
      class MATCLASS ACI209CuringCorrectionFactorModel
      {
      public:
         ACI209CuringCorrectionFactorModel() = default;
         /// \param curingType curing type
         /// \param curingDuration the curing duration in days
         ACI209CuringCorrectionFactorModel(CuringType curingType,Float64 curingDuration);
         ACI209CuringCorrectionFactorModel(const ACI209CuringCorrectionFactorModel& rOther) = default;

         virtual ~ACI209CuringCorrectionFactorModel() = default;

         ACI209CuringCorrectionFactorModel& operator=(const ACI209CuringCorrectionFactorModel& rOther) = default;

         void SetCuringType(CuringType curingType);
         CuringType GetCuringType() const;

         void SetCuringDuration(Float64 curingDuration);
         Float64 GetCuringDuration() const;

         virtual Float64 GetCorrectionFactor() const;

      private:
         CuringType m_CuringType{ CuringType::Moist };
         Float64 m_CuringDuration{ 7.0 };

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      /// Specialization of the shrinkage strain model to accomodate ACI209 correction factors
      /// that are not supported by the base class. Specifically, this class adds the curing correction factor model
      class MATCLASS ACI209ConcreteShrinkageModel : public ConcreteShrinkageTemplateModel
      {
      public:
         ACI209ConcreteShrinkageModel(Float64 ecu);
         ACI209ConcreteShrinkageModel();
         ACI209ConcreteShrinkageModel(const ACI209ConcreteShrinkageModel& rOther) = default;

         virtual ~ACI209ConcreteShrinkageModel() = default;

         ACI209ConcreteShrinkageModel& operator=(const ACI209ConcreteShrinkageModel& rOther) = default;

         void SetCuringCorrectionFactorModel(const std::shared_ptr<const ACI209CuringCorrectionFactorModel>& model);
         const std::shared_ptr<const ACI209CuringCorrectionFactorModel>& GetCuringCorrectionFactorModel() const;

         virtual Float64 GetShrinkageStrain(Float64 t) const override;

      private:
         std::shared_ptr<const ACI209CuringCorrectionFactorModel> m_CuringModel{std::make_shared<ACI209CuringCorrectionFactorModel>()};

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
