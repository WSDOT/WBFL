///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <DManip/EditableStationTextBlock.h>
#include <DManip/EditableTextBlock.h>
#include <DManip/InplaceEditCtrl.h>
#include <DManip/DisplayMgr.h>


using namespace WBFL::DManip;

EditableStationTextBlock::EditableStationTextBlock(IDType id) : iTextBlock(id)
{
   m_EditableTextBlock = EditableTextBlock::Create();
   m_EditableTextBlock->SetFormat(EditableTextBlock::Format::Text);
}

void EditableStationTextBlock::Init()
{
   m_EventRelay = NestedDisplayObjectEventRelay::Create(this);
   m_EditableTextBlock->RegisterEventSink(m_EventRelay);

   SetText(AsString().c_str());
}

std::_tstring EditableStationTextBlock::AsString() const
{
   return m_Station.AsString(m_StationFormat);
}

std::shared_ptr<EditableStationTextBlock> EditableStationTextBlock::Create(IDType id)
{ 
   auto me = std::shared_ptr<EditableStationTextBlock>(new EditableStationTextBlock(id)); 
   me->Init();
   return me;
}

std::shared_ptr<EditableStationTextBlock> EditableStationTextBlock::Create(const WBFL::Units::StationFormat& stationFormat, IDType id)
{
   auto me = std::shared_ptr<EditableStationTextBlock>(new EditableStationTextBlock(id));
   me->SetStationFormat(stationFormat);
   me->Init();
   return me;
}

void EditableStationTextBlock::SetStationFormat(const WBFL::Units::StationFormat& stationFormat)
{
   m_StationFormat = stationFormat;
   SetText(AsString().c_str());
}

const WBFL::Units::StationFormat& EditableStationTextBlock::GetStationFormat() const
{
   return m_StationFormat;
}

void EditableStationTextBlock::CreateEditControl()
{
   auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
   ipedit->CreateEditControl();

   // Replace the text in the edit control with the value in display units, without
   // the unit tag...
   CInplaceEdit* pEdit = GetEditObject();

   // Make sure text is right justified
   pEdit->ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);
}

void EditableStationTextBlock::DestroyEditControl()
{
   auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
   ipedit->DestroyEditControl();
}

bool EditableStationTextBlock::ValidateData()
{
   try
   {
      // use a temporary object because we don't want to alter m_Station
      WBFL::COGO::Station station;
      station.FromString(std::_tstring(m_EditableTextBlock->GetText()),m_StationFormat);
   }
   catch (...)
   {
      return false;
   }
   return true;
}

void EditableStationTextBlock::OnDataChanged()
{
   auto ipedit = std::dynamic_pointer_cast<iInplaceEditable>(m_EditableTextBlock);
   ipedit->OnDataChanged();
}

bool EditableStationTextBlock::OnLButtonDown(UINT nFlags, const POINT& point)
{
   // Confirm this point is really over the text block
   // Text blocks are often aggregated with other objects. The
   // LButtonDown event could have occurred over the other display object
   // and been forwarded here. The edit task should not begin if
   // the mouse was not pressed over the text.
   auto map = m_EditableTextBlock->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   auto p = map->LPtoWP(point.x, point.y);

   // Hit test the text block
   if (HitTest(point))
   {
      DoInplaceEdit();
      return true;
   }
   else
   {
      return false;
   }
}

void EditableStationTextBlock::SetText(LPCTSTR lpszText)
{
   m_EditableTextBlock->SetText(lpszText);
}

CString EditableStationTextBlock::GetText() const
{
   return AsString().c_str();
}

void EditableStationTextBlock::SetStation(const WBFL::COGO::Station& station)
{
   m_Station = station;
   SetText(AsString().c_str());
}

const WBFL::COGO::Station& EditableStationTextBlock::GetStation() const
{
   return m_Station;
}

WBFL::COGO::Station EditableStationTextBlock::GetEditedStation() const
{
   WBFL::COGO::Station editedValue;
   try
   {
      WBFL::COGO::Station station;
      station.FromString(std::_tstring(m_EditableTextBlock->GetEditedText()),m_StationFormat);
      editedValue = station;
   }
   catch (...)
   {
      ASSERT(false);
   }

   return editedValue;
}

CDisplayView* EditableStationTextBlock::GetDisplayView()
{
   return m_EditableTextBlock->GetDisplayList()->GetDisplayMgr()->GetView();
}

CInplaceEdit* EditableStationTextBlock::GetEditObject()
{
   auto editable = std::dynamic_pointer_cast<EditableTextBlock>(m_EditableTextBlock);
   return editable->GetEditObject();
}

std::shared_ptr<iInplaceEditable> EditableStationTextBlock::GetInplaceEditable()
{
   return std::dynamic_pointer_cast<iInplaceEditable>(shared_from_this());
}
