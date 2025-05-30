///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <EAF\EAFTypes.h>
#include <EAF\Broker.h>
#include <EAF\Transaction.h>
#include <array>

namespace WBFL
{
   namespace EAF
   {
      class ChangeUnitsTxn : public Transaction
      {
      public:
         ChangeUnitsTxn(std::weak_ptr<WBFL::EAF::Broker> pBroker,WBFL::EAF::UnitMode oldUnits,WBFL::EAF::UnitMode newUnits);
         virtual std::_tstring Name() const override;
         virtual std::unique_ptr<Transaction> CreateClone() const override;
         virtual bool Execute() override;
         virtual void Undo() override;
         virtual bool IsUndoable() const override;
         virtual bool IsRepeatable() const override;

      private:
         bool DoExecute(int i);
         std::weak_ptr<WBFL::EAF::Broker> m_pBroker;
         std::array<WBFL::EAF::UnitMode, 2> m_UnitMode;
      };
   };
};
