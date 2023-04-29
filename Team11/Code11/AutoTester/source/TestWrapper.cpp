#include "AbstractWrapper.h"
#include "TestWrapper.h"

using namespace std;

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;
TestWrapper::~TestWrapper() {}

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
	pkb = new PKB();
	pkbQueryAPI = new PKBQueryAPI(pkb);
	pkbStorageAPI = new PKBStorageAPI(pkb);
}

std::string TestWrapper::readFile(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		exit(EXIT_FAILURE);  
	}
	return std::string(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>()
	);
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your Parser to do the parsing
  // ...rest of your code...

	std::string sourceCode = readFile(filename);

	ASTGenerator* astGenerator = new ASTGenerator(sourceCode);
	ProgrammeNode* prog = astGenerator->generate();

	CFG* cfg = new CFG();

	std::unordered_map<int, std::unordered_set<int>>* cfgMap = cfg->generateCFGMap(prog);

	std::unordered_map<std::string, std::unordered_set<std::string>> procMapping = astGenerator->getProcMapping();

	CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *pkbStorageAPI);
	NextExtractor* nextExtractor = new NextExtractor(cfgMap, *pkbStorageAPI);

	VisitorManager visitorManager = VisitorManager(prog, *pkbStorageAPI);
	visitorManager.initialiseVisitors();

	callsExtractor->extractCalls();
	callsExtractor->extractCallsT();
	nextExtractor->extractNext();

	pkbStorageAPI->updateAllProcCalls(prog->getProcedureNodes().size());

}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
	// call your evaluator to evaluate the query here
	  // ...code to evaluate query...

	  // store the answers to the query in the results list (it is initially empty)
	  // each result must be a string.
	try {
		PQLQueryObject pqlQueryObject = PQLParser().parseQuery(query);

		QPSEvaluator qpsEvaluator = QPSEvaluator(pqlQueryObject, *pkbQueryAPI);

		QueryResult queryResult = qpsEvaluator.initialiseEvaluate();

		ResultProjector projector = ResultProjector(pkbQueryAPI, pqlQueryObject.makeDeclareMap());

		results = projector.projectResult(&queryResult, pqlQueryObject.getPQLSynonym(), pqlQueryObject.isSelectBoolean());
	}
	catch (QPSException e) {
		results = { std::string(e.what()) };
	}
	catch (SPAException e) {
		results = { };
	}
	catch (std::exception e) {
		results = { };
	}
}
