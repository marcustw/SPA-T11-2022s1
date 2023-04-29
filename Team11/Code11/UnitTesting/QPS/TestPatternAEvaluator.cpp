#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/PatternEvaluator/PatternAEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestPatternAEvaluator)
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
		TEST_METHOD(evaluatePatternA_NoInformation)
		{
			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftIdent_RightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {"a"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftWildcard_RightPartial)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::MIXED, "x + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "2" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftIdent_RightPartial)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "y");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::MIXED, "x + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);

			DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "2" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_doubleWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "2" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftSynonym_RightWildcard)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "v");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a", "v"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "2" };
			std::unordered_set<std::string> expectedVarValues = { "x", "y" };
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftSynonym_RightPartial)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "x + 1");

			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "v");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::MIXED, "x + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a", "v"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "2" };
			std::unordered_set<std::string> expectedVarValues = { "y" };
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftIdent_RightFull)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");
			pkbStorageApi->insertStmtExpressionLst(1, "1");
			pkbStorageApi->insertStmtExpressionLst(1, "z + 1");
			pkbStorageApi->insertStmtExactExpression(1, "z + 1");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "z + 1");

			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::FULL, "z + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftSynonym_RightFull)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");
			pkbStorageApi->insertStmtExpressionLst(1, "1");
			pkbStorageApi->insertStmtExpressionLst(1, "z + 1");
			pkbStorageApi->insertStmtExactExpression(1, "z + 1");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "z + 1");

			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "v");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::FULL, "z + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a", "v" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = { "x" };
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternA_hasInformation_leftWildCard_RightFull)
		{
			pkbStorageApi->insertProc(1, 2, "testMain");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertStmt(1, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(1, "z");
			pkbStorageApi->insertStmtExpressionLst(1, "1");
			pkbStorageApi->insertStmtExpressionLst(1, "z + 1");
			pkbStorageApi->insertStmtExactExpression(1, "z + 1");

			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertStmt(2, StatementType::ASSIGN_STMT);
			pkbStorageApi->insertStmtExpressionLst(2, "z + 1");

			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::FULL, "z + 1");
			PQLPattern pqlPattern = PQLPattern(std::string("a"), PQLPatternType::PATTERN_A,
				entRef, expressionSpec, 2);
			DeclareMap declareMap = { { "a", EntityType::ASSIGN }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternAEvaluator patternEvaluator = PatternAEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "a" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("a");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}
	};
}  // namespace UnitTesting
