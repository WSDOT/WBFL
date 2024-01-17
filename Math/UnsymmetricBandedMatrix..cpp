///////////////////////////////////////////////////////////////////////
// BEToolbox
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Math\MathLib.h>
#include <Math/UnsymmetricBandedMatrix.h>
#include <System\Threads.h>
#include <vector>
#include <future>

using namespace WBFL::Math;

UnsymmetricBandedMatrix::UnsymmetricBandedMatrix(IndexType N, IndexType BW,Storage storage) :
   N(N), BW(BW), storage(storage)
{
   Initialize(N, BW);
}

void UnsymmetricBandedMatrix::Initialize(IndexType n, IndexType bw)
{
   b.clear();
   ba.clear();

   N = n;
   BW = bw;
   half_band_width = BW / 2;

   if (storage == Storage::Column)
   {
      std::vector<Float64> z;
      z.resize(BW, 0.0);
      ba.resize(N, z);
   }
   else
   {
      std::vector<Float64> z;
      z.resize(N, 0.0);
      ba.resize(BW, z);
   }

   b.resize(N, 0.0);
}

IndexType UnsymmetricBandedMatrix::GetSize() const
{
   return N;
}

IndexType UnsymmetricBandedMatrix::GetBandwidth() const
{
   return BW;
}

void UnsymmetricBandedMatrix::SetCoefficient(IndexType i, IndexType j, Float64 aij)
{
   IndexType m, n;
   Full2Condensed(i, j, half_band_width, m, n);
   ba[m][n] = aij;
}

Float64 UnsymmetricBandedMatrix::GetCoefficient(IndexType i, IndexType j) const
{
   IndexType m, n;
   Full2Condensed(i, j, half_band_width, m, n);
   return (BW <= n ? 0 : ba[m][n]);
}

void UnsymmetricBandedMatrix::SetC(IndexType i, Float64 bi)
{
   b[i] = bi;
}

Float64 UnsymmetricBandedMatrix::GetC(IndexType i) const
{
   return b[i];
}

std::vector<Float64> UnsymmetricBandedMatrix::Solve()
{
   std::vector<Float64> x;
   x.resize(N, 0.0);

   // Gaussian elimination phase
   for (IndexType j = 0; j < N; j++)
   {
      IndexType jmax = min(j + half_band_width, N - 1);
      for (IndexType i = j + 1; i <= jmax; i++)
      {
         IndexType m, n;
         Full2Condensed(i, j, half_band_width, m, n);
         Float64 Aij = ba[m][n];
         Full2Condensed(j, j, half_band_width, m, n);
         Float64 Ajj = ba[m][n];
         CHECK(!IsZero(Ajj));

         Float64 c = Aij / Ajj;
         IndexType kmin = max(j, j < half_band_width ? 0 : j - half_band_width);
         IndexType kmax = min(j + half_band_width, N - 1);

         IndexType nWorkerThreads, nElementsPerThread;
         WBFL::System::Threads::GetThreadParameters(kmax - kmin + 1, nWorkerThreads, nElementsPerThread);
         std::vector<std::future<void>> vFutures;
         IndexType kStart = kmin;
         for (IndexType t = 0; t < nWorkerThreads; t++)
         {
            IndexType kEnd = kStart + nElementsPerThread - 1;
            vFutures.emplace_back(std::async([this, c, i, j, kStart, kEnd] {ReduceRow(c, i, j, kStart, kEnd);}));
            kStart = kEnd + 1;
         }

         ReduceRow(c, i, j, kStart, kmax);

         for (auto& f : vFutures)
         {
            f.get();
         }
         b[i] -= c*b[j];
      }
   }

   // Back substitution phase
   IndexType m, n;
   Full2Condensed(N - 1, N - 1, half_band_width, m, n);
   Float64 Ann = ba[m][n];
   x[N - 1] = b[N - 1] / Ann;
   for (IndexType i = N - 2; i >= 0 && i != INVALID_INDEX; i--)
   {
      Float64 sum = 0;
      IndexType kmax = min(i + half_band_width, N - 1);
      for (IndexType j = i + 1; j <= kmax; j++)
      {
         Full2Condensed(i, j, half_band_width, m, n);
         sum += ba[m][n] * x[j];
      }
      Full2Condensed(i, i, half_band_width, m, n);
      Float64 Aii = ba[m][n];
      x[i] = (b[i] - sum) / Aii;
   }

   return x;
}

void UnsymmetricBandedMatrix::Full2Condensed(IndexType i, IndexType j, IndexType half_band_width, IndexType& m, IndexType& n) const
{
   if (storage == Storage::Column)
   {
      m = i;
      n = j - i + half_band_width;
   }
   else
   {
      m = j - i + half_band_width;
      n = i;
   }
}

void UnsymmetricBandedMatrix::ReduceRow(Float64 c, IndexType i, IndexType j, IndexType kStart, IndexType kEnd)
{
   for (IndexType k = kStart; k <= kEnd; k++)
   {
      IndexType o, p;
      Full2Condensed(j, k, half_band_width, o, p);
      Float64 c_Ajk = c*ba[o][p];

      IndexType m, n;
      Full2Condensed(i, k, half_band_width, m, n);
      ba[m][n] -= c_Ajk;
   }
}

Float64 UnsymmetricBandedMatrix::operator()(IndexType i, IndexType j) const
{
   return GetCoefficient(i, j);
}

Float64 UnsymmetricBandedMatrix::operator[](IndexType i) const
{
   return GetC(i);
}

void UnsymmetricBandedMatrix::Dump(std::ostream& os, bool bFull) const
{
   if (bFull)
      DumpFull(os);
   else
      DumpBanded(os);
}

void UnsymmetricBandedMatrix::DumpBanded(std::ostream& os) const
{
   for (IndexType i = 0; i < N; i++)
   {
      os << "[";
      for (IndexType j = 0; j < BW; j++)
      {
         if (storage == Storage::Row)
            std::swap(i, j);

         os << ba[i][j] << " ";
      }
      os << "]" << std::endl;
   }
}

void UnsymmetricBandedMatrix::DumpFull(std::ostream& os) const
{
   for (IndexType i = 0; i < N; i++)
   {
      os << "[";
      for (IndexType j = 0; j < N; j++)
      {
         IndexType m, n;
         Full2Condensed(i, j, half_band_width, m, n);
         Float64 value = GetCoefficient(i, j); // (BW < n ? 0 : ba[m][n]);
         os << value << " ";
      }
      os << "]" << std::endl;
   }
}
