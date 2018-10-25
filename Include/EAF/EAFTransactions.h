///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <System\Transaction.h>

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
interface IEAFTransactions : IUnknown
{
   virtual void Execute(txnTransaction& rTxn) = 0;
   virtual void Execute(txnTransaction* pTxn) = 0;
   virtual void Undo() = 0;
   virtual void Redo() = 0;
   virtual void Repeat() = 0;
   virtual bool CanUndo() = 0;
   virtual bool CanRedo() = 0;
   virtual bool CanRepeat() = 0;
   virtual std::_tstring UndoName() = 0;
   virtual std::_tstring RedoName() = 0;
   virtual std::_tstring RepeatName() = 0;
   virtual CollectionIndexType GetTxnCount() = 0;
   virtual CollectionIndexType GetUndoCount() = 0;
};
