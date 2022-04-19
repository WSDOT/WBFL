///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_CONNECTION_H_
#define INCLUDED_BRIDGEMODELING_CONNECTION_H_
#pragma once

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bmfConnection
// SYNOPSIS:      
// DESCRIPTION:   Connections describe the geometry at the intersection
//                of a girder and a pier.  The end region of a girder
//                is considered to be a function of both the girder and
//                the pier.  Since these properties are neither exclusively
//                members of a girder or pier, they are captured in this
//                attributed class.
// EXAMPLES:      
// BUGS:          
// ALSO SEE:
//////////////////X////////////////////X/////////////////////////////////////

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

class BMFCLASS bmfConnection
{
public:
   // LIFECYCLE

   // Method:      Connection
   // Description: Default c'tor
   // Return:      N/A
   bmfConnection();

   // Method:      Connection
   // Description: Default c'tor
   // Return:      N/A
   bmfConnection(const std::_tstring& name,
                 Float64 brgOffset,
                 bmfMeasuredHow how_brg,
                 Float64 gdrEndSize,
                 bmfMeasuredHow how_gdr);

   // Method:      Connection
   // Description: Copy c'tor
   // Return:      N/A
   bmfConnection(const bmfConnection& connection);

   // Method:      ~Connection
   // Description: d'tor
   // Return:      N/A
   virtual ~bmfConnection(); 

   // OPERATORS

   // Method:      operator =
   // Description: Assignment operator
   // Return:      Reference to self.
   bmfConnection& operator = (const bmfConnection& connection);

   // OPERATIONS

   // ACCESS

   // Method:      GetBearingOffset
   // Description: Returns the location of the bearing line measured
   //              as an offset from the pier station.  The pier station
   //              is the back of pavement seat for end piers and
   //              the centerline of pier for interior piers.
   // Return:      Returns bearing offset
   Float64 GetBearingOffset() const;
   bmfMeasuredHow GetHowBearingOffSetIsMeasured() const;

   // Method:      GetGirderEndSize
   // Description: Returns the length of the end region of a girder.  The
   //              end region is that portion of the girder between the
   //              end of the girder and the point of bearing.
   // Return:      Returns girder end size
   Float64 GetGirderEndSize() const;
   bmfMeasuredHow GetHowGirderEndSizeIsMeasured() const;

   std::_tstring GetName() const;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   std::_tstring m_Name;
   Float64 m_BearingOffset;
   Float64 m_GirderEndSize;
   bmfMeasuredHow m_BearingHow;
   bmfMeasuredHow m_GirderHow;

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void MakeCopy(const bmfConnection& connection);

   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_CONNECTION_H_
