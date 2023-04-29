#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKB.h"
#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKBQueryAPI.h"
#include "../source/QPS/Parser/PQLParser.h"
#include "../source/QPS/Evaluator/QPSEvaluator.h"
#include "../source/QPS/Evaluator/QueryResult.h"
#include "../source/QPS/Projector/ResultProjector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(TestFrontEnd)
	{
	private:
		PKB* pkb;
		PKBStorageAPI* pkbStorageApi;
		PKBQueryAPI* pkbQueryApi;

		TEST_METHOD_INITIALIZE(initTables)
		{
			pkb = new PKB();
			pkbStorageApi = new PKBStorageAPI(pkb);
			pkbQueryApi = new PKBQueryAPI(pkb);
		}
	public:
		TEST_METHOD(query_valid_declarationAndSelectStmt)
		{
			std::string query = std::string("stmt s; Select s");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(1, "x");
			std::string syn = "s";

			PQLQueryObject pqlQueryObject = PQLParser().parseQuery(query);

			Assert::AreEqual(pqlQueryObject.isSelectBoolean(), false);

			PQLReference s = PQLReference(PQLReferenceType::SYNONYM, syn);
			std::vector<PQLReference> querySyns = { s };
			PQLDeclaration d = PQLDeclaration(EntityType::STMT, syn);
			std::vector<PQLDeclaration> queryDeclarations = { d };
			Assert::AreEqual(pqlQueryObject.getPQLSynonym().size(), querySyns.size());
			Assert::IsTrue(pqlQueryObject.getPQLSynonym() == querySyns);
			Assert::AreEqual(pqlQueryObject.getPQLDeclaration().size(), queryDeclarations.size());
			Assert::IsTrue(pqlQueryObject.getPQLDeclaration() == queryDeclarations);

			QPSEvaluator qpsEvaluator = QPSEvaluator(pqlQueryObject, *pkbQueryApi);
			QueryResult queryResult = qpsEvaluator.initialiseEvaluate();

			Assert::IsTrue(!queryResult.hasNone());

			ResultProjector projector = ResultProjector(pkbQueryApi, pqlQueryObject.makeDeclareMap());

			std::list<std::string> results = projector.projectResult(
				&queryResult, pqlQueryObject.getPQLSynonym(), pqlQueryObject.isSelectBoolean());

			std::list<std::string> expectedResults = { "1" };

			Assert::AreEqual(results.size(), expectedResults.size());
			Assert::IsTrue(results == expectedResults);
		}

		TEST_METHOD(query_valid_declarationAndSelectStmt_oneSuchThat)
		{
			std::string query = std::string("stmt s; variable v; Select s such that Uses(s, v)");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertProc(1, 5, "main");
			std::vector<std::string> modifiedVar = { "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, modifiedVar);
			std::unordered_map<std::string, std::vector<std::string>> usesStable =
				pkbQueryApi->getUsesSTable();
			Assert::IsTrue(usesStable.count("1") > 0);
			Assert::IsTrue(pkbQueryApi->getUsesSTable().at("1") == modifiedVar);

			PQLQueryObject pqlQueryObject = PQLParser().parseQuery(query);

			Assert::AreEqual(pqlQueryObject.isSelectBoolean(), false);

			PQLReference s = PQLReference(PQLReferenceType::SYNONYM, "s");
			PQLDeclaration stmt = PQLDeclaration(EntityType::STMT, "s");
			PQLDeclaration var = PQLDeclaration(EntityType::VARIABLE, "v");
			std::vector<PQLReference> querySyns = { s };
			std::vector<PQLDeclaration> queryDeclarations = { stmt, var };

			Assert::AreEqual(pqlQueryObject.getPQLSynonym().size(), querySyns.size());
			Assert::IsTrue(pqlQueryObject.getPQLSynonym() == querySyns);
			Assert::AreEqual(pqlQueryObject.getPQLDeclaration().size(), queryDeclarations.size());
			Assert::IsTrue(pqlQueryObject.getPQLDeclaration() == queryDeclarations);

			QPSEvaluator qpsEvaluator = QPSEvaluator(pqlQueryObject, *pkbQueryApi);
			QueryResult queryResult = qpsEvaluator.initialiseEvaluate();

			Assert::IsTrue(!queryResult.hasNone());

			ResultProjector projector = ResultProjector(pkbQueryApi, pqlQueryObject.makeDeclareMap());

			std::list<std::string> results = projector.projectResult(
				&queryResult, pqlQueryObject.getPQLSynonym(), pqlQueryObject.isSelectBoolean());

			std::list<std::string> expectedResults = { "1" };

			Assert::AreEqual(results.size(), expectedResults.size());
			Assert::IsTrue(results == expectedResults);
		}
	};
}  // namespace IntegrationTesting
