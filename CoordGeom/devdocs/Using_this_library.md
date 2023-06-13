# Using this library{#WBFL_COGO_Using_this_library}

The WBFL COGO library has three functional areas: Coordinate Geometry Modeling, Roadway Geometrics and Bridge Framing Geometry. Each will be explained with brief examples below.

First, there are some general concepts that are applicable to the entire library.

## General Concepts
The following topics discuss general concepts used throughout this library.

@subpage WBFL_COGO_Angles_Directions_Stations

@subpage WBFL_COGO_Offsets

@subpage WBFL_COGO_Units

@subpage WBFL_COGO_Value_Semantics_for_Points


## Coordinate Geometry Modeling
Coordinate geometry modeling (commonly referred to as COGO) is used to perform geometric calculations in a planar coordinate space. Additionally, geometric elements can be stored in a model and later used to perform additional calculations and define complex entities such as alignments, paths, profiles, and surfaces.

This basic example illustrates how to create a COGO model.

~~~
WBFL::COGO::Model model;
model.StorePoint(0,0.0,0.0); // store a point with ID 0 at coordinate (0,0)
model.StorePoint(1,10,0); // store a point with ID 1 at coordinate (10,0)

// Locate a new point 20 ft from point 1 using a backsight angle of 45 degrees
model.LocatePoint(2,0,1,20,ToRadian(45.0),0.0);

auto p2 = model.GetPoint(2);
std::cout << p2.X() << ", " << p2.Y();
~~~

Geometric computations can be performed without a `Model` object using the `Utilities` object. 

~~~
using namespace WBFL::Geometry;
using namespace WBFL::COGO;

Point2d p0(0,0);
Point2d p1(10,0);

Angle angle(ToRadian(45.0));
auto p2 = COGO::LocateByDistanceAndAngle(p0,p1,20.0,angle,0.0);
std::cout << p2.X() << ", " << p2.Y();
~~~

## Roadway Geometry Modeling
The roadway geometry modeling capabilities of this library complement the COGO modeling. A roadway consists of an `Alignment`. Optionally, one or more `Profile` objects can be assigned to the `Alignment` representing the vertical profile of the roadway or other related object such as a buried pipeline. `Profile` objects can have  associated `Surface` objects. The `Surface` object can be used to model a roadway surface (or other related surface like existing ground, a roadway subgrade surface, and others).

### Defining an Alignment
An alignment is defined by a sequence of `PathElement` objects such as `PathSegment` and `CircularCurve`. The `PathElement` objects do not need to be connected end to end. The alignment will fill in any gaps with `PathSegment` objects to form a continuous alignment path.

#### Creating an alignment in a COGO model
This example shows how to create an alignment in a COGO model. 
~~~
WBFL::COGO::Model model;
model.StorePoint(0,0,0); // Point on back tangent
model.StorePoint(1,1000,0); // PI
model.StorePoint(2,0,1000) // Point on forward tangent

IDType curveID = 0;
model.StoreCircularCurve(curveID,0,1,2,500.0); // Store the definition of a 500' radius circular curve

IDType alignmentID = 999;
model.StoreAlignment(alignment); // creates a new alignment
model.AppendElementToAlignment(alignmentID,PathElementType::CircularCurve,curveID); // add the circular curve to the alignment

model.SetAlignmentReferenceStation(aligmentID,"0+00"); // station 0+00 at the start of the alignment

auto alignment = model.CreateAlignment(alignmentID);
~~~

#### Creating an alignment 
This example shows how to explicitly create an alignment.
~~~
auto alignment = Alignment::Create();
WBFL::Geometry::Point2d pbt(0,0);
WBFL::Geometry::Point2d pi(1000,0);
WBFL::Geometry::Point2d pft(0,1000);
auto circular_curve = CircularCurve::Create(pbt,pi,pft,500.0);
alignment->AddPathElement(circular_curve);
alignment->SetRefenceStation(0.00); // station 0+00 at start of the alignment
~~~

