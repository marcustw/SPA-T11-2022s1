#include <string>
#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../source/SP/AST/ASTGenerator.h"
#include "../../source/Common/Lexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestASTGenerator)
	{
	public:
		TEST_METHOD(generate_singleStmt_singleAssign_singleConstant_success)
		{
			std::string input = "procedure procName { x = 2; }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("procName"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* stmt = stmts.at(0);
			Assert::IsTrue(typeid(*stmt) == typeid(AssignNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<AssignNode*>(stmt)->getVariable();
			Assert::AreEqual(std::string("x"), variable->getValue());
			Assert::IsTrue(typeid(variable->getExpressionType()) == typeid(ExpressionType::VARIABLE));

			// Check Constant
			ExpressionNode* expression = dynamic_cast<AssignNode*>(stmt)->getExpression();
			Assert::AreEqual(std::string("2"), expression->getValue());
			Assert::IsTrue(expression->getExpressionType() == ExpressionType::CONSTANT);
		};

		TEST_METHOD(generate_singleStmt_singleRead_success)
		{
			std::string input = "procedure readProc { read z; }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("readProc"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* stmt = stmts.at(0);
			Assert::IsTrue(typeid(*stmt) == typeid(ReadNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<ReadNode*>(stmt)->getVar();
			Assert::AreEqual(std::string("z"), variable->getValue());
			Assert::IsTrue(variable->getExpressionType() == ExpressionType::VARIABLE);
		};

		TEST_METHOD(generate_singleStmt_singlePrint_success)
		{
			std::string input = "procedure printProc { print z; }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("printProc"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* stmt = stmts.at(0);
			Assert::IsTrue(typeid(*stmt) == typeid(PrintNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<PrintNode*>(stmt)->getVar();
			Assert::AreEqual(std::string("z"), variable->getValue());
			Assert::IsTrue(variable->getExpressionType() == ExpressionType::VARIABLE);
		};

		TEST_METHOD(generate_singleStmt_singleWhile_singleCondExpr_success)
		{
			std::string input = "procedure whileProc { while (x > 1) { read z;} }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("whileProc"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* whileStmt = stmts.at(0);
			Assert::IsTrue(typeid(*whileStmt) == typeid(WhileNode));

			// Check Cond Expr
			ExpressionNode* condExpr = dynamic_cast<WhileNode*>(whileStmt)->getCondExpr();
			Assert::IsTrue(condExpr->getExpressionType() == ExpressionType::REL_EXPR);
			Assert::AreEqual(std::string(">"), condExpr->getValue());

			ExpressionNode* var = condExpr->getLeftChild();
			Assert::IsTrue(var->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("x"), var->getValue());

			ExpressionNode* constant = condExpr->getRightChild();
			Assert::IsTrue(constant->getExpressionType() == ExpressionType::CONSTANT);
			Assert::AreEqual(std::string("1"), constant->getValue());

			StmtLstNode* innerStmtLst = dynamic_cast<WhileNode*>(whileStmt)->getStmtLst();
			std::vector<StmtNode*> innerStmts = innerStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), innerStmts.size());

			// Check Stmt
			StmtNode* readStmt = innerStmts.at(0);
			Assert::IsTrue(typeid(*readStmt) == typeid(ReadNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<ReadNode*>(readStmt)->getVar();
			Assert::AreEqual(std::string("z"), variable->getValue());
			Assert::IsTrue(variable->getExpressionType() == ExpressionType::VARIABLE);
		};

		TEST_METHOD(generate_singleStmt_singleIf_singleCondExpr_success)
		{
			std::string input = "procedure ifProc { if (x > 1) then { read z;} else {print x;} }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("ifProc"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* ifStmt = stmts.at(0);
			Assert::IsTrue(typeid(*ifStmt) == typeid(IfNode));

			// Check Cond Expr
			ExpressionNode* condExpr = dynamic_cast<IfNode*>(ifStmt)->getCondExpr();
			Assert::IsTrue(condExpr->getExpressionType() == ExpressionType::REL_EXPR);
			Assert::AreEqual(std::string(">"), condExpr->getValue());

			ExpressionNode* var = condExpr->getLeftChild();
			Assert::IsTrue(var->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("x"), var->getValue());

			ExpressionNode* constant = condExpr->getRightChild();
			Assert::IsTrue(constant->getExpressionType() == ExpressionType::CONSTANT);
			Assert::AreEqual(std::string("1"), constant->getValue());

			// Check If StmtLst
			StmtLstNode* ifStmtLst = dynamic_cast<IfNode*>(ifStmt)->getIfStmtLst();
			std::vector<StmtNode*> ifInnerStmts = ifStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), ifInnerStmts.size());

			// Check Stmt
			StmtNode* readStmt = ifInnerStmts.at(0);
			Assert::IsTrue(typeid(*readStmt) == typeid(ReadNode));

			// Check Variable
			ExpressionNode* readVar = dynamic_cast<ReadNode*>(readStmt)->getVar();
			Assert::AreEqual(std::string("z"), readVar->getValue());
			Assert::IsTrue(readVar->getExpressionType() == ExpressionType::VARIABLE);

			// Check Else StmtLst
			StmtLstNode* elseStmtLst = dynamic_cast<IfNode*>(ifStmt)->getElseStmtLst();
			std::vector<StmtNode*> elseInnerStmts = elseStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), elseInnerStmts.size());

			// Check Stmt
			StmtNode* printStmt = elseInnerStmts.at(0);
			Assert::IsTrue(typeid(*printStmt) == typeid(PrintNode));

			// Check Variable
			ExpressionNode* printVar = dynamic_cast<PrintNode*>(printStmt)->getVar();
			Assert::AreEqual(std::string("x"), printVar->getValue());
			Assert::IsTrue(printVar->getExpressionType() == ExpressionType::VARIABLE);
		};

		TEST_METHOD(generate_multiStmt_unnested__success)
		{
			std::string input = "procedure multi { read x; print y; a = 2; } ";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("multi"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(3), stmts.size());

			// Check Stmt
			StmtNode* readStmt = stmts.at(0);
			Assert::IsTrue(typeid(*readStmt) == typeid(ReadNode));

			// Check Variable
			ExpressionNode* readVar = dynamic_cast<ReadNode*>(readStmt)->getVar();
			Assert::AreEqual(std::string("x"), readVar->getValue());
			Assert::IsTrue(readVar->getExpressionType() == ExpressionType::VARIABLE);

			// Check Stmt
			StmtNode* printStmt = stmts.at(1);
			Assert::IsTrue(typeid(*printStmt) == typeid(PrintNode));

			// Check Variable
			ExpressionNode* printVar = dynamic_cast<PrintNode*>(printStmt)->getVar();
			Assert::AreEqual(std::string("y"), printVar->getValue());
			Assert::IsTrue(printVar->getExpressionType() == ExpressionType::VARIABLE);

			// Check Stmt
			StmtNode* assign = stmts.at(2);
			Assert::IsTrue(typeid(*assign) == typeid(AssignNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<AssignNode*>(assign)->getVariable();
			Assert::AreEqual(std::string("a"), variable->getValue());
			Assert::IsTrue(typeid(variable->getExpressionType()) == typeid(ExpressionType::VARIABLE));

			// Check Constant
			ExpressionNode* expression = dynamic_cast<AssignNode*>(assign)->getExpression();
			Assert::AreEqual(std::string("2"), expression->getValue());
			Assert::IsTrue(expression->getExpressionType() == ExpressionType::CONSTANT);
		}

		TEST_METHOD(generate_multiStmt_singleIf_singleWhile_doubleNested_success)
		{
			std::string input = "procedure multinest { if (x > 1) then { while (x == 2) { read z; } } else {print x;} }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("multinest"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* ifStmt = stmts.at(0);
			Assert::IsTrue(typeid(*ifStmt) == typeid(IfNode));

			// Check Cond Expr
			ExpressionNode* condExpr = dynamic_cast<IfNode*>(ifStmt)->getCondExpr();
			Assert::IsTrue(condExpr->getExpressionType() == ExpressionType::REL_EXPR);
			Assert::AreEqual(std::string(">"), condExpr->getValue());

			ExpressionNode* var = condExpr->getLeftChild();
			Assert::IsTrue(var->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("x"), var->getValue());

			ExpressionNode* constant = condExpr->getRightChild();
			Assert::IsTrue(constant->getExpressionType() == ExpressionType::CONSTANT);
			Assert::AreEqual(std::string("1"), constant->getValue());

			// Check If StmtLst
			StmtLstNode* ifStmtLst = dynamic_cast<IfNode*>(ifStmt)->getIfStmtLst();
			std::vector<StmtNode*> ifInnerStmts = ifStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), ifInnerStmts.size());

			// Check Stmt
			StmtNode* whileStmt = ifInnerStmts.at(0);
			Assert::IsTrue(typeid(*whileStmt) == typeid(WhileNode));

			// Check Cond Expr
			ExpressionNode* whileCondExpr = dynamic_cast<WhileNode*>(whileStmt)->getCondExpr();
			Assert::IsTrue(whileCondExpr->getExpressionType() == ExpressionType::REL_EXPR);
			Assert::AreEqual(std::string("=="), whileCondExpr->getValue());

			ExpressionNode* whileVar = whileCondExpr->getLeftChild();
			Assert::IsTrue(whileVar->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("x"), whileVar->getValue());

			ExpressionNode* whileConstant = whileCondExpr->getRightChild();
			Assert::IsTrue(whileConstant->getExpressionType() == ExpressionType::CONSTANT);
			Assert::AreEqual(std::string("2"), whileConstant->getValue());

			StmtLstNode* whileInnerStmtLst = dynamic_cast<WhileNode*>(whileStmt)->getStmtLst();
			std::vector<StmtNode*> whileInnerStmts = whileInnerStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), whileInnerStmts.size());

			// Check Stmt
			StmtNode* readStmt = whileInnerStmts.at(0);
			Assert::IsTrue(typeid(*readStmt) == typeid(ReadNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<ReadNode*>(readStmt)->getVar();
			Assert::AreEqual(std::string("z"), variable->getValue());
			Assert::IsTrue(variable->getExpressionType() == ExpressionType::VARIABLE);


			// Check Else StmtLst
			StmtLstNode* elseStmtLst = dynamic_cast<IfNode*>(ifStmt)->getElseStmtLst();
			std::vector<StmtNode*> elseInnerStmts = elseStmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), elseInnerStmts.size());

			// Check Stmt
			StmtNode* printStmt = elseInnerStmts.at(0);
			Assert::IsTrue(typeid(*printStmt) == typeid(PrintNode));

			// Check Variable
			ExpressionNode* printVar = dynamic_cast<PrintNode*>(printStmt)->getVar();
			Assert::AreEqual(std::string("x"), printVar->getValue());
			Assert::IsTrue(printVar->getExpressionType() == ExpressionType::VARIABLE);
		};

		// Checks for left associativity
		TEST_METHOD(generate_singleStmt_singleAssign_success) {
			std::string input = "procedure leftAssociative { x6 = x1 * x2 * y1 - y2 + left * right; }";

			ASTGenerator* generator = new ASTGenerator(input);

			ProgrammeNode* root = generator->generate();

			// Check Procedure
			std::vector<ProcedureNode*> procedures = root->getProcedureNodes();
			Assert::AreEqual(size_t(1), procedures.size());
			Assert::AreEqual(std::string("leftAssociative"), procedures.at(0)->getProcedureName());

			// Check StmtLst
			StmtLstNode* stmtLst = procedures.at(0)->getStmtLstNode();
			std::vector<StmtNode*> stmts = stmtLst->getStmtNodes();
			Assert::AreEqual(size_t(1), stmts.size());

			// Check Stmt
			StmtNode* assign = stmts.at(0);
			Assert::IsTrue(typeid(*assign) == typeid(AssignNode));

			// Check Variable
			ExpressionNode* variable = dynamic_cast<AssignNode*>(assign)->getVariable();
			Assert::AreEqual(std::string("x6"), variable->getValue());
			Assert::IsTrue(typeid(variable->getExpressionType()) == typeid(ExpressionType::VARIABLE));

			// Check Assigned Expression
			ExpressionNode* expression = dynamic_cast<AssignNode*>(assign)->getExpression();
			Assert::AreEqual(std::string("+"), expression->getValue());
			Assert::IsTrue(expression->getExpressionType() == ExpressionType::EXP_OPR);

			ExpressionNode* multiplyExpr = expression->getRightChild();
			ExpressionNode* leftChild = multiplyExpr->getLeftChild();
			ExpressionNode* rightChild = multiplyExpr->getRightChild();

			Assert::AreEqual(std::string("*"), multiplyExpr->getValue());
			Assert::IsTrue(multiplyExpr->getExpressionType() == ExpressionType::TERM_OPR);
			Assert::AreEqual(std::string("left"), leftChild->getValue());
			Assert::IsTrue(leftChild->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("right"), rightChild->getValue());
			Assert::IsTrue(rightChild->getExpressionType() == ExpressionType::VARIABLE);

			expression = expression->getLeftChild();
			leftChild = expression->getLeftChild();
			rightChild = expression->getRightChild();

			Assert::AreEqual(std::string("-"), expression->getValue());
			Assert::IsTrue(expression->getExpressionType() == ExpressionType::EXP_OPR);
			Assert::AreEqual(std::string("*"), leftChild->getValue());
			Assert::IsTrue(leftChild->getExpressionType() == ExpressionType::TERM_OPR);
			Assert::AreEqual(std::string("y2"), rightChild->getValue());
			Assert::IsTrue(rightChild->getExpressionType() == ExpressionType::VARIABLE);

			expression = expression->getLeftChild();
			leftChild = expression->getLeftChild();
			rightChild = expression->getRightChild();

			Assert::AreEqual(std::string("*"), leftChild->getValue());
			Assert::IsTrue(leftChild->getExpressionType() == ExpressionType::TERM_OPR);
			Assert::AreEqual(std::string("y1"), rightChild->getValue());
			Assert::IsTrue(rightChild->getExpressionType() == ExpressionType::VARIABLE);

			expression = expression->getLeftChild();
			leftChild = expression->getLeftChild();
			rightChild = expression->getRightChild();

			Assert::AreEqual(std::string("x1"), leftChild->getValue());
			Assert::IsTrue(leftChild->getExpressionType() == ExpressionType::VARIABLE);
			Assert::AreEqual(std::string("x2"), rightChild->getValue());
			Assert::IsTrue(rightChild->getExpressionType() == ExpressionType::VARIABLE);
		};
	};
}  // namespace UnitTesting

