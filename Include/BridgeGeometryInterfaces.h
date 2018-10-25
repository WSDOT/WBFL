#pragma once

#include <WBFLTools.h>
#include <WBFLGeometry.h>
#include <WBFLCogo.h>
#include <DManip\DManip.h>

// {2DD680A7-7466-4bfe-B2B8-56C9342EA39A}
DEFINE_GUID(IID_IRoadway, 
0x2dd680a7, 0x7466, 0x4bfe, 0xb2, 0xb8, 0x56, 0xc9, 0x34, 0x2e, 0xa3, 0x9a);
interface IRoadway : IUnknown
{
   virtual void GetBearing(IDType alignmentID,Float64 station,IDirection** ppBearing) = 0;
   virtual void GetNormal(IDType alignmentID,Float64 station,IDirection** ppBearing) = 0;
};

// {C9273843-E784-4f2e-945A-FCC295EA8F60}
DEFINE_GUID(IID_IRoadwayData, 
0xc9273843, 0xe784, 0x4f2e, 0x94, 0x5a, 0xfc, 0xc2, 0x95, 0xea, 0x8f, 0x60);
interface IRoadwayData : IUnknown
{
   virtual IndexType GetAlignmentCount() = 0;
   virtual IndexType GetAlignmentIndex(IDType alignmentID) = 0;
   virtual IDType GetAlignmentID(IndexType alignmentIdx) = 0;
   //virtual void SetAlignmentDescription(Int32 alignmentID,const CAlignmentDescription& alignmentDesc) = 0;
   //virtual CAlignmentDescription GetAlignmentDescription(Int32 alignmentID) = 0;
};

// {66FEEE56-1104-47f6-A4D9-EB1FAF5C7EFB}
DEFINE_GUID(IID_IRoadwayDataEvents, 
0x66feee56, 0x1104, 0x47f6, 0xa4, 0xd9, 0xeb, 0x1f, 0xaf, 0x5c, 0x7e, 0xfb);
interface IRoadwayDataEvents : IUnknown
{
   virtual void OnRoadwayDataChanged() = 0;
};

// {781B305A-A57A-4a86-AC36-897F1FDF197A}
DEFINE_GUID(IID_IRoadwayDisplayBuilder, 
0x781b305a, 0xa57a, 0x4a86, 0xac, 0x36, 0x89, 0x7f, 0x1f, 0xdf, 0x19, 0x7a);
interface IRoadwayDisplayBuilder : IUnknown
{
   virtual void BuildRoadwayDisplay(CDisplayView* pView) = 0;
};