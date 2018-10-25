///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <Material\Concrete.h>
#include <WBFLGeometry.h>
#include <WBFLGenericBridge.h>

/*****************************************************************************
CLASS 
   lrfdAlternativeTensileStressCalculator

   Utility class for dealing with alternative tensile stress in casting yard and at lifting
*****************************************************************************/

class LRFDCLASS lrfdAlternativeTensileStressCalculator
{
public:
   lrfdAlternativeTensileStressCalculator(const matConcrete& concrete,Float64 fy,bool bLimitBarStress,Float64 fsMax);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdAlternativeTensileStressCalculator()
   {;}

   void SetReinforcementYieldStrength(Float64 fy);
   Float64 GetReinforcementYieldStrength() const;

   // if true, the stress in the mild reinforcement is limited to the bar stress limit, otherwise it is not.
   void LimitBarStress(bool bLimit);
   bool LimitBarStress() const;

   // set/get the bar stress limit
   void SetBarStressLimit(Float64 fsMax);
   Float64 GetBarStressLimit() const;

   void SetConcrete(const matConcrete& concrete);
   const matConcrete& GetConcrete() const;

   void ComputeAlternativeStressRequirements(IShape* pShape,IRebarSection* pRebarSection,
                                                Float64 Wtop,Float64 Wbot,
                                                Float64 fTopLeft, Float64 fTopRight, Float64 fBotLeft, Float64 fBotRight,
                                                Float64 *pYna, Float64* pNAslope, Float64 *pAreaTens, Float64 *pT, 
                                                Float64 *pAsProvd, Float64 *pAsReqd, bool* pbIsAdequateRebar);

   static void ComputeReqdFcTens(Float64 lambda,Float64 ft, // stress demand
                          Float64 rcsT, bool rcsBfmax, Float64 rcsFmax, Float64 rcsTalt, // allowable stress coeff's
                          Float64* pFcNo,Float64* pFcWithRebar);

private:
   lrfdAlternativeTensileStressCalculator(); // no default constructor

   Float64 m_fy;

   bool m_bLimitBarStress;
   Float64 m_fsMax;

   matConcrete m_Concrete;
};
