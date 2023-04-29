#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/ContainerWhile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestContainerWhile)
	{
	public:
		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_singleContainer_firstStmt)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 4);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(1);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "4" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_singleContainer_lastStmt)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 4);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(4);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "4" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_multipleContainers)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 4);
			whileContainerBox.insertWhileContainer(8, 11);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(9);
			std::vector<std::vector<std::string>> expectedRes = { { "8", "11" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_nestedContainers)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(3, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(5);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" } , { "3", "5" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_deepNestedContainers1)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(2, 7);
			whileContainerBox.insertWhileContainer(3, 6);
			whileContainerBox.insertWhileContainer(4, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(4);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" }, {"2", "7"}, {"3", "6"}, {"4", "5"}};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeFromStmtIdx_deepNestedContainers2)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(2, 7);
			whileContainerBox.insertWhileContainer(3, 6);
			whileContainerBox.insertWhileContainer(4, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeFromStmtIdx(6);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" }, {"2", "7"}, {"3", "6"} };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeClosed_nestedContainers)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(3, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeClosed(3, 6);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" } };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeClosed_deepNestedContainers1)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(2, 7);
			whileContainerBox.insertWhileContainer(3, 6);
			whileContainerBox.insertWhileContainer(4, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeClosed(4, 5);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" }, {"2", "7"}, {"3", "6"}, {"4", "5"} };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getWhileContainerRangeClosed_deepNestedContainers2)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 8);
			whileContainerBox.insertWhileContainer(2, 7);
			whileContainerBox.insertWhileContainer(3, 6);
			whileContainerBox.insertWhileContainer(4, 5);

			std::vector<std::vector<std::string>> res = whileContainerBox.getWhileContainerRangeClosed(4, 6);
			std::vector<std::vector<std::string>> expectedRes = { { "1", "8" }, {"2", "7"}, {"3", "6"} };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertWhileContainer_getAllWhileContainers_multipleContainers)
		{
			ContainerWhile whileContainerBox = ContainerWhile();
			whileContainerBox.insertWhileContainer(1, 4);
			whileContainerBox.insertWhileContainer(7, 9);

			std::vector<std::string> res = whileContainerBox.getAllWhileContainers();
			std::vector<std::string> expectedRes = { "1", "7" };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
