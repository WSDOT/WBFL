///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_BRIDGEMODEL_H_
#define INCLUDED_BRIDGEANALYSIS_BRIDGEMODEL_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <boost\shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadFactory.h>
#include <BridgeAnalysis\LiveLoad.h>
#include <BridgeAnalysis\LoadCombination.h>
#include <BridgeAnalysis\AnalysisResultsManager.h>
#include <BridgeAnalysis\LiveLoadSolver.h>
#include <BridgeAnalysis\LoadCase.h>
#include <BridgeAnalysis\SupportElement.h>
#include <BridgeAnalysis\SpanElement.h>
#include <BridgeAnalysis\Reaction.h>
#include <BridgeAnalysis\PointOfInterest.h>
#include <BridgeAnalysis\Envelope.h>
#include <System\NextAvailableId.h>
#include <GraphicsLib\PointMapper.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// The client uses this interface for 99% of the interaction with the
// Subsystem

// classes that are required for the declaration of bamBridgeModel
// but are not to be seen by clients of BAM.
class bamLoader;
class bamLoadCase;
class bamDeadLoadCase;

// MISCELLANEOUS
//

class BAMCLASS bamBridgeModel
{
public:

   // LIFECYCLE
   bamBridgeModel();
   virtual ~bamBridgeModel(); 

   // OPERATORS
   // OPERATIONS


   //------------------------------------------------------------------------
   // Method:      SetAnalysisResultsManager
   // Description: Provides the model with a new AnalysisResultsManager.
   // Return:      Returns a pointer to the old AnalysisResultsManager.
   void SetAnalysisResultsManager(bamAnalysisResultsManager* pAnalysisResultsManager,bool shouldDelete = true);
   bamAnalysisResultsManager* GetAnalysisResultsManager();

   //------------------------------------------------------------------------
   // Method:      SetLiveLoadSolver
   // Description: Provides the model with a new LiveLoadSolver.
   // Return:      Returns a pointer to the old LiveLoadSolver.
   //              You must delete this object if you no longer need it.
   void SetLiveLoadSolver(bamLiveLoadSolver* pSolver,bool shouldDelete = true);
   bamLiveLoadSolver* GetLiveLoadSolver();

   //===== Span Elements =====
   // Method:      CreateSpanElement - Form 1
   // Description: Creates a new span element.  Uses the information
   //              stored in rSpanElementInfo.
   //              Segments are not supported yet, so it is not advised
   //              that you make heavy use of this method.
   // Return:      None
   void CreateSpanElement(const bamSpanElementInfo& rSpanElementInfo);

   // Method:      CreateSpanElement - Form 2
   // Description: Creates a new span element with one segment. The
   //              span element is not connected to support elements.
   // Return:      None
   void CreateSpanElement(Int32 spanElementId,
                          Float64 area,
                          Float64 izz,
                          Float64 e,
                          Float64 density);

   // Method:      ConnectSpanElement
   // Description: Connects a span element to support elements
   // Return:      None
   void ConnectSpanElement(Int32 spanElementId,
                           Int32 startPierId,
                           Int32 endPierId);

   // Method:      RemoveSpanElement
   // Description: Removes a span element from the model
   // Return:      None
   void RemoveSpanElement(Int32 spanElementId);

   // Method:      GetSpanElementCount
   // Description: Returns the number of span elements in the model
   // Return:      Number of span elements in the model.
   Int32 GetSpanElementCount() const;

   // Method:      EnumSpanElements
   // Description: Enumerates up to count span element id's. If count
   //              is zero, all id's are enumerated
   // Return:      None
   void EnumSpanElements(Int32** ppSpanElementId,Int32 count = 0) const;

   // Method:      GetSpanElementInfo
   // Description: Fills out the span element info struct
   // Return:      None
   void GetSpanElementInfo(bamSpanElementInfo& rSpanElementInfo) const;

   //===== Support Elements =====

   // Method:      CreateSupportElement - Form 1
   // Description: Creates a simple support element.
   // Return:      None
   void CreateSupportElement(Int32 supportElementId,
                             Float64 location,
                             bamSupportFixity fixity);

   // Method:      CreateSupportElement - Form 2
   // Description: Creates a simple support element using support element info
   // Return:      None
   void CreateSupportElement(const bamSupportElementInfo& rSupportElementInfo);

