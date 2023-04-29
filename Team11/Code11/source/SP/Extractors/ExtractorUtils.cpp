#include "ExtractorUtils.h"
#include "../AST/SPSyntax.h"


std::vector<int> getChildStmtIndexes(std::vector<StmtNode*> childNodes) {
    std::vector<int> childStmtIndexes = std::vector<int>();
    for (auto& i : childNodes) {
        childStmtIndexes.push_back(i->getStmtIndex());
    }
    return childStmtIndexes;
}

std::string flatten(ExpressionNode* self) {
    std::string expr = "";
    if (self == nullptr) return expr;

    ExpressionType type = self->getExpressionType();
    switch (type) {
    case ExpressionType::EXP_OPR:               // { "+", "-" };
    case ExpressionType::REL_EXPR:              // { "<", "<=", ">", ">=", "!=", "=="};
    case ExpressionType::TERM_OPR:              // { "*", "/", "%" };
    case ExpressionType::COND_EXPR:
    case ExpressionType::LOGICAL_OPR:           // { "&&", "||" };
        expr = SPSyntax::LEFT_BRACKET
            + flatten(self->getLeftChild())
            + self->getValue()
            + flatten(self->getRightChild())
            + SPSyntax::RIGHT_BRACKET;
        break;
    case ExpressionType::CONSTANT:
    case ExpressionType::VARIABLE:
        expr += flatten(self->getLeftChild()) + self->getValue() + flatten(self->getRightChild());
        break;
    }
    return expr;
}
