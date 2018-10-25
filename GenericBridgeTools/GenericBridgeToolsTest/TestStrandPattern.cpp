///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TestStrandPattern.cpp: implementation of the CTestStrandPattern class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStrandPattern.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStrandPattern::CTestStrandPattern()
{

}

CTestStrandPattern::~CTestStrandPattern()
{

}

void CTestStrandPattern::Test()
{
   CComPtr<IStrandGrid> strand_grid;
   TRY_TEST(strand_grid.CoCreateInstance(CLSID_StrandGrid),S_OK);


   TRY_TEST(strand_grid->AddGridPoint(NULL),E_INVALIDARG);
   /////////////////////////////////////////////////////////
   // Create a simple strand pattern... 2" x 2" grid
   // three rows of 5 strands
   for ( int row = 0; row < 3; row++ )
   {
      Float64 y = (row+1)*2;
      for ( int strand = 0; strand < 3; strand++ )
      {
         Float64 x = strand*2;
         CComPtr<IPoint2d> p;
         p.CoCreateInstance(CLSID_Point2d);
         p->Move(x,y);
         TRY_TEST(strand_grid->AddGridPoint(p),S_OK);
      }
   }

   GridIndexType gridCount;
   TRY_TEST(strand_grid->get_GridPointCount(NULL),E_POINTER);
   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 9, true);

   CComPtr<IPoint2dCollection> points;
   TRY_TEST(strand_grid->get_GridPoints(NULL),E_POINTER);
   TRY_TEST(strand_grid->get_GridPoints(&points),S_OK);

   TRY_TEST(strand_grid->ClearGridPoints(),S_OK);
   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 0, true);

   TRY_TEST(strand_grid->AddGridPoints(NULL),E_INVALIDARG);
   TRY_TEST(strand_grid->AddGridPoints(points),S_OK);
   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 9, true);

   CComPtr<IPoint2d> p;
   TRY_TEST(strand_grid->get_GridPoint(-1,&p),E_INVALIDARG);
   TRY_TEST(strand_grid->get_GridPoint(10000,&p),E_INVALIDARG);
   TRY_TEST(strand_grid->get_GridPoint(0,NULL),E_POINTER);
   int i = 0;
   for ( int row = 0; row < 3; row++ )
   {
      Float64 y = (row+1)*2;
      for ( int strand = 0; strand < 3; strand++ )
      {
         Float64 x = strand*2;

         p.Release();
         TRY_TEST(strand_grid->get_GridPoint(i++,&p),S_OK);

         Float64 _x,_y;
         p->get_X(&_x);
         p->get_Y(&_y);

         TRY_TEST(IsEqual(x,_x),true);
         TRY_TEST(IsEqual(y,_y),true);
      }
   }

   TRY_TEST(strand_grid->RemoveGridPoint(-1),E_INVALIDARG);
   TRY_TEST(strand_grid->RemoveGridPoint(1000),E_INVALIDARG);
   TRY_TEST(strand_grid->RemoveGridPoint(0),S_OK);
   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 8, true);

   strand_grid->ClearGridPoints();
   strand_grid->AddGridPoints(points);

   TRY_TEST(strand_grid->get_GridPointCount(NULL),E_POINTER);
   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 9,true);

   CComPtr<IRect2d> box;
   TRY_TEST(strand_grid->GridBoundingBox(&box),S_OK);

   Float64 dval;
   box->get_Top(&dval);
   TRY_TEST(dval == 6.0, true);
   box->get_Bottom(&dval);
   TRY_TEST(dval == 0.0, true);

   // this should be the full strand pattern... strand pattern point and strand point will always
   // be the same for this case because point reflection is enabled
   i = 0;
   for ( int row = 0; row < 3; row++ )
   {
      Float64 y = (row+1)*2;
      for ( int strand = 0; strand < 3; strand++ )
      {
         Float64 x = strand*2;

         p.Release();
         TRY_TEST(strand_grid->get_GridPoint(i,&p),S_OK);

         Float64 _x,_y;
         p->get_X(&_x);
         p->get_Y(&_y);

         TRY_TEST(IsEqual(x,_x),true);
         TRY_TEST(IsEqual(y,_y),true);

         i++;

      }
   }

   CComQIPtr<IStrandGridFiller> strand_filler(strand_grid);

   StrandIndexType nStrands;
   TRY_TEST(strand_filler->get_MaxStrandCount(NULL),E_POINTER);
   TRY_TEST(strand_filler->get_MaxStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 15, true);

   TRY_TEST(strand_filler->GetMaxStrandFill(NULL),E_POINTER);
   CComPtr<ILongArray> fill_array;
   TRY_TEST(strand_filler->GetMaxStrandFill(&fill_array),S_OK);

   TRY_TEST(strand_filler->put_StrandFill(fill_array),S_OK);

   TRY_TEST(strand_filler->GetStrandCount(NULL),E_POINTER);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 15, true);

   fill_array->put_Item(0,0);
   TRY_TEST(strand_filler->put_StrandFill(fill_array),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 14, true);

   fill_array->put_Item(0,2);
   TRY_TEST(strand_filler->put_StrandFill(fill_array),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 16, true);

   TRY_TEST(strand_filler->RemoveAllStrands(),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 0, true);

   TRY_TEST(strand_filler->put_StrandFill(fill_array),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 16, true);

   CComPtr<ILongArray> new_array;
   new_array.CoCreateInstance(CLSID_LongArray);
   TRY_TEST(strand_filler->put_StrandFill(new_array),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 0, true);

   TRY_TEST(strand_filler->put_StrandFill(fill_array),S_OK);
   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 16, true);

   points.Release();
   CollectionIndexType count;
   TRY_TEST(strand_filler->GetStrandPositions(NULL),E_POINTER);
   TRY_TEST(strand_filler->GetStrandPositions(&points),S_OK);
   points->get_Count(&count);
   TRY_TEST(count == 16, true);

   TRY_TEST(strand_filler->get_StrandBoundingBox(NULL),E_POINTER);
   box.Release();
   TRY_TEST(strand_filler->get_StrandBoundingBox(&box),S_OK);
   box->get_Top(&dval);
   TRY_TEST(dval == 6.0, true);
   box->get_Bottom(&dval);
   TRY_TEST(dval == 2.0, true);
   box->get_Left(&dval);
   TRY_TEST(dval == -4.0, true);
   box->get_Right(&dval);
   TRY_TEST(dval == 4.0, true);

   Float64 x, y;
   TRY_TEST(strand_filler->get_CG(&x,&y),S_OK);
   TRY_TEST(x == 0.0, true);
   TRY_TEST(y == 3.875, true);

   TRY_TEST(strand_filler->get_FilledGridBounds(&x,&y),S_OK);
   TRY_TEST(x == 2.0, true);
   TRY_TEST(y == 6.0, true);

   TRY_TEST(strand_filler->StrandIndexToGridIndex(3, NULL),E_POINTER);
   TRY_TEST(strand_filler->StrandIndexToGridIndex(3, &gridCount),S_OK);
   TRY_TEST(gridCount == 1, true);
   TRY_TEST(strand_filler->StrandIndexToGridIndex(11, &gridCount),S_OK);
   TRY_TEST(gridCount == 6, true);

   RowIndexType nRows;
   TRY_TEST(strand_filler->get_RowsWithStrand(NULL),E_POINTER);
   TRY_TEST(strand_filler->get_RowsWithStrand(&nRows),S_OK);
   TRY_TEST(nRows,3);

   TRY_TEST(strand_filler->get_NumStrandsInRow(-1,&nStrands),E_INVALIDARG);
   TRY_TEST(strand_filler->get_NumStrandsInRow(10,&nStrands),E_INVALIDARG);
   TRY_TEST(strand_filler->get_NumStrandsInRow( 0,NULL),     E_POINTER);
   TRY_TEST(strand_filler->get_NumStrandsInRow( 0,&nStrands),S_OK);
   TRY_TEST(nStrands,6);
   TRY_TEST(strand_filler->get_NumStrandsInRow( 1,&nStrands),S_OK);
   TRY_TEST(nStrands,5);
   TRY_TEST(strand_filler->get_NumStrandsInRow( 2,&nStrands),S_OK);
   TRY_TEST(nStrands,5);

   // Ex functions
   new_array->Add(1);
   new_array->Add(2);
   new_array->Add(0);
   new_array->Add(1);
   new_array->Add(2);

   TRY_TEST(strand_filler->put_VerticalStrandAdjustment( 2.5),S_OK);
   TRY_TEST(strand_filler->get_VerticalStrandAdjustment( NULL),E_POINTER);
   TRY_TEST(strand_filler->get_VerticalStrandAdjustment( &dval),S_OK);
   TRY_TEST(dval == 2.5, true);


   TRY_TEST(strand_filler->GetStrandCountEx( new_array,NULL),  E_POINTER);
   TRY_TEST(strand_filler->GetStrandCountEx( NULL,&nStrands),  E_INVALIDARG);
   TRY_TEST(strand_filler->GetStrandCountEx( new_array,&nStrands),S_OK);
   TRY_TEST(nStrands,6);

   points.Release();
   TRY_TEST(strand_filler->GetStrandPositionsEx(NULL,&points),E_INVALIDARG);
   TRY_TEST(strand_filler->GetStrandPositionsEx(new_array,NULL),E_POINTER);
   TRY_TEST(strand_filler->GetStrandPositionsEx(new_array,&points),S_OK);
   points->get_Count(&count);
   TRY_TEST(count == 6, true);

   box.Release();
   TRY_TEST(strand_filler->get_StrandBoundingBoxEx(NULL,&box),E_INVALIDARG);
   TRY_TEST(strand_filler->get_StrandBoundingBoxEx(new_array,NULL),E_POINTER);
   TRY_TEST(strand_filler->get_StrandBoundingBoxEx(new_array,&box),S_OK);
   box->get_Top(&dval);
   TRY_TEST(dval == 6.5, true);
   box->get_Bottom(&dval);
   TRY_TEST(dval == 4.5, true);
   box->get_Left(&dval);
   TRY_TEST(dval == -2.0, true);
   box->get_Right(&dval);
   TRY_TEST(dval == 2.0, true);

   TRY_TEST(strand_filler->get_CGEx(NULL,&x,&y),E_INVALIDARG);
   TRY_TEST(strand_filler->get_CGEx(new_array,&x,&y),S_OK);
   TRY_TEST(x == 0.0, true);
   TRY_TEST(y == 5.5, true);

   TRY_TEST(strand_filler->StrandIndexToGridIndexEx(new_array,3, NULL),E_POINTER);
   TRY_TEST(strand_filler->StrandIndexToGridIndexEx(new_array,4, &gridCount),S_OK);
   TRY_TEST(gridCount == 3, true);
   TRY_TEST(strand_filler->StrandIndexToGridIndexEx(new_array,11, &gridCount),E_INVALIDARG);

   TRY_TEST(strand_filler->GetStrandDebondCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 0, true);

   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondedStrandsByGridIndex(&fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count), S_OK);
   TRY_TEST(count == 0, true);

   TRY_TEST(strand_grid->get_GridPointCount(&gridCount),S_OK);
   TRY_TEST(gridCount == 9,true);


   Float64 dl, dr;
   for (CollectionIndexType is = 0; is < count; is++)
   {
      TRY_TEST(strand_filler->GetDebondLengthByGridIndex(is,&y,&dl, &dr),S_FALSE);
      TRY_TEST(dl == 0.0,true);
      TRY_TEST(dr == 0.0,true);

      TRY_TEST(strand_filler->GetBondedLengthByGridIndex(is,1.0, 20.0, &y, &dl, &dr),S_FALSE);
      TRY_TEST(dl == 1.0,true);
      TRY_TEST(dr == 19.0,true);
   }

   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(55,&y,&dl, &dr),E_INVALIDARG);

   TRY_TEST(strand_filler->GetStrandCount(&nStrands),S_OK);
   TRY_TEST(nStrands == 16, true);
   for (StrandIndexType is=0; is<nStrands; is++)
   {
      TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(is,&y,&dl, &dr),S_FALSE);
      TRY_TEST(dl == 0.0,true);
      TRY_TEST(dr == 0.0,true);

      TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(is, 1.0, 20.0, &y, &dl, &dr),S_FALSE);
      TRY_TEST(dl == 1.0,true);
      TRY_TEST(dr == 19.0,true);
   }

   TRY_TEST(strand_filler->get_RowsWithStrand(&nRows),S_OK);
   TRY_TEST(nRows,3);

   TRY_TEST(strand_filler->get_StrandDebondInRow(2, &nStrands),S_OK);
   TRY_TEST(nStrands,0);

   VARIANT_BOOL bDebonded;
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(1, &bDebonded),S_OK);
   TRY_TEST(bDebonded,VARIANT_FALSE);

   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(4, &bDebonded),E_INVALIDARG);


   CComPtr<IDblArray> alft, argt;
   TRY_TEST(strand_filler->GetDebondSections(&alft, &argt),S_OK);
   TRY_TEST(alft->get_Count(&count), S_OK);
   TRY_TEST(count == 0, true);
   TRY_TEST(argt->get_Count(&count), S_OK);
   TRY_TEST(count == 0, true);

   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtLeftSection(0, &fill_array),E_INVALIDARG);
   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtRightSection(0, &fill_array),E_INVALIDARG);

   // this can result in unsymmetrical debonding... only one strand is debonded
   TRY_TEST(strand_filler->DebondStrandByGridIndex(50,2.0,3.0),E_INVALIDARG);
   TRY_TEST(strand_filler->DebondStrandByGridIndex(3,2.0,3.0),S_OK);
   TRY_TEST(strand_filler->DebondStrandByGridIndex(5,3.0,4.0),S_OK);
   TRY_TEST(strand_filler->DebondStrandByGridIndex(8,5.0,6.0),S_OK);

   TRY_TEST(strand_filler->GetStrandDebondCount(&nStrands),S_OK);
   TRY_TEST(nStrands , 5);

   Float64 l1, l2;
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(50,&y,&l1,&l2),E_INVALIDARG);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(0,&y,NULL,&l2),E_POINTER);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(0,&y,&l1,NULL),E_POINTER);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(0,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(1,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(3,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,2.0),true);
   TRY_TEST(IsEqual(l2,3.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(4,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(5,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,3.0),true);
   TRY_TEST(IsEqual(l2,4.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByGridIndex(8,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,5.0),true);
   TRY_TEST(IsEqual(l2,6.0),true);

   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(0,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(1,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(2,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(3,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(4,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(5,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(6,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,2.0),true);
   TRY_TEST(IsEqual(l2,3.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(7,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(8,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(9,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,3.0),true);
   TRY_TEST(IsEqual(l2,4.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(10,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,3.0),true);
   TRY_TEST(IsEqual(l2,4.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(11,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(12,&y,&l2,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(13,&y,&l1,&l2),S_FALSE); // not debonded
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(14,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,5.0),true);
   TRY_TEST(IsEqual(l2,6.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(15,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,5.0),true);
   TRY_TEST(IsEqual(l2,6.0),true);
   TRY_TEST(strand_filler->GetDebondLengthByPositionIndex(16,&y,&l1,&l2),E_INVALIDARG);

   TRY_TEST(strand_filler->get_StrandDebondInRow(-1,&nStrands),E_INVALIDARG);
   TRY_TEST(strand_filler->get_StrandDebondInRow(4,&nStrands),E_INVALIDARG);
   TRY_TEST(strand_filler->get_StrandDebondInRow(0,NULL),E_POINTER);
   TRY_TEST(strand_filler->get_StrandDebondInRow(0,&nStrands),S_OK);
   TRY_TEST(nStrands,0);
   TRY_TEST(strand_filler->get_StrandDebondInRow(1,&nStrands),S_OK);
   TRY_TEST(nStrands,3);
   TRY_TEST(strand_filler->get_StrandDebondInRow(2,&nStrands),S_OK);
   TRY_TEST(nStrands,2);

   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(-1,&bDebonded),E_INVALIDARG);
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(10,&bDebonded),E_INVALIDARG);
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(0,NULL),E_POINTER);
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(0,&bDebonded),S_OK);
   TRY_TEST(bDebonded,VARIANT_FALSE);
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(1,&bDebonded),S_OK);
   TRY_TEST(bDebonded,VARIANT_TRUE);
   TRY_TEST(strand_filler->IsExteriorStrandDebondedInRow(2,&bDebonded),S_OK);
   TRY_TEST(bDebonded,VARIANT_TRUE);

   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(0, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,5);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(2, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,5);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(2.5, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,4);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(3, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,4);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(3.5, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(6, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,0);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(14, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,0);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(24, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,0);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(35, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(40, 40.0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,5);
   fill_array.Release();
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(41, 40.0, &fill_array),E_INVALIDARG);
   TRY_TEST(strand_filler->GetStrandsDebondedByPositionIndex(-1, 40.0, &fill_array),E_INVALIDARG);


   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(16,4.0,40,&y,&l1,&l2),E_INVALIDARG);

   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(1,0.0,40,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,40.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(1,4.0,40,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,4.0),true);
   TRY_TEST(IsEqual(l2,36.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(6,4.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,2.0),true);
   TRY_TEST(IsEqual(l2,33.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(6,1.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(6,24.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,22.0),true);
   TRY_TEST(IsEqual(l2,13.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(7,24.0,40,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,24.0),true);
   TRY_TEST(IsEqual(l2,16.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(7,40.0,40,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,40.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(7,20.0,40,&y,&l1,&l2),S_FALSE);
   TRY_TEST(IsEqual(l1,20.0),true);
   TRY_TEST(IsEqual(l2,20.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(9,40.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(9,38.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,0.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);
   TRY_TEST(strand_filler->GetBondedLengthByPositionIndex(9,36.0,40,&y,&l1,&l2),S_OK);
   TRY_TEST(IsEqual(l1,33.0),true);
   TRY_TEST(IsEqual(l2,0.0),true);

   alft.Release();
   argt.Release();
   TRY_TEST(strand_filler->GetDebondSections(&alft, &argt),S_OK);
   TRY_TEST(alft->get_Count(&count), S_OK);
   TRY_TEST(count, 3);
   TRY_TEST(argt->get_Count(&count), S_OK);
   TRY_TEST(count, 3);
   TRY_TEST(alft->get_Item(0, &l1), S_OK);
   TRY_TEST(l1, 2.0);
   TRY_TEST(alft->get_Item(1, &l1), S_OK);
   TRY_TEST(l1, 3.0);
   TRY_TEST(alft->get_Item(2, &l1), S_OK);
   TRY_TEST(l1, 5.0);
   TRY_TEST(argt->get_Item(0, &l1), S_OK);
   TRY_TEST(l1, 6.0);
   TRY_TEST(argt->get_Item(1, &l1), S_OK);
   TRY_TEST(l1, 4.0);
   TRY_TEST(argt->get_Item(2, &l1), S_OK);
   TRY_TEST(l1, 3.0);

   fill_array.Release();
   IDType item;
   TRY_TEST(strand_filler->GetDebondAtLeftSection(0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,1);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,6);
   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtLeftSection(1, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,9);
   TRY_TEST(fill_array->get_Item(1, &item), S_OK);
   TRY_TEST(item,10);
   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtLeftSection(2, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,14);
   TRY_TEST(fill_array->get_Item(1, &item), S_OK);
   TRY_TEST(item,15);

   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtRightSection(0, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,14);
   TRY_TEST(fill_array->get_Item(1, &item), S_OK);
   TRY_TEST(item,15);
   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtRightSection(1, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,9);
   TRY_TEST(fill_array->get_Item(1, &item), S_OK);
   TRY_TEST(item,10);
   fill_array.Release();
   TRY_TEST(strand_filler->GetDebondAtRightSection(2, &fill_array),S_OK);
   TRY_TEST(fill_array->get_Count(&count),S_OK);
   TRY_TEST(count,1);
   TRY_TEST(fill_array->get_Item(0, &item), S_OK);
   TRY_TEST(item,6);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(strand_filler);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStrandGrid ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(strand_grid,IID_IStrandGrid,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);

}