   /*
   // Method:      CreateSupportElement - Form 3
   // Description: Creates a frame support element.
   // Return:      None
   void CreateSupportElement(Int32 supportElementId,
                             Float64 location,
                             Float64 height,
                             Float64 baseOffset,
                             SupportFixity fixity,
                             Float64 area,
                             Float64 izz,
                             Float64 e,
                             Float64 density);
   */

   // Method:      RemoveSupportElement
   // Description: Removes a support element from the model
   // Return:      None
   void RemoveSupportElement(Int32 supportElementId);

   // Method:      GetSupportElementCount
   // Description: Returns the number of support elements in the model
   // Return:      Number of support elements
   Int32 GetSupportElementCount() const;

   // Method:      EnumSupportElements
   // Description: Enumerates up to count support element id's. If count
   //              is zero, all id's are enumerated
   // Return:      None
   void EnumSupportElements(Int32** ppSupportElementId,Int32 count = 0) const;
/*
   // Method:      GetSupportElementInfo
   // Description: Fills out the support element info struct
   // Return:      None
   void GetSupportElementInfo(SupportElementInfo& rSupportElementInfo) const;
*/
/*
   //===== General Elements =====

   // Method:      SetEndRelease, GetEndRelease
   // Description: Sets/Gets the element end releases.
   //              Release codes are RELEASE_NONE and RELEASE_MZ.
   //              Future versions can add more release codes that
   //              can be bit-wise or'ed
   void SetEndRelease(Int32 elementId,    // Id of the subject element
                      ElementType type,  // Element type (span,support)
                      Int32 startRelease, // Release code for start of element
                      Int32 endRelease);  // Release code for end of element
   void GetEndRelease(Int32 elementId,
                      ElementType type,
                      Int32& startRelease,
                      Int32& endRelease);

   // Method:      AddHinge
   // Description: Adds an in-span hinge to a support or span element.
   // Return:      None
   void AddHinge(Int32 elementId,ElementType type,Float64 distFromStart);

   // Method:      AddSegment
   // Description: Add a segment to a span or support element
   // Return:      None
   void AddSegment(Int32 elementId,
                   ElementType type,
                   Float64 offset,
                   Float64 area,
                   Float64 iz,
                   Float64 e,
                   Float64 density);
*/

   //===== Loads and Load Cases =====

   // ID's for load cases, load combinations, live loads, and
   // envelopes cannot be duplicates!!!!
   // Loading refers to load cases, load combinations, live loads,
   // and envelopes.

   // Method:      CreateLoadCase
   // Description: Creates a new load case
   // Return:      Loading identifier
   void CreateLoadCase(Int32 id);

   // Method:      CreateDeadLoadCase
   // Description: Creates a new dead load case.  Dead load case
   //              automatically generate self weight loads for
   //              all span and support elements, except for those
   //              provided in the exclude list
   // Return:      Loading identifier
   void CreateDeadLoadCase(Int32 id,
                           bamElementExcludeInfo* pExcludeList = 0, // elements to be excluded
                           Int32 excludeCount = 0); // # of elements in the exclude list

   // Method:      RemoveLoadCase
   // Description: Removes a load case from the model
   // Return:      None
   void RemoveLoadCase(Int32 loadCaseId);

   // Method:      RemoveLoad
   // Description: Removes a load from a load case
   // Return:      None
   void RemoveLoad(Int32 loadCaseId, Int32 loadIdx);

   // Method:      GetLoadCaseCount
   // Description: Returns the number of load cases in the model
   // Return:      Number of load cases
   Int32 GetLoadCaseCount() const;

   // Method:      EnumLoadCases
   // Description: Enumerates up to count load case id's. If count
   //              is zero, all id's are enumerated
   // Return:      None
   void EnumLoadCases(Int32** ppLoadCaseId,Int32 count = 0) const;

   // Method:      GetLoadCount
   // Description: Returns the number of loads in a load case
   // Return:      Number of loads
   Int32 GetLoadCount(Int32 loadCaseId) const;

   // Method:      EnableLoadCase
   // Description: Enables a load case.
   // Return:      None
   void EnableLoadCase(Int32 loadCaseId);

   // Method:      DisableLoadCase
   // Description: Disables a load case. Disabled load cases are
   //              ignored during analysis
   // Return:      None
   void DisableLoadCase(Int32 loadCaseId);

   // Method:      IsLoadCaseEnabled
   // Description: Tests the state of a load case
   // Return:      true if the load case is enabled
   bool IsLoadCaseEnabled(Int32 loadCaseId) const;

   // Method:      GetLoadingCount
   // Description: Returns the count of all loadings, including
   //              load cases, load combinations, and live load envelopes.
   // Return:      Loading count
   Int32 GetLoadingCount() const;

