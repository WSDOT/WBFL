///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <GenericBridge\Helpers.h>
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
   m_FlangeThickening = 0;
   m_FlangeThickeningType = ttEnds;

   m_JointSectionType = jstConstantDepth;
   m_LongitudinalJointThickness = 0;

   return S_OK;
}

void CThickenedFlangeBulbTeeSegment::FinalRelease()
{
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
STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Section(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection)
{
   CHECK_RETOBJ(ppSection);

   if (m_Shapes.size() == 0 )
   {
      *ppSection = 0;
      return S_OK;
   }

   HRESULT hr;
   CComPtr<IShape> primaryShape;
   hr = get_PrimaryShape(Xs,sectionBias,coordinateSystem,&primaryShape);
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

   CComQIPtr<IJointedSection> jointedSection(primaryShape);
   ATLASSERT(jointedSection);
   CComPtr<IShape> leftJoint, rightJoint;
   jointedSection->GetJointShapes(&leftJoint, &rightJoint);

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

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_PrimaryShape(Float64 Xs,SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CComPtr<IShape> girderShape;
   get_GirderShape(Xs, coordinateSystem, &girderShape);

   CComPtr<IShape> shape;
   if (coordinateSystem == cstGirder)
   {
      get_GirderShape(Xs, cstBridge, &shape);
   }
   else
   {
      shape = girderShape;
   }

   CComQIPtr<IFlangedDeckedSection> section(shape);
   ATLASSERT(section);
   CComPtr<IShape> leftJoint, rightJoint;
   CreateJointShapes(Xs, section, coordinateSystem, &leftJoint, &rightJoint);

   CComQIPtr<IJointedSection> jointedSection(girderShape);
   jointedSection->SetJointShapes(leftJoint, rightJoint);

   girderShape.CopyTo(ppShape);

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::GetVolumeAndSurfaceArea(Float64* pVolume, Float64* pSurfaceArea)
{
   CHECK_RETVAL(pVolume);
   CHECK_RETVAL(pSurfaceArea);

   if (m_bUpdateVolumeAndSurfaceArea)
   {
      if (m_Shapes.size() == 0)
      {
         m_Volume = 0;
         m_SurfaceArea = 0;
      }
      else
      {
         Float64 L;
         get_Length(&L);

         if (IsZero(m_FlangeThickening))
         {
            Float64 perimeter;
            m_Shapes.front().Shape->get_Perimeter(&perimeter);

            CComPtr<IShapeProperties> shapeProps;
            m_Shapes.front().Shape->get_ShapeProperties(&shapeProps);

            Float64 area;
            shapeProps->get_Area(&area);


            m_Volume = area*L;
            m_SurfaceArea = perimeter*L + 2 * area;
         }
         else
         {
            Float64 X = 0;
            CComPtr<IShape> shape;
            get_PrimaryShape(X, sbRight, cstGirder, &shape); // don't use the shape in m_Shapes. There is to flange thickening so we have to
                                                              // get the primary shape so the effect of TFT is included
            Float64 prev_perimeter;
            shape->get_Perimeter(&prev_perimeter);

            CComPtr<IShapeProperties> shapeProps;
            shape->get_ShapeProperties(&shapeProps);

            Float64 start_area;
            shapeProps->get_Area(&start_area);

            Float64 prev_area = start_area;

            Float64 V = 0;
            Float64 S = 0;
            IndexType nSections = 10;
            Float64 dx = L / nSections;
            for (IndexType i = 1; i <= nSections; i++)
            {
               X += dx;

               shape.Release();
               get_PrimaryShape(X, sbLeft, cstGirder, &shape);

               Float64 perimeter;
               shape->get_Perimeter(&perimeter);

               shapeProps.Release();
               shape->get_ShapeProperties(&shapeProps);
               Float64 area;
               shapeProps->get_Area(&area);

               Float64 avg_perimeter = (prev_perimeter + perimeter)/* / 2*/; // save the divide by 2 for outside the loop
               Float64 avg_area = (prev_area + area) /* / 2*/; // save the divide by 2 for outside the loop

               S += avg_perimeter*dx;
               V += avg_area*dx;

               prev_perimeter = perimeter;
               prev_area = area;
            }

            // divide by 2 now
            S /= 2;
            V /= 2;

            Float64 end_area;
            shapeProps->get_Area(&end_area);

            S += start_area + end_area;

            m_Volume = V;
            m_SurfaceArea = S;
         }
      }

      m_bUpdateVolumeAndSurfaceArea = false;
   }

   *pVolume = m_Volume;
   *pSurfaceArea = m_SurfaceArea;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_InternalSurfaceAreaOfVoids(Float64* pSurfaceArea)
{
   CHECK_RETVAL(pSurfaceArea);
   *pSurfaceArea = 0;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_Profile(VARIANT_BOOL bIncludeClosure,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   CComPtr<IPolyShape> shape;
   shape.CoCreateInstance(CLSID_PolyShape);

   CComPtr<ISegment> prevSegment;
   get_PrevSegment(&prevSegment);

   CComPtr<ISegment> nextSegment;
   get_NextSegment(&nextSegment);

   Float64 l;
   Float64 brgOffset, endDist;
   if (bIncludeClosure == VARIANT_TRUE && nextSegment)
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

   CComQIPtr<IFlangedDeckedSection> section(m_Shapes.front().Shape);
   ATLASSERT(section);

   Float64 H;
   section->GetMaxHeight(&H);

   shape->AddPoint(0.0,0.0); // bottom left

   Float64 Ls;
   m_Impl.m_pGirderLine->get_GirderLength(&Ls);

   int nPoints = 21;
   int nSpaces = nPoints - 1;
   if (!IsZero(m_Impl.m_Precamber))
   {
      // work left to right along bottom of segment
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = i*Ls / nSpaces;
         Float64 y = m_Impl.ComputePrecamber(x,Ls);
         if (bIncludeClosure == VARIANT_TRUE && prevSegment)
         {
            x += (brgOffset - endDist);
         }
         shape->AddPoint(x, y);
      }
   }

   shape->AddPoint(Ls,0.0); // bottom right

   if (bIncludeClosure == VARIANT_TRUE && nextSegment)
   {
      shape->AddPoint(l, 0.0);
   }


   // work right to keft along top of segment
   if (!IsZero(m_Impl.m_Precamber) || !IsZero(m_FlangeThickening))
   {
      for (int i = 0; i < nPoints; i++)
      {
         Float64 x = Ls - i*Ls / nSpaces;
         Float64 top_flange_thickening = ComputeTopFlangeThickening(x, Ls, m_FlangeThickeningType, m_FlangeThickening);

         Float64 precamber = m_Impl.ComputePrecamber(x,Ls);
         Float64 y = H + top_flange_thickening + precamber;

         if (bIncludeClosure == VARIANT_TRUE && prevSegment)
         {
            x += (brgOffset - endDist);
         }

         shape->AddPoint(x, y);
      }
   }
   else
   {
      shape->AddPoint(l, H); // top right
      shape->AddPoint(0.0, H); // top left
   }

   // Shape is to be in girder path coordinates so X = 0 is at the CL Pier
   // Y = 0 is also at the CL Pier and is estabilished by projecting a horizontal
   // line from the top,left corner of the profile... That is, the elevation of the top
   // left corner of the profile is 0.
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
      CComQIPtr<IFlangedDeckedSection> section(pShape);
      if (section == nullptr)
      {
         ATLASSERT(false); // first shape must be a flanged deck section
         return E_INVALIDARG;
      }
   }

   ShapeData shapeData;
   shapeData.Shape = pShape;
   shapeData.FGMaterial = pFGMaterial;
   shapeData.BGMaterial = pBGMaterial;

   m_Shapes.push_back(shapeData);

   m_bUpdateVolumeAndSurfaceArea = true;
   m_Volume = -1;
   m_SurfaceArea = -1;
   m_ShapeCache.clear();

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

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_GirderShape(Float64 Xs, SectionCoordinateSystemType coordinateSystem, IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0)
   {
      *ppShape = 0;
      return S_OK;
   }

   CComPtr<IShape> newShape;

   auto found = m_ShapeCache.find(Xs);
   if (found != m_ShapeCache.end())
   {
      found->second->Clone(&newShape);
   }
   else
   {
      m_Shapes.front().Shape->Clone(&newShape);

      Float64 Ls;
      get_Length(&Ls);
      Float64 top_flange_thickening = ComputeTopFlangeThickening(Xs, Ls, m_FlangeThickeningType, m_FlangeThickening);

      CComQIPtr<IFlangedDeckedSection> section(newShape);
      section->AddTopFlangeThickening(top_flange_thickening);

      m_ShapeCache.emplace_hint(m_ShapeCache.end(), Xs, newShape);
   }

   if (coordinateSystem == cstBridge)
   {
      // put shape in bridge coordinates
      CComQIPtr<IFlangedDeckedSection> section(newShape);
      AdjustPosition(Xs, section);
   }

   *ppShape = newShape;
   (*ppShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_TopFlangeSlope(Float64* pSlope)
{
   // returns the transverse top flange slope
   CHECK_RETVAL(pSlope);

   if (m_Shapes.size() == 0)
   {
      *pSlope = 0;
      return S_OK;
   }

   CComQIPtr<IFlangedDeckedSection> section(m_Shapes.front().Shape);
   ATLASSERT(section); // if this is nullptr... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;

   Float64 n1, n2;
   section->GetCrownSlopes(&n1, &n2);

   Float64 C2;
   section->GetCrown(&C2);

   Float64 W5, W6;
   section->GetOverhangs(&W5, &W6);

   if (IsZero(C2))
   {
      *pSlope = n2;
   }
   else if (IsEqual(C2,W5+W6))
   {
      *pSlope = n1;
   }
   else
   {
      *pSlope = 0.5*(n1 + n2);
   }

   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_FlangeThickeningType(ThickeningType type)
{
   m_FlangeThickeningType = type;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_FlangeThickeningType(ThickeningType* pType)
{
   CHECK_RETVAL(pType);
   *pType = m_FlangeThickeningType;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_FlangeThickening(Float64 flangeThickening)
{
   if (flangeThickening < 0)
   {
      ATLASSERT(false);
      return E_INVALIDARG;
   }

   m_FlangeThickening = flangeThickening;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_FlangeThickening(Float64* pFlangeThickening)
{
   CHECK_RETVAL(pFlangeThickening);
   *pFlangeThickening = m_FlangeThickening;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_TopFlangeThickening(Float64 Xs, Float64* pThickening)
{
   CHECK_RETVAL(pThickening);

   Float64 Ls;
   get_Length(&Ls);
   *pThickening = ComputeTopFlangeThickening(Xs, Ls, m_FlangeThickeningType, m_FlangeThickening);

   return S_OK;
}

////////////////////////////////////////////////////////////////////
// ILongitudinalJoints implementation
STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_CrossSection(JointSectionType type)
{
   m_JointSectionType = type;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_CrossSection(JointSectionType* pType)
{
   CHECK_RETVAL(pType);
   *pType = m_JointSectionType;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::put_JointThickness(Float64 thickness)
{
   if (thickness < 0)
   {
      return E_INVALIDARG;
   }

   m_LongitudinalJointThickness = thickness;
   return S_OK;
}

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_JointThickness(Float64 * pThickness)
{
   CHECK_RETVAL(pThickness);
   *pThickness = m_LongitudinalJointThickness;
   return S_OK;
}

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

STDMETHODIMP CThickenedFlangeBulbTeeSegment::get_JointShapes(Float64 Xs, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJoint, IShape** ppRightJoint)
{
   CComPtr<IShape> primaryShape;
   get_PrimaryShape(Xs,sbRight, coordinateSystem,&primaryShape);
   CComQIPtr<IJointedSection> section(primaryShape);
   ATLASSERT(section);
   return section->GetJointShapes(ppLeftJoint, ppRightJoint);
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

HRESULT CThickenedFlangeBulbTeeSegment::AdjustPosition(Float64 Xs, IFlangedDeckedSection* pSection)
{
   // This method puts pSection in Bridge Section Coordinates

   // Get the point where the girder line is located in bridge section coordiantes
   // This point corresponds to the point on the top of the girder above the CL web
   CComPtr<IPoint2d> pntGirderLine;
   GB_GetSectionLocation(this, Xs, &pntGirderLine);

   // We don't have direct access to a point in pBeam for the top of girder at CL Web
   // but the hook point is at bottom of beam at CL of web... if we put this point at
   // the right location, the entire shape will be moved to the correct location

   // the beam hook point is at the bottom CL of the web
   // Adjust the position of the beam so that the hook point is horizonally aligned with pntGirderLine and
   // is the CL height below pntGirderLine

   CComPtr<IPoint2d> pntBottomCL;
   pSection->GetBottomCLPoint(&pntBottomCL);

   Float64 x, y;
   pntGirderLine->Location(&x, &y);

   Float64 Hcl;
   pSection->GetCLHeight(&Hcl);

   pntBottomCL->Move(x, y - Hcl);

   return S_OK;
}

HRESULT CThickenedFlangeBulbTeeSegment::CreateJointShapes(Float64 Xs, IFlangedDeckedSection* pSection, SectionCoordinateSystemType coordinateSystem, IShape** ppLeftJoint, IShape** ppRightJoint)
{
   CHECK_RETOBJ(ppLeftJoint);
   CHECK_RETOBJ(ppRightJoint);

   // pSection must be in bridge section coordinates, without orientation effects applied

   LocationType location;
   m_Impl.m_pSSMbr->get_LocationType(&location);

   CComPtr<IGenericBridge> bridge;
   m_Impl.m_pSSMbr->get_Bridge(&bridge);

   CComPtr<ISuperstructureMemberSegment> segment;
   m_Impl.m_pSSMbr->get_Segment(0, &segment); // assuming there is only one segment per superstructure member
   
   Float64 orientation;
   segment->get_Orientation(&orientation);

   Float64 W5, W6;
   pSection->GetOverhangs(&W5, &W6);

   CComQIPtr<IFlangePoints> flangePoints(pSection);
   CComPtr<IPoint2d> leftTop, leftBottom, topCL, topCentral, rightTop, rightBottom;
   flangePoints->GetTopFlangePoints(&leftTop, &leftBottom, &topCL, &topCentral, &rightTop, &rightBottom);

   // Get normal to our girderline
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

   // create a line normal to our girderline
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(pntOnThisSegment, v);

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

      Float64 leftOrientation;
      leftSegment->get_Orientation(&leftOrientation);

      CComPtr<IGirderLine> leftGirderLine;
      leftSegment->get_GirderLine(&leftGirderLine);

      CComPtr<IPath> leftPath;
      leftGirderLine->get_Path(&leftPath);

      // intersect left girder's line with the normal to our line... this is where are going to get the left girder's information
      CComPtr<IPoint2d> pntOnLeftSegment;
      leftPath->Intersect(line, pntOnThisSegment, &pntOnLeftSegment);

      Float64 spacing;
      pntOnThisSegment->DistanceEx(pntOnLeftSegment, &spacing);

      CComPtr<IPoint2d> pntAtStartOfLeftGirderLine;
      leftGirderLine->get_PierPoint(etStart, &pntAtStartOfLeftGirderLine);

      Float64 distAlongLeftGirderLine;
      pntAtStartOfLeftGirderLine->DistanceEx(pntOnLeftSegment, &distAlongLeftGirderLine);

      CComQIPtr<IThickenedFlangeSegment> segment(leftSegment);

      CComPtr<IShape> leftGirderShape;
      segment->get_GirderShape(distAlongLeftGirderLine,cstBridge, &leftGirderShape);

      CComQIPtr<IFlangedDeckedSection> leftSection(leftGirderShape);

      Float64 leftW5, leftW6;
      leftSection->GetOverhangs(&leftW5, &leftW6);

      Float64 jointWidth = spacing - (W5 + leftW6);
      if (!IsZero(jointWidth))
      {
         CComQIPtr<IFlangePoints> flangePoints(leftGirderShape);
         CComPtr<IPoint2d> leftBeam_leftTop, leftBeam_leftBottom, leftBeam_topCL, leftBeam_topCentral, leftBeam_rightTop, leftBeam_rightBottom;
         flangePoints->GetTopFlangePoints(&leftBeam_leftTop, &leftBeam_leftBottom, &leftBeam_topCL, &leftBeam_topCentral, &leftBeam_rightTop, &leftBeam_rightBottom);

         // Edge of joint associated with this girder is half-way between this girder and the girder on the left
         
         // Top points
         Float64 xl, yl, xr, yr;
         leftBeam_rightTop->Location(&xl, &yl);
         leftTop->Location(&xr, &yr);

         CComPtr<IPoint2d> pntTopLeft;
         pntTopLeft.CoCreateInstance(CLSID_Point2d);
         pntTopLeft->Move(0.5*(xl + xr), 0.5*(yl + yr));

         CComPtr<IPoint2d> pntTopRight(leftTop);
         
         CComPtr<IPoint2d> pntBottomLeft, pntBottomRight;
         if (m_JointSectionType == jstConstantDepth)
         {
            pntTopLeft->Clone(&pntBottomLeft);
            pntTopRight->Clone(&pntBottomRight);

            pntBottomLeft->Offset(0, -m_LongitudinalJointThickness);
            pntBottomRight->Offset(0, -m_LongitudinalJointThickness);
         }
         else
         {
            // Bottom point
            leftBeam_rightBottom->Location(&xl, &yl);
            leftBottom->Location(&xr, &yr);

            pntBottomLeft.CoCreateInstance(CLSID_Point2d);
            pntBottomLeft->Move(0.5*(xl + xr), 0.5*(yl + yr));

            pntBottomRight = leftBottom;
         }

         if (!IsZero(orientation) || !IsZero(leftOrientation))
         {
            // make adjust for girder orientation
            Float64 Yr;
            pntTopRight->get_Y(&Yr);
            Float64 Yl;
            pntTopLeft->get_Y(&Yl);
            Float64 dy = Yr - Yl;
            pntTopLeft->Offset(0, dy);
            pntBottomLeft->Offset(0, dy);
         }

         CComPtr<IPolyShape> joint;
         joint.CoCreateInstance(CLSID_PolyShape);
         joint->AddPointEx(pntTopLeft);
         joint->AddPointEx(pntBottomLeft);
         joint->AddPointEx(pntBottomRight);
         joint->AddPointEx(pntTopRight);
        
         if (coordinateSystem == cstGirder)
         {
            CComQIPtr<IXYPosition> position(pSection);
            CComPtr<IPoint2d> pntTC;
            position->get_LocatorPoint(lpTopCenter, &pntTC);
            Float64 dx, dy;
            pntTC->Location(&dx, &dy);

            CComQIPtr<IXYPosition> jntPosition(joint);
            jntPosition->Offset(-dx, -dy);
         }

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

      Float64 rightOrientation;
      rightSegment->get_Orientation(&rightOrientation);

      CComPtr<IGirderLine> rightGirderLine;
      rightSegment->get_GirderLine(&rightGirderLine);

      CComPtr<IPath> rightPath;
      rightGirderLine->get_Path(&rightPath);

      CComPtr<IPoint2d> pntOnRightSegment;
      rightPath->Intersect(line, pntOnThisSegment, &pntOnRightSegment);

      Float64 spacing;
      pntOnThisSegment->DistanceEx(pntOnRightSegment, &spacing);

      CComPtr<IPoint2d> pntAtStartOfRightGirderLine;
      rightGirderLine->get_PierPoint(etStart, &pntAtStartOfRightGirderLine);

      Float64 distAlongRightGirderLine;
      pntAtStartOfRightGirderLine->DistanceEx(pntOnRightSegment, &distAlongRightGirderLine);

      CComQIPtr<IThickenedFlangeSegment> segment(rightSegment);

      CComPtr<IShape> rightGirderShape;
      segment->get_GirderShape(distAlongRightGirderLine, cstBridge, &rightGirderShape);

      CComQIPtr<IFlangedDeckedSection> rightSection(rightGirderShape);

      Float64 rightW5, rightW6;
      rightSection->GetOverhangs(&rightW5,&rightW6);

      Float64 jointWidth = spacing - (W6 + rightW5);
      if (!IsZero(jointWidth))
      {
         CComQIPtr<IFlangePoints> flangePoints(rightGirderShape);
         CComPtr<IPoint2d> rightBeam_leftTop, rightBeam_leftBottom, rightBeam_topCL, rightBeam_topCentral, rightBeam_rightTop, rightBeam_rightBottom;
         flangePoints->GetTopFlangePoints(&rightBeam_leftTop, &rightBeam_leftBottom, &rightBeam_topCL, &rightBeam_topCentral, &rightBeam_rightTop, &rightBeam_rightBottom);

         CComPtr<IPoint2d> pntTopLeft(rightTop);

         Float64 xl, yl, xr, yr;
         rightTop->Location(&xl, &yl);
         rightBeam_leftTop->Location(&xr, &yr);

         CComPtr<IPoint2d> pntTopRight;
         pntTopRight.CoCreateInstance(CLSID_Point2d);
         pntTopRight->Move(0.5*(xl + xr), 0.5*(yl + yr));


         CComPtr<IPoint2d> pntBottomLeft, pntBottomRight;
         if (m_JointSectionType == jstConstantDepth)
         {
            pntTopLeft->Clone(&pntBottomLeft);
            pntTopRight->Clone(&pntBottomRight);

            pntBottomLeft->Offset(0, -m_LongitudinalJointThickness);
            pntBottomRight->Offset(0, -m_LongitudinalJointThickness);
         }
         else
         {
            rightBottom->Location(&xl, &yl);
            rightBeam_leftBottom->Location(&xr, &yr);

            pntBottomRight.CoCreateInstance(CLSID_Point2d);
            pntBottomRight->Move(0.5*(xl + xr), 0.5*(yl + yr));

            pntBottomLeft = rightBottom;
         }

         if (!IsZero(orientation) || !IsZero(rightOrientation))
         {
            // make adjust for girder orientation
            Float64 Yr;
            pntTopRight->get_Y(&Yr);
            Float64 Yl;
            pntTopLeft->get_Y(&Yl);
            Float64 dy = Yr - Yl;
            pntTopRight->Offset(0, -dy);
            pntBottomRight->Offset(0, -dy);
         }

         CComPtr<IPolyShape> joint;
         joint.CoCreateInstance(CLSID_PolyShape);
         joint->AddPointEx(pntTopLeft);
         joint->AddPointEx(pntBottomLeft);
         joint->AddPointEx(pntBottomRight);
         joint->AddPointEx(pntTopRight);

         if (coordinateSystem == cstGirder)
         {
            CComQIPtr<IXYPosition> position(pSection);
            CComPtr<IPoint2d> pntTC;
            position->get_LocatorPoint(lpTopCenter, &pntTC);
            Float64 dx, dy;
            pntTC->Location(&dx, &dy);

            CComQIPtr<IXYPosition> jntPosition(joint);
            jntPosition->Offset(-dx, -dy);
         }

         CComQIPtr<IShape> shape(joint);
         shape.CopyTo(ppRightJoint);
      }
   }

   return S_OK;
}
