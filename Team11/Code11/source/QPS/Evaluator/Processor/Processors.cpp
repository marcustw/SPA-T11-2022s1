#include "Processors.h"

Processors::Processors(PKBQueryAPI pkbQueryApi) : pkbQueryApi(pkbQueryApi) {
	Processors::affectsTProcessor = new AffectsTProcessor(new AffectsProcessor(pkbQueryApi), pkbQueryApi);
	Processors::affectsProcessor = affectsTProcessor->getAffectsProcessor();
	Processors::nextTProcessor = new NextTProcessor(pkbQueryApi);
}


AffectsProcessor* Processors::getAffectsProcessor() {
	return affectsProcessor;
}

AffectsTProcessor* Processors::getAffectsTProcessor() {
	return affectsTProcessor;
}

NextTProcessor* Processors::getNextTProcessor() {
	return nextTProcessor;
}

Processors::~Processors() {
	delete nextTProcessor;
	delete affectsProcessor;
	delete affectsTProcessor;
}
