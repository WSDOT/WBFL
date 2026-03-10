///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <EAF\EAFExp.h>
#include <EAF\Transaction.h>
#include <memory>

namespace WBFL
{
   namespace EAF
   {
      /// @brief A macro transaction is a collection of other transactions.
      class EAFCLASS MacroTxn : public Transaction
      {
      public:
         MacroTxn() = default;
         virtual ~MacroTxn() = default; 

         MacroTxn(const MacroTxn&) = delete;
         MacroTxn& operator=(const MacroTxn&) = delete;

         virtual bool Execute() override;
         virtual void Undo() override;
         virtual std::_tstring Name() const override;
         virtual std::unique_ptr<Transaction> CreateClone() const override;
         virtual void Log(std::_tostream& os) const override;
         virtual bool IsUndoable() const override;
         virtual bool IsRepeatable() const override;
   
         /// @brief Sets the transactions name
         void Name(const std::_tstring& name);
   
         /// @brief Adds a transaction to this macro. The transcation will be cloned.
         void AddTransaction(Transaction& rTxn);

         /// @brief Adds a transaction to this macro.
         void AddTransaction(std::unique_ptr<Transaction>&& pTxn);

         /// @brief Returns the number of transactions in this macro.
         IndexType GetTxnCount() const;

      protected:
         std::_tstring m_Name{ _T("Macro") };
         using TxnContainer = std::vector<std::unique_ptr<Transaction>>;
         TxnContainer m_Transactions;
      };
   };
};
