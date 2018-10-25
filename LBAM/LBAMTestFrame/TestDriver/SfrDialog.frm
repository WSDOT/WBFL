VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form SfrDialog 
   AutoRedraw      =   -1  'True
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Edit Section Requests"
   ClientHeight    =   6132
   ClientLeft      =   2760
   ClientTop       =   3756
   ClientWidth     =   9504
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6132
   ScaleWidth      =   9504
   ShowInTaskbar   =   0   'False
   Begin VB.Frame ctlStressFrame 
      Caption         =   "Stress Results"
      Height          =   1932
      Left            =   5760
      TabIndex        =   25
      Top             =   1800
      Width           =   3372
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid ctlStressGrid 
         Height          =   1332
         Left            =   240
         TabIndex        =   26
         Top             =   360
         Width           =   2892
         _ExtentX        =   5101
         _ExtentY        =   2350
         _Version        =   393216
         _NumberOfBands  =   1
         _Band(0).Cols   =   2
      End
   End
   Begin VB.HScrollBar SfScroller 
      Height          =   252
      Left            =   480
      TabIndex        =   10
      Top             =   3120
      Width           =   4812
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid ctlResultsGrid 
      Height          =   1212
      Left            =   600
      TabIndex        =   11
      Top             =   4320
      Width           =   2844
      _ExtentX        =   5017
      _ExtentY        =   2138
      _Version        =   393216
      Rows            =   4
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.CommandButton ctlClone 
      Caption         =   "Clone"
      Height          =   372
      Left            =   2280
      TabIndex        =   9
      Top             =   2520
      Width           =   1092
   End
   Begin VB.ComboBox ctlOrientation 
      Height          =   288
      ItemData        =   "SfrDialog.frx":0000
      Left            =   3000
      List            =   "SfrDialog.frx":000A
      TabIndex        =   8
      Text            =   "Orientation"
      Top             =   1320
      Width           =   2292
   End
   Begin VB.ComboBox ctlPOIs 
      Height          =   288
      Left            =   480
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   1320
      Width           =   1692
   End
   Begin VB.ComboBox ctlLoadingNames 
      Height          =   288
      ItemData        =   "SfrDialog.frx":0022
      Left            =   3000
      List            =   "SfrDialog.frx":0024
      TabIndex        =   6
      Text            =   "Loading Name"
      Top             =   2040
      Width           =   2292
   End
   Begin VB.ComboBox ctlSummation 
      Height          =   288
      ItemData        =   "SfrDialog.frx":0026
      Left            =   3000
      List            =   "SfrDialog.frx":0030
      TabIndex        =   5
      Text            =   "Summation Method"
      Top             =   600
      Width           =   2292
   End
   Begin VB.ComboBox ctlLoadingType 
      Height          =   288
      ItemData        =   "SfrDialog.frx":0052
      Left            =   480
      List            =   "SfrDialog.frx":005F
      TabIndex        =   4
      Text            =   "LoadingType"
      Top             =   2040
      Width           =   2052
   End
   Begin VB.ComboBox ctlStages 
      Height          =   288
      ItemData        =   "SfrDialog.frx":008F
      Left            =   480
      List            =   "SfrDialog.frx":0091
      TabIndex        =   3
      Text            =   "Stages"
      Top             =   600
      Width           =   2052
   End
   Begin VB.CommandButton ctlDelete 
      Caption         =   "Delete"
      Height          =   372
      Left            =   3480
      TabIndex        =   2
      Top             =   2520
      Width           =   1092
   End
   Begin VB.CommandButton ctlAdd 
      Caption         =   "Add"
      Height          =   372
      Left            =   1080
      TabIndex        =   1
      Top             =   2520
      Width           =   1092
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Done"
      Height          =   732
      Left            =   7560
      TabIndex        =   0
      Top             =   4920
      Width           =   1215
   End
   Begin VB.Frame ctlResultsFrame 
      Caption         =   "Section Force Results"
      Height          =   1812
      Left            =   240
      TabIndex        =   12
      Top             =   3960
      Width           =   3492
   End
   Begin VB.Frame Frame2 
      Caption         =   "Edit Request"
      Height          =   3612
      Left            =   240
      TabIndex        =   13
      Top             =   120
      Width           =   5292
      Begin VB.Label Label11 
         Caption         =   "Loading Name"
         Height          =   252
         Left            =   2760
         TabIndex        =   19
         Top             =   1680
         Width           =   2052
      End
      Begin VB.Label Label10 
         Caption         =   "Loading Type"
         Height          =   252
         Left            =   240
         TabIndex        =   18
         Top             =   1680
         Width           =   1572
      End
      Begin VB.Label Label9 
         Caption         =   "Results Orientation"
         Height          =   252
         Left            =   2760
         TabIndex        =   17
         Top             =   960
         Width           =   1932
      End
      Begin VB.Label Label8 
         Caption         =   "POI"
         Height          =   252
         Left            =   240
         TabIndex        =   16
         Top             =   960
         Width           =   1092
      End
      Begin VB.Label Label7 
         Caption         =   "Summation Method"
         Height          =   252
         Left            =   2760
         TabIndex        =   15
         Top             =   240
         Width           =   1692
      End
      Begin VB.Label Label6 
         Caption         =   "Stage"
         Height          =   252
         Left            =   240
         TabIndex        =   14
         Top             =   240
         Width           =   1332
      End
      Begin VB.Label ctlRecords 
         Alignment       =   2  'Center
         Caption         =   "Record 0 of 0"
         Height          =   252
         Left            =   1200
         TabIndex        =   20
         Top             =   3240
         Width           =   3012
      End
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid ctlDeflectionsGrid 
      Height          =   1212
      Left            =   4200
      TabIndex        =   21
      Top             =   4320
      Width           =   2844
      _ExtentX        =   5017
      _ExtentY        =   2138
      _Version        =   393216
      Rows            =   4
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.Frame ctlDeflectionsFrame 
      Caption         =   "Section Deflection Results"
      Height          =   1812
      Left            =   3960
      TabIndex        =   22
      Top             =   3960
      Width           =   3372
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid ctlPOIGrid 
      Height          =   852
      Left            =   6000
      TabIndex        =   23
      Top             =   480
      Width           =   2004
      _ExtentX        =   3535
      _ExtentY        =   1503
      _Version        =   393216
      Rows            =   3
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.Frame ctlPOIFrame 
      Caption         =   "POI location"
      Height          =   1452
      Left            =   5760
      TabIndex        =   24
      Top             =   120
      Width           =   2412
   End
