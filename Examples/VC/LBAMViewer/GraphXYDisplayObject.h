#pragma once
#include "stdAfx.h"


interface IPoint2d;
interface iDataSet2d;
interface iDisplayObject;

interface iDataPointFactory
{
   // creates a data point at the specified location. 
   // The object created must also support the  iConnectable interface
   virtual std::shared_ptr<WBFL::DManip::iDisplayObject> CreateDataPoint(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY) = 0;

   // get color for lines between data points
   virtual COLORREF GetColor() = 0;
};

interface iGraphXyDataProvider
{
   virtual void SetDataSet(std::shared_ptr<iDataSet2d> dataSet) = 0;
   virtual std::shared_ptr<iDataSet2d> GetDataSet() = 0;

   virtual void SetDataPointFactory(std::shared_ptr<iDataPointFactory> factory) = 0;
   virtual std::shared_ptr<iDataPointFactory> GetDataPointFactory() = 0;
};

class iGraphXyDisplayObject : public WBFL::DManip::CompositeDisplayObject
{
protected:
   iGraphXyDisplayObject(IDType id) : WBFL::DManip::CompositeDisplayObject(id) {}

public:
   virtual WBFL::Geometry::Rect2d GetGraphBounds() = 0;
   virtual void SetGraphBounds(const WBFL::Geometry::Rect2d& newVal) = 0;
   virtual std::_tstring GetTitle() = 0;
   virtual void SetTitle(const std::_tstring& title) = 0;
   virtual IndexType GetDataCount() = 0;
   virtual void AddData(std::shared_ptr<iGraphXyDataProvider> data) = 0;
   virtual std::shared_ptr<iGraphXyDataProvider> GetData(IndexType idx) = 0;
   virtual void Commit() = 0;
   virtual void ClearData() = 0;
   virtual IndexType GetNumberOfMajorIncrements() = 0;
   virtual void SetNumberOfMajorIncrements(IndexType newVal) = 0;
   virtual BOOL DoDisplayAxisValues() = 0;
   virtual void DoDisplayAxisValues(BOOL newVal) = 0;
   virtual BOOL DoDisplayGrid() = 0;
   virtual void DoDisplayGrid(BOOL newVal) = 0;
};