VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Mohr's Circle Example"
   ClientHeight    =   3192
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3192
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "Update"
      Height          =   372
      Left            =   600
      TabIndex        =   14
      Top             =   2400
      Width           =   972
   End
   Begin VB.TextBox txtDir 
      Height          =   372
      Left            =   1080
      TabIndex        =   7
      Text            =   "0.00"
      Top             =   1440
      Width           =   972
   End
   Begin VB.TextBox txtSxy 
      Height          =   372
      Left            =   1080
      TabIndex        =   5
      Text            =   "0.00"
      Top             =   840
      Width           =   972
   End
   Begin VB.TextBox txtSyy 
      Height          =   372
      Left            =   1080
      TabIndex        =   3
      Text            =   "0.00"
      Top             =   480
      Width           =   972
   End
   Begin VB.TextBox txtSxx 
      Height          =   372
      Left            =   1080
      TabIndex        =   1
      Text            =   "0.00"
      Top             =   120
      Width           =   972
   End
   Begin VB.Label lblPrincDir 
      AutoSize        =   -1  'True
      Caption         =   "PrincDir"
      Height          =   192
      Left            =   2280
      TabIndex        =   15
      Top             =   840
      Width           =   564
   End
   Begin VB.Label lblSxy1 
      AutoSize        =   -1  'True
      Caption         =   "Sxy1"
      Height          =   192
      Left            =   2280
      TabIndex        =   13
      Top             =   1920
      Width           =   348
   End
   Begin VB.Label lblSy1 
      AutoSize        =   -1  'True
      Caption         =   "Sy1"
      Height          =   192
      Left            =   2280
      TabIndex        =   12
      Top             =   1680
      Width           =   276
   End
   Begin VB.Label lblSx1 
      AutoSize        =   -1  'True
      Caption         =   "Sx1"
      Height          =   192
      Left            =   2280
      TabIndex        =   11
      Top             =   1440
      Width           =   264
   End
   Begin VB.Label lblS12 
      AutoSize        =   -1  'True
      Caption         =   "S12"
      Height          =   192
      Left            =   2280
      TabIndex        =   10
      Top             =   600
      Width           =   276
   End
   Begin VB.Label lblS22 
      AutoSize        =   -1  'True
      Caption         =   "S22"
      Height          =   192
      Left            =   2280
      TabIndex        =   9
      Top             =   360
      Width           =   276
   End
   Begin VB.Label lblS11 
      AutoSize        =   -1  'True
      Caption         =   "S11"
      Height          =   192
      Left            =   2280
      TabIndex        =   8
      Top             =   120
      Width           =   276
   End
   Begin VB.Label Label4 
      Caption         =   "Orientation (radians)"
      Height          =   372
      Left            =   120
      TabIndex        =   6
      Top             =   1440
      Width           =   972
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Sxy"
      Height          =   192
      Left            =   120
      TabIndex        =   4
      Top             =   840
      Width           =   264
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Sy"
      Height          =   192
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   192
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Sx"
      Height          =   192
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   180
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private g_MohrCircle As WBFLTools.MohrCircle

Private Sub cmdUpdate_Click()
   g_MohrCircle.Sii = txtSxx
   g_MohrCircle.Sjj = txtSyy
   g_MohrCircle.Sij = txtSxy
   
   lblS11 = "Smax = " & g_MohrCircle.Smax
   lblS22 = "Smin = " & g_MohrCircle.Smin
   lblS12 = "Tmax = " & g_MohrCircle.Tmax
   lblPrincDir = "Principle Direction = " & g_MohrCircle.PrincipleDirection * 180 / 3.1415
   
   Dim Sx1 As Double
   Dim Sy1 As Double
   Dim Sxy1 As Double
   
   g_MohrCircle.ComputeState txtDir * 3.1415 / 180#, Sx1, Sy1, Sxy1
   
   lblSx1 = "Sx1 = " & Sx1
   lblSy1 = "Sy1 = " & Sy1
   lblSxy1 = "Sxy1 = " & Sxy1
End Sub

Private Sub Form_Load()
   Set g_MohrCircle = New WBFLTools.MohrCircle
   
   cmdUpdate_Click
End Sub

Private Sub Form_Unload(Cancel As Integer)
   Set g_MohrCircle = Nothing
End Sub
