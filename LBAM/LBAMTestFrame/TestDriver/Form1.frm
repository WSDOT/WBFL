VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form Form1 
   Caption         =   "LBAM Model Tester"
   ClientHeight    =   7044
   ClientLeft      =   132
   ClientTop       =   708
   ClientWidth     =   8748
   LinkTopic       =   "Form1"
   ScaleHeight     =   7044
   ScaleWidth      =   8748
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ctlEditInfluenceRequests 
      Caption         =   "Edit InfluenceResultRequests"
      Height          =   492
      Left            =   4320
      TabIndex        =   25
      Top             =   6240
      Width           =   2292
   End
   Begin VB.Frame Frame2 
      Caption         =   "Analysis Type"
      Height          =   852
      Left            =   360
      TabIndex        =   22
      Top             =   1680
      Width           =   6492
      Begin VB.OptionButton ctlDeflectionModel 
         Caption         =   "Use Deflection Model"
         Height          =   252
         Left            =   240
         TabIndex        =   24
         Top             =   480
         Width           =   2652
      End
      Begin VB.OptionButton ctlForceModel 
         Caption         =   "Use Force Model"
         Height          =   252
         Left            =   240
         TabIndex        =   23
         Top             =   240
         Width           =   3012
      End
   End
   Begin VB.CheckBox ctlComputeStresses 
      Caption         =   "Compute Stresses"
      Height          =   252
      Left            =   6120
      TabIndex        =   21
      Top             =   4440
      Width           =   1572
   End
   Begin VB.CheckBox ctlComputeDeflections 
      Caption         =   "Compute Deflections"
      Height          =   252
      Left            =   6120
      TabIndex        =   20
      Top             =   3960
      Width           =   1812
   End
   Begin VB.CheckBox ctlComputeForces 
      Caption         =   "Compute Forces"
      Height          =   252
      Left            =   6120
      TabIndex        =   19
      Top             =   3480
      Width           =   1452
   End
   Begin VB.TextBox ctlStressMvt 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   2160
      TabIndex        =   17
      Text            =   "no test loaded"
      Top             =   4440
      Width           =   1572
   End
   Begin VB.TextBox ctlStressMpd 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   4320
      TabIndex        =   16
      Text            =   "no test loaded"
      Top             =   4440
      Width           =   1572
   End
   Begin VB.TextBox ctlDeflectionMvt 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   2160
      TabIndex        =   14
      Text            =   "no test loaded"
      Top             =   3960
      Width           =   1572
   End
   Begin VB.TextBox ctlDeflectionMpd 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   4320
      TabIndex        =   13
      Text            =   "no test loaded"
      Top             =   3960
      Width           =   1572
   End
   Begin VB.CommandButton ctlEditSectionForceRequests 
      Caption         =   "Edit SectionRequests"
      Height          =   492
      Left            =   4320
      TabIndex        =   11
      Top             =   5520
      Width           =   2292
   End
   Begin VB.TextBox ctlSectionForceMpd 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   4320
      TabIndex        =   8
      Text            =   "no test loaded"
      Top             =   3480
      Width           =   1572
   End
   Begin VB.TextBox ctlSectionForceMvt 
      Alignment       =   1  'Right Justify
      Height          =   288
      Left            =   2160
      TabIndex        =   7
      Text            =   "no test loaded"
      Top             =   3480
      Width           =   1572
   End
   Begin VB.TextBox ctlDescription 
      Height          =   612
      Left            =   600
      TabIndex        =   2
      Text            =   "No test loaded"
      Top             =   720
      Width           =   6012
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   7560
      Top             =   120
      _ExtentX        =   677
      _ExtentY        =   677
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Caption         =   "Description"
      Height          =   1092
      Left            =   360
      TabIndex        =   3
      Top             =   480
      Width           =   6492
   End
   Begin VB.Label ctlInfluenceRequestsText 
      Caption         =   "There are zero InfluenceResultsRequests in this Tester"
      Height          =   372
      Left            =   360
      TabIndex        =   26
      Top             =   6360
      Width           =   3612
   End
   Begin VB.Label Label8 
      Alignment       =   1  'Right Justify
      Caption         =   "Stresses:"
      Height          =   252
      Left            =   360
      TabIndex        =   18
      Top             =   4440
      Width           =   1212
   End
   Begin VB.Label Label7 
      Alignment       =   1  'Right Justify
      Caption         =   "Deflections"
      Height          =   252
      Left            =   360
      TabIndex        =   15
      Top             =   3960
      Width           =   1212
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000002&
      X1              =   0
      X2              =   7800
      Y1              =   0
      Y2              =   0
   End
   Begin VB.Label ctlSectionForceRequests 
      Caption         =   "There are zero SectionRequests in this Tester"
      Height          =   252
      Left            =   360
      TabIndex        =   12
      Top             =   5640
      Width           =   3852
   End
   Begin VB.Label Label6 
      Caption         =   "Test Requests"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   7.8
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   240
      TabIndex        =   10
      Top             =   5160
      Width           =   2292
   End
   Begin VB.Label Label5 
      Caption         =   "Tolerances"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   7.8
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   240
      TabIndex        =   9
      Top             =   3000
      Width           =   1212
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Forces:"
      Height          =   252
      Left            =   360
      TabIndex        =   4
      Top             =   3480
      Width           =   1212
   End
   Begin VB.Label Label4 
      Alignment       =   2  'Center
      Caption         =   "Min Percent Difference"
      Height          =   252
      Left            =   4080
      TabIndex        =   6
      Top             =   3120
      Width           =   2052
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "Min Value Tolerance"
      Height          =   252
      Left            =   1920
      TabIndex        =   5
      Top             =   3120
      Width           =   2052
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "File Name:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   7.8
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   0
      TabIndex        =   1
      Top             =   120
      Width           =   1212
   End
   Begin VB.Label ctlFileName 
      Caption         =   "No file is loaded"
      Height          =   252
      Left            =   1320
      TabIndex        =   0
      Top             =   120
      Width           =   7332
   End
   Begin VB.Menu File 
      Caption         =   "File"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "Open"
      End
      Begin VB.Menu mnuSave 
         Caption         =   "Save"
      End
      Begin VB.Menu mnuSaveAs 
         Caption         =   "Save As..."
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "Close"
      End
      Begin VB.Menu sep 
         Caption         =   "--------"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuNewFromModel 
         Caption         =   "New From LBAM Model"
      End
      Begin VB.Menu mnuExportLBAM 
         Caption         =   "Export to LBAM Model"
      End
      Begin VB.Menu mnuAttachLBAM 
         Caption         =   "Attach to LBAM Model"
      End
      Begin VB.Menu mnuImportResults 
         Caption         =   "Import Results from File"
      End
      Begin VB.Menu ctlSpace 
         Caption         =   "--------"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuExit 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu mnuAction 
      Caption         =   "Action"
      Begin VB.Menu mnuSeed 
         Caption         =   "Seed Test With Results"
      End
      Begin VB.Menu mnuRunComparison 
         Caption         =   "Run Comparison"
      End
      Begin VB.Menu mnuClearResults 
         Caption         =   "Clear All Results"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private m_TestFrameManager As New TestFrameManager
