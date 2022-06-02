///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

// Command Identifiers
// From MFC Tech Note 022, command identifiers should be in the range 0x8000 (32768) to 0xDFFF (57343)
// EAF is going to reserve 256 command IDs
#define EAF_RESERVED_COMMAND_BASE 0x8000 // (32768) base identifier for reserved commands

// This is the first command ID that can be used by actual applications
// that sub-class CEAFApp or CEAFPluginApp
#define EAF_FIRST_USER_COMMAND (EAF_RESERVED_COMMAND_BASE+0x0100) // (33024) first command ID that can be used by sub-classes

// Commands that EAFApp provides standard process for. This is like the way
// CWinApp profiles standard processing for ID_FILE_NEW and ID_FILE_OPEN
// max is EAF_RESERVED_COMMAND_BASE+255
#define EAFID_VIEW_STATUSCENTER            (EAF_RESERVED_COMMAND_BASE+0)
#define EAFID_VIEW_STATUSCENTER2           (EAF_RESERVED_COMMAND_BASE+1)
#define EAFID_VIEW_STATUSCENTER3           (EAF_RESERVED_COMMAND_BASE+2)
#define EAFID_APP_LEGAL                    (EAF_RESERVED_COMMAND_BASE+3)
#define EAFID_UNITS_SI                     (EAF_RESERVED_COMMAND_BASE+4)
#define EAFID_UNITS_US                     (EAF_RESERVED_COMMAND_BASE+5)
#define EAFID_EDIT_UNITS                   (EAF_RESERVED_COMMAND_BASE+6)
#define EAFID_TIPOFTHEDAY                  (EAF_RESERVED_COMMAND_BASE+7)
#define EAFID_MANAGE_APP_PLUGINS           (EAF_RESERVED_COMMAND_BASE+8)
#define EAFID_REPORT_MENU_DISPLAY_MODE     (EAF_RESERVED_COMMAND_BASE+9)
#define EAFID_OPTIONS_REPORTING            (EAF_RESERVED_COMMAND_BASE+10)
#define EAFID_OPTIONS_HINTS                (EAF_RESERVED_COMMAND_BASE+11)
#define EAFID_TOGGLE_AUTOCALC              (EAF_RESERVED_COMMAND_BASE+12)
#define EAFID_AUTOCALC_UPDATENOW           (EAF_RESERVED_COMMAND_BASE+13)
#define EAFID_HELP_SOURCE                  (EAF_RESERVED_COMMAND_BASE+14)
#define EAFID_HELPWND_BACK                 (EAF_RESERVED_COMMAND_BASE+15)
#define EAFID_HELPWND_FORWARD              (EAF_RESERVED_COMMAND_BASE+16)
#define EAFID_OPTIONS_AUTOSAVE             (EAF_RESERVED_COMMAND_BASE+17)
#define EAFID_HELP_VIEWER                  (EAF_RESERVED_COMMAND_BASE+18)

// reserve commands IDs for the report popup menus (first ID must be one more than the EAFID_xxx above)
#define EAF_REPORT_MENU_BASE (EAF_RESERVED_COMMAND_BASE+19)
#define EAF_REPORT_MENU_COUNT 50 // maximum 50 reports
#define EAF_REPORT_MENU_LAST (EAF_REPORT_MENU_BASE + 2*EAF_REPORT_MENU_COUNT)

// reserve command IDs for the graph popup menus
#define EAF_GRAPH_MENU_BASE (EAF_REPORT_MENU_LAST + 1)
#define EAF_GRAPH_MENU_COUNT 50 // maximum 50 graphs
#define EAF_GRAPH_MENU_LAST (EAF_GRAPH_MENU_BASE + EAF_GRAPH_MENU_COUNT)

// reserve command IDs for toolbar menu
#define EAF_TOOLBAR_MENU_BASE (EAF_GRAPH_MENU_LAST + 1)
#define EAF_TOOLBAR_MENU_COUNT 40 // maximum of 40 toolbars
#define EAF_TOOLBAR_MENU_LAST (EAF_TOOLBAR_MENU_BASE + EAF_TOOLBAR_MENU_COUNT)

// reservied IDs for status bar items
#define EAFID_INDICATOR_MIN                1
#define EAFID_INDICATOR_MODIFIED           1  // Modifed box
#define EAFID_INDICATOR_STATUS             2  // Status center indicator
#define EAFID_INDICATOR_AUTOCALC_ON        3  // AutoCalc mode is on
#define EAFID_INDICATOR_AUTOCALC_OFF       4  // AutoCalc mode is off
#define EAFID_INDICATOR_AUTOSAVE_ON        5  // Autosave mode is on
#define EAFID_INDICATOR_AUTOSAVE_OFF       6  // Autosave mode is off
#define EAFID_INDICATOR_MAX                6

