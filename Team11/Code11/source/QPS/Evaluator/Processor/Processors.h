#pragma once

#include "AffectsProcessor.h"
#include "AffectsTProcessor.h"
#include "NextTProcessor.h"


class Processors {
private:
	AffectsProcessor* affectsProcessor;
	AffectsTProcessor* affectsTProcessor;
	NextTProcessor* nextTProcessor;
	PKBQueryAPI pkbQueryApi;

public:
	explicit Processors(PKBQueryAPI);
	~Processors();
	AffectsProcessor* getAffectsProcessor();
	AffectsTProcessor* getAffectsTProcessor();
	NextTProcessor* getNextTProcessor();
};
