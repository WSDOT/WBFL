VERSION 5.00
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form PDelta 
   Caption         =   "P - Delta Analysis for a Simple Column"
   ClientHeight    =   6270
   ClientLeft      =   45
   ClientTop       =   345
   ClientWidth     =   9975
   LinkTopic       =   "PDelta"
   ScaleHeight     =   6270
   ScaleWidth      =   9975
   StartUpPosition =   3  'Windows Default
   Begin MSChart20Lib.MSChart MSChart1 
      Height          =   5772
      Left            =   3120
      OleObjectBlob   =   "PDelta.frx":0000
      TabIndex        =   13
      Top             =   240
      Width           =   6612
   End
   Begin VB.TextBox PerturbCtl 
      Height          =   288
      Left            =   1320
      TabIndex        =   10
      Text            =   "0.01"
      ToolTipText     =   "Inital moment applied to top of column = Perturbation * P * Length"
      Top             =   2400
      Width           =   972
   End
   Begin VB.TextBox LoadCtl 
      Height          =   288
      Left            =   1320
      TabIndex        =   7
      Text            =   "4.0"
      ToolTipText     =   "Downward axial load applied to top of column"
      Top             =   1920
      Width           =   972
   End
   Begin VB.TextBox EACtl 
      Height          =   288
      Left            =   1320
      TabIndex        =   6
      Text            =   "4.0"
      ToolTipText     =   "Axial stiffness. Used to calculate axial deformation"
      Top             =   1200
      Width           =   972
   End
   Begin VB.TextBox EICtl 
      Height          =   288
      Left            =   1320
      TabIndex        =   5
      Text            =   "1000.0"
      ToolTipText     =   "Bending stiffness"
      Top             =   720
      Width           =   972
   End
   Begin VB.TextBox LengthCtl 
      Height          =   288
      Left            =   1320
      TabIndex        =   1
      Text            =   "100.0"
      ToolTipText     =   "Total length of column"
      Top             =   240
      Width           =   972
   End
   Begin VB.CommandButton Analyze 
      Caption         =   "Analyze"
      Height          =   492
      Left            =   600
      TabIndex        =   0
      Top             =   3360
      Width           =   1212
   End
   Begin VB.Label StableCtl 
      ForeColor       =   &H000000FF&
      Height          =   612
      Left            =   120
      TabIndex        =   14
      Top             =   4920
      Width           =   2772
   End
   Begin VB.Label Label6 
      Caption         =   "%"
      Height          =   372
      Left            =   2400
      TabIndex        =   12
      Top             =   2400
      Width           =   372
   End
   Begin VB.Label Label5 
      Caption         =   "Perturbation"
      Height          =   252
      Left            =   120
      TabIndex        =   11
      Top             =   2400
      Width           =   1212
   End
   Begin VB.Label EulerCtl 
      Caption         =   "Euler Buckling Load = "
      Height          =   612
      Left            =   120
      TabIndex        =   9
      ToolTipText     =   "Calculated from 0.25*PI^2*EI/L^2"
      Top             =   4320
      Width           =   2772
   End
   Begin VB.Label Label4 
      Caption         =   "Axial Load, P"
      Height          =   252
      Left            =   120
      TabIndex        =   8
      Top             =   1920
      Width           =   1212
   End
   Begin VB.Label Label3 
      Caption         =   "EA"
      Height          =   252
      Left            =   480
      TabIndex        =   4
      Top             =   1200
      Width           =   612
   End
   Begin VB.Label Label2 
      Caption         =   "EI"
      Height          =   252
      Left            =   480
      TabIndex        =   3
      Top             =   720
      Width           =   612
   End
   Begin VB.Label Label1 
      Caption         =   "Length"
      Height          =   372
      Left            =   480
      TabIndex        =   2
      Top             =   240
      Width           =   732
   End
End
Attribute VB_Name = "PDelta"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Option Base 1
Private Const NUMITERS As Integer = 100
Private Const PI As Double = 3.14159265
Private GraphArray()

Private Function Max(mx As Double, p1 As Double, p2 As Double)
   If p1 > p2 Then
      mx = p1
   Else
      mx = p2
   End If
End Function
Private Function Min(mn As Double, p1 As Double, p2 As Double)
   If p1 < p2 Then
      mn = p1
   Else
      mn = p2
   End If
End Function
Private Sub Compute_Euler(Optional pcr As Double)
   Dim length As Double, ea As Double, ei As Double
   length = LengthCtl
   ea = EACtl
   ei = EICtl
   pcr = 0.25 * PI * PI * ei / (length * length)
   
   Dim st As String
   st = "Euler Critical Buckling Load = "
   st = st + Format(pcr, "0.0000")
 
   EulerCtl = st

