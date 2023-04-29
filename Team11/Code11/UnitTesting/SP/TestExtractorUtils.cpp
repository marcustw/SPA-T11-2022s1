#include <string>
#include <typeinfo>
#include <vector>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../source/SP/Extractors/ExtractorUtils.h"
#include "../../source/SP/AST/ExpressionNode.h"
#include "../../source/SP/AST/StmtNode.h"
#include "../../source/Common/Types.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestExtractorUtils)
	{
	public:
		TEST_METHOD(test_getChildStmtIndexes)
		{
			StmtNode* stmtNode1 = new AssignNode(1);
			StmtNode* stmtNode2 = new AssignNode(5);
			StmtNode* stmtNode3 = new AssignNode(66);

			std::vector<StmtNode*> lstNodes = { stmtNode1, stmtNode2, stmtNode3 };
			std::vector<int> expectedRes = { 1, 5, 66 };

			Assert::IsTrue(expectedRes == getChildStmtIndexes(lstNodes));
		};

		TEST_METHOD(flatten_one_exp_operator_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);
			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);

			Assert::AreEqual(std::string("(x+1)"), flatten(exprNode));
		};

		TEST_METHOD(flatten_one_rel_operator_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, ">=", ExpressionType::REL_EXPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);
			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);

			Assert::AreEqual(std::string("(x>=1)"), flatten(exprNode));
		};

		TEST_METHOD(flatten_one_term_operator_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "*", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "y", ExpressionType::VARIABLE);
			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);

			Assert::AreEqual(std::string("(x*y)"), flatten(exprNode));
		};

		TEST_METHOD(flatten_one_logical_operator_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "||", ExpressionType::LOGICAL_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "y", ExpressionType::VARIABLE);
			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);

			Assert::AreEqual(std::string("(x||y)"), flatten(exprNode));
		};



		TEST_METHOD(flatten_multiple_operators_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* eInnerLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeLeft->addLeftChild(eInnerLeft);
			exprNodeLeft->addRightChild(eInnerRight);

			Assert::AreEqual(std::string("((x+1)/2)"), flatten(exprNode));
		};

		TEST_METHOD(flatten_bracket_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* eInnerLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "1", ExpressionType::VARIABLE);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeRight->addLeftChild(eInnerLeft);
			exprNodeRight->addRightChild(eInnerRight);

			// Expression before parsing: "2/(x+1)"
			Assert::AreEqual(std::string("(2/(x+1))"), flatten(exprNode));
		};

		TEST_METHOD(flatten_nested_bracket_twoLevels_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* eInnerLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* e2InnerLeft = new ExpressionNode(1, "y", ExpressionType::VARIABLE);
			ExpressionNode* e2InnerRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeRight->addLeftChild(eInnerLeft);
			exprNodeRight->addRightChild(eInnerRight);
			eInnerRight->addLeftChild(e2InnerLeft);
			eInnerRight->addRightChild(e2InnerRight);

			// Expression before parsing: "2/(x+(y+1))"
			Assert::AreEqual(std::string("(y+1)"), flatten(eInnerRight));
			Assert::AreEqual(std::string("(x+(y+1))"), flatten(exprNodeRight));
			Assert::AreEqual(std::string("(2/(x+(y+1)))"), flatten(exprNode));
		};

		TEST_METHOD(flatten_nested_bracket_threeLevels_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);

			ExpressionNode* eInnerLeft = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "3", ExpressionType::CONSTANT);

			ExpressionNode* e2InnerLeft = new ExpressionNode(1, "x8", ExpressionType::VARIABLE);
			ExpressionNode* e2InnerRight = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);

			ExpressionNode* e3InnerLeft = new ExpressionNode(1, "x1", ExpressionType::VARIABLE);
			ExpressionNode* e3InnerRight = new ExpressionNode(1, "2", ExpressionType::CONSTANT);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeRight->addLeftChild(eInnerLeft);
			exprNodeRight->addRightChild(eInnerRight);
			exprNodeLeft->addLeftChild(e2InnerLeft);
			exprNodeLeft->addRightChild(e2InnerRight);
			e2InnerRight->addLeftChild(e3InnerLeft);
			e2InnerRight->addRightChild(e3InnerRight);

			// Expression before parsing: "(x8 + (x1/2))/2+3"
			Assert::AreEqual(std::string("(x1/2)"), flatten(e2InnerRight));
			Assert::AreEqual(std::string("(x8+(x1/2))"), flatten(exprNodeLeft));
			Assert::AreEqual(std::string("(2+3)"), flatten(exprNodeRight));
			Assert::AreEqual(std::string("((x8+(x1/2))/(2+3))"), flatten(exprNode));
		};

		TEST_METHOD(flatten_multiple_bracket_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "/", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* eInnerLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "y", ExpressionType::VARIABLE);
			ExpressionNode* e2InnerLeft = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* e2InnerRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeLeft->addLeftChild(eInnerLeft);
			exprNodeLeft->addRightChild(eInnerRight);
			exprNodeRight->addLeftChild(e2InnerLeft);
			exprNodeRight->addRightChild(e2InnerRight);

			// Expression before parsing: "(x+y)/(2*1)"
			Assert::AreEqual(std::string("(x+y)"), flatten(exprNodeLeft));
			Assert::AreEqual(std::string("(2*1)"), flatten(exprNodeRight));
			Assert::AreEqual(std::string("((x+y)/(2*1))"), flatten(exprNode));
		};

		TEST_METHOD(flatten_long_logical_expression)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "||", ExpressionType::TERM_OPR);
			ExpressionNode* exprNodeLeft = new ExpressionNode(1, "==", ExpressionType::EXP_OPR);
			ExpressionNode* exprNodeRight = new ExpressionNode(1, "==", ExpressionType::EXP_OPR);
			ExpressionNode* eInnerLeft = new ExpressionNode(1, "x", ExpressionType::VARIABLE);
			ExpressionNode* eInnerRight = new ExpressionNode(1, "y", ExpressionType::VARIABLE);
			ExpressionNode* e2InnerLeft = new ExpressionNode(1, "2", ExpressionType::CONSTANT);
			ExpressionNode* e2InnerRight = new ExpressionNode(1, "1", ExpressionType::CONSTANT);

			exprNode->addLeftChild(exprNodeLeft);
			exprNode->addRightChild(exprNodeRight);
			exprNodeLeft->addLeftChild(eInnerLeft);
			exprNodeLeft->addRightChild(eInnerRight);
			exprNodeRight->addLeftChild(e2InnerLeft);
			exprNodeRight->addRightChild(e2InnerRight);

			// Expression before parsing: "(x+y)||(2*1)"
			Assert::AreEqual(std::string("(x==y)"), flatten(exprNodeLeft));
			Assert::AreEqual(std::string("(2==1)"), flatten(exprNodeRight));
			Assert::AreEqual(std::string("((x==y)||(2==1))"), flatten(exprNode));
		};
		TEST_METHOD(flatten_split_tree)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "-", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode2 = new ExpressionNode(1, "right", ExpressionType::VARIABLE);
			ExpressionNode* exprNode3 = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode4 = new ExpressionNode(1, "x1", ExpressionType::VARIABLE);
			ExpressionNode* exprNode5 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode6 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode7 = new ExpressionNode(1, "left", ExpressionType::VARIABLE);
			ExpressionNode* exprNode8 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode9 = new ExpressionNode(1, "y2", ExpressionType::VARIABLE);
			ExpressionNode* exprNode10 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode11 = new ExpressionNode(1, "x2", ExpressionType::VARIABLE);
			ExpressionNode* exprNode12 = new ExpressionNode(1, "y1", ExpressionType::VARIABLE);

			exprNode->addRightChild(exprNode2);
			exprNode->addLeftChild(exprNode3);
			exprNode3->addRightChild(exprNode5);
			exprNode3->addLeftChild(exprNode4);
			exprNode5->addRightChild(exprNode7);
			exprNode5->addLeftChild(exprNode6);
			exprNode6->addRightChild(exprNode9);
			exprNode6->addLeftChild(exprNode8);
			exprNode8->addRightChild(exprNode12);
			exprNode8->addLeftChild(exprNode11);

			Assert::AreEqual(std::string("((x1+(((x2*y1)*y2)*left))-right)"), flatten(exprNode));
		}
		TEST_METHOD(flatten_heavy_left_tree)
		{
			ExpressionNode* exprNode = new ExpressionNode(1, "+", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode2 = new ExpressionNode(1, "-", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode3 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode4 = new ExpressionNode(1, "left", ExpressionType::VARIABLE);
			ExpressionNode* exprNode5 = new ExpressionNode(1, "right", ExpressionType::VARIABLE);

			ExpressionNode* exprNode6 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode7 = new ExpressionNode(1, "y2", ExpressionType::VARIABLE);
			ExpressionNode* exprNode8 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode9 = new ExpressionNode(1, "y1", ExpressionType::VARIABLE);
			ExpressionNode* exprNode10 = new ExpressionNode(1, "*", ExpressionType::EXP_OPR);
			ExpressionNode* exprNode11 = new ExpressionNode(1, "x1", ExpressionType::VARIABLE);
			ExpressionNode* exprNode12 = new ExpressionNode(1, "x2", ExpressionType::VARIABLE);

			exprNode->addRightChild(exprNode3);
			exprNode->addLeftChild(exprNode2);

			exprNode2->addRightChild(exprNode7);
			exprNode2->addLeftChild(exprNode6);

			exprNode3->addRightChild(exprNode5);
			exprNode3->addLeftChild(exprNode4);

			exprNode6->addRightChild(exprNode9);
			exprNode6->addLeftChild(exprNode8);

			exprNode8->addRightChild(exprNode12);
			exprNode8->addLeftChild(exprNode11);

			Assert::AreEqual(std::string("((((x1*x2)*y1)-y2)+(left*right))"), flatten(exprNode));
		}
	};
}  // namespace UnitTesting
