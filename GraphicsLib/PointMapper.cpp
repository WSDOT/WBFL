///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <GraphicsLib\GraphicsLibLib.h>
#include <GraphicsLib\PointMapper.h>
#include <MathEx.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grlibPointMapper
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

LONG round_to_nearest_whole_number(Float64 x)
{
   // :WARNING: rab 11.15.96 : Possible loss of data
   // :METHOD: round_to_nearest_whole_number()
   //
   // ceil and floor return Float64. These return values must
   // be cast to LONG. Float64s are 8 byte and LONGs are 4 byte
   // this could result in a possible loss of data. (Though I've
   // never experienced it)

   return  LONG((x - LONG(x)) > 0.5) ? (LONG)ceil(x) : (LONG)floor(x);
} // round_to_nearest_whole_number

//======================== LIFECYCLE  =======================================

grlibPointMapper::grlibPointMapper()
{
   m_WorldExtentX = 0.;
   m_WorldExtentY = 0.;
   m_WorldOriginX = 0.;
   m_WorldOriginY = 0.;

   m_DeviceExtentX = 1;
   m_DeviceExtentY = 1;
   m_DeviceOriginX = 1;
   m_DeviceOriginY = 1;
   m_OriginalDeviceExtentX = 1;
   m_OriginalDeviceExtentY = 1;

   m_MappingMode = Anisotropic;
   m_MappingModeModifier = NoFit;

   m_PixelDensityX = 1.0;
   m_PixelDensityY = 1.0;
} // grlibPointMapper

grlibPointMapper::grlibPointMapper(const grlibPointMapper& mapper)
{
   MakeCopy(mapper);
} // grlibPointMapper

grlibPointMapper::~grlibPointMapper()
{
} // ~grlibPointMapper

//======================== OPERATORS  =======================================

grlibPointMapper& grlibPointMapper::operator = (const grlibPointMapper& mapper)
{
   if ( this != &mapper )
      MakeAssignment( mapper ); 

   return *this;
} // operator =

//======================== OPERATIONS =======================================

void grlibPointMapper::WPtoDP(Float64 wx,Float64 wy,LONG* dx,LONG* dy) const
{
   // :NOTE: rab 11.14.96 : Assumed direction of axes
   // :METHOD: grlibPointMapper::WPtoDP()
   // It is assumed that the world axes increase up and to the left and the
   // device axes increase down and to the left. For this reason, the extent
   // ratio is negative in the y mapping.

   if (m_WorldExtentX == 0)
   {
      *dx = m_DeviceOriginX;
   }
   else
   {
      Float64 x;
      x = (wx - m_WorldOriginX) * ( (Float64)m_DeviceExtentX / m_WorldExtentX)
          + m_DeviceOriginX;

      *dx = round_to_nearest_whole_number(x);
   }


   if (m_WorldExtentY == 0)
   {
      *dy = m_DeviceOriginY;
   }
   else
   {
      Float64 y;
      y = (wy - m_WorldOriginY) * ( (Float64)m_DeviceExtentY / (-m_WorldExtentY) )
          + m_DeviceOriginY;

      *dy = round_to_nearest_whole_number(y);
   }
} // WPtoDP

void grlibPointMapper::WPtoDP(const gpPoint2d& p,LONG* dx,LONG* dy) const
{
   WPtoDP( p.X(), p.Y(), dx, dy );
}

void grlibPointMapper::WPtoDP(IPoint2d* pPoint,LONG* dx,LONG* dy) const
{
   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);
   WPtoDP(x,y,dx,dy);
}

void grlibPointMapper::DPtoWP(LONG dx,LONG dy,Float64* wx,Float64* wy) const
{
   // :NOTE: rab 11.14.96 : Assumed direction of axes
   // :METHOD: grlibPointMapper::DPtoWP()
   // It is assumed that the world axes increase up and to the left and the
   // device axes increase down and to the left. For this reason, the extent
   // ratio is negative in the y mapping.

   if (m_DeviceExtentX == 0)
   {
      *wx = 0.0;
   }
   else
   {
      *wx = (dx - m_DeviceOriginX) * (m_WorldExtentX / (Float64)m_DeviceExtentX)
           + m_WorldOriginX;
   }

   if (m_DeviceExtentY == 0)
   {
      *wy = 0.0;
   }
   else
   {
      *wy = (dy - m_DeviceOriginY) * (-m_WorldExtentY / (Float64)m_DeviceExtentY)
           + m_WorldOriginY;
   }
} // DPtoWP

