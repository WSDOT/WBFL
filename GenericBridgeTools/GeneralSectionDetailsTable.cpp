///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include <WBFLGenericBridgeTools\GeneralSectionDetailsTable.h>
#include <Reporter\Reporter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcTable* CreateGeneralSectionDetailsTable(IGeneralSectionSolution* pSolution, Float64 Ytg, bool bSimpleFormat, const WBFL::Units::ForceData& GeneralForce, const WBFL::Units::LengthData& ComponentDim, const WBFL::Units::PressureData& Stress, const WBFL::Units::Length2Data& Area);

rptRcTable* CreateGeneralSectionDetailsTable(IGeneralSectionSolution* pSolution, Float64 Ytg, bool bSimpleFormat, IEAFDisplayUnits* pDisplayUnits)
{
   return CreateGeneralSectionDetailsTable(pSolution, Ytg, bSimpleFormat, pDisplayUnits->GetGeneralForceUnit(), pDisplayUnits->GetComponentDimUnit(), pDisplayUnits->GetStressUnit(), pDisplayUnits->GetAreaUnit());
}

rptRcTable* CreateGeneralSectionDetailsTable(IGeneralSectionSolution* pSolution, Float64 Ytg, bool bSimpleFormat, const WBFL::Units::IndirectMeasure* pDisplayUnits)
{
   return CreateGeneralSectionDetailsTable(pSolution, Ytg, bSimpleFormat, pDisplayUnits->GeneralForce, pDisplayUnits->ComponentDim, pDisplayUnits->Stress, pDisplayUnits->Area);
}

