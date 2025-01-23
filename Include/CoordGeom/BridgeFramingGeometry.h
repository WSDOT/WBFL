///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/CompositeLayoutLineFactory.h>
#include <CoordGeom/CompositePierLineFactory.h>
#include <CoordGeom/CompositeGirderLineFactory.h>
#include <CoordGeom/CompositeDiaphragmLineFactory.h>
#include <CoordGeom/DeckBoundaryFactory.h>
#include <CoordGeom/Model.h>
#include <array>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Object defining bridge framing plan and related geometry.
      /// There are two methods of defining the bridge framing geometry; create and initialize during object creation and create then initialized.
      /// When using the create then initialize method, all of the factory object must be created and assigned to this object before requesting any geometry.
      /// Bridge frame geometry is created on demand by calling the factory objects in the following order:
      /// 1. Pier Line Factory
      /// 2. Layout Line Factory
      /// 3. Girder Line Factory
      /// 4. Diaphragm Line Factory
      /// 5. Deck Boundary Factory (if provided)
      /// 
      /// Multiple factories of each type can be added to the model. When the factory Create method is called, all previously created geometry
      /// elements are replaced.
      /// 
      /// The bridge geometry object manages all of the geometric object created by the factory objects.
      class COORDGEOMCLASS BridgeFramingGeometry : public std::enable_shared_from_this<BridgeFramingGeometry>
      {
      private:
         BridgeFramingGeometry() = default;
         BridgeFramingGeometry(IDType bridgeAlignmentID, std::shared_ptr<const Alignment> alignment);
         BridgeFramingGeometry(IDType bridgeAlignmentID, std::shared_ptr<Model> model);
         BridgeFramingGeometry(IDType bridgeAlignmentID, const std::vector<std::pair<IDType, std::shared_ptr<const Alignment>>>& alignments,
            std::shared_ptr<LayoutLineFactory> layoutLineFactory, std::shared_ptr<PierLineFactory> pierLineFactory, std::shared_ptr<GirderLineFactory> girderLineFactory,
            std::shared_ptr<DiaphragmLineFactory> diaphragmLineFactory, std::shared_ptr<DeckBoundaryFactory> deckBoundaryFactory);
         BridgeFramingGeometry(IDType bridgeAlignmentID, std::shared_ptr<Model> model,
            std::shared_ptr<LayoutLineFactory> layoutLineFactory, std::shared_ptr<PierLineFactory> pierLineFactory, std::shared_ptr<GirderLineFactory> girderLineFactory,
            std::shared_ptr<DiaphragmLineFactory> diaphragmLineFactory, std::shared_ptr<DeckBoundaryFactory> deckBoundaryFactory);
         BridgeFramingGeometry(const BridgeFramingGeometry&) = default;
         BridgeFramingGeometry& operator=(const BridgeFramingGeometry& other) = default;

      public:
         static std::shared_ptr<BridgeFramingGeometry> Create();

         /// @brief Creates a bridge geometry model but does not create any of the required factory objects. 
         /// @param bridgeAlignmentID The ID of the alignment associated with the bridge alignment
         /// @param alignment The alignment associated with the bridge geometry
         /// @return 
         static std::shared_ptr<BridgeFramingGeometry> Create(IDType bridgeAlignmentID, std::shared_ptr<const Alignment> alignment);

         /// @brief Creates and initializes a bridge geometry model
         /// @param bridgeAlignmentID The ID of the alignment associated with the bridge alignment
         /// @param alignments Collection of alignments and their associated identifiers
         /// @param layoutLineFactory The layout line factory
         /// @param pierLineFactory The pier line factory
         /// @param girderLineFactory The girder line factory
         /// @param diaphragmLineFactory The diaphragm line factory.
         /// @param deckBoundaryFactory The deck boundary factory.
         /// @return 
         static std::shared_ptr<BridgeFramingGeometry> Create(IDType bridgeAlignmentID, const std::vector<std::pair<IDType, std::shared_ptr<const Alignment>>>& alignments,
            std::shared_ptr<LayoutLineFactory> layoutLineFactory, std::shared_ptr<PierLineFactory> pierLineFactory, std::shared_ptr<GirderLineFactory> girderLineFactory,
            std::shared_ptr<DiaphragmLineFactory> diaphragmLineFactory, std::shared_ptr<DeckBoundaryFactory> deckBoundaryFactory);

         ~BridgeFramingGeometry() = default;

         /// @brief Adds an alignment to the bridge geometry model.
         /// @param alignmentID The alignment identifier
         /// @param alignment The alignment object
         void AddAlignment(IDType alignmentID, std::shared_ptr<const Alignment> alignment);
         std::shared_ptr<const Alignment> GetAlignment(IDType alignmentID) const;

         /// @brief Returns the alignment associated with the bridge
         /// @return 
         std::shared_ptr<const Alignment> GetBridgeAlignment() const;

         /// @brief Returns the bridge line path. The bridge line is a line that is offset and parallel to the alignment
         /// @return 
         std::shared_ptr<const Path> GetBridgeLine() const;

         /// @brief Offset from the alignment to the bridge line
         /// @param offset 
         void SetBridgeLineOffset(Float64 offset);
         Float64 GetBridgeLineOffset() const;

         /// @brief Identifier of the alignment used for the bridge geometry
         /// @param bridgeAlignmentID
         void SetBridgeAlignmentID(IDType bridgeAlignmentID);
         IDType GetBridgeAlignmentID() const;

         /// @brief Sets the ID of the profile associated with the bridge alignment
         /// @param profileID 
         void SetProfileID(IDType profileID);
         IDType GetProfileID() const;

         /// @brief Sets the ID of the surface for the bridge
         void SetSurfaceID(IDType surfaceID);
         IDType GetSurfaceID() const;

         /// @name Pier Lines
         /// @{

         /// @brief Adds a pier line factory to the model
         /// @param factory 
         void AddPierLineFactory(std::shared_ptr<PierLineFactory> factory);

         /// @brief Returns the number of pier lines
         /// @return 
         IndexType GetPierLineCount() const;

         /// @brief Searches for a pier line by its identifier
         /// @param id 
         /// @return 
         std::shared_ptr<const PierLine> FindPierLine(PierIDType id) const;

         /// @brief Returns a pier line
         /// @param idx 
         /// @return 
         std::shared_ptr<const PierLine> GetPierLine(PierIndexType idx) const;
         /// @}

         /// @name Layout Lines
         /// @{

         /// @brief Adds a layout line factory to the model
         /// @param factory 
         void AddLayoutLineFactory(std::shared_ptr<LayoutLineFactory> factory);

         /// @brief Returns the number of layout lines
         /// @return 
         IndexType GetLayoutLineCount() const;

         /// @brief Searches for a layout line by its identifier
         /// @param id 
         /// @return 
         std::shared_ptr<const Path> FindLayoutLine(IDType id) const;

         /// @brief Returns a layout line
         /// @param idx 
         /// @return 
         std::shared_ptr<const Path> GetLayoutLine(IndexType idx) const;
         /// @}

         /// @name Girder Lines
         /// @{

         /// @brief Adds a girder line factory to the model
         void AddGirderLineFactory(std::shared_ptr<GirderLineFactory> factory);

         /// @brief Returns the number of girder lines
         /// @return 
         IndexType GetGirderLineCount() const;

         /// @brief Searches for a girder line by its identifier
         /// @param id 
         /// @return 
         std::shared_ptr<const GirderLine> FindGirderLine(IDType id) const;

         /// @brief Returns a girder line
         /// @param idx 
         /// @return 
         std::shared_ptr<const GirderLine> GetGirderLine(IndexType idx) const;

         /// @}

         /// @name Diaphragm Lines
         /// @{

         /// @brief Adds a diaphragm line factory to the model
         /// @param factory
         void AddDiaphragmLineFactory(std::shared_ptr<DiaphragmLineFactory> factory);

         /// @brief Returns the number of diaphragm lines
         /// @return 
         IndexType GetDiaphragmLineCount() const;

         /// @brief Searches for a diaphragm line based on its identifier
         /// @param id 
         /// @return 
         std::shared_ptr<const DiaphragmLine> FindDiaphragmLine(IDType id) const;

         /// @brief Returns a diaphragm line
         /// @param idx 
         /// @return 
         std::shared_ptr<const DiaphragmLine> GetDiaphragmLine(IndexType idx) const;
         /// @}

         /// @name Deck Boundary
         /// @{
         /// 
         /// @brief Sets the deck boundary factory, if applicable
         /// @param factory 
         void SetDeckBoundaryFactory(std::shared_ptr<DeckBoundaryFactory> factory);

         std::shared_ptr<const DeckBoundary> GetDeckBoundary() const;
         /// @}

      private:
         std::map<IDType, std::shared_ptr<const Alignment>> m_Alignments;
         IDType m_BridgeAlignmentID = INVALID_ID;

         Float64 m_BridgeLineOffset = 0.0; // offset from the alignment to the bridge line (typically the bridge centerline)
                                           // positive value locates the bridge line to the right of the alignment

         mutable std::shared_ptr<Path> m_BridgeLine; // this is the bridge line. it is a path that is parallel to the bridge alignment
                                                     // and offset by the alignment offset

         // Profile and Surface IDs for the bridge alignment
         IDType m_ProfileID = INVALID_ID;
         IDType m_SurfaceID = INVALID_ID;

         std::shared_ptr<CompositeLayoutLineFactory> m_LayoutLineFactory{ std::make_shared<CompositeLayoutLineFactory>() };
         std::shared_ptr<CompositePierLineFactory> m_PierLineFactory{ std::make_shared<CompositePierLineFactory>() };
         std::shared_ptr<CompositeGirderLineFactory> m_GirderLineFactory{ std::make_shared<CompositeGirderLineFactory>() };
         std::shared_ptr<CompositeDiaphragmLineFactory> m_DiaphragmLineFactory{ std::make_shared<CompositeDiaphragmLineFactory>() };
         std::shared_ptr<DeckBoundaryFactory> m_DeckBoundaryFactory;

         mutable std::vector<std::shared_ptr<PierLine>> m_PierLines;
         mutable std::vector<std::pair<IDType, std::shared_ptr<Path>>> m_LayoutLines;
         mutable std::vector<std::shared_ptr<GirderLine>> m_GirderLines;
         mutable std::vector<std::shared_ptr<DiaphragmLine>> m_DiaphragmLines;
         mutable std::shared_ptr<DeckBoundary> m_DeckBoundary;

         const Int8 All = 0;
         const Int8 PierLineState = 1;
         const Int8 LayoutLineState = 2;
         const Int8 GirderLineState = 3;
         const Int8 DiaphragmLineState = 4;
         const Int8 DeckBoundaryState = 5;
         mutable Int8 m_CurrentState = All;
         void InvalidateState(Int8 state) const;
         void ValidateState(Int8 state) const;

         void UpdateBridgeLine() const;
      };
   };
};
