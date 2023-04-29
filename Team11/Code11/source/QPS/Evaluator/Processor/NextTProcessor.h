#pragma once

#include <string>
#include <stack>

#include "../../Common/QPSCache.h"
#include "../../Common/PQLCommon.h"
#include "../../../PKB/PKBQueryAPI.h"
#include "../QueryResult.h"

class NextTProcessor {
private:
    QPSCache* cache;
    PKBQueryAPI pkbQueryApi;
    void updateCache(std::string prev, std::string next);
    std::unordered_set<StmtIndex> checkCachedNextT(std::string stmtIndex);

    void searchAndPushToVectors(std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
        std::vector<std::string>* searchVector, std::string prev, std::string next);
    std::string popStack(std::stack<std::string>* stack);
    bool canFindSpecificNextTPairInStack(std::stack<std::string>* stack, std::unordered_set<std::string>* traversedSet,
        std::string prev, std::string next, std::unordered_map<std::string, bool>* visited);
    bool canFindAnyNextTPairInStack(std::stack<std::string>* stack, std::vector<std::string>* searchVector,
        std::unordered_map<std::string, bool>* visited);
    void findAllNextTPairsInStack(std::stack<std::string>* stack, std::string prev,
        std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
        std::vector<std::string>* searchVector, std::unordered_map<std::string,
        bool>* visited);

    void processCacheFetch(const std::unordered_set<StmtIndex> &cacheFetch,
        std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
        std::vector<std::string>* searchVector, std::unordered_map<std::string,
        bool>* visited, std::string prev);

    void NextTProcessor::searchAndPushCacheFetch(std::vector<std::string>* leftVector,
        std::vector<std::string>* rightVector, std::vector<std::string>* searchVector,
        std::string prev, const std::unordered_set<StmtIndex>& cacheFetch);
    void processPKBFetch(const std::string &vector, std::unordered_map<std::string,
        bool>* visited, std::stack<std::string>* stack);

public:
    explicit NextTProcessor(PKBQueryAPI pkbQueryApi);
    ~NextTProcessor();

    void findSameStmtNextTPair(std::vector<std::string>* allStmts, std::vector<std::string>* returnVector);
    void findAllNextTPairs(std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
        std::vector<std::string>* lhsStmts, std::vector<std::string>* rhsStmts,
        PQLReferenceType lhsRef, PQLReferenceType rhsRef);
    bool checkSpecificNextTPair(std::string prev, std::string next);
    bool checkForAnyNextTPair(std::vector<std::string>* lhsStmts, std::vector<std::string>* rhsStmts);
};
