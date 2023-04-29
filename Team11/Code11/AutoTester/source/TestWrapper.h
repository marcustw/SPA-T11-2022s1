#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <list>
#include <fstream>
#include <sstream>

// include your other headers here
#include "AbstractWrapper.h"
#include "../../source/PKB/PKB.h"
#include "../../source/PKB/PKBQueryAPI.h"
#include "../../source/PKB/PKBStorageAPI.h"
#include "../../source/QPS/Parser/PQLParser.h"
#include "../../source/QPS/Evaluator/QPSEvaluator.h"
#include "../../source/QPS/Evaluator/QueryResult.h"
#include "../../source/QPS/Projector/ResultProjector.h"
#include "../../source/SP/AST/ASTGenerator.h"
#include "../../source/SP/Visitors/VisitorManager.h"
#include "../../source/SP/Extractors/CFG.h"
#include "../../source/SP/Extractors/CallsExtractor.h"
#include "../../source/SP/Extractors/NextExtractor.h"



class TestWrapper : public AbstractWrapper {
	
	PKB* pkb;
	PKBQueryAPI* pkbQueryAPI;
	PKBStorageAPI* pkbStorageAPI;

	std::string readFile(std::string filename);

 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
