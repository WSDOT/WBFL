///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_GEOMMODEL_H_
#define INCLUDED_GEOMMODEL_GEOMMODEL_H_
#pragma once

// This is a master include file for the Geometric Modeling Package
#if defined(BUILDGEOMMODELLIB)
	#error Do not use this header file in the Geometric Modeling Package
   #error It is for external users only
#endif


#include <GeomModel\GeomModelLib.h>
#include <GeomModel\Circle.h>
#include <GeomModel\CircularSegment.h>
#include <GeomModel\CompositeShape.h>
#include <GeomModel\ElasticProperties.h>
#include <GeomModel\IShape.h>
#include <GeomModel\IPrecastBeam.h>
#include <GeomModel\UBeam.h>
#include <GeomModel\NUBeam.h>
#include <GeomModel\MassProperties.h>
#include <GeomModel\Polygon.h>
#include <GeomModel\PrecastBeam.h>
#include <GeomModel\TrafficBarrier.h>
#include <GeomModel\Properties.h>
#include <GeomModel\Rectangle.h>
#include <GeomModel\Section.h>
#include <GeomModel\SectionListener.h>
#include <GeomModel\ShapeImp.h>
#include <GeomModel\ShapeListener.h>
#include <GeomModel\ShapeUtils.h>
#include <GeomModel\Triangle.h>
#include <GeomModel\WsdotPrecastBeams.h>

#endif // INCLUDED_GEOMMODEL_GEOMMODEL_H_