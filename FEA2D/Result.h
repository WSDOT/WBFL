///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Ported near-verbatim from Fem2d\RESULT.H - internal implementation
// detail (result-cache storage for Joint/Member/POI), not part of the
// public FEA2D API. Only changes from the original: ATLASSERT -> CHECK,
// FemAll.h -> WBFLTypes.h, the WBFL::FEA2D::Internals namespace, and
// std::array (rather than a C array) for m_Force/m_Disp - same layout and
// performance, but supports direct assignment (operator= is now just
// = default instead of a hand-written loop) and zero-initializes instead
// of leaving values garbage before the first SetActions()/Set() call.
// The constructor/SetActions()/Set() parameters stay raw pointers rather
// than std::array/std::span, since Joint::GetReactions()/GetDeflection()
// (their only real callers) are themselves Float64* - changing that is a
// separate, larger change to FEA2D's public API.

#pragma once

#include <algorithm>
#include <array>
#include <map>
#include <WBFLTypes.h>
#include <System\Checks.h>

namespace WBFL
{
   namespace FEA2D
   {
      namespace Internals
      {
         // Manages results for a model component.
         // Three degrees of freedom
         template <LONG TNForceDof, LONG TNDispDof>
         class Result
         {
         public:

            Result(LoadCaseIDType id):
            m_LoadingID(id)
            {
            }

            Result(LoadCaseIDType id,const Float64 *force,const Float64 *disp):
            m_LoadingID(id)
            {
               SetActions(force, disp);
            }

            void SetActions(const Float64 *force,const Float64 *disp)
            {
               std::copy_n(force, TNForceDof, m_Force.begin());
               std::copy_n(disp, TNDispDof, m_Disp.begin());
            }

            void Set(LoadCaseIDType lcid, const Float64 *force,const Float64 *disp)
            {
               m_LoadingID = lcid;
               SetActions(force, disp);
            }

            ~Result() = default;

            LoadCaseIDType GetID() const
            {
               return m_LoadingID;
            }

            // Gets are zero-based
            Float64 GetForce(LONG dof) const
            {
               CHECK(dof<TNForceDof); // "Bounds Error"
               return m_Force[dof];
            }

            void SetForce(LONG dof, Float64 force)
            {
               CHECK(dof<TNForceDof); // "Bounds Error"
               m_Force[dof] = force;
            }

            Float64 GetDeflection(LONG dof) const
            {
               CHECK(dof<TNDispDof); // "Bounds Error"
               return m_Disp[dof];
            }

            void SetDeflection(LONG dof, Float64 disp)
            {
               CHECK(dof<TNDispDof); // "Bounds Error"
               m_Disp[dof] = disp;
            }

            Result& operator= (const Result& rOther) = default;
         private:
            LoadCaseIDType m_LoadingID;
            std::array<Float64, TNForceDof> m_Force{};
            std::array<Float64, TNDispDof> m_Disp{};
         };

         template<class TResult>
         class ResultArray
         {
         public:
            ResultArray(IDType id) : m_ID(id) {;}

            IDType GetID() const { return m_ID; };

            TResult* Find( IDType resultId)
            {
               ResultVecIterator it( m_ResultVec.find(resultId) );
               if (it != m_ResultVec.end())
               {
                  return &(it->second);
               }
               else
               {
                  return nullptr;
               }
            }

            // Add
            // returns pointer to newly added result.
            // m_ResultVec is a std::map, so this pointer (like the one Find()
            // returns) stays valid across insertion/erasure of *other* keys -
            // only erasing this specific result's ID, or destroying the
            // ResultArray itself, invalidates it. Every call site in this
            // codebase already only holds it briefly within one function, so
            // this is exactly as safe as using std::map::find() directly.
            const TResult* Add(const TResult& res)
            {
               CHECK(0==this->Find(res.GetID())); // "Attempt to add result with duplicate ID"
               std::pair<ResultVecIterator, bool> st;
               st = m_ResultVec.insert(ResultVec::value_type(res.GetID(), res) );
               TResult& ref = (st.first->second);
               return &ref;
            }

            // Remove
            // returns number removed
            IndexType Remove(IDType resultID)
            {
               IndexType n = m_ResultVec.erase(resultID);
               return n;
            }

            const TResult* operator [] (IDType id) const // indexed by load case id!!
            {
               return this->Find(id);
            }

            bool operator == (const ResultArray &array) const { return (m_ID == array.m_ID); };
         private:
            ResultArray();
            IDType m_ID; // jnt, mbr, or poi id.
            using ResultVec = std::map<IDType, TResult>;
            using ResultVecIterator = typename ResultVec::iterator;
            using ConstResultVecIterator = typename ResultVec::const_iterator;
            ResultVec m_ResultVec;
         };
      };
   };
};
