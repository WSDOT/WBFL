///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"{
#endif 

//// {011408A7-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(LIBID_WBFLDManip, 
//0x11408a7, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408A9-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iCenterOnPointTask, 
0x11408a9, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {F8C24AC0-865C-4002-8ADF-8D1231917ADB}
DEFINE_GUID(IID_iConnector, 
0xf8c24ac0, 0x865c, 0x4002, 0x8a, 0xdf, 0x8d, 0x12, 0x31, 0x91, 0x7a, 0xdb);

// {011408AE-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iConnectable, 
0x11408ae, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408AD-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iSocketFactory, 
0x11408ad, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408AC-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iSocket, 
0x11408ac, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408AB-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iPlugEvents, 
0x11408ab, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408AA-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iPlug, 
0x11408aa, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408CA-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iCoordinateMap, 
0x11408ca, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B0-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDimensionLine, 
0x11408b0, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408A4-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDisplayList, 
0x11408a4, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {C151B87B-5A17-4be7-9398-1A7933273B1C}
DEFINE_GUID(IID_iDisplayListEvents, 
0xc151b87b, 0x5a17, 0x4be7, 0x93, 0x98, 0x1a, 0x79, 0x33, 0x27, 0x3b, 0x1c);

// {011408A5-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDisplayMgr, 
0x11408a5, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {3567D433-8CCC-4f50-B582-5F394F6FA31E}
DEFINE_GUID(IID_iDisplayObject, 
0x3567d433, 0x8ccc, 0x4f50, 0xb5, 0x82, 0x5f, 0x39, 0x4f, 0x6f, 0xa3, 0x1e);

// {63D5B3D9-EC86-403f-A512-B0EC4D773CB2}
DEFINE_GUID(IID_iDisplayObjectEvents, 
0x63d5b3d9, 0xec86, 0x403f, 0xa5, 0x12, 0xb0, 0xec, 0x4d, 0x77, 0x3c, 0xb2);

// {011408B1-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDisplayObjectFactory, 
0x11408b1, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B2-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDragDataSource, 
0x11408b2, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B3-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDragDataSink, 
0x11408b3, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B4-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDragData, 
0x11408b4, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B5-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDraggable, 
0x11408b5, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {08B7FA73-309C-44fe-A16B-99ABED30804C}
DEFINE_GUID(IID_iDrawPointStrategy, 
0x8b7fa73, 0x309c, 0x44fe, 0xa1, 0x6b, 0x99, 0xab, 0xed, 0x30, 0x80, 0x4c);

// {011408B6-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iDropSite, 
0x11408b6, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {3F3B59C3-833B-42cc-B8EA-D0BD5B9C4939}
DEFINE_GUID(IID_iEditableTextBlock, 
0x3f3b59c3, 0x833b, 0x42cc, 0xb8, 0xea, 0xd0, 0xbd, 0x5b, 0x9c, 0x49, 0x39);

// {4CB52485-1DD0-4c11-A02F-7F6058F11FBA}
DEFINE_GUID(IID_iEditableUnitValueTextBlock, 
0x4cb52485, 0x1dd0, 0x4c11, 0xa0, 0x2f, 0x7f, 0x60, 0x58, 0xf1, 0x1f, 0xba);

// {011408B8-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iForeignDragDropTask, 
0x11408b8, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B9-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iInplaceEditable, 
0x11408b9, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408B7-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iInplaceEditTask, 
0x11408b7, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BA-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iLineDisplayObject, 
0x11408ba, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BA-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iLocalDragDropTask, 
0x11408ba, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BC-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iMapping, 
0x11408bc, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BD-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iPointDisplayObject, 
0x11408bd, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BE-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iRectSelectTask, 
0x11408be, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408BF-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iTask, 
0x11408bf, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408C0-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iTaskFactory, 
0x11408c0, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408C1-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iTextBlock, 
0x11408c1, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {164EB164-2ADC-4C9D-BECE-A8F8DFB0B713}
DEFINE_GUID(IID_iAnchoredTextBlock,
0x164eb164, 0x2adc, 0x4c9d, 0xbe, 0xce, 0xa8, 0xf8, 0xdf, 0xb0, 0xb7, 0x13);

