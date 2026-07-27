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

      /// A prescribed support settlement/rotation applied at a joint.
      /// Owned exclusively by the WBFL::FEA2D::Loading it was created on -
      /// see the design note on ownership/lifetime in Joint.h; the same
      /// applies here (private constructor and destructor, Loading as the
      /// only friend).
      class FEA2DCLASS JointDisplacement
      {
      public:
         JointDisplacement(const JointDisplacement&) = delete;
         JointDisplacement& operator=(const JointDisplacement&) = delete;

         LoadIDType GetID() const noexcept;

         JointIDType GetJointID() const noexcept;
         /// Returns true if this changed the JointID
         bool SetJointID(JointIDType jointID) noexcept;

         void GetDeflection(Float64* pDx, Float64* pDy, Float64* pRz) const noexcept;
         /// Always reports changed, unconditionally
         void SetDeflection(Float64 Dx, Float64 Dy, Float64 Rz) noexcept;

         Float64 GetDx() const noexcept;
         bool SetDx(Float64 dx) noexcept;
         Float64 GetDy() const noexcept;
         bool SetDy(Float64 dy) noexcept;
         Float64 GetRz() const noexcept;
         bool SetRz(Float64 rz) noexcept;

         /// Returns the ID of the Loading this load belongs to
         LoadCaseIDType GetLoadingID() const noexcept;

      private:
         friend class Loading;
         friend struct std::default_delete<JointDisplacement>; // see the design note in Joint.h

         JointDisplacement(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, JointIDType jointID, Float64 Dx, Float64 Dy, Float64 Rz);
         ~JointDisplacement() = default;

         Model* m_pModel; // for reporting this loadcase dirty on mutation (Model::OnLoadingChanged)
         LoadCaseIDType m_LoadingID;
         LoadIDType m_ID;
         JointIDType m_JointID;
         Float64 m_Dx;
         Float64 m_Dy;
         Float64 m_Rz;
      };
   };
};
