///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// EAFAutoCalcGraphBuilder.h : header file
//

#include <EAF\EAFExp.h>
#include <EAF\EAFGraphBuilderBase.h>

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcGraphBuilder

class EAFCLASS CEAFAutoCalcGraphBuilder : public CEAFGraphBuilderBase
{
public:
   CEAFAutoCalcGraphBuilder();
   CEAFAutoCalcGraphBuilder(const CEAFAutoCalcGraphBuilder& other);
   virtual ~CEAFAutoCalcGraphBuilder();

   // Updates the graph taking into account the stat of the AutoCalc settings
   virtual void Update() override;

   // Forces the graph to always update
   virtual void ForceUpdate();

protected:

   DECLARE_MESSAGE_MAP()
};
