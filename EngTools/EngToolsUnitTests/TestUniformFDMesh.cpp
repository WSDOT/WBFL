#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestUniformFDMesh)
	{
	public:
		
		TEST_METHOD(Test)
		{
			UniformFDMesh mesh(0.25, 0.25);
			mesh.HasSymmetry(true);
			Assert::IsTrue(mesh.HasSymmetry());
			mesh.AllocateElementRows(5);
			Assert::AreEqual((IndexType)5, mesh.GetElementRowCount());
			Assert::AreEqual(0.25 * 0.25, mesh.GetElementArea());

			mesh.AddElements(0, 1, 3);
			mesh.AddElements(1, 1, 3);
			mesh.AddElements(2, 0, 4);
			mesh.AddElements(3, 2, 3);
			Assert::ExpectException<std::domain_error>([&mesh]() {mesh.GetMeshArea(); });
			mesh.AddElements(4, 2, 3);
			Assert::AreEqual(2.0, mesh.GetMeshArea());

			mesh.AddElementRow(0, 4);
			Assert::AreEqual(2.5, mesh.GetMeshArea());

			Assert::AreEqual((IndexType)6, mesh.GetElementRowCount());
			Assert::AreEqual((IndexType)20, mesh.GetElementCount());
			Assert::AreEqual((IndexType)9, mesh.GetInteriorNodeCount());
			Assert::AreEqual((IndexType)3, mesh.GetMaxIntriorNodesPerRow());

			IndexType gridRowStartIdx, firstElementIdx, lastElementIdx;
			mesh.GetElementRange(0, &gridRowStartIdx, &firstElementIdx, &lastElementIdx);
			Assert::AreEqual((IndexType)1, gridRowStartIdx);
			Assert::AreEqual((IndexType)0, firstElementIdx);
			Assert::AreEqual((IndexType)2, lastElementIdx);

			mesh.GetElementRange(2, &gridRowStartIdx, &firstElementIdx, &lastElementIdx);
			Assert::AreEqual((IndexType)0, gridRowStartIdx);
			Assert::AreEqual((IndexType)6, firstElementIdx);
			Assert::AreEqual((IndexType)9, lastElementIdx);

			mesh.GetElementRange(5, &gridRowStartIdx, &firstElementIdx, &lastElementIdx);
			Assert::AreEqual((IndexType)0, gridRowStartIdx);
			Assert::AreEqual((IndexType)16, firstElementIdx);
			Assert::AreEqual((IndexType)19, lastElementIdx);

			IndexType gridRowIdx, gridRowPositionIdx;
			mesh.GetElementPosition(0, &gridRowIdx, &gridRowPositionIdx);
			Assert::AreEqual((IndexType)0, gridRowIdx);
			Assert::AreEqual((IndexType)1, gridRowPositionIdx);

			mesh.GetElementPosition(10, &gridRowIdx, &gridRowPositionIdx);
			Assert::AreEqual((IndexType)3, gridRowIdx);
			Assert::AreEqual((IndexType)2, gridRowPositionIdx);

			mesh.GetElementPosition(19, &gridRowIdx, &gridRowPositionIdx);
			Assert::AreEqual((IndexType)5, gridRowIdx);
			Assert::AreEqual((IndexType)3, gridRowPositionIdx);

			Assert::ExpectException<std::invalid_argument>([&]() {mesh.GetElementPosition(35, &gridRowIdx, &gridRowPositionIdx); });

			const auto* element = mesh.GetElement(0);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::BottomLeft]);
			Assert::AreEqual((IndexType)0, element->Node[+FDMeshElement::Corner::BottomRight]);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::TopRight]);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::TopLeft]);

			element = mesh.GetElement(10);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::BottomLeft]);
			Assert::AreEqual((IndexType)5, element->Node[+FDMeshElement::Corner::BottomRight]);
			Assert::AreEqual((IndexType)4, element->Node[+FDMeshElement::Corner::TopRight]);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::TopLeft]);

			element = mesh.GetElement(19);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::BottomLeft]);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::BottomRight]);
			Assert::AreEqual((IndexType)INVALID_INDEX, element->Node[+FDMeshElement::Corner::TopRight]);
			Assert::AreEqual((IndexType)8, element->Node[+FDMeshElement::Corner::TopLeft]);

			IndexType Nx, Ny;
			std::tie(Nx,Ny) = mesh.GetGridSize();
			Assert::AreEqual((IndexType)5, Nx);
			Assert::AreEqual((IndexType)6, Ny);
		}
	};
}
