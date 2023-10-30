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

#pragma once

#include <Graphing/GraphingExp.h>
#include <Graphing/GraphingTypes.h>
#include <vector>

namespace WBFL
{
   namespace Graphing
   {
      /// Maps points from world space to device space
      /// 
      /// Instances of this class are used to map Float64s to Int32s.
      /// This is typically done for graphics in Windows. The device
      /// points can be in any Windows device context mapping mode.
      /// 
      /// The point mapping can be forced to conform to a scale.
      /// This is useful when drawing on a hard copy (paper) and the
      /// graphics need to conform to an engineering scale such as
      /// 1:50.  The best scale is selected from the list of available
      /// scales.  You must provide the mapper with available scales
      /// using the AddScale() method.  Scales values must be in the
      /// range [0.1, 1.0).  You must also provide the mapper with
      /// the pixel density of the device.  The world units and pixel 
      /// density must be in consistant units. For example,  if
      /// the pixel density is 300 dpi then world units must be in
      /// inches.  In Windows, the pixel density can be easily
      /// obtained from GetDeviceCaps() with LOGPIXELSX and
      /// LOGPIXELSY arguments.
      /// 
      /// Some common scales (world units in mm):
      /// US Engineering Scale:
      /// 1 : 0.12 (1 : 10)
      /// 1 : 0.24 (1 : 20)
      /// 1 : 0.36 (1 : 30)
      /// 1 : 0.48 (1 : 40)
      /// 1 : 0.60 (1 : 50)
      /// 1 : 0.72 (1 : 60)
      /// 
      /// SI Engineering Scales:
      /// 1 : 0.100 (1 : 100)
      /// 1 : 0.125 (1 : 125)
      /// 1 : 0.150 (1 : 150)
      /// 1 : 0.200 (1 : 200)
      /// 1 : 0.250 (1 : 250)
      /// 1 : 0.500 (1 : 500)
      /// 
      /// Convert Dots-per-inch (dpi) to Dots-per-millimeter
      /// divide by 25.4 mm/inch
      /// 
      /// EXAMPLE
      /// The following code snippet maps a 1 mile by 1 mile square
      /// (given in feet) to a 100 by 200 pixel rectangle
      /// ~~~
      /// PointMapper mapper;
      /// mapper.SetMappingMode( PointMapper::Anisotropic );
      /// mapper.SetWorldExt(5280.,5280.);
      /// mapper.SetDeviceExt(100,200);
      /// mapper.SetDeviceOrg(0,200);
      /// mapper.WPtoDP(0.,0.,dx,dy);       // dx =   0, dy = 200
      /// mapper.WPtoDP(5280.,5280.,dx,dy); // dx = 100, dy = 0
      /// mapper.WPtoDP(5280.,0.,dx,dy);    // dx = 100, dy = 200
      /// ~~~
      class GRAPHINGCLASS PointMapper
      {
      public:
         enum class MapMode { Isotropic, Anisotropic };
         enum class MapModeModifier { NoFit, BestFitX, BestFitY, BestFitXY };

         PointMapper() = default;
         PointMapper(const PointMapper& mapper) = default;
         ~PointMapper() = default;

         PointMapper& operator=(const PointMapper& mapper) = default;

         void WPtoDP(Float64 wx,Float64 wy,LONG* dx,LONG* dy) const;
         void WPtoDP(const Point& p,LONG* dx,LONG* dy) const;

         void DPtoWP(LONG dx,LONG dy,Float64* wx,Float64* wy) const;
         Point DPtoWP(LONG dx,LONG dy) const;

         void AddScale(Float64 scale);
         void ClearScales();

         void SetWorldExt(Float64 wx,Float64 wy);
         void SetWorldExt(const Size& wExt);
   
         void GetWorldExt(Float64* wx,Float64* wy) const;
         Size GetWorldExt() const;
   
         void SetWorldOrg(Float64 wx,Float64 wy);
         void SetWorldOrg(const Point& wOrg);
   
         void GetWorldOrg(Float64* wx,Float64* wy) const;
         Point GetWorldOrg() const;
   
         void SetDeviceExt(LONG dx,LONG dy);
         void GetDeviceExt(LONG* dx,LONG* dy) const;
         void GetAdjustedDeviceExt(LONG* dx,LONG* dy) const;
   
         void SetDeviceOrg(LONG dx,LONG dy);
         void GetDeviceOrg(LONG* dx,LONG* dy) const;
   
         void SetMappingMode(PointMapper::MapMode mm);
         PointMapper::MapMode GetMappingMode() const;
   
         void SetMappingModeModifier(PointMapper::MapModeModifier mmm);
         PointMapper::MapModeModifier GetMappingModeModifier() const;
   
         void SetPixelDensity(Float64 pdx,Float64 pdy);
         void GetPixelDensity(Float64* pdx,Float64* pdy) const;

         Float64 GetScaleX() const;
         Float64 GetScaleY() const;

      private:
         Float64 m_WorldExtentX = 1;
         Float64 m_WorldExtentY = 1;
         Float64 m_WorldOriginX = 0;
         Float64 m_WorldOriginY = 0;
         LONG   m_DeviceExtentX = 1;
         LONG   m_DeviceExtentY = 1;
         LONG   m_OriginalDeviceExtentX = 1;
         LONG   m_OriginalDeviceExtentY = 1;
         LONG   m_DeviceOriginX = 0;
         LONG   m_DeviceOriginY = 0;
         Float64 m_PixelDensityX = 1;
         Float64 m_PixelDensityY = 1;

         MapMode         m_MappingMode = MapMode::Anisotropic;
         MapModeModifier m_MappingModeModifier = MapModeModifier::NoFit;

         using Scales = std::vector<Float64>;
         Scales m_Scales;

         void UpdateDeviceExtents();
         Float64 GetBestFitScale(Float64 refScale);
      };

   }; // Graphing
}; // WBFL

