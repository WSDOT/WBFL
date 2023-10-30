///////////////////////////////////////////////////////////////////////
// BEToolbox
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#pragma once

#include <EngTools\EngToolsExp.h>
#include <array>
#include <vector>
#include <memory>

namespace WBFL
{
   namespace EngTools
   {
      /// An element in a UniformFDMesh
      class ENGTOOLSCLASS FDMeshElement
      {
      public:
         // access array with Corner enum
         enum class Corner { BottomLeft, BottomRight, TopRight, TopLeft }; // the order of this must match the order of the poly points in a rectangle object

         /// Indices of the nodes of the mesh element. Use the Corner enum to access the array. 
         /// Indices are INVALID_INDEX when the node attached to a boundary or the index of
         /// and internal node
         std::array<IndexType, 4> Node{ INVALID_INDEX,INVALID_INDEX,INVALID_INDEX,INVALID_INDEX };
      };
      inline constexpr auto operator+(FDMeshElement::Corner c) noexcept { return std::underlying_type<FDMeshElement::Corner>::type(c); }

      /// A finite difference mesh of uniformly sized mesh elements
      class ENGTOOLSCLASS UniformFDMesh
      {
      public:
         UniformFDMesh(); ///< Default constructor. Call SetElementSize() before using this mesh
         UniformFDMesh(Float64 dx, Float64 dy); ///< Creates a mesh with dx by dy size elements
         ~UniformFDMesh();

         void HasSymmetry(bool bSymmetric); ///< Indicates if the mesh has a vertical axis of symmetry on its right hand boundary
         bool HasSymmetry() const; ///< Returns true if the mesh is symmetric

         void AllocateElementRows(IndexType nRows); ///< Allocates element rows for the mesh. This must be called prior to calling AddElements()
         void SetElementSize(Float64 dx, Float64 dy); ///< Sets the size of the mesh elements
         std::pair<Float64,Float64> GetElementSize() const; ///< Gets the size of the mesh elements (dx,dy)
         Float64 GetElementArea() const; ///< Returns the area of a single mesh element
         Float64 GetMeshArea() const; ///< Returns the total mesh area

         /// Adds elements to a previously allocated mesh row
         void AddElements(IndexType gridRowIdx, /**< index of the grid row where elements are being added */
            IndexType gridRowStartIdx, /**< index within the grid row where the first element is located */
            IndexType nElements/**< number of elements to add */
         );

         /// Adds a new row of mesh elements at the bottom of the mesh
         void AddElementRow(IndexType gridRowStartIdx, /**< index within the grid row where the first element is located */
            IndexType nElements/**< number of elements to add */
         );

         IndexType GetElementRowCount() const; ///< Returns the number of element rows in the mesh


         /// Gets the range of element indices in a row
         /// \param gridRowIdx grid row for which to get the element range
         /// \return GridRowStartIdx, FirstElementIdx, LastElementIdx
         /// GridRowStartIdx = index within the grid row where the first element is located
         /// FirstElementIdx = global index of the first element in the row
         /// LastElementIdx = global index of the last element in the row
         std::tuple<IndexType,IndexType,IndexType> GetElementRange(IndexType gridRowIdx) const;

         /// @brief Gets the position of an element
         /// @param elementIdx 
         /// @return GridRowIdx, GridRowPositionIdx
         std::pair<IndexType,IndexType> GetElementPosition(IndexType elementIdx) const;

         IndexType GetElementCount() const; ///< Returns the total number of elements in the mesh
         IndexType GetInteriorNodeCount() const; ///< Returns the number of interior nodes
         IndexType GetMaxIntriorNodesPerRow() const; ///< Returns the maximum number of interior nodes per row

         /// Returns the specified mesh element
         const FDMeshElement* GetElement(IndexType elementIdx /**< global index of the desired element*/) const;

         /// Returns the mesh element directly above the specified element
         const FDMeshElement* GetElementAbove(IndexType gridRowIdx /**< row where the element is located*/,
            IndexType elementIdx /**< index of the element within the row, starting from the left edge of the mesh*/
         ) const;

         /// Returns the mesh element directly below the specified element
         const FDMeshElement* GetElementBelow(IndexType gridRowIdx /**< row where the element is located*/,
            IndexType elementIdx /**< index of the element within the row, starting from the left edge of the mesh*/
         ) const;

         /// @brief Returns the overall size of the mesh
         /// @return Pair in the form of (Nx,Ny)
         std::pair<IndexType, IndexType> GetGridSize() const;

#if defined _DEBUG
         void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

      protected:
         Float64 m_Dx, m_Dy; // element dimensions
         bool m_bIsSymmetric;

         struct GridRow
         {
            IndexType gridRowStartIdx; // index in the grid row where the first element is located
            IndexType firstElementIdx; // global index of the first element in this row
            IndexType nElements; // number of elements in this row

            inline GridRow() : gridRowStartIdx(INVALID_INDEX), firstElementIdx(INVALID_INDEX), nElements(INVALID_INDEX) {};
            inline GridRow(IndexType a, IndexType b, IndexType c) : gridRowStartIdx(a), firstElementIdx(b), nElements(c) {};
            inline IndexType GetNextRowFirstElementIndex() const { return firstElementIdx + nElements; }
            inline bool ContainsElement(IndexType elementIdx) const { return firstElementIdx <= elementIdx && elementIdx < (firstElementIdx + nElements); }
         };
         mutable std::vector<GridRow> m_vGridRows;
         mutable std::vector<FDMeshElement> m_vElements;
         mutable IndexType m_Nx; // overall number of grid squares in a row
         mutable IndexType m_nMaxElementsPerRow; // maximum number of elements in a row. this is the overall width of the grid and defines the axis of symmetry if the mesh is symmetric
         mutable IndexType m_nMaxInteriorNodesPerRow; // maximum number of interior nodes in a row. bandwidth is equal to 2(max nodes per row)+1
         mutable IndexType m_nInteriorNodes; // number of interior nodes (this is the number of degrees of freedom in the FD model)

         mutable bool m_bIsDirty;
         void Update() const;
         void Clear();
         IndexType GetFirstElementIndex(IndexType gridRowIdx);
      };
   };
};