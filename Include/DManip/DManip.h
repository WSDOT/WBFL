///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_DMANIP_H_
#define INCLUDED_DMANIP_H_
#pragma once

#include <WBFLDManip.h>

#include <atlbase.h>

#include <afxole.h>

#include <WBFLTools.h>
#include <WBFLGeometry.h>

#include <DManip\DManip_clsid.cpp>
#include <DManip\DManipTypes.h>

#include <DManip\CoordinateMap.h>

#include <DManip\DisplayMgr.h>
#include <DManip\DisplayMgrEvents.h>

#include <DManip\DisplayList.h>
#include <DManip\DisplayObjectContainer.h>

#include <DManip\DisplayObjectEvents.h>
#include <DManip\DisplayView.h>
#include <DManip\Mapping.h>

// Display Objects Interfaces
#include <DManip\DisplayObjectFactory.h>
#include <DManip\DisplayObject.h>
#include <DManip\TextBlock.h>
#include <DManip\PointDisplayObject.h>
#include <DManip\DimensionLine.h>
#include <DManip\Line.h>
#include <DManip\CompositeDisplayObject.h>
#include <DManip\NorthArrow.h>

// Inplace Editing Interfaces
#include <DManip\InplaceEdit.h>
#include <DManip\InplaceEditCtrl.h>
#include <DManip\InplaceNumericEditCtrl.h>

// Connectable Objects and Connectors
#include <DManip\Connections.h>

// Display Object Implementations
#include <DManip\EditableTextBlock.h>
#include <DManip\EditableUnitValueTextBlock.h>

// Drag and Drop
#include <DManip\DragData.h>
#include <DManip\DropSite.h>
#include <DManip\Draggable.h>

// Tools
#include <DManip\ToolPalette.h>
#include <DManip\Tool.h>

// Tasks
#include <DManip\TaskFactory.h>
#include <DManip\Task.h>

// Misc
#include <DManip\GravityWellStrategy.h>
#include <DManip\ShapeGravityWellStrategy.h>

#include <DManip\DrawPointStrategy.h>
#include <DManip\DrawLineStrategy.h>
#include <DManip\SimpleDrawLineStrategy.h>
#include <DManip\SimpleDrawDashedLineStrategy.h>
#include <DManip\SimpleDrawPointStrategy.h>
#include <DManip\RectangleDrawLineStrategy.h>
#include <DManip\ExtRectangleDrawLineStrategy.h>
#include <DManip\ShapeDrawStrategy.h>
#include <DManip\TargetDrawStrategy.h>
#include <DManip\CompoundDrawLineStrategy.h>


#endif // INCLUDED_DMANIP_H_