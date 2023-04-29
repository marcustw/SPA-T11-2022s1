#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/Next.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestNext)
	{
	public:
		TEST_METHOD(insertNext_getNextLeftArgLst_singleStmt)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3 });

			std::vector<std::string> res = nextBox.getNextLeftArgLst(3);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextLeftArgLst_multipleStmts)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3 });
			nextBox.insertNext(3, { 4 });

			std::vector<std::string> res = nextBox.getNextLeftArgLst(4);
			std::vector<std::string> expectedRes = { "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextLeftArgLst_containerStmt1)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3, 6 });

			std::vector<std::string> res = nextBox.getNextLeftArgLst(3);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextLeftArgLst_containerStmt2)
		{
			Next nextBox = Next();
			nextBox.insertNext(1, { 2 });
			nextBox.insertNext(1, { 5, 7 });

			std::vector<std::string> res = nextBox.getNextLeftArgLst(5);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextLeftArgLst_statementDoesNotExist)
		{
			Next nextBox = Next();

			std::vector<std::string> res = nextBox.getNextLeftArgLst(1);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextRightArgLst_singleStmt)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3 });

			std::vector<std::string> res = nextBox.getNextRightArgLst(2);
			std::vector<std::string> expectedRes = { "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextRightArgLst_multipleStmts)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3 });
			nextBox.insertNext(3, { 4 });

			std::vector<std::string> res = nextBox.getNextRightArgLst(2);
			std::vector<std::string> expectedRes = { "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextRightArgLst_containerStmt1)
		{
			Next nextBox = Next();
			nextBox.insertNext(2, { 3, 4 });

			std::vector<std::string> res = nextBox.getNextRightArgLst(2);
			std::vector<std::string> expectedRes = { "3", "4" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextRightArgLst_containerStmt2)
		{
			Next nextBox = Next();
			nextBox.insertNext(1, { 2 });
			nextBox.insertNext(1, { 5, 7 });

			std::vector<std::string> res = nextBox.getNextRightArgLst(1);
			std::vector<std::string> expectedRes = { "2", "5", "7" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertNext_getNextRightArgLst_statementDoesNotExist)
		{
			Next nextBox = Next();

			std::vector<std::string> res = nextBox.getNextRightArgLst(1);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
