///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <boost\shared_ptr.hpp>

struct matConcreteBaseShrinkageDetails;
struct matConcreteBaseCreepDetails;

/*****************************************************************************
CLASS 
   matConcreteBase

   Abstract base class for time-dependent concrete material models.
*****************************************************************************/

class MATCLASS matConcreteBase
{
public:
   enum Type { Normal, AllLightweight, SandLightweight };
   enum CureMethod { Moist, Steam };

   matConcreteBase(LPCTSTR name = _T("Unknown"));
   virtual ~matConcreteBase();

   void SetName(const std::_tstring& name);
   std::_tstring GetName() const;

   // Set/Get the time of concrete
   void SetType(Type type);
   Type GetType() const;

   // Returns a string name that represents the type of concrete.
   static std::_tstring GetTypeName(Type type,bool bFull);
   static Type GetTypeFromName(LPCTSTR strName);

   // Indicates if the concrete defines an aggregate splitting strength
   bool HasAggSplittingStrength() const;
   void HasAggSplittingStrength(bool bHasFct);

   // Set/Get the aggregate splitting strength
   void SetAggSplittingStrength(Float64 ft);
   Float64 GetAggSplittingStrength() const;

   // Set/Get the maximum aggregate size
   void SetMaxAggregateSize(Float64 size);
   Float64 GetMaxAggregateSize() const;

   // Set/Get the density of the concrete used for computing secant modulus
   void SetStrengthDensity(Float64 d);
   Float64 GetStrengthDensity() const;

   // Set/Get the density of the concrete used for computing unit weight
   void SetWeightDensity(Float64 d);
   Float64 GetWeightDensity() const;

   // Set/Get the ambient relative humidity
   void SetRelativeHumidity(Float64 rh);
   Float64 GetRelativeHumidity() const;

   // Set/Get the volume to surface area (V/S) ratio
   void SetVSRatio(Float64 vs);
   Float64 GetVSRatio() const;

   // Set/Get the time when the concrete is cast. When getting properties
   // such as Ec, this time is subtracted from the time provided to get
   // the age of the concrete.
   void SetTimeAtCasting(Float64 time);
   Float64 GetTimeAtCasting() const;

   // Age when the concrete first takes load (for creep)
   void SetAgeAtInitialLoading(Float64 age);
   Float64 GetAgeAtInitialLoading() const;

   // Set/Get the cure time
   void SetCureTime(Float64 t);
   Float64 GetCureTime() const;

   // Set/Get the cure method
   void SetCureMethod(matConcreteBase::CureMethod method);
   matConcreteBase::CureMethod GetCureMethod() const;

   // Returns the age of the concrete at time t. Return value is < 0
   // if t is before casting
   Float64 GetAge(Float64 t) const;

   // Returns the compressive strength of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFc(Float64 t) const = 0;

   // Returns the secant modulus of the concrete at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetEc(Float64 t) const = 0;

   // Returns the modulus of rupture for shear calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetShearFr(Float64 t) const = 0;

   // Returns the modulus of rupture for flexure calculations at time t. If
   // t occurs before the time at casting, zero is returned.
   virtual Float64 GetFlexureFr(Float64 t) const = 0;

   // Returns the total free shrinkage that has occured from time at casting
   // to the time specified
   virtual Float64 GetFreeShrinkageStrain(Float64 t) const = 0;
   virtual boost::shared_ptr<matConcreteBaseShrinkageDetails> GetFreeShrinkageStrainDetails(Float64 t) const = 0;

   // Returns the creep coefficient at time t for a loading applied at time tla
   virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const = 0;
   virtual boost::shared_ptr<matConcreteBaseCreepDetails> GetCreepCoefficientDetails(Float64 t,Float64 tla) const = 0;

   // Creates a clone of this object
   virtual matConcreteBase* CreateClone() const = 0;

protected:
   // prevent copying and assignment (use CreateClone instead)
   matConcreteBase(const matConcreteBase& rOther);
   matConcreteBase& operator = (const matConcreteBase& rOther);

   virtual void OnChanged();

   void InitializeShrinkageDetails(Float64 t,matConcreteBaseShrinkageDetails* pDetails) const;
   void InitializeCreepDetails(Float64 t,Float64 tla,matConcreteBaseCreepDetails* pDetails) const;

protected:
   Type        m_Type;
   std::_tstring m_Name;
   bool        m_bHasFct; // has aggregate splitting strength
   Float64     m_Fct;     // aggregate splitting strength
   Float64     m_MaxAggregateSize;
   Float64     m_StrengthDensity;
   Float64     m_WeightDensity;
   Float64     m_RelativeHumidity;
   Float64     m_VS; // V/S ratio
   Float64     m_TimeAtCasting; // time at casting... days
   Float64     m_AgeAtInitialLoading; // days
   Float64     m_CureTime; // duration of time that the concrete is cured
   CureMethod  m_CureMethod;
};


struct MATCLASS matConcreteBaseShrinkageDetails
{
   matConcreteBaseShrinkageDetails() : shrinkage_duration(0), cureMethod(matConcreteBase::Moist), esh(0) {}
   Float64 shrinkage_duration; // duration of time overwhich shrinkage occurs
   matConcreteBase::CureMethod cureMethod;
   Float64 esh;
};

struct MATCLASS matConcreteBaseCreepDetails
{
   matConcreteBaseCreepDetails() : age(0), age_at_loading(0), fci(0), Ct(0) {}
   Float64 age;
   Float64 age_at_loading;
   Float64 fci;
   Float64 Ct;
};