// {011408C2-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iTool, 
0x11408c2, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {011408C3-F865-11d4-8B9C-006097C68A9C}
DEFINE_GUID(IID_iZoomRectTask, 
0x11408c3, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);

// {777A934D-53F9-491b-8245-5C3F39B532FF}
DEFINE_GUID(IID_iGravityWellStrategy, 
0x777a934d, 0x53f9, 0x491b, 0x82, 0x45, 0x5c, 0x3f, 0x39, 0xb5, 0x32, 0xff);

// {CE829923-BC12-4dc4-BE46-FEB1850F2C7D}
DEFINE_GUID(IID_iCompositeDisplayObject, 
0xce829923, 0xbc12, 0x4dc4, 0xbe, 0x46, 0xfe, 0xb1, 0x85, 0xf, 0x2c, 0x7d);

// {971C39FA-D0F1-4825-AD21-4B5B2A85A708}
DEFINE_GUID(IID_iDrawLineStrategy, 
0x971c39fa, 0xd0f1, 0x4825, 0xad, 0x21, 0x4b, 0x5b, 0x2a, 0x85, 0xa7, 0x8);

// {3AD38EA6-AD00-4db5-95A2-4A6F433223B0}
DEFINE_GUID(IID_iSimpleDrawLineStrategy, 
0x3ad38ea6, 0xad00, 0x4db5, 0x95, 0xa2, 0x4a, 0x6f, 0x43, 0x32, 0x23, 0xb0);

// {53F1094A-3B6A-483d-B5CE-5D3084B9EDA1}
DEFINE_GUID(IID_iSimpleDrawDashedLineStrategy, 
0x53f1094a, 0x3b6a, 0x483d, 0xb5, 0xce, 0x5d, 0x30, 0x84, 0xb9, 0xed, 0xa1);

// {4AACC54C-81AD-46e9-9B09-E07AAC29D5AA}
DEFINE_GUID(IID_iRectangleDrawLineStrategy, 
0x4aacc54c, 0x81ad, 0x46e9, 0x9b, 0x9, 0xe0, 0x7a, 0xac, 0x29, 0xd5, 0xaa);

// {F76D3357-1955-4ec1-9686-D0C4409E2EE5}
DEFINE_GUID(IID_iSimpleDrawPointStrategy, 
0xf76d3357, 0x1955, 0x4ec1, 0x96, 0x86, 0xd0, 0xc4, 0x40, 0x9e, 0x2e, 0xe5);

// {CBE1C9E6-D5C0-4bf5-BFC1-AAAA8EA975BE}
DEFINE_GUID(IID_iDisplayMgrEvents, 
0xcbe1c9e6, 0xd5c0, 0x4bf5, 0xbf, 0xc1, 0xaa, 0xaa, 0x8e, 0xa9, 0x75, 0xbe);

// {27CCBDD1-9B6C-493b-931F-C3FF67A09ABB}
DEFINE_GUID(IID_iToolIcon, 
0x27ccbdd1, 0x9b6c, 0x493b, 0x93, 0x1f, 0xc3, 0xff, 0x67, 0xa0, 0x9a, 0xbb);

// {A398765E-7831-4d5b-8361-ED63DBD6E93A}
DEFINE_GUID(IID_iShapeDrawStrategy, 
0xa398765e, 0x7831, 0x4d5b, 0x83, 0x61, 0xed, 0x63, 0xdb, 0xd6, 0xe9, 0x3a);

// {8B8DB485-E3F8-4f7b-9723-DE5092789E6C}
DEFINE_GUID(IID_iTargetDrawStrategy, 
0x8b8db485, 0xe3f8, 0x4f7b, 0x97, 0x23, 0xde, 0x50, 0x92, 0x78, 0x9e, 0x6c);