Private m_FileName As String
Private m_Enabled As Boolean
Private m_IsDirty As Boolean
Private Const m_NoFileMsg As String = "No File Loaded"

Private Sub ctlComputeDeflections_Click()
   If m_Enabled Then
      If ctlComputeDeflections.Value = Checked Then
         m_TestFrameManager.m_Tester.DoComputeDeflections = True
      Else
         m_TestFrameManager.m_Tester.DoComputeDeflections = False
      End If
      m_IsDirty = True
   End If
End Sub

Private Sub ctlComputeForces_Click()
   If m_Enabled Then
      If ctlComputeForces.Value = Checked Then
         m_TestFrameManager.m_Tester.DoComputeForces = True
      Else
         m_TestFrameManager.m_Tester.DoComputeForces = False
      End If
      m_IsDirty = True
   End If
End Sub

Private Sub ctlComputeStresses_Click()
   If m_Enabled Then
      If ctlComputeStresses.Value = Checked Then
         m_TestFrameManager.m_Tester.DoComputeStresses = True
      Else
         m_TestFrameManager.m_Tester.DoComputeStresses = False
      End If
      m_IsDirty = True
   End If
End Sub

Private Sub ctlEditInfluenceRequests_Click()
   Dim dlg As New IlrDialog
   Set dlg.m_Model = m_TestFrameManager.m_Tester.Model
   Set dlg.m_Requests = m_TestFrameManager.m_Tester.InfluenceResultRequests
   dlg.Show 1
   
   UpdateIfrDisplay
   
   'assimilate dirty flag from dialog
   m_IsDirty = dlg.m_Dirty

End Sub

Private Sub ctlEditSectionForceRequests_Click()
   Dim dlg As New SfrDialog
   Set dlg.m_Model = m_TestFrameManager.m_Tester.Model
   Set dlg.m_Requests = m_TestFrameManager.m_Tester.SectionResultRequests
   dlg.Show 1
   
   UpdateSfrDisplay
   
   'assimilate dirty flag from dialog
   m_IsDirty = dlg.m_Dirty

