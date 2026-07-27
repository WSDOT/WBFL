///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <FEA2D\FEA2DExp.h>
#include <FEA2D\Enums.h>
#include <WBFLTypes.h>
#include <set>
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Model;
      class Member;
      class Loading;
      class JointLoad;
      class JointDisplacement;

      /// A node in the finite element model. Owned exclusively by the Model
      /// it was created on - CreateJoint()/FindJoint() hand out a non-owning
      /// Joint* into storage Model retains for the object's whole life; the
      /// constructor and destructor are both private (with Model as the
      /// only friend) specifically so a caller can't construct one directly
      /// or delete the one they were handed - only Model may create or
      /// destroy a Joint. Use Model::RemoveJoint()/ClearJoints() to end a
      /// Joint's life instead.
      ///
      /// A query for the members attached to this joint would have to walk
      /// every member, and Model already owns the full member collection,
      /// so that query lives on Model instead (see
      /// Model::GetAttachedMembers()). Joint does hold a back-pointer to
      /// Model, but only a narrow one: mutators report a structural change
      /// to Model::OnStructuralChange() so Model knows to refactor the
      /// stiffness matrix before the next result query (see the design
      /// note on Model::EnsureAnalyzed()) - Joint itself still doesn't fire
      /// COM-style change-notification events; that's the retained Fem2d
      /// COM facade's job (which depends on FEA2D, not the other way
      /// around), translating a bool mutator result into an OnModelChanged
      /// event for its VBA/Excel clients.
      class FEA2DCLASS Joint
      {
      public:
         static constexpr int NumDof = 3;

         Joint(const Joint&) = delete;
         Joint& operator=(const Joint&) = delete;

         JointIDType GetID() const noexcept;

         Float64 GetX() const noexcept;
         /// Returns true if this changed X
         bool SetX(Float64 x) noexcept;
         Float64 GetY() const noexcept;
         /// Returns true if this changed Y
         bool SetY(Float64 y) noexcept;

         /// Returns true if this changed the release state
         bool ReleaseDof(JointReleaseType rel) noexcept;
         /// Fully releases (frees) the joint. Returns true if this changed
         /// the release state
         bool Free() noexcept;
         /// Fully supports (fixes) the joint. Returns true if this changed
         /// the release state
         bool Support() noexcept;

         bool IsSupport() const noexcept;
         bool IsDofReleased(JointReleaseType rel) const noexcept;
         bool IsDofSupported(JointReleaseType rel) const noexcept;

      private:
         friend class Model;
         friend class Member;
         friend class Loading;
         // unique_ptr<Joint>'s default deleter (owned by Model::m_Joints)
         // calls delete from inside this standard library helper, not from
         // inside Model itself, so it needs its own grant - see the design
         // note on the private destructor below.
         friend struct std::default_delete<Joint>;

         Joint(Model* pModel, JointIDType id, Float64 x = 0.0, Float64 y = 0.0);
         ~Joint() = default;

         // fe analysis-related functions - internal use only, called by
         // Model/Member during Model::EnsureAnalyzed()
         void InitModel(LONG nGDOF, LONG nCDOF, LONG& nGDOFused, LONG& nCDOFused);
         LONG GetGlobalDOF(LONG dof) const;
         LONG GetCondensedDOF(LONG dof) const;

         void ClearLoads();
         void ApplyLoad(const JointLoad* ld);
         void ApplyLoad(const JointDisplacement* ld);
         bool WasDeflectionLoadApplied() const noexcept { return m_dispLoadApplied; }
         void GetFglobal(Float64* v) const;

         void SetDeflection(const Float64* disp);
         void GetDeflection(Float64* disp) const;

         void ComputeReactions();
         void GetReactions(Float64* react) const;

         void Link(Member* pel);

         bool IsEquilibriumSatisfied(Float64 forceTolerance, Float64 momentTolerance);

         Model* m_pModel; // for reporting structural changes (Model::OnStructuralChange)
         JointIDType m_ID;
         Float64 m_X;
         Float64 m_Y;
         long m_Releases; // a bit value of true means dof is free

         LONG m_CondensedDOF[NumDof];  // Condensed DOF numbers
         LONG m_GlobalDOF[NumDof];     // Global DOF numbers
         Float64 m_jntLoad[NumDof];     // Joint loads
         Float64 m_dispLoad[NumDof];    // Joint deflection load
         bool m_dispLoadApplied;       // was applied?
         Float64 m_Disp[NumDof];        // deflections
         Float64 m_Reaction[NumDof];    // reactions

         std::set<Member*> m_AttachedMembers; // members attached to this joint - only valid during/after Compute()
      };
   };
};
