#pragma once
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <stack>
#include <utility>

#include "../AST/StmtNode.h"
#include "../AST/ExpressionNode.h"

#ifndef EXTRACTORUTILS_H
#define EXTRACTORUTILS_H

std::vector<int> getChildStmtIndexes(std::vector<StmtNode*> childNodes);
std::string flatten(ExpressionNode* self);

#endif