End
Attribute VB_Name = "SfrDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public m_Requests As SectionResultRequests
Private m_CurrentRequest As SectionResultRequest
Public m_Model As LBAMModel
Public m_Dirty As Boolean
Private m_MuteEvents As Boolean

Private Sub ctlAdd_Click()
   ' add a new request
   If Not m_MuteEvents Then
      Dim sfr As New SectionResultRequest
      InitSfr sfr
      m_Requests.Add sfr
      
      Dim cnt As Integer
      cnt = m_Requests.count
      If cnt = 1 Then
         EnableCtrls True
      End If
      
      UpdateScroller
      DisplayRecord (cnt - 1)
      SfScroller.Value = cnt - 1
      MakeDirty
   End If
End Sub

Private Sub DisplayRecord(index As Integer)
   ' have to mute events to keep them from cascading
   m_MuteEvents = True
   
   If m_Requests.count = 0 Then
   
      EnableCtrls False
      
   Else
      Set m_CurrentRequest = m_Requests(index)
      
      ' stage
      Dim stg As String, idx As Integer
      stg = m_CurrentRequest.Stage
      idx = FindComboString(ctlStages, stg)
      If idx = -1 Then
         MsgBox "Error - The selected stage in the current request did not match any in the model. Resetting to default"
         m_CurrentRequest.Stage = m_Model.stages.Item(0).name
         idx = 0
      End If
      ctlStages.ListIndex = idx
      
      ' summation method
      Dim summ As ResultsSummationType
      summ = m_CurrentRequest.ResultsSummationType
      idx = CInt(summ)
      If idx < 0 Or idx > ctlSummation.ListCount - 1 Then
         MsgBox "Error - The selected summation type in the current request is out of range. Resetting to default"
         m_CurrentRequest.ResultsSummationType = rsCummulative
         idx = 0
      End If
      ctlSummation.ListIndex = idx
      
      ' poi
      Dim poi As Integer
      poi = m_CurrentRequest.poiid
      idx = FindComboInt(ctlPOIs, poi)
      If idx = -1 Then
         MsgBox "Error - The selected poi in the current request did not match any in the model. Resetting to default"
         m_CurrentRequest.poiid = m_Model.POIs.Item(0).Id
         idx = 0
      End If
      ctlPOIs.ListIndex = idx
      
      ' orientation
      Dim ornt As ResultsOrientation
      ornt = m_CurrentRequest.ResultsOrientation
      idx = CInt(ornt)
      If idx < 0 Or idx > ctlOrientation.ListCount - 1 Then
         MsgBox "Error - The selected orientation type in the current request is out of range. Resetting to default"
         m_CurrentRequest.ResultsOrientation = roGlobal
         idx = 0
      End If
      ctlOrientation.ListIndex = idx
   
      ' loading type
      Dim lt As LoadingType
      lt = m_CurrentRequest.LoadingType
      idx = CInt(lt)
      If idx < 0 Or idx > ctlLoadingType.ListCount - 1 Then
         MsgBox "Error - The selected loading type in the current request is out of range. Resetting to default"
         m_CurrentRequest.LoadingType = ltLoadGroup
         idx = CInt(ltLoadGroup)
      End If
      ctlLoadingType.ListIndex = idx
      
      ' fill in loading names for loading type
      FillLoadingNamesForLoadingType (lt)
      
      ' loading name
      Dim ln As String
      ln = m_CurrentRequest.LoadingName
      idx = FindComboString(ctlLoadingNames, ln)
      If idx = -1 Then
         MsgBox "Error - The selected loading name in the current request did not match any in the model. Resetting to default"
         m_CurrentRequest.LoadingName = m_Model.LoadGroups.Item(0).name
         ctlLoadingType.ListIndex = 0 ' set back to loadgroup
         idx = 0
      End If
      ctlLoadingNames.ListIndex = idx

      ' poi coordinates
      FillPoiGrid

      ' fill grid with results
      FillForceGrid
      
      ' fill deflection grid
      FillDeflectionGrid
      
      ' fill stress grid
      FillStressGrid
      
   End If
   
   ' let events happen
   m_MuteEvents = False
   
