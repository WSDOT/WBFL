UI Integration {#WBFL_EAF_UIIntegration}
==========================================
An Agent (or Extension Agent) integrates with the application's user interface by implementing
`WBFL::EAF::IAgentUIIntegration` and, in its `IntegrateWithUI(bool bIntegrate)` override, registering
and unregistering with the broker interfaces described on this page. All of them are reached the
usual way, e.g. `GET_IFACE(IEAFMainMenu, pMainMenu);`.

## Receiving command notifications

### The command ID collision problem
Windows/MFC command routing needs every command - menu item, toolbar button, accelerator key - to
have a unique numeric ID within the application. Independently-developed extension agents can't
coordinate with each other on that: two different vendors' `.rc` resource files can easily both
define, say, `ID_COMMAND1 = 32771`. The EAF framework resolves this for you, so an extension agent
can freely use whatever local command IDs its own resource file happens to define, without needing
to know or care what any other agent picked.

`WBFL::EAF::PluginCommandManager` (`Include\EAF\PluginCommandManager.h`) is the piece that makes this
work. Once, at startup, the *host* document/app reserves a block of IDs for plug-in use -
`GET_IFACE`-style code in an extension agent never does this itself:
~~~
UINT nCommands = GetPluginCommandManager()->ReserveCommandIDRange(256);
~~~
From then on, every time an extension agent registers a menu item, toolbar button, or accelerator
key - via `Menu::AppendMenu`/`LoadMenu`, `ToolBar::LoadToolBar`/`AddButtons`/`InsertButton`,
`AcceleratorTable::AddAccelKey`/`AddAccelTable` - and hands in its own local ID, the framework mints a
fresh, globally-unique ID from that reserved block and substitutes it into the live menu/toolbar/
accelerator structure. Windows and MFC only ever see the unique ID; your local ID never has to be
unique across the whole application, only within your own resource file.

When the user actually invokes the command, MFC's routing fires with that unique ID.
`CEAFDocument::OnCmdMsg`/`CEAFApp::OnCmdMsg` look it up, translate it back to your original local ID,
and *that's* the value handed to your `ICommandCallback::OnCommandMessage` below - not the unique
one. This is why an ordinary message map using your own local command constants just works, with no
special handling needed on your part (see the `ICommandCallback` section immediately below).

### `ICommandCallback`
Every menu item, toolbar button, and accelerator key registered below takes a `callback` parameter -
this is how a click or key press actually reaches your code. Menus, toolbars, and accelerator keys
all route through the same mechanism: `WBFL::EAF::ICommandCallback` (`Include\EAF\EAFUIIntegration.h`):
~~~
class ICommandCallback
{
public:
   virtual BOOL OnCommandMessage(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) = 0;
   virtual BOOL GetStatusBarMessageString(UINT nID, CString& rMessage) const = 0;
   virtual BOOL GetToolTipMessageString(UINT nID, CString& rMessage) const = 0;
};
~~~
Your agent class implements this alongside deriving from MFC's `CCmdTarget`, and passes itself as the
`callback` argument everywhere below:
~~~
auto callback = std::dynamic_pointer_cast<WBFL::EAF::ICommandCallback>(shared_from_this());
~~~
`OnCommandMessage` is called by the framework whenever one of your registered commands is invoked.
The standard implementation just forwards to `CCmdTarget::OnCmdMsg`, which puts you back on familiar
ground - an ordinary MFC message map on your agent class handles the actual command:
~~~
BOOL CMyAgent::OnCommandMessage(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
   return OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BEGIN_MESSAGE_MAP(CMyAgent, CCmdTarget)
   ON_COMMAND(ID_COMMAND1, &CMyAgent::OnCommand1)
END_MESSAGE_MAP()
~~~
`GetStatusBarMessageString`/`GetToolTipMessageString` are called by the framework to populate the
status bar prompt and toolbar tooltip for a command ID - the usual implementation just loads the
standard MFC command string resource and splits it on `\n` (status bar prompt before, tooltip after),
same as MFC's own `ON_COMMAND` string resource convention:
~~~
BOOL CMyAgent::GetStatusBarMessageString(UINT nID, CString& rMessage) const
{
   if (rMessage.LoadString(nID))
      rMessage.Replace('\n', '\0');
   return TRUE;
}

BOOL CMyAgent::GetToolTipMessageString(UINT nID, CString& rMessage) const
{
   CString str;
   if (str.LoadString(nID))
   {
      int pos = str.Find('\n');
      if (0 < pos)
         rMessage = str.Mid(pos + 1);
   }
   return TRUE;
}
~~~

## Menus
`IEAFMainMenu` (`Include\EAF\EAFUIIntegration.h`) has two methods - `GetMainMenu()` and
`CreateContextMenu()` - both returning a `WBFL::EAF::Menu` (`Include\EAF\Menu.h`), which is where the
actual work happens.

**Adding commands to an existing menu.** Locate the target (sub)menu by caption with
`FindMenuItem`, then splice in with `InsertMenu`/`AppendMenu` (or remove with `RemoveMenu`):
~~~
auto pMainMenu = pFrame->GetMainMenu();
UINT filePos = pMainMenu->FindMenuItem(_T("&File"));
auto pFileMenu = pMainMenu->GetSubMenu(filePos);
UINT managePos = pFileMenu->FindMenuItem(_T("Manage"));
auto pManageMenu = pFileMenu->GetSubMenu(managePos);
pManageMenu->AppendMenu(ID_MANAGE_PLUGINS, _T("Manage Plugins and Extensions..."), callback);
~~~
This is also how a menu can be made conditional on document type - a real caller reads which kind of
document is open and calls `DeleteButton`/`RemoveMenu` for items that don't apply before showing the
menu.

**Adding a new top-level menu.** `Menu::CreatePopupMenu(pos, name)` on the main menu creates a new
drop-down at a given position, then `LoadMenu` fills it from an `.rc` menu resource:
~~~
UINT nMenus = pMenu->GetMenuItemCount();
m_MyMenu = pMenu->CreatePopupMenu(nMenus - 1, _T("MyExtension")); // before the last menu (Help)
m_MyMenu->LoadMenu(IDR_MENU, callback);
~~~

**Context menus.** `IEAFMainMenu::CreateContextMenu()` returns a fresh `Menu` to build up the same
way (`LoadMenu`/`AppendMenu`) and show with `TrackPopupMenu`.

## Toolbars
`IEAFToolbars` creates, fetches, and destroys `WBFL::EAF::ToolBar` objects (`Include\EAF\ToolBar.h`).
There's no separate method for "add to an existing toolbar" versus "add to a new one" - `GetToolBar`
returns a handle to *any* toolbar, including the application's own standard ones if you know its ID,
and the same `LoadToolBar`/`AddButtons`/`InsertButton` methods work on it either way:
~~~
// a brand new toolbar
m_ToolBarID = pToolBars->CreateToolBar(_T("Extension Agent Toolbar"));
auto pToolBar = pToolBars->GetToolBar(m_ToolBarID);
pToolBar->LoadToolBar(IDR_TOOLBAR, callback);

// adding to an existing one
GET_IFACE(IEditByUI, pEditUI);
UINT stdID = pEditUI->GetStdToolBarID();
auto pStdToolBar = pToolBars->GetToolBar(stdID);
pStdToolBar->InsertButton(-1, cmdID, -1, _T("Extension Command"), callback);
~~~

## Accelerator Keys
`IEAFAcceleratorTable` (`Include\EAF\EAFUIIntegration.h`) has `AddAccelTable`, `AddAccelKey`, and two
`RemoveAccelKey` overloads. It's implemented by `CEAFDocProxyAgent`, a core agent that's always
present, so it's reliably reachable from any broker-based code:
~~~
GET_IFACE(IEAFAcceleratorTable, pAccelTable);
pAccelTable->AddAccelKey(FCONTROL | FVIRTKEY, VK_U, ID_UPDATE_TEMPLATE, callback);
~~~
This is the right path for **Agent-level code**, which has broker access. Code that runs before any
document/broker exists - an `IPluginApp` at application startup, or in response to an app-wide
plugin-enable/disable toggle spanning zero or more open documents - has no broker to reach through,
and correctly goes straight to the single, application-wide accelerator table instead:
~~~
CEAFMainFrame* pFrame = EAFGetMainFrame();
pFrame->GetAcceleratorTable()->AddAccelKey(FALT | FCONTROL | FVIRTKEY, VK_U, ID_UPDATE_TEMPLATE, callback);
~~~
Both are the same underlying `WBFL::EAF::AcceleratorTable` object - `IEAFAcceleratorTable` is simply
the broker-reachable front door to it for code that has one.

## Views
`IEAFViewRegistrar::RegisterView(nResourceID, callback, pFrameClass, pViewClass, hSharedMenu, maxViewCount)`
registers a custom `CView`/`CFrameWnd` pair, returning a key used with `CreateView`/`RemoveView`/
`UpdateRegisteredView`/`GetRegisteredView`:
~~~
GET_IFACE(IEAFViewRegistrar, pViewRegistrar);
m_MyViewKey = pViewRegistrar->RegisterView(IDR_MENU, callback,
   RUNTIME_CLASS(CEAFOutputChildFrame), RUNTIME_CLASS(CMyView), nullptr, maxViewCount);
...
pViewRegistrar->CreateView(m_MyViewKey, pCreateData); // pCreateData is your own struct, passed through as void*
~~~
The same logical view can vary its frame/view class pair by document type - a real caller picks
between two different `RUNTIME_CLASS` pairs for the "same" view depending on which document type is
asking, at registration time.

A related but distinct interface is `IEAFViewController` (`Include\EAF\EAFViewController.h`) -
obtained via `CEAFViewControllerFactory::GetViewController`, not registered with the broker. Where
`IEAFViewRegistrar` registers a view *type* and creates instances of it, `IEAFViewController` controls
one already-open view instance (`IsOpen`, `Close`, `Minimize`, `Maximize`, `Restore`) - useful for a
scripting or automation caller that needs to manipulate a view that's already on screen.
