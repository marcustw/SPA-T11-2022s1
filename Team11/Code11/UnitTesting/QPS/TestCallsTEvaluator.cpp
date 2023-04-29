#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../../source/QPS/Evaluator/RelationshipEvaluator/CallsTEvaluator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestCallsTEvaluator)
	{
	private:
		PKB* pkb;
		PKBStorageAPI* pkbStorageApi;
		PKBQueryAPI* pkbQueryApi;



		TEST_METHOD_INITIALIZE(init) {
			pkb = new PKB();
			pkbQueryApi = new PKBQueryAPI(pkb);
			pkbStorageApi = new PKBStorageAPI(pkb);
		}
	public:
		TEST_METHOD(evaluateCallsT_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "procedureA");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");
			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_doubleProcname)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "procedureA");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_doubleWildCard)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_doubleSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "p1");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "p", "p1" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_doubleSameSynonym)
		{
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "p");

			DeclareMap map = { {"p", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_leftSynonym_rightProcName)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");
			DeclareMap map = { {"p", EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "p" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_leftProcName_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "procedureA");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_leftWildcard_rightProcName)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "p" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_leftSynonym_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set<std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "p" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_hasInformation_leftWildcard_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set <std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "p");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"p1", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set <std::string> expectedSynonyms = { "p" };
			std::unordered_set <std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_doubleProcname_noCallStmt)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "procedureA");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			// no synonyms expected, since no calls from A to B
			std::unordered_set <std::string> expectedSynonyms = {};
			std::unordered_set <std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateCallsT_leftProcName_rightSynonym_callStmt)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set <std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "procedureA");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "p");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedProcedures = { "procedureB" };
			std::vector<std::string> actualProcs = result.getResult("p");

			std::unordered_set<std::string> actualProcValues(actualProcs.begin(), actualProcs.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedProcedures == actualProcValues);
		}

		TEST_METHOD(evaluateCallsT_leftSynonym_rightProcname_callStmt)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set <std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL_T, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedProcedures = { "procedureA" };
			std::vector<std::string> actualProcs = result.getResult("p");

			std::unordered_set<std::string> actualProcValues(actualProcs.begin(), actualProcs.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedProcedures == actualProcValues);
		}

		TEST_METHOD(evaluateCallsT_leftSynonym_rightProcname_call_noCallT)
		{
			pkbStorageApi->insertProc(1, 2, "procedureA");
			pkbStorageApi->insertProc(3, 4, "procedureB");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertProcCall(2, "procedureB", "procedureA");
			pkbStorageApi->insertStmt(2, StatementType::CALL_STMT);

			pkbStorageApi->insertAssign(3, "x");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			std::unordered_set <std::string> procLst;
			procLst.insert("procedureB");

			pkbStorageApi->setRelationship(RelationshipType::CALL, "procedureA", procLst);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "procedureB");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			CallsTEvaluator callsTEvaluator = CallsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = callsTEvaluator.evaluate();

			std::unordered_set <std::string> expectedSynonyms = {};
			std::unordered_set <std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}
	};
}  // namespace UnitTesting
