VERSION 5.00
Object = "{FE0065C0-1B7B-11CF-9D53-00AA003C9CB6}#1.1#0"; "COMCT232.OCX"
Begin VB.Form frmOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Options"
   ClientHeight    =   1536
   ClientLeft      =   5664
   ClientTop       =   2208
   ClientWidth     =   2904
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1536
   ScaleWidth      =   2904
   ShowInTaskbar   =   0   'False
   Begin ComCtl2.UpDown UpDown1 
      Height          =   252
      Left            =   1813
      TabIndex        =   2
      Top             =   120
      Width           =   192
      _ExtentX        =   339
      _ExtentY        =   445
      _Version        =   327681
      Value           =   1
      AutoBuddy       =   -1  'True
      BuddyControl    =   "txtPrecision"
      BuddyDispid     =   196615
      OrigLeft        =   1920
      OrigTop         =   120
      OrigRight       =   2112
      OrigBottom      =   372
      Min             =   1
      SyncBuddy       =   -1  'True
      BuddyProperty   =   0
      Enabled         =   -1  'True
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   372
      Left            =   1560
      TabIndex        =   4
      Top             =   960
      Width           =   972
   End
   Begin VB.CheckBox ckScientific 
      Caption         =   "Use Scientifc Notation"
      Height          =   252
      Left            =   240
      TabIndex        =   3
      Top             =   480
      Width           =   1932
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   372
      Left            =   360
      TabIndex        =   0
      Top             =   960
      Width           =   972
   End
   Begin VB.Label txtPrecision 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Label1"
      Height          =   252
      Left            =   1080
      TabIndex        =   5
      Top             =   120
      Width           =   732
   End
   Begin VB.Label lblPrecision 
      Caption         =   "Precision"
      Height          =   252
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   852
   End
End
Attribute VB_Name = "frmOptions"
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

Private Sub cmdCancel_Click()
   Me.Hide
End Sub

Private Sub cmdOK_Click()
   Me.Hide
   frmMain.Precision = txtPrecision
   frmMain.ConvertNow
End Sub

Private Sub Form_Load()
   txtPrecision = frmMain.Precision
End Sub
