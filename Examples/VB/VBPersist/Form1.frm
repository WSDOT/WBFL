VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2628
   ClientLeft      =   48
   ClientTop       =   348
   ClientWidth     =   5652
   LinkTopic       =   "Form1"
   ScaleHeight     =   2628
   ScaleWidth      =   5652
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Load"
      Height          =   612
      Left            =   2280
      TabIndex        =   1
      Top             =   600
      Width           =   1452
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Save"
      Height          =   612
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   1332
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' this project gives an example of how to create and use VB controls
' that use the IStructuredStorage interfaces.
' The form in this project is used to save and restore data from Controls
' defined in the PersistControl project.
Dim m_Embedded As New TestPersistable
Option Explicit


Private Sub Command1_Click()

Dim ss As New StructuredSave2
ss.Open ("test.xml")
ss.BeginUnit "MyUnit", 1#
ss.Property("MyString") = "This is a string"
ss.Property("MyDouble") = 2.712

ss.Property("Embedded") = m_Embedded

ss.Property("MyInteger") = 42
ss.EndUnit
ss.Close

End Sub

Private Sub Command2_Click()
Dim ts As String
Dim td As Double
Dim ti As Integer
Dim b As Boolean

m_Embedded.Count = 32
m_Embedded.Name = CStr("bogus name")
m_Embedded.Length = 3.141


Dim sl As New StructuredLoad2
sl.Open ("test.xml")
sl.BeginUnit "MyUnit"
ts = CStr(sl.Property("MyString"))
td = sl.Property("MyDouble")

' Dim iss As IStructuredStorage2
' Set iss = m_Embedded
' iss.Load sl
Set m_Embedded = sl.Property("Embedded")

ti = sl.Property("MyInteger")
b = sl.EndUnit
sl.Close


End Sub

Private Sub Form_Load()
   m_Embedded.Count = 2
   m_Embedded.Name = CStr("I am an embedded object")
   m_Embedded.Length = 14.2

End Sub