// {76D6D4CC-E0AF-4893-9CA8-53ECE8422802}
DEFINE_GUID(IID_iCompoundDrawLineStrategy, 
0x76d6d4cc, 0xe0af, 0x4893, 0x9c, 0xa8, 0x53, 0xec, 0xe8, 0x42, 0x28, 0x2);

// {F8834E1B-2359-42CA-9B91-2C67E8C4DF47}
DEFINE_GUID(IID_iCompoundDrawPointStrategy,
0xf8834e1b, 0x2359, 0x42ca, 0x9b, 0x91, 0x2c, 0x67, 0xe8, 0xc4, 0xdf, 0x47);

// {E9C6C54F-77CF-4ee4-9465-4821BBD0CEF3}
DEFINE_GUID(IID_iExtRectangleDrawLineStrategy, 
0xe9c6c54f, 0x77cf, 0x4ee4, 0x94, 0x65, 0x48, 0x21, 0xbb, 0xd0, 0xce, 0xf3);

// {66542767-5F40-4124-9CCF-7A5456E3328C}
DEFINE_GUID(IID_iViewTitle, 
0x66542767, 0x5f40, 0x4124, 0x9c, 0xcf, 0x7a, 0x54, 0x56, 0xe3, 0x32, 0x8c);

// {1CDB522C-E3B4-4664-8E67-BB56605BB377}
DEFINE_GUID(IID_iShapeGravityWellStrategy, 
0x1cdb522c, 0xe3b4, 0x4664, 0x8e, 0x67, 0xbb, 0x56, 0x60, 0x5b, 0xb3, 0x77);

// {5BF66BDA-4EC4-4857-9534-054257BEB172}
DEFINE_GUID(IID_iNorthArrow, 
0x5bf66bda, 0x4ec4, 0x4857, 0x95, 0x34, 0x5, 0x42, 0x57, 0xbe, 0xb1, 0x72);

// {5E2EAAA6-5171-49E6-B0E8-F65923C9CA45}
DEFINE_GUID(IID_iShapeDrawStrategy2,
   0x5e2eaaa6, 0x5171, 0x49e6, 0xb0, 0xe8, 0xf6, 0x59, 0x23, 0xc9, 0xca, 0x45);

////////////////////////////////////////////////////////////////////

