///////////////////////////////////////////////////////////////////////
// RCCapacity Test - Test driver for RCCapacity library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include "stdafx.h"
#include "GeneralTests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void TestISupportUnitServer(IUnknown* punk)
{
   CComQIPtr<ISupportUnitServer> sus(punk);
   TRY_TEST( sus != nullptr, true );

   CComPtr<IUnitServer> unitServer;
   TRY_TEST(sus->get_UnitServer(nullptr),E_POINTER);
   TRY_TEST(sus->get_UnitServer(&unitServer), S_OK );
   TRY_TEST(unitServer != nullptr, true );
   TRY_TEST(sus->putref_UnitServer(nullptr),E_INVALIDARG);
   TRY_TEST(sus->putref_UnitServer(unitServer),S_OK);
}


void DumpSolution(IGeneralSection* section, IMomentCapacitySolution* solution)
{
   USES_CONVERSION;
   CComPtr<IGeneralSectionSolution> general_solution;
   solution->get_GeneralSectionSolution(&general_solution);

   IndexType nSlices;
   general_solution->get_SliceCount(&nSlices);
   std::cout << "Element, Material, Top, Bottom, Ycg, Area, initial strain, incremental strain, total strain, stress, force, moment" << std::endl;
   for (IndexType sliceIdx = 0; sliceIdx < nSlices; sliceIdx++)
   {
      CComPtr<IGeneralSectionSlice> slice;
      general_solution->get_Slice(sliceIdx, &slice);
      Float64 area;
      CComPtr<IPoint2d> cg;
      Float64 initial_strain;
      Float64 incremental_strain;
      Float64 total_strain;
      Float64 fgStress;
      slice->get_Area(&area);
      slice->get_CG(&cg);
      slice->get_InitialStrain(&initial_strain);
      slice->get_IncrementalStrain(&incremental_strain);
      slice->get_TotalStrain(&total_strain);
      slice->get_ForegroundStress(&fgStress);

      CComPtr<IStressStrain> ss;
      slice->get_ForegroundMaterial(&ss);
      CComBSTR bstrMaterial;
      ss->get_Name(&bstrMaterial);

      Float64 y;
      cg->get_Y(&y);

      CComPtr<IShape> shape;
      slice->get_Shape(&shape);
      CComPtr<IRect2d> rect;
      shape->get_BoundingBox(&rect);
      Float64 top, bottom;
      rect->get_Top(&top);
      rect->get_Bottom(&bottom);

      IndexType shapeIdx;
      slice->get_ShapeIndex(&shapeIdx);
      CComBSTR bstrName;
      section->get_Name(shapeIdx, &bstrName);

      std::cout << OLE2A(bstrName) << ", " << OLE2A(bstrMaterial) << ", " << top << ", " << bottom << ", " << y << ", " << area << ", " << initial_strain << ", " << incremental_strain << ", " << total_strain << ", " << fgStress << ", " << area * fgStress << ", " << area * fgStress * y << std::endl;
   }
}