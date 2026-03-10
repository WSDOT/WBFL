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

#include <EAF\Transaction.h>

/*****************************************************************************
INTERFACE
   IEAFTransactions

   Interface for executing transaction objects

DESCRIPTION
   Interface for executing transaction objects. Transaction objects
   allow edits to be undone and redone

*****************************************************************************/
// {3FA1C988-FC39-4a3d-A0E9-F4EC48871AC1}
DEFINE_GUID(IID_IEAFTransactions, 
0x3fa1c988, 0xfc39, 0x4a3d, 0xa0, 0xe9, 0xf4, 0xec, 0x48, 0x87, 0x1a, 0xc1);
interface IEAFTransactions
{
   virtual void Execute(const WBFL::EAF::Transaction& rTxn) = 0;
   virtual void Execute(std::unique_ptr<WBFL::EAF::Transaction>&& pTxn) = 0;
   virtual void Undo() = 0;
   virtual void Redo() = 0;
   virtual void Repeat() = 0;
   virtual bool CanUndo() const = 0;
   virtual bool CanRedo() const = 0;
   virtual bool CanRepeat() const = 0;
   virtual std::_tstring UndoName() const = 0;
   virtual std::_tstring RedoName() const = 0;
   virtual std::_tstring RepeatName() const = 0;
   virtual IndexType GetTxnCount() const = 0;
   virtual IndexType GetUndoCount() const = 0;
};
