#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPCIDeckedIBeam)
	{
	public:
		
		PCIDeckedIBeam GetTestBeam()
		{
			PCIDeckedIBeam beam;

			// Use some real dimensions
			beam.SetW1(26);
			beam.SetW2(45.5);
			beam.SetW3(7.5);
			beam.SetW4(1);
			beam.SetW5(5.5);
			beam.SetW6(38.375);
			beam.SetD1(8);
			beam.SetD2(1);
			beam.SetD3(0.5);
			beam.SetD4(0.5);
			beam.SetD5(1);
			beam.SetD6(9);
			beam.SetD7(3);
			beam.SetD8(10);
			beam.SetD9(3.75);
			beam.SetH(54);
			beam.SetT(4);
			beam.SetR1(9);
			beam.SetR2(12);
			beam.SetR3(2);
			beam.SetC1(1.0);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -58.5));
			Assert::IsTrue(IsEqual(box.Right(), 58.5));
			Assert::IsTrue(IsEqual(box.Top(), 54.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			Assert::IsTrue(IsEqual(props.GetArea(), 941.66528114402706));
			Assert::IsTrue(IsEqual(props.GetIxx(), 420903.30302683858));
			Assert::IsTrue(IsEqual(props.GetIyy(), 403184.22410364990));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0, 0.0005));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 32.324778419863591));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 58.5));
			Assert::IsTrue(IsEqual(props.GetXright(), 58.5));
			Assert::IsTrue(IsEqual(props.GetYtop(), 54.0 - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 403.95659655723534));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 54.));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(0), 106.));
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeWidth(0), 38.375));
			Assert::IsTrue(IsEqual(beam.GetAvgWebWidth(), 4.));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();

			// Shape on right
			Point2d p1(0, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

			// shape on left
			p1.Move(0, -20);
			p2.Move(100, -20);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 151);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.187500000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, 2.3491454707782506));
			Assert::IsTrue(points[i++] == Point2d(-19.183767796630057, 2.4712719795213163));
			Assert::IsTrue(points[i++] == Point2d(-19.172585115862230, 2.5929426872968921));
			Assert::IsTrue(points[i++] == Point2d(-19.153993693735359, 2.7137034942793949));
			Assert::IsTrue(points[i++] == Point2d(-19.128062917217761, 2.8331036965780481));
			Assert::IsTrue(points[i++] == Point2d(-19.094889565240940, 2.9506976683554598));
			Assert::IsTrue(points[i++] == Point2d(-19.054597447500939, 3.0660465249938786));
			Assert::IsTrue(points[i++] == Point2d(-19.007336942375364, 3.1787197611018394));
			Assert::IsTrue(points[i++] == Point2d(-18.953284435680711, 3.2882968572478388));
			Assert::IsTrue(points[i++] == Point2d(-18.892641662364621, 3.3943688494243704));
			Assert::IsTrue(points[i++] == Point2d(-18.825634953590029, 3.4965398553847775));
			Assert::IsTrue(points[i++] == Point2d(-18.752514392021229, 3.5944285521563053));
			Assert::IsTrue(points[i++] == Point2d(-18.673552878464520, 3.6876695992149822));
			Assert::IsTrue(points[i++] == Point2d(-18.589045113346895, 3.7759150020107608));
			Assert::IsTrue(points[i++] == Point2d(-18.499306496834112, 3.8588354107539438));
			Assert::IsTrue(points[i++] == Point2d(-18.404671951693135, 3.9361213496155827));
			Assert::IsTrue(points[i++] == Point2d(-18.305494673292252, 4.0074843717542095));
			Assert::IsTrue(points[i++] == Point2d(-18.202144811404128, 4.0726581358581102));
			Assert::IsTrue(points[i++] == Point2d(-18.095008088731589, 4.1313994001852627));
			Assert::IsTrue(points[i++] == Point2d(-17.984484361312038, 4.1834889303909915));
			Assert::IsTrue(points[i++] == Point2d(-17.870986126173410, 4.2287323177551244));
			Assert::IsTrue(points[i++] == Point2d(-9.8990832429595521, 7.1276060934692520));
			Assert::IsTrue(points[i++] == Point2d(-9.2180938321277708, 7.3990664176540477));
			Assert::IsTrue(points[i++] == Point2d(-8.5549514676104650, 7.7116035988884200));
			Assert::IsTrue(points[i++] == Point2d(-7.9121311315752365, 8.0640511848513370));
			Assert::IsTrue(points[i++] == Point2d(-7.2920319602465025, 8.4550937694747361));
			Assert::IsTrue(points[i++] == Point2d(-6.6969682898411946, 8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(-6.1291610189953278, 9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(-5.5907293199186316, 9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(-5.0836827292128834, 10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(-4.6099136478726308, 10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(-4.1711902784598287, 11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(-3.7691500258122659, 12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(-3.4052933859157282, 12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(-3.0809783457478215, 13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(-2.7974153149943675, 14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(-2.5556626085543499, 14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(-2.3566224966934257, 15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(-2.2010378375878421, 16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(-2.0894893048266212, 16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(-2.0223932202196480, 17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(-2.0271438002832998, 36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(-2.1084114709345680, 37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(-2.2433128089712202, 38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(-2.4310340955093395, 38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(-2.6704430040798801, 39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(-2.9600954307716645, 40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(-3.2982442050020992, 40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(-3.6828496283725691, 41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(-4.1115917780386653, 41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(-4.5818845003818183, 42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(-5.0908910105731424, 42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(-5.6355410039336338, 43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(-6.2125491758757176, 43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(-6.8184350387147230, 44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(-7.4495439158161219, 44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(-8.1020689864427879, 44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(-8.7720742483287388, 44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(-9.4555182594701073, 45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(-10.148278515923954, 45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(-10.846176318569077, 45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-51.000000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000000, 47.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 47.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 47.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(58.500000000000000, 47.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(58.500000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(51.000000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.846176318569077, 45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(10.148278515923954, 45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(9.4555182594701073, 45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(8.7720742483287388, 44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(8.1020689864427879, 44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(7.4495439158161219, 44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(6.8184350387147230, 44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(6.2125491758757176, 43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(5.6355410039336338, 43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(5.0908910105731424, 42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(4.5818845003818183, 42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(4.1115917780386653, 41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(3.6828496283725691, 41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(3.2982442050020992, 40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(2.9600954307716645, 40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(2.6704430040798801, 39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(2.4310340955093395, 38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(2.2433128089712202, 38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(2.1084114709345680, 37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(2.0271438002832998, 36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(2.0223932202196480, 17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(2.0894893048266212, 16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(2.2010378375878421, 16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(2.3566224966934257, 15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(2.5556626085543499, 14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(2.7974153149943675, 14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(3.0809783457478215, 13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(3.4052933859157282, 12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(3.7691500258122659, 12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(4.1711902784598287, 11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(4.6099136478726308, 10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(5.0836827292128834, 10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(5.5907293199186316, 9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(6.1291610189953278, 9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(6.6969682898411946, 8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(7.2920319602465025, 8.4550937694747361));
			Assert::IsTrue(points[i++] == Point2d(7.9121311315752365, 8.0640511848513370));
			Assert::IsTrue(points[i++] == Point2d(8.5549514676104650, 7.7116035988884200));
			Assert::IsTrue(points[i++] == Point2d(9.2180938321277708, 7.3990664176540477));
			Assert::IsTrue(points[i++] == Point2d(9.8990832429595521, 7.1276060934692520));
			Assert::IsTrue(points[i++] == Point2d(17.870986126173410, 4.2287323177551244));
			Assert::IsTrue(points[i++] == Point2d(17.984484361312038, 4.1834889303909915));
			Assert::IsTrue(points[i++] == Point2d(18.095008088731589, 4.1313994001852627));
			Assert::IsTrue(points[i++] == Point2d(18.202144811404128, 4.0726581358581102));
			Assert::IsTrue(points[i++] == Point2d(18.305494673292252, 4.0074843717542095));
			Assert::IsTrue(points[i++] == Point2d(18.404671951693135, 3.9361213496155827));
			Assert::IsTrue(points[i++] == Point2d(18.499306496834112, 3.8588354107539438));
			Assert::IsTrue(points[i++] == Point2d(18.589045113346895, 3.7759150020107608));
			Assert::IsTrue(points[i++] == Point2d(18.673552878464520, 3.6876695992149822));
			Assert::IsTrue(points[i++] == Point2d(18.752514392021229, 3.5944285521563053));
			Assert::IsTrue(points[i++] == Point2d(18.825634953590029, 3.4965398553847775));
			Assert::IsTrue(points[i++] == Point2d(18.892641662364621, 3.3943688494243704));
			Assert::IsTrue(points[i++] == Point2d(18.953284435680711, 3.2882968572478388));
			Assert::IsTrue(points[i++] == Point2d(19.007336942375364, 3.1787197611018394));
			Assert::IsTrue(points[i++] == Point2d(19.054597447500939, 3.0660465249938786));
			Assert::IsTrue(points[i++] == Point2d(19.094889565240940, 2.9506976683554598));
			Assert::IsTrue(points[i++] == Point2d(19.128062917217761, 2.8331036965780481));
			Assert::IsTrue(points[i++] == Point2d(19.153993693735359, 2.7137034942793949));
			Assert::IsTrue(points[i++] == Point2d(19.172585115862230, 2.5929426872968921));
			Assert::IsTrue(points[i++] == Point2d(19.183767796630057, 2.4712719795213163));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, 2.3491454707782506));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);

			Assert::AreEqual(beamClone.GetW1(),26.);
			Assert::AreEqual(beamClone.GetW2(),45.5);
			Assert::AreEqual(beamClone.GetW4(),1.);
			Assert::AreEqual(beamClone.GetW5(),5.5);
			Assert::AreEqual(beamClone.GetW6(),38.375);
			Assert::AreEqual(beamClone.GetD1(),8.);
			Assert::AreEqual(beamClone.GetD2(),1.);
			Assert::AreEqual(beamClone.GetD3(),0.5);
			Assert::AreEqual(beamClone.GetD4(),0.5);
			Assert::AreEqual(beamClone.GetD5(),1.);
			Assert::AreEqual(beamClone.GetD6(),9.);
			Assert::AreEqual(beamClone.GetD7(),3.);
			Assert::AreEqual(beamClone.GetD8(),10.);
			Assert::AreEqual(beamClone.GetD9(),3.75);
			Assert::AreEqual(beamClone.GetH(),54.);
			Assert::AreEqual(beamClone.GetT(),4.);
			Assert::AreEqual(beamClone.GetR1(),9.);
			Assert::AreEqual(beamClone.GetR2(),12.);
			Assert::AreEqual(beamClone.GetR3(),2.);
			Assert::AreEqual(beamClone.GetC1(),1.0);
		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, 0.5);
			Assert::IsTrue(beam.PointInShape(pnt));

			pnt.Move(500, 500);
			Assert::IsFalse(beam.PointInShape(pnt));

			pnt.Move(0, 0); // Point on perimeter
			Assert::IsFalse(beam.PointInShape(pnt));
		}

		TEST_METHOD(ClipWithLine)
		{
			auto beam = GetTestBeam();

			// setup clipping line
			Point2d p1(-5000, 50);
			Point2d p2(5000, 50);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 146);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.187500000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, 2.3491454707782506));
			Assert::IsTrue(points[i++] == Point2d(-19.183767796630057, 2.4712719795213163));
			Assert::IsTrue(points[i++] == Point2d(-19.172585115862230, 2.5929426872968921));
			Assert::IsTrue(points[i++] == Point2d(-19.153993693735359, 2.7137034942793949));
			Assert::IsTrue(points[i++] == Point2d(-19.128062917217761, 2.8331036965780481));
			Assert::IsTrue(points[i++] == Point2d(-19.094889565240940, 2.9506976683554598));
			Assert::IsTrue(points[i++] == Point2d(-19.054597447500939, 3.0660465249938786));
			Assert::IsTrue(points[i++] == Point2d(-19.007336942375364, 3.1787197611018394));
			Assert::IsTrue(points[i++] == Point2d(-18.953284435680711, 3.2882968572478388));
			Assert::IsTrue(points[i++] == Point2d(-18.892641662364621, 3.3943688494243704));
			Assert::IsTrue(points[i++] == Point2d(-18.825634953590029, 3.4965398553847775));
			Assert::IsTrue(points[i++] == Point2d(-18.752514392021229, 3.5944285521563053));
			Assert::IsTrue(points[i++] == Point2d(-18.673552878464520, 3.6876695992149822));
			Assert::IsTrue(points[i++] == Point2d(-18.589045113346895, 3.7759150020107608));
			Assert::IsTrue(points[i++] == Point2d(-18.499306496834112, 3.8588354107539438));
			Assert::IsTrue(points[i++] == Point2d(-18.404671951693135, 3.9361213496155827));
			Assert::IsTrue(points[i++] == Point2d(-18.305494673292252, 4.0074843717542095));
			Assert::IsTrue(points[i++] == Point2d(-18.202144811404128, 4.0726581358581102));
			Assert::IsTrue(points[i++] == Point2d(-18.095008088731589, 4.1313994001852627));
			Assert::IsTrue(points[i++] == Point2d(-17.984484361312038, 4.1834889303909915));
			Assert::IsTrue(points[i++] == Point2d(-17.870986126173410, 4.2287323177551244));
			Assert::IsTrue(points[i++] == Point2d(-9.8990832429595521, 7.1276060934692520));
			Assert::IsTrue(points[i++] == Point2d(-9.2180938321277708, 7.3990664176540477));
			Assert::IsTrue(points[i++] == Point2d(-8.5549514676104650, 7.7116035988884200));
			Assert::IsTrue(points[i++] == Point2d(-7.9121311315752365, 8.0640511848513370));
			Assert::IsTrue(points[i++] == Point2d(-7.2920319602465025, 8.4550937694747361));
			Assert::IsTrue(points[i++] == Point2d(-6.6969682898411946, 8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(-6.1291610189953278, 9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(-5.5907293199186316, 9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(-5.0836827292128834, 10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(-4.6099136478726308, 10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(-4.1711902784598287, 11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(-3.7691500258122659, 12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(-3.4052933859157282, 12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(-3.0809783457478215, 13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(-2.7974153149943675, 14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(-2.5556626085543499, 14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(-2.3566224966934257, 15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(-2.2010378375878421, 16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(-2.0894893048266212, 16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(-2.0223932202196480, 17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(-2.0271438002832998, 36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(-2.1084114709345680, 37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(-2.2433128089712202, 38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(-2.4310340955093395, 38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(-2.6704430040798801, 39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(-2.9600954307716645, 40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(-3.2982442050020992, 40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(-3.6828496283725691, 41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(-4.1115917780386653, 41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(-4.5818845003818183, 42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(-5.0908910105731424, 42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(-5.6355410039336338, 43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(-6.2125491758757176, 43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(-6.8184350387147230, 44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(-7.4495439158161219, 44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(-8.1020689864427879, 44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(-8.7720742483287388, 44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(-9.4555182594701073, 45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(-10.148278515923954, 45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(-10.846176318569077, 45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(-12.631748422367412, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-51.000000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000000, 47.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 47.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 47.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(58.500000000000000, 47.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(58.500000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(51.000000000000000, 46.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(12.631748422367412, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.846176318569077, 45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(10.148278515923954, 45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(9.4555182594701073, 45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(8.7720742483287388, 44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(8.1020689864427879, 44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(7.4495439158161219, 44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(6.8184350387147230, 44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(6.2125491758757176, 43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(5.6355410039336338, 43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(5.0908910105731424, 42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(4.5818845003818183, 42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(4.1115917780386653, 41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(3.6828496283725691, 41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(3.2982442050020992, 40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(2.9600954307716645, 40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(2.6704430040798801, 39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(2.4310340955093395, 38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(2.2433128089712202, 38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(2.1084114709345680, 37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(2.0271438002832998, 36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(2.0223932202196480, 17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(2.0894893048266212, 16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(2.2010378375878421, 16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(2.3566224966934257, 15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(2.5556626085543499, 14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(2.7974153149943675, 14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(3.0809783457478215, 13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(3.4052933859157282, 12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(3.7691500258122659, 12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(4.1711902784598287, 11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(4.6099136478726308, 10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(5.0836827292128834, 10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(5.5907293199186316, 9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(6.1291610189953278, 9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(6.6969682898411946, 8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(7.2920319602465025, 8.4550937694747361));
			Assert::IsTrue(points[i++] == Point2d(7.9121311315752365, 8.0640511848513370));
			Assert::IsTrue(points[i++] == Point2d(8.5549514676104650, 7.7116035988884200));
			Assert::IsTrue(points[i++] == Point2d(9.2180938321277708, 7.3990664176540477));
			Assert::IsTrue(points[i++] == Point2d(9.8990832429595521, 7.1276060934692520));
			Assert::IsTrue(points[i++] == Point2d(17.870986126173410, 4.2287323177551244));
			Assert::IsTrue(points[i++] == Point2d(17.984484361312038, 4.1834889303909915));
			Assert::IsTrue(points[i++] == Point2d(18.095008088731589, 4.1313994001852627));
			Assert::IsTrue(points[i++] == Point2d(18.202144811404128, 4.0726581358581102));
			Assert::IsTrue(points[i++] == Point2d(18.305494673292252, 4.0074843717542095));
			Assert::IsTrue(points[i++] == Point2d(18.404671951693135, 3.9361213496155827));
			Assert::IsTrue(points[i++] == Point2d(18.499306496834112, 3.8588354107539438));
			Assert::IsTrue(points[i++] == Point2d(18.589045113346895, 3.7759150020107608));
			Assert::IsTrue(points[i++] == Point2d(18.673552878464520, 3.6876695992149822));
			Assert::IsTrue(points[i++] == Point2d(18.752514392021229, 3.5944285521563053));
			Assert::IsTrue(points[i++] == Point2d(18.825634953590029, 3.4965398553847775));
			Assert::IsTrue(points[i++] == Point2d(18.892641662364621, 3.3943688494243704));
			Assert::IsTrue(points[i++] == Point2d(18.953284435680711, 3.2882968572478388));
			Assert::IsTrue(points[i++] == Point2d(19.007336942375364, 3.1787197611018394));
			Assert::IsTrue(points[i++] == Point2d(19.054597447500939, 3.0660465249938786));
			Assert::IsTrue(points[i++] == Point2d(19.094889565240940, 2.9506976683554598));
			Assert::IsTrue(points[i++] == Point2d(19.128062917217761, 2.8331036965780481));
			Assert::IsTrue(points[i++] == Point2d(19.153993693735359, 2.7137034942793949));
			Assert::IsTrue(points[i++] == Point2d(19.172585115862230, 2.5929426872968921));
			Assert::IsTrue(points[i++] == Point2d(19.183767796630057, 2.4712719795213163));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, 2.3491454707782506));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));

			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 17);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-12.631748422367412, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(12.631748422367412, 50.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-5000, 50, 5000, 10000);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 17);
			int i = 0;

			Assert::IsTrue(points[i++] == Point2d(-12.631748422367412, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(54.000000000000000, 53.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 52.500000000000000));
			Assert::IsTrue(points[i++] == Point2d(53.000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.666666666666664, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.000000000000000, 52.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(12.631748422367412, 50.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(HookPoint)
		{
			// Test hook point behavior
			auto beam = GetTestBeam();
			Assert::IsTrue(TestHookPoint(beam));
		}

		TEST_METHOD(Move)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			// Get moment of inertia about CG before move
			// These properties should be invariant
			Float64 area = props.GetArea();
			Float64 Ixx = props.GetIxx();
			Float64 Iyy = props.GetIyy();
			Float64 Ixy = props.GetIxy();

			Point2d from(0, 0);
			Point2d to(100, 100);

			beam.Move(from, to);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 151);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.812500000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(80.812500000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(80.812500000000000, 102.34914547077825));
			Assert::IsTrue(points[i++] == Point2d(80.816232203369935, 102.47127197952132));
			Assert::IsTrue(points[i++] == Point2d(80.827414884137767, 102.59294268729690));
			Assert::IsTrue(points[i++] == Point2d(80.846006306264641, 102.71370349427940));
			Assert::IsTrue(points[i++] == Point2d(80.871937082782239, 102.83310369657805));
			Assert::IsTrue(points[i++] == Point2d(80.905110434759052, 102.95069766835546));
			Assert::IsTrue(points[i++] == Point2d(80.945402552499061, 103.06604652499388));
			Assert::IsTrue(points[i++] == Point2d(80.992663057624640, 103.17871976110185));
			Assert::IsTrue(points[i++] == Point2d(81.046715564319285, 103.28829685724784));
			Assert::IsTrue(points[i++] == Point2d(81.107358337635375, 103.39436884942437));
			Assert::IsTrue(points[i++] == Point2d(81.174365046409974, 103.49653985538478));
			Assert::IsTrue(points[i++] == Point2d(81.247485607978774, 103.59442855215630));
			Assert::IsTrue(points[i++] == Point2d(81.326447121535480, 103.68766959921498));
			Assert::IsTrue(points[i++] == Point2d(81.410954886653101, 103.77591500201076));
			Assert::IsTrue(points[i++] == Point2d(81.500693503165891, 103.85883541075394));
			Assert::IsTrue(points[i++] == Point2d(81.595328048306868, 103.93612134961558));
			Assert::IsTrue(points[i++] == Point2d(81.694505326707741, 104.00748437175420));
			Assert::IsTrue(points[i++] == Point2d(81.797855188595875, 104.07265813585811));
			Assert::IsTrue(points[i++] == Point2d(81.904991911268411, 104.13139940018526));
			Assert::IsTrue(points[i++] == Point2d(82.015515638687958, 104.18348893039099));
			Assert::IsTrue(points[i++] == Point2d(82.129013873826594, 104.22873231775512));
			Assert::IsTrue(points[i++] == Point2d(90.100916757040451, 107.12760609346925));
			Assert::IsTrue(points[i++] == Point2d(90.781906167872222, 107.39906641765404));
			Assert::IsTrue(points[i++] == Point2d(91.445048532389535, 107.71160359888842));
			Assert::IsTrue(points[i++] == Point2d(92.087868868424763, 108.06405118485134));
			Assert::IsTrue(points[i++] == Point2d(92.707968039753496, 108.45509376947473));
			Assert::IsTrue(points[i++] == Point2d(93.303031710158805, 108.88327190230650));
			Assert::IsTrue(points[i++] == Point2d(93.870838981004667, 109.34698753547633));
			Assert::IsTrue(points[i++] == Point2d(94.409270680081363, 109.84450998793542));
			Assert::IsTrue(points[i++] == Point2d(94.916317270787118, 110.37398240471011));
			Assert::IsTrue(points[i++] == Point2d(95.390086352127369, 110.93342868706216));
			Assert::IsTrue(points[i++] == Point2d(95.828809721540168, 111.52076086769132));
			Assert::IsTrue(points[i++] == Point2d(96.230849974187734, 112.13378690345377));
			Assert::IsTrue(points[i++] == Point2d(96.594706614084274, 112.77021885651297));
			Assert::IsTrue(points[i++] == Point2d(96.919021654252177, 113.42768143338895));
			Assert::IsTrue(points[i++] == Point2d(97.202584685005633, 114.10372085003672));
			Assert::IsTrue(points[i++] == Point2d(97.444337391445657, 114.79581398986724));
			Assert::IsTrue(points[i++] == Point2d(97.643377503306567, 115.50137782053172));
			Assert::IsTrue(points[i++] == Point2d(97.798962162412153, 116.21777903432363));
			Assert::IsTrue(points[i++] == Point2d(97.910510695173372, 116.94234387621864));
			Assert::IsTrue(points[i++] == Point2d(97.977606779780359, 117.67236812287210));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 118.40512717533049));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 136.15253132549728));
			Assert::IsTrue(points[i++] == Point2d(97.972856199716702, 136.85099508204127));
			Assert::IsTrue(points[i++] == Point2d(97.891588529065430, 137.54524573620466));
			Assert::IsTrue(points[i++] == Point2d(97.756687191028774, 138.23109559885341));
			Assert::IsTrue(points[i++] == Point2d(97.568965904490653, 138.90440765405503));
			Assert::IsTrue(points[i++] == Point2d(97.329556995920115, 139.56112051337519));
			Assert::IsTrue(points[i++] == Point2d(97.039904569228341, 140.19727291399232));
			Assert::IsTrue(points[i++] == Point2d(96.701755794997894, 140.80902761285930));
			Assert::IsTrue(points[i++] == Point2d(96.317150371627434, 141.39269453278314));
			Assert::IsTrue(points[i++] == Point2d(95.888408221961328, 141.94475302080690));
			Assert::IsTrue(points[i++] == Point2d(95.418115499618182, 142.46187308463197));
			Assert::IsTrue(points[i++] == Point2d(94.909108989426855, 142.94093547898393));
			Assert::IsTrue(points[i++] == Point2d(94.364458996066361, 143.37905052076152));
			Assert::IsTrue(points[i++] == Point2d(93.787450824124278, 143.77357551947699));
			Assert::IsTrue(points[i++] == Point2d(93.181564961285275, 144.12213071784765));
			Assert::IsTrue(points[i++] == Point2d(92.550456084183878, 144.42261364638634));
			Assert::IsTrue(points[i++] == Point2d(91.897931013557212, 144.67321180540398));
			Assert::IsTrue(points[i++] == Point2d(91.227925751671265, 144.87241359792733));
			Assert::IsTrue(points[i++] == Point2d(90.544481740529889, 145.01901744758476));
			Assert::IsTrue(points[i++] == Point2d(89.851721484076052, 145.11213904646161));
			Assert::IsTrue(points[i++] == Point2d(89.153823681430922, 145.15121668920631));
			Assert::IsTrue(points[i++] == Point2d(87.000000000000000, 151.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(51.000000000000000, 152.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.000000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(41.500000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(41.500000000000000, 147.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(47.000000000000000, 147.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(47.000000000000000, 152.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(46.000000000000000, 153.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(46.000000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(154.00000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(154.00000000000000, 153.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(153.00000000000000, 152.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(153.00000000000000, 147.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(158.50000000000000, 147.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(158.50000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(151.00000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(149.00000000000000, 152.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(113.00000000000000, 151.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.84617631856908, 145.15121668920631));
			Assert::IsTrue(points[i++] == Point2d(110.14827851592395, 145.11213904646161));
			Assert::IsTrue(points[i++] == Point2d(109.45551825947011, 145.01901744758476));
			Assert::IsTrue(points[i++] == Point2d(108.77207424832874, 144.87241359792733));
			Assert::IsTrue(points[i++] == Point2d(108.10206898644279, 144.67321180540398));
			Assert::IsTrue(points[i++] == Point2d(107.44954391581612, 144.42261364638634));
			Assert::IsTrue(points[i++] == Point2d(106.81843503871472, 144.12213071784765));
			Assert::IsTrue(points[i++] == Point2d(106.21254917587572, 143.77357551947699));
			Assert::IsTrue(points[i++] == Point2d(105.63554100393364, 143.37905052076152));
			Assert::IsTrue(points[i++] == Point2d(105.09089101057315, 142.94093547898393));
			Assert::IsTrue(points[i++] == Point2d(104.58188450038182, 142.46187308463197));
			Assert::IsTrue(points[i++] == Point2d(104.11159177803867, 141.94475302080690));
			Assert::IsTrue(points[i++] == Point2d(103.68284962837257, 141.39269453278314));
			Assert::IsTrue(points[i++] == Point2d(103.29824420500211, 140.80902761285930));
			Assert::IsTrue(points[i++] == Point2d(102.96009543077166, 140.19727291399232));
			Assert::IsTrue(points[i++] == Point2d(102.67044300407989, 139.56112051337519));
			Assert::IsTrue(points[i++] == Point2d(102.43103409550935, 138.90440765405503));
			Assert::IsTrue(points[i++] == Point2d(102.24331280897123, 138.23109559885341));
			Assert::IsTrue(points[i++] == Point2d(102.10841147093457, 137.54524573620466));
			Assert::IsTrue(points[i++] == Point2d(102.02714380028330, 136.85099508204127));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 136.15253132549728));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 118.40512717533049));
			Assert::IsTrue(points[i++] == Point2d(102.02239322021964, 117.67236812287210));
			Assert::IsTrue(points[i++] == Point2d(102.08948930482663, 116.94234387621864));
			Assert::IsTrue(points[i++] == Point2d(102.20103783758785, 116.21777903432363));
			Assert::IsTrue(points[i++] == Point2d(102.35662249669343, 115.50137782053172));
			Assert::IsTrue(points[i++] == Point2d(102.55566260855434, 114.79581398986724));
			Assert::IsTrue(points[i++] == Point2d(102.79741531499437, 114.10372085003672));
			Assert::IsTrue(points[i++] == Point2d(103.08097834574782, 113.42768143338895));
			Assert::IsTrue(points[i++] == Point2d(103.40529338591573, 112.77021885651297));
			Assert::IsTrue(points[i++] == Point2d(103.76915002581227, 112.13378690345377));
			Assert::IsTrue(points[i++] == Point2d(104.17119027845983, 111.52076086769132));
			Assert::IsTrue(points[i++] == Point2d(104.60991364787263, 110.93342868706216));
			Assert::IsTrue(points[i++] == Point2d(105.08368272921288, 110.37398240471011));
			Assert::IsTrue(points[i++] == Point2d(105.59072931991864, 109.84450998793542));
			Assert::IsTrue(points[i++] == Point2d(106.12916101899533, 109.34698753547633));
			Assert::IsTrue(points[i++] == Point2d(106.69696828984119, 108.88327190230650));
			Assert::IsTrue(points[i++] == Point2d(107.29203196024650, 108.45509376947473));
			Assert::IsTrue(points[i++] == Point2d(107.91213113157524, 108.06405118485134));
			Assert::IsTrue(points[i++] == Point2d(108.55495146761046, 107.71160359888842));
			Assert::IsTrue(points[i++] == Point2d(109.21809383212778, 107.39906641765404));
			Assert::IsTrue(points[i++] == Point2d(109.89908324295955, 107.12760609346925));
			Assert::IsTrue(points[i++] == Point2d(117.87098612617341, 104.22873231775512));
			Assert::IsTrue(points[i++] == Point2d(117.98448436131204, 104.18348893039099));
			Assert::IsTrue(points[i++] == Point2d(118.09500808873159, 104.13139940018526));
			Assert::IsTrue(points[i++] == Point2d(118.20214481140412, 104.07265813585811));
			Assert::IsTrue(points[i++] == Point2d(118.30549467329226, 104.00748437175420));
			Assert::IsTrue(points[i++] == Point2d(118.40467195169313, 103.93612134961558));
			Assert::IsTrue(points[i++] == Point2d(118.49930649683411, 103.85883541075394));
			Assert::IsTrue(points[i++] == Point2d(118.58904511334690, 103.77591500201076));
			Assert::IsTrue(points[i++] == Point2d(118.67355287846452, 103.68766959921498));
			Assert::IsTrue(points[i++] == Point2d(118.75251439202123, 103.59442855215630));
			Assert::IsTrue(points[i++] == Point2d(118.82563495359003, 103.49653985538478));
			Assert::IsTrue(points[i++] == Point2d(118.89264166236462, 103.39436884942437));
			Assert::IsTrue(points[i++] == Point2d(118.95328443568071, 103.28829685724784));
			Assert::IsTrue(points[i++] == Point2d(119.00733694237536, 103.17871976110185));
			Assert::IsTrue(points[i++] == Point2d(119.05459744750094, 103.06604652499388));
			Assert::IsTrue(points[i++] == Point2d(119.09488956524095, 102.95069766835546));
			Assert::IsTrue(points[i++] == Point2d(119.12806291721776, 102.83310369657805));
			Assert::IsTrue(points[i++] == Point2d(119.15399369373536, 102.71370349427940));
			Assert::IsTrue(points[i++] == Point2d(119.17258511586223, 102.59294268729690));
			Assert::IsTrue(points[i++] == Point2d(119.18376779663006, 102.47127197952132));
			Assert::IsTrue(points[i++] == Point2d(119.18750000000000, 102.34914547077825));
			Assert::IsTrue(points[i++] == Point2d(119.18750000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(118.18750000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx, 0.01));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy, 0.01));
		}

		TEST_METHOD(Offset)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			// Get moment of inertia about CG before move
			// These properties should be invariant
			Float64 area = props.GetArea();
			Float64 Ixx = props.GetIxx();
			Float64 Iyy = props.GetIyy();
			Float64 Ixy = props.GetIxy();

			Size2d size(100, 100);
			beam.Offset(size);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 151);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.812500000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(80.812500000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(80.812500000000000, 102.34914547077825));
			Assert::IsTrue(points[i++] == Point2d(80.816232203369935, 102.47127197952132));
			Assert::IsTrue(points[i++] == Point2d(80.827414884137767, 102.59294268729690));
			Assert::IsTrue(points[i++] == Point2d(80.846006306264641, 102.71370349427940));
			Assert::IsTrue(points[i++] == Point2d(80.871937082782239, 102.83310369657805));
			Assert::IsTrue(points[i++] == Point2d(80.905110434759052, 102.95069766835546));
			Assert::IsTrue(points[i++] == Point2d(80.945402552499061, 103.06604652499388));
			Assert::IsTrue(points[i++] == Point2d(80.992663057624640, 103.17871976110185));
			Assert::IsTrue(points[i++] == Point2d(81.046715564319285, 103.28829685724784));
			Assert::IsTrue(points[i++] == Point2d(81.107358337635375, 103.39436884942437));
			Assert::IsTrue(points[i++] == Point2d(81.174365046409974, 103.49653985538478));
			Assert::IsTrue(points[i++] == Point2d(81.247485607978774, 103.59442855215630));
			Assert::IsTrue(points[i++] == Point2d(81.326447121535480, 103.68766959921498));
			Assert::IsTrue(points[i++] == Point2d(81.410954886653101, 103.77591500201076));
			Assert::IsTrue(points[i++] == Point2d(81.500693503165891, 103.85883541075394));
			Assert::IsTrue(points[i++] == Point2d(81.595328048306868, 103.93612134961558));
			Assert::IsTrue(points[i++] == Point2d(81.694505326707741, 104.00748437175420));
			Assert::IsTrue(points[i++] == Point2d(81.797855188595875, 104.07265813585811));
			Assert::IsTrue(points[i++] == Point2d(81.904991911268411, 104.13139940018526));
			Assert::IsTrue(points[i++] == Point2d(82.015515638687958, 104.18348893039099));
			Assert::IsTrue(points[i++] == Point2d(82.129013873826594, 104.22873231775512));
			Assert::IsTrue(points[i++] == Point2d(90.100916757040451, 107.12760609346925));
			Assert::IsTrue(points[i++] == Point2d(90.781906167872222, 107.39906641765404));
			Assert::IsTrue(points[i++] == Point2d(91.445048532389535, 107.71160359888842));
			Assert::IsTrue(points[i++] == Point2d(92.087868868424763, 108.06405118485134));
			Assert::IsTrue(points[i++] == Point2d(92.707968039753496, 108.45509376947473));
			Assert::IsTrue(points[i++] == Point2d(93.303031710158805, 108.88327190230650));
			Assert::IsTrue(points[i++] == Point2d(93.870838981004667, 109.34698753547633));
			Assert::IsTrue(points[i++] == Point2d(94.409270680081363, 109.84450998793542));
			Assert::IsTrue(points[i++] == Point2d(94.916317270787118, 110.37398240471011));
			Assert::IsTrue(points[i++] == Point2d(95.390086352127369, 110.93342868706216));
			Assert::IsTrue(points[i++] == Point2d(95.828809721540168, 111.52076086769132));
			Assert::IsTrue(points[i++] == Point2d(96.230849974187734, 112.13378690345377));
			Assert::IsTrue(points[i++] == Point2d(96.594706614084274, 112.77021885651297));
			Assert::IsTrue(points[i++] == Point2d(96.919021654252177, 113.42768143338895));
			Assert::IsTrue(points[i++] == Point2d(97.202584685005633, 114.10372085003672));
			Assert::IsTrue(points[i++] == Point2d(97.444337391445657, 114.79581398986724));
			Assert::IsTrue(points[i++] == Point2d(97.643377503306567, 115.50137782053172));
			Assert::IsTrue(points[i++] == Point2d(97.798962162412153, 116.21777903432363));
			Assert::IsTrue(points[i++] == Point2d(97.910510695173372, 116.94234387621864));
			Assert::IsTrue(points[i++] == Point2d(97.977606779780359, 117.67236812287210));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 118.40512717533049));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 136.15253132549728));
			Assert::IsTrue(points[i++] == Point2d(97.972856199716702, 136.85099508204127));
			Assert::IsTrue(points[i++] == Point2d(97.891588529065430, 137.54524573620466));
			Assert::IsTrue(points[i++] == Point2d(97.756687191028774, 138.23109559885341));
			Assert::IsTrue(points[i++] == Point2d(97.568965904490653, 138.90440765405503));
			Assert::IsTrue(points[i++] == Point2d(97.329556995920115, 139.56112051337519));
			Assert::IsTrue(points[i++] == Point2d(97.039904569228341, 140.19727291399232));
			Assert::IsTrue(points[i++] == Point2d(96.701755794997894, 140.80902761285930));
			Assert::IsTrue(points[i++] == Point2d(96.317150371627434, 141.39269453278314));
			Assert::IsTrue(points[i++] == Point2d(95.888408221961328, 141.94475302080690));
			Assert::IsTrue(points[i++] == Point2d(95.418115499618182, 142.46187308463197));
			Assert::IsTrue(points[i++] == Point2d(94.909108989426855, 142.94093547898393));
			Assert::IsTrue(points[i++] == Point2d(94.364458996066361, 143.37905052076152));
			Assert::IsTrue(points[i++] == Point2d(93.787450824124278, 143.77357551947699));
			Assert::IsTrue(points[i++] == Point2d(93.181564961285275, 144.12213071784765));
			Assert::IsTrue(points[i++] == Point2d(92.550456084183878, 144.42261364638634));
			Assert::IsTrue(points[i++] == Point2d(91.897931013557212, 144.67321180540398));
			Assert::IsTrue(points[i++] == Point2d(91.227925751671265, 144.87241359792733));
			Assert::IsTrue(points[i++] == Point2d(90.544481740529889, 145.01901744758476));
			Assert::IsTrue(points[i++] == Point2d(89.851721484076052, 145.11213904646161));
			Assert::IsTrue(points[i++] == Point2d(89.153823681430922, 145.15121668920631));
			Assert::IsTrue(points[i++] == Point2d(87.000000000000000, 151.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(51.000000000000000, 152.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(49.000000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(41.500000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(41.500000000000000, 147.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(47.000000000000000, 147.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(47.000000000000000, 152.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(46.000000000000000, 153.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(46.000000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(154.00000000000000, 154.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(154.00000000000000, 153.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(153.00000000000000, 152.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(153.00000000000000, 147.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(158.50000000000000, 147.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(158.50000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(151.00000000000000, 146.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(149.00000000000000, 152.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(113.00000000000000, 151.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.84617631856908, 145.15121668920631));
			Assert::IsTrue(points[i++] == Point2d(110.14827851592395, 145.11213904646161));
			Assert::IsTrue(points[i++] == Point2d(109.45551825947011, 145.01901744758476));
			Assert::IsTrue(points[i++] == Point2d(108.77207424832874, 144.87241359792733));
			Assert::IsTrue(points[i++] == Point2d(108.10206898644279, 144.67321180540398));
			Assert::IsTrue(points[i++] == Point2d(107.44954391581612, 144.42261364638634));
			Assert::IsTrue(points[i++] == Point2d(106.81843503871472, 144.12213071784765));
			Assert::IsTrue(points[i++] == Point2d(106.21254917587572, 143.77357551947699));
			Assert::IsTrue(points[i++] == Point2d(105.63554100393364, 143.37905052076152));
			Assert::IsTrue(points[i++] == Point2d(105.09089101057315, 142.94093547898393));
			Assert::IsTrue(points[i++] == Point2d(104.58188450038182, 142.46187308463197));
			Assert::IsTrue(points[i++] == Point2d(104.11159177803867, 141.94475302080690));
			Assert::IsTrue(points[i++] == Point2d(103.68284962837257, 141.39269453278314));
			Assert::IsTrue(points[i++] == Point2d(103.29824420500211, 140.80902761285930));
			Assert::IsTrue(points[i++] == Point2d(102.96009543077166, 140.19727291399232));
			Assert::IsTrue(points[i++] == Point2d(102.67044300407989, 139.56112051337519));
			Assert::IsTrue(points[i++] == Point2d(102.43103409550935, 138.90440765405503));
			Assert::IsTrue(points[i++] == Point2d(102.24331280897123, 138.23109559885341));
			Assert::IsTrue(points[i++] == Point2d(102.10841147093457, 137.54524573620466));
			Assert::IsTrue(points[i++] == Point2d(102.02714380028330, 136.85099508204127));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 136.15253132549728));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 118.40512717533049));
			Assert::IsTrue(points[i++] == Point2d(102.02239322021964, 117.67236812287210));
			Assert::IsTrue(points[i++] == Point2d(102.08948930482663, 116.94234387621864));
			Assert::IsTrue(points[i++] == Point2d(102.20103783758785, 116.21777903432363));
			Assert::IsTrue(points[i++] == Point2d(102.35662249669343, 115.50137782053172));
			Assert::IsTrue(points[i++] == Point2d(102.55566260855434, 114.79581398986724));
			Assert::IsTrue(points[i++] == Point2d(102.79741531499437, 114.10372085003672));
			Assert::IsTrue(points[i++] == Point2d(103.08097834574782, 113.42768143338895));
			Assert::IsTrue(points[i++] == Point2d(103.40529338591573, 112.77021885651297));
			Assert::IsTrue(points[i++] == Point2d(103.76915002581227, 112.13378690345377));
			Assert::IsTrue(points[i++] == Point2d(104.17119027845983, 111.52076086769132));
			Assert::IsTrue(points[i++] == Point2d(104.60991364787263, 110.93342868706216));
			Assert::IsTrue(points[i++] == Point2d(105.08368272921288, 110.37398240471011));
			Assert::IsTrue(points[i++] == Point2d(105.59072931991864, 109.84450998793542));
			Assert::IsTrue(points[i++] == Point2d(106.12916101899533, 109.34698753547633));
			Assert::IsTrue(points[i++] == Point2d(106.69696828984119, 108.88327190230650));
			Assert::IsTrue(points[i++] == Point2d(107.29203196024650, 108.45509376947473));
			Assert::IsTrue(points[i++] == Point2d(107.91213113157524, 108.06405118485134));
			Assert::IsTrue(points[i++] == Point2d(108.55495146761046, 107.71160359888842));
			Assert::IsTrue(points[i++] == Point2d(109.21809383212778, 107.39906641765404));
			Assert::IsTrue(points[i++] == Point2d(109.89908324295955, 107.12760609346925));
			Assert::IsTrue(points[i++] == Point2d(117.87098612617341, 104.22873231775512));
			Assert::IsTrue(points[i++] == Point2d(117.98448436131204, 104.18348893039099));
			Assert::IsTrue(points[i++] == Point2d(118.09500808873159, 104.13139940018526));
			Assert::IsTrue(points[i++] == Point2d(118.20214481140412, 104.07265813585811));
			Assert::IsTrue(points[i++] == Point2d(118.30549467329226, 104.00748437175420));
			Assert::IsTrue(points[i++] == Point2d(118.40467195169313, 103.93612134961558));
			Assert::IsTrue(points[i++] == Point2d(118.49930649683411, 103.85883541075394));
			Assert::IsTrue(points[i++] == Point2d(118.58904511334690, 103.77591500201076));
			Assert::IsTrue(points[i++] == Point2d(118.67355287846452, 103.68766959921498));
			Assert::IsTrue(points[i++] == Point2d(118.75251439202123, 103.59442855215630));
			Assert::IsTrue(points[i++] == Point2d(118.82563495359003, 103.49653985538478));
			Assert::IsTrue(points[i++] == Point2d(118.89264166236462, 103.39436884942437));
			Assert::IsTrue(points[i++] == Point2d(118.95328443568071, 103.28829685724784));
			Assert::IsTrue(points[i++] == Point2d(119.00733694237536, 103.17871976110185));
			Assert::IsTrue(points[i++] == Point2d(119.05459744750094, 103.06604652499388));
			Assert::IsTrue(points[i++] == Point2d(119.09488956524095, 102.95069766835546));
			Assert::IsTrue(points[i++] == Point2d(119.12806291721776, 102.83310369657805));
			Assert::IsTrue(points[i++] == Point2d(119.15399369373536, 102.71370349427940));
			Assert::IsTrue(points[i++] == Point2d(119.17258511586223, 102.59294268729690));
			Assert::IsTrue(points[i++] == Point2d(119.18376779663006, 102.47127197952132));
			Assert::IsTrue(points[i++] == Point2d(119.18750000000000, 102.34914547077825));
			Assert::IsTrue(points[i++] == Point2d(119.18750000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(118.18750000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx, 0.01));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy, 0.01));
		}

		TEST_METHOD(LocatorPoint)
		{
			auto beam = GetTestBeam();

			auto hookPnt = beam.GetHookPoint();

			// BottomLeft
			hookPnt->Move(0, 0);
			Point2d to(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
			auto from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(158.5, 100.0));

			// BottomCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

			// BottomRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(41.5, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(158.5, 73.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 73.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(41.5, 73.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(158.5, 46.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 46.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(41.5, 46.0));

			// HookPoint
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));
		}

		TEST_METHOD(Rotate)
		{
			auto beam = GetTestBeam();
			auto hookPnt = beam.GetHookPoint();
			hookPnt->Move(0, 0);

			Point2d c(0, 0);

			beam.Rotate(c, M_PI);

			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 151);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500000000000, -2.2273263659492487e-15));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, -1.0000000000000024));
			Assert::IsTrue(points[i++] == Point2d(19.187500000000000, -2.3491454707782529));
			Assert::IsTrue(points[i++] == Point2d(19.183767796630057, -2.4712719795213185));
			Assert::IsTrue(points[i++] == Point2d(19.172585115862230, -2.5929426872968944));
			Assert::IsTrue(points[i++] == Point2d(19.153993693735359, -2.7137034942793972));
			Assert::IsTrue(points[i++] == Point2d(19.128062917217761, -2.8331036965780503));
			Assert::IsTrue(points[i++] == Point2d(19.094889565240940, -2.9506976683554620));
			Assert::IsTrue(points[i++] == Point2d(19.054597447500939, -3.0660465249938809));
			Assert::IsTrue(points[i++] == Point2d(19.007336942375364, -3.1787197611018416));
			Assert::IsTrue(points[i++] == Point2d(18.953284435680711, -3.2882968572478410));
			Assert::IsTrue(points[i++] == Point2d(18.892641662364621, -3.3943688494243727));
			Assert::IsTrue(points[i++] == Point2d(18.825634953590029, -3.4965398553847797));
			Assert::IsTrue(points[i++] == Point2d(18.752514392021229, -3.5944285521563075));
			Assert::IsTrue(points[i++] == Point2d(18.673552878464520, -3.6876695992149844));
			Assert::IsTrue(points[i++] == Point2d(18.589045113346895, -3.7759150020107630));
			Assert::IsTrue(points[i++] == Point2d(18.499306496834112, -3.8588354107539460));
			Assert::IsTrue(points[i++] == Point2d(18.404671951693135, -3.9361213496155849));
			Assert::IsTrue(points[i++] == Point2d(18.305494673292252, -4.0074843717542121));
			Assert::IsTrue(points[i++] == Point2d(18.202144811404128, -4.0726581358581129));
			Assert::IsTrue(points[i++] == Point2d(18.095008088731589, -4.1313994001852645));
			Assert::IsTrue(points[i++] == Point2d(17.984484361312038, -4.1834889303909932));
			Assert::IsTrue(points[i++] == Point2d(17.870986126173410, -4.2287323177551261));
			Assert::IsTrue(points[i++] == Point2d(9.8990832429595521, -7.1276060934692529));
			Assert::IsTrue(points[i++] == Point2d(9.2180938321277690, -7.3990664176540486));
			Assert::IsTrue(points[i++] == Point2d(8.5549514676104632, -7.7116035988884208));
			Assert::IsTrue(points[i++] == Point2d(7.9121311315752356, -8.0640511848513388));
			Assert::IsTrue(points[i++] == Point2d(7.2920319602465016, -8.4550937694747379));
			Assert::IsTrue(points[i++] == Point2d(6.6969682898411937, -8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(6.1291610189953269, -9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(5.5907293199186308, -9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(5.0836827292128826, -10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(4.6099136478726290, -10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(4.1711902784598269, -11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(3.7691500258122645, -12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(3.4052933859157264, -12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(3.0809783457478197, -13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(2.7974153149943657, -14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(2.5556626085543481, -14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(2.3566224966934239, -15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(2.2010378375878403, -16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(2.0894893048266190, -16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(2.0223932202196457, -17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(1.9999999999999978, -18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(1.9999999999999956, -36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(2.0271438002832953, -36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(2.1084114709345636, -37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(2.2433128089712153, -38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(2.4310340955093346, -38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(2.6704430040798752, -39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(2.9600954307716596, -40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(3.2982442050020944, -40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(3.6828496283725642, -41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(4.1115917780386599, -41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(4.5818845003818129, -42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(5.0908910105731371, -42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(5.6355410039336284, -43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(6.2125491758757123, -43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(6.8184350387147177, -44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(7.4495439158161165, -44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(8.1020689864427826, -44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(8.7720742483287335, -44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(9.4555182594701019, -45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(10.148278515923948, -45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(10.846176318569071, -45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(12.999999999999993, -51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(48.999999999999993, -52.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(50.999999999999993, -46.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(58.499999999999993, -46.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(58.499999999999993, -47.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(52.999999999999993, -47.500000000000007));
			Assert::IsTrue(points[i++] == Point2d(52.999999999999993, -52.500000000000007));
			Assert::IsTrue(points[i++] == Point2d(53.999999999999993, -53.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(53.999999999999993, -54.000000000000007));
			Assert::IsTrue(points[i++] == Point2d(-6.6130927153957075e-15, -54.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000007, -53.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-54.000000000000007, -52.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000007, -52.499999999999993));
			Assert::IsTrue(points[i++] == Point2d(-53.000000000000007, -47.499999999999993));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000007, -46.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-58.500000000000007, -45.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-51.000000000000007, -45.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-49.000000000000007, -51.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000007, -51.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-10.846176318569082, -45.151216689206308));
			Assert::IsTrue(points[i++] == Point2d(-10.148278515923959, -45.112139046461593));
			Assert::IsTrue(points[i++] == Point2d(-9.4555182594701126, -45.019017447584751));
			Assert::IsTrue(points[i++] == Point2d(-8.7720742483287442, -44.872413597927341));
			Assert::IsTrue(points[i++] == Point2d(-8.1020689864427933, -44.673211805403994));
			Assert::IsTrue(points[i++] == Point2d(-7.4495439158161272, -44.422613646386331));
			Assert::IsTrue(points[i++] == Point2d(-6.8184350387147283, -44.122130717847639));
			Assert::IsTrue(points[i++] == Point2d(-6.2125491758757230, -43.773575519476978));
			Assert::IsTrue(points[i++] == Point2d(-5.6355410039336391, -43.379050520761524));
			Assert::IsTrue(points[i++] == Point2d(-5.0908910105731477, -42.940935478983917));
			Assert::IsTrue(points[i++] == Point2d(-4.5818845003818236, -42.461873084631968));
			Assert::IsTrue(points[i++] == Point2d(-4.1115917780386706, -41.944753020806900));
			Assert::IsTrue(points[i++] == Point2d(-3.6828496283725740, -41.392694532783153));
			Assert::IsTrue(points[i++] == Point2d(-3.2982442050021041, -40.809027612859296));
			Assert::IsTrue(points[i++] == Point2d(-2.9600954307716694, -40.197272913992315));
			Assert::IsTrue(points[i++] == Point2d(-2.6704430040798850, -39.561120513375187));
			Assert::IsTrue(points[i++] == Point2d(-2.4310340955093444, -38.904407654055042));
			Assert::IsTrue(points[i++] == Point2d(-2.2433128089712251, -38.231095598853408));
			Assert::IsTrue(points[i++] == Point2d(-2.1084114709345725, -37.545245736204670));
			Assert::IsTrue(points[i++] == Point2d(-2.0271438002833042, -36.850995082041280));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000044, -36.152531325497279));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000022, -18.405127175330495));
			Assert::IsTrue(points[i++] == Point2d(-2.0223932202196502, -17.672368122872101));
			Assert::IsTrue(points[i++] == Point2d(-2.0894893048266234, -16.942343876218644));
			Assert::IsTrue(points[i++] == Point2d(-2.2010378375878439, -16.217779034323627));
			Assert::IsTrue(points[i++] == Point2d(-2.3566224966934275, -15.501377820531712));
			Assert::IsTrue(points[i++] == Point2d(-2.5556626085543517, -14.795813989867240));
			Assert::IsTrue(points[i++] == Point2d(-2.7974153149943692, -14.103720850036726));
			Assert::IsTrue(points[i++] == Point2d(-3.0809783457478233, -13.427681433388953));
			Assert::IsTrue(points[i++] == Point2d(-3.4052933859157299, -12.770218856512972));
			Assert::IsTrue(points[i++] == Point2d(-3.7691500258122672, -12.133786903453771));
			Assert::IsTrue(points[i++] == Point2d(-4.1711902784598305, -11.520760867691328));
			Assert::IsTrue(points[i++] == Point2d(-4.6099136478726326, -10.933428687062165));
			Assert::IsTrue(points[i++] == Point2d(-5.0836827292128843, -10.373982404710100));
			Assert::IsTrue(points[i++] == Point2d(-5.5907293199186325, -9.8445099879354316));
			Assert::IsTrue(points[i++] == Point2d(-6.1291610189953287, -9.3469875354763339));
			Assert::IsTrue(points[i++] == Point2d(-6.6969682898411955, -8.8832719023065003));
			Assert::IsTrue(points[i++] == Point2d(-7.2920319602465034, -8.4550937694747343));
			Assert::IsTrue(points[i++] == Point2d(-7.9121311315752374, -8.0640511848513352));
			Assert::IsTrue(points[i++] == Point2d(-8.5549514676104668, -7.7116035988884191));
			Assert::IsTrue(points[i++] == Point2d(-9.2180938321277726, -7.3990664176540468));
			Assert::IsTrue(points[i++] == Point2d(-9.8990832429595521, -7.1276060934692511));
			Assert::IsTrue(points[i++] == Point2d(-17.870986126173410, -4.2287323177551226));
			Assert::IsTrue(points[i++] == Point2d(-17.984484361312038, -4.1834889303909897));
			Assert::IsTrue(points[i++] == Point2d(-18.095008088731589, -4.1313994001852610));
			Assert::IsTrue(points[i++] == Point2d(-18.202144811404128, -4.0726581358581075));
			Assert::IsTrue(points[i++] == Point2d(-18.305494673292252, -4.0074843717542068));
			Assert::IsTrue(points[i++] == Point2d(-18.404671951693135, -3.9361213496155805));
			Assert::IsTrue(points[i++] == Point2d(-18.499306496834112, -3.8588354107539415));
			Assert::IsTrue(points[i++] == Point2d(-18.589045113346895, -3.7759150020107586));
			Assert::IsTrue(points[i++] == Point2d(-18.673552878464520, -3.6876695992149799));
			Assert::IsTrue(points[i++] == Point2d(-18.752514392021229, -3.5944285521563031));
			Assert::IsTrue(points[i++] == Point2d(-18.825634953590029, -3.4965398553847753));
			Assert::IsTrue(points[i++] == Point2d(-18.892641662364621, -3.3943688494243682));
			Assert::IsTrue(points[i++] == Point2d(-18.953284435680711, -3.2882968572478366));
			Assert::IsTrue(points[i++] == Point2d(-19.007336942375364, -3.1787197611018372));
			Assert::IsTrue(points[i++] == Point2d(-19.054597447500939, -3.0660465249938764));
			Assert::IsTrue(points[i++] == Point2d(-19.094889565240940, -2.9506976683554575));
			Assert::IsTrue(points[i++] == Point2d(-19.128062917217761, -2.8331036965780458));
			Assert::IsTrue(points[i++] == Point2d(-19.153993693735359, -2.7137034942793927));
			Assert::IsTrue(points[i++] == Point2d(-19.172585115862230, -2.5929426872968899));
			Assert::IsTrue(points[i++] == Point2d(-19.183767796630057, -2.4712719795213141));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, -2.3491454707782484));
			Assert::IsTrue(points[i++] == Point2d(-19.187500000000000, -0.99999999999999767));
			Assert::IsTrue(points[i++] == Point2d(-18.187500000000000, 2.2273263659492487e-15));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
