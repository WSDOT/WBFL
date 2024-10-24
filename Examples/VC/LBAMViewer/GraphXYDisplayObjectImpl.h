#pragma once
#include <GeomModel/GeomModel.h>
#include "GraphXYDisplayObject.h"

interface iDataSet2d;

class GraphMapper;

class CGraphXyDisplayObject : public iGraphXyDisplayObject
{
private:
   CGraphXyDisplayObject(IDType id = INVALID_ID);

public:
   static std::shared_ptr<CGraphXyDisplayObject> Create(IDType id = INVALID_ID) { return std::shared_ptr<CGraphXyDisplayObject>(new CGraphXyDisplayObject(id)); }

   // iGraphXyDisplayObject
public:
   WBFL::Geometry::Rect2d GetGraphBounds() override;
   void SetGraphBounds(const WBFL::Geometry::Rect2d& newVal) override;
   std::_tstring GetTitle() override;
   void SetTitle(const std::_tstring& title) override;
   IndexType GetDataCount() override;
   void AddData(std::shared_ptr<iGraphXyDataProvider> data) override;
   std::shared_ptr<iGraphXyDataProvider> GetData(IndexType idx) override;
   void Commit() override;
   void ClearData() override;
   IndexType GetNumberOfMajorIncrements() override;
   void SetNumberOfMajorIncrements(IndexType newVal) override;
   BOOL DoDisplayAxisValues() override;
   void DoDisplayAxisValues(BOOL newVal) override;
   BOOL DoDisplayGrid() override;
   void DoDisplayGrid(BOOL newVal) override;

private:
   WBFL::Geometry::Rect2d m_GraphBounds;     // rectangle where graph is displayed in view
   std::_tstring         m_Title;
   BOOL     m_DoDisplayAxisValues;
   BOOL     m_DoDisplayGrid;
   IndexType m_NumberOfMajorIncrements;

   using DataSetHolder = std::shared_ptr<iGraphXyDataProvider>;
   using DataSetCollection = std::vector< DataSetHolder >;
   using DataSetIterator = DataSetCollection::iterator;
   DataSetCollection                     m_DataSets;

   long                                 m_NumDos; // number of display objects

   void RebuildDisplayObjects();
   void AddMyDisplayObject(std::shared_ptr<WBFL::DManip::iDisplayObject> pdo);
   void ClearDisplayObjects();
   void DrawAxis(GraphMapper& mapper);
   void DrawCurves(GraphMapper& mapper);
   void DrawGraph(Float64 t, Float64 l, Float64 r, Float64 b);
   void GetCurveBoundary(Float64* t, Float64* l, Float64* r, Float64* b);
   void DrawAxisLine(Float64 startX, Float64 startY, Float64 endX, Float64 endY, UINT width = 1);
   void DrawString(std::_tstring& string, Float64 wx, Float64 wy, UINT textAlign);
};

class CGraphXyDataProvider : public iGraphXyDataProvider
{
public:
   CGraphXyDataProvider();

   // iGraphXyDataProvider
   void SetDataSet(std::shared_ptr<iDataSet2d> dataSet) override;
   std::shared_ptr<iDataSet2d> GetDataSet() override;
   void SetDataPointFactory(std::shared_ptr<iDataPointFactory> factory) override;
   std::shared_ptr<iDataPointFactory> GetDataPointFactory() override;

private:
   std::shared_ptr<iDataSet2d>          m_DataSet;
   std::shared_ptr<iDataPointFactory>   m_Factory;
};
