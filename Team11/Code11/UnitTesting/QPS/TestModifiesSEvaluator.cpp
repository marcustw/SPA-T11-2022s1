#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/QPS/Evaluator/RelationshipEvaluator/ModifiesSEvaluator.h"
#include "../source/QPS/Evaluator/GetAllEvaluator.h"
#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifiesSEvaluator)
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
		TEST_METHOD(evaluateModifiesS_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");
			DeclareMap map = { {"a", EntityType::ASSIGN}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_NoModifies)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			std::vector<std::string> modifiedVars = {};
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"a", EntityType::ASSIGN}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_lhsSyn_rhsSyn_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			std::vector<std::string> modifiedVars = {"x", "y", "z"};
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"a", EntityType::ASSIGN}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {"1"};
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateModifiesS_lhsSyn_rhsWildcard_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertWhileContainer(1, 4);
			pkbStorageApi->insertWhileContainer(8, 11);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<std::string> modifiedVars = { "x" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 8, modifiedVars);

			std::string selectSyn = "wh";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"wh", EntityType::WHILE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "1", "8" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_lhsSyn_rhsIdent_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			std::vector<std::string> modifiedVars = { "x"};
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			std::string selectSyn = "a";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "x");

			DeclareMap map = { {"a", EntityType::ASSIGN} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "1" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_lhsSyn_rhsIdent_validOutput_2)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertWhileContainer(1, 4);
			pkbStorageApi->insertAssign(2, "x");
			pkbStorageApi->insertVar(2, "x");

			std::vector<std::string> modifiedVars = { "x", "y", "z"};
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);
			std::vector<std::string> modifiedVars2 = { "x" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 2, modifiedVars2);

			std::string selectSyn = "wh";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "x");

			DeclareMap map = { {"a", EntityType::ASSIGN}, { "wh", EntityType::WHILE } };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "1" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateModifiesS_lhsInt_rhsSynonym_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, "y");
			std::vector<std::string> modifiedVars = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "x", "y"};
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
		}

		TEST_METHOD(evaluateModifiesS_lhsInt_rhsWildcard_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			std::vector<std::string> modifiedVars = { "x", "y"};
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			std::string selectSyn = "a";

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"a", EntityType::ASSIGN} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "1" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
		}


		TEST_METHOD(evaluateModifiesS_lhsInt_rhsIdent_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "v3");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "v3");
			std::vector<std::string> modifiedVars = { "v3" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			// selects var name instead
			std::string selectSyn = "1";

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v3");

			DeclareMap map = { };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "v3" };
			std::vector<std::string> actualResults = result.getResult("v3");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_lhsInt_rhsIdent_validNoOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, "y");
			std::vector<std::string> modifiedVars = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesS_lhsWildcard_rhsIdent_invalid)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, "y");
			std::vector<std::string> modifiedVars = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_S, 1, modifiedVars);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesSEvaluator modifiesSEvalautor = ModifiesSEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);


			auto wrapperResult = [&modifiesSEvalautor, this] {
				QueryResult result = modifiesSEvalautor.evaluate();
			};
			Assert::ExpectException<QPSException>(wrapperResult);
		}
	};
}  // namespace UnitTesting
