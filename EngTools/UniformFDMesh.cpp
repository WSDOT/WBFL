///////////////////////////////////////////////////////////////////////
// BEToolbox
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include <EngTools/EngToolsLib.h>
#include <EngTools/UniformFDMesh.h>

using namespace WBFL::EngTools;

UniformFDMesh::UniformFDMesh()
{
   Clear();
}

UniformFDMesh::UniformFDMesh(Float64 dx, Float64 dy)
{
   Clear();
   m_Dx = dx;
   m_Dy = dy;
}

UniformFDMesh::~UniformFDMesh()
{
   Clear();
}

void UniformFDMesh::HasSymmetry(bool bSymmetric)
{
   if (m_bIsSymmetric != bSymmetric)
   {
      m_bIsSymmetric = true;
      Clear();
   }
}

bool UniformFDMesh::HasSymmetry() const
{
   return m_bIsSymmetric;
}

void UniformFDMesh::AllocateElementRows(IndexType nRows)
{
   m_vGridRows.resize(nRows);
}

void UniformFDMesh::SetElementSize(Float64 dx, Float64 dy)
{
   m_Dx = dx;
   m_Dy = dy;
}

std::pair<Float64,Float64> UniformFDMesh::GetElementSize() const
{
   return { m_Dx,m_Dy };
}

Float64 UniformFDMesh::GetElementArea() const
{
   return m_Dx*m_Dy;
}

Float64 UniformFDMesh::GetMeshArea() const
{
   return (HasSymmetry() ? 2 : 1) * GetElementCount() * GetElementArea();
}

void UniformFDMesh::AddElements(IndexType gridRowIdx, IndexType gridRowStartIdx, IndexType nElements)
{
   auto& row = m_vGridRows[gridRowIdx];
   row.gridRowStartIdx = gridRowStartIdx;
   row.nElements = nElements;
   row.firstElementIdx = GetFirstElementIndex(gridRowIdx);

   m_Nx = max(m_Nx, row.gridRowStartIdx + row.nElements);
   m_bIsDirty = true;
}

void UniformFDMesh::AddElementRow(IndexType gridRowStartIdx, IndexType nElements)
{
   IndexType firstElementIdx = (m_vGridRows.size() == 0 ? 0 : m_vGridRows.back().GetNextRowFirstElementIndex());
   m_vGridRows.emplace_back(gridRowStartIdx, firstElementIdx, nElements);
   m_Nx = max(m_Nx, gridRowStartIdx + nElements);
   m_bIsDirty = true;
}

IndexType UniformFDMesh::GetElementRowCount() const
{
   return m_vGridRows.size();
}

std::tuple<IndexType, IndexType, IndexType> UniformFDMesh::GetElementRange(IndexType gridRowIdx) const
{
   const auto& gridRow(m_vGridRows[gridRowIdx]);
   return { gridRow.gridRowStartIdx, gridRow.firstElementIdx, gridRow.firstElementIdx + gridRow.nElements - 1 };
}

std::pair<IndexType, IndexType> UniformFDMesh::GetElementPosition(IndexType elementIdx) const
{
   IndexType gridRowIdx = 0; // keep track of the rows
   for (const auto& gridRow : m_vGridRows)
   {
      if (gridRow.ContainsElement(elementIdx))
      {
         // element is contained in the row

         IndexType d = elementIdx - gridRow.firstElementIdx; // element count from first element to current element
         IndexType gridRowPositionIdx = gridRow.gridRowStartIdx + d; // position of the element from the start of the grid row
         return { gridRowIdx, gridRowPositionIdx };
      }

      gridRowIdx++;
   }

   std::ostringstream os;
   os << "Element " << elementIdx << " not found.";
   std::invalid_argument e(os.str());
   throw e;
}

IndexType UniformFDMesh::GetElementCount() const
{
   if (m_bIsDirty)
   {
      Update();
   }
   return m_vElements.size();
}

IndexType UniformFDMesh::GetInteriorNodeCount() const
{
   if (m_bIsDirty)
   {
      Update();
   }

   return m_nInteriorNodes;
}

IndexType UniformFDMesh::GetMaxIntriorNodesPerRow() const
{
   if (m_bIsDirty)
   {
      Update();
   }

   return m_nMaxInteriorNodesPerRow;
}

