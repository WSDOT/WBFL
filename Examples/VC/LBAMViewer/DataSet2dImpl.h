#pragma once
#include "DataSet2d.h"

class CDataSet2dImpl : public iDataSet2d
{
public:
   CDataSet2dImpl() = default;
   CDataSet2dImpl(const CDataSet2dImpl&) = default;

   std::shared_ptr<iDataSet2d> Clone();

   // iDataSet2d
   WBFL::Geometry::Point2d GetItem(IndexType idx) override;
   IndexType GetCount() override;
   void Add(const WBFL::Geometry::Point2d& p) override;
   void Insert(IndexType index, const WBFL::Geometry::Point2d& p) override;
   void Remove(IndexType index) override;
   void Clear() override;

protected:
   using ContainerItem = WBFL::Geometry::Point2d;
   using ContainerType = std::vector<ContainerItem>;
   using ContainerIterator = ContainerType::iterator;
   ContainerType m_Container;
};
