#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/GetAllEvaluator.h"
#include "../source/QPS/Evaluator/RelationshipEvaluator/NextEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestNextEvaluator)
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
		TEST_METHOD(evaluateNext_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_doubleInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_doubleWildCard)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_doubleSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s1");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {"s", "s1"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_doubleSameSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftSynonym_rightInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftInteger_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftInteger_rightWildCard)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftWildcard_rightInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftSynonym_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftWildcard_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftSynonym_rightInteger_validNext)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			std::unordered_set<std::string> expectedValues = { "1"};
			std::vector<std::string> actual = result.getResult("s");
			std::unordered_set<std::string> actualValues(actual.begin(), actual.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedValues == actualValues);
		}

		TEST_METHOD(evaluateNext_hasInformation_leftSynonym_rightInteger_InvalidNext)
		{
			pkbStorageApi->insertProc(1, 2, "testNext");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> nextVector;
			nextVector.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateNext_whileLoop_leftInteger_rightSynonym_validNext)
		{
			pkbStorageApi->insertProc(1, 3, "testNext");

			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertWhileContainer(2, 3);
			pkbStorageApi->insertStmt(2, StatementType::WHILE_STMT);

			pkbStorageApi->insertAssign(3, "y");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> oneVector;
			std::vector<StmtIndex> twoVector;
			std::vector<StmtIndex> threeVector;

			oneVector.push_back(2);
			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, oneVector);

			twoVector.push_back(3);
			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, twoVector);

			threeVector.push_back(2);
			pkbStorageApi->setRelationship(RelationshipType::NEXT, 3, threeVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "3");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {"s"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			std::unordered_set<std::string> expectedValues = { "2" };
			std::vector<std::string> actual = result.getResult("s");
			std::unordered_set<std::string> actualValues(actual.begin(), actual.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedValues == actualValues);
		}

		TEST_METHOD(evaluateNext_ifStmt_leftInteger_rightSynonym_validNext)
		{
			pkbStorageApi->insertProc(1, 3, "testNext");

			pkbStorageApi->insertStmt(1, StatementType::IF_STMT);

			pkbStorageApi->insertAssign(2, "x");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "y");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<StmtIndex> ifContainer;
			ifContainer.push_back(2);
			std::vector<StmtIndex> elseContainer;
			elseContainer.push_back(3);
			std::vector<std::vector<StmtIndex>> ifBlockContainer;
			ifBlockContainer.push_back(ifContainer);
			ifBlockContainer.push_back(elseContainer);

			pkbStorageApi->insertIfContainer(ifBlockContainer);

			std::vector<StmtIndex> oneVector;
			std::vector<StmtIndex> twoVector;
			std::vector<StmtIndex> threeVector;

			oneVector.push_back(2);
			oneVector.push_back(3);
			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, oneVector);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, twoVector);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 3, threeVector);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			NextEvaluator nextEvaluator = NextEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = nextEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			std::unordered_set<std::string> expectedValues = { "2", "3"};
			std::vector<std::string> actual = result.getResult("s");
			std::unordered_set<std::string> actualValues(actual.begin(), actual.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedValues == actualValues);
		}
	};
}  // namespace UnitTesting
