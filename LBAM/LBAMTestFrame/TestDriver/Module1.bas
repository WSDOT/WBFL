Attribute VB_Name = "Module1"
Option Explicit
' a bunch of utilities
Public Function GridFmt(val As Double) As String
   Dim str As String
   If val <> 0# And Abs(val) < 0.0001 Then
      str = Format(val, "0.000e+00")
   Else
      str = Format(val, "####0.0###")
      If Len(str) > 10 Then
         str = Format(val, "0.000e+00")
      End If
   End If
   
   GridFmt = str
End Function

Public Function IsNothing(Value As Variant) As Boolean

   Dim vTest As Variant
   Dim iArrayStart As Integer
   Dim iCtr As Integer
   Dim bFlag As Boolean
   
   If IsEmpty(Value) Then
       IsNothing = True
       Exit Function
   End If
   
   If IsNull(Value) Then
       IsNothing = True
       Exit Function
   End If
   
   If VarType(Value) = vbString Then
       If Value = "" Then
           IsNothing = True
           Exit Function
       End If
   End If
   
   If IsNumeric(Value) Then
       If Value = 0 Then
           IsNothing = True
           Exit Function
       End If
   End If
   
   If IsObject(Value) Then
       If Value Is Nothing Then
           IsNothing = True
           Exit Function
       End If
       
   End If
   
   If IsArray(Value) Then
       On Error Resume Next
       vTest = Value(0)
       iArrayStart = IIf(Err.Number = 0, 0, 1)
       Err.Clear
       On Error GoTo 0
       For iCtr = iArrayStart To UBound(Value)
           If Not IsNothing(Value(iCtr)) Then
               bFlag = True
               Exit For
           End If
           
       Next
       IsNothing = Not bFlag
   End If
   
End Function

Public Function FindComboString(cbx As ComboBox, str As String) As Integer
   Dim retval As Integer
   retval = -1
   Dim cnt As Integer, i As Integer
   cnt = cbx.ListCount
   For i = 0 To cnt - 1
     If cbx.List(i) = str Then
        retval = i
        Exit For
     End If
   Next i
   
   FindComboString = retval
End Function

Public Function FindComboInt(cbx As ComboBox, intg As Integer) As Integer
   Dim retval As Integer
   retval = -1
   Dim cnt As Integer, i As Integer
   cnt = cbx.ListCount
   For i = 0 To cnt - 1
     If CInt(cbx.List(i)) = intg Then
        retval = i
        Exit For
     End If
   Next i
   
   FindComboInt = retval
End Function

