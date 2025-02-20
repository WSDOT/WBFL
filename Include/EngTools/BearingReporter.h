///////////////////////////////////////////////////////////////////////
// Stability
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <EngTools\Bearing.h>
#include <EngTools\BearingLoads.h>
#include <EngTools\BearingCalculator.h>
#include <Reporter\Chapter.h>
#include <Units/IndirectMeasure.h>
#include <LRFD/BDSManager.h>


namespace WBFL
{
   namespace EngTools
   {
      ///  Generates reports for lifting stability analysis
      class ENGTOOLSCLASS BearingReporter
      {
      public:
         BearingReporter();

         /// Builds the specification check chapter
         void BuildSpecCheckChapter(const WBFL::Units::IndirectMeasure* pDispUnits, rptChapter* pChapter, 
             rptParagraph* pPara, const Bearing& brg, const BearingLoads& brg_loads, 
             const BearingCalculator& brg_calc, const WBFL::LRFD::BDSManager::Edition spec);
      };
   }
}