   // Method:      EnumLoadings
   // Description: Enumerates up to count loading id's. If count
   //              is zero, all id's are enumerated
   // Return:      None
   void EnumLoadings(Int32** ppLoadingId,Int32 count = 0) const;

   //===== Envelopes =====

   // Method:      AddEnvelope
   // Description: Adds an envelope to the model
   // Return:      A unique envelope identifier
   void AddEnvelope(const bamEnvelope& rEnvelope);
   void RemoveEnvelope(Int32 id);
   const bamEnvelope* GetEnvelope(Int32 id) const;

   //===== Load Combinations =====

   void AddLoadCombination(const bamLoadCombination& rLoadCombination);
   void RemoveLoadCombination(Int32 id);
   const bamLoadCombination* GetLoadCombination(Int32 id) const;

   //===== Live Load =====

   void AddLiveLoad(const bamLiveLoad& ll);
   void RemoveLiveLoad(Int32 id);
   const bamLiveLoad* GetLiveLoad(Int32 id) const;

   //===== Points Of Interest =====

   // Method:      AddPointOfInterest - Form 1
   // Description: Adds a point of interest using an absolute location.
   // Return:      None
   void AddPointOfInterest(Int32 poi,Float64 absLoc);

   // Method:      AddPointOfInterest - Form 2
   // Description: Adds a point of interest offset from the start
   //              of a span element
   // Return:      None
   void AddPointOfInterest(Int32 poi,Int32 spanElementId,Float64 offset);

   // Method:      GeneratePointsOfInterest
   // Description: Generates points of interest on a span element
   // Return:      None
   void GeneratePointsOfInterest(Int32 startPoi, // Starting poi id
                                 Int32 nPoi,     // Number of poi to generate
                                 Int32 spanElementId, // Span element id
                                 Int32 poiInc = 1); // poi increment

   // Method:      GetPointOfInterest
   // Description: Gets the point of interest description
   // Return:      None
   void GetPointOfInterest(Int32 poi, // point of interest id
                           Int32& spanElementId, // span element id 
                           Float64& offset, // offset from start of span
                           Float64& absLoc // absolute location
                           ) const;

   // Method:      GetPointOfInterestCount
   // Description: Retuns the number of points of interest
   // Return:      Point of interest count
   Int32 GetPointOfInterestCount() const;

   // Method:      EnumPointsOfInterest
   // Description: Enumerates up to count point of interest id's. If count
   //              is zero, all id's are enumerated
   // Return:      None
   void EnumPointsOfInterest(Int32** ppPoi,Int32 count) const;

   const bamPointOfInterest* GetPointOfInterest(Int32 id) const;
   bamPointOfInterest* GetPointOfInterest(Int32 id);

   //===== Stress Points =====

   // Method:      AddStressPoint
   // Description: Attaches a stress point to a point of interest
   // Return:      None
   void AddStressPoint(Int32 poi,Int32 idx,Float64 S);
   void RemoveStressPoint(Int32 poi,Int32 idx);




   // Method:      Analyze
   // Description: Analyzes the bridge model.  If bForce is true, the
   //              model is always analyzed. If the model has previously
   //              been analyzed and has not been since modified, the
   //              analysis is not re-done unless bForce is true.
   // Return:      None
   virtual void Analyze(bool bForce = false);

   bamBridgeModel* Clone() const;

   // ACCESS

   // Method:      GetLoadFactory
   // Description: Returns a reference to the load factory.  The load 
   //              factory is used to create and add loads to the model.
   // Return:      Reference to the load factory
   bamLoadFactory& GetLoadFactory();

   // Method:      Draw
   // Description: Drabam the bridge model
   // Return:      None
   virtual void Draw(HDC hDC,RECT rect,grlibPointMapper::MapMode mapMode) const;

   bamSectionResults ReadSectionResults(const bamSectionResultsKey& key) const;
   bamSectionStress ReadSectionStress(const bamSectionStressKey& key) const;

   // Method:      ReadReactions
   // Description: Extracts the reactions for a particular support element
   // Return:      None
   bamReaction ReadReaction(const bamReactionKey& key) const;

   // INQUIRY

   // Method:      IsAnalyzed
   // Description: Returns true if the model has been previously analyzed
   // Return:      True if previously analyzed
   bool IsAnalyzed() const;

   // Method:      IsModified
   // Description: Returns true if the model has been modified
   // Return:      True if the model has been modified
   bool IsModified() const;

