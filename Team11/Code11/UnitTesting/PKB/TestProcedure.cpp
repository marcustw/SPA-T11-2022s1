#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/Procedure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestProcedure)
	{
	public:
		TEST_METHOD(insertProc_getAllProcedures_singleProcedure)
		{
			Procedure procedureBox = Procedure();
			procedureBox.insertProc(1, 4, "main");

			std::vector<std::string> res = procedureBox.getAllProcedures();
			std::vector<std::string> expectedRes = { "main" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProc_getAllProcedures_multipleProcedure)
		{
			Procedure procedureBox = Procedure();
			procedureBox.insertProc(1, 4, "main");
			procedureBox.insertProc(5, 8, "add");

			std::vector<std::string> res = procedureBox.getAllProcedures();
			std::vector<std::string> expectedRes = { "main", "add"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProc_getProcedureFromStmtIdx_stmtWithinProcedure)
		{
			Procedure procedureBox = Procedure();
			procedureBox.insertProc(1, 4, "main");

			std::vector<std::string> res1 = procedureBox.getProcedureFromStmtIdx(1);
			std::vector<std::string> res2 = procedureBox.getProcedureFromStmtIdx(2);
			std::vector<std::string> expectedRes1 = { "main" };
			std::vector<std::string> expectedRes2 = { "main" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertProc_getProcedureFromStmtIdx_stmtNotWithinProcedure)
		{
			Procedure procedureBox = Procedure();
			procedureBox.insertProc(1, 4, "main");

			std::vector<std::string> res = procedureBox.getProcedureFromStmtIdx(5);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
