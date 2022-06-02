///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOAD_H_
#define INCLUDED_BRIDGEANALYSIS_LOAD_H_
#pragma once

#include <BridgeAnalysis\BridgeAnalysisExp.h>


// Forward Declarations
class bamLoadCase;
class bamLoader;
class bamSpanElement;

class bamLoad
{
public:
   bamLoad(IDType elementId,bamElementType type,bamLoadDirection direction);
   virtual ~bamLoad();

   virtual void Apply();
   virtual void Remove();

   bamLoadCase& GetLoadCase();
   bamLoadDirection GetDirection();

   IDType   GetElementId() const;
   bamElementType GetElementType() const;


   // The remaining portion of the interface if for the
   // Bridge Modeling Framework only. Do not call these functions
   // directly!!!

   void SetLoadCase(bamLoadCase* lc);

   bool operator==(const bamLoad& other) const;

protected:
   IDType m_ElementId;
   bamElementType m_ElementType;

   bamLoadDirection m_Direction;
   virtual bamLoader* CreateLoader() = 0;

   virtual bool IsEqual(const bamLoad& other) const;

private:
   std::auto_ptr<bamLoader> m_pLoader;
   bamLoader& GetLoader();

   bamLoadCase* m_LoadCase;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class bamConcForceY : public bamLoad
{
public:
   bamConcForceY(IDType elementId,
                bamElementType type,
                Float64 location,
                Float64 p,
                bool isFractional = false,
                bamLoadDirection direction = Local);
   virtual ~bamConcForceY();

   Float64 GetLocation();
   Float64 GetMagnitude();
   bool IsFractional();

protected:
   Float64 m_Location;
   Float64 m_Magnitude;
   bool m_IsFractional;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class bamUnifForceY : public bamLoad
{
public:
   bamUnifForceY(IDType elementId,
                bamElementType type,
                Float64 start,
                Float64 end,
                Float64 w,
                bool isFractional = false,
                bamLoadDirection direction = Local);
   virtual ~bamUnifForceY();

   Float64 GetStartLocation();
   Float64 GetEndLocation();
   Float64 GetMagnitude();
   bool IsFractional();

protected:
   Float64 m_StartLocation;
   Float64 m_EndLocation;
   Float64 m_Magnitude;
   bool m_IsFractional;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

class bamConcMomentZ : public bamLoad
{
public:
   bamConcMomentZ(IDType elementId,
                  bamElementType type,
                  Float64 location,
                  Float64 p,
                  bool isFractional = false);
   virtual ~bamConcMomentZ();

   Float64 GetLocation();
   Float64 GetMagnitude();
   bool IsFractional();

protected:
   Float64 m_Location;
   Float64 m_Magnitude;
   bool m_IsFractional;

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

#endif // INCLUDED_BRIDGEANALYSIS_LOAD_H_