gpPoint2d grlibPointMapper::DPtoWP(LONG dx,LONG dy) const
{
   Float64 wx,wy;
   DPtoWP(dx,dy,&wx,&wy);
   return gpPoint2d(wx,wy);
}

void grlibPointMapper::DPtoWP(LONG dx,LONG dy,IPoint2d** ppPoint) const
{
   Float64 wx,wy;
   DPtoWP(dx,dy,&wx,&wy);

   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(wx,wy);
   (*ppPoint) = point;
   (*ppPoint)->AddRef();
}

void grlibPointMapper::AddScale(Float64 scale)
{
   PRECONDITION(0.1 <= scale && scale < 1.0);

   if (m_Scales.empty() ||
      std::find(m_Scales.begin(),m_Scales.end(),scale) == m_Scales.end())
   {
      // scale does not currently exist
      m_Scales.push_back(scale);

      // Update extents if using any of the fit map mode modifiers
      if ( m_MappingModeModifier != NoFit )
         UpdateDeviceExtents();
   }
} // AddScale

void grlibPointMapper::ClearScales()
{
   m_Scales.clear();
} // ClearScales

//======================== ACCESS     =======================================

void grlibPointMapper::SetWorldExt(Float64 wx,Float64 wy)
{
   m_WorldExtentX = wx;
   m_WorldExtentY = wy;

   UpdateDeviceExtents();
} // SetWorldExt

void grlibPointMapper::SetWorldExt(const gpSize2d& wExt)
{
   SetWorldExt( wExt.Dx(), wExt.Dy() );
}

void grlibPointMapper::GetWorldExt(Float64* wx,Float64* wy) const
{
   *wx = m_WorldExtentX;
   *wy = m_WorldExtentY;
} // GetWorldExt

gpSize2d grlibPointMapper::GetWorldExt() const
{
   return gpSize2d( m_WorldExtentX, m_WorldExtentY );
}

void grlibPointMapper::SetWorldOrg(Float64 wx,Float64 wy)
{
   m_WorldOriginX = wx;
   m_WorldOriginY = wy;
} // SetWorldOrg

void grlibPointMapper::SetWorldOrg(const gpPoint2d& wOrg)
{
   SetWorldOrg( wOrg.X(), wOrg.Y() );
}

void grlibPointMapper::GetWorldOrg(Float64* wx,Float64* wy) const
{
   *wx = m_WorldOriginX;
   *wy = m_WorldOriginY;
} // GetWorldOrg

gpPoint2d grlibPointMapper::GetWorldOrg() const
{
   return gpPoint2d( m_WorldOriginX, m_WorldOriginY );
}

void grlibPointMapper::SetDeviceExt(LONG dx,LONG dy)
{
   m_OriginalDeviceExtentX = dx;
   m_OriginalDeviceExtentY = dy;

   UpdateDeviceExtents();
} // SetDeviceExt

void grlibPointMapper::GetDeviceExt(LONG* dx,LONG* dy) const
{
   *dx = m_OriginalDeviceExtentX;
   *dy = m_OriginalDeviceExtentY;
} // GetDeviceExt

void grlibPointMapper::GetAdjustedDeviceExt(LONG* dx,LONG* dy) const
{
   *dx = m_DeviceExtentX;
   *dy = m_DeviceExtentY;
} // GetAdjustedDeviceExt

void grlibPointMapper::SetDeviceOrg(LONG dx,LONG dy)
{
   m_DeviceOriginX = dx;
   m_DeviceOriginY = dy;
} // SetDeviceOrg

void grlibPointMapper::GetDeviceOrg(LONG* dx,LONG* dy) const
{
   *dx = m_DeviceOriginX;
   *dy = m_DeviceOriginY;
} // GetDeviceOrg

void grlibPointMapper::SetMappingMode(grlibPointMapper::MapMode mm)
{
   m_MappingMode = mm;
   UpdateDeviceExtents();
} // SetMappingMode

