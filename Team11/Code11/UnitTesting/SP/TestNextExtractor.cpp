#include <string>
#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKBQueryAPI.h"
#include "../source/PKB/PKB.h"
#include "../source/SP/Extractors/NextExtractor.h"
#include "../source/Common/Lexer.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestNextExtractor)
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
		TEST_METHOD(extractNext_two_statements)
		{
			std::unordered_map<int, std::unordered_set<int>>* cfgMap = new std::unordered_map<int, std::unordered_set<int>>();

			(*cfgMap)[1].insert(2);

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::NEXT, 1);

			Assert::IsTrue(emptyVector.empty());

			NextExtractor* nextExtractor = new NextExtractor(cfgMap, *(pkbStorageApi));
			nextExtractor->extractNext();

			std::vector<std::string> extractedNextVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::NEXT, 1);

			Assert::IsTrue(!extractedNextVector.empty());
			Assert::IsTrue(extractedNextVector.at(0) == std::string("2"));
		}

		TEST_METHOD(extractNext_one_stmt_next_two_stmts)
		{
			std::unordered_map<int, std::unordered_set<int>>* cfgMap = new std::unordered_map<int, std::unordered_set<int>>();

			(*cfgMap)[2].insert(1);
			(*cfgMap)[2].insert(3);

			std::vector<std::string> emptyVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::NEXT, 2);

			Assert::IsTrue(emptyVector.empty());

			NextExtractor* nextExtractor = new NextExtractor(cfgMap, *(pkbStorageApi));
			nextExtractor->extractNext();

			std::vector<std::string> extractedNextVector = pkbQueryApi->getRelationshipRightArg(RelationshipType::NEXT, 2);

			Assert::IsTrue(extractedNextVector.size() == 2);
			Assert::IsTrue(extractedNextVector.at(0) == std::string("1"));
			Assert::IsTrue(extractedNextVector.at(1) == std::string("3"));
		}
	};
};  // namespace UnitTesting
