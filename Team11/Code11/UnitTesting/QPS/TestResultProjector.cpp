#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/QPS/Projector/ResultProjector.h"
#include "../source/QPS/Parser/PQLQueryObject.h"
#include "../source/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestResultProjector)
	{
	private:
		PKB* pkb;
		PKBQueryAPI* pkbQueryApi;

		TEST_METHOD_INITIALIZE(initTables)
		{
			pkb = new PKB();
			pkbQueryApi = new PKBQueryAPI(pkb);
		}
	public:
		TEST_METHOD(validResult_validOutput_selectAssignment)
		{
			std::string syn = "a";
			std::unordered_map<std::string, std::vector<std::string>> results = {
				{"a", { "1", "2", "3", "4", "11" } }
			};
			QueryResult queryResult = QueryResult(results);
			DeclareMap declareMap = { { "a", EntityType::STMT } };
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			std::list<std::string> expectedOutput = { "1", "2", "3", "4", "11"};
			output.sort();
			expectedOutput.sort();
			Assert::AreEqual(output.size(), expectedOutput.size());
			auto outputPtr = output.begin();
			auto expectedOutputPtr = expectedOutput.begin();
			for (size_t i = 0; i < results.size(); i++) {
				Assert::AreEqual(*outputPtr, *expectedOutputPtr);
				std::advance(outputPtr, 1);
				std::advance(expectedOutputPtr, 1);
			}
		}


		TEST_METHOD(validResult_validOutput_selectProcedure)
		{
			std::string syn = "p";
			std::unordered_map<std::string, std::vector<std::string>> results = {
				{"p", { "main", "example", "source"}}
			};
			QueryResult queryResult = QueryResult(results);
			DeclareMap declareMap = { { "p", EntityType::PROCEDURE } };
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			// test sorted output projected
			std::list<std::string> expectedOutput = { "example", "main", "source" };
			output.sort();
			expectedOutput.sort();
			Assert::AreEqual(output.size(), expectedOutput.size());
			auto outputPtr = output.begin();
			auto expectedOutputPtr = expectedOutput.begin();
			for (size_t i = 0; i < results.size(); i++) {
				Assert::AreEqual(*outputPtr, *expectedOutputPtr);
				std::advance(outputPtr, 1);
				std::advance(expectedOutputPtr, 1);
			}
		}


		TEST_METHOD(validResult_validOutput_selectVariable)
		{
			std::string syn = "v1";
			std::unordered_map<std::string, std::vector<std::string>> results = {
				{"v1", { "x", "y", "a", "b2", "cx3"}}
			};
			DeclareMap declareMap = { { "v1", EntityType::VARIABLE } };
			QueryResult queryResult = QueryResult(results);
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			// test sorted output projected
			std::list<std::string> expectedOutput = { "a", "b2", "cx3", "x", "y" };

			Assert::AreEqual(output.size(), expectedOutput.size());
			output.sort();
			expectedOutput.sort();
			auto outputPtr = output.begin();
			auto expectedOutputPtr = expectedOutput.begin();
			for (size_t i = 0; i < results.size(); i++) {
				Assert::AreEqual(*outputPtr, *expectedOutputPtr);
				std::advance(outputPtr, 1);
				std::advance(expectedOutputPtr, 1);
			}
		}

		TEST_METHOD(validResult_validOutput_selectWhile_EmptyOutput)
		{
			std::string syn = "wh";
			std::unordered_map<std::string, std::vector<std::string>> results = {
				{"wh", {}}
			};
			DeclareMap declareMap = { { "wh", EntityType::WHILE } };
			QueryResult queryResult = QueryResult(results);
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			size_t expectedSize = 0;
			Assert::AreEqual(output.size(), expectedSize);
		}

		TEST_METHOD(validResult_validOutput_selectIfs_EmptyQueryResult)
		{
			std::string syn = "ifs";
			QueryResult queryResult = QueryResult(false);
			DeclareMap declareMap = { { "ifs", EntityType::IF } };
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			size_t expectedSize = 0;
			Assert::AreEqual(output.size(), expectedSize);
		}

		TEST_METHOD(validResult_validOutput_selectConstants_NoneResult)
		{
			std::string syn = "con";
			QueryResult queryResult = QueryResult(true);
			DeclareMap declareMap = { { "con", EntityType::STMT } };
			ResultProjector resultProjector = ResultProjector(pkbQueryApi, declareMap);
			std::vector<PQLReference> pqlRefs = { PQLReference(PQLReferenceType::SYNONYM, syn) };
			std::list<std::string> output = resultProjector.projectResult(&queryResult, pqlRefs, false);
			size_t expectedSize = 0;
			Assert::AreEqual(output.size(), expectedSize);
		}
	};
}  // namespace UnitTesting
