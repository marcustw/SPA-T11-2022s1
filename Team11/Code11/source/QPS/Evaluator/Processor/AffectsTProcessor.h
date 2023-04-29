#pragma once

#include <string>

#include "../../../PKB/PKBQueryAPI.h"
#include "../../../Common/Types.h"
#include "AffectsProcessor.h"

#ifndef AFFECTSTPROCESSOR_H
#define AFFECTSTPROCESSOR_H

class AffectsTProcessor : public AffectsProcessor {
private:
	QPSCache* affectsTcache;
	AffectsProcessor* affectsProcessor;

public:
	AffectsTProcessor(AffectsProcessor* affectsProcessor, PKBQueryAPI pkbQueryApi);
	~AffectsTProcessor();

	bool checkRs(const std::string& leftIndex, const std::string& rightIndex) override;

	AffectsProcessor* getAffectsProcessor();
};


#endif
