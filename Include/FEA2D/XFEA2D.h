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

#include <FEA2D/FEA2DExp.h>
#include <System/Exception.h>

#define THROW_FEA2D(reason) throw XFEA2D(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace FEA2D
   {
      /// Numeric reason codes for XFEA2D. Values are kept numerically
      /// identical to the corresponding FEM2D_E_* HRESULT codes declared in
      /// Fem2dErrors.h (i.e. ReasonCode == HRESULT_CODE(FEM2D_E_XXX)) so the
      /// retained Fem2d COM facade can translate a caught XFEA2D back to the
      /// exact original HRESULT with a single table lookup, rather than
      /// duplicating error-classification logic. In-tree C++ consumers can
      /// just catch XFEA2D directly and never need to look at this code.
      enum class ReasonCode
      {
         MemberHasSameJoints = 512,
         MemberJointNotExists = 513,
         MemberWithIdAlreadyExists = 514,
         JointWithIdAlreadyExists = 515,
         StiffnessMustBePositive = 516,
         JointLoadWithIdAlreadyExists = 517,
         PointLoadWithIdAlreadyExists = 518,
         LoadingWithIdAlreadyExists = 519,
         InvalidPointLoadLocation = 520,
         InvalidPoiLocation = 521,
         PoiWithIdAlreadyExists = 522,
         PointLoadOffGirderEnd = 523,
         FractionalValueOutOfRange = 524,
         ZeroLengthMember = 525,
         JointEquilibriumNotSatisfied = 526,
         MemberEquilibriumNotSatisfied = 527,
         PoiReferencesMemberNotExists = 528,
         PoiFractionalOutOfRange = 529,
         PoiLocatedOffMemberEnd = 530,
         JointNotFound = 531,
         LoadingNotFound = 532,
         MemberNotFound = 533,
         PoiNotFound = 534,
         SolvingGlobalStiffness = 535,
         InvalidGlobalDof = 536,
         InvalidCondensedDof = 537,
         JointLoadRefJointNotExists = 538,
         PointLoadRefMemberNotExists = 539,
         JointDispWithIdAlreadyExists = 540,
         JointDispRefJointNotExists = 541,
         JointDispToFixedDofOnly = 542,
         MatrixBackSubstitution = 543,
         MatrixFactoring = 544,
         StrainLoadOffGirderEnd = 546,
         DistLoadOffGirderEnd = 545,
         DistLoadBBeforeA = 547,
         DistLoadRefMemberNotExists = 548,
         InvalidDistLoadLocation = 549,
         DistLoadWithIdAlreadyExists = 550,
         InvalidLoadOrientation = 551,
         MemberStrainWithIdAlreadyExists = 552,
         ModelHasNoJoints = 553,
         ModelHasNoMembers = 554,

         // Persistence (Model::Save/Load) failures - these have no
         // corresponding FEM2D_E_* HRESULT in Fem2dErrors.h, since the
         // legacy engine let raw IStructuredSave2/Load2 HRESULTs (or the
         // STRLOAD_E_* constants below) propagate directly rather than
         // wrapping them in a domain error. Given a number outside the
         // 512-554 range used above so they're visually distinguishable
         // from the FEM2D_E_* mirror.
         PersistenceIOError = 600,      // an IStructuredSave2/Load2 call itself failed
         PersistenceBadVersion = 601,   // STRLOAD_E_BADVERSION equivalent - file too new
         PersistenceInvalidFormat = 602,// STRLOAD_E_INVALIDFORMAT equivalent - corrupt/truncated
      };

      /// A FEA2D modeling or solution error has occurred
      class FEA2DCLASS XFEA2D : public WBFL::System::XBase
      {
      public:
         XFEA2D() = default;
         XFEA2D(const XFEA2D&) = default;

         /// Constructs the exception. Prefer the THROW_FEA2D(reason) macro over
         /// calling this directly - it supplies the file and line automatically.
         XFEA2D(ReasonCode reason, const std::_tstring& file, Uint32 line);
         virtual ~XFEA2D() = default;

         XFEA2D& operator=(const XFEA2D&) = default;

         /// Performs a polymorphic re-throw of *this, preserving the concrete
         /// exception type. Use this to re-throw a previously-caught XFEA2D
         /// (e.g. after catching it as a reference to its WBFL::System::XBase
         /// base class) without slicing it.
         virtual void Throw() const override;

         /// Returns the numeric ReasonCode this exception was constructed
         /// with, as an Int32.
         virtual Int32 GetReason() const noexcept override;

         /// Returns the ReasonCode this exception was constructed with.
         ReasonCode GetReasonCode() const noexcept;

         /// Returns the base class error message with a description of the
         /// reason code appended.
         virtual std::_tstring GetErrorMessage() const override;

      private:
         ReasonCode m_Reason = ReasonCode::ModelHasNoJoints;
      };
   };
};
