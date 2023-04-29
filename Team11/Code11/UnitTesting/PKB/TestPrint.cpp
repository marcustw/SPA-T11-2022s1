#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/PrintVar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPrint)
	{
	public:
		TEST_METHOD(insertPrint_getStmtLstfromVar_singleStmt)
		{
			PrintVar printBox = PrintVar();
			printBox.insertPrint(1, "x");

			std::vector<std::string> res = printBox.getStmtLstfromVar("x");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertPrint_getStmtLstfromVar_multipleStmt)
		{
			PrintVar printBox = PrintVar();
			printBox.insertPrint(1, "x");
			printBox.insertPrint(2, "x");

			std::vector<std::string> res = printBox.getStmtLstfromVar("x");
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertPrint_getStmtLstfromVar_doesNotExists)
		{
			PrintVar printBox = PrintVar();
			printBox.insertPrint(1, "x");

			std::vector<std::string> res = printBox.getStmtLstfromVar("y");
			std::vector<std::string> expectedRes = { };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertPrint_getAllPrints_multipleStmt)
		{
			PrintVar printBox = PrintVar();
			printBox.insertPrint(1, "x");
			printBox.insertPrint(2, "y");

			std::vector<std::string> res = printBox.getAllPrints();
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