   // Method:      Set/GetGravityDirection
   // Description: Returns the assumed direction of gravity
   // Return:      Assumed direction of gravity
   void SetGravityDirection(bamGravityDirection gravityDir);
   bamGravityDirection GetGravityDirection() const;

   // Method:      Set/GetGravitionalAcceleration
   // Description: Returns the gravitational acceleration used
   //              for computing self weight.
   // Return:      Gravitational acceleration
   void SetGravitionalAcceleration(Float64 gravity);
   Float64 GetGravitionalAcceleration() const;

   Float64 GetBridgeLength() const;
   Float64 GetSpanLength(Int32 spanId) const;

   const bamSpanElement* GetSpanElement(Int32 spanElementId) const;
   const bamSupportElement* GetSupportElement(Int32 supportElementId) const;
   const bamLoadCase* GetLoadCase(Int32 loadCaseId) const;

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void SetAnalyzedFlag(bool flag);
   void SetModifiedFlag(bool flag = true);

   virtual bamBridgeModel* DoClone() const = 0;
   virtual void DeepCopy(bamBridgeModel* pModel) const;

   virtual void DoSetup();
   virtual void DoBuildModel();
   virtual void DoBeginLoadCase(bamLoadCase& lc);
   virtual void DoAnalyze();
   virtual void DoCollectResults(Int32 poiId,bamSectionResults& sr);
   virtual void DoCollectReactions(Int32 supportId,bamReaction& reaction);
   virtual void DoEndLoadCase();
   virtual void DoCleanup();

   virtual bamLoadFactory* CreateLoadFactory() = 0;

   void AbsLocationToRelLocation(Float64 absLoc,Int32& spanIdx,Float64& offset) const;
   void RelLocationToAbsLocation(Int32 spanIdx,Float64 offset,Float64& absLoc) const;

   // ACCESS
   bamSpanElement* GetSpanElement(Int32 spanElementId);
   bamSupportElement* GetSupportElement(Int32 supportElementId);
   bamLoadCase* GetLoadCase(Int32 loadCaseId);
   bamLoadCombination* GetLoadCombination(Int32 id);

   void WriteSectionResults(const bamSectionResultsKey& key,const bamSectionResults& sr);
   void WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& sr);
   void WriteReaction( const bamReactionKey& key,
                       const bamReaction& reaction );
   // INQUIRY

