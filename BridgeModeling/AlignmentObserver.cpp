#include <BridgeModeling\BridgeModelingLib.h>
#include "AlignmentObserver.h"
#include <BridgeModeling\Bridge.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void bmfAlignmentObserver::FinalRelease()
{
   if ( m_pBridge )
   {
      ReleaseBridge();
   }
}

void bmfAlignmentObserver::SetBridge(bmfBridge* pBridge)
{
   m_pBridge = pBridge;

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   HRESULT hr;
   hr = AtlAdvise(alignment,this,IID_IPathEvents,&m_dwCookie);
   ATLASSERT( SUCCEEDED(hr) );
}

void bmfAlignmentObserver::ReleaseBridge()
{
   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   HRESULT hr;
   hr = AtlUnadvise(alignment,IID_IPathEvents,m_dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   m_pBridge = 0;
}

STDMETHODIMP bmfAlignmentObserver::OnPathChanged(IPath* path)
{
   m_pBridge->OnAlignmentChanged();
   return S_OK;
}

STDMETHODIMP bmfAlignmentObserver::OnProfileChanged(IProfile* profile)
{
   return S_OK;
}
