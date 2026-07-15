///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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

#include <Units\UnitsLib.h>
#include <Units\DynamicUnitTypeManager.h>
#include <Units\XUnit.h>
#include <algorithm>


using namespace WBFL::Units;

void DynamicUnitTypeManager::AddUnitType(const std::_tstring& name, Float64 m, Float64 l, Float64 t, Float64 k, Float64 a)
{
   if (m_UnitTypes.find(name) != m_UnitTypes.end())
   {
      THROW(XUnit, Reason::UnitTypeAlreadyDefined);
   }

   UnitTypeEntry entry;
   entry.Dimension.Mass = m;
   entry.Dimension.Length = l;
   entry.Dimension.Time = t;
   entry.Dimension.Temperature = k;
   entry.Dimension.Angle = a;

   m_UnitTypes.emplace(name, std::move(entry));
   m_UnitTypeOrder.push_back(name);
}

void DynamicUnitTypeManager::RemoveUnitType(const std::_tstring& name)
{
   auto found = m_UnitTypes.find(name);
   if (found == m_UnitTypes.end())
   {
      THROW(XUnit, Reason::UnitTypeNotFound);
   }
   m_UnitTypes.erase(found);

   auto orderIter = std::find(m_UnitTypeOrder.begin(), m_UnitTypeOrder.end(), name);
   m_UnitTypeOrder.erase(orderIter);
}

void DynamicUnitTypeManager::ClearUnitTypes()
{
   m_UnitTypes.clear();
   m_UnitTypeOrder.clear();
}

bool DynamicUnitTypeManager::HasUnitType(const std::_tstring& name) const
{
   return m_UnitTypes.find(name) != m_UnitTypes.end();
}

IndexType DynamicUnitTypeManager::GetUnitTypeCount() const
{
   return (IndexType)m_UnitTypes.size();
}

std::vector<std::_tstring> DynamicUnitTypeManager::GetUnitTypeNames() const
{
   return m_UnitTypeOrder;
}

const std::_tstring& DynamicUnitTypeManager::GetUnitTypeName(IndexType index) const
{
   if (m_UnitTypeOrder.size() <= index)
   {
      THROW(XUnit, Reason::UnitTypeNotFound);
   }
   return m_UnitTypeOrder[index];
}

DynamicUnitTypeDimension DynamicUnitTypeManager::GetUnitTypeDimension(const std::_tstring& name) const
{
   return GetUnitTypeEntry(name).Dimension;
}

void DynamicUnitTypeManager::AddUnit(const std::_tstring& unitTypeName, const std::_tstring& tag, Float64 cf)
{
   AddUnit(unitTypeName, tag, 0.0, cf, 0.0);
}

void DynamicUnitTypeManager::AddUnit(const std::_tstring& unitTypeName, const std::_tstring& tag, Float64 preTerm, Float64 cf, Float64 postTerm)
{
   UnitTypeEntry& entry = GetUnitTypeEntry(unitTypeName);

   if (entry.Units.find(tag) != entry.Units.end())
   {
      THROW(XUnit, Reason::UnitAlreadyDefined);
   }

   const DynamicUnitTypeDimension& dim = entry.Dimension;
   entry.Units.emplace(tag, DynamicPhysical(dim.Mass, dim.Length, dim.Time, dim.Temperature, dim.Angle, preTerm, cf, postTerm, tag));
   entry.UnitOrder.push_back(tag);
}

void DynamicUnitTypeManager::RemoveUnit(const std::_tstring& unitTypeName, const std::_tstring& tag)
{
   UnitTypeEntry& entry = GetUnitTypeEntry(unitTypeName);
   auto found = entry.Units.find(tag);
   if (found == entry.Units.end())
   {
      THROW(XUnit, Reason::UnitNotFound);
   }
   entry.Units.erase(found);

   auto orderIter = std::find(entry.UnitOrder.begin(), entry.UnitOrder.end(), tag);
   entry.UnitOrder.erase(orderIter);
}

void DynamicUnitTypeManager::ClearUnits(const std::_tstring& unitTypeName)
{
   UnitTypeEntry& entry = GetUnitTypeEntry(unitTypeName);
   entry.Units.clear();
   entry.UnitOrder.clear();
}

bool DynamicUnitTypeManager::HasUnit(const std::_tstring& unitTypeName, const std::_tstring& tag) const
{
   auto found = m_UnitTypes.find(unitTypeName);
   if (found == m_UnitTypes.end())
   {
      return false;
   }
   return found->second.Units.find(tag) != found->second.Units.end();
}

IndexType DynamicUnitTypeManager::GetUnitCount(const std::_tstring& unitTypeName) const
{
   return (IndexType)GetUnitTypeEntry(unitTypeName).Units.size();
}

std::vector<std::_tstring> DynamicUnitTypeManager::GetUnitTags(const std::_tstring& unitTypeName) const
{
   return GetUnitTypeEntry(unitTypeName).UnitOrder;
}

const std::_tstring& DynamicUnitTypeManager::GetUnitTag(const std::_tstring& unitTypeName, IndexType index) const
{
   const UnitTypeEntry& entry = GetUnitTypeEntry(unitTypeName);
   if (entry.UnitOrder.size() <= index)
   {
      THROW(XUnit, Reason::UnitNotFound);
   }
   return entry.UnitOrder[index];
}

const DynamicPhysical& DynamicUnitTypeManager::GetUnit(const std::_tstring& unitTypeName, const std::_tstring& tag) const
{
   const UnitTypeEntry& entry = GetUnitTypeEntry(unitTypeName);
   auto found = entry.Units.find(tag);
   if (found == entry.Units.end())
   {
      THROW(XUnit, Reason::UnitNotFound);
   }
   return found->second;
}

DynamicUnitTypeManager::UnitTypeEntry& DynamicUnitTypeManager::GetUnitTypeEntry(const std::_tstring& name)
{
   auto found = m_UnitTypes.find(name);
   if (found == m_UnitTypes.end())
   {
      THROW(XUnit, Reason::UnitTypeNotFound);
   }
   return found->second;
}

const DynamicUnitTypeManager::UnitTypeEntry& DynamicUnitTypeManager::GetUnitTypeEntry(const std::_tstring& name) const
{
   auto found = m_UnitTypes.find(name);
   if (found == m_UnitTypes.end())
   {
      THROW(XUnit, Reason::UnitTypeNotFound);
   }
   return found->second;
}
