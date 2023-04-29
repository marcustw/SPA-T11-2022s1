#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/Parent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestParent)
	{
	public:
		TEST_METHOD(insertParent_getParentLeftArgLst_singleStmt)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });

			std::vector<std::string> res = parentBox.getParentLeftArgLst(2);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentLeftArgLst_multipleStmt1)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2, 3, 4 });

			std::vector<std::string> res = parentBox.getParentLeftArgLst(3);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentLeftArgLst_multipleStmt2)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });
			parentBox.insertParent(1, { 3 });
			parentBox.insertParent(1, { 4 });

			std::vector<std::string> res = parentBox.getParentLeftArgLst(3);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentLeftArgLst_stmtDoesNotExist)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });

			std::vector<std::string> res = parentBox.getParentLeftArgLst(3);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_singleStmt)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });

			std::vector<std::string> res = parentBox.getParentRightArgLst(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_repeatedStmt)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });
			parentBox.insertParent(1, { 2 });

			std::vector<std::string> res = parentBox.getParentRightArgLst(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_multipleStmt1)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });
			parentBox.insertParent(1, { 3 });
			parentBox.insertParent(1, { 4 });

			std::vector<std::string> res = parentBox.getParentRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "2", "3", "4" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_multipleStmt2)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2, 3, 4 });

			std::vector<std::string> res = parentBox.getParentRightArgLst(1);
			std::vector<std::string> expectedRes = { "2", "3", "4" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_multipleStmt3)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });
			parentBox.insertParent(1, { 5 });
			parentBox.insertParent(2, { 3 });
			parentBox.insertParent(2, { 4 });

			std::vector<std::string> res1 = parentBox.getParentRightArgLst(1);
			std::vector<std::string> res2 = parentBox.getParentRightArgLst(2);
			std::vector<std::string> expectedRes1 = { "2", "5" };
			std::vector<std::string> expectedRes2 = { "3", "4" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertParent_getParentRightArgLst_stmtDoesNotExist)
		{
			Parent parentBox = Parent();
			parentBox.insertParent(1, { 2 });

			std::vector<std::string> res = parentBox.getParentRightArgLst(3);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