const FDMeshElement* UniformFDMesh::GetElement(IndexType elementIdx) const
{
   if (m_bIsDirty)
   {
      Update();
   }

   return (m_vElements.size() <= elementIdx ? nullptr : &m_vElements[elementIdx]);
}

const FDMeshElement* UniformFDMesh::GetElementAbove(IndexType gridRowIdx, IndexType elementIdx) const
{
   const FDMeshElement* pElement = nullptr;
   if (0 < gridRowIdx && gridRowIdx < m_vGridRows.size())
   {
      const auto& thisRow = m_vGridRows[gridRowIdx];
      IndexType gridElementIdx = thisRow.gridRowStartIdx + elementIdx; // this is the index of the element counting from the left edge of the overall mesh

      const auto& prevRow = m_vGridRows[gridRowIdx - 1];
      IndexType prevGridRowStartIdx = prevRow.gridRowStartIdx;
      IndexType prevGridRowEndIdx = prevRow.gridRowStartIdx + prevRow.nElements - 1;
      if (prevGridRowStartIdx <= gridElementIdx && gridElementIdx <= prevGridRowEndIdx)
      {
         IndexType idx = gridElementIdx - prevRow.gridRowStartIdx + prevRow.firstElementIdx;
         pElement = &m_vElements[idx];
      }
   }
   return pElement;
}

const FDMeshElement* UniformFDMesh::GetElementBelow(IndexType gridRowIdx, IndexType elementIdx) const
{
   if (m_bIsDirty)
   {
      Update();
   }

   const FDMeshElement* pElement = nullptr;
   if (gridRowIdx < m_vGridRows.size())
   {
      const auto& thisRow = m_vGridRows[gridRowIdx];
      IndexType gridElementIdx = thisRow.gridRowStartIdx + elementIdx; // this is the index of the element counting from the left edge of the overall mesh

      const auto& nextRow = m_vGridRows[gridRowIdx + 1];
      IndexType nextGridRowStartIdx = nextRow.gridRowStartIdx;
      IndexType nextGridRowEndIdx = nextRow.gridRowStartIdx + nextRow.nElements - 1;
      if (nextGridRowStartIdx <= gridElementIdx && gridElementIdx <= nextGridRowEndIdx)
      {
         IndexType idx = gridElementIdx - nextRow.gridRowStartIdx + nextRow.firstElementIdx;
         pElement = &m_vElements[idx];
      }
   }
   return pElement;
}

std::pair<IndexType,IndexType> UniformFDMesh::GetGridSize() const
{
   if (m_bIsDirty)
   {
      Update();
   }

   return std::make_pair(m_Nx,m_vGridRows.size());
}