//// {A2703706-F85B-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_DisplayList, 
//0xa2703706, 0xf85b, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408A6-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_DisplayMgr, 
//0x11408a6, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408C4-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_InplaceEditTask, 
//0x11408c4, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408C5-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_RectSelectTask, 
//0x11408c5, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408C6-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_LocalDragDropTask, 
//0x11408c6, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408CB-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_ForeignDragDropTask, 
//0x11408cb, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408C7-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_DragDataSource, 
//0x11408c7, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408C8-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_DragDataSink, 
//0x11408c8, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408CC-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_CenterOnPointTask, 
//0x11408cc, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408CD-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_ZoomRectTask, 
//0x11408cd, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408CE-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_TaskFactory, 
//0x11408ce, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408CF-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_DisplayObjectFactory, 
//0x11408cf, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408D0-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_Mapping, 
//0x11408d0, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408D1-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_Plug, 
//0x11408d1, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408D2-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_Socket, 
//0x11408d2, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408D3-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_SocketFactory, 
//0x11408d3, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {011408D4-F865-11d4-8B9C-006097C68A9C}
//DEFINE_GUID(CLSID_PointDisplayObject, 
//0x11408d4, 0xf865, 0x11d4, 0x8b, 0x9c, 0x0, 0x60, 0x97, 0xc6, 0x8a, 0x9c);
//
//// {38D4D890-DF6E-404c-9374-E9375BDE0DF0}
//DEFINE_GUID(CLSID_SimpleDrawPointStrategy, 
//0x38d4d890, 0xdf6e, 0x404c, 0x93, 0x74, 0xe9, 0x37, 0x5b, 0xde, 0xd, 0xf0);
//
//// {8EB55FED-8056-4d6b-9F89-09FC59C84618}
//DEFINE_GUID(CLSID_TextBlock, 
//0x8eb55fed, 0x8056, 0x4d6b, 0x9f, 0x89, 0x9, 0xfc, 0x59, 0xc8, 0x46, 0x18);
//
//// {D66088C8-7E4A-49d7-A306-28BF10B53A88}
//DEFINE_GUID(CLSID_EditableTextBlock, 
//0xd66088c8, 0x7e4a, 0x49d7, 0xa3, 0x6, 0x28, 0xbf, 0x10, 0xb5, 0x3a, 0x88);
//
//// {C24E4B67-AAC1-4da4-A3F2-373C558333D6}
//DEFINE_GUID(CLSID_EditableUnitValueTextBlock, 
//0xc24e4b67, 0xaac1, 0x4da4, 0xa3, 0xf2, 0x37, 0x3c, 0x55, 0x83, 0x33, 0xd6);
//
//// {531F5C30-FFC3-4a22-ADE5-D640C8CBE284}
//DEFINE_GUID(CLSID_LineDisplayObject, 
//0x531f5c30, 0xffc3, 0x4a22, 0xad, 0xe5, 0xd6, 0x40, 0xc8, 0xcb, 0xe2, 0x84);
//
//// {9B7A1DE8-C7DB-4512-A94F-D6FF62505B12}
//DEFINE_GUID(CLSID_DimensionLineDisplayObject, 
//0x9b7a1de8, 0xc7db, 0x4512, 0xa9, 0x4f, 0xd6, 0xff, 0x62, 0x50, 0x5b, 0x12);
//
//// {44D1610A-A8FF-41b0-B94F-24B0A59C629A}
//DEFINE_GUID(CLSID_Tool, 
//0x44d1610a, 0xa8ff, 0x41b0, 0xb9, 0x4f, 0x24, 0xb0, 0xa5, 0x9c, 0x62, 0x9a);
//
//// {A1C5BEE7-6799-462b-B72A-F4BD47E94341}
//DEFINE_GUID(CLSID_CompositeDisplayObject, 
//0xa1c5bee7, 0x6799, 0x462b, 0xb7, 0x2a, 0xf4, 0xbd, 0x47, 0xe9, 0x43, 0x41);
//
//// {2F67AF5C-6D47-4dea-9D1F-D6F396E6831C}
//DEFINE_GUID(CLSID_SimpleDrawLineStrategy, 
//0x2f67af5c, 0x6d47, 0x4dea, 0x9d, 0x1f, 0xd6, 0xf3, 0x96, 0xe6, 0x83, 0x1c);
//
//// {682DF075-020C-45b1-BBF4-11C159644BA5}
//DEFINE_GUID(CLSID_RectangleDrawLineStrategy, 
//0x682df075, 0x20c, 0x45b1, 0xbb, 0xf4, 0x11, 0xc1, 0x59, 0x64, 0x4b, 0xa5);
//
//// {4D0A0066-E3FE-41a7-8AE7-8E8A77851EA8}
//DEFINE_GUID(CLSID_ShapeDrawStrategy, 
//0x4d0a0066, 0xe3fe, 0x41a7, 0x8a, 0xe7, 0x8e, 0x8a, 0x77, 0x85, 0x1e, 0xa8);
//
//// {E9E341BF-F158-46ae-8DB2-3E709E02AD8A}
//DEFINE_GUID(CLSID_TargetDrawStrategy, 
//0xe9e341bf, 0xf158, 0x46ae, 0x8d, 0xb2, 0x3e, 0x70, 0x9e, 0x2, 0xad, 0x8a);
//
//// {326E7437-FC61-41ed-AA42-6EF8CE2583FF}
//DEFINE_GUID(CLSID_CompoundDrawLineStrategy, 
//0x326e7437, 0xfc61, 0x41ed, 0xaa, 0x42, 0x6e, 0xf8, 0xce, 0x25, 0x83, 0xff);
//
//// {383B8C08-A236-44c7-BEE1-E41ADD831AC7}
//DEFINE_GUID(CLSID_ExtRectangleDrawLineStrategy, 
//0x383b8c08, 0xa236, 0x44c7, 0xbe, 0xe1, 0xe4, 0x1a, 0xdd, 0x83, 0x1a, 0xc7);
//
//// {6DBAF4E1-4291-4112-9687-9C8F9E0425B4}
//DEFINE_GUID(CLSID_ViewTitle, 
//0x6dbaf4e1, 0x4291, 0x4112, 0x96, 0x87, 0x9c, 0x8f, 0x9e, 0x4, 0x25, 0xb4);
//
//// {DC3F42E8-7A6A-48be-8E0C-5D86E9D5EEBE}
//DEFINE_GUID(CLSID_NorthArrow, 
//0xdc3f42e8, 0x7a6a, 0x48be, 0x8e, 0xc, 0x5d, 0x86, 0xe9, 0xd5, 0xee, 0xbe);
//
//// {4F2C8970-5720-437b-B6CA-EA9092311244}
//DEFINE_GUID(CLSID_ShapeGravityWellStrategy, 
//0x4f2c8970, 0x5720, 0x437b, 0xb6, 0xca, 0xea, 0x90, 0x92, 0x31, 0x12, 0x44);

