#pragma once

enum DataPointSymbolType
{
   dpstNone = -1,
   dpst0 = 0,
   dpst1 = 1,
   dpst2 = 2,
   dpst3 = 3,
   dpst4 = 4,
   dpst5 = 5,
   dpst6 = 6,
   dpst7 = 7,
   dpst8 = 8,
   dpst9 = 9,
   dpstCircle = 10,
   dpstTriangle = 11,
   dpstCross = 12,
   dpstLeft = 13,
   dpstRight = 14,
   dpstLastDefault = 15  // this needs to always be the last in the list (for iterating)
};

interface iDataSet2d
{
   virtual WBFL::Geometry::Point2d GetItem(IndexType idx) = 0;
   virtual IndexType GetCount() = 0;
   virtual void Add(const WBFL::Geometry::Point2d& p) = 0;
   virtual void Insert(IndexType index, const WBFL::Geometry::Point2d& p) = 0;
   virtual void Remove(IndexType index) = 0;
   virtual void Clear() = 0;
};