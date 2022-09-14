///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Math\MathExp.h>

namespace WBFL
{
   namespace Math
   {
      /// System of equations where the coefficient matrix is unsymmetric and banded
      /// 
      /// [A]{B} = {C} 
      /// [Matrix A]*{Vector B} = {Vector C}
      /// 
      /// The system of equations is solved for {B}
      /// 
      /// An example of an unsymmetric banded matrix. There is a band of numbers along
      /// the diagonal, but they are no symmetric about the main diagonal
      /// [A] = [5|2|0|0]
      ///       [3|4|2|0]
      ///       [0|7|6|3]
      ///       [0|0|4|9]
      class MATHCLASS UnsymmetricBandedMatrix
      {
      public:
         enum class Storage
         {
            Column, ///< The coefficient matrix is stored by columns
            Row ///< The coefficient matrix is stored by rows
         };

         UnsymmetricBandedMatrix() = default;
         UnsymmetricBandedMatrix(IndexType N, IndexType BW,Storage storage = Storage::Column);

         // Creates the matrix and vector. The matrix object takes ownership of ba and b
         UnsymmetricBandedMatrix(IndexType N, IndexType BW,Storage storage, Float64** ba, Float64* b);
         ~UnsymmetricBandedMatrix();

         // copy semantics are non-trivial and have not been implemented
         UnsymmetricBandedMatrix(const UnsymmetricBandedMatrix&) = delete;
         UnsymmetricBandedMatrix& operator=(const UnsymmetricBandedMatrix&) = delete;

         void Initialize(IndexType N, IndexType BW);
         IndexType GetSize() const;
         IndexType GetBandwidth() const;
         void SetCoefficient(IndexType i, IndexType j, Float64 aij);
         Float64 GetCoefficient(IndexType i, IndexType j);
         void SetB(IndexType i, Float64 bi);
         Float64 GetB(IndexType i) const;
         std::unique_ptr<Float64[]> Solve();

         Float64& operator()(IndexType i, IndexType j);
         Float64& operator[](IndexType i);

         void Dump(std::ostream& os, bool bFull) const;

      private:
         IndexType N{0};
         IndexType BW{0};
         IndexType half_band_width{0};
         Float64** ba = nullptr;
         Float64* b = nullptr;
         Storage storage{Storage::Column};

         void Full2Condensed(IndexType i, IndexType j, IndexType half_band_width, IndexType& m, IndexType& n) const;
         void ReduceRow(Float64 c, IndexType i, IndexType j, IndexType kStart, IndexType kEnd);

         void Clear();
         void DumpBanded(std::ostream& os) const;
         void DumpFull(std::ostream& os) const;
      };
   };
};
