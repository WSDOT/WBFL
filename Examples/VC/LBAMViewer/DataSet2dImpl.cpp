///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "DataSet2dImpl.h"

WBFL::Geometry::Point2d CDataSet2dImpl::GetItem(IndexType index)
{
   CHECK(0 <= index && index < m_Container.size());
   return m_Container[index];
}

IndexType CDataSet2dImpl::GetCount()
{
   return m_Container.size();
}

void CDataSet2dImpl::Add(const WBFL::Geometry::Point2d& point)
{
   m_Container.emplace_back(point);
}

void CDataSet2dImpl::Insert(IndexType index, const WBFL::Geometry::Point2d& point)
{
   CHECK(0 <= index && index <= m_Container.size());
   if (index == m_Container.size())
   {
      Add(point);
   }
   else
   {
      ContainerIterator it = m_Container.begin();
      it += index;
      m_Container.insert(it, ContainerItem(point));
   }
}

void CDataSet2dImpl::Remove(IndexType index)
{
   CHECK(0 <= index && index < m_Container.size());

   ContainerIterator it = m_Container.begin();
   it += index;
   m_Container.erase(it);
}

void CDataSet2dImpl::Clear()
{
   m_Container.clear();
}

std::shared_ptr<iDataSet2d> CDataSet2dImpl::Clone()
{
   // create a new stress point collection and fill it up
   return std::make_shared<CDataSet2dImpl>(*this);
}

