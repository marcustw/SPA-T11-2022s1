#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/ModifiesS.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifiesS)
	{
	public:
		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_singleStmt)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSLeftArgLst("z");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_multipleStmt)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });
			modifiesSBox.insertModifiesS(2, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSLeftArgLst("z");
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_repeatedStmtSameVar)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSLeftArgLst("z");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_containerStatement1)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z", "y" });

			std::vector<std::string> res1 = modifiesSBox.getModifiesSLeftArgLst("z");
			std::vector<std::string> res2 = modifiesSBox.getModifiesSLeftArgLst("y");
			std::vector<std::string> expectedRes1 = { "1" };
			std::vector<std::string> expectedRes2 = { "1" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_containerStatement2)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });
			modifiesSBox.insertModifiesS(1, { "y" });

			std::vector<std::string> res1 = modifiesSBox.getModifiesSLeftArgLst("z");
			std::vector<std::string> res2 = modifiesSBox.getModifiesSLeftArgLst("y");
			std::vector<std::string> expectedRes1 = { "1" };
			std::vector<std::string> expectedRes2 = { "1" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_varDoesNotExist1)
		{
			ModifiesS modifiesSBox = ModifiesS();

			std::vector<std::string> res = modifiesSBox.getModifiesSLeftArgLst("w");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSLeftArgLst_varDoesNotExist2)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSLeftArgLst("w");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_singleVar)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(1);
			std::vector<std::string> expectedRes = { "z" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_containerStatement1)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });
			modifiesSBox.insertModifiesS(1, { "y" });

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(1);
			std::vector<std::string> expectedRes = { "z", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_containerStatement2)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z", "y"});

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(1);
			std::vector<std::string> expectedRes = { "z", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_deepNestedContainerStatement)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });
			modifiesSBox.insertModifiesS(1, { "y", "x"});
			modifiesSBox.insertModifiesS(1, { "x", "w" });
			modifiesSBox.insertModifiesS(1, { "a", "w"});
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "z", "y", "w", "x", "a" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_stmtDoesNotExist1)
		{
			ModifiesS modifiesSBox = ModifiesS();

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(1);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesS_getModifiesSRightArgLst_stmtDoesNotExist2)
		{
			ModifiesS modifiesSBox = ModifiesS();
			modifiesSBox.insertModifiesS(1, { "z" });

			std::vector<std::string> res = modifiesSBox.getModifiesSRightArgLst(2);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
