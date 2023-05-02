///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/Station.h>
#include <array>

namespace WBFL
{
   namespace COGO
   {
      class Surface; // forward declaration

      /// @brief A object that represent a Surface widening modification
      /// A widening can be applied to one or two segments of the SurfaceTemplate. This is to facilitate symmetric widening with a single Widening object.
      /// @image html Images/Widening.png
      class COORDGEOMCLASS Widening
      {
      private:
         Widening() = default;
         Widening(const Widening&) = default;
         Widening& operator=(const Widening&) = delete;

         void SetSurface(std::weak_ptr<const Surface> surface);
         friend Surface;

      public:
         ~Widening() = default;

         /// @brief Creates a new Widening object
         /// @return 
         static std::shared_ptr<Widening> Create();
         static std::shared_ptr<Widening> Create(const Widening& widening);

         /// @brief Creates and initializes a new Widening object
         /// @param beginTransitionStation Station where the entry widening transition begins
         /// @param beginFullWidening Station where the full widening begins
         /// @param endFullWidening Station where the fill widening ends
         /// @param endTransitionStation Station where the exit widening transition ends
         /// @param widening The width of the widening. Positive values widen the surface and negative values make it more narrow.
         /// @param segment1 Index of a TemplateSegment to widen
         /// @param segment2 Index of a TemplateSegment to widen. Use INVALID_INDEX if the widening is applied to only one TemplateSegment.
         /// @return 
         static std::shared_ptr<Widening> Create(const Station& beginTransitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTransitionStation, Float64 widening, IndexType segment1,IndexType segment2);

         /// @brief Returns the Surface associated with this Widening
         /// @return 
         std::shared_ptr<const Surface> GetSurface() const;
         
         /// @brief Initializes a Widening
         /// @param beginTrasitionStation Station where the entry widening transition begins
         /// @param beginFullWidening Station where the full widening begins
         /// @param endFullWidening Station where the fill widening ends
         /// @param endTrasitionStation Station where the exit widening transition ends
         /// @param widening The width of the widening. Positive values widen the surface and negative values make it more narrow.
         /// @param segment1 Index of a TemplateSegment to widen
         /// @param segment2 Index of a TemplateSegment to widen. Use INVALID_INDEX if the widening is applied to only one TemplateSegment.
         void Init(const Station& beginTrasitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTrasitionStation, Float64 widening, IndexType segment1, IndexType segment2);

         /// @brief Station where the entry widening transition begins
         /// @param beginTrasitionStation 
         void SetBeginTransition(const Station& beginTrasitionStation);
         const Station& GetBeginTransition() const;

         /// @brief Station where the full widening begins
         /// @param beginFullWidening 
         void SetBeginFullWidening(const Station& beginFullWidening);
         const Station& GetBeginFullWidening() const;

         /// @brief Station where the full widening ends
         /// @param endFullWidening 
         void SetEndFullWidening(const Station& endFullWidening);
         const Station& GetEndFullWidening() const;

         /// @brief Station where the exit widening transition ends
         /// @param endTrasitionStation 
         void SetEndTransition(const Station& endTrasitionStation);
         const Station& GetEndTransition() const;

         /// @brief The width of the widening. Positive values widen the surface and negative values make it more narrow.
         /// @param widening 
         void SetWidening(Float64 widening);
         Float64 GetWidening() const;

         /// @brief Index of the SurfaceTemplateSegment to be widened
         /// @param pntIdx 0 or 1 to indicate which of the two widening areas the segment index applies
         /// @param segmentIdx Index of the SurfaceTemplateSegment to widen;
         void SetSegment(IndexType pntIdx, IndexType segmentIdx);

         /// @brief Returns the index of the SurfaceTemplateSegment to be widened
         /// @param pntIdx 0 or 1 to indicate which of the two widening areas the segment index applies
         /// @return 
         IndexType GetSegment(IndexType pntIdx) const;

         /// @brief Computes the widening for the specified SurfaceTemplateSegment at a station.
         /// @param station Station where the widening is to be computed
         /// @param surfaceTemplateSegmentIndex Index of the SurfaceTemplateSegment for which the widening is to be computed
         /// @return The computed widening. If the specified SurfaceTemplateSegment is not widened the computed widening is zero.
         Float64 GetWidening(const Station& station,IndexType surfaceTemplateSegmentIndex) const;


#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         std::weak_ptr<const Surface> m_Surface;
         Station m_BeginTransition;
         Station m_BeginFullWidening;
         Station m_EndFullWidening;
         Station m_EndTransition;
         Float64 m_Widening = 0.0;
         std::array<IndexType, 2> m_SegmentIndex{ 0,INVALID_INDEX };

         std::shared_ptr<const Alignment> GetAlignment() const;
      };
   };
};
