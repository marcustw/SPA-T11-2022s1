#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/ContainerIf.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestContainerIf)
	{
	public:
		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_singleContainer_firstStmt)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(1);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "3" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_singleContainer_randomStmt)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(2);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "3" } };

			Assert::IsTrue(expectedRes == res);
		}
		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_singleContainer_lastStmt)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(3);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "3" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_ifElseContainers)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3}, {4, 7} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(4);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "7" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_innerNestedContainers)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3}, {4, 10} });
			ifContainerBox.insertIfContainer({ {5, 6}, {7, 8} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(6);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "10" }, { "5", "8" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_outerNestedContainers)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3}, {4, 10} });
			ifContainerBox.insertIfContainer({ {5, 6}, {7, 8} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(9);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "10" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_deepNestedContainers1)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {35, 39}, {40, 44} });
			ifContainerBox.insertIfContainer({ {37, 38}, {39} });
			ifContainerBox.insertIfContainer({ {41, 42}, {43} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(38);
			std::vector<std::vector<std::string>> expectedRes = { { "35", "44" }, {"37", "39"} };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeFromStmtIdx_deepNestedContainers2)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 8}, {9, 14} });
			ifContainerBox.insertIfContainer({ {2, 7}, {8} });
			ifContainerBox.insertIfContainer({ {5, 6}, {7} });
			ifContainerBox.insertIfContainer({ {10, 13}, {14} });
			ifContainerBox.insertIfContainer({ {11, 12}, {13} });


			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeFromStmtIdx(14);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "14" }, {"10", "14"} };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeClosed_rangeWithinNesting)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3}, {4, 10} });
			ifContainerBox.insertIfContainer({ {5, 6}, {7, 8} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeClosed(5, 7);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "10" }, { "5", "8" }};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getIfContainerRangeClosed_rangeOutsideNesting)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3}, {4, 10} });
			ifContainerBox.insertIfContainer({ {5, 6}, {7, 8} });

			std::vector<std::vector<std::string>> res = ifContainerBox.getIfContainerRangeClosed(7, 9);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "10" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getAllIfContainers_multipleContainers)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 3} });
			ifContainerBox.insertIfContainer({ {4, 6}, {7, 8} });

			std::vector<std::string> res = ifContainerBox.getAllIfContainers();
			std::vector<std::string> expectedRes = {"1", "4"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertIfContainer_getAllIfContainers_nestedContainers)
		{
			ContainerIf ifContainerBox = ContainerIf();
			ifContainerBox.insertIfContainer({ {1, 6} });
			ifContainerBox.insertIfContainer({ {2, 3}, {4, 6} });

			std::vector<std::string> res = ifContainerBox.getAllIfContainers();
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
