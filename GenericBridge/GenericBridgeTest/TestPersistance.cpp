///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestPersistance.cpp: implementation of the CTestPersistance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPersistance.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPersistance::CTestPersistance()
{

}

CTestPersistance::~CTestPersistance()
{

}

void CTestPersistance::Test()
{
//   // Create a default bridge
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
//
//   TRY_TEST(TestBridge(bridge),true);
//
//   // Lets make the bridge more complicated
//
//   // Add Spans/Piers
//   // Make span 1 100' add spans 2 (200') and 3 (300')
//   CComPtr<ISpanCollection> spans;
//   bridge->get_Spans(&spans);
//   CComPtr<ISpan> span;
//   spans->get_Item(0,&span);
//   span->put_Length(100.0);
//
//   bridge->InsertSpanAndPier(0,200.0,qcbAfter,qcbLeft);
//   bridge->InsertSpanAndPier(1,300.0,qcbAfter,qcbLeft);
//
//   // Put some segments on girder line 0
//   CComPtr<ISuperstructureMemberCollection> members;
//   bridge->get_SuperstructureMembers(0,&members);
//   
//   members->Add();
//   members->Add();
//   members->Add();
//   members->Add();
//
//   CComPtr<IPrismaticSegment> pris_segment;
//   pris_segment.CoCreateInstance(CLSID_PrismaticSegment);
//   pris_segment->put_Length(-0.5);
//
//   CComPtr<IEnumSuperstructureMember> enumMembers;
//   members->get__EnumElements(&enumMembers);
//   CComPtr<ISuperstructureMember> member;
//   while ( enumMembers->Next(1,&member,NULL) != S_FALSE )
//   {
//      member->put_Length(-0.25);
//
//      member->put_Fractional(VARIANT_TRUE);
//
//      member->AddSegment(pris_segment);
//      member->AddSegment(pris_segment);
//
//      member.Release();
//   }
//
//#pragma Reminder("Piers and linked piers")
//
//   // Link all the piers togetner
//   CComPtr<IPierCollection> piers;
//   bridge->get_Piers(&piers);
//
//   CComPtr<IPier> pier1;
//   piers->get_Item(0,&pier1);
//
//   // Build up a longitudinal pier description
//   CComPtr<ILongitudinalPierDescription> lpd;
//   pier1->get_LongitudinalPierDescription(&lpd);
//
//   CComPtr<IPrismaticSegment> newSegment;
//   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
//
//   BuildSegment(newSegment);
//
//   lpd->AddSegment(newSegment);
//   lpd->AddSegment(newSegment);
//   lpd->AddSegment(newSegment);
//   lpd->AddSegment(newSegment);
//   lpd->put_Height(4.0);
//   lpd->put_BaseOffset(-3.0);
//
//   // Build up a transverse pier description
//   CComPtr<ITransversePierDescription> tpd;
//   pier1->CreateTransversePierDescription();
//   pier1->get_TransversePierDescription(&tpd);
//
//   CComPtr<ICrossBeam> xbeam;
//   tpd->get_CrossBeam(&xbeam);
//
//   xbeam->AddSegment(newSegment);
//   xbeam->AddSegment(newSegment);
//   xbeam->AddSegment(newSegment);
//
//   CComPtr<IColumnSpacing> columnSpacing;
//   tpd->get_ColumnSpacing(&columnSpacing);
//   columnSpacing->put_Overhang(qcbLeft,2.0);
//   columnSpacing->put_Overhang(qcbRight,2.0);
//
//   columnSpacing->put_Uniform(VARIANT_FALSE);
//
//   columnSpacing->Add(3);
//   columnSpacing->put_Spacing(0,1.0);
//   columnSpacing->put_Spacing(1,2.0);
//   columnSpacing->put_Spacing(2,3.0);
//
//   CComPtr<IColumn> column;
//   columnSpacing->get_Column(1,&column);
//
//   column->AddSegment(newSegment);
//   column->AddSegment(newSegment);
//   column->AddSegment(newSegment);
//   column->AddSegment(newSegment);
//
//   
//   TRY_TEST(TestBridge(bridge),true);
}

bool CTestPersistance::TestBridge(IGenericBridge* bridge)
{
   CComPtr<IStructuredSave2> save;
   save.CoCreateInstance(CLSID_StructuredSave2);
   save->Open(CComBSTR("bridge.xml"));
   save->BeginUnit(CComBSTR("PersistanceTest"),1.0);

   CComQIPtr<IStructuredStorage2> ss(bridge);
   ss->Save(save);

   save->EndUnit();
   save->Close();

   CComPtr<IStructuredLoad2> load;
   load.CoCreateInstance(CLSID_StructuredLoad2);
   load->Open(CComBSTR("bridge.xml"));
   load->BeginUnit(CComBSTR("PersistanceTest"));

   CComPtr<IGenericBridge> bridge2;
   bridge2.CoCreateInstance(CLSID_GenericBridge);

   ss.Release();
   bridge2->QueryInterface(&ss);
   ss->Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   load->Close();

   save.Release();
   save.CoCreateInstance(CLSID_StructuredSave2);
   save->Open(CComBSTR("bridge2.xml"));
   save->BeginUnit(CComBSTR("PersistanceTest"),1.0);
   ss->Save(save);
   save->EndUnit();
   save->Close();

   // compare two files by comparing strings. note that xml parser based files have only two lines
   // the first line is the xml processing instruction and the second line is all of the data
   // for this simple case we can simply compare the two data strings. For huge files, we
   // might have to resort to less memory intensive methods.
   try
   {
      std::_tstring x1;
      std::_tifstream if1("bridge.xml");
      std::getline(if1, x1);
      std::getline(if1, x1); // second line is the data

      std::_tstring x2;
      std::_tifstream if2("bridge2.xml");
      std::getline(if2, x2);
      std::getline(if2, x2);

      return x1 == x2;

   }
   catch(...)
   {
      ATLASSERT(false);
      return false;
   }
}

void CTestPersistance::BuildSegment(IPrismaticSegment* segment)
{
   //segment->put_Length(2.0);

   //CComPtr<ICircle> circle;
   //circle.CoCreateInstance(CLSID_Circle);
   //circle->put_Radius(3);

   //CComQIPtr<IShape> shape(circle);

   //segment->putref_Shape(shape);
}
