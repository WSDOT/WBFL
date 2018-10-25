///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2013  Washington State Department of Transportation
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

///////////////////////////////////////////////////////////////////////
// Revision Log
// ============
// May 1997 - Created, Richard Brice, PE
// Oct 1999 - Released as Open Source

#if !defined FEM2D_RESULT_H_
#define FEM2D_RESULT_H_

#pragma once

#include <map>
#include "FemAll.h"


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

   Result(LoadCaseIDType id,Float64 *force,Float64 *disp):
   m_LoadingID(id)
   {
      SetActions(force, disp);
   }

   void SetActions(Float64 *force,Float64 *disp)
   {
      long i;
      for (i = 0; i < TNForceDof; i++)
      {
         m_Force[i] = force[i];
      }

      for (i = 0; i < TNDispDof; i++)
      {
         m_Disp[i] = disp[i];
      }
   }

   ~Result()
   {
   }

   LoadCaseIDType GetID() const
   {
      return m_LoadingID;
   }

   // Gets are zero-based
   Float64 GetForce(LONG dof) const
   {
      ATLASSERT(dof<TNForceDof); // "Bounds Error"
      return m_Force[dof];
   }

   void SetForce(LONG dof, Float64 force) 
   {
      ATLASSERT(dof<TNForceDof); // "Bounds Error"
      m_Force[dof] = force;
   }

   Float64 GetDisplacement(LONG dof) const
   {
      ATLASSERT(dof<TNDispDof); // "Bounds Error"
      return m_Disp[dof];
   }

   void SetDisplacement(LONG dof, Float64 disp) 
   {
      ATLASSERT(dof<TNDispDof); // "Bounds Error"
      m_Disp[dof] = disp;
   }

   Result& operator= (const Result& rOther)
   {
      if (this!=&rOther)
      {
         m_LoadingID = rOther.m_LoadingID;
         for (LONG i=0; i<TNForceDof; i++)
         {
            m_Force[i] = rOther.m_Force[i];
         }

         for (LONG j=0; j<TNDispDof; j++)
         {
            m_Disp[j] = rOther.m_Disp[j];
         }
      }

      return *this;
   }
private:
   LoadCaseIDType m_LoadingID;
   Float64 m_Force[TNForceDof];
   Float64 m_Disp[TNDispDof];
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
      if (it!=m_ResultVec.end())
         return &(it->second);
      else
      {
         return 0;
      }
   }

   // Add
   // returns pointer to newly added result.
   // NOTE: Be very careful when using this pointer. it can easily be hosed by
   //       subsequent modifications to the container.
   const TResult* Add(const TResult& res)
   {
      ATLASSERT(0==this->Find(res.GetID())); // "Attempt to add result with duplicate ID"
      std::pair<ResultVecIterator, bool> st;
      st = m_ResultVec.insert(ResultVec::value_type(res.GetID(), res) );
      TResult& ref = (st.first->second);
      return &ref;
   }

   // Remove
   // returns number removed
   CollectionIndexType Remove(IDType resultID)
   {
      CollectionIndexType n = m_ResultVec.erase(resultID);
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
   typedef std::map<IDType,TResult> ResultVec;
   typedef typename ResultVec::iterator ResultVecIterator;
   typedef typename ResultVec::const_iterator ConstResultVecIterator;
   ResultVec m_ResultVec;
};


#endif // FEM2D_RESULT_H_
