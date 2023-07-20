#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestNUDeckedIBeam)
	{
	public:
		
		NUDeckedIBeam GetTestBeam()
		{
			NUDeckedIBeam beam;

			// Use some real dimensions
			beam.SetW1(26);
			beam.SetW2(49);
			beam.SetW3(1);
			beam.SetW4(38);
			beam.SetD1(2);
			beam.SetD2(6);
			beam.SetD3(9);
			beam.SetD4(3);
			beam.SetD5(13);
			beam.SetD6(5);
			beam.SetH(108);
			beam.SetT(4);
			beam.SetR1(10);
			beam.SetR2(22.5);
			beam.SetC1(1.0);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -63.0));
			Assert::IsTrue(IsEqual(box.Right(), 63.0));
			Assert::IsTrue(IsEqual(box.Top(), 108.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			Assert::IsTrue(IsEqual(props.GetArea(), 1286.6976042586434));
			Assert::IsTrue(IsEqual(props.GetIxx(), 2471035.0754711358));
			Assert::IsTrue(IsEqual(props.GetIyy(), 419404.68570325995));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0, 0.0005));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 59.057149336875156));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 63.0));
			Assert::IsTrue(IsEqual(props.GetXright(), 63.0));
			Assert::IsTrue(IsEqual(props.GetYtop(), 108.0 - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 502.08150632310787));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 108.));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(0), 126.));
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeWidth(0), 38.0));
			Assert::IsTrue(IsEqual(beam.GetAvgWebWidth(), 4.));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();

			Point2d p1(0, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.0));

			// shape on left
			p1.Move(0, -20);
			p2.Move(100, -20);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.0));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 99);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-18.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-19.000000, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(-19.000000, 5.000000));
			Assert::IsTrue(points[i++] == Point2d(-14.919567, 6.920204));
			Assert::IsTrue(points[i++] == Point2d(-13.784272, 7.494207));
			Assert::IsTrue(points[i++] == Point2d(-12.683233, 8.131457));
			Assert::IsTrue(points[i++] == Point2d(-11.619970, 8.829917));
			Assert::IsTrue(points[i++] == Point2d(-10.597881, 9.587353));
			Assert::IsTrue(points[i++] == Point2d(-9.620235, 10.401345));
			Assert::IsTrue(points[i++] == Point2d(-8.690156, 11.269289));
			Assert::IsTrue(points[i++] == Point2d(-7.810618, 12.188412));
			Assert::IsTrue(points[i++] == Point2d(-6.984432, 13.155775));
			Assert::IsTrue(points[i++] == Point2d(-6.214240, 14.168286));
			Assert::IsTrue(points[i++] == Point2d(-5.502503, 15.222708));
			Assert::IsTrue(points[i++] == Point2d(-4.851498, 16.315670));
			Assert::IsTrue(points[i++] == Point2d(-4.263305, 17.443679));
			Assert::IsTrue(points[i++] == Point2d(-3.739804, 18.603127));
			Assert::IsTrue(points[i++] == Point2d(-3.282669, 19.790310));
			Assert::IsTrue(points[i++] == Point2d(-2.893361, 21.001431));
			Assert::IsTrue(points[i++] == Point2d(-2.573126, 22.232619));
			Assert::IsTrue(points[i++] == Point2d(-2.322985, 23.479937));
			Assert::IsTrue(points[i++] == Point2d(-2.143741, 24.739400));
			Assert::IsTrue(points[i++] == Point2d(-2.035964, 26.006980));
			Assert::IsTrue(points[i++] == Point2d(-2.000000, 27.278625));
			Assert::IsTrue(points[i++] == Point2d(-2.000000, 89.099500));
			Assert::IsTrue(points[i++] == Point2d(-2.030436, 89.879106));
			Assert::IsTrue(points[i++] == Point2d(-2.121557, 90.653967));
			Assert::IsTrue(points[i++] == Point2d(-2.272810, 91.419366));
			Assert::IsTrue(points[i++] == Point2d(-2.483274, 92.170643));
			Assert::IsTrue(points[i++] == Point2d(-2.751667, 92.903226));
			Assert::IsTrue(points[i++] == Point2d(-3.076356, 93.612655));
			Assert::IsTrue(points[i++] == Point2d(-3.455364, 94.294612));
			Assert::IsTrue(points[i++] == Point2d(-3.886384, 94.944946));
			Assert::IsTrue(points[i++] == Point2d(-4.366793, 95.559698));
			Assert::IsTrue(points[i++] == Point2d(-4.893667, 96.135125));
			Assert::IsTrue(points[i++] == Point2d(-5.463797, 96.667726));
			Assert::IsTrue(points[i++] == Point2d(-6.073714, 97.154259));
			Assert::IsTrue(points[i++] == Point2d(-6.719705, 97.591761));
			Assert::IsTrue(points[i++] == Point2d(-7.397838, 97.977569));
			Assert::IsTrue(points[i++] == Point2d(-8.103985, 98.309335));
			Assert::IsTrue(points[i++] == Point2d(-8.833848, 98.585041));
			Assert::IsTrue(points[i++] == Point2d(-9.582983, 98.803006));
			Assert::IsTrue(points[i++] == Point2d(-10.346831, 98.961905));
			Assert::IsTrue(points[i++] == Point2d(-11.120742, 99.060770));
			Assert::IsTrue(points[i++] == Point2d(-11.900005, 99.099000));
			Assert::IsTrue(points[i++] == Point2d(-13.000000, 105.000000));
			Assert::IsTrue(points[i++] == Point2d(-62.000000, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(-63.000000, 108.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 108.000000));
			Assert::IsTrue(points[i++] == Point2d(63.000000, 108.000000));
			Assert::IsTrue(points[i++] == Point2d(62.000000, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000, 105.000000));
			Assert::IsTrue(points[i++] == Point2d(11.900005, 99.099000));
			Assert::IsTrue(points[i++] == Point2d(11.120742, 99.060770));
			Assert::IsTrue(points[i++] == Point2d(10.346831, 98.961905));
			Assert::IsTrue(points[i++] == Point2d(9.582983, 98.803006));
			Assert::IsTrue(points[i++] == Point2d(8.833848, 98.585041));
			Assert::IsTrue(points[i++] == Point2d(8.103985, 98.309335));
			Assert::IsTrue(points[i++] == Point2d(7.397838, 97.977569));
			Assert::IsTrue(points[i++] == Point2d(6.719705, 97.591761));
			Assert::IsTrue(points[i++] == Point2d(6.073714, 97.154259));
			Assert::IsTrue(points[i++] == Point2d(5.463797, 96.667726));
			Assert::IsTrue(points[i++] == Point2d(4.893667, 96.135125));
			Assert::IsTrue(points[i++] == Point2d(4.366793, 95.559698));
			Assert::IsTrue(points[i++] == Point2d(3.886384, 94.944946));
			Assert::IsTrue(points[i++] == Point2d(3.455364, 94.294612));
			Assert::IsTrue(points[i++] == Point2d(3.076356, 93.612655));
			Assert::IsTrue(points[i++] == Point2d(2.751667, 92.903226));
			Assert::IsTrue(points[i++] == Point2d(2.483274, 92.170643));
			Assert::IsTrue(points[i++] == Point2d(2.272810, 91.419366));
			Assert::IsTrue(points[i++] == Point2d(2.121557, 90.653967));
			Assert::IsTrue(points[i++] == Point2d(2.030436, 89.879106));
			Assert::IsTrue(points[i++] == Point2d(2.000000, 89.099500));
			Assert::IsTrue(points[i++] == Point2d(2.000000, 27.278625));
			Assert::IsTrue(points[i++] == Point2d(2.035964, 26.006980));
			Assert::IsTrue(points[i++] == Point2d(2.143741, 24.739400));
			Assert::IsTrue(points[i++] == Point2d(2.322985, 23.479937));
			Assert::IsTrue(points[i++] == Point2d(2.573126, 22.232619));
			Assert::IsTrue(points[i++] == Point2d(2.893361, 21.001431));
			Assert::IsTrue(points[i++] == Point2d(3.282669, 19.790310));
			Assert::IsTrue(points[i++] == Point2d(3.739804, 18.603127));
			Assert::IsTrue(points[i++] == Point2d(4.263305, 17.443679));
			Assert::IsTrue(points[i++] == Point2d(4.851498, 16.315670));
			Assert::IsTrue(points[i++] == Point2d(5.502503, 15.222708));
			Assert::IsTrue(points[i++] == Point2d(6.214240, 14.168286));
			Assert::IsTrue(points[i++] == Point2d(6.984432, 13.155775));
			Assert::IsTrue(points[i++] == Point2d(7.810618, 12.188412));
			Assert::IsTrue(points[i++] == Point2d(8.690156, 11.269289));
			Assert::IsTrue(points[i++] == Point2d(9.620235, 10.401345));
			Assert::IsTrue(points[i++] == Point2d(10.597881, 9.587353));
			Assert::IsTrue(points[i++] == Point2d(11.619970, 8.829917));
			Assert::IsTrue(points[i++] == Point2d(12.683233, 8.131457));
			Assert::IsTrue(points[i++] == Point2d(13.784272, 7.494207));
			Assert::IsTrue(points[i++] == Point2d(14.919567, 6.920204));
			Assert::IsTrue(points[i++] == Point2d(19.000000, 5.000000));
			Assert::IsTrue(points[i++] == Point2d(19.000000, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(18.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);

			Assert::AreEqual(beamClone.GetW1(), 26.);
			Assert::AreEqual(beamClone.GetW2(), 49.);
			Assert::AreEqual(beamClone.GetW3(), 1.);
			Assert::AreEqual(beamClone.GetW4(), 38.);
			Assert::AreEqual(beamClone.GetD1(), 2.);
			Assert::AreEqual(beamClone.GetD2(), 6.);
			Assert::AreEqual(beamClone.GetD3(), 9.);
			Assert::AreEqual(beamClone.GetD4(), 3.);
			Assert::AreEqual(beamClone.GetD5(), 13.);
			Assert::AreEqual(beamClone.GetD6(), 5.);
			Assert::AreEqual(beamClone.GetH(), 108.);
			Assert::AreEqual(beamClone.GetT(), 4.);
			Assert::AreEqual(beamClone.GetR1(), 10.);
			Assert::AreEqual(beamClone.GetR2(), 22.5);
			Assert::AreEqual(beamClone.GetC1(), 1.0);
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
			Assert::IsTrue(points.size() == 52);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.000000000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.000000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-14.919566682577722, 6.9202039140810676));
			Assert::IsTrue(points[i++] == Point2d(-13.784271817127612, 7.4942073729084058));
			Assert::IsTrue(points[i++] == Point2d(-12.683232873045956, 8.1314574383290577));
			Assert::IsTrue(points[i++] == Point2d(-11.619969639454686, 8.8299169563801492));
			Assert::IsTrue(points[i++] == Point2d(-10.597881144502185, 9.5873530993974114));
			Assert::IsTrue(points[i++] == Point2d(-9.6202347893876414, 10.401344503893995));
			Assert::IsTrue(points[i++] == Point2d(-8.6901559031689644, 11.269289011148551));
			Assert::IsTrue(points[i++] == Point2d(-7.8106177517455109, 12.188411985757359));
			Assert::IsTrue(points[i++] == Point2d(-6.9844320329544836, 13.155775185558154));
			Assert::IsTrue(points[i++] == Point2d(-6.2142398881663432, 14.168286154570225));
			Assert::IsTrue(points[i++] == Point2d(-5.5025034591133419, 15.222708108923422));
			Assert::IsTrue(points[i++] == Point2d(-4.8514980169420348, 16.315670284173059));
			Assert::IsTrue(points[i++] == Point2d(-4.2633046886516048, 17.443678710922502));
			Assert::IsTrue(points[i++] == Point2d(-3.7398038041701298, 18.603127384305779));
			Assert::IsTrue(points[i++] == Point2d(-3.2826688853366406, 19.790309791624125));
			Assert::IsTrue(points[i++] == Point2d(-2.8933612960049970, 21.001430761284837));
			Assert::IsTrue(points[i++] == Point2d(-2.5731255703721096, 22.232618595163775));
			Assert::IsTrue(points[i++] == Point2d(-2.3229854344647514, 23.479937445607128));
			Assert::IsTrue(points[i++] == Point2d(-2.1437405335035145, 24.739399897505763));
			Assert::IsTrue(points[i++] == Point2d(-2.0359638756058480, 26.006979715219636));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 27.278624713603435));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 27.278624713603435));
			Assert::IsTrue(points[i++] == Point2d(2.0359638756058480, 26.006979715219636));
			Assert::IsTrue(points[i++] == Point2d(2.1437405335035145, 24.739399897505763));
			Assert::IsTrue(points[i++] == Point2d(2.3229854344647514, 23.479937445607128));
			Assert::IsTrue(points[i++] == Point2d(2.5731255703721096, 22.232618595163775));
			Assert::IsTrue(points[i++] == Point2d(2.8933612960049970, 21.001430761284837));
			Assert::IsTrue(points[i++] == Point2d(3.2826688853366406, 19.790309791624125));
			Assert::IsTrue(points[i++] == Point2d(3.7398038041701298, 18.603127384305779));
			Assert::IsTrue(points[i++] == Point2d(4.2633046886516048, 17.443678710922502));
			Assert::IsTrue(points[i++] == Point2d(4.8514980169420348, 16.315670284173059));
			Assert::IsTrue(points[i++] == Point2d(5.5025034591133419, 15.222708108923422));
			Assert::IsTrue(points[i++] == Point2d(6.2142398881663432, 14.168286154570225));
			Assert::IsTrue(points[i++] == Point2d(6.9844320329544836, 13.155775185558154));
			Assert::IsTrue(points[i++] == Point2d(7.8106177517455109, 12.188411985757359));
			Assert::IsTrue(points[i++] == Point2d(8.6901559031689644, 11.269289011148551));
			Assert::IsTrue(points[i++] == Point2d(9.6202347893876414, 10.401344503893995));
			Assert::IsTrue(points[i++] == Point2d(10.597881144502185, 9.5873530993974114));
			Assert::IsTrue(points[i++] == Point2d(11.619969639454686, 8.8299169563801492));
			Assert::IsTrue(points[i++] == Point2d(12.683232873045956, 8.1314574383290577));
			Assert::IsTrue(points[i++] == Point2d(13.784271817127612, 7.4942073729084058));
			Assert::IsTrue(points[i++] == Point2d(14.919566682577722, 6.9202039140810676));
			Assert::IsTrue(points[i++] == Point2d(19.000000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(19.000000000000000, 1.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 51);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(-2.0304356263457279, 89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(-2.1215572399126987, 90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(-2.2728101720244052, 91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(-2.4832737271357566, 92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(-2.7516667872222023, 92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(-3.0763556101056242, 93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(-3.4553637742476404, 94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(-3.8863842094750911, 94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(-4.3667932404051850, 95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(-4.8936665570862186, 96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(-5.4637970156385878, 96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(-6.0737141605413276, 97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(-6.7197053497296153, 97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(-7.3978383539120962, 97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(-8.1039852925431752, 98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(-8.8338477607489736, 98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(-9.5829829942562785, 98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(-10.346830913055204, 98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(-11.120741879177437, 99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(-11.900004999625033, 99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-62.000000000000000, 106.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-63.000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(63.000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(62.000000000000000, 106.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.900004999625033, 99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(11.120741879177437, 99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(10.346830913055204, 98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(9.5829829942562785, 98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(8.8338477607489736, 98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(8.1039852925431752, 98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(7.3978383539120962, 97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(6.7197053497296153, 97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(6.0737141605413276, 97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(5.4637970156385878, 96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(4.8936665570862186, 96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(4.3667932404051850, 95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(3.8863842094750911, 94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(3.4553637742476404, 94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(3.0763556101056242, 93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(2.7516667872222023, 92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(2.4832737271357566, 92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(2.2728101720244052, 91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(2.1215572399126987, 90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(2.0304356263457279, 89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 50.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-5000, 50, 5000, 10000);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 51);
			int i = 0;

			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000000, 89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(-2.0304356263457279, 89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(-2.1215572399126987, 90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(-2.2728101720244052, 91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(-2.4832737271357566, 92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(-2.7516667872222023, 92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(-3.0763556101056242, 93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(-3.4553637742476404, 94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(-3.8863842094750911, 94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(-4.3667932404051850, 95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(-4.8936665570862186, 96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(-5.4637970156385878, 96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(-6.0737141605413276, 97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(-6.7197053497296153, 97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(-7.3978383539120962, 97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(-8.1039852925431752, 98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(-8.8338477607489736, 98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(-9.5829829942562785, 98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(-10.346830913055204, 98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(-11.120741879177437, 99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(-11.900004999625033, 99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-62.000000000000000, 106.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-63.000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(63.000000000000000, 108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(62.000000000000000, 106.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.900004999625033, 99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(11.120741879177437, 99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(10.346830913055204, 98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(9.5829829942562785, 98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(8.8338477607489736, 98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(8.1039852925431752, 98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(7.3978383539120962, 97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(6.7197053497296153, 97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(6.0737141605413276, 97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(5.4637970156385878, 96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(4.8936665570862186, 96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(4.3667932404051850, 95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(3.8863842094750911, 94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(3.4553637742476404, 94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(3.0763556101056242, 93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(2.7516667872222023, 92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(2.4832737271357566, 92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(2.2728101720244052, 91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(2.1215572399126987, 90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(2.0304356263457279, 89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(2.0000000000000000, 50.000000000000000));
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
			Assert::IsTrue(points.size() == 99);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(82.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.000000000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(85.080433317422276, 106.92020391408107));
			Assert::IsTrue(points[i++] == Point2d(86.215728182872382, 107.49420737290841));
			Assert::IsTrue(points[i++] == Point2d(87.316767126954048, 108.13145743832905));
			Assert::IsTrue(points[i++] == Point2d(88.380030360545319, 108.82991695638015));
			Assert::IsTrue(points[i++] == Point2d(89.402118855497818, 109.58735309939740));
			Assert::IsTrue(points[i++] == Point2d(90.379765210612362, 110.40134450389399));
			Assert::IsTrue(points[i++] == Point2d(91.309844096831029, 111.26928901114854));
			Assert::IsTrue(points[i++] == Point2d(92.189382248254489, 112.18841198575736));
			Assert::IsTrue(points[i++] == Point2d(93.015567967045513, 113.15577518555816));
			Assert::IsTrue(points[i++] == Point2d(93.785760111833653, 114.16828615457023));
			Assert::IsTrue(points[i++] == Point2d(94.497496540886658, 115.22270810892343));
			Assert::IsTrue(points[i++] == Point2d(95.148501983057969, 116.31567028417305));
			Assert::IsTrue(points[i++] == Point2d(95.736695311348399, 117.44367871092250));
			Assert::IsTrue(points[i++] == Point2d(96.260196195829877, 118.60312738430578));
			Assert::IsTrue(points[i++] == Point2d(96.717331114663352, 119.79030979162413));
			Assert::IsTrue(points[i++] == Point2d(97.106638703995003, 121.00143076128484));
			Assert::IsTrue(points[i++] == Point2d(97.426874429627887, 122.23261859516377));
			Assert::IsTrue(points[i++] == Point2d(97.677014565535245, 123.47993744560713));
			Assert::IsTrue(points[i++] == Point2d(97.856259466496482, 124.73939989750576));
			Assert::IsTrue(points[i++] == Point2d(97.964036124394156, 126.00697971521964));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 127.27862471360343));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 189.09950001249939));
			Assert::IsTrue(points[i++] == Point2d(97.969564373654265, 189.87910645139243));
			Assert::IsTrue(points[i++] == Point2d(97.878442760087296, 190.65396732823129));
			Assert::IsTrue(points[i++] == Point2d(97.727189827975593, 191.41936596779252));
			Assert::IsTrue(points[i++] == Point2d(97.516726272864247, 192.17064329267623));
			Assert::IsTrue(points[i++] == Point2d(97.248333212777794, 192.90322618369402));
			Assert::IsTrue(points[i++] == Point2d(96.923644389894378, 193.61265531701821));
			Assert::IsTrue(points[i++] == Point2d(96.544636225752356, 194.29461230864473));
			Assert::IsTrue(points[i++] == Point2d(96.113615790524904, 194.94494600093731));
			Assert::IsTrue(points[i++] == Point2d(95.633206759594813, 195.55969773124423));
			Assert::IsTrue(points[i++] == Point2d(95.106333442913780, 196.13512542877368));
			Assert::IsTrue(points[i++] == Point2d(94.536202984361410, 196.66772639304753));
			Assert::IsTrue(points[i++] == Point2d(93.926285839458671, 197.15425861527771));
			Assert::IsTrue(points[i++] == Point2d(93.280294650270378, 197.59176051288006));
			Assert::IsTrue(points[i++] == Point2d(92.602161646087907, 197.97756895699837));
			Assert::IsTrue(points[i++] == Point2d(91.896014707456828, 198.30933548330341));
			Assert::IsTrue(points[i++] == Point2d(91.166152239251034, 198.58504058738944));
			Assert::IsTrue(points[i++] == Point2d(90.417017005743716, 198.80300601775053));
			Assert::IsTrue(points[i++] == Point2d(89.653169086944800, 198.96190499150779));
			Assert::IsTrue(points[i++] == Point2d(88.879258120822556, 199.06077027070279));
			Assert::IsTrue(points[i++] == Point2d(88.099995000374975, 199.09900004999625));
			Assert::IsTrue(points[i++] == Point2d(87.000000000000000, 205.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(38.000000000000000, 206.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(37.000000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(163.00000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(162.00000000000000, 206.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(113.00000000000000, 205.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.90000499962503, 199.09900004999625));
			Assert::IsTrue(points[i++] == Point2d(111.12074187917744, 199.06077027070279));
			Assert::IsTrue(points[i++] == Point2d(110.34683091305520, 198.96190499150779));
			Assert::IsTrue(points[i++] == Point2d(109.58298299425628, 198.80300601775053));
			Assert::IsTrue(points[i++] == Point2d(108.83384776074897, 198.58504058738944));
			Assert::IsTrue(points[i++] == Point2d(108.10398529254317, 198.30933548330341));
			Assert::IsTrue(points[i++] == Point2d(107.39783835391209, 197.97756895699837));
			Assert::IsTrue(points[i++] == Point2d(106.71970534972962, 197.59176051288006));
			Assert::IsTrue(points[i++] == Point2d(106.07371416054133, 197.15425861527771));
			Assert::IsTrue(points[i++] == Point2d(105.46379701563859, 196.66772639304753));
			Assert::IsTrue(points[i++] == Point2d(104.89366655708622, 196.13512542877368));
			Assert::IsTrue(points[i++] == Point2d(104.36679324040519, 195.55969773124423));
			Assert::IsTrue(points[i++] == Point2d(103.88638420947510, 194.94494600093731));
			Assert::IsTrue(points[i++] == Point2d(103.45536377424764, 194.29461230864473));
			Assert::IsTrue(points[i++] == Point2d(103.07635561010562, 193.61265531701821));
			Assert::IsTrue(points[i++] == Point2d(102.75166678722221, 192.90322618369402));
			Assert::IsTrue(points[i++] == Point2d(102.48327372713575, 192.17064329267623));
			Assert::IsTrue(points[i++] == Point2d(102.27281017202441, 191.41936596779252));
			Assert::IsTrue(points[i++] == Point2d(102.12155723991270, 190.65396732823129));
			Assert::IsTrue(points[i++] == Point2d(102.03043562634574, 189.87910645139243));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 189.09950001249939));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 127.27862471360343));
			Assert::IsTrue(points[i++] == Point2d(102.03596387560584, 126.00697971521964));
			Assert::IsTrue(points[i++] == Point2d(102.14374053350352, 124.73939989750576));
			Assert::IsTrue(points[i++] == Point2d(102.32298543446475, 123.47993744560713));
			Assert::IsTrue(points[i++] == Point2d(102.57312557037211, 122.23261859516377));
			Assert::IsTrue(points[i++] == Point2d(102.89336129600500, 121.00143076128484));
			Assert::IsTrue(points[i++] == Point2d(103.28266888533665, 119.79030979162413));
			Assert::IsTrue(points[i++] == Point2d(103.73980380417012, 118.60312738430578));
			Assert::IsTrue(points[i++] == Point2d(104.26330468865160, 117.44367871092250));
			Assert::IsTrue(points[i++] == Point2d(104.85149801694203, 116.31567028417305));
			Assert::IsTrue(points[i++] == Point2d(105.50250345911334, 115.22270810892343));
			Assert::IsTrue(points[i++] == Point2d(106.21423988816635, 114.16828615457023));
			Assert::IsTrue(points[i++] == Point2d(106.98443203295449, 113.15577518555816));
			Assert::IsTrue(points[i++] == Point2d(107.81061775174551, 112.18841198575736));
			Assert::IsTrue(points[i++] == Point2d(108.69015590316897, 111.26928901114854));
			Assert::IsTrue(points[i++] == Point2d(109.62023478938764, 110.40134450389399));
			Assert::IsTrue(points[i++] == Point2d(110.59788114450218, 109.58735309939740));
			Assert::IsTrue(points[i++] == Point2d(111.61996963945468, 108.82991695638015));
			Assert::IsTrue(points[i++] == Point2d(112.68323287304595, 108.13145743832905));
			Assert::IsTrue(points[i++] == Point2d(113.78427181712762, 107.49420737290841));
			Assert::IsTrue(points[i++] == Point2d(114.91956668257772, 106.92020391408107));
			Assert::IsTrue(points[i++] == Point2d(119.00000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(119.00000000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(118.00000000000000, 100.00000000000000));
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
			Assert::IsTrue(points.size() == 99);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(82.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.000000000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(81.000000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(85.080433317422276, 106.92020391408107));
			Assert::IsTrue(points[i++] == Point2d(86.215728182872382, 107.49420737290841));
			Assert::IsTrue(points[i++] == Point2d(87.316767126954048, 108.13145743832905));
			Assert::IsTrue(points[i++] == Point2d(88.380030360545319, 108.82991695638015));
			Assert::IsTrue(points[i++] == Point2d(89.402118855497818, 109.58735309939740));
			Assert::IsTrue(points[i++] == Point2d(90.379765210612362, 110.40134450389399));
			Assert::IsTrue(points[i++] == Point2d(91.309844096831029, 111.26928901114854));
			Assert::IsTrue(points[i++] == Point2d(92.189382248254489, 112.18841198575736));
			Assert::IsTrue(points[i++] == Point2d(93.015567967045513, 113.15577518555816));
			Assert::IsTrue(points[i++] == Point2d(93.785760111833653, 114.16828615457023));
			Assert::IsTrue(points[i++] == Point2d(94.497496540886658, 115.22270810892343));
			Assert::IsTrue(points[i++] == Point2d(95.148501983057969, 116.31567028417305));
			Assert::IsTrue(points[i++] == Point2d(95.736695311348399, 117.44367871092250));
			Assert::IsTrue(points[i++] == Point2d(96.260196195829877, 118.60312738430578));
			Assert::IsTrue(points[i++] == Point2d(96.717331114663352, 119.79030979162413));
			Assert::IsTrue(points[i++] == Point2d(97.106638703995003, 121.00143076128484));
			Assert::IsTrue(points[i++] == Point2d(97.426874429627887, 122.23261859516377));
			Assert::IsTrue(points[i++] == Point2d(97.677014565535245, 123.47993744560713));
			Assert::IsTrue(points[i++] == Point2d(97.856259466496482, 124.73939989750576));
			Assert::IsTrue(points[i++] == Point2d(97.964036124394156, 126.00697971521964));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 127.27862471360343));
			Assert::IsTrue(points[i++] == Point2d(98.000000000000000, 189.09950001249939));
			Assert::IsTrue(points[i++] == Point2d(97.969564373654265, 189.87910645139243));
			Assert::IsTrue(points[i++] == Point2d(97.878442760087296, 190.65396732823129));
			Assert::IsTrue(points[i++] == Point2d(97.727189827975593, 191.41936596779252));
			Assert::IsTrue(points[i++] == Point2d(97.516726272864247, 192.17064329267623));
			Assert::IsTrue(points[i++] == Point2d(97.248333212777794, 192.90322618369402));
			Assert::IsTrue(points[i++] == Point2d(96.923644389894378, 193.61265531701821));
			Assert::IsTrue(points[i++] == Point2d(96.544636225752356, 194.29461230864473));
			Assert::IsTrue(points[i++] == Point2d(96.113615790524904, 194.94494600093731));
			Assert::IsTrue(points[i++] == Point2d(95.633206759594813, 195.55969773124423));
			Assert::IsTrue(points[i++] == Point2d(95.106333442913780, 196.13512542877368));
			Assert::IsTrue(points[i++] == Point2d(94.536202984361410, 196.66772639304753));
			Assert::IsTrue(points[i++] == Point2d(93.926285839458671, 197.15425861527771));
			Assert::IsTrue(points[i++] == Point2d(93.280294650270378, 197.59176051288006));
			Assert::IsTrue(points[i++] == Point2d(92.602161646087907, 197.97756895699837));
			Assert::IsTrue(points[i++] == Point2d(91.896014707456828, 198.30933548330341));
			Assert::IsTrue(points[i++] == Point2d(91.166152239251034, 198.58504058738944));
			Assert::IsTrue(points[i++] == Point2d(90.417017005743716, 198.80300601775053));
			Assert::IsTrue(points[i++] == Point2d(89.653169086944800, 198.96190499150779));
			Assert::IsTrue(points[i++] == Point2d(88.879258120822556, 199.06077027070279));
			Assert::IsTrue(points[i++] == Point2d(88.099995000374975, 199.09900004999625));
			Assert::IsTrue(points[i++] == Point2d(87.000000000000000, 205.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(38.000000000000000, 206.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(37.000000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(163.00000000000000, 208.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(162.00000000000000, 206.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(113.00000000000000, 205.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.90000499962503, 199.09900004999625));
			Assert::IsTrue(points[i++] == Point2d(111.12074187917744, 199.06077027070279));
			Assert::IsTrue(points[i++] == Point2d(110.34683091305520, 198.96190499150779));
			Assert::IsTrue(points[i++] == Point2d(109.58298299425628, 198.80300601775053));
			Assert::IsTrue(points[i++] == Point2d(108.83384776074897, 198.58504058738944));
			Assert::IsTrue(points[i++] == Point2d(108.10398529254317, 198.30933548330341));
			Assert::IsTrue(points[i++] == Point2d(107.39783835391209, 197.97756895699837));
			Assert::IsTrue(points[i++] == Point2d(106.71970534972962, 197.59176051288006));
			Assert::IsTrue(points[i++] == Point2d(106.07371416054133, 197.15425861527771));
			Assert::IsTrue(points[i++] == Point2d(105.46379701563859, 196.66772639304753));
			Assert::IsTrue(points[i++] == Point2d(104.89366655708622, 196.13512542877368));
			Assert::IsTrue(points[i++] == Point2d(104.36679324040519, 195.55969773124423));
			Assert::IsTrue(points[i++] == Point2d(103.88638420947510, 194.94494600093731));
			Assert::IsTrue(points[i++] == Point2d(103.45536377424764, 194.29461230864473));
			Assert::IsTrue(points[i++] == Point2d(103.07635561010562, 193.61265531701821));
			Assert::IsTrue(points[i++] == Point2d(102.75166678722221, 192.90322618369402));
			Assert::IsTrue(points[i++] == Point2d(102.48327372713575, 192.17064329267623));
			Assert::IsTrue(points[i++] == Point2d(102.27281017202441, 191.41936596779252));
			Assert::IsTrue(points[i++] == Point2d(102.12155723991270, 190.65396732823129));
			Assert::IsTrue(points[i++] == Point2d(102.03043562634574, 189.87910645139243));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 189.09950001249939));
			Assert::IsTrue(points[i++] == Point2d(102.00000000000000, 127.27862471360343));
			Assert::IsTrue(points[i++] == Point2d(102.03596387560584, 126.00697971521964));
			Assert::IsTrue(points[i++] == Point2d(102.14374053350352, 124.73939989750576));
			Assert::IsTrue(points[i++] == Point2d(102.32298543446475, 123.47993744560713));
			Assert::IsTrue(points[i++] == Point2d(102.57312557037211, 122.23261859516377));
			Assert::IsTrue(points[i++] == Point2d(102.89336129600500, 121.00143076128484));
			Assert::IsTrue(points[i++] == Point2d(103.28266888533665, 119.79030979162413));
			Assert::IsTrue(points[i++] == Point2d(103.73980380417012, 118.60312738430578));
			Assert::IsTrue(points[i++] == Point2d(104.26330468865160, 117.44367871092250));
			Assert::IsTrue(points[i++] == Point2d(104.85149801694203, 116.31567028417305));
			Assert::IsTrue(points[i++] == Point2d(105.50250345911334, 115.22270810892343));
			Assert::IsTrue(points[i++] == Point2d(106.21423988816635, 114.16828615457023));
			Assert::IsTrue(points[i++] == Point2d(106.98443203295449, 113.15577518555816));
			Assert::IsTrue(points[i++] == Point2d(107.81061775174551, 112.18841198575736));
			Assert::IsTrue(points[i++] == Point2d(108.69015590316897, 111.26928901114854));
			Assert::IsTrue(points[i++] == Point2d(109.62023478938764, 110.40134450389399));
			Assert::IsTrue(points[i++] == Point2d(110.59788114450218, 109.58735309939740));
			Assert::IsTrue(points[i++] == Point2d(111.61996963945468, 108.82991695638015));
			Assert::IsTrue(points[i++] == Point2d(112.68323287304595, 108.13145743832905));
			Assert::IsTrue(points[i++] == Point2d(113.78427181712762, 107.49420737290841));
			Assert::IsTrue(points[i++] == Point2d(114.91956668257772, 106.92020391408107));
			Assert::IsTrue(points[i++] == Point2d(119.00000000000000, 105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(119.00000000000000, 101.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(118.00000000000000, 100.00000000000000));
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
			Assert::IsTrue(*hookPnt == Point2d(163.0, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(37.0, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(163.0, 46.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 46.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(37.0, 46.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(163.0, -8.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, -8.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(37.0, -8.0));

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
			Assert::IsTrue(points.size() == 99);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.000000000000000, -2.2043642384652358e-15));
			Assert::IsTrue(points[i++] == Point2d(19.000000000000000, -1.0000000000000022));
			Assert::IsTrue(points[i++] == Point2d(19.000000000000000, -5.0000000000000027));
			Assert::IsTrue(points[i++] == Point2d(14.919566682577722, -6.9202039140810694));
			Assert::IsTrue(points[i++] == Point2d(13.784271817127610, -7.4942073729084075));
			Assert::IsTrue(points[i++] == Point2d(12.683232873045954, -8.1314574383290594));
			Assert::IsTrue(points[i++] == Point2d(11.619969639454684, -8.8299169563801509));
			Assert::IsTrue(points[i++] == Point2d(10.597881144502184, -9.5873530993974132));
			Assert::IsTrue(points[i++] == Point2d(9.6202347893876397, -10.401344503893997));
			Assert::IsTrue(points[i++] == Point2d(8.6901559031689626, -11.269289011148553));
			Assert::IsTrue(points[i++] == Point2d(7.8106177517455091, -12.188411985757361));
			Assert::IsTrue(points[i++] == Point2d(6.9844320329544818, -13.155775185558154));
			Assert::IsTrue(points[i++] == Point2d(6.2142398881663414, -14.168286154570225));
			Assert::IsTrue(points[i++] == Point2d(5.5025034591133402, -15.222708108923422));
			Assert::IsTrue(points[i++] == Point2d(4.8514980169420330, -16.315670284173059));
			Assert::IsTrue(points[i++] == Point2d(4.2633046886516031, -17.443678710922502));
			Assert::IsTrue(points[i++] == Point2d(3.7398038041701276, -18.603127384305779));
			Assert::IsTrue(points[i++] == Point2d(3.2826688853366384, -19.790309791624125));
			Assert::IsTrue(points[i++] == Point2d(2.8933612960049944, -21.001430761284837));
			Assert::IsTrue(points[i++] == Point2d(2.5731255703721070, -22.232618595163775));
			Assert::IsTrue(points[i++] == Point2d(2.3229854344647487, -23.479937445607128));
			Assert::IsTrue(points[i++] == Point2d(2.1437405335035113, -24.739399897505763));
			Assert::IsTrue(points[i++] == Point2d(2.0359638756058449, -26.006979715219636));
			Assert::IsTrue(points[i++] == Point2d(1.9999999999999967, -27.278624713603435));
			Assert::IsTrue(points[i++] == Point2d(1.9999999999999891, -89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(2.0304356263457168, -89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(2.1215572399126876, -90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(2.2728101720243941, -91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(2.4832737271357455, -92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(2.7516667872221907, -92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(3.0763556101056126, -93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(3.4553637742476289, -94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(3.8863842094750796, -94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(4.3667932404051735, -95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(4.8936665570862070, -96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(5.4637970156385762, -96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(6.0737141605413161, -97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(6.7197053497296038, -97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(7.3978383539120838, -97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(8.1039852925431628, -98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(8.8338477607489612, -98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(9.5829829942562661, -98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(10.346830913055191, -98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(11.120741879177425, -99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(11.900004999625020, -99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(12.999999999999988, -105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(61.999999999999986, -106.00000000000001));
			Assert::IsTrue(points[i++] == Point2d(62.999999999999986, -108.00000000000001));
			Assert::IsTrue(points[i++] == Point2d(-1.3226185430791415e-14, -108.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-63.000000000000014, -107.99999999999999));
			Assert::IsTrue(points[i++] == Point2d(-62.000000000000014, -105.99999999999999));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000012, -105.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.900004999625045, -99.099000049996249));
			Assert::IsTrue(points[i++] == Point2d(-11.120741879177450, -99.060770270702776));
			Assert::IsTrue(points[i++] == Point2d(-10.346830913055216, -98.961904991507794));
			Assert::IsTrue(points[i++] == Point2d(-9.5829829942562910, -98.803006017750548));
			Assert::IsTrue(points[i++] == Point2d(-8.8338477607489860, -98.585040587389443));
			Assert::IsTrue(points[i++] == Point2d(-8.1039852925431877, -98.309335483303414));
			Assert::IsTrue(points[i++] == Point2d(-7.3978383539121086, -97.977568956998368));
			Assert::IsTrue(points[i++] == Point2d(-6.7197053497296269, -97.591760512880057));
			Assert::IsTrue(points[i++] == Point2d(-6.0737141605413392, -97.154258615277712));
			Assert::IsTrue(points[i++] == Point2d(-5.4637970156385993, -96.667726393047531));
			Assert::IsTrue(points[i++] == Point2d(-4.8936665570862301, -96.135125428773691));
			Assert::IsTrue(points[i++] == Point2d(-4.3667932404051966, -95.559697731244214));
			Assert::IsTrue(points[i++] == Point2d(-3.8863842094751027, -94.944946000937293));
			Assert::IsTrue(points[i++] == Point2d(-3.4553637742476520, -94.294612308644716));
			Assert::IsTrue(points[i++] == Point2d(-3.0763556101056357, -93.612655317018223));
			Assert::IsTrue(points[i++] == Point2d(-2.7516667872222138, -92.903226183694031));
			Assert::IsTrue(points[i++] == Point2d(-2.4832737271357677, -92.170643292676232));
			Assert::IsTrue(points[i++] == Point2d(-2.2728101720244163, -91.419365967792515));
			Assert::IsTrue(points[i++] == Point2d(-2.1215572399127098, -90.653967328231289));
			Assert::IsTrue(points[i++] == Point2d(-2.0304356263457390, -89.879106451392417));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000111, -89.099500012499377));
			Assert::IsTrue(points[i++] == Point2d(-2.0000000000000036, -27.278624713603435));
			Assert::IsTrue(points[i++] == Point2d(-2.0359638756058511, -26.006979715219636));
			Assert::IsTrue(points[i++] == Point2d(-2.1437405335035176, -24.739399897505763));
			Assert::IsTrue(points[i++] == Point2d(-2.3229854344647540, -23.479937445607128));
			Assert::IsTrue(points[i++] == Point2d(-2.5731255703721123, -22.232618595163775));
			Assert::IsTrue(points[i++] == Point2d(-2.8933612960049997, -21.001430761284837));
			Assert::IsTrue(points[i++] == Point2d(-3.2826688853366428, -19.790309791624125));
			Assert::IsTrue(points[i++] == Point2d(-3.7398038041701320, -18.603127384305779));
			Assert::IsTrue(points[i++] == Point2d(-4.2633046886516066, -17.443678710922502));
			Assert::IsTrue(points[i++] == Point2d(-4.8514980169420365, -16.315670284173059));
			Assert::IsTrue(points[i++] == Point2d(-5.5025034591133437, -15.222708108923422));
			Assert::IsTrue(points[i++] == Point2d(-6.2142398881663450, -14.168286154570225));
			Assert::IsTrue(points[i++] == Point2d(-6.9844320329544853, -13.155775185558154));
			Assert::IsTrue(points[i++] == Point2d(-7.8106177517455126, -12.188411985757357));
			Assert::IsTrue(points[i++] == Point2d(-8.6901559031689661, -11.269289011148549));
			Assert::IsTrue(points[i++] == Point2d(-9.6202347893876432, -10.401344503893993));
			Assert::IsTrue(points[i++] == Point2d(-10.597881144502187, -9.5873530993974097));
			Assert::IsTrue(points[i++] == Point2d(-11.619969639454688, -8.8299169563801474));
			Assert::IsTrue(points[i++] == Point2d(-12.683232873045958, -8.1314574383290559));
			Assert::IsTrue(points[i++] == Point2d(-13.784271817127614, -7.4942073729084040));
			Assert::IsTrue(points[i++] == Point2d(-14.919566682577722, -6.9202039140810658));
			Assert::IsTrue(points[i++] == Point2d(-19.000000000000000, -4.9999999999999973));
			Assert::IsTrue(points[i++] == Point2d(-19.000000000000000, -0.99999999999999767));
			Assert::IsTrue(points[i++] == Point2d(-18.000000000000000, 2.2043642384652358e-15));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
