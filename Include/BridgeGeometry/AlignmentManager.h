#pragma once
#include <BridgeGeometry\BridgeGeometryExp.h>

#include <BridgeGeometry\AlignmentDescription.h>
#include <map>

class BGCLASS CAlignmentManager
{
public:
   CAlignmentManager(void);
   ~CAlignmentManager(void);

   bool EditAlignment(); // returns true if the alignment was changed

   Uint32 GetAlignmentCount();
   Uint32 GetAlignmentIndex(Int32 alignmentID);
   Int32 GetAlignmentID(Uint32 alignmentIdx);
   void SetAlignmentDescription(Int32 alignmentID,const CAlignmentDescription& alignmentDesc);
   CAlignmentDescription GetAlignmentDescription(Int32 alignmentID);

private:
   typedef std::map<Int32,CAlignmentDescription> AlignmentDescContainer;
   AlignmentDescContainer m_AlignmentDescriptions; // key = alignmentID
};
