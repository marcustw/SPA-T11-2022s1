#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/ParentT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestParentT)
	{
	public:
		TEST_METHOD(insertParentT_getParentTLeftArgLst_singleStmt)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });

			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(2);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTLeftArgLst_multipleStmt1)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2, 3 });
			parentTBox.insertParentT(2, { 3 });

			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(3);
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTLeftArgLst_multipleStmt2)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3 });
			parentTBox.insertParentT(1, { 3 });

			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(3);
			std::vector<std::string> expectedRes = { "2", "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTLeftArgLst_nestedStmt1)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3 });
			parentTBox.insertParentT(1, { 3 });
			parentTBox.insertParentT(3, { 4, 5 });
			parentTBox.insertParentT(2, { 4, 5 });
			parentTBox.insertParentT(1, { 4, 5 });


			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(4);
			std::vector<std::string> expectedRes = { "3", "2", "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTLeftArgLst_nestedStmt2)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3, 4 });
			parentTBox.insertParentT(1, { 3, 4 });
			parentTBox.insertParentT(4, { 5, 6, 9 });
			parentTBox.insertParentT(2, { 5, 6, 9 });
			parentTBox.insertParentT(1, { 5, 6, 9 });
			parentTBox.insertParentT(1, { 5, 6, 9 });
			parentTBox.insertParentT(6, { 7, 8 });
			parentTBox.insertParentT(4, { 7, 8 });
			parentTBox.insertParentT(2, { 7, 8 });
			parentTBox.insertParentT(1, { 7, 8 });

			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(7);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "1", "2", "4", "6" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertParentT_getParentTLeftArgLst_stmtDoesNotExist)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });

			std::vector<std::string> res = parentTBox.getParentTLeftArgLst(3);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTRightArgLst_singleStmt)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });

			std::vector<std::string> res = parentTBox.getParentTRightArgLst(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}
		TEST_METHOD(insertParentT_getParentTRightArgLst_multipleS1)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2, 3 });
			parentTBox.insertParentT(2, { 3 });

			std::vector<std::string> res1 = parentTBox.getParentTRightArgLst(1);
			std::vector<std::string> res2 = parentTBox.getParentTRightArgLst(2);
			std::vector<std::string> expectedRes1 = { "2", "3" };
			std::vector<std::string> expectedRes2 = { "3" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertParentT_getParentTRightArgLst_multipleS2)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3 });
			parentTBox.insertParentT(1, { 3 });

			std::vector<std::string> res = parentTBox.getParentTRightArgLst(1);
			std::vector<std::string> expectedRes = { "2", "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTRightArgLst_nestedStmt1)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3 });
			parentTBox.insertParentT(1, { 3 });
			parentTBox.insertParentT(3, { 4, 5 });
			parentTBox.insertParentT(2, { 4, 5 });
			parentTBox.insertParentT(1, { 4, 5 });

			std::vector<std::string> res = parentTBox.getParentTRightArgLst(2);
			std::vector<std::string> expectedRes = { "3", "4", "5" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParentT_getParentTRightArgLst_nestedStmt2)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });
			parentTBox.insertParentT(2, { 3, 4 });
			parentTBox.insertParentT(1, { 3, 4 });
			parentTBox.insertParentT(4, { 5, 6, 9 });
			parentTBox.insertParentT(2, { 5, 6, 9 });
			parentTBox.insertParentT(1, { 5, 6, 9 });
			parentTBox.insertParentT(1, { 5, 6, 9 });
			parentTBox.insertParentT(6, { 7, 8 });
			parentTBox.insertParentT(4, { 7, 8 });
			parentTBox.insertParentT(2, { 7, 8 });
			parentTBox.insertParentT(1, { 7, 8 });

			std::vector<std::string> res = parentTBox.getParentTRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "2", "3", "4", "5", "6", "7", "8", "9" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertParentT_getParentTRightArgLst_stmtDoesNotExist)
		{
			ParentT parentTBox = ParentT();
			parentTBox.insertParentT(1, { 2 });

			std::vector<std::string> res1 = parentTBox.getParentTRightArgLst(2);
			std::vector<std::string> res2 = parentTBox.getParentTRightArgLst(3);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res1);
			Assert::IsTrue(expectedRes == res2);
		}
	};
}  // namespace UnitTesting
