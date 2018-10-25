VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Convert"
   ClientHeight    =   1320
   ClientLeft      =   150
   ClientTop       =   720
   ClientWidth     =   4680
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1320
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstUnitType 
      Height          =   840
      Left            =   120
      TabIndex        =   1
      ToolTipText     =   "Select a unit type"
      Top             =   360
      Width           =   1572
   End
   Begin VB.TextBox txtConvertFrom 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   1800
      TabIndex        =   2
      Text            =   "txtConvertFrom"
      ToolTipText     =   "Enter the number that you want to convert"
      Top             =   360
      Width           =   1812
   End
   Begin VB.ComboBox cboTo 
      Height          =   315
      Left            =   3600
      Style           =   2  'Dropdown List
      TabIndex        =   6
      ToolTipText     =   "Select a unit to convert to"
      Top             =   960
      Width           =   975
   End
   Begin VB.ComboBox cboFrom 
      Height          =   315
      ItemData        =   "frmMain.frx":0442
      Left            =   3600
      List            =   "frmMain.frx":0444
      Style           =   2  'Dropdown List
      TabIndex        =   3
      ToolTipText     =   "Select a unit to convert from"
      Top             =   360
      Width           =   975
   End
   Begin VB.Label lblUnitType 
      AutoSize        =   -1  'True
      Caption         =   "Select Unit Type"
      Height          =   192
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1188
   End
   Begin VB.Label lblConvertTo 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Label1"
      Height          =   288
      Left            =   1800
      TabIndex        =   5
      ToolTipText     =   "This is the converted value"
      Top             =   960
      Width           =   1812
   End
   Begin VB.Label lblText 
      Caption         =   "is equal to"
      Height          =   252
      Left            =   2640
      TabIndex        =   4
      Top             =   720
      Width           =   852
   End
   Begin VB.Menu mnuConfigure 
      Caption         =   "&Configure"
      Begin VB.Menu mnuOptions 
         Caption         =   "&Options..."
      End
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

Option Explicit
Public Precision As Double
Private unitSvr As New WBFLUnitServer.UnitServer

Sub ConvertNow()
   Dim dblFrom As Double
   Dim strFrom As String
   Dim dblTo As Double
   Dim strTo As String

   dblFrom = txtConvertFrom.Text
   strFrom = cboFrom.Text
   strTo = cboTo.Text

   If (strFrom = "" Or strTo = "") Then
      Exit Sub
   End If
   
   Dim conv As IUnitConvert
   Set conv = unitSvr
   dblTo = conv.Convert(dblFrom, strFrom, strTo)

   Dim fmt As String
   fmt = "#."
   Dim i As Integer
   For i = 1 To Precision
     fmt = fmt & "0"
   Next i
   If (frmOptions.ckScientific.Value = 1) Then
      fmt = fmt & "E+00"
   End If
   
   lblConvertTo = Format(dblTo, fmt)
   
End Sub


Private Sub cboFrom_Click()
   'Convert when the from unit changes
   ConvertNow
End Sub

Private Sub cboTo_Click()
   'Convert when the to unit changes
   ConvertNow
End Sub

Private Sub UpdateComboBoxes()
   
   Dim u As WBFLUnitServer.Unit
   cboFrom.Clear
   cboTo.Clear

   'Fill up the combo boxes with the unit tags
   Dim units As WBFLUnitServer.units
   Dim unitType As WBFLUnitServer.unitType
   Set unitType = unitSvr.unitTypes.Item(lstUnitType.ListIndex)
   Set units = unitType.units
   Dim i As Integer
   For i = 0 To units.Count - 1
      Set u = units.Item(i)
      cboFrom.AddItem u.Tag
      cboTo.AddItem u.Tag
   Next
   cboFrom.ListIndex = 0
   cboTo.ListIndex = 0

End Sub


Private Sub lstUnitType_Click()
   UpdateComboBoxes
End Sub

Private Sub Form_Load()
   Precision = 3
   
   'Instantiate the unit server
   Set unitSvr = New WBFLUnitServer.UnitServer
   
   'Lets start with a valid number
   txtConvertFrom.Text = 1#

   'Fill the combo box with unit types
   Dim unitTypes As WBFLUnitServer.unitTypes
   Set unitTypes = unitSvr.unitTypes
   Dim ut As WBFLUnitServer.unitType
   Dim i As Long
   For i = 0 To unitTypes.Count - 1
      Set ut = unitTypes.Item(i)
      lstUnitType.AddItem ut.Label
   Next
   
   lstUnitType.ListIndex = 0
   
   UpdateComboBoxes
   
   ConvertNow

End Sub


Private Sub Form_Unload(Cancel As Integer)
   Set unitSvr = Nothing
   End
End Sub

Private Sub mnuOptions_Click()
   frmOptions.Show vbModal, Me
End Sub

Private Sub txtConvertFrom_Change()
  If (IsNumeric(txtConvertFrom) = True) Then
     ConvertNow
  End If
End Sub
