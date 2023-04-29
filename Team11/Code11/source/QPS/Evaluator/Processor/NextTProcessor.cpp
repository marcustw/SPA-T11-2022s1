#include "NextTProcessor.h"

NextTProcessor::NextTProcessor(PKBQueryAPI pkbQueryApi) : pkbQueryApi(pkbQueryApi) {
	cache = new QPSCache();
}

NextTProcessor::~NextTProcessor() {
	delete cache;
}

std::unordered_set<StmtIndex> NextTProcessor::checkCachedNextT(std::string stmtIndex) {
	return cache->getRightArgs(stoi(stmtIndex));
}

void NextTProcessor::updateCache(std::string prev, std::string next) {
	cache->insert(stoi(prev), stoi(next));
}

void NextTProcessor::searchAndPushToVectors(std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
	std::vector<std::string>* searchVector, std::string prev, std::string next) {
	if (std::find(searchVector->begin(), searchVector->end(), next) != searchVector->end()) {
		leftVector->push_back(prev);
		rightVector->push_back(next);
	}
}

std::string NextTProcessor::popStack(std::stack<std::string>* stack) {
	std::string curr = stack->top();
	stack->pop();
	return curr;
}

/** Fetches from PKb and iterates throught he result.
Visits each stmt and pushes to stack**/
void NextTProcessor::processPKBFetch(const std::string &curr, std::unordered_map<std::string,
	bool>* visited, std::stack<std::string>* stack) {
	std::vector<std::string> vector =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(curr));

	for (auto& it : vector) {
		if ((*visited)[it] != true) {
			stack->push(it);
			(*visited)[it] = true;
		}
	}
}

/** Fetches from cache and iterates through result
visits each stmt and updates the cache for prev (not the stmt it was just fetched from) **/
void NextTProcessor::processCacheFetch(const std::unordered_set<StmtIndex> &cacheFetch,
	std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
	std::vector<std::string>* searchVector, std::unordered_map<std::string,
	bool>* visited, std::string prev) {
	for (auto& it3 : cacheFetch) {
		if ((*visited)[std::to_string(it3)] != true) {
			searchAndPushToVectors(leftVector, rightVector, searchVector, prev, std::to_string(it3));
			(*visited)[std::to_string(it3)] = true;
			updateCache(prev, std::to_string(it3));
		}
	}
}
/** Traverse and populate the stack to find all NextT of prev**/
void NextTProcessor::findAllNextTPairsInStack(std::stack<std::string>* stack, std::string prev,
	std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
	std::vector<std::string>* searchVector, std::unordered_map<std::string,
	bool>* visited) {
	while (!stack->empty()) {
		std::string curr = popStack(stack);
		updateCache(prev, curr);

		searchAndPushToVectors(leftVector, rightVector, searchVector, prev, curr);

		// check if it exists on the cache
		std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(curr);

		if (cacheFetch.empty()) {
			processPKBFetch(curr, visited, stack);
		}

		processCacheFetch(cacheFetch, leftVector, rightVector, searchVector, visited, prev);
	}
}

/** Iterates through cache fetch vector
and searches for NextT Pairs **/
void NextTProcessor::searchAndPushCacheFetch(std::vector<std::string>* leftVector,
	std::vector<std::string>* rightVector, std::vector<std::string>* searchVector,
	std::string prev, const std::unordered_set<StmtIndex> &cacheFetch) {
	for (auto& it3 : cacheFetch) {
		searchAndPushToVectors(leftVector, rightVector, searchVector, prev, std::to_string(it3));
	}
}

// Finds all NextT pairs between two vectors
void NextTProcessor::findAllNextTPairs(std::vector<std::string>* leftVector, std::vector<std::string>* rightVector,
	std::vector<std::string>* lhsStmts, std::vector<std::string>* rhsStmts,
	PQLReferenceType lhsRef, PQLReferenceType rhsRef) {
	std::vector<std::string>::reverse_iterator it = lhsStmts->rbegin();

	for (std::vector<std::string>::reverse_iterator it = lhsStmts->rbegin(); it != lhsStmts->rend(); it++) {
		std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(*it);

		if (!cacheFetch.empty()) {
			searchAndPushCacheFetch(leftVector, rightVector, rhsStmts, *it, cacheFetch);
			continue;
		}

		std::vector<std::string> lhsNextVector =
			pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(*it));
		std::unordered_map<std::string, bool>* visited = new std::unordered_map<std::string, bool>();
		std::stack<std::string>* stack = new std::stack<std::string>();

		for (auto& it2 : lhsNextVector) {
			stack->push(it2);
		}

		findAllNextTPairsInStack(stack, *it, leftVector, rightVector, rhsStmts, visited);
	}
}