### Defining a Profile
A profile is defined by a sequence of `ProfileElement` objects such as `ProfileSegment` and `VerticalCurve`. The `ProfileElement` objects do no need to be connected end to end. The profile will fill in any gaps with `ProfileSegment` objects to form a continuous profile.

#### Creating a profile in a COGO model
This example shows how to create a profile in a COGO model. It builds on the COGO model example above for the alignment.
~~~
model.StoreProfilePoint(0,"1+00",500.0);
model.StoreProfilePoint(1,"2+00",600.0);
IDType segmentID = 0;
model.StoreProfileSegment(segmentID,0,1);

IDType profileID = 888;
model.StoreProfile(profileID);
model.AppendProfileElement(profileID,ProfileElementType::Segment,segmentID);

// Associate the profile with the alignment
model.AttachProfileToAlignment(profileID,alignmentID);

// Creating the alignment creates the associated profile
alignment = model.CreateAlignment(alignmentID);
~~~

#### Creating a profile
This example shows how to explicitly create a profile. It builds on the example above.
~~~
auto profile = Profile::Create();
auto segment = ProfileSegment::Create(ProfilePoint(100,500),ProfilePoint(200,600));
profile->AddProfileElement(segment);

// Associate the profile with the alignment
IDType profileID = 888;
alignment->AddProfile(profileID,profile);
~~~

### Defining a Surface
A surface is defined with a sequence of `SurfaceTemplate` objects. The surface is linearlly interpolated between each `SurfaceTemplate`.

#### Creating a surface in a COGO model
This example shows how to create a surface in a COGO model. It builds on the COGO model examples above for the alignment and profile.
~~~
IDType surfaceID = 0;
// create a surface with two segments per surface template. The alignment and profile
// are coincident on ridge point index 1
model.StoreSurface(0,2,1,1);

// Associate the surface with the profile
model.AttachSurfaceToProfile(surfaceID,profileID);

// define the surface with two templates with a 2% crown at Station 0+00 and
// a 6% cross slope at 5+00
model.AddSurfaceTemplate(surfaceID,0.00);
model.AddSurfaceTemplate(surfaceID,500.0);

model.UpdateSurfaceTemplateSegment(surufaceID,0,0,20.0,0.02,SurfaceTemplateSegment::SlopeType::Horizontal);
model.UpdateSurfaceTemplateSegment(surufaceID,0,1,20.0,-0.02,SurfaceTemplateSegment::SlopeType::Horizontal);

model.UpdateSurfaceTemplateSegment(surufaceID,1,0,20.0,0.06,SurfaceTemplateSegment::SlopeType::Horizontal);
model.UpdateSurfaceTemplateSegment(surufaceID,1,1,20.0,0.06,SurfaceTemplateSegment::SlopeType::Horizontal);
~~~

#### Creating a surface
This example shows how to explicitly create a surface. It builds on the examples above for the alignment and profile.
~~~
// create a surface with two segments per surface template. The alignment and profile
// are coincident on ridge point index 1
auto surface = Surface::Create(2,1,1);

// Associate the surface with the profile
IDType surfaceID = 0;
profile->AddSurface(surfaceID,surface);

// define the surface with two templates with a 2% crown at Station 0+00 and
// a 6% cross slope at 5+00
auto template1 = surface->CreateSurfaceTemplate(0.00); // create a template at 0+00
auto template2 = surface->CreateSurfaceTemplate(500.0); // create a template at 5+00

template1->UpdateSegmentParameters(0,20.0,0.02,SurfaceTemplateSegment::SlopeType::Horizontal);
template1->UpdateSegmentParameters(1,20.0,-0.02,SurfaceTemplateSegment::SlopeType::Horizontal);

template2->UpdateSegmentParameters(0,20.0,0.06,SurfaceTemplateSegment::SlopeType::Horizontal);
template2->UpdateSegmentParameters(1,20.0,0.06,SurfaceTemplateSegment::SlopeType::Horizontal);
~~~

