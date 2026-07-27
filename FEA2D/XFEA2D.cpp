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

#include <FEA2D\FEA2DLib.h>
#include <FEA2D\XFEA2D.h>

using namespace WBFL::FEA2D;

XFEA2D::XFEA2D(ReasonCode reason, const std::_tstring& file, Uint32 line) :
   WBFL::System::XBase(file, line), m_Reason(reason)
{
}

void XFEA2D::Throw() const
{
   throw* static_cast<const XFEA2D*>(this);
}

Int32 XFEA2D::GetReason() const noexcept
{
   return static_cast<Int32>(m_Reason);
}

ReasonCode XFEA2D::GetReasonCode() const noexcept
{
   return m_Reason;
}

std::_tstring XFEA2D::GetErrorMessage() const
{
   std::_tstring reasonMsg;
   switch (m_Reason)
   {
   case ReasonCode::MemberHasSameJoints:            reasonMsg = _T("Member start and end joint must be different"); break;
   case ReasonCode::MemberJointNotExists:           reasonMsg = _T("Member references a joint that does not exist"); break;
   case ReasonCode::MemberWithIdAlreadyExists:      reasonMsg = _T("A member with this ID already exists"); break;
   case ReasonCode::JointWithIdAlreadyExists:       reasonMsg = _T("A joint with this ID already exists"); break;
   case ReasonCode::StiffnessMustBePositive:        reasonMsg = _T("Stiffness must be positive"); break;
   case ReasonCode::JointLoadWithIdAlreadyExists:   reasonMsg = _T("A joint load with this ID already exists"); break;
   case ReasonCode::PointLoadWithIdAlreadyExists:   reasonMsg = _T("A point load with this ID already exists"); break;
   case ReasonCode::LoadingWithIdAlreadyExists:     reasonMsg = _T("A loading with this ID already exists"); break;
   case ReasonCode::InvalidPointLoadLocation:       reasonMsg = _T("Location of point load must be greater than or equal to -1.0"); break;
   case ReasonCode::InvalidPoiLocation:              reasonMsg = _T("Location of POI must be greater than or equal to -1.0"); break;
   case ReasonCode::PoiWithIdAlreadyExists:          reasonMsg = _T("A POI with this ID already exists"); break;
   case ReasonCode::PointLoadOffGirderEnd:           reasonMsg = _T("Point load is located beyond the end of a member"); break;
   case ReasonCode::FractionalValueOutOfRange:       reasonMsg = _T("Fractional values must range from -1.0 to 0.0"); break;
   case ReasonCode::ZeroLengthMember:                reasonMsg = _T("Member has zero length"); break;
   case ReasonCode::JointEquilibriumNotSatisfied:    reasonMsg = _T("Equilibrium not satisfied for joint"); break;
   case ReasonCode::MemberEquilibriumNotSatisfied:   reasonMsg = _T("Equilibrium not satisfied for member"); break;
   case ReasonCode::PoiReferencesMemberNotExists:    reasonMsg = _T("POI references a member which does not exist"); break;
   case ReasonCode::PoiFractionalOutOfRange:         reasonMsg = _T("POI has fractional location that is less than -1.0"); break;
   case ReasonCode::PoiLocatedOffMemberEnd:          reasonMsg = _T("POI is located beyond the end of a member"); break;
   case ReasonCode::JointNotFound:                   reasonMsg = _T("Joint not found"); break;
   case ReasonCode::LoadingNotFound:                 reasonMsg = _T("Loading not found"); break;
   case ReasonCode::MemberNotFound:                  reasonMsg = _T("Member not found"); break;
   case ReasonCode::PoiNotFound:                     reasonMsg = _T("POI not found"); break;
   case ReasonCode::SolvingGlobalStiffness:          reasonMsg = _T("Error in global stiffness solution. Structure may be unstable."); break;
   case ReasonCode::InvalidGlobalDof:                reasonMsg = _T("Invalid global degree of freedom"); break;
   case ReasonCode::InvalidCondensedDof:             reasonMsg = _T("Invalid condensed degree of freedom"); break;
   case ReasonCode::JointLoadRefJointNotExists:      reasonMsg = _T("Joint load references a joint which does not exist"); break;
   case ReasonCode::PointLoadRefMemberNotExists:     reasonMsg = _T("Point load references a member which does not exist"); break;
   case ReasonCode::JointDispWithIdAlreadyExists:    reasonMsg = _T("A joint deflection load with this ID already exists"); break;
   case ReasonCode::JointDispRefJointNotExists:      reasonMsg = _T("Joint deflection references a joint which does not exist"); break;
   case ReasonCode::JointDispToFixedDofOnly:         reasonMsg = _T("Joint deflections may only be applied to supported DOFs"); break;
   case ReasonCode::MatrixBackSubstitution:          reasonMsg = _T("Error during matrix back-substitution. The structure is likely unstable."); break;
   case ReasonCode::MatrixFactoring:                 reasonMsg = _T("Error during matrix factoring. The structure is likely unstable."); break;
   case ReasonCode::DistLoadOffGirderEnd:            reasonMsg = _T("Distributed load is located beyond the end of a member"); break;
   case ReasonCode::DistLoadBBeforeA:                reasonMsg = _T("Distributed load end location must not be before its start location"); break;
   case ReasonCode::DistLoadRefMemberNotExists:      reasonMsg = _T("Distributed load references a member which does not exist"); break;
   case ReasonCode::InvalidDistLoadLocation:         reasonMsg = _T("Location of distributed load start and end must be greater than or equal to -1.0"); break;
   case ReasonCode::DistLoadWithIdAlreadyExists:     reasonMsg = _T("A distributed load with this ID already exists"); break;
   case ReasonCode::InvalidLoadOrientation:          reasonMsg = _T("Invalid load orientation parameter"); break;
   case ReasonCode::MemberStrainWithIdAlreadyExists: reasonMsg = _T("A member strain load with this ID already exists"); break;
   case ReasonCode::ModelHasNoJoints:                reasonMsg = _T("Model must have at least one joint"); break;
   case ReasonCode::ModelHasNoMembers:               reasonMsg = _T("Model must have at least one member"); break;
   case ReasonCode::StrainLoadOffGirderEnd:          reasonMsg = _T("Member strain load is located beyond the end of a member"); break;
   case ReasonCode::PersistenceIOError:              reasonMsg = _T("An error occurred reading or writing the structured storage file"); break;
   case ReasonCode::PersistenceBadVersion:           reasonMsg = _T("The file was saved by a newer version of FEA2D"); break;
   case ReasonCode::PersistenceInvalidFormat:        reasonMsg = _T("The file is corrupt or truncated"); break;
   default:                                          reasonMsg = _T("Unknown FEA2D error"); break;
   }

   auto msg = __super::GetErrorMessage();
   msg += reasonMsg;
   return msg;
}
