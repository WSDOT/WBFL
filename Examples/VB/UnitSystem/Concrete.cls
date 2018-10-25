VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Concrete"
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

'Very simple product model of concrete
'Internal units are SI

Private mFc As Double 'local copy
Private mDensity As Double 'local copy
Private unitServer As WBFLUnitServer.unitServer

Implements WBFLUnitServer.ISupportUnitServer

Public Property Get E() As Double
   Dim tmpDensity As Double
   Dim tmpFc As Double
   Dim tmpE As Double
   
   'Convert data from "Base Units" to SI units
   tmpDensity = unitServer.UnitConvert.ConvertFromBaseUnits(mDensity, "kg/m^3")
   tmpFc = unitServer.UnitConvert.ConvertFromBaseUnits(mFc, "MPa")
   
   'Compute modulus of elasticity (result in MPa)
   tmpE = 0.043 * tmpDensity ^ 1.5 * Sqr(tmpFc)
   
   'Convert result to Base Units
    E = unitServer.UnitConvert.ConvertToBaseUnits(tmpE, "MPa")
End Property

Public Property Let Density(ByVal vData As Double)
    mDensity = vData
End Property

Public Property Get Density() As Double
    Density = mDensity
End Property

Public Property Let fc(ByVal vData As Double)
    mFc = vData
End Property

Public Property Get fc() As Double
    fc = mFc
End Property

Private Property Set ISupportUnitServer_UnitServer(ByVal RHS As WBFLUnitServer.IUnitServer)
   Set unitServer = RHS
End Property

Private Property Get ISupportUnitServer_UnitServer() As WBFLUnitServer.IUnitServer
   Set ISupportUnitServer_UnitServer = unitServer
End Property
