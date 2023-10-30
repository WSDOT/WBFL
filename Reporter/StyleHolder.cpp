///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include <Reporter\StyleHolder.h>        // class implementation

rptStyleHolder::rptStyleHolder() :
rptReportItem()
{
}

rptStyleHolder::rptStyleHolder(const rptStyleName& MyStyleName) :
rptReportItem(MyStyleName)
{
}

rptStyleHolder::rptStyleHolder(const rptStyleHolder& rOther) :
rptReportItem(rOther)
{
   MakeCopy(rOther);
}

rptStyleHolder::~rptStyleHolder()
{
}

rptStyleHolder& rptStyleHolder::operator= (const rptStyleHolder& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

void rptStyleHolder::MakeCopy(const rptStyleHolder& rOther)
{
   // Add copy code here...
}

void rptStyleHolder::MakeAssignment(const rptStyleHolder& rOther)
{
   rptReportItem::MakeAssignment( rOther );
   MakeCopy( rOther );
}