// these delclarations allow things like uuidof and CComPtr::Cocreateinstance to work
struct __declspec(uuid("{011408A9-F865-11d4-8B9C-006097C68A9C}")) iCenterOnPointTask;
struct __declspec(uuid("{F8C24AC0-865C-4002-8ADF-8D1231917ADB}")) iConnector;
struct __declspec(uuid("{011408AE-F865-11d4-8B9C-006097C68A9C}")) iConnectable;
struct __declspec(uuid("{011408AD-F865-11d4-8B9C-006097C68A9C}")) iSocketFactory;
struct __declspec(uuid("{011408AC-F865-11d4-8B9C-006097C68A9C}")) iSocket;
struct __declspec(uuid("{011408AB-F865-11d4-8B9C-006097C68A9C}")) iPlugEvents;
struct __declspec(uuid("{011408AA-F865-11d4-8B9C-006097C68A9C}")) iPlug;
struct __declspec(uuid("{011408CA-F865-11d4-8B9C-006097C68A9C}")) iCoordinateMap;
struct __declspec(uuid("{011408B0-F865-11d4-8B9C-006097C68A9C}")) iDimensionLine;
struct __declspec(uuid("{011408A4-F865-11d4-8B9C-006097C68A9C}")) iDisplayList;
struct __declspec(uuid("{C151B87B-5A17-4be7-9398-1A7933273B1C}")) iDisplayListEvents;
struct __declspec(uuid("{011408A5-F865-11d4-8B9C-006097C68A9C}")) iDisplayMgr;
struct __declspec(uuid("{3567D433-8CCC-4f50-B582-5F394F6FA31E}")) iDisplayObject;
struct __declspec(uuid("{63D5B3D9-EC86-403f-A512-B0EC4D773CB2}")) iDisplayObjectEvents;
struct __declspec(uuid("{011408B1-F865-11d4-8B9C-006097C68A9C}")) iDisplayObjectFactory;
struct __declspec(uuid("{011408B2-F865-11d4-8B9C-006097C68A9C}")) iDragDataSource;
struct __declspec(uuid("{011408B3-F865-11d4-8B9C-006097C68A9C}")) iDragDataSink;
struct __declspec(uuid("{011408B4-F865-11d4-8B9C-006097C68A9C}")) iDragData;
struct __declspec(uuid("{011408B5-F865-11d4-8B9C-006097C68A9C}")) iDraggable;
struct __declspec(uuid("{08B7FA73-309C-44fe-A16B-99ABED30804C}")) iDrawPointStrategy;
struct __declspec(uuid("{011408B6-F865-11d4-8B9C-006097C68A9C}")) iDropSite;
struct __declspec(uuid("{4CB52485-1DD0-4c11-A02F-7F6058F11FBA}")) iEditableUnitValueTextBlock;
struct __declspec(uuid("{234FAD14-18FD-423b-8DCB-5025293A6328}")) iEditableTextBlock;
struct __declspec(uuid("{011408B8-F865-11d4-8B9C-006097C68A9C}")) iForeignDragDropTask;
struct __declspec(uuid("{011408B9-F865-11d4-8B9C-006097C68A9C}")) iInplaceEditable;
struct __declspec(uuid("{011408B7-F865-11d4-8B9C-006097C68A9C}")) iInplaceEditTask;
struct __declspec(uuid("{011408BA-F865-11d4-8B9C-006097C68A9C}")) iLineDisplayObject;
struct __declspec(uuid("{011408BA-F865-11d4-8B9C-006097C68A9C}")) iLocalDragDropTask;
struct __declspec(uuid("{011408BC-F865-11d4-8B9C-006097C68A9C}")) iMapping;
struct __declspec(uuid("{011408BD-F865-11d4-8B9C-006097C68A9C}")) iPointDisplayObject;
struct __declspec(uuid("{011408BE-F865-11d4-8B9C-006097C68A9C}")) iRectSelectTask;
struct __declspec(uuid("{011408BF-F865-11d4-8B9C-006097C68A9C}")) iTask;
struct __declspec(uuid("{011408C0-F865-11d4-8B9C-006097C68A9C}")) iTaskFactory;
struct __declspec(uuid("{011408C1-F865-11d4-8B9C-006097C68A9C}")) iTextBlock;
struct __declspec(uuid("{164EB164-2ADC-4C9D-BECE-A8F8DFB0B713}")) iAnchoredTextBlock;
struct __declspec(uuid("{011408C2-F865-11d4-8B9C-006097C68A9C}")) iTool;
struct __declspec(uuid("{011408C3-F865-11d4-8B9C-006097C68A9C}")) iZoomRectTask;
struct __declspec(uuid("{777A934D-53F9-491b-8245-5C3F39B532FF}")) iGravityWellStrategy;
struct __declspec(uuid("{CE829923-BC12-4dc4-BE46-FEB1850F2C7D}")) iCompositeDisplayObject;
struct __declspec(uuid("{971C39FA-D0F1-4825-AD21-4B5B2A85A708}")) iDrawLineStrategy;
struct __declspec(uuid("{3AD38EA6-AD00-4db5-95A2-4A6F433223B0}")) iSimpleDrawLineStrategy;
struct __declspec(uuid("{4AACC54C-81AD-46e9-9B09-E07AAC29D5AA}")) iRectangleDrawLineStrategy;
struct __declspec(uuid("{F76D3357-1955-4ec1-9686-D0C4409E2EE5}")) iSimpleDrawPointStrategy;
struct __declspec(uuid("{27CCBDD1-9B6C-493b-931F-C3FF67A09ABB}")) iToolIcon;
struct __declspec(uuid("{CBE1C9E6-D5C0-4bf5-BFC1-AAAA8EA975BE}")) iDisplayMgrEvents;
struct __declspec(uuid("{A398765E-7831-4d5b-8361-ED63DBD6E93A}")) iShapeDrawStrategy;
struct __declspec(uuid("{8B8DB485-E3F8-4f7b-9723-DE5092789E6C}")) iTargetDrawStrategy;
struct __declspec(uuid("{76D6D4CC-E0AF-4893-9CA8-53ECE8422802}")) iCompoundDrawLineStrategy;
struct __declspec(uuid("{F8834E1B-2359-42CA-9B91-2C67E8C4DF47}")) iCompoundDrawPointStrategy;
struct __declspec(uuid("{E9C6C54F-77CF-4ee4-9465-4821BBD0CEF3}")) iExtRectangleDrawLineStrategy;
struct __declspec(uuid("{66542767-5F40-4124-9CCF-7A5456E3328C}")) iViewTitle;
struct __declspec(uuid("{1CDB522C-E3B4-4664-8E67-BB56605BB377}")) iShapeGravityWellStrategy;
struct __declspec(uuid("{5BF66BDA-4EC4-4857-9534-054257BEB172}")) iNorthArrow;
struct __declspec(uuid("{5E2EAAA6-5171-49E6-B0E8-F65923C9CA45}")) iShapeDrawStrategy2;

#ifdef __cplusplus
}
#endif
