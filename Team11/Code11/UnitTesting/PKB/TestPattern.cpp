#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Pattern/Pattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPattern)
	{
	public:
		TEST_METHOD(insertStmtExpressionLst_getExpressionLstFromStmt)
		{
			Pattern patternBox = Pattern();
			patternBox.insertStmtExpressionLst(1, "1+x");
			patternBox.insertStmtExpressionLst(1, "1+x+y");

			std::vector<std::string> res = patternBox.getExpressionLstFromStmt(1);
			std::vector<std::string> expectedRes = { "1+x+y",  "1+x"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertStmtExactExpression_getStmtLstFromExactExpression)
		{
			Pattern patternBox = Pattern();
			patternBox.insertStmtExactExpression(1, "1 + x + y");

			std::vector<std::string> res = patternBox.getStmtLstFromExactExpression("1 + x + y");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