End Sub
Private Sub FillPoiGrid()
   Dim poi_id As Integer
   poi_id = m_CurrentRequest.poiid
   
   Dim curr_poi As poi
   Set curr_poi = m_Model.POIs.Find(poi_id)
   If curr_poi Is Nothing Then
      MsgBox "Programming error - could not find poi"
   End If
   
   Dim x As Double, y As Double
   m_Model.ComputeLocation curr_poi.MemberID, curr_poi.MemberType, curr_poi.location, x, y
   
   ctlPOIGrid.Enabled = True
   ctlPOIFrame.Enabled = True
   ctlPOIGrid.Row = 1
   ctlPOIGrid.Col = 1
   ctlPOIGrid.Text = GridFmt(x)
   ctlPOIGrid.Row = 2
   ctlPOIGrid.Text = GridFmt(y)

End Sub
Private Sub FillForceGrid()
      If Not IsNothing(m_CurrentRequest.SectionForceResult) Then
      
         With m_CurrentRequest.SectionForceResult
            ctlResultsGrid.Enabled = True
            ctlResultsFrame.Enabled = True
            ctlResultsGrid.Row = 1
            ctlResultsGrid.Col = 1
            ctlResultsGrid.Text = GridFmt(.XLeft)
            ctlResultsGrid.Row = 2
            ctlResultsGrid.Text = GridFmt(.YLeft)
            ctlResultsGrid.Row = 3
            ctlResultsGrid.Text = GridFmt(.ZLeft)
            ctlResultsGrid.Col = 2
            ctlResultsGrid.Row = 1
            ctlResultsGrid.Text = GridFmt(.XRight)
            ctlResultsGrid.Row = 2
            ctlResultsGrid.Text = GridFmt(.YRight)
            ctlResultsGrid.Row = 3
            ctlResultsGrid.Text = GridFmt(.ZRight)
         End With
      
      Else
         ClearForceGrid
      End If
End Sub
Private Sub ClearForceGrid()
   ' clear grid text and disable
   Dim i As Integer, j As Integer
   For i = 1 To 2
       For j = 1 To 3
         ctlResultsGrid.Row = j
         ctlResultsGrid.Col = i
         ctlResultsGrid.Text = ""

       Next j
   Next i
   
   ctlResultsGrid.Enabled = False
   ctlResultsFrame.Enabled = False
