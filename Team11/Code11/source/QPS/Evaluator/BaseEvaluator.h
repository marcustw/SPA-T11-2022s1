#pragma once
#ifndef BASEEVALUATOR_H
#define BASEEVALUATOR_H

#include "../../Common/SPAException.h"
#include "../../PKB/PKBQueryAPI.h"
#include "../Common/PQLCommon.h"
#include "QueryResult.h"

class BaseEvaluator {
protected:
    PKBQueryAPI pkbQueryApi;

public:
    explicit BaseEvaluator(const PKBQueryAPI& pkbQueryApi);

    virtual std::unordered_set<std::string> getSynonyms() const = 0;

    virtual QueryResult evaluate() = 0;

    virtual std::string toString() const = 0;

    virtual int priority() const = 0;
};

#endif
