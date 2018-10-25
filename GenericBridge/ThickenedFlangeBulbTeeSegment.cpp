///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// ThickenedFlangeBulbTeeSegment.cpp : Implementation of CThickenedFlangeBulbTeeSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "ThickenedFlangeBulbTeeSegment.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThickenedFlangeBulbTeeSegment
HRESULT CThickenedFlangeBulbTeeSegment::FinalConstruct()
{
   //m_pGirderLine = nullptr;
   //m_Orientation = 0;
   //m_HaunchDepth[0] = 0;
   //m_HaunchDepth[1] = 0;
   //m_HaunchDepth[2] = 0;
   //m_Fillet = 0;
   //m_Precamber = 0;

   m_FlangeThickening = 0;
   m_FlangeThickeningType = ttEnds;

   return S_OK;
}

void CThickenedFlangeBulbTeeSegment::FinalRelease()
{
   //m_pGirderLine = nullptr;
   m_Shapes.clear();
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISegment,
      &IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// ISuperstructureMemberSegment implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Section(StageIndexType stageIdx,Float64 Xs,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   HRESULT hr;
   CComPtr<IShape> primaryShape;
   hr = get_PrimaryShape(Xs, &primaryShape);
   ATLASSERT(SUCCEEDED(hr));
   if ( FAILED(hr) )
   {
      return hr;
   }

   // create our section object
   CComPtr<ICompositeSectionEx> section;
   section.CoCreateInstance(CLSID_CompositeSectionEx);

   section->QueryInterface(IID_ISection,(void**)ppSection);
   ATLASSERT(*ppSection != nullptr);

   // add the primary shape
   Float64 Efg = 0;
   m_Shapes.front().FGMaterial->get_E(stageIdx,&Efg);
   
   Float64 Ebg = 0;
   if ( m_Shapes.front().BGMaterial )
   {
      m_Shapes.front().BGMaterial->get_E(stageIdx,&Ebg);
   }

   Float64 Dfg = 0;
   m_Shapes.front().FGMaterial->get_Density(stageIdx,&Dfg);
   
   Float64 Dbg = 0;
   if ( m_Shapes.front().BGMaterial )
   {
      m_Shapes.front().BGMaterial->get_Density(stageIdx,&Dbg);
   }

   section->AddSection(primaryShape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);

   // Add joint
   Float64 Ejoint(0), Djoint(0);
   if (m_JointMaterial)
   {
      m_JointMaterial->get_E(stageIdx, &Ejoint);
      m_JointMaterial->get_Density(stageIdx, &Djoint);
   }

   CComQIPtr<IBulbTeeSection> btSection(primaryShape);
   ATLASSERT(btSection);
   CComPtr<IShape> leftJoint, rightJoint;
   GetJointShapes(Xs, btSection, &leftJoint, &rightJoint);

   btSection->SetJointShapes(leftJoint, rightJoint);

   if (!IsZero(Ejoint))
   {
      if (leftJoint)
      {
         section->AddSection(leftJoint, Ejoint, 0, Djoint, 0, VARIANT_TRUE);
      }

      if (rightJoint)
      {
         section->AddSection(rightJoint, Ejoint, 0, Djoint, 0, VARIANT_TRUE);
      }
   }

   // add all the secondary shapes
   std::vector<ShapeData>::iterator iter(m_Shapes.begin());
   std::vector<ShapeData>::iterator end(m_Shapes.end());
   iter++; // skip the first shape, we already processed it

   for ( ; iter != end; iter++ )
   {
      ShapeData& shapeData = *iter;

      Float64 Efg = 0;
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_E(stageIdx,&Efg);
      }

      Float64 Ebg;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_E(stageIdx,&Ebg);
      }

      Float64 Dfg = 0;
      if ( shapeData.FGMaterial )
      {
         shapeData.FGMaterial->get_Density(stageIdx,&Dfg);
      }

      Float64 Dbg = 0;
      if ( shapeData.BGMaterial )
      {
         shapeData.BGMaterial->get_Density(stageIdx,&Dbg);
      }

      CComPtr<IShape> shape;
      shapeData.Shape->Clone(&shape);

      section->AddSection(shape,Efg,Ebg,Dfg,Dbg,VARIANT_TRUE);
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_PrimaryShape(Float64 Xs,IShape** ppShape)
{
   CComPtr<IShape> girderShape;
   get_GirderShape(Xs, &girderShape);

   CComQIPtr<IBulbTeeSection> btSection(girderShape);
   ATLASSERT(btSection);
   CComPtr<IShape> leftJoint, rightJoint;
   GetJointShapes(Xs, btSection, &leftJoint, &rightJoint);

   btSection->SetJointShapes(leftJoint, rightJoint);

   girderShape.CopyTo(ppShape);

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   CComPtr<IPolyShape> shape;
   shape.CoCreateInstance(CLSID_PolyShape);

   Float64 l;
   Float64 brgOffset, endDist;
   if (bIncludeClosure == VARIANT_TRUE)
   {
      m_Impl.m_pGirderLine->get_LayoutLength(&l);
      brgOffset = 0;
      endDist = 0;
   }
   else
   {
      m_Impl.m_pGirderLine->get_GirderLength(&l);
      m_Impl.m_pGirderLine->get_BearingOffset(etStart, &brgOffset);
      m_Impl.m_pGirderLine->get_EndDistance(etStart, &endDist);
   }

   shape->AddPoint(l,0.0); // bottom right

   Float64 Ls;
   m_Impl.m_pGirderLine->get_GirderLength(&Ls);

   int nPoints = 21;
   int nSpaces = nPoints - 1;
   if (!IsZero(m_Impl.m_Precamber))
   {
      // work right to left along bottom of segment
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = Ls - i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x,Ls);
         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }
         shape->AddPoint(x, y);
      }
   }

   shape->AddPoint(0.0,0.0); // bottom left

   CComQIPtr<IBulbTeeSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // get dimensions of beam shape at start and end of segment
   CComPtr<IBulbTee2> pcBeam;
   beam->get_Beam(&pcBeam);

   Float64 H;
   pcBeam->get_MaxHeight(&H);

   // work left to right along top of segment
   if (!IsZero(m_Impl.m_Precamber) || !IsZero(m_FlangeThickening))
   {
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = i*Ls / nSpaces;
         Float64 top_flange_thickening = GetFlangeThickening(x);
         Float64 precamber = m_Impl.ComputePrecamber(x,Ls);
         Float64 y = H + top_flange_thickening + precamber;

         if (bIncludeClosure == VARIANT_TRUE)
         {
            x += (brgOffset - endDist);
         }

         shape->AddPoint(x, y);
      }
   }
   else
   {
      shape->AddPoint(0.0, H); // top left
      shape->AddPoint(l, H); // top right
   }

   // Shape is to be in girder path coordinates so (0,0) is at the CL Pier and at the elevation of the top of the shape
   //
   // CL Pier   Start of segment
   // |         |       CL Bearing
   // |(0,0)    |       |
   // *         +-------+---------------\  
   // |         |       .               /
   // |         +-------+---------------\  
   // |         |endDist|
   // |         |<----->|
   // |                 |
   // |    brgOffset    |
   // |<--------------->|
   //
   //          Elevation View

   // The bottom left coordinate is currently at (0,0)
   // The shape needs to be moved horizontally by a distance of brgOffset-endDist
   // and vertically by a distance equal to the height of the girder at its left CL Brg

   CComQIPtr<IXYPosition> position(shape);
   CComPtr<IPoint2d> topLeft;
   position->get_LocatorPoint(lpTopLeft, &topLeft);
   topLeft->Move(0, 0);
   Float64 netUpwardAdjustment = m_Impl.m_Precamber;
   if (m_FlangeThickeningType == ttCenter)
   {
      netUpwardAdjustment += m_FlangeThickening;
   }
   else
   {
      netUpwardAdjustment -= m_FlangeThickening;
   }

   if ( 0 < netUpwardAdjustment)
   {
      topLeft->Offset(0, netUpwardAdjustment);
   }

   topLeft->Offset(brgOffset - endDist, 0);

   position->put_LocatorPoint(lpTopLeft, topLeft);

   shape->QueryInterface(ppShape);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// IThickenedFlangeSegment implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::AddShape(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial)
{
   CHECK_IN(pShape);

   if ( m_Shapes.size() == 0 )
   {
      CComQIPtr<IBulbTeeSection> beam(pShape);
      if ( beam == nullptr )
      {
         ATLASSERT(false); // first shape must be a flanged girder section
         return E_INVALIDARG;
      }
   }

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_ShapeCount(IndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_Shapes.size();
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_ForegroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].FGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_BackgroundMaterial(IndexType index,IMaterial* *material)
{
   if ( m_Shapes.size() <= index || index == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(material);
   (*material) = m_Shapes[index].BGMaterial;

   if ( *material )
   {
      (*material)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_GirderShape(Float64 Xs, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0)
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IBulbTeeSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

                    // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;

   // get dimensions of beam shape at start and end of segment
   CComPtr<IBulbTee2> pcBeam;

   Float64 W1, W2, W3, W4, W5, W6;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   Float64 T1, T2;
   Float64 C1, C2;
   Float64 n1, n2;

   beam->get_Beam(&pcBeam);

   pcBeam->get_W1(&W1);
   pcBeam->get_W2(&W2);
   pcBeam->get_W3(&W3);
   pcBeam->get_W4(&W4);
   pcBeam->get_W5(&W5);
   pcBeam->get_W6(&W6);

   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);
   pcBeam->get_D6(&D6);
   pcBeam->get_D7(&D7);

   pcBeam->get_T1(&T1);
   pcBeam->get_T2(&T2);

   pcBeam->get_C1(&C1);
   pcBeam->get_C2(&C2);

   pcBeam->get_n1(&n1);
   pcBeam->get_n2(&n2);

   // parabolic interpolation of the depth of the top flange thickening

   Float64 top_flange_thickening = GetFlangeThickening(Xs);

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IBulbTeeSection> btSection(newShape);
   CComPtr<IBulbTee2> newBeam;
   btSection->get_Beam(&newBeam);
   newBeam->put_D1(D1 + top_flange_thickening); // basic top flange thickness plus thicken of the top flange
   newBeam->put_D2(D2);
   newBeam->put_D3(D3);
   newBeam->put_D4(D4);
   newBeam->put_D5(D5);
   newBeam->put_D6(D6);
   newBeam->put_D7(D7);
   newBeam->put_W1(W1);
   newBeam->put_W2(W2);
   newBeam->put_W3(W3);
   newBeam->put_W4(W4);
   newBeam->put_W5(W5); // left top flange overhang
   newBeam->put_W6(W6); // right top flange overhang
   newBeam->put_T1(T1);
   newBeam->put_T2(T2);
   newBeam->put_C1(C1);
   newBeam->put_C2(C2); // location of crown point measured from left flange tip
   newBeam->put_n1(n1); // left crown slope
   newBeam->put_n2(n2); // right crown slope

   AdjustPosition(Xs, btSection, newShape);

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_FlangeThickeningType(ThickeningType type)
{
   m_FlangeThickeningType = type;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_FlangeThickening(Float64 flangeThickening)
{
   m_FlangeThickening = flangeThickening;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_TopFlangeThickening(Float64 Xs, Float64* pThickening)
{
   CHECK_RETVAL(pThickening);
   *pThickening = GetFlangeThickening(Xs);
   return S_OK;
}

////////////////////////////////////////////////////////////////////
// ILongitudinalJoints implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_HasJoints(VARIANT_BOOL* pbHasJoints)
{
   CHECK_RETVAL(pbHasJoints);
   *pbHasJoints = (m_JointMaterial == nullptr ? VARIANT_FALSE : VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::putref_JointMaterial(IMaterial* material)
{
   CHECK_IN(material);
   m_JointMaterial = material;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_JointMaterial(IMaterial** material)
{
   CHECK_RETOBJ(material);
   return m_JointMaterial.CopyTo(material);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_JointShapes(Float64 Xs, IShape** ppLeftJoint, IShape** ppRightJoint)
{
   CComPtr<IShape> primaryShape;
   get_PrimaryShape(Xs,&primaryShape);
   CComQIPtr<IBulbTeeSection> btSection(primaryShape);
   ATLASSERT(btSection);
   return GetJointShapes(Xs, btSection, ppLeftJoint, ppRightJoint);
}

////////////////////////////////////////////////////////////////////
// IItemData implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::AddItemData(BSTR name,IUnknown* data)
{
   return m_ItemDataMgr.AddItemData(name,data);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetItemData(BSTR name,IUnknown** data)
{
   return m_ItemDataMgr.GetItemData(name,data);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::RemoveItemData(BSTR name)
{
   return m_ItemDataMgr.RemoveItemData(name);
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetItemDataCount(CollectionIndexType* count)
{
   return m_ItemDataMgr.GetItemDataCount(count);
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::Load(IStructuredLoad2* load)
{
   return E_NOTIMPL;
   //CComVariant var;
   //load->BeginUnit(CComBSTR("Segment"));

   //load->get_Property(CComBSTR("Length"),&var);
   //m_Length = var.dblVal;

   //m_Shape.Release();
   //load->get_Property(CComBSTR("Shape"),&var);
   //if ( var.vt == VT_UNKNOWN )
   //   var.punkVal->QueryInterface(&m_Shape);

   //VARIANT_BOOL bEnd;
   //load->EndUnit(&bEnd);
   //return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::Save(IStructuredSave2* save)
{
   return E_NOTIMPL;
   //save->BeginUnit(CComBSTR("Segment"),1.0);

   //save->put_Property(CComBSTR("Length"),CComVariant(m_Length));
   //if ( m_Shape )
   //   save->put_Property(CComBSTR("Shape"),CComVariant(m_Shape));
   //else
   //   save->put_Property(CComBSTR("Shape"),CComVariant(0));

   //save->EndUnit();
   //return S_OK;
}

Float64 CThickenedFlangeBulbTeeSegment::GetFlangeThickening(Float64 Xs)
{
   // parabolic interpolation of the depth of the top flange thickening
   Float64 segLength;
   get_Length(&segLength);

   Float64 thickening;
   if (m_FlangeThickeningType == ttEnds)
   {
      thickening = 4 * m_FlangeThickening*Xs*Xs / (segLength*segLength) - 4 * m_FlangeThickening*Xs / segLength + m_FlangeThickening;
   }
   else
   {
      thickening = -4 * m_FlangeThickening*Xs*Xs / (segLength*segLength) + 4 * m_FlangeThickening*Xs / segLength;
   }
   return thickening;
}

HRESULT CThickenedFlangeBulbTeeSegment::AdjustPosition(Float64 distAlongSegment, IBulbTeeSection* pSection, IShape* pShape)
{
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this, distAlongSegment, &pntTopCenter); // this is the top center of the bounding box in bridge coordinates

                                                                 // adjust the top center point so that the top of the girder is at the correct elevation,
                                                                 // not the top center of the bounding box.

                                                                 // because the top flange may be sloped and the high point can be anywhere along the top of the girder
                                                                 // we need to adjust the elevation of the top center of the bounding box by the difference in elevation between
                                                                 // the top edge of the bounding box and the top of the actual girder on the vertical line passing through
                                                                 // the top center of the bounding box.


   CComPtr<IBulbTee2> pcBeam;
   pSection->get_Beam(&pcBeam);

   Float64 W5, W6;
   Float64 C2;
   Float64 n1, n2;

   pcBeam->get_W5(&W5); // distance from left side of girder at grade n1
   pcBeam->get_W6(&W6); // distance from right side of girder at grade n2
   pcBeam->get_C2(&C2); // distance from left edge to grade break between n1 and n2
   pcBeam->get_n1(&n1); // grade on left side of girder
   pcBeam->get_n2(&n2); // grade on right side of girder

   Float64 W = 0.5*(W5 + W6); // this is the center point measured from the left

   if (IsEqual(C2, W) && 0 < n1 && n2 < 0)
   {
      // do nothing
      // The crown point is exactly on the CL of the girder and it is higher than the flange tips
      // The top center point is in the correct location
   }
   else
   {
      pntTopCenter->Offset(0, fabs(n1*C2 + n2*(W - C2))); // raise the top center of the bounding box by the approprate amount, which will raise the girder to the correct elevlation
   }

   CComQIPtr<IXYPosition> position(pShape);
   position->put_LocatorPoint(lpTopCenter, pntTopCenter);

   return S_OK;
}

HRESULT CThickenedFlangeBulbTeeSegment::GetJointShapes(Float64 Xs, IBulbTeeSection* pSection, IShape** ppLeftJoint, IShape** ppRightJoint)
{
   CHECK_RETOBJ(ppLeftJoint);
   CHECK_RETOBJ(ppRightJoint);

   LocationType location;
   m_Impl.m_pSSMbr->get_LocationType(&location);

   CComPtr<IGenericBridge> bridge;
   m_Impl.m_pSSMbr->get_Bridge(&bridge);

   CComPtr<IBulbTee2> beam;
   pSection->get_Beam(&beam);

   Float64 W5, W6;
   beam->get_W5(&W5);
   beam->get_W6(&W6);

   CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
   beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCentral, &rightTop, &rightBottom);

   Float64 Hl, Hc, Hr;
   beam->GetTopFlangeThickness(&Hl, &Hc, &Hr);

   CComPtr<IPath> path;
   m_Impl.m_pGirderLine->get_Path(&path);

   CComPtr<IPoint2d> pntOnThisSegment;
   path->LocatePoint(Xs, omtAlongDirection, 0.0, CComVariant(0.0), &pntOnThisSegment);

   CComPtr<IDirection> dirNormal;
   path->Normal(Xs, &dirNormal);
   Float64 normal;
   dirNormal->get_Value(&normal);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_Direction(normal);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(pntOnThisSegment, v);

   CComQIPtr<IXYPosition> position(pSection);
   ATLASSERT(position);
   if (location != ltLeftExteriorGirder)
   {
      GirderIDType leftSSMbrID;
      m_Impl.m_pSSMbr->get_LeftSSMbrID(&leftSSMbrID);
      CComPtr<ISuperstructureMember> leftSSMbr;
      bridge->get_SuperstructureMember(leftSSMbrID, &leftSSMbr);

      if (leftSSMbr == nullptr)
      {
         return E_FAIL;
      }

      CComPtr<ISuperstructureMemberSegment> leftSegment;
      leftSSMbr->get_Segment(0, &leftSegment); // assuming there is only one segment per superstructure member

      CComPtr<IGirderLine> leftGirderLine;
      leftSegment->get_GirderLine(&leftGirderLine);

      CComPtr<IPath> leftPath;
      leftGirderLine->get_Path(&leftPath);

      CComPtr<IPoint2d> pntOnLeftSegment;
      leftPath->Intersect(line, pntOnThisSegment, &pntOnLeftSegment);

      Float64 spacing;
      pntOnThisSegment->DistanceEx(pntOnLeftSegment, &spacing);

      CComPtr<IPoint2d> pntAtStartOfLeftGirderLine;
      leftGirderLine->get_EndPoint(etStart, &pntAtStartOfLeftGirderLine);

      Float64 distAlongLeftGirderLine;
      pntAtStartOfLeftGirderLine->DistanceEx(pntOnLeftSegment, &distAlongLeftGirderLine);

      CComQIPtr<IThickenedFlangeSegment> segment(leftSegment);

      CComPtr<IShape> leftGirderShape;
      segment->get_GirderShape(distAlongLeftGirderLine, &leftGirderShape);

      CComQIPtr<IBulbTeeSection> leftSection(leftGirderShape);
      CComPtr<IBulbTee2> leftBeam;
      leftSection->get_Beam(&leftBeam);

      Float64 leftW5, leftW6;
      leftBeam->get_W5(&leftW5);
      leftBeam->get_W6(&leftW6);

      Float64 jointWidth = spacing - (W5 + leftW6);
      if (!IsZero(jointWidth))
      {
         Float64 leftHl, leftHc, leftHr;
         leftBeam->GetTopFlangeThickness(&leftHl, &leftHc, &leftHr);

         CComPtr<IPoint2d> pnt1;
         pnt1.CoCreateInstance(CLSID_Point2d);
         pnt1->MoveEx(leftTop);
         pnt1->Offset(-jointWidth / 2, 0);

         CComPtr<IPoint2d> pnt2;
         pnt2.CoCreateInstance(CLSID_Point2d);
         pnt2->MoveEx(leftBottom);
         pnt2->Offset(-jointWidth / 2, (Hl - leftHr) / 2);

         CComPtr<IPolyShape> joint;
         joint.CoCreateInstance(CLSID_PolyShape);
         joint->AddPointEx(pnt1); // top right of joint
         joint->AddPointEx(pnt2); // bottom right of joint
         joint->AddPointEx(leftBottom); // bottom left of joint
         joint->AddPointEx(leftTop); // top left of joint

         CComQIPtr<IShape> shape(joint);
         shape.CopyTo(ppLeftJoint);
      }
   }

   if (location != ltRightExteriorGirder)
   {
      GirderIDType rightSSMbrID;
      m_Impl.m_pSSMbr->get_RightSSMbrID(&rightSSMbrID);
      CComPtr<ISuperstructureMember> rightSSMbr;
      bridge->get_SuperstructureMember(rightSSMbrID, &rightSSMbr);

      if (rightSSMbr == nullptr)
      {
         return E_FAIL;
      }

      CComPtr<ISuperstructureMemberSegment> rightSegment;
      rightSSMbr->get_Segment(0, &rightSegment); // assuming there is only one segment per superstructure member

      CComPtr<IGirderLine> rightGirderLine;
      rightSegment->get_GirderLine(&rightGirderLine);

      CComPtr<IPath> rightPath;
      rightGirderLine->get_Path(&rightPath);

      CComPtr<IPoint2d> pntOnRightSegment;
      rightPath->Intersect(line, pntOnThisSegment, &pntOnRightSegment);

      Float64 spacing;
      pntOnThisSegment->DistanceEx(pntOnRightSegment, &spacing);

      CComPtr<IPoint2d> pntAtStartOfRightGirderLine;
      rightGirderLine->get_EndPoint(etStart, &pntAtStartOfRightGirderLine);

      Float64 distAlongRightGirderLine;
      pntAtStartOfRightGirderLine->DistanceEx(pntOnRightSegment, &distAlongRightGirderLine);

      CComQIPtr<IThickenedFlangeSegment> segment(rightSegment);

      CComPtr<IShape> rightGirderShape;
      segment->get_GirderShape(distAlongRightGirderLine, &rightGirderShape);

      CComQIPtr<IBulbTeeSection> rightSection(rightGirderShape);
      CComPtr<IBulbTee2> rightBeam;
      rightSection->get_Beam(&rightBeam);

      Float64 rightW5, rightW6;
      rightBeam->get_W5(&rightW5);
      rightBeam->get_W6(&rightW6);

      Float64 jointWidth = spacing - (W6 + rightW5);
      if (!IsZero(jointWidth))
      {
         Float64 rightHl, rightHc, rightHr;
         rightBeam->GetTopFlangeThickness(&rightHl, &rightHc, &rightHr);

         CComPtr<IPoint2d> pnt1;
         pnt1.CoCreateInstance(CLSID_Point2d);
         pnt1->MoveEx(rightTop);
         pnt1->Offset(jointWidth / 2, 0);

         CComPtr<IPoint2d> pnt2;
         pnt2.CoCreateInstance(CLSID_Point2d);
         pnt2->MoveEx(rightBottom);
         pnt2->Offset(jointWidth / 2, (Hr - rightHl) / 2);

         CComPtr<IPolyShape> joint;
         joint.CoCreateInstance(CLSID_PolyShape);
         joint->AddPointEx(pnt1); // top right of joint
         joint->AddPointEx(pnt2); // bottom right of joint
         joint->AddPointEx(rightBottom); // bottom left of joint
         joint->AddPointEx(rightTop); // top left of joint

         CComQIPtr<IShape> shape(joint);
         shape.CopyTo(ppRightJoint);
      }
   }

   return S_OK;
}