End Sub
Private Sub FillDeflectionGrid()
      If Not IsNothing(m_CurrentRequest.DeflectionResult) Then
      
         With m_CurrentRequest.DeflectionResult
            ctlDeflectionsGrid.Enabled = True
            ctlDeflectionsFrame.Enabled = True
            ctlDeflectionsGrid.Row = 1
            ctlDeflectionsGrid.Col = 1
            ctlDeflectionsGrid.Text = GridFmt(.XLeft)
            ctlDeflectionsGrid.Row = 2
            ctlDeflectionsGrid.Text = GridFmt(.YLeft)
            ctlDeflectionsGrid.Row = 3
            ctlDeflectionsGrid.Text = GridFmt(.ZLeft)
            ctlDeflectionsGrid.Col = 2
            ctlDeflectionsGrid.Row = 1
            ctlDeflectionsGrid.Text = GridFmt(.XRight)
            ctlDeflectionsGrid.Row = 2
            ctlDeflectionsGrid.Text = GridFmt(.YRight)
            ctlDeflectionsGrid.Row = 3
            ctlDeflectionsGrid.Text = GridFmt(.ZRight)
         End With
      
      Else
         ClearDeflectionsGrid
      End If
End Sub
Private Sub ClearDeflectionsGrid()
   ' clear grid text and disable
   Dim i As Integer, j As Integer
   i = 1
   For j = 1 To 3
     ctlDeflectionsGrid.Row = j
     ctlDeflectionsGrid.Col = i
     ctlDeflectionsGrid.Text = ""

   Next j
   
   ctlDeflectionsGrid.Enabled = False
   ctlDeflectionsFrame.Enabled = False
End Sub


Private Sub FillStressGrid()
   Dim left_count As Long, right_count As Long, i As Long
   left_count = 0
   right_count = 0
   If Not IsNothing(m_CurrentRequest.StressResults) Then
      left_count = m_CurrentRequest.StressResults.LeftCount
      right_count = m_CurrentRequest.StressResults.RightCount
   End If
      
   If left_count <> 0 Then
      ctlStressGrid.Rows = left_count + 1
      
      For i = 0 To left_count - 1
         Dim result As ISectionStressResult
         Set result = m_CurrentRequest.StressResults
      
         With result
            ctlStressGrid.Enabled = True
            ctlStressFrame.Enabled = True
            ctlStressGrid.Row = i + 1
            ctlStressGrid.Col = 0
            ctlStressGrid.Text = i
            ctlStressGrid.Col = 1
            ctlStressGrid.Text = GridFmt(.GetLeftResult(i))
            ctlStressGrid.Col = 2
            If (right_count > i) Then
               ctlStressGrid.Text = GridFmt(.GetRightResult(i))
            End If
         End With
      Next i

   Else
      ClearStressGrid
   End If
End Sub
Private Sub ClearStressGrid()
   ' clear grid text and disable
   ctlStressGrid.Rows = 1
   
   ctlStressGrid.Enabled = False
   ctlStressFrame.Enabled = False
End Sub


Private Sub FillLoadingNamesForLoadingType(lt As LoadingType)
   ctlLoadingNames.Clear
   
   If lt = ltLoadGroup Then
   
      Dim lgs As LoadGroups
      Set lgs = m_Model.LoadGroups
      Dim lg As LoadGroup
      For Each lg In lgs
         ctlLoadingNames.AddItem lg.name
      Next
      
'   ElseIf lt = ltLoadCase Then
'   ElseIf lt = ltLoadCombination Then
   
   Else
      MsgBox "Only LoadGroups are supported in this version - get off your butt and get finished. By the way, this request is now hosed"
   End If
   
End Sub

Private Sub InitSfr(request As SectionResultRequest)
   ' select some simple defaults
   request.Stage = m_Model.stages.Item(0).name
   request.LoadingType = ltLoadGroup
   request.LoadingName = m_Model.LoadGroups.Item(0).name
   request.poiid = m_Model.POIs.Item(0).Id
End Sub
Private Sub ctlClone_Click()

   If Not m_MuteEvents Then
      Dim clone As SectionResultRequest
      Set clone = m_CurrentRequest.clone
      m_Requests.Add clone
      
      Dim cnt As Integer
      cnt = m_Requests.count
      DisplayRecord (cnt - 1)
      UpdateScroller
      SfScroller.Value = cnt - 1
      MakeDirty
   End If
