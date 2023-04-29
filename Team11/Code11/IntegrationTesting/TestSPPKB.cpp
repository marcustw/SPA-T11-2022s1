#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/SP/AST/ASTGenerator.h"
#include "../source/SP/Visitors/EntityVisitor.h"
#include "../source/SP/Visitors/Visitor.h"

#include "../source/PKB/PKB.h"
#include "../source/PKB/PKBStorageAPI.h"
#include "../source/PKB/PKBQueryAPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(SPPKB)
	{
	private:
		std::string source_while = "procedure sumDigits { read number; sum = 0;"
			" while (number > 0) { digit = number % 10; sum = sum + digit; "
			"number = number / 10; } print sum; }";

		std::string source_if = "procedure printAscending { read num1; read num2;"
			"noSwap = 0; if (num1 > num2) then { temp = num1; num1 = num2;"
			" num2 = temp; } else { noSwap = 1;} print num1; print num2; print noSwap;}";

		std::string source_while_nestedIf = "procedure main { y = x + 3; while ((x != 0)"
			" && (y != 0)) { a = b + 1; if (a == 0) then{ c = 1; }"
			"else { c = c / 5; print d; } x = y * c; }}";

		std::string source_multi_proc = "procedure main { read x1; read x2; x3 = (x1 + 1) / 2 - 3; }"
			" procedure second { x4 = 4; print x4; } procedure third { x5 = (5 + 6) / (7 * 8); x6 = 9;}";

		std::string source_multi_while = "procedure multipleWhile {while (x1 == 3) {x2 = x2 + 5;"
			"x3 = x3;if (x4 == x4) then{while (x5 == 3) {x6 = x6 + 5; x1 = x1;} x2 = x2;}"
			"else {read x3;} } while (x4 == x4) {read x5; x5 = x6; } while (x1 >= 2) {if (x2 == x3) then{"
			"while (x3 == 3) {x4 = x4 + 5;x6 = x5;}x5 = x5;}else {read x6;}}}";

		std::string source_multi_if = "procedure multipleIf {if (x1 == 1) then { print x2; }"
			"else { if (x3 < 3) then { if (x5 >= 5) then {x6 = 6;}"
			" else { read x3;}} else { read x4;}}}";

	public:
		TEST_METHOD(SPPKB_source_while)
		{
			ASTGenerator* generator = new ASTGenerator(source_while);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("sumDigits") == pkbQueryApi->getAllProcedures().at(0));

			Assert::AreEqual(size_t(4), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(3), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("sum"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("number"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("digit"), pkbQueryApi->getAllVars().at(2));

			Assert::AreEqual(size_t(2), pkbQueryApi->getAllConsts().size());
			Assert::AreEqual(size_t(0), pkbQueryApi->getAllIfContainers().size());
			Assert::AreEqual(size_t(1), pkbQueryApi->getAllWhileContainers().size());
		}

		TEST_METHOD(SPPKB_source_if)
		{
			ASTGenerator* generator = new ASTGenerator(source_if);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("printAscending") == pkbQueryApi->getAllProcedures().at(0));

			Assert::AreEqual(size_t(5), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(4), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("num1"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("num2"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("noSwap"), pkbQueryApi->getAllVars().at(2));
			Assert::AreEqual(std::string("temp"), pkbQueryApi->getAllVars().at(3));

			Assert::AreEqual(size_t(2), pkbQueryApi->getAllConsts().size());
			Assert::AreEqual(size_t(1), pkbQueryApi->getAllIfContainers().size());
			Assert::AreEqual(size_t(0), pkbQueryApi->getAllWhileContainers().size());
		}

		TEST_METHOD(SPPKB_source_while_nestedIf)
		{
			ASTGenerator* generator = new ASTGenerator(source_while_nestedIf);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("main") == pkbQueryApi->getAllProcedures().at(0));

			Assert::AreEqual(size_t(5), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(6), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("a"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("y"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("x"), pkbQueryApi->getAllVars().at(2));
			Assert::AreEqual(std::string("b"), pkbQueryApi->getAllVars().at(3));
			Assert::AreEqual(std::string("c"), pkbQueryApi->getAllVars().at(4));
			Assert::AreEqual(std::string("d"), pkbQueryApi->getAllVars().at(5));

			Assert::AreEqual(size_t(4), pkbQueryApi->getAllConsts().size());
			Assert::AreEqual(size_t(1), pkbQueryApi->getAllIfContainers().size());
			Assert::AreEqual(size_t(1), pkbQueryApi->getAllWhileContainers().size());
		}

		TEST_METHOD(SPPKB_source_multi_proc)
		{
			ASTGenerator* generator = new ASTGenerator(source_multi_proc);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(3), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("main") == pkbQueryApi->getAllProcedures().at(0));
			Assert::IsTrue(std::string("second") == pkbQueryApi->getAllProcedures().at(1));
			Assert::IsTrue(std::string("third") == pkbQueryApi->getAllProcedures().at(2));


			Assert::AreEqual(size_t(4), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(6), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("x1"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("x2"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("x3"), pkbQueryApi->getAllVars().at(2));
			Assert::AreEqual(std::string("x4"), pkbQueryApi->getAllVars().at(3));
			Assert::AreEqual(std::string("x5"), pkbQueryApi->getAllVars().at(4));
			Assert::AreEqual(std::string("x6"), pkbQueryApi->getAllVars().at(5));

			Assert::AreEqual(size_t(9), pkbQueryApi->getAllConsts().size());
		}

		TEST_METHOD(SPPKB_source_multi_while)
		{
			ASTGenerator* generator = new ASTGenerator(source_multi_while);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("multipleWhile") == pkbQueryApi->getAllProcedures().at(0));

			Assert::AreEqual(size_t(5), pkbQueryApi->getAllWhileContainers().size());

			Assert::AreEqual(size_t(9), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(6), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("x1"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("x2"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("x3"), pkbQueryApi->getAllVars().at(2));
			Assert::AreEqual(std::string("x4"), pkbQueryApi->getAllVars().at(3));
			Assert::AreEqual(std::string("x5"), pkbQueryApi->getAllVars().at(4));
			Assert::AreEqual(std::string("x6"), pkbQueryApi->getAllVars().at(5));

			Assert::AreEqual(size_t(3), pkbQueryApi->getAllConsts().size());
		}

		TEST_METHOD(SPPKB_source_multi_if)
		{
			ASTGenerator* generator = new ASTGenerator(source_multi_if);
			ProgrammeNode* root = generator->generate();

			PKB* pkb = new PKB();
			PKBStorageAPI* pkbStorageApi = new PKBStorageAPI(pkb);
			PKBQueryAPI* pkbQueryApi = new PKBQueryAPI(pkb);

			EntityVisitor* entityVisitor = new EntityVisitor(*pkbStorageApi);

			root->accept(entityVisitor);

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllProcedures().size());
			Assert::IsTrue(std::string("multipleIf") == pkbQueryApi->getAllProcedures().at(0));

			Assert::AreEqual(size_t(1), pkbQueryApi->getAllAssignments().size());

			Assert::AreEqual(size_t(6), pkbQueryApi->getAllVars().size());
			Assert::AreEqual(std::string("x1"), pkbQueryApi->getAllVars().at(0));
			Assert::AreEqual(std::string("x2"), pkbQueryApi->getAllVars().at(1));
			Assert::AreEqual(std::string("x3"), pkbQueryApi->getAllVars().at(2));
			Assert::AreEqual(std::string("x5"), pkbQueryApi->getAllVars().at(3));
			Assert::AreEqual(std::string("x6"), pkbQueryApi->getAllVars().at(4));
			Assert::AreEqual(std::string("x4"), pkbQueryApi->getAllVars().at(5));

			Assert::AreEqual(size_t(4), pkbQueryApi->getAllConsts().size());
			Assert::AreEqual(size_t(3), pkbQueryApi->getAllIfContainers().size());
		}
	};
}  // namespace IntegrationTesting