End Sub

Private Sub Analyze_Click()

Dim model As model
Set model = New model

Dim joints As JointCollection
Set joints = model.joints

Dim jnt As joint
Set jnt = joints.Create(1, 0#, 0#)
jnt.Support

Dim l As Double
l = LengthCtl

Set jnt = joints.Create(2, 0#, l)

Dim members As MemberCollection
Set members = model.members

Dim ea As Double
Dim ei As Double
ea = EACtl
ei = EICtl

Dim mbr As member
Set mbr = members.Create(1, 1, 2, ea, ei)

Dim P As Double
P = LoadCtl

Dim pert As Double
pert = PerturbCtl
Dim mInit As Double
mInit = -pert * P * l / 100

Dim loadings As LoadingCollection
Set loadings = model.loadings
Dim loading As loading
Set loading = loadings.Create(1)
Dim jointloads As JointLoadCollection
Set jointloads = loading.jointloads
Dim jointload As jointload

' Initial column load
Set jointload = jointloads.Create(1, 2, 0, -P, mInit)

Dim dx As Double, dy As Double, rz As Double
Dim dx_min As Double, dy_min As Double
Dim dx_max As Double, dy_max As Double
dx_min = 1E+300
dy_min = 1E+300
dx_max = -1E+300
dy_max = -1E+300
Dim mnew As Double

Dim res As IModelResults
Set res = model.Results

Dim arrValues(1 To NUMITERS, 1 To 3)
Dim i As Integer, j As Integer
On Error GoTo SolveError
For i = 1 To NUMITERS
   res.ComputeJointDisplacements 1, 2, dx, dy, rz
   
   arrValues(i, 1) = Str(i) 'label
   arrValues(i, 2) = dx
   arrValues(i, 3) = dy
   Call Min(dy_min, dy_min, dy)
   Call Max(dy_max, dy_max, dy)
   Call Min(dx_min, dx_min, dx)
   Call Max(dx_max, dx_max, dx)
   
   mnew = -P * dx
   jointload.Mz = mnew
Next i

' got to here, no error from fem2d.
ReDim GraphArray(1 To NUMITERS, 1 To 3)
For i = 1 To NUMITERS
   For j = 1 To 3
      GraphArray(i, j) = arrValues(i, j)
   Next j
Next i

' Check deflection to see if iteration converged.
Dim lastval As Double, nextlastval As Double, pd As Double
Dim passed As Boolean
lastval = GraphArray(NUMITERS, 2)
nextlastval = GraphArray(NUMITERS - 1, 2)
If nextlastval <> 0 Then
    pd = Abs((lastval - nextlastval) / nextlastval)
    If pd < 0.01 Then
        passed = True
    Else
        passed = False
    End If
Else
    passed = True
End If

If passed Then
    StableCtl.ForeColor = RGB(0, 255, 0)
    StableCtl = "Column is Stable"
Else
    StableCtl.ForeColor = RGB(255, 0, 0)
    Dim ste As String
    ste = "Column is Unstable. Did not converge after "
    ste = ste + Str(NUMITERS)
    ste = ste + " iterations"
    StableCtl = ste
End If

GoTo FillGraph ' goto's are hateful, but once they start...

SolveError:
' f.e. engine crapped for some reason. Assume this means unstable
Dim lastit As Integer
lastit = i - 1
' shrink size of array to fit data
ReDim GraphArray(1 To lastit, 1 To 3)
For i = 1 To lastit
   For j = 1 To 3
      GraphArray(i, j) = arrValues(i, j)
   Next j
Next i

StableCtl.ForeColor = RGB(255, 0, 0)
Dim st As String
st = "Column is Unstable. F.E. model became unstable after "
st = st + Str(lastit)
st = st + " iterations"
StableCtl = st

FillGraph:
' fill the graph with the data we have up to now

MSChart1.ChartData = GraphArray

With MSChart1
    .chartType = VtChChartType2dLine
    .ColumnCount = 2
    .ColumnLabelCount = 2
    .Column = 1
    .ColumnLabel = "X"
    .Column = 2
    .ColumnLabel = "Y"
    .Plot.UniformAxis = False
    .Plot.Axis(VtChAxisIdX).Tick.Style = VtChAxisTickStyleNone
End With

MSChart1.Refresh

End Sub

Private Sub EICtl_Change()
    Compute_Euler
End Sub

Private Sub Form_Load()
    Dim pcr As Double
    Compute_Euler pcr
    LoadCtl = 0.9 * pcr
    
    Analyze_Click
End Sub
