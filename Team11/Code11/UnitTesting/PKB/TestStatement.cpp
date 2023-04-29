#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/Statement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStatement)
	{
	public:
		TEST_METHOD(insertStmt_getAllStmts_singleStmt)
		{
			Statement statementBox = Statement();
			statementBox.insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<std::string> res = statementBox.getAllStmts();
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertStmt_getAllStmts_multipleStmt)
		{
			Statement statementBox = Statement();
			statementBox.insertStmt(1, StatementType::ASSIGN_STMT);
			statementBox.insertStmt(3, StatementType::READ_STMT);

			std::vector<std::string> res = statementBox.getAllStmts();
			std::vector<std::string> expectedRes = { "1", "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertStmt_getStmtTypeFromStmtIdx_presentStmtIndex)
		{
			Statement statementBox = Statement();
			statementBox.insertStmt(1, StatementType::ASSIGN_STMT);

			std::vector<StatementType> res = statementBox.getStmtTypeFromStmtIdx(1);
			std::vector<StatementType> expectedRes = { StatementType::ASSIGN_STMT };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
