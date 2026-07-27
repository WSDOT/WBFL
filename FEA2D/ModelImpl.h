///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
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

// Private implementation detail for WBFL::FEA2D::Model (Pimpl - see the
// design note at the top of Include\FEA2D\Member.h for why). Holds the
// global stiffness matrix/force vector and the per-loading result caches,
// all of which use the internal-only SymBandedMatrix/Result<> types.

#pragma once

#include <FEA2D\Model.h>
#include "SymBandedMatrix.h"
#include "Result.h"
#include <map>
#include <memory>
#include <set>

namespace WBFL
{
   namespace FEA2D
   {
      class Model::ModelImpl
      {
      public:
         static constexpr LONG NumJointDof = Joint::NumDof; // 3

         Float64 m_ForceEquilibriumTolerance = 0.10;
         Float64 m_MomentEquilibriumTolerance = 0.10;
         std::_tstring m_Name;

         // Lazy-analysis dirty tracking (see EnsureAnalyzed() in Model.cpp).
         // Starts fully dirty: a freshly-constructed model has never been
         // analyzed. m_bStructuralDirty means the global stiffness matrix
         // itself is stale (a joint/member changed) - when set, every
         // loading's stored results are stale too, not just the matrix.
         // m_DirtyLoadings tracks loadings that need a fresh solve+store
         // even though K itself is still valid (only their loads changed).
         // Both live here (behind Model's unique_ptr<ModelImpl>) rather than
         // as direct Model data members specifically so EnsureAnalyzed() and
         // its callers can stay const - unique_ptr doesn't propagate
         // constness to what it points to, so no `mutable` is needed either.
         bool m_bStructuralDirty = true;
         std::set<LoadCaseIDType> m_DirtyLoadings;

         LONG m_BandWidth = -1;
         LONG m_NumGlobalDOF = -1;
         LONG m_NumCondensedDOF = -1;
         Internals::SymBandedMatrix m_K; // condensed global stiffness matrix
         Float64* m_pF = nullptr;     // condensed global force vector, size m_NumCondensedDOF

         ~ModelImpl()
         {
            FreeFGlobal();
         }

         void FreeFGlobal()
         {
            delete[] m_pF;
            m_pF = nullptr;
         }

         using JntResult = Internals::Result<NumJointDof, NumJointDof>;
         using JntResultArray = Internals::ResultArray<JntResult>;
         std::map<JointIDType, std::unique_ptr<JntResultArray>> m_JntResults;

         using MbrResult = Member::MbrResult; // Internals::Result<12,12>
         using MbrResultArray = Internals::ResultArray<MbrResult>;
         std::map<MemberIDType, std::unique_ptr<MbrResultArray>> m_MbrResults;

         // 2*NumJointDof force values (left-face fx,fy,mz then right-face
         // fx,fy,mz), NumJointDof deflection values (dx,dy,rz) - mirrors
         // CModel's PoiResult = Result<NUM_DOF*2, NUM_DOF>.
         using PoiResult = Internals::Result<2 * NumJointDof, NumJointDof>;
         using PoiResultArray = Internals::ResultArray<PoiResult>;
         std::map<PoiIDType, std::unique_ptr<PoiResultArray>> m_PoiResults;

         // Simple cache for negative load case POI results (e.g. LBAM
         // influence-line queries, which ask for the same POI/negative
         // load case repeatedly in a row) - mirrors CModel's
         // SimplePOIResultCache exactly.
         struct SimplePOIResultCache
         {
            SimplePOIResultCache() : m_PoiID(-MAX_ID), m_LoadCase(-MAX_ID), m_PoiResult(-MAX_ID) {}

            bool IsHit(PoiIDType poiid, LoadCaseIDType lcase) const noexcept
            {
               if (lcase < 0) // only cache negative load cases
                  return poiid == m_PoiID && lcase == m_LoadCase;
               else
                  return false;
            }

            void ClearCache() noexcept
            {
               m_PoiID = -MAX_ID;
               m_LoadCase = -MAX_ID;
            }

            void Update(PoiIDType poiid, LoadCaseIDType lcase, const PoiResult& poiresult)
            {
               m_PoiID = poiid;
               m_LoadCase = lcase;
               m_PoiResult = poiresult;
            }

            PoiResult m_PoiResult;

         private:
            PoiIDType m_PoiID;
            LoadCaseIDType m_LoadCase;
         } m_SimplePOIResultCache;
      };
   };
};
