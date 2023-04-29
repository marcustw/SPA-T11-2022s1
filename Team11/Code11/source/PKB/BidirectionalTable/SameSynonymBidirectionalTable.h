#pragma once

#ifndef SAME_SYNONYM_BIDIRECTIONAL_TABLE
#define SAME_SYNONYM_BIDIRECTIONAL_TABLE

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "../../Common/Types.h"

template<typename S>
class SameSynonymBidirectionalTable {
private:
	std::unordered_map<S, std::unordered_set<S>> leftRightTable;
	std::unordered_map<S, std::unordered_set<S>> rightLeftTable;

public:
	SameSynonymBidirectionalTable();
	void insert(TableDirection tableDirection, S key, std::unordered_set<S> value);

	// returns value found in table given key
	std::unordered_set<S> contains(TableDirection tableDirection, S key);
};

template<typename S>
SameSynonymBidirectionalTable<S>::SameSynonymBidirectionalTable() {}

template<typename S>
void SameSynonymBidirectionalTable<S>::insert(TableDirection tableDirection, S key, std::unordered_set<S> value) {
	if (tableDirection == TableDirection::LEFTKEY) {
		leftRightTable[key] = value;
	} else if (tableDirection == TableDirection::RIGHTKEY) {
		rightLeftTable[key] = value;
	}
}

template<typename S>
std::unordered_set<S> SameSynonymBidirectionalTable<S>::contains(TableDirection tableDirection, S key) {
	switch (tableDirection) {
	case TableDirection::LEFTKEY:
		if (leftRightTable.find(key) != leftRightTable.end()) {
			return leftRightTable.at(key);
		}
		break;
	case TableDirection::RIGHTKEY:
		if (rightLeftTable.find(key) != rightLeftTable.end()) {
			return rightLeftTable.at(key);
		}
		break;
	default:
		break;
	}
	return std::unordered_set<S>();
}

#endif
