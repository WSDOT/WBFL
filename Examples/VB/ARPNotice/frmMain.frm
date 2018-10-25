VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "ARP Notice Example"
   ClientHeight    =   2565
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   3735
   LinkTopic       =   "ARP Notice Example"
   ScaleHeight     =   2565
   ScaleWidth      =   3735
   StartUpPosition =   3  'Windows Default
   Begin VB.Menu Help 
      Caption         =   "Help"
      Index           =   1
      Begin VB.Menu mnuLegalNotice 
         Caption         =   "Legal Notice"
         Index           =   2
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private arpNotice As New WBFLTools.arpNotice
Private bShowAgain As Boolean

Private Sub Form_Load()
   bShowAgain = GetSetting("ARPNotice", "StartUp", "ShowLegal", "True")
   'bShowAgain = True 'In a real application, you would read this from the registry
   arpNotice.ShowAgain = bShowAgain
   If (arpNotice.ShowAgain) Then
      If (arpNotice.Show(True, ltAROSL) = ltReject) Then
         End
      End If
   End If
   bShowAgain = arpNotice.ShowAgain
End Sub

Private Sub Form_Unload(Cancel As Integer)
 'In a real application, you would save bShowAgain to the registry
 SaveSetting "ARPNotice", "Startup", "ShowLegal", CStr(bShowAgain)
End Sub

Private Sub mnuLegalNotice_Click(Index As Integer)
   arpNotice.ShowAgain = bShowAgain
   arpNotice.Show False, ltARLOSL
   bShowAgain = arpNotice.ShowAgain
End Sub
