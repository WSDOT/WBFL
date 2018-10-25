VERSION 5.00
Begin VB.Form frmInput 
   Caption         =   "Input"
   ClientHeight    =   2556
   ClientLeft      =   48
   ClientTop       =   276
   ClientWidth     =   3744
   LinkTopic       =   "Form1"
   ScaleHeight     =   2556
   ScaleWidth      =   3744
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtForce 
      Alignment       =   1  'Right Justify
      Height          =   372
      Left            =   720
      TabIndex        =   9
      Text            =   "0"
      Top             =   1560
      Width           =   972
   End
   Begin VB.ComboBox cboTubes 
      Height          =   288
      ItemData        =   "frmInput.frx":0000
      Left            =   120
      List            =   "frmInput.frx":0002
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   1200
      Width           =   1572
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   372
      Left            =   1440
      TabIndex        =   6
      Top             =   2040
      Width           =   972
   End
   Begin VB.TextBox txtDensity 
      Alignment       =   1  'Right Justify
      Height          =   372
      Left            =   720
      TabIndex        =   4
      Text            =   "155"
      Top             =   600
      Width           =   972
   End
   Begin VB.TextBox txtFc 
      Alignment       =   1  'Right Justify
      Height          =   372
      Left            =   720
      TabIndex        =   1
      Text            =   "4"
      Top             =   120
      Width           =   972
   End
   Begin VB.Label lblForce 
      AutoSize        =   -1  'True
      Caption         =   "Label4"
      Height          =   192
      Left            =   1800
      TabIndex        =   10
      Top             =   1560
      Width           =   492
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Force"
      Height          =   192
      Left            =   120
      TabIndex        =   8
      Top             =   1680
      Width           =   420
   End
   Begin VB.Label lblDensity 
      AutoSize        =   -1  'True
      Caption         =   "Label3"
      Height          =   192
      Left            =   1800
      TabIndex        =   5
      Top             =   720
      Width           =   492
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Density"
      Height          =   192
      Left            =   120
      TabIndex        =   3
      Top             =   720
      Width           =   540
   End
   Begin VB.Label lblFc 
      AutoSize        =   -1  'True
      Caption         =   "Label2"
      Height          =   192
      Left            =   1800
      TabIndex        =   2
      Top             =   240
      Width           =   492
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "F'c"
      Height          =   192
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   216
   End
End
Attribute VB_Name = "frmInput"
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

Implements WBFLUnitServer.ISupportUnitSystem
Private unitSystem As WBFLUnitServer.unitSystem

Private Sub cmdOK_Click()
   'Extract data from this form and give it to the main form
   frmMain.concrete.Density = unitSystem.DisplayUnitMgr.ConvertFromDisplayUnits(txtDensity, "Density")
   frmMain.concrete.fc = unitSystem.DisplayUnitMgr.ConvertFromDisplayUnits(txtFc, "Stress")
   
   frmMain.Aconc = frmMain.Tube.VoidArea(cboTubes.Text)
   frmMain.Asteel = frmMain.Tube.Area(cboTubes.Text)
   
   frmMain.Force = unitSystem.DisplayUnitMgr.ConvertFromDisplayUnits(txtForce, "Force")
   Unload Me
End Sub

Private Sub Form_Load()
   cboTubes.AddItem "16x16"
   cboTubes.AddItem "14x14"
   
   cboTubes.Text = frmMain.TubeName
End Sub

Private Property Set ISupportUnitSystem_UnitSystem(ByVal RHS As WBFLUnitServer.IUnitSystem)
   Set unitSystem = RHS
   
   'Get the tag of the default display unit for the current unit mode
   'Assign the tag to the label that is to the right of the text box
   lblFc.Caption = unitSystem.DisplayUnitMgr.Tag("Stress")
   lblDensity.Caption = unitSystem.DisplayUnitMgr.Tag("Density")
   lblForce.Caption = unitSystem.DisplayUnitMgr.Tag("Force")
   
   'Format the current values for display and assigned to the text boxes
   txtDensity = unitSystem.DisplayUnitMgr.Format(frmMain.concrete.Density, "Density", False)
   txtFc = unitSystem.DisplayUnitMgr.Format(frmMain.concrete.fc, "Stress", False)
   txtForce = unitSystem.DisplayUnitMgr.Format(frmMain.Force, "Force", False)
End Property

Private Property Get ISupportUnitSystem_UnitSystem() As WBFLUnitServer.IUnitSystem
   Set ISupportUnitSystem_UnitSystem = unitSystem
End Property
