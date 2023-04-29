#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/QPS/Evaluator/WithEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestWithEvaluator)
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
		TEST_METHOD(evaluateWith_valid_stmtNo)
		{
			std::string syn = "a";
			PQLReference lhsRef = std::pair(PQLReferenceType::STMT_NO, syn);
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			pkbStorageApi->insertAssign(1, "x");
			pkbStorageApi->insertAssign(2, "y");
			pkbStorageApi->insertAssign(3, "z");

			DeclareMap map = { {"a", EntityType::ASSIGN}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);
			PQLWith with = PQLWith(lhsRef, rhsRef);

			with.verify(map);

			WithEvaluator withEvaluator = WithEvaluator(with, EntityType::ASSIGN, EntityType::CONSTANT, *pkbQueryApi);

			QueryResult result = withEvaluator.evaluate();

			std::vector<std::string> expectedResults = { "1" };
			std::vector<std::string> actualResults = result.getResult(syn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(expectedResults.size(), actualResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateWith_valid_procName)
		{
			std::string syn = "p";
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "main");
			PQLReference rhsRef = std::pair(PQLReferenceType::PROC_NAME, syn);
			pkbStorageApi->insertProc(1, 5, "main");

			DeclareMap map = { {"p", EntityType::PROCEDURE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);
			PQLWith with = PQLWith(lhsRef, rhsRef);

			with.verify(map);

			WithEvaluator withEvaluator = WithEvaluator(with, EntityType::CONSTANT, EntityType::PROCEDURE, *pkbQueryApi);

			QueryResult result = withEvaluator.evaluate();

			std::vector<std::string> expectedResults = { "main" };
			std::vector<std::string> actualResults = result.getResult(syn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(expectedResults.size(), actualResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateWith_valid_varName)
		{
			std::string syn = "v";
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "x1");
			PQLReference rhsRef = std::pair(PQLReferenceType::VAR_NAME, syn);
			pkbStorageApi->insertVar(2, "x1");
			pkbStorageApi->insertVar(3, "x2");
			pkbStorageApi->insertVar(4, "x3");

			DeclareMap map = { {"p", EntityType::VARIABLE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);
			PQLWith with = PQLWith(lhsRef, rhsRef);

			with.verify(map);

			WithEvaluator withEvaluator = WithEvaluator(with, EntityType::CONSTANT, EntityType::VARIABLE, *pkbQueryApi);

			QueryResult result = withEvaluator.evaluate();

			std::vector<std::string> expectedResults = { "x1" };
			std::vector<std::string> actualResults = result.getResult(syn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(expectedResults.size(), actualResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(evaluateWith_valid_varName_noResult)
		{
			std::string syn = "v";
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "x4");
			PQLReference rhsRef = std::pair(PQLReferenceType::VAR_NAME, syn);
			pkbStorageApi->insertVar(2, "x1");
			pkbStorageApi->insertVar(3, "x2");
			pkbStorageApi->insertVar(4, "x3");

			DeclareMap map = { {"p", EntityType::VARIABLE}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);
			PQLWith with = PQLWith(lhsRef, rhsRef);

			with.verify(map);

			WithEvaluator withEvaluator = WithEvaluator(with, EntityType::CONSTANT, EntityType::VARIABLE, *pkbQueryApi);

			QueryResult result = withEvaluator.evaluate();

			std::vector<std::string> expectedResults = { };
			std::vector<std::string> actualResults = result.getResult(syn);

			Assert::IsTrue(result.hasNone());
		}

		TEST_METHOD(evaluateWith_valid_value)
		{
			std::string syn = "c";
			PQLReference lhsRef = std::pair(PQLReferenceType::VALUE, syn);
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "500");
			pkbStorageApi->insertConst(2, { 500 });

			DeclareMap map = { {"c", EntityType::CONSTANT}, {"v", EntityType::VARIABLE} };
			GetAllEvaluator getAllEvaluator = GetAllEvaluator(*pkbQueryApi);
			PQLWith with = PQLWith(lhsRef, rhsRef);

			with.verify(map);

			WithEvaluator withEvaluator = WithEvaluator(with, EntityType::CONSTANT, EntityType::CONSTANT, *pkbQueryApi);

			QueryResult result = withEvaluator.evaluate();

			std::vector<std::string> expectedResults = { "500" };
			std::vector<std::string> actualResults = result.getResult(syn);

			Assert::IsTrue(!result.hasNone());
			Assert::AreEqual(expectedResults.size(), actualResults.size());
			Assert::IsTrue(expectedResults == actualResults);
		}
	};
}  // namespace UnitTesting
