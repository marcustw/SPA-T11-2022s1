#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/ReadVar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestRead)
	{
	public:
		TEST_METHOD(insertRead_getStmtLstfromVar_singleStmt)
		{
			ReadVar readBox = ReadVar();
			readBox.insertRead(1, "x");

			std::vector<std::string> res = readBox.getStmtLstfromVar("x");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertRead_getStmtLstfromVar_multipleStmt)
		{
			ReadVar readBox = ReadVar();
			readBox.insertRead(1, "x");
			readBox.insertRead(2, "x");

			std::vector<std::string> res = readBox.getStmtLstfromVar("x");
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertRead_getStmtLstfromVar_singleStmt_doesNotExists)
		{
			ReadVar readBox = ReadVar();
			readBox.insertRead(1, "x");

			std::vector<std::string> res = readBox.getStmtLstfromVar("y");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertRead_getVarfromStmtIdx_exists)
		{
			ReadVar readBox = ReadVar();
			readBox.insertRead(1, "x");

			std::vector<std::string> res = readBox.getVarfromStmtIdx(1);
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertRead_getAllReads_multipleStmt)
		{
			ReadVar readBox = ReadVar();
			readBox.insertRead(1, "x");
			readBox.insertRead(2, "y");

			std::vector<std::string> res = readBox.getAllReads();
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
