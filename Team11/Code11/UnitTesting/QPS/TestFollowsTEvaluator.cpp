#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "QPS/Evaluator/GetAllEvaluator.h"
#include "QPS/Evaluator/RelationshipEvaluator/FollowsTEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestFollowsTEvaluator)
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
		TEST_METHOD(evaluateFollowsT_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = {2});

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleWildCard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s1");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s", "s1" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleSameSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftSynonym_rightInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftInteger_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s1");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s1" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftInteger_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftWildcard_rightInteger)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftSynonym_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_leftWildcard_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 2 });

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleInteger_IfStatement)
		{
			pkbStorageApi->insertProc(1, 5, "testMain");
			pkbStorageApi->insertStmt(1, StatementType::IF_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(3, "y");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertIfContainer({ {1, 2}, {3, 4} });

			pkbStorageApi->insertAssign(5, "y");
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);

			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 5 });

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "5");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateFollowsT_hasInformation_doubleSynonym_IfStatement)
		{
			pkbStorageApi->insertProc(1, 5, "testMain");
			pkbStorageApi->insertStmt(1, StatementType::IF_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(3, "y");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertAssign(4, "y");
			pkbStorageApi->insertStmt(4, StatementType::ASSIGN_STMT);

			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 3, std::vector<int>() = { 4 });

			pkbStorageApi->insertIfContainer({ {1, 2}, {3, 4} });

			pkbStorageApi->insertAssign(5, "y");
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);

			pkbStorageApi->setRelationship(RelationshipType::FOLLOWS_T, 1, std::vector<int>() = { 5 });

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s1");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			FollowsTEvaluator followsTEvaluator = FollowsTEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = followsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s", "s1" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedLhsValues = { "1", "3" };
			std::unordered_set<std::string> expectedRhsValues = { "5", "4" };
			std::vector<std::string> actualLhs = result.getResult("s");
			std::vector<std::string> actualRhs = result.getResult("s1");
			std::unordered_set<std::string> actualLhsValues(actualLhs.begin(), actualLhs.end());
			std::unordered_set<std::string> actualRhsValues(actualRhs.begin(), actualRhs.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedLhsValues == actualLhsValues);
			Assert::IsTrue(expectedRhsValues == actualRhsValues);
		}
	};
}  // namespace UnitTesting
