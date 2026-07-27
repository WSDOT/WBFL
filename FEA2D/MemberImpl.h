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

// Private implementation detail for WBFL::FEA2D::Member (Pimpl - see the
// design note at the top of Include\FEA2D\Member.h). Holds every field
// that touches the internal-only Matrix/Vector6/MbrLoad types, so that
// header never has to include Matrix.h/MbrLoad.h/Result.h.

#pragma once

#include <FEA2D\Member.h>
#include <FEA2D\Joint.h>
#include "Matrix.h"
#include "MbrLoad.h"
#include "Result.h"
#include <list>

namespace WBFL
{
   namespace FEA2D
   {
      class Member::MemberImpl
      {
      public:
         MemberImpl(Member* pMember, Model* pModel, MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI);

         Model* m_pModel; // for resolving joint IDs during Compute()
         MemberIDType m_ID;
         long m_StartReleases;
         long m_EndReleases;
         Float64 m_EA;
         Float64 m_EI;

         Internals::Matrix m_Kglobal;
         Internals::Matrix m_Klocal;
         Internals::Vector6 m_Fglobal;
         Internals::Matrix m_TransMatrix;

         std::list<Internals::MbrLoad*> m_Loads; // non-owning - Loading owns the concrete load objects

         Internals::Vector6 m_Dlocal; // local deflections
         Internals::Vector6 m_Rlocal; // local resultant forces

         // a little class to keep our joint information up to date and to
         // optimize length and angle calculations
         class JointKeeper
         {
         public:
            // Takes pModel directly (rather than reaching through
            // pMember->m_pImpl->m_pModel) to avoid relying on the
            // multi-level nested-class access rules for a class nested two
            // levels deep (JointKeeper in MemberImpl in Member).
            JointKeeper(Member* pMember, Model* pModel);
            bool PutStartJoint(JointIDType id);
            JointIDType GetStartJoint() const noexcept;
            bool PutEndJoint(JointIDType id);
            JointIDType GetEndJoint() const noexcept;
            void GetJoints(Joint** pStart, Joint** pEnd);
            Float64 GetLength();
            Float64 GetAngle();
            bool m_Dirty;
         private:
            JointKeeper() = delete;
            void Compute();
            Member* m_pMember;
            Model* m_pModel;
            JointIDType m_StartJoint;
            JointIDType m_EndJoint;
            Joint* m_pStartJoint;
            Joint* m_pEndJoint;
            Float64 m_Length;
            Float64 m_Angle;
         };

         JointKeeper m_JointKeeper;
      };
   };
};
