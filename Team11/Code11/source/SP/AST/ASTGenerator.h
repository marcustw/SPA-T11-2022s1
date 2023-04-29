#pragma once

#include <string>
#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "../../Common/SPAException.h"
#include "../AST/TNode.h"
#include "../../Common/Lexer.h"
#include "ProgrammeNode.h"
#include "ProcedureNode.h"
#include "StmtLstNode.h"
#include "ExpressionNode.h"
#include "StmtNode.h"
#include "../../Common/ExpressionParser.h"
#include "../../Common/Types.h"
#include "SPSyntax.h"

class ASTGenerator {
public:
	explicit ASTGenerator(std::string source);
	ProgrammeNode* generate();
	std::unordered_map<std::string, std::unordered_set<std::string>> getProcMapping();

private:
	int* stmtIndex;
	ExpressionParser* expParser;
	Lexer* lexer;

	std::string curentParsingProcedure;
	std::vector<std::string> calledProcedures;
	std::vector<std::string> declaredProcedures;
	std::unordered_map<std::string, std::unordered_set<std::string>> procMapping;

	std::vector<std::string> declaredVariables;
	void processCalledProcedures(std::string currProc, std::stack<std::string>* stack);
	ProgrammeNode* extractProgrammeNode();
	ProcedureNode* extractProcedureNode();
	StmtLstNode* extractStmtLstNode(std::string procName);
	StmtNode* extractStmtNode(int* stmtIndex, std::string procName);
	ReadNode* extractReadNode(int* stmtIndex);
	PrintNode* extractPrintNode(int* stmtIndex);
	CallNode* extractCallNode(int* stmtIndex, std::string procName);
	AssignNode* extractAssignNode(int* stmtIndex, std::string var);
	WhileNode* extractWhileNode(int* stmtIndex, std::string procName);
	IfNode* extractIfNode(int* stmtIndex, std::string procName);

	void checkForCyclicProcedures(std::string procName);
	void checkEveryCalledProcedureDeclared(const std::vector<std::string> &procs);
};
