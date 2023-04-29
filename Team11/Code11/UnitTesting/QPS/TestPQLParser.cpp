#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/QPS/Parser/PQLParser.h"
#include "../source/QPS/Evaluator/QPSEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Includes PQLParser and PQLQueryObject
namespace UnitTesting
{
	TEST_CLASS(TestPQLParser)
	{
	public:
		TEST_METHOD(parseQuery_declarationAndSelectVariableOnly)
		{
			std::string query = "variable v; Select v";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("v") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::VARIABLE);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("v") == 0);
		}


		TEST_METHOD(parseQuery_declarationAndSelectConstantOnly)
		{
			std::string query = "constant c; Select c";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("c") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::CONSTANT);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("c") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectStatementsOnly)
		{
			std::string query = "stmt s; Select s";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("s") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::STMT);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("s") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectReadOnly)
		{
			std::string query = "read re; Select re";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("re") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::READ);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("re") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectPrintOnly)
		{
			std::string query = "print p2; Select p2";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("p2") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::PRINT);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("p2") == 0);
		}


		TEST_METHOD(parseQuery_declarationAndSelectProcedureOnly)
		{
			std::string query = "procedure pr0c3dur5; Select pr0c3dur5";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("pr0c3dur5") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::PROCEDURE);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("pr0c3dur5") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectIfsOnly)
		{
			std::string query = "if ifs; Select ifs";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("ifs") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::IF);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("ifs") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectWhilesOnly)
		{
			std::string query = "while ww; Select ww";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("ww") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::WHILE);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("ww") == 0);
		}

		TEST_METHOD(parseQuery_declarationAndSelectAssignsOnly)
		{
			std::string query = "assign a123; Select a123";
			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 1);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("a123") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().empty());
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::ASSIGN);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("a123") == 0);
		}

		TEST_METHOD(parseQuery_invalidDeclaration)
		{
			std::string query = "assign 123a; Select 123a";
			auto wrapperQuery = [&query, this] {
				PQLParser pqlParser = PQLParser();
				PQLQueryObject queryObj = pqlParser.parseQuery(query);
			};
			Assert::ExpectException<QPSException>(wrapperQuery);
		}


		TEST_METHOD(parseQuery_valid_oneModifiesLhsSynRhsWildcardNoPattern)
		{
			std::string query = "assign a; variable v; Select a such that Modifies(a, _)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLDeclaration().size() == 2);
			Assert::IsTrue(queryObj.getPQLSynonym().front().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().front().second.compare("a") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLDeclaration().front().first == EntityType::ASSIGN);
			Assert::IsTrue(queryObj.getPQLDeclaration().front().second.compare("a") == 0);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::MODIFIES);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "a");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::WILDCARD);
		}

		TEST_METHOD(parseQuery_valid_oneUsesLhsSynRhsSynNoPattern)
		{
			std::string query = "assign a; variable v; Select a such that Uses(a, v)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::USES);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "a");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "v");
		}

		TEST_METHOD(parseQuery_valid_oneAffects)
		{
			std::string query = "assign a; Select a such that Affects (a, 10)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::AFFECTS);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "a");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "10");
		}

		TEST_METHOD(parseQuery_valid_oneAffects_T)
		{
			std::string query = "assign a; Select a such that Affects* (a, 10)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::AFFECTS_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "a");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "10");
		}

		TEST_METHOD(parseQuery_valid_oneCalls)
		{
			std::string query = "procedure p,q; Select p such that Calls(p, _)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::CALL);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "p");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::WILDCARD);
		}

		TEST_METHOD(parseQuery_valid_oneCalls_T)
		{
			std::string query = "procedure p; Select p such that Calls*(p, \"Third\")";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::CALL_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "p");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::IDENT);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "Third");
		}

		TEST_METHOD(parseQuery_valid_oneNext)
		{
			std::string query = "stmt s; Select s such that Next (5, s)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::NEXT);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "5");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "s");
		}

		TEST_METHOD(parseQuery_valid_twoNext_T)
		{
			std::string query = "stmt s; Select s such that Next* (5, s) and Next* (s, 12)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 2);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::NEXT_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "5");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "s");

			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRelType() == RelationshipType::NEXT_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().second == "s");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().second == "12");
		}

		TEST_METHOD(parseQuery_valid_twoNext_T_multiSuchThat)
		{
			std::string query = "stmt s; Select s such that Next* (5, s) such that Next* (s, 12)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 2);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::NEXT_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "5");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "s");

			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRelType() == RelationshipType::NEXT_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().second == "s");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().second == "12");
		}

		TEST_METHOD(parseQuery_valid_selectTuple)
		{
			std::string query = "stmt s1, s2; Select <s1,s2> such that Follows(s1,s2)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.getPQLSynonym().size() == 2);
			Assert::AreEqual(queryObj.isSelectBoolean(), false);
			Assert::IsTrue(queryObj.getPQLSynonym().at(0).first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().at(0).second == "s1");
			Assert::IsTrue(queryObj.getPQLSynonym().at(1).first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLSynonym().at(1).second == "s2");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::FOLLOWS);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "s1");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "s2");
		}

		TEST_METHOD(parseQuery_valid_selectBoolean)
		{
			std::string query = "Select BOOLEAN such that Next* (2, 9)";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 1);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::IsTrue(queryObj.isSelectBoolean());
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::NEXT_T);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "2");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::INTEGER);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "9");
		}

		TEST_METHOD(parseQuery_valid_with)
		{
			std::string query =
				"procedure p, q; Select p such that Calls (p, q) with q.procName = \"Third\" such that Modifies (p, \"i\")";

			PQLParser pqlParser = PQLParser();
			PQLQueryObject queryObj = pqlParser.parseQuery(query);
			Assert::IsTrue(queryObj.getPQLWithClauses().size() == 1);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().size() == 2);
			Assert::IsTrue(queryObj.getPQLPatternRef().empty());
			Assert::AreEqual(queryObj.isSelectBoolean(), false);

			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRelType() == RelationshipType::CALL);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getLhsRef().second == "p");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(0).getRhsRef().second == "q");

			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRelType() == RelationshipType::MODIFIES);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().first == PQLReferenceType::SYNONYM);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getLhsRef().second == "p");
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().first == PQLReferenceType::IDENT);
			Assert::IsTrue(queryObj.getPQLRelationshipRef().at(1).getRhsRef().second == "i");

			Assert::IsTrue(queryObj.getPQLWithClauses().at(0).getLhsRef().first == PQLReferenceType::PROC_NAME);
			Assert::IsTrue(queryObj.getPQLWithClauses().at(0).getLhsRef().second == "q");
			Assert::IsTrue(queryObj.getPQLWithClauses().at(0).getRhsRef().first == PQLReferenceType::IDENT);
			Assert::IsTrue(queryObj.getPQLWithClauses().at(0).getRhsRef().second == "Third");
		}
	};
}  // namespace UnitTesting