End Sub
Private Sub UpdateIfrDisplay()
   ' update caption
   Dim msg As String
   msg = "There are " + CStr(m_TestFrameManager.m_Tester.InfluenceResultRequests.count) + " InfluenceResultRequests in this Tester"
   ctlInfluenceRequestsText.Caption = msg
End Sub
Private Sub UpdateSfrDisplay()
   ' update caption
   Dim msg As String
   msg = "There are " + CStr(m_TestFrameManager.m_Tester.SectionResultRequests.count) + " SectionResultRequests in this Tester"
   ctlSectionForceRequests.Caption = msg
End Sub
Private Sub ctlForceModel_Click()
   m_TestFrameManager.m_Tester.AnalysisType = atForce
End Sub
Private Sub ctlDeflectionModel_Click()
   m_TestFrameManager.m_Tester.AnalysisType = atDeflection
End Sub

Private Sub Form_Unload(Cancel As Integer)
   If m_IsDirty Then
      If Not IsNothing(m_TestFrameManager.m_Tester) Then
         mnuSaveAs_Click
      End If
   End If
End Sub

Private Sub mnuAttachLBAM_Click()
   Attach_LBAM_Model_File (False)
End Sub

Private Sub mnuClearResults_Click()
   m_TestFrameManager.m_Tester.ClearResults
End Sub
Private Sub mnuExit_Click()
   Unload Me
End Sub

Private Sub mnuExportLBAM_Click()
   On Error GoTo ErrHandler
   ' Set filters.
   With CommonDialog1
      .Flags = cdlOFNFileMustExist + cdlOFNNoReadOnlyReturn
      .Filter = "All Files (*.*)|*.*|LBAM Model (XML) Files (*.xml)|*.xml"
      .FilterIndex = 2
      .DialogTitle = "Export LBAM Model As"
   End With

   ' Display the Open dialog box.
   CommonDialog1.ShowSave
   Dim filname As String
   filname = CommonDialog1.fileName

   Dim ss As New StructuredSave2
   ss.Open (filname)
   
   Dim sst As IStructuredStorage2
   Set sst = m_TestFrameManager.m_Tester.Model
   
   sst.Save ss
   ss.Close
   Exit Sub
   
ErrHandler:
' User pressed Cancel button.
   Exit Sub
   
End Sub

Private Sub mnuFileClose_Click()
   Set m_TestFrameManager.m_Tester = Nothing
   InitControls
   EnableControls False
   m_IsDirty = False
End Sub
Private Sub InitControls()
   ctlFileName.Caption = m_NoFileMsg
   ctlSectionForceMvt.Text = m_NoFileMsg
   ctlSectionForceMpd.Text = m_NoFileMsg
   ctlDeflectionMvt.Text = m_NoFileMsg
   ctlDeflectionMpd.Text = m_NoFileMsg
   ctlStressMvt.Text = m_NoFileMsg
   ctlStressMpd.Text = m_NoFileMsg
   ctlDescription.Text = m_NoFileMsg
End Sub
Private Sub EnableControls(enable As Boolean)
   m_Enabled = enable
   ctlEditSectionForceRequests.Enabled = enable
   ctlEditInfluenceRequests.Enabled = enable
   ctlSectionForceMvt.Enabled = enable
   ctlSectionForceMpd.Enabled = enable
   ctlDeflectionMvt.Enabled = enable
   ctlDeflectionMpd.Enabled = enable
   ctlStressMvt.Enabled = enable
   ctlStressMpd.Enabled = enable
   ctlDescription.Enabled = enable
   ctlComputeForces.Enabled = enable
   ctlComputeDeflections.Enabled = enable
   ctlComputeStresses.Enabled = enable
   ctlForceModel.Enabled = enable
   ctlDeflectionModel.Enabled = enable
   
   mnuSave.Enabled = enable
   mnuSaveAs.Enabled = enable
   mnuFileClose.Enabled = enable
   mnuExportLBAM.Enabled = enable
   mnuRunComparison.Enabled = enable
   mnuSeed.Enabled = enable
   mnuAttachLBAM.Enabled = enable
   mnuClearResults.Enabled = enable
   mnuImportResults.Enabled = enable
   