void UniformFDMesh::Update() const
{
   if (std::any_of(m_vGridRows.begin(), m_vGridRows.end(), [](const auto& row) {return row.gridRowStartIdx == INVALID_INDEX || row.firstElementIdx == INVALID_INDEX || row.nElements == INVALID_INDEX; }))
   {
      std::domain_error e("Mesh rows have not been defined. Use AddElements or AddElementRow to defined mesh elements.");
      throw e;
   }

   m_vElements.clear();
   m_vElements.reserve(m_vGridRows.back().firstElementIdx + m_vGridRows.back().nElements);

   auto iter = std::begin(m_vGridRows);
   auto end = std::end(m_vGridRows);

   // create elements for the first row
   // by definition, the top left and top right nodes are boundary nodes
   // the bottom left node of the first element and the bottom right node of the last
   // element are also boundary nodes. we'll deal with the interior nodes as we build the 
   // remaining element rows
   const auto& firstElementRow(*iter++);
   m_nMaxElementsPerRow = firstElementRow.nElements;
   for (IndexType i = 0; i < firstElementRow.nElements; i++)
   {
      m_vElements.emplace_back(FDMeshElement());
   }

   m_nInteriorNodes = 0; // interior node index
   IndexType rowIdx = 1;
   IndexType lastElementPrevRowIdx = firstElementRow.gridRowStartIdx + firstElementRow.nElements - 1;
   for (; iter != end; iter++, rowIdx++)
   {
      const auto& elementRow(*iter);
      IndexType nInteriorNodesThisRow = 0;

      m_nMaxElementsPerRow = max(m_nMaxElementsPerRow, elementRow.nElements);

      // loop over all elements in row
      // the bottom right corner of the last element is a boundary node, unless the mesh is symmetric
      IndexType lastElementThisRowIdx = elementRow.nElements - 1;
      for (IndexType i = 0; i < elementRow.nElements; i++)
      {
         IndexType elementIdxThisRow = i + elementRow.gridRowStartIdx;

         m_vElements.emplace_back(FDMeshElement());
         FDMeshElement* pElement = &m_vElements.back();

         const FDMeshElement* pElementAbove = GetElementAbove(rowIdx, i);

         if (i != 0)
         {
            const FDMeshElement* pPrevElement = &m_vElements[m_vElements.size() - 2];
            pElement->Node[+FDMeshElement::Corner::TopLeft] = pPrevElement->Node[+FDMeshElement::Corner::TopRight];
            if (pElementAbove)
            {
               // bottom left node of the element above this element shares this element's top left node
               (const_cast<FDMeshElement*>(pElementAbove))->Node[+FDMeshElement::Corner::BottomLeft] = pElement->Node[+FDMeshElement::Corner::TopLeft];
            }
         }

         if (pElementAbove)
         {
            const FDMeshElement* pElementAboveRight = GetElementAbove(rowIdx, i + 1);
            if (
               // if this is not the last element in the row and there is an element above and to the right of this element, the right nodes aren't on a boundary
               (i != lastElementThisRowIdx && pElementAboveRight != nullptr)
               || // -OR-
               // if this is the last element in the row, and there is symmetry, and this element is in the last column of the grid, this is an "interior" node (on the symmetry axis)
               (i == lastElementThisRowIdx && m_bIsSymmetric && elementIdxThisRow == m_Nx-1)
               )
            {
               pElement->Node[+FDMeshElement::Corner::TopRight] = m_nInteriorNodes; // this is an interior node
               nInteriorNodesThisRow++;
               m_nInteriorNodes++;

               // bottom right node of the element above this element shares this element's top right node
               (const_cast<FDMeshElement*>(pElementAbove))->Node[+FDMeshElement::Corner::BottomRight] = pElement->Node[+FDMeshElement::Corner::TopRight];
            }
         }
      } // next element in the row
      lastElementPrevRowIdx = elementRow.gridRowStartIdx + elementRow.nElements - 1;
      m_nMaxInteriorNodesPerRow = max(m_nMaxInteriorNodesPerRow, nInteriorNodesThisRow);
   } // next row

   m_bIsDirty = false;
}

void UniformFDMesh::Clear()
{
   m_bIsDirty = true;
   m_Nx = 0;
   m_nMaxInteriorNodesPerRow = 0;
   m_nInteriorNodes = 0;
   m_vElements.clear();
}

IndexType UniformFDMesh::GetFirstElementIndex(IndexType gridRowIdx)
{
   if (gridRowIdx == 0)
   {
      return 0;
   }

   auto& row = m_vGridRows[gridRowIdx];
   if (row.firstElementIdx == INVALID_INDEX)
   {
      return GetFirstElementIndex(gridRowIdx - 1) + m_vGridRows[gridRowIdx - 1].nElements;
   }
   else
   {
      return row.firstElementIdx;
   }
}

#if defined _DEBUG
void UniformFDMesh::Dump(WBFL::Debug::LogContext& os) const
{
   if (m_bIsDirty)
   {
      Update();
   }

   for (const auto& row : m_vGridRows)
   {
      os << "[";
      for (IndexType i = 0; i < row.nElements; i++)
      {
         IndexType elementIdx = row.firstElementIdx + i;
         os << elementIdx << " (";
         for (int j = 0; j < 4; j++)
         {
            if (m_vElements[elementIdx].Node[j] == INVALID_INDEX)
            {
               os << "-";
            }
            else
            {
               os << m_vElements[elementIdx].Node[j];
            }
            os << ", ";
         }
         os << ") ";
      }
      os << "]" << WBFL::Debug::endl;
   }
}
#endif // _DEBUG