rptRcTable* CreateGeneralSectionDetailsTable(IGeneralSectionSolution* pSolution, Float64 Ytg, bool bSimpleFormat, const WBFL::Units::ForceData& GeneralForce,const WBFL::Units::LengthData& ComponentDim, const WBFL::Units::PressureData& Stress, const WBFL::Units::Length2Data& Area)
{
   INIT_UV_PROTOTYPE(rptForceUnitValue, force, GeneralForce, false);
   INIT_UV_PROTOTYPE(rptLengthUnitValue, shortLength, ComponentDim, false);
   INIT_UV_PROTOTYPE(rptStressUnitValue, stress, Stress, false);
   INIT_UV_PROTOTYPE(rptAreaUnitValue, area, Area, false);

   ColumnIndexType nColumns = (bSimpleFormat ? 7 : 8);
   rptRcTable* pTable = rptStyleManager::CreateDefaultTable(nColumns);

   ColumnIndexType col = 0;


   if (bSimpleFormat)
   {
      (*pTable)(0, col++) << _T("Slice");
      (*pTable)(0, col++) << COLHDR(Sub2(_T("y"), _T("top")), rptLengthUnitTag, ComponentDim);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("y"), _T("bot")), rptLengthUnitTag, ComponentDim);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("y"), _T("cg")), rptLengthUnitTag, ComponentDim);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("i")), rptAreaUnitTag, Area);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("f"), _T("i")), rptStressUnitTag, Stress);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("T"), _T("i")), rptForceUnitTag, GeneralForce);
   }
   else
   {
      pTable->SetNumberOfHeaderRows(2);

      pTable->SetRowSpan(0, col, 2);
      (*pTable)(0, col++) << _T("Slice");

      pTable->SetColumnSpan(0, col, 2);
      (*pTable)(0, col) << _T("Points");
      (*pTable)(1, col++) << COLHDR(_T("x"), rptLengthUnitTag, ComponentDim);
      (*pTable)(1, col++) << COLHDR(_T("y"), rptLengthUnitTag, ComponentDim);

      pTable->SetColumnSpan(0, col, 2);
      (*pTable)(0, col) << _T("Centroid");
      (*pTable)(1, col++) << COLHDR(Sub2(_T("x"), _T("cg")), rptLengthUnitTag, ComponentDim);
      (*pTable)(1, col++) << COLHDR(Sub2(_T("y"), _T("cg")), rptLengthUnitTag, ComponentDim);

      pTable->SetRowSpan(0, col, 2);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("A"), _T("i")), rptAreaUnitTag, Area);

      pTable->SetRowSpan(0, col, 2);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("f"), _T("i")), rptStressUnitTag, Stress);

      pTable->SetRowSpan(0, col, 2);
      (*pTable)(0, col++) << COLHDR(Sub2(_T("T"), _T("i")), rptForceUnitTag, GeneralForce);
   }


   Float64 neutral_axis_angle;
   pSolution->get_NeutralAxisDirection(&neutral_axis_angle);

   IndexType nSlices;
   pSolution->get_SliceCount(&nSlices);

   RowIndexType row = pTable->GetNumberOfHeaderRows();
   for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
   {
      col = 0;

      RowIndexType rowIncrement = 1;

      CComPtr<IGeneralSectionSlice> slice;
      pSolution->get_Slice(sliceIdx, &slice);

      CComPtr<IShape> slice_shape;
      slice->get_Shape(&slice_shape);

      if (bSimpleFormat)
      {
         (*pTable)(row, col++) << sliceIdx + 1;

         CComPtr<IRect2d> bbox;
         slice_shape->get_BoundingBox(&bbox);
         Float64 ytop, ybot;
         bbox->get_Top(&ytop);
         bbox->get_Bottom(&ybot);
      
#if defined _DEBUG
         CComQIPtr<IXYPosition> position(slice_shape);
         CComPtr<IPoint2d> pntTC, pntBC;
         position->get_LocatorPoint(lpTopCenter, &pntTC);
         position->get_LocatorPoint(lpBottomCenter, &pntBC);
      
         Float64 _yt, _yb;
         pntTC->get_Y(&_yt);
         pntBC->get_Y(&_yb);

         ATLASSERT(IsEqual(ytop, _yt));
         ATLASSERT(IsEqual(ybot, _yb));
#endif // _DEBUG

         ytop -= Ytg;
         ybot -= Ytg;

         CComPtr<IPoint2d> pntCG;
         slice->get_CG(&pntCG);
         Float64 ycg;
         pntCG->get_Y(&ycg);
         ycg -= Ytg; // convert to girder section coordinates

         (*pTable)(row, col++) << shortLength.SetValue(ytop);
         (*pTable)(row, col++) << shortLength.SetValue(ybot);
         (*pTable)(row, col++) << shortLength.SetValue(ycg);

         rowIncrement = 1;
      }
      else
      {
         // in the more complex format, we list the polygon points
         // that make up each slice
         CComPtr<IPoint2dCollection> points;
         slice_shape->get_PolyPoints(&points);
         points->Offset(0, -Ytg);

         IndexType nPoints;
         points->get_Count(&nPoints);

         pTable->SetRowSpan(row, col, nPoints);
         (*pTable)(row, col++) << sliceIdx + 1;

         RowIndexType pointRow = row;
         for (IndexType pntIdx = 0; pntIdx < nPoints; pntIdx++, pointRow++)
         {
            CComPtr<IPoint2d> pnt;
            points->get_Item(pntIdx, &pnt);
            Float64 x, y;
            pnt->Location(&x, &y);
            (*pTable)(pointRow, col) << shortLength.SetValue(x);
            (*pTable)(pointRow, col + 1) << shortLength.SetValue(y);
         }
         col += 2;

         CComPtr<IPoint2d> pntCG;
         slice->get_CG(&pntCG);
         pntCG->Offset(0, -Ytg);
         Float64 xcg, ycg;
         pntCG->Location(&xcg, &ycg);

         pTable->SetRowSpan(row, col, nPoints);
         (*pTable)(row, col++) << shortLength.SetValue(xcg);
         pTable->SetRowSpan(row, col, nPoints);
         (*pTable)(row, col++) << shortLength.SetValue(ycg);

         pTable->SetRowSpan(row, col, nPoints); // Ai
         pTable->SetRowSpan(row, col+1, nPoints); // fi
         pTable->SetRowSpan(row, col+2, nPoints); // Ti

         rowIncrement = nPoints;
      }

      Float64 slice_area;
      slice->get_Area(&slice_area);

      Float64 avg_stress;
      slice->get_ForegroundStress(&avg_stress);

      Float64 t = slice_area*avg_stress;

      (*pTable)(row, col++) << area.SetValue(slice_area);
      (*pTable)(row, col++) << stress.SetValue(avg_stress);
      (*pTable)(row, col++) << force.SetValue(t);

      row += rowIncrement;
   }

   return pTable;
}