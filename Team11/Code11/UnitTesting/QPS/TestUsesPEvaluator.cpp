#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/RelationshipEvaluator/UsesPEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestUsesPEvaluator)
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
		TEST_METHOD(evaluateUsesP_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("p");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_NoUses)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			std::vector<std::string> usedVars = {};
			pkbStorageApi->setRelationship(RelationshipType::USES_P, "testMain", usedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("p");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsSyn_rhsSyn_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);
			pkbStorageApi->insertAssign(5, targetVars[0]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[0]);

			pkbStorageApi->insertAssign(8, targetVars[1]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[1]);

			std::vector<std::string> usedVars2 = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"a", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { proc1, proc2 };
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateUsesP_lhsSyn_rhsWildcard_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			std::string selectSyn = "wh";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"wh", EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { proc1 };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsSyn_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc1);
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			std::vector<std::string> usedVars2 = { "y"};
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "prokemon";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVars[0]);

			DeclareMap map = { {selectSyn, EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { proc1 };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsSyn_rhsIdent_validOutput_2)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> usedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "pro";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "x");

			DeclareMap map = { {selectSyn, EntityType::PROCEDURE}, { "wh", EntityType::WHILE } };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { proc1, proc2 };  // note lexicographical order
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateUsesP_lhsIdent_rhsSynonym_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> usedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc1);
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "x", "z2" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
		}

		TEST_METHOD(evaluateUsesP_lhsInt_rhsWildcard_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> usedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "a";

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc1);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"a", EntityType::ASSIGN} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
		}


		TEST_METHOD(evaluateUsesP_lhsIdent_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> usedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			// selects var name instead
			std::string selectSyn = proc1;

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVars[0]);

			DeclareMap map = { };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "x", "z2" };
			std::vector<std::string> actualResults = result.getResult(targetVars[0]);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsIdent_rhsIdent_validNoOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> usedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc1);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsWildcard_rhsIdent_invalid)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, "y");
			std::vector<std::string> usedVars = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, "testMain", usedVars);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);


			auto wrapperResult = [&UsesPEvalautor, this] {
				QueryResult result = UsesPEvalautor.evaluate();
			};
			Assert::ExpectException<QPSException>(wrapperResult);
		}


		TEST_METHOD(evaluateUsesP_lhsSynCall_rhsSyn_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc2);
			pkbStorageApi->insertAssign(5, targetVars[0]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[0]);

			pkbStorageApi->insertAssign(8, targetVars[1]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[1]);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);

			std::vector<std::string> usedVars2 = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"a", EntityType::CALL}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11", "12" };
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(expectedResults.size(), actualResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateUsesP_lhsSynCall_rhsWildcard_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			std::string selectSyn = "wh";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {selectSyn, EntityType::CALL} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11"};
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateUsesP_lhsSynCall_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertAssign(2, targetVars[2]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[2]);

			std::vector<std::string> usedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc1, usedVars);

			pkbStorageApi->insertProc(5, 9, proc1);
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);

			std::vector<std::string> usedVars2 = { "y" };
			pkbStorageApi->setRelationship(RelationshipType::USES_P, proc2, usedVars2);

			std::string selectSyn = "prokemon";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVars[0]);

			DeclareMap map = { {selectSyn, EntityType::CALL} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			UsesPEvaluator UsesPEvalautor = UsesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = UsesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}
	};
}  // namespace UnitTesting