End Sub
Private Sub ctlDelete_Click()
   If Not m_MuteEvents Then
      Dim idx As Integer
      idx = SfScroller.Value
      m_Requests.Remove (idx)
      idx = idx - 1
      If idx = -1 Then
         idx = 0
      End If
   
      UpdateScroller
      DisplayRecord (idx)
      MakeDirty
   End If
End Sub

Private Sub ctlLoadingNames_Click()
   If Not m_MuteEvents Then
      Dim name As String
      name = ctlLoadingNames.List(ctlLoadingNames.ListIndex)
      m_CurrentRequest.LoadingName = name
      MakeDirty
   End If
End Sub

Private Sub ctlLoadingType_Click()
   If Not m_MuteEvents Then
      Dim idx As Integer
      idx = ctlLoadingType.ListIndex
      If idx = CInt(ltLoadGroup) Then
         m_CurrentRequest.LoadingType = ltLoadGroup
   '   ElseIf idx = CInt(ltLoadCase) Then
   '      m_CurrentRequest.LoadingType = ltLoadCase
   '   ElseIf idx = CInt(ltLoadCombination) Then
   '      m_CurrentRequest.LoadingType = ltLoadCombination
      Else
         MsgBox "Invalid loading type in UI - only load groups are currently supported"
      End If
   
      FillLoadingNamesForLoadingType (m_CurrentRequest.LoadingType)
      
      MakeDirty
   End If
End Sub

Private Sub ctlOrientation_Click()
   If Not m_MuteEvents Then
      Dim idx As Integer
      idx = ctlOrientation.ListIndex
      If idx = CInt(roGlobal) Then
         m_CurrentRequest.ResultsOrientation = roGlobal
      ElseIf idx = CInt(roMember) Then
         m_CurrentRequest.ResultsOrientation = roMember
      Else
         MsgBox "Invalid orientation type in UI"
      End If
      
      MakeDirty
   End If
End Sub
Private Sub ctlPOIs_Click()
   If Not m_MuteEvents Then
       Dim poiid As Integer
       poiid = ctlPOIs.List(ctlPOIs.ListIndex)
       m_CurrentRequest.poiid = poiid
      
       MakeDirty
       
      ' update poi coordinates
       FillPoiGrid
   End If
End Sub

Private Sub ctlStages_Click()
   If Not m_MuteEvents Then
      Dim name As String
      name = ctlStages.List(ctlStages.ListIndex)
      m_CurrentRequest.Stage = name
      
      MakeDirty
   End If
End Sub

Private Sub ctlSummation_Click()
   If Not m_MuteEvents Then
      Dim idx As Integer
      idx = ctlSummation.ListIndex
      If idx = CInt(rsCummulative) Then
         m_CurrentRequest.ResultsSummationType = rsCummulative
      ElseIf idx = CInt(rsIncremental) Then
         m_CurrentRequest.ResultsSummationType = rsIncremental
      Else
         MsgBox "Invalid summation type in UI"
      End If
      
      MakeDirty
   End If
End Sub
Private Sub Form_Load()
  ' first check model
  If m_Model.POIs.count = 0 Then
     MsgBox "Model has no POIs. You must have at least one POI to create a test"
     Unload Me
  End If
  
  If m_Model.stages.count = 0 Then
     MsgBox "Model has no Stages. You must have at least one Stage to create a test"
     Unload Me
  End If
  
  If m_Model.LoadGroups.count = 0 Then
     MsgBox "Model has no LoadGroups. You must have at least one LoadGroup to create a test"
     Unload Me
  End If
  
  ' load up combo boxes
  InitCtrls
  
  'set scroller
  SfScroller.Value = 0
  UpdateScroller
 
  ' set record if we have one
  If m_Requests.count = 0 Then
      EnableCtrls False
  Else
      EnableCtrls True
      DisplayRecord (0)
  End If
  
  ' not dirty yet
  m_Dirty = False
End Sub
Private Sub OKButton_Click()
   Unload Me
End Sub