## Bridge Framing Geometry
The bridge framing geometry features are used to layout the plan view framing of a bridge model. The bridge framing model consists of pier lines, girder lines, and a deck boundary. A pier line defines the location of a pier along an alignment, the centerline of the pier, and geometric properties defining the location of bearings and the end geometry of beams framing into the pier. Girder lines define the centerline of a girder. The deck boundary defines the transverse edges the ends of the deck) and the side edges of a deck.

The girder lines and deck boundary lines can be defined using layout lines. 

Pier lines, layout lines, girder lines, diaphragm lines, and deck boundaries are created using factory objects. 

The following example creates a framing model for three span bridge.

~~~
   // Create an alignment
   auto alignment = Alignment::Create();
   Float64 segment_length = 100000;
   auto path_segment = PathSegment::Create(WBFL::Geometry::Point2d(0, 0), WBFL::Geometry::Size2d(segment_length, 0.0));
   alignment->AddPathElement(path_segment);
   alignment->SetReferenceStation(0.0);
   
   IDType alignmentID = 999;
   
   // Create a bridge geometry object
   auto framing = BridgeFramingGeometry::Create(alignmentID,alignment);
   
   // Create a factory for the pier lines
   for(int i = 0; i < 4; i++)
   {
      ConnectionGeometry back, ahead; // default values are used for this example
	  Float64 station = i*100;
	  IDType id = (IDType)(i);
	  
	  // factory that creates a single pier line
	  auto pier_line_factory = std::make_shared<SinglePierLineFactory>(id,alignmentID,station,_T("Normal"),pier_length, -pier_length/2, back, ahead);
	  framing->AddPierLineFactory(pier_line_factory);
   }
   
   // create a layout line to aid in defining the girder lines
   // layout line is parallel to and offset from the alignment
   auto layout_line_factory = std::make_shared<AlignmentOffsetLayoutLineFactory>();
   layout_line_factory->SetAlignmentID(alignmentID);
   layout_line_factory->SetLayoutLineID(100);
   layout_line_factory->SetLayoutLineIDIncrement(1);
   layout_line_factory->SetLayoutLineCount(5); // create 5 layout lines
   layout_line_factory->SetOffset(-10.0); // offset from alignment (10 ft left)
   layout_line_factory->SetOffsetIncrement(5.0); // each subsequent layout line is 5 ft to the right of the previous
   framing->AddLayoutLineFactory(layout_line_factory);

   // Create girder lines
   auto girder_line_factory = std::make_shared<SimpleGirderLineFactory>();
   girder_line_factory->SetGirderLineID(500); // left most girder line has ID 500
   girder_line_factory->SetGirderLineIDIncrement(1); // girder line ID increments by 1
   girder_line_factory->SetLayoutLineID(SideType::Left, 100); // layout line used to locate the left girder line
   girder_line_factory->SetLayoutLineID(SideType::Right, 104); // layout line used to location the right girder line
   girder_line_factory->SetLayoutLineIDIncrement(1);
   girder_line_factory->SetGirderLineType(GirderLineType::Chord); // layout as a chord
   girder_line_factory->SetPierID(EndType::Start, 0); // layout girders between pier line ID = 0 and ...
   girder_line_factory->SetPierID(EndType::End, 4); // ... pier line ID = 4
   girder_line_factory->SetPierIDIncrement(1);
   girder_line_factory->IsContinuous(false); // girder lines not continuous so 5 girder lines are created in each span
   framing->AddGirderLineFactory(girder_line_factory);
   
   auto nGirderLines = framing->GetGirderLineCount(); // should be 15
~~~

## Additional Examples
Additional examples can be found in the WBFL\\Examples\\VC\\COGO folder. The *Sunshine_Subdivision* example illustrates a method of modeling the geometry of a parcel of land and is based on the first example in the ICES COGO manual. The *Offset_Profile_Grade* example illustrates a roadway geometry example where the profile grade line is offset from the alignment. Superelevation modifications are applied to the roadway surface with pivot points at the left and right curb lines as well as at the profile grade line.