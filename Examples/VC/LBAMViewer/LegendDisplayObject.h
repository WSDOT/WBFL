#pragma once

#include <DManip\DisplayObjectDefaultImpl.h>
#include <DManip\Draggable.h>
#include "LegendMessageCatcher.h"
#include "Legend.h"

#include <memory>

static const int CMENU_BASE = 100;

class CLegendDisplayObject : 
   public WBFL::DManip::LegendDisplayObject,
   public iMessageListener
{
private:
   CLegendDisplayObject(IDType id) : WBFL::DManip::LegendDisplayObject(id) {}

public:
   static std::shared_ptr<CLegendDisplayObject> Create(IDType id = INVALID_ID) { return std::shared_ptr<CLegendDisplayObject>(new CLegendDisplayObject(id)); }


   // iDisplayObject overrides
   bool OnRButtonDown(UINT nFlags, const POINT& point) override
   {
      if(!WBFL::DManip::LegendDisplayObject::OnRButtonDown(nFlags,point))
      {
         auto pDL = GetDisplayList();
         auto dispMgr = pDL->GetDisplayMgr();
         CDisplayView* view = dispMgr->GetView();

         POINT screen_point = point;
         view->ClientToScreen(&screen_point);

         RowIndexType nrows = max(GetEntryCount(), GetNumRows());

         CMenu menu;
         menu.CreatePopupMenu();
         menu.AppendMenu(MF_STRING | MF_DISABLED, 0, _T("Select Number of Rows"));

         for (RowIndexType it = 1; it <= nrows; it++)
         {
            CString str;
            str.Format(_T("%d"), it);
            UINT iFlags = MF_STRING | MF_ENABLED;
            menu.AppendMenu(iFlags, CMENU_BASE + it, str);
         }

         // need to create a new window in this gui thread in order to catch menu
         // messages
         m_pMessageCatcher = std::make_unique<CLegendMessageCatcher>(this);
         m_pMessageCatcher->Create(nullptr, _T("MessageCatcher\0"), WS_DISABLED, CRect(), view, 0);

         menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, m_pMessageCatcher.get());

         return true;
      }

      return false;
   }

   // iMessageListener
   void OnCaughtMessage(int nrows) override
   {
      auto pDL = GetDisplayList();
      auto dispMgr = pDL->GetDisplayMgr();
      CDisplayView* view = dispMgr->GetView();
      CDManipClientDC dc(view);

      SetNumRows(nrows);

      m_pMessageCatcher->DestroyWindow();
   }

   std::unique_ptr<CLegendMessageCatcher> m_pMessageCatcher;
};
