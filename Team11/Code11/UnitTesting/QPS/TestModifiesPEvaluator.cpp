#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/QPS/Evaluator/RelationshipEvaluator/ModifiesPEvaluator.h"
#include "../source/QPS/Evaluator/GetAllEvaluator.h"
#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifiesPEvaluator)
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
		TEST_METHOD(evaluateModifiesP_NoInformation)
		{
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");
			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("p");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_NoModifies)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(5, "x");
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(6, "y");
			pkbStorageApi->insertStmt(6, StatementType::ASSIGN_STMT);
			std::vector<std::string> modifiedVars = {};

			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("a");

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsSyn_rhsSyn_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> modifiedVars = { "x", "y", "z" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);


			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "testMain" };
			std::vector<std::string> actualResults = result.getResult("p");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateModifiesP_lhsSyn_rhsWildcard_validOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertProc(5, 9, "proseizure");
			pkbStorageApi->insertWhileContainer(1, 4);
			pkbStorageApi->insertWhileContainer(8, 11);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<std::string> modifiedVars = { "x" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);

			std::vector<std::string> modifiedVars2 = { "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "proseizure", modifiedVars2);

			std::string selectSyn = "pro";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"pro", EntityType::PROCEDURE} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "testMain", "proseizure" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsSyn_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string targetVar = "x";
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVar);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVar);
			std::vector<std::string> modifiedVars = { targetVar, "Y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);

			pkbStorageApi->insertProc(5, 9, proc2);
			pkbStorageApi->insertAssign(5, "Y");
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, "Y");
			std::vector<std::string> modifiedVars2 = { "Y" };  // proc2 no target var
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc2, modifiedVars2);

			std::string selectSyn = "p";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVar);

			DeclareMap map = { {"p", EntityType::PROCEDURE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "testMain" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsSyn_rhsIdent_validOutput_2)
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

			std::vector<std::string> modifiedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);

			pkbStorageApi->insertProc(5, 9, proc2);  // have to insert proc2
			pkbStorageApi->insertAssign(5, targetVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[1]);

			pkbStorageApi->insertAssign(8, targetVars[0]);
			pkbStorageApi->insertStmt(8, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(8, targetVars[0]);

			std::vector<std::string> modifiedVars2 = { "y", "x" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc2, modifiedVars2);

			std::string selectSyn = "pro";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "x");

			DeclareMap map = { {selectSyn, EntityType::PROCEDURE}, { "wh", EntityType::WHILE } };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesPEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesPEvalautor.evaluate();

			std::vector<std::string> expectedResults = { proc1, proc2 };  // note lexicographical order
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateModifiesP_lhsIdent_rhsSynonym_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);
			pkbStorageApi->insertAssign(2, targetVars[1]);
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, targetVars[1]);
			std::vector<std::string> modifiedVars = targetVars;
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);

			std::string selectSyn = "v";

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc1);
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);

			DeclareMap map = { {selectSyn, EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = targetVars;
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsIdent_rhsWildcard_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[0]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[0]);

			pkbStorageApi->insertVar(2, targetVars[1]);
			pkbStorageApi->insertStmt(2, StatementType::PRINT_STMT);

			pkbStorageApi->insertAssign(3, targetVars[2]);
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(3, targetVars[2]);

			pkbStorageApi->insertProc(5, 9, proc2);
			pkbStorageApi->insertAssign(5, targetVars[0]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, targetVars[0]);

			pkbStorageApi->insertAssign(8, targetVars[1]);
			pkbStorageApi->insertStmt(8, StatementType::READ_STMT);
			pkbStorageApi->insertVar(8, targetVars[1]);


			std::vector<std::string> modifiedVars = { "x", "z2" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);


			std::vector<std::string> modifiedVars2 = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc2, modifiedVars2);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc2);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "x", "y" };
			std::vector<std::string> actualResults = result.getResult(proc2);

			Assert::IsTrue(!result.hasNone());
		}


		TEST_METHOD(evaluateModifiesP_lhsIdent_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::vector<std::string> targetVars = { "x", "y", "z2" };
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVars[2]);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVars[2]);
			std::vector<std::string> modifiedVars = { targetVars[2] };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, proc1);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVars[2]);

			DeclareMap map = { };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "z2" };
			std::vector<std::string> actualResults = result.getResult(targetVars[2]);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsIdent_rhsIdent_validNoOutput)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(2, "y");
			std::vector<std::string> modifiedVars = { "x", "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);

			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "testMain");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "v");

			DeclareMap map = { {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = {};
			std::vector<std::string> actualResults = result.getResult("v");

			Assert::IsTrue(result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsWildcard_rhsIdent_invalid)
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

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);


			auto wrapperResult = [&modifiesSEvalautor, this] {
				QueryResult result = modifiesSEvalautor.evaluate();
			};
			Assert::ExpectException<QPSException>(wrapperResult);
		}

		TEST_METHOD(evaluateModifiesP_lhsSynCall_rhsSyn_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			pkbStorageApi->insertAssign(3, "z");
			pkbStorageApi->insertStmt(3, StatementType::ASSIGN_STMT);

			std::vector<std::string> modifiedVars = { "x", "y", "z" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);

			pkbStorageApi->insertProc(5, 9, proc1);
			pkbStorageApi->insertAssign(5, modifiedVars[1]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, modifiedVars[1]);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);


			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "p");
			PQLReference rhsRef = std::pair(PQLReferenceType::SYNONYM, "v");

			DeclareMap map = { {"p", EntityType::CALL}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11" };
			std::vector<std::string> actualResults = result.getResult("p");

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(evaluateModifiesP_lhsSynCall_rhsWildcard_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertProc(5, 9, "proseizure");
			pkbStorageApi->insertWhileContainer(1, 4);
			pkbStorageApi->insertWhileContainer(8, 11);

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);

			std::vector<std::string> modifiedVars = { "x" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "testMain", modifiedVars);

			std::vector<std::string> modifiedVars2 = { "y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, "proseizure", modifiedVars2);

			pkbStorageApi->insertProc(5, 9, proc1);
			pkbStorageApi->insertAssign(5, modifiedVars2[0]);
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, modifiedVars2[0]);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);

			std::string selectSyn = "pro";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");

			DeclareMap map = { {"pro", EntityType::CALL} };

			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11", "12" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateModifiesP_lhsSynCall_rhsIdent_validOutput)
		{
			std::string proc1 = "testMain";
			std::string proc2 = "proseizure";
			std::string proc3 = "procthree";
			std::string targetVar = "x";
			pkbStorageApi->insertProc(1, 4, proc1);
			pkbStorageApi->insertAssign(1, targetVar);
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(1, targetVar);
			std::vector<std::string> modifiedVars = { targetVar, "Y" };
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc1, modifiedVars);

			pkbStorageApi->insertProc(5, 9, proc2);
			pkbStorageApi->insertAssign(5, "Y");
			pkbStorageApi->insertStmt(5, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertVar(5, "Y");
			std::vector<std::string> modifiedVars2 = { "Y" };  // proc2 no target var
			pkbStorageApi->setRelationship(RelationshipType::MODIFIES_P, proc2, modifiedVars2);

			// proc3
			pkbStorageApi->insertProc(10, 13, proc3);
			pkbStorageApi->insertProcCall(11, proc1, proc3);
			pkbStorageApi->insertProcCall(12, proc2, proc3);

			std::string selectSyn = "p";

			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, selectSyn);
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, targetVar);

			DeclareMap map = { {"p", EntityType::CALL} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);

			ModifiesPEvaluator modifiesSEvalautor = ModifiesPEvaluator(lhsRef, rhsRef, map, *pkbQueryApi, getAllEvaluator);
			QueryResult result = modifiesSEvalautor.evaluate();

			std::vector<std::string> expectedResults = { "11" };
			std::vector<std::string> actualResults = result.getResult(selectSyn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(actualResults.size(), expectedResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}
	};
}  // namespace UnitTesting
