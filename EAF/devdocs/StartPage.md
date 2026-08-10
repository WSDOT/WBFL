Start Page {#WBFL_EAF_StartPage}
==========================================
`CEAFMainFrame` can show a "start page" - a special MDI child window displayed when the application
has no document open. EAF supplies the lifecycle for this (creating, showing, hiding, resizing, and
destroying the window) but supplies no content of its own: by default, an application built on EAF
has no start page at all. Content is supplied by overriding a single hook on your application's own
`CEAFMainFrame`-derived main frame class.

## Supplying start page content
`CEAFMainFrame::CreateStartPage()` (`Include\EAF\EAFMainFrame.h`) is the hook:
~~~
virtual std::shared_ptr<CEAFStartPageWnd> CreateStartPage();
~~~
It is `protected` and `virtual` - override it in your `CEAFMainFrame`-derived main frame class and
return a `shared_ptr` to a `CEAFStartPageWnd`-derived window, or `nullptr` if your application has no
start page. The base implementation simply returns `nullptr`.

Construct the window, but don't call `Create()` on it yourself - the framework does that for you
after your override returns, as part of `ShowStartPage()` (see below).

`CEAFStartPageWnd` (`Include\EAF\EAFStartPageWnd.h`) is the base class to derive your start page
window from:
~~~
class CMyStartPageWnd : public CEAFStartPageWnd
{
   // populate the window's contents, e.g. in OnCreate/PreCreateWindow
};

std::shared_ptr<CEAFStartPageWnd> CMyMainFrame::CreateStartPage()
{
   return std::make_shared<CMyStartPageWnd>();
}
~~~

## Lifecycle
The remaining five members are owned by the framework and are not overridable - none of them is
`virtual`:

- `ShowStartPage()` - the first time it's called, calls your `CreateStartPage()` override, `Create()`s
  the returned window as an MDI child, and calls `ResizeStartPage()`. On later calls, if the window
  already exists, it's simply un-hidden.
- `HideStartPage()` - hides the start page window, unless `KeepStartPageOpen(TRUE)` has been set.
- `KeepStartPageOpen(BOOL)` / `KeepStartPageOpen() const` - get/set whether `HideStartPage()` should
  actually hide the window, e.g. to support a user preference that keeps the start page visible
  alongside open documents.
- `ResizeStartPage()` - lays out the start page window within the main frame's client area.
- `DestroyStartPage()` - closes and releases the start page window.

`CreateStartPage()` is the only member of this group meant to be overridden.
