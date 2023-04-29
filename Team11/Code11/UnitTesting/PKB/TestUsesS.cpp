#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/UsesS.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestUsesS)
	{
	public:
		TEST_METHOD(insertUsesS_getUsesSLeftArgLst_singleStmt)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });

			std::vector<std::string> res = usesSBox.getUsesSLeftArgLst("x");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSLeftArgLst_multipleStmts)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });
			usesSBox.insertUsesS(3, { "x", "z" });

			std::vector<std::string> res = usesSBox.getUsesSLeftArgLst("x");
			std::vector<std::string> expectedRes = { "1", "3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_gegetUsesSLeftArgLst_containerStatement1)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y", "a", "b" });

			std::vector<std::string> res = usesSBox.getUsesSLeftArgLst("x");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSLeftArgLst_varDoesNotExist1)
		{
			UsesS usesSBox = UsesS();

			std::vector<std::string> res = usesSBox.getUsesSLeftArgLst("z");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSLeftArgLst_varDoesNotExist2)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });

			std::vector<std::string> res = usesSBox.getUsesSLeftArgLst("z");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_singleVar)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_multipleVars)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::vector<std::string> expectedRes = { "x", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_containerStatement1)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y", "a", "b" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "x", "y", "a", "b" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_containerStatement2)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });
			usesSBox.insertUsesS(1, { "a", "b" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "x", "y", "a", "b" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_deepNestedContainerStatement)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });
			usesSBox.insertUsesS(1, { "a", "b" });
			usesSBox.insertUsesS(1, { "c", "d" });
			usesSBox.insertUsesS(1, { "a" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "x", "y", "a", "b", "c", "d" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_StmtDoesNotExist1)
		{
			UsesS usesSBox = UsesS();

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(1);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesS_getUsesSRightArgLst_StmtDoesNotExist2)
		{
			UsesS usesSBox = UsesS();
			usesSBox.insertUsesS(1, { "x", "y" });

			std::vector<std::string> res = usesSBox.getUsesSRightArgLst(2);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
