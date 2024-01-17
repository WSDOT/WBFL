///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <EAF\EAFTransaction.h>

class testUndoableTxn : public CEAFTransaction
{
public:
   testUndoableTxn();
   virtual bool Execute() override;
   virtual void Undo() override;
   virtual std::unique_ptr<CEAFTransaction> CreateClone() const override;
   virtual void Log(std::_tostream& os) const override;
   virtual std::_tstring Name() const override;
   virtual bool IsUndoable() const override;
   virtual bool IsRepeatable() const override;
};

class testNotUndoableTxn : public CEAFTransaction
{
public:
   testNotUndoableTxn();
   virtual bool Execute() override;
   virtual std::unique_ptr<CEAFTransaction> CreateClone() const override;
   virtual void Log(std::_tostream& os) const override;
   virtual std::_tstring Name() const override;
   virtual bool IsUndoable() const override;
   virtual bool IsRepeatable() const override;
};

class testNotRepeatableTxn : public CEAFTransaction
{
public:
   testNotRepeatableTxn();
   virtual bool Execute() override;
   virtual void Undo() override;
   virtual std::unique_ptr<CEAFTransaction> CreateClone() const override;
   virtual void Log(std::_tostream& os) const override;
   virtual std::_tstring Name() const override;
   virtual bool IsUndoable() const override;
   virtual bool IsRepeatable() const override;
};