grlibPointMapper::MapMode grlibPointMapper::GetMappingMode() const
{
   return m_MappingMode;
} // GetMappingMode

void grlibPointMapper::SetMappingModeModifier(grlibPointMapper::MapModeModifier mmm)
{
   m_MappingModeModifier = mmm;
   UpdateDeviceExtents();
}

grlibPointMapper::MapModeModifier grlibPointMapper::GetMappingModeModifier() const
{
   return m_MappingModeModifier;
}

void grlibPointMapper::SetPixelDensity(Float64 pdx,Float64 pdy)
{
   m_PixelDensityX = pdx;
   m_PixelDensityY = pdy;

   UpdateDeviceExtents();
} // SetPixelDensity

void grlibPointMapper::GetPixelDensity(Float64* pdx,Float64* pdy) const
{
   *pdx = m_PixelDensityX;
   *pdy = m_PixelDensityY;
} // GetPixelDensity

//======================== INQUIRY    =======================================
Float64 grlibPointMapper::GetScaleX() const
{
   Float64 scale;

   if (m_DeviceExtentX == 0)
      scale = 0;
   else
      scale = fabs(m_WorldExtentX * m_PixelDensityX / m_DeviceExtentX);

   return scale;
} // GetScaleX

Float64 grlibPointMapper::GetScaleY() const
{
   Float64 scale;

   if (m_DeviceExtentY == 0)
      scale = 0;
   else
      scale = fabs(m_WorldExtentY * m_PixelDensityY / m_DeviceExtentY);

   return scale;
} // GetScaleY

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


void grlibPointMapper::MakeCopy(const grlibPointMapper& rOther)
{
   m_WorldExtentX          = rOther.m_WorldExtentX;
   m_WorldExtentY          = rOther.m_WorldExtentY;         
   m_WorldOriginX          = rOther.m_WorldOriginX;         
   m_WorldOriginY          = rOther.m_WorldOriginY;         
   m_DeviceExtentX         = rOther.m_DeviceExtentX;        
   m_DeviceExtentY         = rOther.m_DeviceExtentY;        
   m_OriginalDeviceExtentX = rOther.m_OriginalDeviceExtentX;
   m_OriginalDeviceExtentY = rOther.m_OriginalDeviceExtentY;
   m_DeviceOriginX         = rOther.m_DeviceOriginX;        
   m_DeviceOriginY         = rOther.m_DeviceOriginY;        
   m_PixelDensityX         = rOther.m_PixelDensityX;        
   m_PixelDensityY         = rOther.m_PixelDensityY;        
   m_Scales                = rOther.m_Scales;               
   m_MappingMode           = rOther.m_MappingMode;          
   m_MappingModeModifier   = rOther.m_MappingModeModifier;
}

void grlibPointMapper::MakeAssignment(const grlibPointMapper& rOther)
{
   MakeCopy(rOther);
}


