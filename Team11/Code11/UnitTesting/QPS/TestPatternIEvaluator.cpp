#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/PatternEvaluator/PatternIEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestPatternIEvaluator)
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
		TEST_METHOD(evaluatePatternI_NoInformation)
		{
			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("if"), PQLPatternType::PATTERN_I,
				entRef, expressionSpec, 3);
			DeclareMap declareMap = { { "if", EntityType::IF }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternIEvaluator patternEvaluator = PatternIEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = {};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();

			Assert::IsTrue(result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
		}

		TEST_METHOD(evaluatePatternI_hasInformation_leftIdent_centreWildcard_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 6, "testMain");
			pkbStorageApi->insertIfContainer({{1, 2}, {3, 3}});
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertIfContainer({ {4, 5}, {6, 6} });
			pkbStorageApi->insertVar(4, "y");


			PQLReference entRef = std::pair(PQLReferenceType::IDENT, "x");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("if"), PQLPatternType::PATTERN_I,
				entRef, expressionSpec, 3);
			DeclareMap declareMap = { { "if", EntityType::IF }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternIEvaluator patternEvaluator = PatternIEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "if" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("if");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternI_hasInformation_leftSynonym_centreWildcard_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 6, "testMain");
			pkbStorageApi->insertIfContainer({ {1, 2}, {3, 3} });
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertIfContainer({ {4, 5}, {6, 6} });
			pkbStorageApi->insertVar(4, "y");


			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "v");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("if"), PQLPatternType::PATTERN_I,
				entRef, expressionSpec, 3);
			DeclareMap declareMap = { { "if", EntityType::IF }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternIEvaluator patternEvaluator = PatternIEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "if", "v"};
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "4"};
			std::unordered_set<std::string> expectedVarValues = {"x", "y"};
			std::vector<std::string> actualSyn = result.getResult("if");
			std::vector<std::string> actualVar = result.getResult("v");
			std::unordered_set<std::string> actualSynValues(actualSyn.begin(), actualSyn.end());
			std::unordered_set<std::string> actualVarValues(actualVar.begin(), actualVar.end());

			Assert::IsTrue(!result.hasNone());
			Assert::IsTrue(expectedSynonyms == actualSynonyms);
			Assert::IsTrue(expectedSynValues == actualSynValues);
			Assert::IsTrue(expectedVarValues == actualVarValues);
		}

		TEST_METHOD(evaluatePatternI_hasInformation_leftWildCard_centreWildcard_rightWildcard)
		{
			pkbStorageApi->insertProc(1, 6, "testMain");
			pkbStorageApi->insertIfContainer({ {1, 2}, {3, 3} });
			pkbStorageApi->insertVar(1, "x");

			pkbStorageApi->insertIfContainer({ {4, 5}, {6, 6} });
			pkbStorageApi->insertVar(4, "y");


			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expressionSpec = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern(std::string("if"), PQLPatternType::PATTERN_I,
				entRef, expressionSpec, 3);
			DeclareMap declareMap = { { "if", EntityType::IF }, { "v", EntityType::VARIABLE } };
			pqlPattern.verify(declareMap);

			PatternIEvaluator patternEvaluator = PatternIEvaluator(pqlPattern, *pkbQueryApi);
			QueryResult result = patternEvaluator.evaluate();

			std::unordered_set<std::string> expectedSynonyms = { "if" };
			std::unordered_set<std::string> actualSynonyms = result.getSynonyms();
			std::unordered_set<std::string> expectedSynValues = { "1", "4" };
			std::unordered_set<std::string> expectedVarValues = {};
			std::vector<std::string> actualSyn = result.getResult("if");
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