End Sub
Private Sub mnuFileOpen_Click()

   ' CancelError is True.
   On Error GoTo ErrHandler
   With CommonDialog1
      ' Set filters.
      .Flags = cdlOFNFileMustExist + cdlOFNReadOnly
      .Filter = "All Files (*.*)|*.*|Test (XML) Files (*.xml)|*.xml"
      ' Specify default filter.
      .FilterIndex = 2
      .DialogTitle = "Open Test File"
   End With

   ' Display the Open dialog box.
   CommonDialog1.ShowOpen
   ' Call the open file procedure.
   
   Me.MousePointer = vbHourglass
   
   If Not CommonDialog1.fileName = "" Then
      OpenFile (CommonDialog1.fileName)
      
      EnableControls True
      ctlFileName.Caption = CommonDialog1.fileName
      UpdateModelView
      m_IsDirty = False
   End If
   
   Me.MousePointer = vbDefault
   
   Exit Sub

ErrHandler:
' User pressed Cancel button.
   Me.MousePointer = vbDefault
   Exit Sub
   
End Sub

Private Sub OpenFile(fileName As String)
   On Error GoTo ErrHandler

   Dim iload As New StructuredLoad2
   iload.Open (fileName)
   
   Dim tester As New LBAMTester
   Dim iss2 As IStructuredStorage2
   Set iss2 = tester
   iss2.Load iload

   Set m_TestFrameManager.m_Tester = tester
   m_IsDirty = False
   Exit Sub

ErrHandler:
   MsgBox "An Error Occured Opening or Loading the file"
   Exit Sub
   
End Sub
Private Sub Attach_LBAM_Model_File(doCreateNew As Boolean)

   On Error GoTo ErrHandler
   ' Set filters.
   CommonDialog1.Filter = "All Files (*.*)|*.*|LBAM Model (XML) Files (*.xml)|*.xml"
   ' Specify default filter.
   CommonDialog1.FilterIndex = 2
   CommonDialog1.DialogTitle = "Select LBAM File to attach Test to"

   ' Display the Open dialog box.
   CommonDialog1.ShowOpen
   ' Call the open file procedure.
   If Not CommonDialog1.fileName = "" Then
   
      Me.MousePointer = vbHourglass
   
      If doCreateNew Then
         ctlFileName.Caption = "Untitled"
      ' create tester and load model file into it
         Dim tester As New LBAMTester
         Set m_TestFrameManager.m_Tester = tester
      End If
      
      m_TestFrameManager.m_Tester.AttachToModelFile (CommonDialog1.fileName)
      m_IsDirty = True

      EnableControls True

      UpdateModelView
      Me.MousePointer = vbDefault
      
   End If
   
   Exit Sub

ErrHandler:
' User pressed Cancel button.
   Exit Sub

End Sub
Private Sub ctlDescription_Validate(Cancel As Boolean)
   m_TestFrameManager.m_Tester.Description = ctlDescription.Text
   m_IsDirty = True
End Sub
Private Sub ctlSectionForceMpd_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlSectionForceMpd.Text)
      m_TestFrameManager.m_Tester.ForceMinPercentDiff = val / 100
      m_IsDirty = True
   End If
End Sub
Private Sub ctlSectionForceMvt_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlSectionForceMvt.Text)
      m_TestFrameManager.m_Tester.ForceMinTolerance = val
      m_IsDirty = True
   End If
End Sub
Private Sub ctlDeflectionMpd_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlDeflectionMpd.Text)
      m_TestFrameManager.m_Tester.DeflectionMinPercentDiff = val / 100
      m_IsDirty = True
   End If
End Sub
Private Sub ctlDeflectionMvt_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlDeflectionMvt.Text)
      m_TestFrameManager.m_Tester.DeflectionMinTolerance = val
      m_IsDirty = True
   End If
End Sub
Private Sub ctlStressMpd_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlStressMpd.Text)
      m_TestFrameManager.m_Tester.StressMinPercentDiff = val / 100
      m_IsDirty = True
   End If
End Sub
Private Sub ctlStressMvt_Validate(Cancel As Boolean)
   If m_Enabled Then
      Dim val As Double
      val = CDbl(ctlStressMvt.Text)
      m_TestFrameManager.m_Tester.StressMinTolerance = val
      m_IsDirty = True
   End If
End Sub
Private Sub Form_Load()
   m_FileName = "Untitled"
   InitControls
   EnableControls False
   m_IsDirty = False
End Sub

Private Sub mnuImportResults_Click()
   On Error GoTo ErrHandler
   ' Set filters.
   CommonDialog1.Filter = "All Files (*.*)|*.*|LBAM Model (XML) Files (*.xml)|*.xml"
   ' Specify default filter.
   CommonDialog1.FilterIndex = 2
   CommonDialog1.DialogTitle = "Select LBAM File to attach Test to"

   ' Display the Open dialog box.
   CommonDialog1.ShowOpen
   ' Call the open file procedure.
   If Not CommonDialog1.fileName = "" Then
   
      Me.MousePointer = vbHourglass
      
      Dim fn As String
      fn = CommonDialog1.fileName
   
      m_TestFrameManager.m_Tester.ImportResultsFromFile fn
      m_IsDirty = True

      EnableControls True

      UpdateModelView
      Me.MousePointer = vbDefault

   End If

   Exit Sub

