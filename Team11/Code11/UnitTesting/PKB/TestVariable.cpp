#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/Variable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestVariable)
	{
	public:
		TEST_METHOD(insertVariable_getAllVars_singleVar)
		{
			Variable variableBox = Variable();
			variableBox.insertVar(1, "x");

			std::vector<std::string> res = variableBox.getAllVars();
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertVariable_getAllVars_diffVar)
		{
			Variable variableBox = Variable();
			variableBox.insertVar(1, "x");
			variableBox.insertVar(2, "y");

			std::vector<std::string> res = variableBox.getAllVars();
			std::vector<std::string> expectedRes = { "x", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertVariable_getAllVars_repeatedVar)
		{
			Variable variableBox = Variable();
			variableBox.insertVar(1, "x");
			variableBox.insertVar(2, "x");

			std::vector<std::string> res = variableBox.getAllVars();
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertVariable_getVarLstFromStmtIdx_singleVar)
		{
			Variable variableBox = Variable();
			variableBox.insertVar(1, "x");

			std::vector<std::string> res = variableBox.getVarLstFromStmtIdx(1);
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertVariable_getVarLstFromStmtIdx_multipleVars)
		{
			Variable variableBox = Variable();
			variableBox.insertVar(1, "x");
			variableBox.insertVar(1, "y");

			std::vector<std::string> res = variableBox.getVarLstFromStmtIdx(1);
			std::vector<std::string> expectedRes = { "x", "y"};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
