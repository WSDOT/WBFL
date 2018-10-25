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

#ifndef INCLUDED_GRAPHICSLIB_POINTMAPPER_H_
#define INCLUDED_GRAPHICSLIB_POINTMAPPER_H_
#pragma once

// SYSTEM INCLUDES
//
#include <GraphicsLib\GraphicsLibExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>
#include <vector>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
struct IPoint2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grlibPointMapper

   Maps points from world space to device space

DESCRIPTION
   Instances of this class are used to map Float64s to Int32s.
   This is typically done for graphics in Windows. The device
   points can be in any Windows mapping mode that you desire.
 
   The point mapping can be forced to conform to a scale.
   This is useful when drawing on a hard copy (paper) and the
   graphics need to conform to an engineering scale such as
   1:50.  The best scale is selected from the list of available
   scales.  You <B>MUST</B> provide the mapper with available scales
   using the AddScale() method.  Scales values must be in the
   range [0.1, 1.0).  You <B>MUST</B> also provide the mapper with
   the pixel density of the device.  The world units and pixel 
   density must be in consistant units. For example,  if
   the pixel density is 300 dpi then world units must be in
   inches.  In Windows, the pixel density can be easily
   obtained from GetDeviceCaps() with LOGPIXELSX and
   LOGPIXELSY arguements.

  <pre>
   Some common scales (world units in mm):
   US Engineering Scale:
   1 : 0.12 (1 : 10)
   1 : 0.24 (1 : 20)
   1 : 0.36 (1 : 30)
   1 : 0.48 (1 : 40)
   1 : 0.60 (1 : 50)
   1 : 0.72 (1 : 60)

   SI Engineering Scales:
   1 : 0.100 (1 : 100)
   1 : 0.125 (1 : 125)
   1 : 0.150 (1 : 150)
   1 : 0.200 (1 : 200)
   1 : 0.250 (1 : 250)
   1 : 0.500 (1 : 500)

   Convert Dots-per-inch (dpi) to Dots-per-millimeter
   divide by 25.4 mm/inch
   </pre>

   EXAMPLE
   The following code snippet maps a 1 mile by 1 mile square
   (given in feet) to a 100 by 200 pixel rectangle

                grlibPointMapper mapper;
                mapper.SetMappingMode( grlibPointMapper::Anisotropic );
                mapper.SetWorldExt(5280.,5280.);
                mapper.SetDeviceExt(100,200);
                mapper.SetDeviceOrg(0,200);
                mapper.WPtoDP(0.,0.,dx,dy);       // dx =   0, dy = 200
                mapper.WPtoDP(5280.,5280.,dx,dy); // dx = 100, dy = 0
                mapper.WPtoDP(5280.,0.,dx,dy);    // dx = 100, dy = 200
   END
*****************************************************************************/

class GRCLASS grlibPointMapper
{
public:
   // GROUP: ENUMERATIONS
   enum MapMode { Isotropic, Anisotropic };
   enum MapModeModifier { NoFit, BestFitX, BestFitY, BestFitXY };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   grlibPointMapper();

   //------------------------------------------------------------------------
   grlibPointMapper(const grlibPointMapper& mapper);

   //------------------------------------------------------------------------
   ~grlibPointMapper();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   grlibPointMapper& operator = (const grlibPointMapper& mapper);

   // GROUP: OPERATIONS
   
   //------------------------------------------------------------------------
   void WPtoDP(Float64 wx,Float64 wy,LONG* dx,LONG* dy) const;
   
   //------------------------------------------------------------------------
   void WPtoDP(const gpPoint2d& p,LONG* dx,LONG* dy) const;

   //------------------------------------------------------------------------
   void WPtoDP(IPoint2d* pPoint,LONG* dx,LONG* dy) const;

   //------------------------------------------------------------------------
   void DPtoWP(LONG dx,LONG dy,Float64* wx,Float64* wy) const;

