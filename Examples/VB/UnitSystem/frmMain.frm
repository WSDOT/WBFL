VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "UnitSystemTest"
   ClientHeight    =   2556
   ClientLeft      =   48
   ClientTop       =   276
   ClientWidth     =   3744
   LinkTopic       =   "Form1"
   ScaleHeight     =   2556
   ScaleWidth      =   3744
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdUnits 
      Caption         =   "Units..."
      Height          =   372
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   972
   End
   Begin VB.CommandButton cmdInput 
      Caption         =   "Input..."
      Height          =   372
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Sample Program that demonstrates how to use the unit system, unit mode controller, and display units manager."
      Height          =   1332
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   3492
   End
   Begin VB.Label lblPs 
      AutoSize        =   -1  'True
      Caption         =   "Label1"
      Height          =   192
      Left            =   2400
      TabIndex        =   3
      Top             =   600
      Width           =   492
   End
   Begin VB.Label lblPc 
      AutoSize        =   -1  'True
      Caption         =   "Label1"
      Height          =   192
      Left            =   2400
      TabIndex        =   2
      Top             =   120
      Width           =   492
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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

'This form will handle display events. Ideally, the form would
'use an ActiveX control like a graph engine. The control would
'support display unit events
Private WithEvents unitSystem As WBFLUnitServer.unitSystem
Attribute unitSystem.VB_VarHelpID = -1

'Create two objects that support unit server
Public concrete As New concrete 'Uses SI units internally
Public Tube As New SteelTube 'Uses US units internally

Public TubeName As String ' Name of tube
Public Asteel As Double 'Area of Tube
Public Aconc As Double 'Area of Concrete
Public Force As Double 'Axial load
   
Private Pc As Double 'Force in concrete
Private Ps As Double 'Force in steel tube

Private Sub cmdInput_Click()
   Load frmInput
   
   'Provide the form with the applications unit system
   'Not necessary if the unit system is made global
   Dim sus As WBFLUnitServer.ISupportUnitSystem
   Set sus = frmInput
   Set sus.unitSystem = unitSystem
   
   frmInput.Show vbModal, frmMain
   
   UpdateResults 'Recompute results
   UpdateDisplay 'Update the display
End Sub

Private Sub cmdUnits_Click()
   'Tell the Unit Mode Controller to display the unit selection dialog
   'If units are changed, and event is fired. Since the unitSystem
   'variable is defined with events, we will receive notification
   unitSystem.UnitModeController.ShowSelectionDialog
End Sub

Private Sub Form_Load()
   'Create a unit system for this application
   Set unitSystem = New WBFLUnitServer.unitSystem
   
   'Initialize base units
   'These are the units that we want to use
   unitSystem.unitServer.SetBaseUnits "kg", "m", "sec", "C", "rad"
   
   'Associated the unit system with the concrete object
   'This enables us to communicate with the concrete object using
   'base units, regardless of the units the concrete object uses
   'internally
   Dim sus As WBFLUnitServer.ISupportUnitServer
   Set sus = concrete
   Set sus.unitServer = unitSystem.unitServer
   
   'Associated the unit system with the SteelTube object
   'This enables us to communicate with the SteelTube object using
   'base units, regardless of the units the SteelTube object uses
   'internally
   Set sus = Tube
   Set sus.unitServer = unitSystem.unitServer
   
   'Configure the display unit manager
   Dim formatter As New WBFLUnitServer.DisplayUnitFormatter
   formatter.FormatSpecifiers 0, 3, tjRight, nftFixed, 0.0001
   
   Dim group As WBFLUnitServer.IDisplayUnitGroup
   Set group = unitSystem.DisplayUnitMgr.Add("Stress", "Pressure")
   group.Add "MPa", unitsSI, formatter, True
   group.Add "ksi", unitsUS, formatter, True
   
   Set group = unitSystem.DisplayUnitMgr.Add("Density", "Density")
   group.Add "kg/m^3", unitsSI, formatter, True
   group.Add "lb/ft^3", unitsUS, formatter, True
   
   Set group = unitSystem.DisplayUnitMgr.Add("Area", "Length2")
   group.Add "mm^2", unitsSI, formatter, True
   group.Add "in^2", unitsUS, formatter, True
   
   Set group = unitSystem.DisplayUnitMgr.Add("Force", "Force")
   group.Add "kN", unitsSI, formatter, True
   group.Add "kip", unitsUS, formatter, True
   
   'Initiaze some data
   concrete.Density = unitSystem.unitServer.UnitConvert.ConvertToBaseUnits(2560, "kg/m^3")
   concrete.fc = unitSystem.unitServer.UnitConvert.ConvertToBaseUnits(48, "MPa")
   
   TubeName = "16x16"
   
   Force = unitSystem.unitServer.UnitConvert.ConvertToBaseUnits(1000, "kN")
   
   UpdateDisplay
End Sub

Private Sub UpdateResults()
'Compute the force in the steel tube and the concrete
   Pc = Force / (1 + (Asteel * Tube.E) / (Aconc * concrete.E))
   Ps = Force - Pc
   
End Sub

Private Sub UpdateDisplay()
   'Update the display
   lblPc = "Pc = " + unitSystem.DisplayUnitMgr.Format(Pc, "Force", True)
   lblPs = "Ps = " + unitSystem.DisplayUnitMgr.Format(Ps, "Force", True)
End Sub

Private Sub unitSystem_OnUpdateDisplay()
   'An event occured that requires the display to be updated
   'For this example, the unit mode was changed.
   UpdateDisplay
End Sub
