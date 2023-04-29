#include <string>
#include "ASTGenerator.h"
#include "ProgrammeNode.h"
#include "ProcedureNode.h"
#include "StmtLstNode.h"
#include "StmtNode.h"
#include "ExpressionNode.h"
#include "../../Common/Lexer.h"

ASTGenerator::ASTGenerator(std::string source) {
    lexer = new Lexer(source);
    stmtIndex = new int(1);
    expParser = new ExpressionParser(lexer);
}

ProgrammeNode* ASTGenerator::generate() {
    ProgrammeNode* root = extractProgrammeNode();
    return root;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ASTGenerator::getProcMapping() {
    return procMapping;
}

ProgrammeNode* ASTGenerator::extractProgrammeNode() {
    ProgrammeNode* programme = new ProgrammeNode();

    while (!lexer->reachedEnd()) {
        ProcedureNode* proc = extractProcedureNode();
        programme->addProcedure(proc);
        if (std::find(declaredProcedures.begin(), declaredProcedures.end(), proc->getProcedureName())
            != declaredProcedures.end()) {
            throw SPSemanticError(SPSemanticError::DUPLICATE_PROCEDURE_NAME);
        }
        declaredProcedures.push_back(proc->getProcedureName());
    }


    checkEveryCalledProcedureDeclared(declaredProcedures);

    return programme;
}

ProcedureNode* ASTGenerator::extractProcedureNode() {
    std::string procKeyword = lexer->getName();

    if (procKeyword != SPSyntax::PROCEDURE) throw SyntaxError(SyntaxError::PROCEDURE_KEYWORD);

    std::string procName = lexer->getName();
    ProcedureNode* procedure = new ProcedureNode(procName, *stmtIndex);
    curentParsingProcedure = procName;

    if (lexer->getNextSymbol() != SPSyntax::LEFT_CURLY) throw SyntaxError(SyntaxError::PROCEDURE_OPENING_CURLY);

    StmtLstNode* stmtLstNode = extractStmtLstNode(procName);

    if (stmtLstNode->getStmtNodes().empty()) throw SyntaxError(SyntaxError::EMPTY_PROCEDURE);

    procedure->addStmtLst(stmtLstNode);

    if (lexer->getNextSymbol() != SPSyntax::RIGHT_CURLY) throw SyntaxError(SyntaxError::PROCEDURE_CLOSING_CURLY);
    procedure->addLastStmt(*stmtIndex - 1);

    return procedure;
}

StmtLstNode* ASTGenerator::extractStmtLstNode(std::string procName) {
    StmtLstNode* stmtLst = new StmtLstNode();

    while (lexer->lookAhead() != SPSyntax::RIGHT_CURLY) {
        stmtLst->addStmt(extractStmtNode(stmtIndex, procName));
    }

    return stmtLst;
}

StmtNode* ASTGenerator::extractStmtNode(int* stmtIndex, std::string procName) {
    std::string curr_word = lexer->getName();
    std::string look_ahead = lexer->lookAhead();

    if (look_ahead == SPSyntax::EQUALS) {
        return extractAssignNode(stmtIndex, curr_word);
    } else if (curr_word == SPSyntax::READ) {
        return extractReadNode(stmtIndex);
    } else if (curr_word == SPSyntax::PRINT) {
        return extractPrintNode(stmtIndex);
    } else if (curr_word == SPSyntax::CALL) {
        return extractCallNode(stmtIndex, procName);
    } else if (curr_word == SPSyntax::WHILE) {
        return extractWhileNode(stmtIndex, procName);
    } else if (curr_word == SPSyntax::IF) {
        return extractIfNode(stmtIndex, procName);
    } else {
        throw SyntaxError(SyntaxError::SYNTAX_ERROR);
    }
}

ReadNode* ASTGenerator::extractReadNode(int* stmtIndex) {
    ReadNode* readNode = new ReadNode(*stmtIndex, expParser->extractExpressionNode(*stmtIndex));
    if (lexer->getNextSymbol() != SPSyntax::SEMICOLON) throw SyntaxError(SyntaxError::NO_SEMICOLON);
    (*stmtIndex)++;
    return readNode;
}

PrintNode* ASTGenerator::extractPrintNode(int* stmtIndex) {
    PrintNode* printNode = new PrintNode(*stmtIndex, expParser->extractExpressionNode(*stmtIndex));
    if (lexer->getNextSymbol() != SPSyntax::SEMICOLON) throw SyntaxError(SyntaxError::NO_SEMICOLON);
    (*stmtIndex)++;
    return printNode;
}

CallNode* ASTGenerator::extractCallNode(int* stmtIndex, std::string callerProcName) {
    std::string procName = lexer->getName();

    checkForCyclicProcedures(procName);

    procMapping[curentParsingProcedure].insert(procName);
    calledProcedures.push_back(procName);

    CallNode* callNode = new CallNode(*stmtIndex, procName, callerProcName);
    if (lexer->getNextSymbol() != SPSyntax::SEMICOLON) throw SyntaxError(SyntaxError::NO_SEMICOLON);
    (*stmtIndex)++;
    return callNode;
}

void ASTGenerator::processCalledProcedures(std::string currProc, std::stack<std::string>* stack) {
    if (procMapping.find(currProc) != procMapping.end()) {
        for (std::string childProc : procMapping.at(currProc)) {
            stack->push(childProc);
        }
    }
}

void ASTGenerator::checkForCyclicProcedures(std::string procName) {
    std::stack<std::string>* currStack = new std::stack<std::string>();
    std::string currProc = "";

    // Check if direct or indirect cyclic call
    // First pop will also check if it is a recursive call (procedure calling itself)
    currStack->push(procName);

    while (!currStack->empty()) {
        currProc = currStack->top();
        currStack->pop();

        if (currProc == curentParsingProcedure) throw SPSemanticError(SPSemanticError::CYCLIC_PROCEDURE_CALL);

        processCalledProcedures(currProc, currStack);
    }
}

void ASTGenerator::checkEveryCalledProcedureDeclared(const std::vector<std::string> &declaredProcs) {
    for (auto& it : calledProcedures) {
        if (std::find(declaredProcs.begin(), declaredProcs.end(), it) == declaredProcs.end()) {
            throw SPSemanticError(SPSemanticError::UNDECLARED_PROCEDURE);
        }
    }
}

AssignNode* ASTGenerator::extractAssignNode(int* stmtIndex, std::string curr_word) {
    lexer->getNextSymbol();

    AssignNode* assign = new AssignNode(*stmtIndex);

    assign->addVariable(new ExpressionNode(*stmtIndex, curr_word, ExpressionType::VARIABLE, ExpressionPos::LHS));
    assign->addExpression(expParser->extractExpressionNode(assign->getStmtIndex()));

    if (lexer->getNextSymbol() != SPSyntax::SEMICOLON) throw SyntaxError(SyntaxError::NO_SEMICOLON);

    (*stmtIndex)++;
    return assign;
}

WhileNode* ASTGenerator::extractWhileNode(int* stmtIndex, std::string procName) {
    if (lexer->getNextSymbol() != SPSyntax::LEFT_BRACKET) throw SyntaxError(SyntaxError::WHILE_OPENING_BRACKET);
    WhileNode* whileNode = new WhileNode(*stmtIndex);

    (*stmtIndex)++;
    whileNode->setCondExp(expParser->extractCondExpressionNode(whileNode->getStmtIndex()));
    if (lexer->getNextSymbol() != SPSyntax::RIGHT_BRACKET) throw SyntaxError(SyntaxError::WHILE_CLOSING_BRACKET);

    if (lexer->getNextSymbol() != SPSyntax::LEFT_CURLY) throw SyntaxError(SyntaxError::WHILE_OPENING_CURLY);

    whileNode->setStmtLst(extractStmtLstNode(procName));  // points at the first stmt inside stmtLst
    if (lexer->getNextSymbol() != SPSyntax::RIGHT_CURLY) throw SyntaxError(SyntaxError::WHILE_CLOSING_CURLY);

    whileNode->setLastStmtIndex(*stmtIndex - 1);
    return whileNode;
}

IfNode* ASTGenerator::extractIfNode(int* stmtIndex, std::string procName) {
    if (lexer->getNextSymbol() != SPSyntax::LEFT_BRACKET) throw SyntaxError(SyntaxError::IF_OPENING_BRACKET);

    IfNode* ifNode = new IfNode(*stmtIndex);

    ifNode->setCondExp(expParser->extractCondExpressionNode(*stmtIndex));

    if (lexer->getNextSymbol() != SPSyntax::RIGHT_BRACKET) throw SyntaxError(SyntaxError::IF_CLOSING_BRACKET);
    if (lexer->getName() != SPSyntax::THEN) throw SyntaxError(SyntaxError::THEN_KEYWORD);
    if (lexer->getNextSymbol() != SPSyntax::LEFT_CURLY) throw SyntaxError(SyntaxError::IF_OPENING_CURLY);

    (*stmtIndex)++;

    ifNode->setIfStmtLst(extractStmtLstNode(procName));

    if (lexer->getNextSymbol() != SPSyntax::RIGHT_CURLY) throw SyntaxError(SyntaxError::IF_CLOSING_CURLY);

    if (lexer->getName() != SPSyntax::ELSE) throw SyntaxError(SyntaxError::ELSE_KEYWORD);

    if (lexer->getNextSymbol() != SPSyntax::LEFT_CURLY) throw SyntaxError(SyntaxError::IF_OPENING_CURLY);

    ifNode->setElseStmtLst(extractStmtLstNode(procName));

    if (lexer->getNextSymbol() != SPSyntax::RIGHT_CURLY) throw SyntaxError(SyntaxError::IF_CLOSING_CURLY);

    ifNode->setLastStmtIndex(*stmtIndex - 1);

    return ifNode;
}
