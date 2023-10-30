///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include "stdafx.h"
#include <Graphing/PointMapper.h>
#include <MathEx.h>

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Graphing;

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


void PointMapper::WPtoDP(Float64 wx,Float64 wy,LONG* dx,LONG* dy) const
{
   // :NOTE: rab 11.14.96 : Assumed direction of axes
   // :METHOD: PointMapper::WPtoDP()
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
}

void PointMapper::WPtoDP(const Point& p,LONG* dx,LONG* dy) const
{
   WPtoDP( p.X(), p.Y(), dx, dy );
}

void PointMapper::DPtoWP(LONG dx,LONG dy,Float64* wx,Float64* wy) const
{
   // :NOTE: rab 11.14.96 : Assumed direction of axes
   // :METHOD: PointMapper::DPtoWP()
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
}

Point PointMapper::DPtoWP(LONG dx,LONG dy) const
{
   Float64 wx,wy;
   DPtoWP(dx,dy,&wx,&wy);
   return Point(wx,wy);
}

void PointMapper::AddScale(Float64 scale)
{
   PRECONDITION(0.1 <= scale && scale < 1.0);

   if (m_Scales.empty() ||
      std::find(m_Scales.begin(),m_Scales.end(),scale) == m_Scales.end())
   {
      // scale does not currently exist
      m_Scales.push_back(scale);

      // Update extents if using any of the fit map mode modifiers
      if ( m_MappingModeModifier != MapModeModifier::NoFit )
         UpdateDeviceExtents();
   }
}

void PointMapper::ClearScales()
{
   m_Scales.clear();
}

void PointMapper::SetWorldExt(Float64 wx,Float64 wy)
{
   m_WorldExtentX = wx;
   m_WorldExtentY = wy;

   UpdateDeviceExtents();
}

void PointMapper::SetWorldExt(const Size& wExt)
{
   SetWorldExt( wExt.Dx(), wExt.Dy() );
}

void PointMapper::GetWorldExt(Float64* wx,Float64* wy) const
{
   *wx = m_WorldExtentX;
   *wy = m_WorldExtentY;
}

Size PointMapper::GetWorldExt() const
{
   return Size( m_WorldExtentX, m_WorldExtentY );
}

void PointMapper::SetWorldOrg(Float64 wx,Float64 wy)
{
   m_WorldOriginX = wx;
   m_WorldOriginY = wy;
}

void PointMapper::SetWorldOrg(const Point& wOrg)
{
   SetWorldOrg( wOrg.X(), wOrg.Y() );
}

void PointMapper::GetWorldOrg(Float64* wx,Float64* wy) const
{
   *wx = m_WorldOriginX;
   *wy = m_WorldOriginY;
}

Point PointMapper::GetWorldOrg() const
{
   return Point( m_WorldOriginX, m_WorldOriginY );
}

void PointMapper::SetDeviceExt(LONG dx,LONG dy)
{
   m_OriginalDeviceExtentX = dx;
   m_OriginalDeviceExtentY = dy;

   UpdateDeviceExtents();
}

void PointMapper::GetDeviceExt(LONG* dx,LONG* dy) const
{
   *dx = m_OriginalDeviceExtentX;
   *dy = m_OriginalDeviceExtentY;
}

void PointMapper::GetAdjustedDeviceExt(LONG* dx,LONG* dy) const
{
   *dx = m_DeviceExtentX;
   *dy = m_DeviceExtentY;
}

void PointMapper::SetDeviceOrg(LONG dx,LONG dy)
{
   m_DeviceOriginX = dx;
   m_DeviceOriginY = dy;
}

void PointMapper::GetDeviceOrg(LONG* dx,LONG* dy) const
{
   *dx = m_DeviceOriginX;
   *dy = m_DeviceOriginY;
}

void PointMapper::SetMappingMode(PointMapper::MapMode mm)
{
   m_MappingMode = mm;
   UpdateDeviceExtents();
}

PointMapper::MapMode PointMapper::GetMappingMode() const
{
   return m_MappingMode;
}

void PointMapper::SetMappingModeModifier(PointMapper::MapModeModifier mmm)
{
   m_MappingModeModifier = mmm;
   UpdateDeviceExtents();
}

PointMapper::MapModeModifier PointMapper::GetMappingModeModifier() const
{
   return m_MappingModeModifier;
}

void PointMapper::SetPixelDensity(Float64 pdx,Float64 pdy)
{
   m_PixelDensityX = pdx;
   m_PixelDensityY = pdy;

   UpdateDeviceExtents();
}

void PointMapper::GetPixelDensity(Float64* pdx,Float64* pdy) const
{
   *pdx = m_PixelDensityX;
   *pdy = m_PixelDensityY;
}

Float64 PointMapper::GetScaleX() const
{
   Float64 scale;

   if (m_DeviceExtentX == 0)
      scale = 0;
   else
      scale = fabs(m_WorldExtentX * m_PixelDensityX / m_DeviceExtentX);

   return scale;
}

Float64 PointMapper::GetScaleY() const
{
   Float64 scale;

   if (m_DeviceExtentY == 0)
      scale = 0;
   else
      scale = fabs(m_WorldExtentY * m_PixelDensityY / m_DeviceExtentY);

   return scale;
}

void PointMapper::UpdateDeviceExtents()
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

   if ( m_MappingMode == MapMode::Anisotropic )
   {
      if ( m_MappingModeModifier == MapModeModifier::BestFitX )
      {
         scale = ns_world_ext_x * m_PixelDensityX / ns_device_ext_x;
         scale = GetBestFitScale(scale);

         if (scale == 0)
            ns_device_ext_x = 0;
         else
            ns_device_ext_x = round_to_nearest_whole_number( ns_world_ext_x * m_PixelDensityX / scale );
      }

      if ( m_MappingModeModifier == MapModeModifier::BestFitY )
      {
         scale = ns_world_ext_y * m_PixelDensityY / ns_device_ext_y;
         scale = GetBestFitScale(scale);

         if (scale == 0)
            ns_device_ext_y = 0;
         else
            ns_device_ext_y = round_to_nearest_whole_number( ns_world_ext_y * m_PixelDensityY / scale );
      }
   }
   else if ( m_MappingMode == MapMode::Isotropic )
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

      if ( m_MappingModeModifier == MapModeModifier::BestFitX ||
           m_MappingModeModifier == MapModeModifier::BestFitY ||
           m_MappingModeModifier == MapModeModifier::BestFitXY )
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
}

Float64 PointMapper::GetBestFitScale(Float64 refScale)
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
   auto iter = m_Scales.begin();
   while (iter != m_Scales.end())
   {
      norm_best_fit_scale = *iter++;
      CHECK(0.1 <= norm_best_fit_scale && norm_best_fit_scale < 1.0);

      if (norm_ref_scale <= norm_best_fit_scale)
         break;
   }

   best_fit_scale = norm_best_fit_scale * pow(10.,exp);

   return best_fit_scale;
}

