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
#include <EAF\EAFTransaction.h>
#include <memory>

/// @brief A macro transaction is a collection of other transactions.
class EAFCLASS CEAFMacroTxn : public CEAFTransaction
{
public:
   CEAFMacroTxn() = default;
   virtual ~CEAFMacroTxn() = default; 

   CEAFMacroTxn(const CEAFMacroTxn&) = delete;
   CEAFMacroTxn& operator=(const CEAFMacroTxn&) = delete;

   virtual bool Execute() override;
   virtual void Undo() override;
   virtual std::_tstring Name() const override;
   virtual std::unique_ptr<CEAFTransaction> CreateClone() const override;
   virtual void Log(std::_tostream& os) const override;
   virtual bool IsUndoable() const override;
   virtual bool IsRepeatable() const override;
   
   /// @brief Sets the transactions name
   void Name(const std::_tstring& name);
   
   /// @brief Adds a transaction to this macro. The transcation will be cloned.
   void AddTransaction(CEAFTransaction& rTxn);

   /// @brief Adds a transaction to this macro.
   void AddTransaction(std::unique_ptr<CEAFTransaction>&& pTxn);

   /// @brief Returns the number of transactions in this macro.
   IndexType GetTxnCount() const;

protected:
   std::_tstring m_Name{ _T("Macro") };
   using TxnContainer = std::vector<std::unique_ptr<CEAFTransaction>>;
   TxnContainer m_Transactions;
};
