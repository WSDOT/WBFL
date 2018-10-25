VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SteelTube"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'///////////////////////////////////////////////////////////////////////
'// WBFL Unit Server
'// Copyright (C) 2000, Washington State Department of Transportation
'//                     Bridge and Structures Office
'//
'// This software was developed as part of the Alternate Route Project
'//
'// This program is free software; you can redistribute it and/or modify
'// it under the terms of the Alternate Route Open Source License as
'// published by the Washington State Department of Transportation,
'// Bridge and Structures Office.
'//
'// This program is distributed in the hope that it will be useful,
'// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
'// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
'// PURPOSE.  See the Alternate Route Open Source License for more details.
'//
'// You should have received a copy of the Alternate Open Source License
'// along with this program; if not, write to the Washington State
'// Department of Transportation, Bridge and Structures Office,
'// 4500 3rd Ave SE, P.O. Box 47340, Olympia, WA 98503, USA or e-mail
'// Bridge_Support@wsdot.wa.gov
'///////////////////////////////////////////////////////////////////////

'Very simple product model of structual steel tubing
'Internal units for this object are in US units.

Dim unitServer As WBFLUnitServer.unitServer
Implements WBFLUnitServer.ISupportUnitServer

Public Property Get E() As Double
    E = unitServer.UnitConvert.ConvertToBaseUnits(29000#, "ksi")
End Property

Public Property Get VoidArea(name As String) As Double
   Dim tmpArea As Double
   
   Select Case name
     Case "16x16"
        tmpArea = 25.2 'in^2
     Case "14x14"
        tmpArea = 20.6 'in^2
   End Select
   
   'Convert the data to base units before returning. Who ever is
   'using this object is expecting data is base units
   VoidArea = unitServer.UnitConvert.ConvertToBaseUnits(tmpArea, "in^2")
End Property


Public Property Get Area(name As String) As Double
   Dim tmpArea As Double
   
   Select Case name
     Case "16x16"
        tmpArea = 30.4 'in^2
     Case "14x14"
        tmpArea = 26.4 'in^2
   End Select
   
   Area = unitServer.UnitConvert.ConvertToBaseUnits(tmpArea, "in^2")
End Property

Private Property Set ISupportUnitServer_UnitServer(ByVal RHS As WBFLUnitServer.IUnitServer)
   Set unitServer = RHS
End Property

Private Property Get ISupportUnitServer_UnitServer() As WBFLUnitServer.IUnitServer
   Set ISupportUnitServer_UnitServer = unitServer
End Property
