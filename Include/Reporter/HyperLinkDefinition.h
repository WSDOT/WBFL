///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
#define INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>


/// This class defines a hyperlink definition
///
/// This class may be attached to a piece of report content to define the content as a hyperlink.
class REPORTERCLASS rptHyperLinkDefinition
{
public:
   /// Constructor
   rptHyperLinkDefinition(
      const std::_tstring& HyperTarget ///< name of the link target
   );

   /// Returns the link target name
   const std::_tstring& GetTargetName() const;

   /// Sets the link target name
   void SetTargetName(const std::_tstring& target);

private:
   // the target that we are linking to
   std::_tstring m_TargetName;

   rptHyperLinkDefinition() = delete;
};

#endif // INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
