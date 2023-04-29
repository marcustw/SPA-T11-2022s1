#include "stdafx.h"
#include "CppUnitTest.h"

#include "QPS/Parser/PQLPattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPQLPattern)
	{
	public:
		TEST_METHOD(pqlPatternInvalid_missingAssignSyn_SemanticError)
		{
			PQLReference entRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLExpression expression = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern("a", PQLPatternType::PATTERN_A, entRef, expression, 2);

			auto validateResult = [&pqlPattern, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { { "a1", EntityType::ASSIGN } };
				pqlPattern.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a1", EntityType::ASSIGN } };
				pqlPattern.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SEMANTIC_ERROR));
			}
		}

		TEST_METHOD(pqlPatternInvalid_missingLhsSyn_SemanticError)
		{
			PQLReference entRef = std::pair(PQLReferenceType::SYNONYM, "c");
			PQLExpression expression = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern("a", PQLPatternType::PATTERN_A, entRef, expression, 2);

			auto validateResult = [&pqlPattern, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { { "a", EntityType::ASSIGN } };
				pqlPattern.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlPattern.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SEMANTIC_ERROR));
			}
		}


		TEST_METHOD(pqlPatternInvalid_MoreArgsThanRequiredPatternA_SemanticError)
		{
			PQLReference entRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLExpression expression = std::pair(PQLExpressionType::WILDCARD, "_");
			PQLPattern pqlPattern = PQLPattern("a", PQLPatternType::PATTERN_A, entRef, expression, 3);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlPattern.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SEMANTIC_ERROR));
			}
		}
	};
}  // namespace UnitTesting
