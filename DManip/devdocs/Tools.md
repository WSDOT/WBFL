# Tools {#tools}
A tool is an interface element that resides in a tool palette. A tool is typically dragged and dropped onto the Display View or a Display Object. When the tool is dropped, some action is taken by your application.

In the context of a finite element program, there could be a Concentrated Load tool. This tool would be dragged from the tool palette and dropped on a beam member. When the drop occurs the application could add the load to the member.

# Creating Tools
Creating tools is a fairly simple process. A tool is simply a control on a MFC Dialog Bar with an associated Tool object. Tools are typically Icon resources on the dialog bar. The control ID identifies the tool. You can mix and match "Tools" and other dialog resources on a Tool Palette. For example, you can have a couple of tools and then a Combo Box and a push button.

To add a tool palette and tools to your application

1. Create a MFC Dialog Bar and add it to your application. The dialog bar is typically created in the OnCreate method of the CMainFrame class. Refer to the MFC documentation for details on creating dialog bars.
2. Create Tool objects and associate them with the tool palette. Create a Tool object for each of your tools, set its ID and ToolTipText properties, and then call AddTool on CToolPalette. An example is given below.

~~~
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

    // m_wndToolPallete is a CToolPalette object. CToolPalette inherits from CDialogBar
    // IDD_TOOLS is the dialog resource, with some icons for tools
    if ( !m_wndToolPalette.Create(this,IDD_TOOLS, CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR) )
    {
        TRACE0("Failed to create tool palette\n");
        return -1; // fail to create
    }

   // IDC_TOOL is the control id for the icon on the toolbar
   auto tool = WBFL::DManip::Tool::Create(IDC_TOOL);
   tool->SetToolTipText("My Tool");
   m_wndToolPalette.AddTool(tool);

   return 0;
}
~~~