// Searches for Stmts that are NextT of itself
void NextTProcessor::findSameStmtNextTPair(std::vector<std::string>* allStmts, std::vector<std::string>* returnVector) {
	for (auto& it : (*allStmts)) {
		bool hasANextTRelationship = checkSpecificNextTPair(it, it);

		if (hasANextTRelationship) {
			returnVector->push_back(it);
		}
	}
}

/** Traverses and update stack to see if two specific stmts
have a nextT relationship **/
bool NextTProcessor::canFindSpecificNextTPairInStack(std::stack<std::string>* stack,
	std::unordered_set<std::string>* traversedSet, std::string prev, std::string next,
	std::unordered_map<std::string, bool>* visited) {
	while (!stack->empty()) {
		std::string curr = popStack(stack);
		traversedSet->insert(curr);

		if (curr == next) {  // found
			return true;
		}

		std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(curr);

		if (cacheFetch.empty()) {
			processPKBFetch(curr, visited, stack);
		}

		for (auto& it2 : cacheFetch) {
			if (it2 == stoi(next)) {
				return true;
			} else {
				(*visited)[std::to_string(it2)] = true;
				traversedSet->insert(curr);
			}
		}
	}
	return false;
}

// Checks if two statements have a NextT relationship
bool NextTProcessor::checkSpecificNextTPair(std::string prev, std::string next) {
	std::unordered_map<std::string, bool>* visited = new std::unordered_map<std::string, bool>();
	std::unordered_set<std::string>* traversedSet = new std::unordered_set<std::string>();

	std::stack<std::string>* stack = new std::stack<std::string>();
	std::vector<std::string> lhsNextVector =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(prev));

	std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(prev);

	/**
	Skips the traversal if prev has been cached.
	Either next is in the cache or it does not have a NextT relationship
	**/
	if (!cacheFetch.empty()) {
		bool foundInCache = std::find(cacheFetch.begin(), cacheFetch.end(), stoi(next))
			!= cacheFetch.end();
		return foundInCache;
	}

	std::vector<std::string> nextVector =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(prev));

	for (auto& it : nextVector) {
		stack->push(it);
	}

	/**
	Pair confirmed to have NextT Relationship
	Unknown if all Next* of prev has been inserted into traversedSet,
	since execution terminates early when next is found
	**/
	if (canFindSpecificNextTPairInStack(stack, traversedSet, prev, next, visited)) {
		return true;
	}

	/**
	Pair confirmed to not have NextT Relationship,
	All Next* of prev have been inserted to traversedSet
	Update cache before returning false
	**/
	for (auto& it : (*traversedSet)) {
		updateCache(prev, it);
	}
	return false;
}

// Traverses the stack to find at least one NextT Relationship
bool NextTProcessor::canFindAnyNextTPairInStack(std::stack<std::string>* stack, std::vector<std::string>* searchVector,
	std::unordered_map<std::string, bool>* visited) {
	while (!stack->empty()) {
		std::string curr = popStack(stack);

		if (std::find(searchVector->begin(), searchVector->end(), curr) != searchVector->end()) {
			return true;
		}

		std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(curr);

		if (cacheFetch.empty()) {
			processPKBFetch(curr, visited, stack);
		}

		for (auto& it3 : cacheFetch) {
			if ((*visited)[std::to_string(it3)] != true
				&& std::find(searchVector->begin(), searchVector->end(), std::to_string(it3)) != searchVector->end()) {
				return true;
			}
			(*visited)[std::to_string(it3)] = true;
		}
	}
	return false;
}

// Looks for any NextTPair between two vectors
bool NextTProcessor::checkForAnyNextTPair(std::vector<std::string>* lhsStmts,
	std::vector<std::string>* rhsStmts) {
	for (std::vector<std::string>::reverse_iterator it = lhsStmts->rbegin(); it != lhsStmts->rend(); it++) {
		std::unordered_set<StmtIndex> cacheFetch = checkCachedNextT(*it);

		for (auto& it3 : cacheFetch) {
			if (std::find(rhsStmts->begin(), rhsStmts->end(), std::to_string(it3)) != rhsStmts->end()) {
				return true;
			}
		}

		if (!cacheFetch.empty()) {
			continue;
		}

		std::vector<std::string> lhsNextVector =
			pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(*it));
		std::unordered_map<std::string, bool>* visited = new std::unordered_map<std::string, bool>();
		std::stack<std::string>* stack = new std::stack<std::string>();

		for (auto& it2 : lhsNextVector) {
			stack->push(it2);
		}

		if (canFindAnyNextTPairInStack(stack, rhsStmts, visited)) {
			return true;
		}
	}
	return false;
}
