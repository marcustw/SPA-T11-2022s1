#pragma once

#ifndef QPSCACHE_H
#define QPSCACHE_H

#include <unordered_map>
#include <unordered_set>

#include "../../Common/Types.h"


class QPSCache {
private:
    std::unordered_map<StmtIndex, std::unordered_set<StmtIndex>> predecessorTable;
    std::unordered_map<StmtIndex, std::unordered_set<StmtIndex>> successorTable;

    bool containsPred(StmtIndex pred);
    bool containsSuc(StmtIndex suc);
    std::unordered_set<StmtIndex> computedPreds;
    std::unordered_set<StmtIndex> computedSucs;

public:
    QPSCache();

    bool contains(StmtIndex pred, StmtIndex suc);
    void insert(StmtIndex pred, StmtIndex suc);

    bool hasComputedPred(StmtIndex pred);
    bool hasComputedSuc(StmtIndex suc);

    void insertPreds(StmtIndex suc);
    void insertSucs(StmtIndex pred);

    std::unordered_set<StmtIndex> getLeftArgs(StmtIndex rightIndex);
    std::unordered_set<StmtIndex> getRightArgs(StmtIndex leftIndex);
};

#endif
