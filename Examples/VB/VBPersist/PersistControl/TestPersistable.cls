VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TestPersistable"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Implements IStructuredStorage2

Dim m_Len As Double
Dim m_Num As Integer
Dim m_Name As String

Private Sub IStructuredStorage2_Load(ByVal sl As WBFLTools.IStructuredLoad2)
' first intialize members to bogus values to make sure we've really loaded
' the right ones
Name = "dog doo"
Count = -12
Length = -42.2

' now load so we can check our values
sl.BeginUnit "TestStorage"

Dim version As Double
version = sl.version

Name = sl.Property("Name")
Count = sl.Property("Count")
Length = sl.Property("Length")

Dim eu As Boolean
eu = sl.EndUnit
End Sub

Private Sub IStructuredStorage2_Save(ByVal ss As WBFLTools.IStructuredSave2)
ss.BeginUnit "TestStorage", 1#
ss.Property("Name") = Name
ss.Property("Count") = Count
ss.Property("Length") = Length
ss.EndUnit
End Sub

Public Property Get Length() As Double
    Length = m_Len
End Property

Public Property Let Length(ByVal NewValue As Double)
   m_Len = NewValue
End Property

Public Property Get Count() As Integer
   Count = m_Num
End Property

Public Property Let Count(ByVal NewValue As Integer)
   m_Num = NewValue
End Property

Public Property Get Name() As String
    Name = m_Name
End Property

Public Property Let Name(ByVal NewValue As String)
   m_Name = NewValue
End Property