ErrHandler:
' User pressed Cancel button.
   Exit Sub

End Sub

Private Sub mnuNewFromModel_Click()
   
   Attach_LBAM_Model_File (True)
   
End Sub
Private Sub UpdateModelView()
   ctlSectionForceMvt.Text = m_TestFrameManager.m_Tester.ForceMinTolerance
   ctlSectionForceMpd.Text = m_TestFrameManager.m_Tester.ForceMinPercentDiff * 100
   ctlDeflectionMvt.Text = m_TestFrameManager.m_Tester.DeflectionMinTolerance
   ctlDeflectionMpd.Text = m_TestFrameManager.m_Tester.DeflectionMinPercentDiff * 100
   ctlStressMvt.Text = m_TestFrameManager.m_Tester.StressMinTolerance
   ctlStressMpd.Text = m_TestFrameManager.m_Tester.StressMinPercentDiff * 100
   ctlDescription.Text = m_TestFrameManager.m_Tester.Description
   
   If m_TestFrameManager.m_Tester.AnalysisType = atForce Then
      ctlForceModel.Value = Checked
   Else
      ctlDeflectionModel.Value = Checked
   End If
   
   If m_TestFrameManager.m_Tester.DoComputeForces Then
      ctlComputeForces.Value = Checked
   Else
      ctlComputeForces.Value = Unchecked
   End If
   
   If m_TestFrameManager.m_Tester.DoComputeDeflections Then
   ctlComputeDeflections.Value = Checked
   Else
   ctlComputeDeflections.Value = Unchecked
   End If
   
   If m_TestFrameManager.m_Tester.DoComputeStresses Then
      ctlComputeStresses.Value = Checked
   Else
      ctlComputeStresses.Value = Unchecked
   End If
   
   UpdateSfrDisplay
   UpdateIfrDisplay
End Sub

Private Sub mnuRunComparison_Click()

   ' prompt for name of log file
   With CommonDialog1
      .fileName = "log.txt"
      .Flags = cdlOFNFileMustExist + cdlOFNNoReadOnlyReturn
      .Filter = "All Files (*.*)|*.*|Text Files (*.txt)|*.txt"
      .FilterIndex = 2
      .DialogTitle = "Select Log File"
   End With

   ' Display the Open dialog box.
   CommonDialog1.ShowSave
   Dim filname As String
   filname = CommonDialog1.fileName

   Me.MousePointer = vbHourglass

   ' open log file
   Dim tl As New FileTestLogger
   tl.Open (filname)
   
   m_TestFrameManager.m_Tester.ValidateResults tl

   tl.Close
     
   Me.MousePointer = vbDefault
   
   MsgBox "Completed. " + CStr(tl.TotalTests) + " test were run. " + CStr(tl.TotalFails) + " Failed."
   
End Sub

Private Sub mnuSave_Click()
   mnuSaveAs_Click
End Sub

Private Sub mnuSaveAs_Click()

   If IsNothing(m_TestFrameManager.m_Tester) Then
      MsgBox "Cannot save null Tester - you must first attach a model or load a file"
      Exit Sub
   End If

   On Error GoTo ErrHandler
   ' Set filters.
   With CommonDialog1
      .fileName = ctlFileName.Caption
      .Flags = cdlOFNFileMustExist + cdlOFNNoReadOnlyReturn
      .Filter = "All Files (*.*)|*.*|LBAM Tester (XML) Files (*.xml)|*.xml"
      .FilterIndex = 2
      .DialogTitle = "Save Tester As"
   End With
   
   ' Display the Open dialog box.
   CommonDialog1.ShowSave
   Dim filname As String
   filname = CommonDialog1.fileName

   Dim ss As New StructuredSave2
   ss.Open (filname)
   
   Dim sst As IStructuredStorage2
   Set sst = m_TestFrameManager.m_Tester
   
   sst.Save ss
   ss.Close
   
   ctlFileName.Caption = filname
   m_IsDirty = False
   
   Exit Sub

ErrHandler:
' User pressed Cancel button.
   Exit Sub

End Sub

Private Sub mnuSeed_Click()
   ' create test data
   Dim lgs As New LoadGroupForceResponse
      
   Me.MousePointer = vbHourglass
     
   m_TestFrameManager.m_Tester.FillResults
  
   Me.MousePointer = vbDefault
   
   m_IsDirty = True
End Sub
