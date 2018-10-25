///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_PGSEXT_WSDOTCALCULATIONSHEET_H_
#define INCLUDED_PGSEXT_WSDOTCALCULATIONSHEET_H_
#pragma once

// SYSTEM INCLUDES
//
#include <System\System.h>
#include <GeometricPrimitives\GeometricPrimitives.h>

// PROJECT INCLUDES
//
#include <MfcTools\MfcToolsExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   WsdotCalculationSheet

   Class to print a standard WSDOT calculation page border.


DESCRIPTION
   This class prints a standard WSDOT calculation page border. You will need
   to set all parameters to get it to look right.

LOG
   rdp : 02.23.2000 : Created file
*****************************************************************************/

class MFCTOOLSCLASS WsdotCalculationSheet
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   WsdotCalculationSheet();

   //------------------------------------------------------------------------
   // Copy constructor
   WsdotCalculationSheet(const WsdotCalculationSheet& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~WsdotCalculationSheet();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   WsdotCalculationSheet& operator = (const WsdotCalculationSheet& rOther);

   // GROUP: OPERATIONS

   // Print the calculation sheet - returns a rect which defines the client
   // area of the sheet in device coordinates.
   // If doPrint is false, no printing is done - just return client area.
   CRect Print(CDC* pDC, Uint32 sheetNumber, bool doPrint=true);

   // GROUP: ACCESS

   // text to be printed on title block

   void SetTitle(const CString& title);
   CString GetTitle() const;

   void SetEngineer(const CString& engineer);
   CString GetEngineer() const;

   void SetCompany(const CString& Company);
   CString GetCompany() const;

   void SetBridgeName( const CString& Bridge);
   CString GetBridgeName() const;

   void SetBridgeID(const CString& bridgeId);
   CString GetBridgeId() const;

   void SetProjectName( const CString& project);
   CString GetProjectName() const;

   void SetJobNumber(const CString& jobNumber);
   CString GetJobNumber() const;

   // max number of sheets - "sheet 1 of ??"
   void SetMaxSheetNumber(Uint32 maxSheetNumber);
   Uint32 GetMaxSheetNumber() const;

   void SetFileName(const CString& FileName);
   CString GetFileName() const;

   // Rect defining size of margins (top,left,bottom,right) in Millimeters!
   // defaults to left=20mm, top=right=bottom=10mm
   void SetMargins( const gpRect2d margins);
   gpRect2d GetMargins() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const WsdotCalculationSheet& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const WsdotCalculationSheet& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   CString m_Title;
   CString m_Engineer;
   CString m_Company;
   CString m_Bridge;
   CString m_BridgeId;
   CString m_Project;
   CString m_JobNumber;
   CString m_FileName;

   Uint32      m_MaxSheetNo;
   gpRect2d    m_Margins; // inches

   // internals
   // fonts
   CString     m_FontFace;
   Uint32      m_PointSize;
   CFont m_RegFont;
   CFont m_BoldFont;
   CFont m_TitleFont;
   CFont m_FileNameFont;

   // locations of various items in LOMETRIC coords
   mutable CRect  m_Border;
   mutable CPoint m_CompanyLoc;
   mutable CPoint m_ProjectLoc;
   mutable CPoint m_JobNumberLoc;
   mutable CPoint m_SheetLoc;
   mutable CPoint m_BridgeLoc;
   mutable CPoint m_BridgeIdLoc;
   mutable CPoint m_EngineerLoc;
   mutable CPoint m_TitleLoc;
   mutable CPoint m_DateLoc;
   mutable CPoint m_FileNameLoc;

   mutable int m_LineSpacing; // title block lines

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   bool CalculateMetrics(CDC* pDC);
   // GROUP: ACCESS
   // GROUP: INQUIRY

};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_PGSEXT_WSDOTCALCULATIONSHEET_H_
