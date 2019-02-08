///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2019  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\CompositeShape.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmShapeUtils
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmShapeUtils::CopyTraits(const gmShapeImp& rFrom, gmIShape* pTo)
{
   pTo->EnableFillMode(rFrom.IsFillModeEnabled());
   pTo->EnableBorderMode(rFrom.IsBorderModeEnabled());
   pTo->MakeSolid(rFrom.IsSolid());
   pTo->SetFillColor(rFrom.GetFillColor());
   pTo->SetBorderColor(rFrom.GetBorderColor());
}

gmCompositeShape* gmShapeUtils::GetRootNode(gmIShape& rShape)
{
   gmCompositeShape* pold;
   gmCompositeShape* ps = rShape.GetParent();
   if (ps!=0)
   {
      // we're in a composite. loop until we find the top
      bool loop=true;
      while (loop)
      {
         pold = ps;
         ps = pold->GetParent();
         if(ps==0)
            loop=false;
      }
      CHECKX(pold->GetComposite(),_T("Root not not a composite"));
      return pold;
   }
   else
   {
      // shape is not in a composite
      return nullptr;
   }
}

const gmCompositeShape* gmShapeUtils::GetRootNode(const gmIShape& rShape)
{
   const gmCompositeShape* pold;
   const gmCompositeShape* ps = rShape.GetParent();
   if (ps!=0)
   {
      bool loop=true;
      while (loop)
      {
         pold = ps;
         ps = pold->GetParent();
         if(ps==0)
            loop=false;
      }
      CHECKX(pold->GetComposite(),_T("Root not not a composite"));
      return pold;
   }
   else
   {
      return nullptr;
   }
}

gmProperties gmShapeUtils::TransformProperties(const gmElasticProperties& ep,Float64 e)
{
   PRECONDITION( !IsZero(e) );

   gmProperties p;

   p.SetArea( ep.EA() / e );
   p.SetCentroid( ep.Centroid() );
   p.SetIxx( ep.EIxx() / e );
   p.SetIyy( ep.EIyy() / e );
   p.SetIxy( ep.EIxy() / e );
   p.SetYtop( ep.Ytop() );
   p.SetYbottom( ep.Ybottom() );
   p.SetXleft( ep.Xleft() );
   p.SetXright( ep.Xright() );
   p.SetOrigin( ep.GetOrigin() );
   p.SetOrientation( ep.GetOrientation() );

   // Call this last to preserve coordinate system type.
   // Calls to SetOrigin and SetOrientation change the coordinate system type
   // to user defined.
   p.SetCoordinateSystem( (gmProperties::CoordSystemType)ep.GetCoordinateSystem() );

   return p;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _UNITTEST

bool Test_TransformProperties(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmShapeUtils - Test_TransformProperties");

   gmElasticProperties ep(10,gpPoint2d(10,10),10,10,10,10,-10,-10,10, 0);
   gmProperties p = gmShapeUtils::TransformProperties( ep, 2 );
   TRY_TESTME( IsEqual( p.Area(), 5.) );
   TRY_TESTME( IsEqual( p.Ixx(), 5.) );
   TRY_TESTME( IsEqual( p.Iyy(), 5.) );
   TRY_TESTME( IsEqual( p.Ixy(), 5.) );
   TRY_TESTME( IsEqual( p.Ytop(), ep.Ytop() ) );
   TRY_TESTME( IsEqual( p.Ybottom(), ep.Ybottom() ) );
   TRY_TESTME( IsEqual( p.Xleft(), ep.Xleft() ) );
   TRY_TESTME( IsEqual( p.Xright(), ep.Xright() ) );
   TRY_TESTME( p.GetOrigin() == ep.GetOrigin() );
   TRY_TESTME( p.GetOrientation() == ep.GetOrientation() );
   TRY_TESTME( p.GetCoordinateSystem() == (gmProperties::CoordSystemType)ep.GetCoordinateSystem() );

   TESTME_EPILOG("gmShapeUtils - Test_TransformProperties");
}

bool gmShapeUtils::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmShapeUtils");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TRY_TESTME( Test_TransformProperties(rlog) );

   TESTME_EPILOG("gmShapeUtils");
}
#endif // _UNITTEST


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmShapeUtils::~gmShapeUtils()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


