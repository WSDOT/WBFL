///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEMODELING_PIER_H_
#define INCLUDED_BRIDGEMODELING_PIER_H_
#pragma once

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bmfPier
// SYNOPSIS:      
// DESCRIPTION:   A vertical structural component whose purpose is to
//                support spans.  
//
//                In future implementations a pier will be viewed as
//                a collection of structural components, such as
//                cap beams, columns, and footings.
// EXAMPLES:      
// BUGS:          
// ALSO SEE:
//////////////////X////////////////////X/////////////////////////////////////

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeModeling\BridgeModelingExp.h>
#include <GraphicsLib\PointMapper.h>
#include <BridgeModeling\PierLayout.h>
#include <BridgeModeling\Connection.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

class BMFCLASS bmfBridge;
class BMFCLASS bmfSpan;

// MISCELLANEOUS
//

class BMFCLASS bmfPier
{
public:
   // LIFECYCLE

   //------------------------------------------------------------------------
   // Method:      Pier
   // Description: Default c'tor
   // Return:      N/A
   bmfPier();

   //------------------------------------------------------------------------
   // Method:      Pier
   // Description: Explicit c'tor
   // Return:      N/A
   bmfPier(Float64 station,const bmfPierLayout& pl,const bmfConnection* pConnection);

   //------------------------------------------------------------------------
   bmfPier(const bmfPier& rOther);

   //------------------------------------------------------------------------
   // Method:      ~Pier
   // Description: d'tor
   // Return:      N/A
   virtual ~bmfPier(); 

   // OPERATORS

   //------------------------------------------------------------------------
   bmfPier& operator=(const bmfPier& rOther);
   
   //------------------------------------------------------------------------
   // Method:      operator ==
   // Description: Equality operator
   // Return:      true if both piers are at the same location
   bool operator == (const bmfPier& rOther);

   // OPERATIONS

   //------------------------------------------------------------------------
   // Method:      OnSetup
   // Description: Called by the framework when a pier is created.
   //              Override this method to provide specific setup.
   // Return:      None
   virtual void OnSetup();

   //------------------------------------------------------------------------
   // Method:      OnAlignmentChanged
   // Description: Called by the framework immediately after
   //              the alignment is changed.
   // Return:      None
   virtual void OnAlignmentChanged();

   //------------------------------------------------------------------------
   // Method:      Move
   // Description: Moves the pier to a new location while maintaining
   //              is orientation.
   // Return:      None
   void Move(Float64 station);

   //------------------------------------------------------------------------
   // Method:      Layout
   // Description: Changes the layout (orientation) of the pier
   // Return:      None
   void Layout(const bmfPierLayout& pl);

   //------------------------------------------------------------------------
   // Method:      Draw
   // Description: Draws the plan view of the pier
   // Return:      None
   void Draw(HDC hDC,const grlibPointMapper& mapper, bool show_label=true) const;

   // ACCESS

   //------------------------------------------------------------------------
   // Method:      SetID
   // Description: Changes the identifier of the pier
   // Return:      None
   void SetID(PierIDType id);

   //------------------------------------------------------------------------
   // Method:      GetID
   // Description: 
   // Return:      Returns the pier's identifier
   PierIDType GetID() const;

   //------------------------------------------------------------------------
   // Method:      SetConnection
   // Description: Sets the connection component for this pier.
   //              Replaces the previous connection.
   // Return:      None
   void SetConnection(const bmfConnection* pConnection);

   //------------------------------------------------------------------------
   // Method:      GetConnection
   // Description: Access to the connection attribute
   // Return:      Returns a refernece to the connection
   const bmfConnection* GetConnection() const;

   //------------------------------------------------------------------------
   // Method:      GetLayout
   // Description: 
   // Return:      Returns a copy of the pier's layout
   bmfPierLayout GetLayout() const;

   //------------------------------------------------------------------------
   // Method:      GetStation
   // Description: 
   // Return:      Returns the pier station
   Float64 GetStation() const;

   //------------------------------------------------------------------------
   // Method:      GetSkewAngle
   // Description: Skew angle is measured counter clockwise from a line
   //              that is normal to and is to the left of the alignment.
   //              Skew angle is measured in radians.
   // Return:      Returns skew angle
   void GetSkewAngle(IAngle** ppSkewAngle) const;

   //------------------------------------------------------------------------
   // Method:      GetBearing
   // Description: Bearing is measured counter clockwise from due East.
   //              Bearing is measured in radians
   // Return:      Returns bearing of pier
   void GetBearing(IDirection** ppBearing) const;

   //------------------------------------------------------------------------
   // Method:      GetAheadBearingStation
   // Description: Returns the station of the bearing line on the
   //              "ahead on station" side of the pier
   // Return:      Returns ahead bearing station
   Float64 GetAheadBearingStation() const;

   //------------------------------------------------------------------------
   // Method:      GetBackBearingStation
   // Description: Returns the station of the bearing line on the
   //              "back on station" side of the pier
   // Return:      Returns back bearing station
   Float64 GetBackBearingStation() const;

   //------------------------------------------------------------------------
   void SetBridge(bmfBridge* pBridge);

   //------------------------------------------------------------------------
   bmfBridge* GetBridge();

   //------------------------------------------------------------------------
   const bmfBridge* GetBridge() const;

   //------------------------------------------------------------------------
   void SetLeftSpan(bmfSpan* pSpan);

   //------------------------------------------------------------------------
   bmfSpan* GetLeftSpan();

   //------------------------------------------------------------------------
   const bmfSpan* GetLeftSpan() const;

   //------------------------------------------------------------------------
   void SetRightSpan(bmfSpan* pSpan);

   //------------------------------------------------------------------------
   bmfSpan* GetRightSpan();
   
   //------------------------------------------------------------------------
   const bmfSpan* GetRightSpan() const;

   //------------------------------------------------------------------------
   virtual gpRect2d GetBoundingBox() const;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS

   //------------------------------------------------------------------------
   void MakeCopy(const bmfPier& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bmfPier& rOther);

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   PierIDType m_ID;
   bmfBridge* m_pBridge;
   bmfSpan*   m_pLeftSpan;
   bmfSpan*   m_pRightSpan;
   Float64 m_Station;
   const bmfConnection* m_pConnection;
   bmfPierLayout m_Layout;

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEMODELING_PIER_H_
