///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#ifndef INCLUDED_LRFD_LIMITSTATECALCULATOR_H_
#define INCLUDED_LRFD_LIMITSTATECALCULATOR_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <System\SectionAction.h>
#include <Lrfd\LoadModifier.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdLimitStateCalculator

   Computes limit state combinations.


DESCRIPTION
   Computes limit state combinations.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.11.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLimitStateCalculator
{
public:
   // GROUP: ENUMERATIONS
   enum Action { Fx, Fy, Mz, Dx, Dy, Rz };
   enum HorizEarthPressure {Active, AtRest};
   enum VertEarthPressure {OverallStability,
                           RetainingStructures,
                           RigidBuriedStructures,
                           RigidFrames,
                           FlexibleBuriedStructures,
                           FlexibleMetalBoxCulverts};
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdLimitStateCalculator();

   //------------------------------------------------------------------------
   // Copy constructor
   lrfdLimitStateCalculator(const lrfdLimitStateCalculator& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~lrfdLimitStateCalculator();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   lrfdLimitStateCalculator& operator = (const lrfdLimitStateCalculator& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Computes the limit state for the previously defined structural actions.
   sysSectionAction ComputeLimitState(lrfdTypes::LimitState ls,Action action = Mz,lrfdTypes::Optimization opt = lrfdTypes::Max);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the load modifier
   void SetLoadModifier(const lrfdLoadModifier& lm);

   //------------------------------------------------------------------------
   // Returns the load modifier
   lrfdLoadModifier GetLoadModifier();

   //------------------------------------------------------------------------
   void SetLiveLoadDistFactors(const sysSectionValue& gFx,const sysSectionValue& gFy,const sysSectionValue& gMz,
                               const sysSectionValue& gDx,const sysSectionValue& gDy,const sysSectionValue& gRz);
   void GetLiveLoadDistFactors(sysSectionValue* pgFx,sysSectionValue* pgFy,sysSectionValue* pgMz,
                               sysSectionValue* pgDx,sysSectionValue* pgDy,sysSectionValue* pgRz);

   //------------------------------------------------------------------------
   void SetDC(const sysSectionAction& dc);
   void SetDD(const sysSectionAction& dd);
   void SetDW(const sysSectionAction& dw);
   void SetEH(const sysSectionAction& eh,HorizEarthPressure hep);
   void SetEV(const sysSectionAction& eh,VertEarthPressure vep);
   void SetES(const sysSectionAction& es);
   void SetLLIM(const sysSectionAction& llim);
   void SetCE(const sysSectionAction& ce);
   void SetBR(const sysSectionAction& br);
   void SetPL(const sysSectionAction& pl);
   void SetLS(const sysSectionAction& ls);
   void SetEL(const sysSectionAction& el);
   void SetWA(const sysSectionAction& wa);
   void SetWS(const sysSectionAction& ws);
   void SetWL(const sysSectionAction& wl);
   void SetFR(const sysSectionAction& fr);
   void SetTU(const sysSectionAction& tu);
   void SetCR(const sysSectionAction& cr);
   void SetSH(const sysSectionAction& sh);
   void SetTG(const sysSectionAction& tg);
   void SetSE(const sysSectionAction& se);
   void SetEQ(const sysSectionAction& eq);
   void SetIC(const sysSectionAction& ic);
   void SetCT(const sysSectionAction& ct);
   void SetCV(const sysSectionAction& cv);

   sysSectionAction GetDC() const;
   sysSectionAction GetDD() const;
   sysSectionAction GetDW() const;
   sysSectionAction GetEH() const;
   sysSectionAction GetEV() const;
   sysSectionAction GetES() const;
   sysSectionAction GetLLIM() const;
   sysSectionAction GetCE() const;
   sysSectionAction GetBR() const;
   sysSectionAction GetPL() const;
   sysSectionAction GetLS() const;
   sysSectionAction GetEL() const;
   sysSectionAction GetWA() const;
   sysSectionAction GetWS() const;
   sysSectionAction GetWL() const;
   sysSectionAction GetFR() const;
   sysSectionAction GetTU() const;
   sysSectionAction GetCR() const;
   sysSectionAction GetSH() const;
   sysSectionAction GetTG() const;
   sysSectionAction GetSE() const;
   sysSectionAction GetEQ() const;
   sysSectionAction GetIC() const;
   sysSectionAction GetCT() const;
   sysSectionAction GetCV() const;

   HorizEarthPressure GetHorizEarthPressure() const;
   VertEarthPressure GetVertEarthPressure() const;

   Float64 GetMaxDCLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDCLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionDCLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionDCLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxDDLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDDLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionDDLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionDDLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxDWLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDWLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionDWLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionDWLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const;
   Float64 GetMinEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const;
   Float64 GetMaxDeflectionEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const;
   Float64 GetMinDeflectionEHLoadFactor(lrfdTypes::LimitState ls,HorizEarthPressure hep) const;

   Float64 GetMaxEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const;
   Float64 GetMinEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const;
   Float64 GetMaxDeflectionEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const;
   Float64 GetMinDeflectionEVLoadFactor(lrfdTypes::LimitState ls,VertEarthPressure vep) const;

   Float64 GetMaxESLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinESLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionESLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionESLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxLLIMLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinLLIMLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionLLIMLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionLLIMLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxCELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinCELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionCELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionCELoadFactor(lrfdTypes::LimitState ls) const;
   
   Float64 GetMaxBRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinBRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionBRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionBRLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxPLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinPLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionPLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionPLLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxLSLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinLSLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionLSLoadFactor(lrfdTypes::LimitState ls) const;   
   Float64 GetMinDeflectionLSLoadFactor(lrfdTypes::LimitState ls) const;   

   Float64 GetMaxELLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinELLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionELLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionELLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxWALoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinWALoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionWALoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionWALoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxWSLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinWSLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionWSLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionWSLoadFactor(lrfdTypes::LimitState ls) const;
   
   Float64 GetMaxWLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinWLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionWLLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionWLLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxFRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinFRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionFRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionFRLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxTULoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinTULoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionTULoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionTULoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxCRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinCRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionCRLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionCRLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxSHLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinSHLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionSHLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionSHLoadFactor(lrfdTypes::LimitState ls) const;

   void SetTGLoadFactors(Float64 gTGmin,Float64 gTGmax,Float64 gTGdmin,Float64 gTGdmax);
   Float64 GetMaxTGLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinTGLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionTGLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionTGLoadFactor(lrfdTypes::LimitState ls) const;

   void SetSELoadFactors(Float64 gSEmin,Float64 gSEmax,Float64 gSEdmin,Float64 gSEdmax);
   Float64 GetMaxSELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinSELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionSELoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionSELoadFactor(lrfdTypes::LimitState ls) const;

   void SetEQLoadFactors(Float64 gEQmin,Float64 gEQmax,Float64 gEQdmin,Float64 gEQdmax);
   Float64 GetMaxEQLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinEQLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionEQLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionEQLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxICLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinICLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionICLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionICLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxCTLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinCTLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionCTLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionCTLoadFactor(lrfdTypes::LimitState ls) const;

   Float64 GetMaxCVLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinCVLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMaxDeflectionCVLoadFactor(lrfdTypes::LimitState ls) const;
   Float64 GetMinDeflectionCVLoadFactor(lrfdTypes::LimitState ls) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLimitStateCalculator& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLimitStateCalculator& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   sysSectionAction m_Actions[lrfdTypes::LoadCombinationCount];
   lrfdLoadModifier m_LoadModifier;
   HorizEarthPressure m_HorizEarthPressure;
   VertEarthPressure m_VertEarthPressure;
   Float64 m_MinTG, m_MaxTG, m_MaxDeflTG, m_MinDeflTG;
   Float64 m_MinEQ, m_MaxEQ, m_MaxDeflEQ, m_MinDeflEQ;
   Float64 m_MinSE, m_MaxSE, m_MaxDeflSE, m_MinDeflSE;

   // Live load distribution factors
   sysSectionValue m_gFx;
   sysSectionValue m_gFy;
   sysSectionValue m_gMz;
   sysSectionValue m_gDx;
   sysSectionValue m_gDy;
   sysSectionValue m_gRz;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   Float64 GetMaxLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo);
   Float64 GetMinLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo);
   Float64 GetMaxDeflLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo);
   Float64 GetMinDeflLoadFactor(lrfdTypes::LimitState ls,lrfdTypes::LoadCombination combo);

   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_LIMITSTATECALCULATOR_H_