   //------------------------------------------------------------------------
   gpPoint2d DPtoWP(LONG dx,LONG dy) const;
   
   //------------------------------------------------------------------------
   void DPtoWP(LONG dx,LONG dy,IPoint2d** ppPoint) const;

   //------------------------------------------------------------------------
   void AddScale(Float64 scale);
   
   //------------------------------------------------------------------------
   void ClearScales();

   // GROUP: ACCESS
   
   //------------------------------------------------------------------------
   void SetWorldExt(Float64 wx,Float64 wy);
   
   //------------------------------------------------------------------------
   void SetWorldExt(const gpSize2d& wExt);
   
   //------------------------------------------------------------------------
   void GetWorldExt(Float64* wx,Float64* wy) const;
   
   //------------------------------------------------------------------------
   gpSize2d GetWorldExt() const;
   
   //------------------------------------------------------------------------
   void SetWorldOrg(Float64 wx,Float64 wy);
   
   //------------------------------------------------------------------------
   void SetWorldOrg(const gpPoint2d& wOrg);
   
   //------------------------------------------------------------------------
   void GetWorldOrg(Float64* wx,Float64* wy) const;
   
   //------------------------------------------------------------------------
   gpPoint2d GetWorldOrg() const;
   
   //------------------------------------------------------------------------
   void SetDeviceExt(LONG dx,LONG dy);
   
   //------------------------------------------------------------------------
   void GetDeviceExt(LONG* dx,LONG* dy) const;
   
   //------------------------------------------------------------------------
   void GetAdjustedDeviceExt(LONG* dx,LONG* dy) const;
   
   //------------------------------------------------------------------------
   void SetDeviceOrg(LONG dx,LONG dy);
   
   //------------------------------------------------------------------------
   void GetDeviceOrg(LONG* dx,LONG* dy) const;
   
   //------------------------------------------------------------------------
   void SetMappingMode(grlibPointMapper::MapMode mm);
   
   //------------------------------------------------------------------------
   grlibPointMapper::MapMode GetMappingMode() const;
   
   //------------------------------------------------------------------------
   void SetMappingModeModifier(grlibPointMapper::MapModeModifier mmm);
   
   //------------------------------------------------------------------------
   grlibPointMapper::MapModeModifier GetMappingModeModifier() const;
   
   //------------------------------------------------------------------------
   void SetPixelDensity(Float64 pdx,Float64 pdy);
   
   //------------------------------------------------------------------------
   void GetPixelDensity(Float64* pdx,Float64* pdy) const;

   // GROUP: INQUIRY
   
   //------------------------------------------------------------------------
   Float64 GetScaleX() const;
   
   //------------------------------------------------------------------------
   Float64 GetScaleY() const;

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_WorldExtentX;
   Float64 m_WorldExtentY;
   Float64 m_WorldOriginX;
   Float64 m_WorldOriginY;
   LONG   m_DeviceExtentX;
   LONG   m_DeviceExtentY;
   LONG   m_OriginalDeviceExtentX;
   LONG   m_OriginalDeviceExtentY;
   LONG   m_DeviceOriginX;
   LONG   m_DeviceOriginY;
   Float64 m_PixelDensityX;
   Float64 m_PixelDensityY;

   MapMode         m_MappingMode;
   MapModeModifier m_MappingModeModifier;

   typedef std::vector<Float64, std::allocator<Float64> > ScaleContainerType;
   typedef std::vector<Float64, std::allocator<Float64> >::iterator ScaleContainerIteratorType;
   ScaleContainerType m_Scales;

   // GROUP: LIFECYCLE

   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   void UpdateDeviceExtents();
   Float64 GetBestFitScale(Float64 refScale);

   void MakeCopy(const grlibPointMapper& rOther);
   void MakeAssignment(const grlibPointMapper& rOther);

   // GROUP: ACCESS

   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GRAPHICSTOOLS_POINTMAPPER_H_
