///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
#define EAF_RESERVED_COMMAND_BASE 32768 // base identifier for reserved commands
#define EAF_REPORT_MENU_BASE EAF_RESERVED_COMMAND_BASE // reserve commands IDs for the report popup menus
#define EAF_REPORT_MENU_COUNT 100
#define EAF_TOOLBAR_MENU_BASE EAF_REPORT_MENU_BASE + EAF_REPORT_MENU_COUNT + 1 // reserver command IDs for toolbar menu
#define EAF_TOOLBAR_MENU_COUNT 20
#define EAF_COMMAND_BASE EAF_TOOLBAR_MENU_BASE + EAF_TOOLBAR_MENU_COUNT + 1 // base command identifier
#define EAF_FIRST_USER_COMMAND 33024 // (0x8100) first command ID that can be used by sub-classes

#define ID_INDICATOR_MODIFIED           1
#define ID_INDICATOR_STATUS             2

// max is EAF_COMMAND_BASE+256
#define ID_VIEW_STATUSCENTER            EAF_COMMAND_BASE
#define ID_VIEW_STATUSCENTER2           EAF_COMMAND_BASE+1
#define ID_VIEW_STATUSCENTER3           EAF_COMMAND_BASE+2
#define ID_APP_LEGAL                    EAF_COMMAND_BASE+3
#define ID_UNITS_SI                     EAF_COMMAND_BASE+4
#define ID_UNITS_US                     EAF_COMMAND_BASE+5
#define ID_EDIT_UNITS                   EAF_COMMAND_BASE+6
#define ID_TIPOFTHEDAY                  EAF_COMMAND_BASE+7
#define ID_MANAGE_APP_PLUGINS           EAF_COMMAND_BASE+8
