# Using this library {#WBFL_FEA2D_Using_this_library}

## Object creation

`WBFL::FEA2D::Model` is the only object you construct directly. Every joint, member, loading, and POI is created *through* the `Model` (or through a `Loading` it owns) via a `Create...` factory method, and is owned for its entire lifetime by the object that created it. It doesn't make sense to have a `Member` or a `Loading` that doesn't belong to a `Model`, so the API doesn't let you create one.

## A basic model

This example builds a simple two-span beam, applies a point load, and reads back a deflection and a member force.

~~~
#include <FEA2D\Model.h>

using namespace WBFL::FEA2D;

Model model;

// Joints: ID, X, Y
model.CreateJoint(1, 0.0, 0.0);
model.CreateJoint(2, 20.0, 0.0);
model.CreateJoint(3, 40.0, 0.0);

// Supports
model.FindJoint(1)->Support();
model.FindJoint(2)->Support();
model.FindJoint(3)->Support();

// Members: ID, start joint, end joint, EA, EI
model.CreateMember(1, 1, 2, 1e9, 1e7);
model.CreateMember(2, 2, 3, 1e9, 1e7);

// A point of interest at midspan of member 1 - cheaper to query than adding a joint there
model.CreatePOI(1, 1, 0.5);

// A loading with a point load applied to member 1
Loading& loading = model.CreateLoading(1);
loading.CreatePointLoad(1, /*memberID*/ 1, /*location*/ 0.5, /*Fx*/ 0.0, /*Fy*/ -10.0, /*Mz*/ 0.0);

// Ask for results - there is no explicit "Analyze" step
Float64 dx, dy, rz;
model.ComputePOIDeflections(/*loadCase*/ 1, /*poiID*/ 1, LoadOrientation::Global, &dx, &dy, &rz);

Float64 startFx, startFy, startMz, endFx, endFy, endMz;
model.ComputeMemberForces(1, /*memberID*/ 1, LoadOrientation::Member, &startFx, &startFy, &startMz, &endFx, &endFy, &endMz);
~~~

## Releases

Member end releases and joint degree-of-freedom releases both use bit-flag enums, so you can combine them:

~~~
Member* pMember = model.FindMember(1);
pMember->ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz); // pinned at the start

Joint* pJoint = model.FindJoint(2);
pJoint->Support();
pJoint->ReleaseDof(JointReleaseType::Mz); // a roller that also permits rotation
~~~

## Persistence

A `Model` saves and loads through the native `WBFL::System::IStructuredSave`/`IStructuredLoad` interfaces - no COM involved:

~~~
#include <System\FileStream.h>
#include <System\StructuredSaveXml.h>
#include <System\StructuredLoadXml.h>

{
   WBFL::System::FileStream file;
   file.open(L"model.xml", /*read*/ false);
   WBFL::System::StructuredSaveXml save;
   save.BeginSave(&file);
   model.Save(&save);
   save.EndSave();
}

model.Clear();

{
   WBFL::System::FileStream file;
   file.open(L"model.xml", /*read*/ true);
   WBFL::System::StructuredLoadXml load;
   load.BeginLoad(&file);
   model.Load(&load);
   load.EndLoad();
}
~~~

## Additional examples

`WBFL::Examples::VC::FemView` (`WBFL\Examples\VC\FemView`) is a small MFC viewer application that builds and displays a `WBFL::FEA2D::Model` graphically, including editing joints/members/loadings interactively - useful as a fuller worked example of the API than the snippets above. The `FEA2DUnitTests` project (`WBFL\FEA2D\FEA2DUnitTests`) is also a good source of small, focused examples: each test builds a specific model configuration and checks its results against hand-verified or textbook values.
