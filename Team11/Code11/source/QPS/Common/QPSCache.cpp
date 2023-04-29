#include "QPSCache.h"

QPSCache::QPSCache() {}

bool QPSCache::contains(StmtIndex pred, StmtIndex suc) {
    bool predExists = containsPred(pred);
    if (!predExists) return false;

    std::unordered_set<StmtIndex> successorSet = successorTable[pred];
    bool sucExists = (std::find(successorSet.begin(), successorSet.end(), suc) != successorSet.end());
    return sucExists;
}

bool QPSCache::containsPred(StmtIndex key) {
    return (predecessorTable.find(key) != predecessorTable.end());
}

bool QPSCache::containsSuc(StmtIndex key) {
    return (successorTable.find(key) != successorTable.end());
}

void QPSCache::insert(StmtIndex pred, StmtIndex suc) {
    predecessorTable[suc].insert(pred);
    successorTable[pred].insert(suc);
}

std::unordered_set<StmtIndex> QPSCache::getLeftArgs(StmtIndex rightIndex) {
    if (predecessorTable.find(rightIndex) != predecessorTable.end()) {
        return predecessorTable[rightIndex];
    }

    return std::unordered_set<StmtIndex>();
}

std::unordered_set<StmtIndex> QPSCache::getRightArgs(StmtIndex leftIndex) {
    if (successorTable.find(leftIndex) != successorTable.end()) {
        return successorTable[leftIndex];
    }
    return std::unordered_set<StmtIndex>();
}

bool QPSCache::hasComputedPred(StmtIndex pred) {
    return computedPreds.find(pred) != computedPreds.end();
}
bool QPSCache::hasComputedSuc(StmtIndex suc) {
    return computedSucs.find(suc) != computedSucs.end();
}

void QPSCache::insertPreds(StmtIndex suc) {
    computedPreds.insert(suc);
}

void QPSCache::insertSucs(StmtIndex pred) {
    computedSucs.insert(pred);
}
