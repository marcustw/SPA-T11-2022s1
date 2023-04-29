#include <string>
#include <typeinfo>
#include <vector>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../source/SP/Extractors/ExtractorUtils.h"
#include "../../source/SP/AST/ExpressionNode.h"
#include "../../source/SP/AST/StmtNode.h"
#include "../../source/Common/Types.h"
#include "../../source/Common/ExpressionParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestExpressionParser)
	{
	public:
		TEST_METHOD(testExpressionParser_leftAssociative_Add)
		{
			std::string expression = "x + y + z";
			Lexer* lexer = new Lexer(expression);
			ExpressionParser exprParser = ExpressionParser(lexer);
			ExpressionNode* exprNode = exprParser.extractExpressionNode(1);

			std::string expectedExpr = "((x+y)+z)";
			std::string actualExpr = flatten(exprNode);

			Assert::AreEqual(expectedExpr, actualExpr);
		};
	};
}  // namespace UnitTesting
