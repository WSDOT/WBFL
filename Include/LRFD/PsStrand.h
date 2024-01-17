///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Materials/PsStrand.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Encapsulates constants and equations associated with prestressing strands.
      class LRFDCLASS PsStrand
      {
      public:
         enum class Stage { Jacking, BeforeTransfer, AfterTransfer, AfterAllLosses };

         PsStrand() = delete;
         PsStrand(const PsStrand&) = delete;
         virtual ~PsStrand() = delete;

         PsStrand& operator=(const PsStrand&) = delete;

         static Float64 GetUltimateStrength(WBFL::Materials::PsStrand::Grade gr);
         static Float64 GetYieldStrength(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type);
         static Float64 GetStressLimit(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type,Stage stage);
         static Float64 GetModE();

         //------------------------------------------------------------------------
         // Calculates the maximum jacking force for the specified prestressing
         // strands.
         static Float64 GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer);
         static Float64 GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer,Float64 coeff);

         //------------------------------------------------------------------------
         // Calcuates the maximum jacking stress for the specified prestressing strands.
         static Float64 GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer);
         static Float64 GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer,Float64 coeff);

         //------------------------------------------------------------------------
         // Computes the prestress transfer length. 5.11.4.1
         static Float64 GetXferLength(const WBFL::Materials::PsStrand& strand,bool bEpoxyCoated);

         //------------------------------------------------------------------------
         // Returns the coefficient k used to compute the prestress development length. 5.11.4.2
         static Float64 GetDevLengthFactor(Float64 mbrDepth,bool bDebonded);

         //------------------------------------------------------------------------
         // Computes the prestress development length. 5.11.4.2
         static Float64 GetDevLength(const WBFL::Materials::PsStrand& strand, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded = false);
         static Float64 GetDevLength(Float64 db, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded = false);

         //------------------------------------------------------------------------
         // Computes the maximum jacking stress for post-tensioning
         static Float64 GetFpjPT(const WBFL::Materials::PsStrand& strand);

         //------------------------------------------------------------------------
         // Computes the maximum jacking force for post-tensioning
         static Float64 GetPjackPT(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands);
      };
   };
};
