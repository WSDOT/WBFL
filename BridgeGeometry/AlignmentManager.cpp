#include "StdAfx.h"
#include <BridgeGeometry\AlignmentManager.h>
#include "AlignmentDescriptionDlg.h"

CAlignmentManager::CAlignmentManager(void)
{
}

CAlignmentManager::~CAlignmentManager(void)
{
}

bool CAlignmentManager::EditAlignment()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   CAlignmentDescriptionDlg dlg(_T("Alignment"));
   
   // TODO: replace with actual aligment data
   CAlignmentDescription alignment = GetAlignmentDescription(0);
   dlg.m_AlignmentPage.m_Direction = alignment.GetInitialDirection();

   if ( dlg.DoModal() == IDOK )
   {
      alignment.SetInitialDirection(dlg.m_AlignmentPage.m_Direction);
      SetAlignmentDescription(0,alignment);
      return true;
   }

   return false;
}

Uint32 CAlignmentManager::GetAlignmentCount()
{
   return m_AlignmentDescriptions.size();
}

Uint32 CAlignmentManager::GetAlignmentIndex(Int32 alignmentID)
{
   Uint32 idx = 0;
   AlignmentDescContainer::iterator iter;
   for ( iter = m_AlignmentDescriptions.begin(); iter != m_AlignmentDescriptions.end(); iter++, idx++ )
   {
      if ( iter->first == alignmentID )
         return idx;
   }

   return INVALID_INDEX;
}

Int32 CAlignmentManager::GetAlignmentID(Uint32 alignmentIdx)
{
   ATLASSERT( alignmentIdx < m_AlignmentDescriptions.size() && alignmentIdx != INVALID_INDEX );
   AlignmentDescContainer::iterator iter = m_AlignmentDescriptions.begin();
   for ( Uint32 idx = 0; idx < alignmentIdx; idx++ )
   {
      iter++;
   }

   return iter->first;
}

void CAlignmentManager::SetAlignmentDescription(Int32 alignmentID,const CAlignmentDescription& alignmentDesc)
{
   m_AlignmentDescriptions[alignmentID] = alignmentDesc;
}

CAlignmentDescription CAlignmentManager::GetAlignmentDescription(Int32 alignmentID)
{
   return m_AlignmentDescriptions[alignmentID];
}