void grlibPointMapper::UpdateDeviceExtents()
{
   Float64 ns_world_ext_x;  // no-sign world extents
   Float64 ns_world_ext_y;
   LONG   ns_device_ext_x; // no-sign device extents
   LONG   ns_device_ext_y;
   Float64 scale;

   //
   // Copy world and device extents, removing sign
   // Device ratio-ing must be done without signs, because ???
   //
   ns_world_ext_x  = fabs(m_WorldExtentX);
   ns_world_ext_y  = fabs(m_WorldExtentY);
   ns_device_ext_x =  abs(m_OriginalDeviceExtentX);
   ns_device_ext_y =  abs(m_OriginalDeviceExtentY);

   if ( m_MappingMode == Anisotropic )
   {
      if ( m_MappingModeModifier == BestFitX )
      {
         scale = ns_world_ext_x * m_PixelDensityX / ns_device_ext_x;
         scale = GetBestFitScale(scale);

         if (scale == 0)
            ns_device_ext_x = 0;
         else
            ns_device_ext_x = round_to_nearest_whole_number( ns_world_ext_x * m_PixelDensityX / scale );
      }

      if ( m_MappingModeModifier == BestFitY )
      {
         scale = ns_world_ext_y * m_PixelDensityY / ns_device_ext_y;
         scale = GetBestFitScale(scale);

         if (scale == 0)
            ns_device_ext_y = 0;
         else
            ns_device_ext_y = round_to_nearest_whole_number( ns_world_ext_y * m_PixelDensityY / scale );
      }
   }
   else if ( m_MappingMode == Isotropic )
   {
      Float64 s1;
      Float64 s2;

      s1 = ns_world_ext_x * ns_device_ext_y;
      s2 = ns_world_ext_y * ns_device_ext_x;

      if (s1 > s2)
      {
         // ns_world_ext_x cannot be zero
         CHECK(ns_world_ext_x != 0);

         ns_device_ext_y = round_to_nearest_whole_number(
                 (Float64)ns_device_ext_x * ns_world_ext_y / ns_world_ext_x );
      }
      else if (s1 < s2)
      {
         // ns_world_ext_y cannot be zero
         CHECK(ns_world_ext_y != 0);

         ns_device_ext_x = round_to_nearest_whole_number(
                 (Float64)ns_device_ext_y * ns_world_ext_x / ns_world_ext_y );
      }
      else
      {
         // do nothing
         // s1 equals s2, and that is what isotropic is all about
      }

      if ( m_MappingModeModifier == BestFitX ||
           m_MappingModeModifier == BestFitY || 
           m_MappingModeModifier == BestFitXY )
      {
         if (ns_device_ext_x != 0)
            scale = ns_world_ext_x * m_PixelDensityX / ns_device_ext_x;
         else if (ns_device_ext_y != 0)
            scale = ns_world_ext_y * m_PixelDensityY / ns_device_ext_y;
         else
            scale = 0;

         scale = GetBestFitScale(scale);

         if (scale == 0)
         {
            ns_device_ext_x = 0;
            ns_device_ext_y = 0;
         }
         else
         {
            ns_device_ext_x = round_to_nearest_whole_number( ns_world_ext_x * m_PixelDensityX / scale);
            ns_device_ext_y = round_to_nearest_whole_number( ns_world_ext_y * m_PixelDensityY / scale);
         }
      }
   }
   else
   {
      CHECKX( false, _T("The mapping mode is invalid") );
   }


   // Assign new device extents to member variables
   // Be sure to put back signs
   m_DeviceExtentX = (m_OriginalDeviceExtentX < 0 ? -1 : 1) * ns_device_ext_x;
   m_DeviceExtentY = (m_OriginalDeviceExtentY < 0 ? -1 : 1) * ns_device_ext_y;
} // UpdateDeviceExtents

Float64 grlibPointMapper::GetBestFitScale(Float64 refScale)
{
   CHECK( 0 <= refScale );

   Int16 exp;
   Float64 norm_ref_scale;      // normalized between 0.1 and 1.0
   Float64 norm_best_fit_scale; // normalized between 0.1 and 1.0
   Float64 best_fit_scale;

   if ( IsZero( refScale ) )
      return refScale;

   // Container is empty
   PRECONDITION(!m_Scales.empty());

   // Normalize the reference scale
   exp = Int16(log10(refScale)); 
   if (refScale >= 1)
      exp++;

   norm_ref_scale = refScale * pow(10.,-exp);

   // must be between 0.1 and 1.0
   CHECK(0.1 <= norm_ref_scale && norm_ref_scale < 1.0);

   // find the best fit scale from the available scales
   // assume scales are sorted from least to most
   // best fitting scale is the first one >= norm_ref_scale
   ScaleContainerIteratorType iter = m_Scales.begin();
   while (iter != m_Scales.end())
   {
      norm_best_fit_scale = *iter++;
      CHECK(0.1 <= norm_best_fit_scale && norm_best_fit_scale < 1.0);

      if (norm_ref_scale <= norm_best_fit_scale)
         break;
   }

   best_fit_scale = norm_best_fit_scale * pow(10.,exp);

   return best_fit_scale;
} // GetBestFitScale

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================


#if defined _UNITTEST
bool grlibPointMapper::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("grlibPointMapper");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for grlibPointMapper");
   TESTME_EPILOG("grlibPointMapper");
}
#endif // _UNITTEST



