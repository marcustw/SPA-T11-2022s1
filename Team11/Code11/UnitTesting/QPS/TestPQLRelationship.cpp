#include "stdafx.h"
#include "CppUnitTest.h"

#include "QPS/Parser/PQLRelationship.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPQLRelationship)
	{
	public:
		TEST_METHOD(invalidModifies_SemanticError)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SEMANTIC_ERROR));
			}
		}

		TEST_METHOD(invalidUses_SemanticError)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SEMANTIC_ERROR));
			}
		}

		TEST_METHOD(invalidUses_SyntaxError_rhsInt)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidModifies_SyntaxError_rhsInt)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::INTEGER, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}


		TEST_METHOD(invalidParent_SyntaxError_lhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidParent_SyntaxError_rhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidParentT_SyntaxError_lhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT_T;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidParentT_SyntaxError_rhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT_T;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidFollows_SyntaxError_lhsIdent)
		{
			RelationshipType relType = RelationshipType::FOLLOWS;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidFollows_SyntaxError_rhsIdent)
		{
			RelationshipType relType = RelationshipType::FOLLOWS;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}


		TEST_METHOD(invalidFollowsT_SyntaxError_lhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT_T;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(invalidFollowsT_SyntaxError_rhsIdent)
		{
			RelationshipType relType = RelationshipType::PARENT_T;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::IDENT, "1");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			auto validateResult = [&pqlRelRef, this] {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			};

			// Ensure exception is thrown
			Assert::ExpectException<QPSException>(validateResult);

			try {
				std::unordered_set<std::string> allProcedures = { "mainTest" };
				DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
				pqlRelRef.verify(declareMap);
			}
			catch (QPSException s) {
				Assert::AreEqual(std::string(s.what()), std::string(QPSException::QPS_SYNTAX_ERROR));
			}
		}

		TEST_METHOD(validUses_usesS)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::USES_S);
		}

		TEST_METHOD(validUses_lhsIdent_usesP)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::VARIABLE } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::USES_P);
		}

		TEST_METHOD(validUses_lhsSyn_Proc_usesP)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::PROCEDURE } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::USES_P);
		}

		TEST_METHOD(validUses_lhsSyn_Call_usesP)
		{
			RelationshipType relType = RelationshipType::USES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::CALL } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::USES_P);
		}

		TEST_METHOD(validModifies_modifiesS)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::SYNONYM, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::MODIFIES_S);
		}

		TEST_METHOD(validModifies_lhsIdent_modifiesP)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::ASSIGN } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::MODIFIES_P);
		}

		TEST_METHOD(validModifies_lhsSyn_Proc_modifiesP)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::PROCEDURE } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::MODIFIES_P);
		}

		TEST_METHOD(validModifies_lhsSyn_Call_modifiesP)
		{
			RelationshipType relType = RelationshipType::MODIFIES;
			PQLReference lhsRef = std::pair(PQLReferenceType::IDENT, "a");
			PQLReference rhsRef = std::pair(PQLReferenceType::WILDCARD, "_");
			PQLRelationship pqlRelRef = PQLRelationship(relType, lhsRef, rhsRef);

			std::unordered_set<std::string> allProcedures = { "mainTest" };
			DeclareMap declareMap = { {"a", EntityType::CALL } };
			pqlRelRef.verify(declareMap);

			Assert::IsTrue(pqlRelRef.getRelType() == RelationshipType::MODIFIES_P);
		}
	};
}  // namespace UnitTesting
