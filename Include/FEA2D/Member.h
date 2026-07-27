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
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Model;
      class Joint;
      class Loading;

      // Forward-only references to internal implementation-only types
      // (defined in the private FEA2D\Matrix.h / MbrLoad.h / Result.h,
      // which this public header deliberately never includes - matching
      // RCSection's *SolverImpl.h Pimpl convention, and importantly
      // keeping consumers of WBFLFEA2D.dll (Phase 3: LBAM, PGSuper, ...)
      // from ever needing FEA2D's private implementation directory on
      // their own include path).
      namespace Internals
      {
         class MbrLoad;
         template <LONG N> class Vector;
         using Vector6 = Vector<6>;
         template <LONG TNForceDof, LONG TNDispDof> class Result;
      };

      /// A 2-joint beam-column element. Owned exclusively by the Model it
      /// was created on - see the design note on ownership/lifetime in
      /// Joint.h; the same applies here (private constructor and
      /// destructor, Model as the only friend).
      ///
      /// Member's mutators do not fire change notifications themselves;
      /// they return bool to report whether a change occurred - see the
      /// design note in Joint.h.
      class FEA2DCLASS Member
      {
      public:
         static constexpr int NumJoints = 2;
         static constexpr int TotalDOF = 6;
         using MbrResult = Internals::Result<12, 12>;

         Member(const Member&) = delete;
         Member& operator=(const Member&) = delete;

         MemberIDType GetID() const noexcept;

         JointIDType GetStartJoint() const noexcept;
         /// Returns true if this changed the start joint
         bool SetStartJoint(JointIDType id) noexcept;
         JointIDType GetEndJoint() const noexcept;
         /// Returns true if this changed the end joint
         bool SetEndJoint(JointIDType id) noexcept;

         Float64 GetEA() const noexcept;
         /// Throws XFEA2D(ReasonCode::StiffnessMustBePositive) if EA <= 0.
         /// Returns true if this changed EA.
         bool SetEA(Float64 EA);
         Float64 GetEI() const noexcept;
         /// Throws XFEA2D(ReasonCode::StiffnessMustBePositive) if EI <= 0.
         /// Returns true if this changed EI.
         bool SetEI(Float64 EI);

         /// Throws XFEA2D if the start/end joints are the same, don't
         /// exist, or the resulting length is zero. Deliberately does a
         /// fresh joint lookup rather than using the (potentially stale)
         /// JointKeeper cache - mirrors CMember::get_Length(), which does
         /// the same for the same reason: joints don't invalidate a
         /// member's cached length when their X/Y position changes, so the
         /// cache can't be trusted for a real-time query.
         Float64 GetLength() const;

         /// Returns true unconditionally (mirrors CMember::ReleaseEnd,
         /// which always fires)
         bool ReleaseEnd(MemberEndType end, MemberReleaseType releaseType) noexcept;
         bool IsReleased(MemberEndType end, MemberReleaseType releaseType) const noexcept;

         bool operator==(const Member& mbr) const noexcept;

         // functions to deal with location rule. if loc is positive, it is
         // measured directly along member, if -1.0<=loc<0.0, it is
         // fractional. Returns -1 if location is beyond end of beam.
         static Float64 GetRealLocation(Float64 length, Float64 loc);
         Float64 GetRealLocation(Float64 loc) const;

      private:
         friend class Model;
         friend class Joint;
         friend class Loading;
         friend struct std::default_delete<Member>; // see the design note in Joint.h

         Member(Model* pModel, MemberIDType id, JointIDType startJoint = -1, JointIDType endJoint = -1, Float64 EA = 0.0, Float64 EI = 0.0);
         ~Member(); // defined out-of-line in Member.cpp - MemberImpl is incomplete here

         // fe analysis-related functions - internal use only, called by
         // Model/Joint/Loading during Compute()
         void InitModel();
         void ClearLoads();
         void AssembleF();
         JointIDType GetJointNum(const Joint* pj) const;
         void GetGlobalJntForces(JointIDType jntId, Float64* force) const;
         /// Member orientation angle (radians, from the start joint to the
         /// end joint) - needed by Model's result queries to rotate
         /// member-local force/deflection results into global coordinates
         /// when a caller asks for LoadOrientation::Global(Projected).
         Float64 GetAngle() const;
         void ComputeResults();
         LONG GetNumDOF() const noexcept;
         LONG GetNumJoints() const noexcept;
         LONG GetCondensedDOF(LONG dof) const;
         Float64 GetKglobal(LONG DOFi, LONG DOFj) const;
         void GetFglobal(Float64* f) const;

         void ApplyLoad(Internals::MbrLoad* load);

         void ComputeDeflections();
         void ComputeForces();
         void ComputeJointDeflectionForce(Internals::Vector6& pdf) const;

         void GetResults(MbrResult* pres) const;
         void SetResults(const MbrResult& res);

         void GetInternalForces(Float64 loc, MemberFaceType face, Float64* force) const;
         void GetDeflection(Float64 loc, Float64* disp) const;

         bool IsEquilibriumSatisfied(Float64 forceTolerance, Float64 momentTolerance);

         long GetReleaseTypeFlag(MemberReleaseType releaseType) const noexcept;

         void BuildTransformationMatrix();
         void BuildKlocal();
         void BuildKglobal();
         void ComputeFemResults();
         void ComputeClassicResults();
         void GetPinPinRotation(Float64& rz1, Float64& rz2) const;
         void GetPinFixRotation(Float64& rz1) const;
         void GetFixPinRotation(Float64& rz2) const;

         class MemberImpl;
         std::unique_ptr<MemberImpl> m_pImpl;
      };
   };
};
