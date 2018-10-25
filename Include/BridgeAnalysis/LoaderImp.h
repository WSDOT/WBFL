///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADERIMP_H_
#define INCLUDED_BRIDGEANALYSIS_LOADERIMP_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\BridgeModelImp.h>
#include <BridgeAnalysis\Loader.h>
#include <BridgeAnalysis\LoadImp.h>


class bamBridgeModelLoader : public bamLoader
{
public:
   bamBridgeModelLoader(bamBridgeModelImp* pModel,bamLoad* pLoad);
   ~bamBridgeModelLoader();

   void RemoveLoad();
   void AddBeam(rkRoarkBeam* pBeam);
   void AddReaction(Float64 P,Int32 supportId);

protected:
   bamBridgeModelImp* GetBridgeModel();
};

///////////////////////////////////////////////////////////////////////

class bamConcForceYLoaderImp : public bamBridgeModelLoader
{
public:
   bamConcForceYLoaderImp(bamBridgeModelImp* pModel,bamConcForceYImp* pLoad);
   ~bamConcForceYLoaderImp() {}

protected:
   void ApplyToSpanElement();
   void ApplyToSupportElement();

private:
   bamConcForceYImp* m_pMyLoad;
};

///////////////////////////////////////////////////////////////////////

class bamUnifForceYLoaderImp : public bamBridgeModelLoader
{
public:
   bamUnifForceYLoaderImp(bamBridgeModelImp* pModel,bamUnifForceYImp* pLoad);
   ~bamUnifForceYLoaderImp() {}

protected:
   void ApplyToSpanElement();
   void ApplyToSupportElement();

private:
   bamUnifForceYImp* m_pMyLoad;
};

///////////////////////////////////////////////////////////////////////

class bamConcMomentZLoaderImp : public bamBridgeModelLoader
{
public:
   bamConcMomentZLoaderImp(bamBridgeModelImp* pModel,bamConcMomentZImp* pLoad);
   ~bamConcMomentZLoaderImp() {}

protected:
   void ApplyToSpanElement();
   void ApplyToSupportElement();

private:
   bamConcMomentZImp* m_pMyLoad;
};

#endif // INCLUDED_BRIDGEANALYSIS_LOADERIMP_H_