private:
   // DATA MEMBERS
   sysNextAvailableId m_NextAvailableLoadingId;
   sysNextAvailableId m_NextAvailableEnvelopeId;
   sysNextAvailableId m_NextAvailableLiveLoadId;

   bool m_IsModified;
   bool m_IsAnalyzed;
   std::auto_ptr<bamLoadFactory> m_pLoadFactory;
   std::auto_ptr<bamAnalysisResultsManager> m_pAnalysisResultsManager;

   bool m_bShouldDeleteAnalysisResultsManager;
   bool m_bShouldDeleteLiveLoadSolver;

   Float64 m_Gravity;
   bamGravityDirection m_GravityDirection;

   std::auto_ptr<bamLiveLoadSolver>  m_pSolver;

   typedef std::map<Int32, boost::shared_ptr<bamSpanElement> > SpanElementContainer;
   typedef SpanElementContainer::iterator SpanElementIterator;
   typedef SpanElementContainer::const_iterator ConstSpanElementIterator;

   typedef std::map<Int32, boost::shared_ptr<bamSupportElement> > SupportElementContainer;
   typedef SupportElementContainer::iterator SupportElementIterator;
   typedef SupportElementContainer::const_iterator ConstSupportElementIterator;

   typedef std::map<Int32, bamLiveLoad> LiveLoadContainer;
   typedef LiveLoadContainer::iterator LiveLoadIterator;
   typedef LiveLoadContainer::const_iterator ConstLiveLoadIterator;
   
   typedef std::map<Int32, boost::shared_ptr<bamLoadCase> > LoadCaseContainer;
   typedef LoadCaseContainer::iterator LoadCaseIterator;
   typedef LoadCaseContainer::const_iterator ConstLoadCaseIterator;

   typedef std::map<Int32, boost::shared_ptr<bamLoadCombination> > LoadCombinationContainer;
   typedef LoadCombinationContainer::iterator LoadCombinationIterator;
   typedef LoadCombinationContainer::const_iterator ConstLoadCombinationIterator;

   typedef std::map<Int32, boost::shared_ptr<bamEnvelope> > EnvelopeContainer;
   typedef EnvelopeContainer::iterator EnvelopeIterator;
   typedef EnvelopeContainer::const_iterator ConstEnvelopeIterator;

   typedef std::vector<bamPointOfInterest> PoiContainer;
   typedef PoiContainer::iterator PoiIterator;
   typedef PoiContainer::const_iterator ConstPoiIterator;

   // :COMPILER: rab 11.17.96 : Supressed warning
   // :FILE: bamBridgeModel.h
   // Warning C4251 has been suppressed.
   // private data need not be exported.
   #pragma warning (disable : 4251)
   LiveLoadContainer m_LiveLoads;
   LoadCaseContainer m_LoadCases;
   LoadCombinationContainer m_LoadCombinations;
   EnvelopeContainer m_Envelopes;
   SpanElementContainer m_SpanElements;
   SupportElementContainer m_SupportElements;
   PoiContainer m_PointsOfInterest;

   // LIFECYCLE
   bamBridgeModel(const bamBridgeModel& /*bamBridgeModel*/);               // Remove to enable copy

   // OPERATORS
   bamBridgeModel& operator = (const bamBridgeModel& /*bamBridgeModel*/);  // Remove to enable assignment

   // OPERATIONS
   void AddPointOfInterest(Int32 poiId,Int32 spanId,Float64 distFromStart,Float64 absLoc);
   const bamPointOfInterest& StorePointOfInterest(Int32 poi,Int32 spanId,Float64 offset,Float64 absLoc);
   void OnNewPointOfInterest(const bamPointOfInterest& poi);
   void OnNewStressPoint(const bamPointOfInterest& poi,Int32 spid);

   Int32 AddLoad(Int32 loadCaseId,bamLoad* pLoad);
   void StoreSpanElement(bamSpanElement* pSpanElement);
   void StoreSupportElement(bamSupportElement* pSupportElement);
   void StoreLoadCase(bamLoadCase* pLoadCase);
   void StoreLoadCombination(bamLoadCombination* pLoadCombination);
   void StoreLiveLoad(const bamLiveLoad& ll);

   void CollectLoadCaseResults(bamLoadCase& lc);
   void CollectLoadCaseResults( bamLoadCase& rLoadCase, const bamPointOfInterest& poi );
   void LoadCaseStress(bamLoadCase& rLoadCase, const bamSectionResults& sr,const bamPointOfInterest& poi, const bamStressPoint& sp );
   void LoadCaseStress(bamLoadCase& rLoadCase, const bamPointOfInterest& poi, const bamStressPoint& sp );

   void DoLoadCombination(bamLoadCombination& rCombo);
   void DoLoadCombination(bamLoadCombination& rCombo, const bamPointOfInterest& poi);
   void DoLoadCombinationStress(bamLoadCombination& rCombo, const bamPointOfInterest& poi,const bamStressPoint& sp);

   // ACCESS
   // INQUIRY

   friend bamLoader;  // Needs access to span elements
   friend bamLoadFactory; // Needs to call AddLoad
   friend bamLiveLoadSolver; // Needs access to the AnalysisResultsManager
   friend bamDeadLoadCase; // Needs access to span and support elements
   friend bamLoadCombination; // Needs access to WriteResults and WriteReactions
   friend bamEnvelope; // Needs access to WriteResults and WriteReactions

   bool IsValidSpanId(Int32 spanId) const;
   bool IsValidSupportId(Int32 supportId) const;
   bool IsValidLoadCaseId(Int32 id) const;
   bool IsValidLoadCombinationId(Int32 id) const;
   bool IsValidLiveLoadId(Int32 id) const;
   bool IsValidEnvelopeId(Int32 id) const;
   bool IsLoadingIdUsed(Int32 id) const;

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

// INLINE METHODS
//
inline void bamBridgeModel::DoBuildModel()     {}
inline void bamBridgeModel::DoBeginLoadCase(bamLoadCase& /*lc*/)  {}
inline void bamBridgeModel::DoAnalyze()        {}
inline void bamBridgeModel::DoCollectResults(Int32 poiId,bamSectionResults&) {}
inline void bamBridgeModel::DoCollectReactions(Int32 supportId,bamReaction&) {}
inline void bamBridgeModel::DoEndLoadCase()    {}

// Keeps STL happy
inline bool operator < (const bamPointOfInterest& a,const bamPointOfInterest& b)
{ return false; }
inline bool operator == (const bamPointOfInterest& a,const bamPointOfInterest& b)
{ return false; }

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_BRIDGEMODEL_H_
