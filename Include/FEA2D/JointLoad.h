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
#include <WBFLTypes.h>
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Loading;
      class Model;

      /// A concentrated force/moment applied directly at a joint. Owned
      /// exclusively by the WBFL::FEA2D::Loading it was created on - see
      /// the design note on ownership/lifetime in Joint.h; the same
      /// applies here (private constructor and destructor, Loading as the
      /// only friend).
      class FEA2DCLASS JointLoad
      {
      public:
         JointLoad(const JointLoad&) = delete;
         JointLoad& operator=(const JointLoad&) = delete;

         LoadIDType GetID() const noexcept;

         JointIDType GetJointID() const noexcept;
         /// Returns true if this changed the JointID (facade uses this to
         /// decide whether to fire an OnLoadingChanged event)
         bool SetJointID(JointIDType jointID) noexcept;

         void GetForce(Float64* pFx, Float64* pFy, Float64* pMz) const noexcept;
         /// Always reports changed, unconditionally
         void SetForce(Float64 Fx, Float64 Fy, Float64 Mz) noexcept;

         Float64 GetFx() const noexcept;
         bool SetFx(Float64 fx) noexcept;
         Float64 GetFy() const noexcept;
         bool SetFy(Float64 fy) noexcept;
         Float64 GetMz() const noexcept;
         bool SetMz(Float64 mz) noexcept;

         /// Returns the ID of the Loading this load belongs to
         LoadCaseIDType GetLoadingID() const noexcept;

      private:
         friend class Loading;
         friend struct std::default_delete<JointLoad>; // see the design note in Joint.h

         // loadingID is cached rather than a back-pointer to Loading - a
         // load's Loading membership never changes after creation (the COM
         // interface never exposed a put_Loading), so there's no need to
         // couple JointLoad to Loading's full definition. m_pModel is a
         // separate, narrower back-pointer solely so mutators can report
         // this loadcase dirty (see Model::OnLoadingChanged) - it doesn't
         // need Loading's definition either.
         JointLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, JointIDType jointID, Float64 Fx, Float64 Fy, Float64 Mz);
         ~JointLoad() = default;

         Model* m_pModel;
         LoadCaseIDType m_LoadingID;
         LoadIDType m_ID;
         JointIDType m_JointID;
         Float64 m_Fx;
         Float64 m_Fy;
         Float64 m_Mz;
      };
   };
};
