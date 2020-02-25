///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef __iComputeInfluenceLineStrategy_H_
#define __iComputeInfluenceLineStrategy_H_


// polymorphic strategy class for computing influence lines for different effects

class iComputeInfluenceLineStrategy
{
public:
   virtual void GetInfluenceLineResponse(IInfluenceLineResponse** ppResponse) = 0;

   virtual HRESULT ComputeInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType effect, 
                                        IInfluenceLine* *lftInflLine, IInfluenceLine* *rgtInflLine) = 0;

   // returns -1.0 if sign convention flips results for left/right faces, 1.0 if not
   virtual Float64 SignFlip() = 0;
};

// strategy for force results
class ForceInfluenceLineStrategy : public iComputeInfluenceLineStrategy
{
public:
   ForceInfluenceLineStrategy(IInfluenceLineResponse* response, ResultsOrientation or):
   m_Response(response),
   m_Orientation(or)
   {
      ATLASSERT(response!=nullptr);
   }

   virtual HRESULT ComputeInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType effect, 
                                        IInfluenceLine* *lftInflLine, IInfluenceLine* *rgtInflLine)
   {
      return m_Response->ComputeForceInfluenceLine(poiID, stage, effect, m_Orientation, lftInflLine, rgtInflLine);

   }

   virtual Float64 SignFlip()
   {
      return -1.0;
   }

   void GetInfluenceLineResponse(IInfluenceLineResponse** ppResponse)
   {
      *ppResponse = m_Response;
      (*ppResponse)->AddRef();
   }

private:
   IInfluenceLineResponse* m_Response;
   ResultsOrientation      m_Orientation;
};


// strategy for Deflection results
class DeflectionInfluenceLineStrategy : public iComputeInfluenceLineStrategy
{
public:
   DeflectionInfluenceLineStrategy(IInfluenceLineResponse* response):
   m_Response(response)
   {
      ATLASSERT(response!=nullptr);
   }

   virtual HRESULT ComputeInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType effect, 
                                        IInfluenceLine* *lftInflLine, IInfluenceLine* *rgtInflLine)
   {
      return m_Response->ComputeDeflectionInfluenceLine(poiID, stage, effect, lftInflLine, rgtInflLine);
   }

   virtual Float64 SignFlip()
   {
      return 1.0;
   }

   void GetInfluenceLineResponse(IInfluenceLineResponse** ppResponse)
   {
      *ppResponse = m_Response;
      (*ppResponse)->AddRef();
   }

private:
   IInfluenceLineResponse* m_Response;
};

// strategy for Reaction results
class ReactionInfluenceLineStrategy : public iComputeInfluenceLineStrategy
{
public:
   ReactionInfluenceLineStrategy(IInfluenceLineResponse* response):
   m_Response(response)
   {
      ATLASSERT(response!=nullptr);
   }

   virtual HRESULT ComputeInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType effect, 
                                        IInfluenceLine* *lftInflLine, IInfluenceLine* *rgtInflLine)
   {
      // no left/right for reactions
      *rgtInflLine = nullptr;
      return m_Response->ComputeReactionInfluenceLine(poiID, stage, effect, lftInflLine);
   }

   virtual Float64 SignFlip()
   {
      return 1.0;
   }

   void GetInfluenceLineResponse(IInfluenceLineResponse** ppResponse)
   {
      *ppResponse = m_Response;
      (*ppResponse)->AddRef();
   }

private:
   IInfluenceLineResponse* m_Response;
};

// strategy for Support Deflection results
class SupportDeflectionInfluenceLineStrategy : public iComputeInfluenceLineStrategy
{
public:
   SupportDeflectionInfluenceLineStrategy(IInfluenceLineResponse* response):
   m_Response(response)
   {
      ATLASSERT(response!=nullptr);
   }

   virtual HRESULT ComputeInfluenceLine(PoiIDType poiID, BSTR stage, ForceEffectType effect, 
                                        IInfluenceLine* *lftInflLine, IInfluenceLine* *rgtInflLine)
   {
      // no left/right for support defl's
      *rgtInflLine = nullptr;
      return m_Response->ComputeSupportDeflectionInfluenceLine(poiID, stage, effect, lftInflLine);
   }

   virtual Float64 SignFlip()
   {
      return 1.0;
   }

   void GetInfluenceLineResponse(IInfluenceLineResponse** ppResponse)
   {
      *ppResponse = m_Response;
      (*ppResponse)->AddRef();
   }

private:
   IInfluenceLineResponse* m_Response;
};




#endif