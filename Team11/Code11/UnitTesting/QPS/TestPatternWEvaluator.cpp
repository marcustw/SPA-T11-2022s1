#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/PatternEvaluator/PatternWEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestPatternWEvaluator)
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
		TEST_METHOD(evaluatePatternW_NoInformation)
		{
			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("w"), PQLPatternType::PATTERN_W, entRef,
				expressionSpec, 2);
			DeclareMap declareMap = { { "w", EntityType::WHILE }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternWEvaluator patternEvaluator = PatternWEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluatePatternW_hasInformation_leftIdent_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertWhileContainer(1, 2);
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertWhileContainer(3, 4);
			pkbStorageApi->insertVar(3, "y");

			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("w"), PQLPatternType::PATTERN_W,
				entRef, expressionSpec, 2);
			DeclareMap declareMap = { { "w", EntityType::WHILE }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternWEvaluator patternEvaluator = PatternWEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "w" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("w");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternW_hasInformation_leftSynonym_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertWhileContainer(1, 2);
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertWhileContainer(3, 4);
			pkbStorageApi->insertVar(3, "y");

			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "v");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("w"), PQLPatternType::PATTERN_W,
				entRef, expressionSpec, 2);
			DeclareMap declareMap = { { "w", EntityType::WHILE }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternWEvaluator patternEvaluator = PatternWEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "w", "v"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "3"};
			std::unordered_set<std::string> expectedVarValues = {"x", "y"};
			std::vector<std::string> actualSyn = result.getResult("w");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternW_hasInformation_leftWildcard_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 4, "testMain");
			pkbStorageApi->insertWhileContainer(1, 2);
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertWhileContainer(3, 4);
			pkbStorageApi->insertVar(3, "y");

			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("w"), PQLPatternType::PATTERN_W,
				entRef, expressionSpec, 2);
			DeclareMap declareMap = { { "w", EntityType::WHILE }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternWEvaluator patternEvaluator = PatternWEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "w" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "3" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("w");
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
