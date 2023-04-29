#include <string>
#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKBQueryAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/SP/Extractors/CallsExtractor.h"
#include "../source/Common/Lexer.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestCallsExtractor)
	{
	private:
		std::unordered_map<std::string, std::unordered_set<std::string>> procMapping;
		PKBQueryAPI* pkbQueryApi;
		PKBStorageAPI* pkbStorageApi;
		PKB* pkb;

		TEST_METHOD_INITIALIZE(init) {
			pkb = new PKB();
			pkbStorageApi = new PKBStorageAPI(pkb);
			pkbQueryApi = new PKBQueryAPI(pkb);
			procMapping = *(new std::unordered_map<std::string, std::unordered_set<std::string>>());
		}
	public:
		TEST_METHOD(extractCalls_one_procedure_calls_one_procedure)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureA"].insert("procedureB");

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");

			Assert::IsTrue(emptyVector.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCalls();

			std::vector<std::string> extractedCallsVector =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");

			Assert::IsTrue(!extractedCallsVector.empty());
			Assert::AreEqual(extractedCallsVector.at(0), std::string("procedureB"));
		}

		TEST_METHOD(extractCalls_one_procedure_calls_two_procedures)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureA"].insert("procedureB");
			procMapping["procedureA"].insert("procedureC");

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");

			Assert::IsTrue(emptyVector.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCalls();

			std::vector<std::string> extractedCallsVector =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");

			Assert::IsTrue(extractedCallsVector.size() == 2);
			Assert::AreEqual(extractedCallsVector.at(0), std::string("procedureB"));
			Assert::AreEqual(extractedCallsVector.at(1), std::string("procedureC"));
		}

		TEST_METHOD(extractCalls_two_procedure_calls_one_procedure)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureB"] = *(new std::unordered_set<std::string>());

			procMapping["procedureA"].insert("procedureC");
			procMapping["procedureB"].insert("procedureC");

			std::vector<std::string> emptyVectorA = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");
			std::vector<std::string> emptyVectorB = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureB");

			Assert::IsTrue(emptyVectorA.empty());
			Assert::IsTrue(emptyVectorB.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCalls();

			std::vector<std::string> extractedCallsVectorA =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");
			std::vector<std::string> extractedCallsVectorB =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureB");

			Assert::IsTrue(extractedCallsVectorA.size() == 1);
			Assert::IsTrue(extractedCallsVectorB.size() == 1);

			Assert::AreEqual(extractedCallsVectorA.at(0), std::string("procedureC"));
			Assert::AreEqual(extractedCallsVectorB.at(0), std::string("procedureC"));
		}

		TEST_METHOD(extractCallsT_one_procedure_calls_one_procedure)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureA"].insert("procedureB");

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL, "procedureA");

			Assert::IsTrue(emptyVector.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCallsT();

			std::vector<std::string> extractedCallsVector =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");

			Assert::IsTrue(!extractedCallsVector.empty());
			Assert::AreEqual(extractedCallsVector.at(0), std::string("procedureB"));
		}

		TEST_METHOD(extractCallsT_one_procedure_calls_two_procedures)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureA"].insert("procedureB");
			procMapping["procedureA"].insert("procedureC");

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");

			Assert::IsTrue(emptyVector.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCallsT();

			std::vector<std::string> extractedCallsVector =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");

			Assert::IsTrue(extractedCallsVector.size() == 2);
			Assert::AreEqual(extractedCallsVector.at(0), std::string("procedureB"));
			Assert::AreEqual(extractedCallsVector.at(1), std::string("procedureC"));
		}

		TEST_METHOD(extractCallsT_two_procedure_calls_one_procedure)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureB"] = *(new std::unordered_set<std::string>());

			procMapping["procedureA"].insert("procedureC");
			procMapping["procedureB"].insert("procedureC");

			std::vector<std::string> emptyVectorA = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");
			std::vector<std::string> emptyVectorB = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureB");

			Assert::IsTrue(emptyVectorA.empty());
			Assert::IsTrue(emptyVectorB.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCallsT();

			std::vector<std::string> extractedCallsVectorA =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");
			std::vector<std::string> extractedCallsVectorB =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureB");

			Assert::IsTrue(extractedCallsVectorA.size() == 1);
			Assert::IsTrue(extractedCallsVectorB.size() == 1);

			Assert::AreEqual(extractedCallsVectorA.at(0), std::string("procedureC"));
			Assert::AreEqual(extractedCallsVectorB.at(0), std::string("procedureC"));
		}

		TEST_METHOD(extractCallsT_one_procedure_indirect_calls_one_procedure)
		{
			procMapping["procedureA"] = *(new std::unordered_set<std::string>());
			procMapping["procedureB"] = *(new std::unordered_set<std::string>());

			procMapping["procedureA"].insert("procedureB");
			procMapping["procedureB"].insert("procedureC");

			std::vector<std::string> emptyVectorA = pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");

			Assert::IsTrue(emptyVectorA.empty());

			CallsExtractor* callsExtractor = new CallsExtractor(procMapping, *(pkbStorageApi));
			callsExtractor->extractCallsT();

			std::vector<std::string> extractedCallsVectorA =
				pkbQueryApi->getRelationshipRightArg(RelationshipType::CALL_T, "procedureA");

			Assert::IsTrue(extractedCallsVectorA.size() == 2);

			Assert::AreEqual(extractedCallsVectorA.at(0), std::string("procedureB"));
			Assert::AreEqual(extractedCallsVectorA.at(1), std::string("procedureC"));
		}
	};
};  // namespace UnitTesting
