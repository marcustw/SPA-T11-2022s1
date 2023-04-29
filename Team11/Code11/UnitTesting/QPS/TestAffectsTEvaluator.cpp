#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/GetAllEvaluator.h"
#include "../source/QPS/Evaluator/RelationshipEvaluator/AffectsTEvaluator.h"
#include "../source/QPS/Evaluator/Processor/Processors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAffectsTEvaluator)
	{
	private:
		PKB* pkb;
		PKBStorageAPI* pkbStorageApi;
		PKBQueryAPI* pkbQueryApi;
		Processors* processors;
		AffectsTProcessor* affectsTProcessor;


		TEST_METHOD_INITIALIZE(init) {
			pkb = new PKB();
			pkbQueryApi = new PKBQueryAPI(pkb);
			pkbStorageApi = new PKBStorageAPI(pkb);
			processors = new Processors(*pkbQueryApi);
			affectsTProcessor = processors->getAffectsTProcessor();
		}

	public:
		TEST_METHOD(evaluateAffectsT_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_doubleInteger)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_doubleWildCard)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_doubleSynonym)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s1");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s", "s1" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftSynonym_rightInteger)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);
			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftInteger_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT}, {"s1", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftInteger_rightWildCard)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftWildcard_rightInteger)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftSynonym_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftWildcard_rightSynonym)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");

			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_leftSynonym_rightInteger_validNext)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "2");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "s" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			std::unordered_set<std::string> expectedValues = { "1" };
			std::vector<std::string> actual = result.getResult("s");
			std::unordered_set<std::string> actualValues(actual.begin(), actual.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedValues == actualValues);
		}

		TEST_METHOD(evaluateAffectsT_hasInformation_doubleSameSynonym)
		{
			pkbStorageApi->insertProc(1, 3, "test");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> vec1;
			vec1.push_back("x");

			std::vector<std::string> vec2;
			vec2.push_back("y");

			std::vector<std::string> vec3;
			vec3.push_back("z");

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, vec1);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 1, vec3);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, vec2);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 2, vec1);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 3, vec3);
			pkbStorageApi->setRelationship(RelationshipType::USES_S, 3, vec2);

			std::vector<StmtIndex> nextVector1;
			nextVector1.push_back(2);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 1, nextVector1);

			std::vector<StmtIndex> nextVector2;
			nextVector1.push_back(3);

			pkbStorageApi->setRelationship(RelationshipType::NEXT, 2, nextVector2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "s");
			DeclareMap map = { {"s", EntityType::STMT} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			AffectsTEvaluator affectsTEvaluator = AffectsTEvaluator(lhsRef, rhsRef, map,
				*pkbQueryApi, getAllEvaluator, affectsTProcessor);
			QueryResult result = affectsTEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
		}
	};
}  // namespace UnitTesting