Private Sub InitCtrls()
   m_MuteEvents = True
   ' stages
   Dim stages As stages
   Set stages = m_Model.stages
   Dim stg As Stage
   For Each stg In stages
      ctlStages.AddItem stg.name
   Next
   
   ' pois
   Dim POIs As POIs
   Set POIs = m_Model.POIs
   Dim poi As poi
   For Each poi In POIs
      ctlPOIs.AddItem CStr(poi.Id)
   Next
 
   ' labels in force grid
   ctlResultsGrid.Cols = 3
   ctlResultsGrid.Row = 0
   ctlResultsGrid.Col = 0
   ctlResultsGrid.Text = "Force"
   ctlResultsGrid.Row = 1
   ctlResultsGrid.Text = "Fx"
   ctlResultsGrid.Row = 2
   ctlResultsGrid.Text = "Fy"
   ctlResultsGrid.Row = 3
   ctlResultsGrid.Text = "Mz"
   ctlResultsGrid.Row = 0
   ctlResultsGrid.Col = 1
   ctlResultsGrid.Text = "Left"
   ctlResultsGrid.Col = 2
   ctlResultsGrid.Text = "Right"
   ctlResultsGrid.Enabled = False
   ctlResultsFrame.Enabled = False

   ' labels in deflection grid
   ctlDeflectionsGrid.Cols = 3
   ctlDeflectionsGrid.Row = 0
   ctlDeflectionsGrid.Col = 0
   ctlDeflectionsGrid.Text = "Deflection"
   ctlDeflectionsGrid.Row = 1
   ctlDeflectionsGrid.Text = "Dx"
   ctlDeflectionsGrid.Row = 2
   ctlDeflectionsGrid.Text = "Dy"
   ctlDeflectionsGrid.Row = 3
   ctlDeflectionsGrid.Text = "Rz"
   ctlDeflectionsGrid.Row = 0
   ctlDeflectionsGrid.Col = 1
   ctlDeflectionsGrid.Text = "Left"
   ctlDeflectionsGrid.Col = 2
   ctlDeflectionsGrid.Text = "Right"
   ctlDeflectionsGrid.Enabled = False
   ctlDeflectionsFrame.Enabled = False
   
   ' labels in Stress grid
   ctlStressGrid.Cols = 3
   ctlStressGrid.Row = 0
   ctlStressGrid.Col = 0
   ctlStressGrid.Text = "Stress Pt."
   ctlStressGrid.Col = 1
   ctlStressGrid.Text = "S Left"
   ctlStressGrid.Col = 2
   ctlStressGrid.Text = "S Right"
   ctlStressGrid.Enabled = False
   ctlStressFrame.Enabled = False
   
   ' labels in poi grid
   ctlPOIGrid.Cols = 2
   ctlPOIGrid.Row = 0
   ctlPOIGrid.Col = 0
   ctlPOIGrid.Text = "Coord"
   ctlPOIGrid.Row = 1
   ctlPOIGrid.Text = "X"
   ctlPOIGrid.Row = 2
   ctlPOIGrid.Text = "Y"
   ctlPOIGrid.Enabled = False
   ctlPOIFrame.Enabled = False

   m_MuteEvents = False
End Sub
Private Sub UpdateScroller()
   Dim scrlval As Integer
   If m_Requests.count > 0 Then
      SfScroller.Max = m_Requests.count - 1
      scrlval = SfScroller.Value + 1
   Else
      SfScroller.Max = 0
      scrlval = 0
   End If
   
   ctlRecords.Caption = "Record " + CStr(scrlval) + " of " + CStr(m_Requests.count)
   
End Sub

Private Sub EnableCtrls(enable As Boolean)
   ctlStages.Enabled = enable
   ctlPOIs.Enabled = enable
   ctlLoadingType.Enabled = enable
   ctlSummation.Enabled = enable
   ctlOrientation.Enabled = enable
   ctlLoadingNames.Enabled = enable
   
   ctlClone.Enabled = enable
   ctlDelete.Enabled = enable
   
   ctlPOIGrid.Enabled = enable
   ctlPOIFrame.Enabled = enable
End Sub
Private Sub SfScroller_Change()
   Dim idx As Integer
   idx = SfScroller.Value
   UpdateScroller
   DisplayRecord (idx)
End Sub
Private Sub MakeDirty()
   m_CurrentRequest.DeflectionResult = Nothing
   m_CurrentRequest.SectionForceResult = Nothing
   m_CurrentRequest.StressResults = Nothing
   ClearForceGrid
   ClearDeflectionsGrid
   ClearStressGrid
   m_Dirty = True
End Sub

