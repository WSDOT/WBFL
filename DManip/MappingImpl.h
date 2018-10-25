///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// MappingImpl.h: interface for the CMappingImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPINGIMPL_H__BCB8A106_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_MAPPINGIMPL_H__BCB8A106_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <Math\CoordMapper1d.h>
#include <vector>

class ATL_NO_VTABLE CMappingImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMappingImpl, &CLSID_Mapping>,
   public iMapping,
   public iCoordinateMap
{
public:
	CMappingImpl();
	virtual ~CMappingImpl();
   HRESULT FinalConstruct();


DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_MAPPING)

BEGIN_COM_MAP(CMappingImpl)
	COM_INTERFACE_ENTRY(iMapping)
   COM_INTERFACE_ENTRY(iCoordinateMap)
END_COM_MAP()

   // iMapping Implementation
   STDMETHOD_(void,PrepareDC)(CDC* dc);
   STDMETHOD_(void,CleanUpDC)(CDC* dc);
   STDMETHOD_(void,CleanUpPrintDC)(CDC* dc);

   STDMETHOD_(void,SetWorldExt)(Float64 wx,Float64 wy);
   STDMETHOD_(void,SetWorldExt)(ISize2d* wExt);
   STDMETHOD_(void,GetWorldExt)(Float64* wx,Float64* wy);
   STDMETHOD_(void,GetWorldExt)(ISize2d* *wExt);

   STDMETHOD_(void,SetWorldOrg)(Float64 wx,Float64 wy);
   STDMETHOD_(void,SetWorldOrg)(IPoint2d* wOrg);
   STDMETHOD_(void,GetWorldOrg)(Float64* wx,Float64* wy);
   STDMETHOD_(void,GetWorldOrg)(IPoint2d* *wOrg);

   STDMETHOD_(void,SetLogicalOrg)(long lx,long ly);
   STDMETHOD_(void,GetLogicalOrg)(long* lx,long* ly);
   STDMETHOD_(void,SetLogicalExt)(long lx,long ly);
   STDMETHOD_(void,GetLogicalExt)(long* lx,long* ly);
   STDMETHOD_(void,GetAdjustedLogicalExt)(long* lx,long* ly);
   STDMETHOD_(void,GetAdjustedWorldExt)(Float64* dx,Float64* dy);

   STDMETHOD_(void,SetMappingMode)(DManip::MapMode mm);
   STDMETHOD_(DManip::MapMode,GetMappingMode)();

   STDMETHOD_(void,SetRotation)(Float64 cx,Float64 cy,Float64 angle);
   STDMETHOD_(void,SetRotation)(IPoint2d* c,Float64 angle);
   STDMETHOD_(void,GetRotation)(Float64* cx,Float64* cy,Float64* angle);

   // iCoordinateMap Implementation
   STDMETHOD_(void,MPtoWP)(Float64 mx,Float64 my,Float64* wx,Float64* wy);
   STDMETHOD_(void,MPtoWP)(IPoint2d* mp,Float64* wx,Float64* wy);

   STDMETHOD_(void,WPtoMP)(Float64 wx,Float64 wy,Float64* mx,Float64* my);
   STDMETHOD_(void,WPtoMP)(IPoint2d* wp,Float64* mx,Float64* my);

   STDMETHOD_(void,WPtoLP)(Float64 wx,Float64 wy,long* lx,long* ly);
   STDMETHOD_(void,WPtoLP)(IPoint2d* wp,long* lx,long* ly);

   STDMETHOD_(void,LPtoWP)(long lx,long ly,Float64* wx,Float64* wy);
   STDMETHOD_(void,LPtoWP)(long lx,long ly,IPoint2d** wp);

   STDMETHOD_(void,WPtoTP)(Float64 wx,Float64 wy,long* tx,long* ty);
   STDMETHOD_(void,TPtoWP)(long tx,long ty,Float64* wx,Float64* wy);

   STDMETHOD_(void,LPtoTP)(long lx,long ly,long* tx,long* ty);
   STDMETHOD_(void,TPtoLP)(long tx,long ty,long* lx,long* ly);

   STDMETHOD_(CSize,GetTextWindowExtent)();

   STDMETHOD_(CSize,GetTextExtent)(const LOGFONT& font, LPCSTR lpszText);

protected:
   void MakeAssignment(const CMappingImpl& other);
   void MakeCopy(const CMappingImpl& other);

private:
   Float64 m_WorldExtentX;
   Float64 m_WorldExtentY;
   Float64 m_WorldOriginX;
   Float64 m_WorldOriginY;
   long   m_LogicalExtentX;
   long   m_LogicalExtentY;
   long   m_OriginalLogicalExtentX;
   long   m_OriginalLogicalExtentY;
   long   m_LogicalOriginX;
   long   m_LogicalOriginY;

   // do these divisions once and store the result
   // otherwise they would have to happen thousands for times
   // for every point that gets mapped
   void UpdateMappingScale();
   Float64 m_WEX_over_LEX; // m_WorldExtentX/m_LogicalExtentX
   Float64 m_WEY_over_LEY; // m_WorldExtentY/m_LogicalExtentY
   Float64 m_LEX_over_WEX; // m_LogicalExtentX/m_WorldExtentX
   Float64 m_LEY_over_WEY; // m_LogicalExtentY/m_WorldExtentY

   Float64 m_Rotation; // rotation angle;
   Float64 m_RotationX; 
   Float64 m_RotationY; // center of rotation
   Float64 m_cosR; // cosine of the rotation angle
   Float64 m_sinR; // sine of the rotation angle

   DManip::MapMode         m_MappingMode;

   // use a stack to hold the current DC and any other DC's that 
   // are out there in time. Mapping information for each DC must also be stored
   struct StackFrame
   {
      // coordinate mapper from text space to logical space
      // A coordinate is text, B coordinate is logical
      mathCoordMapper1d m_TextCoordMapperX;
      mathCoordMapper1d m_TextCoordMapperY;

      // local dc so we can determine font metrics
      CDC*  m_pDC;
   };

   std::vector<StackFrame> m_Stack;

   void UpdateLogicalExtents();
   void CenterOnPoint(Float64 wx, Float64 wy);
   void CenterWorldInLogical();
};

#endif // !defined(AFX_MAPPINGIMPL_H__BCB8A106_E659_11D4_8B81_006097C68A9C__INCLUDED_)
