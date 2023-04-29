#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/UsesP.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestUsesP)
	{
	public:
		TEST_METHOD(insertUsesP_getUsesPVarLstFromProc_procExist)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesP_getUsesPVarLstFromProc_multipleInsertion1)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m1", { "z" });

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x", "y", "z"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesP_getUsesPVarLstFromProc_multipleInsertion2)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m1", { "y", "z" });

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x", "y", "z" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertUsesP_getUsesPVarLstFromProc_procDoesNotExist)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m2");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
		TEST_METHOD(insertUsesP_getUsesPTable_singleProc)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("main", { "x", "y" });

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "main", { "x", "y" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPTable_multipleProcs)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y" } });
			expectedRes.insert({ "m2", { "y", "z" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getUsesPVarLstFromProc_multipleProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });
			usesPBox.insertUsesP("m3", { "a", "b" });
			usesPBox.insertProcCall("m2", "m1");
			usesPBox.insertProcCall("m3", "m1");

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m1");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "x", "y", "z", "a", "b" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertProcCall_getUsesPVarLstFromProc_deepNestedProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });
			usesPBox.insertUsesP("m3", { "w", "x" });
			usesPBox.insertUsesP("m4", { "a", "z" });
			usesPBox.insertUsesP("m5", { "b", "y" });
			usesPBox.insertProcCall("m5", "m4");
			usesPBox.insertProcCall("m4", "m3");
			usesPBox.insertProcCall("m3", "m2");
			usesPBox.insertProcCall("m2", "m1");

			std::vector<std::string> res = usesPBox.getUsesPVarLstFromProc("m1");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "x", "y", "z", "w", "a", "b" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertProcCall_getUsesPTable_singleProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "z" });
			usesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y", "z" } });
			expectedRes.insert({ "m2", { "z" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getUsesPTable_multipleProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "z" });
			usesPBox.insertUsesP("m3", { "w" });
			usesPBox.insertProcCall("m2", "m1");
			usesPBox.insertProcCall("m3", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y", "z", "w" } });
			expectedRes.insert({ "m2", { "z" } });
			expectedRes.insert({ "m3", { "w" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getUsesPTable_overlapVars)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });
			usesPBox.insertUsesP("m3", { "w", "x"});
			usesPBox.insertProcCall("m2", "m1");
			usesPBox.insertProcCall("m3", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y", "z", "w" } });
			expectedRes.insert({ "m2", { "y", "z" } });
			expectedRes.insert({ "m3", { "w", "x" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getUsesPTable_nestedProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });
			usesPBox.insertUsesP("m3", { "w", "x" });
			usesPBox.insertProcCall("m3", "m2");
			usesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y", "z", "w" } });
			expectedRes.insert({ "m2", { "y", "z", "w", "x" } });
			expectedRes.insert({ "m3", { "w", "x" } });

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getUsesPTable_deepNestedProcCall)
		{
			UsesP usesPBox = UsesP();
			usesPBox.insertUsesP("m1", { "x", "y" });
			usesPBox.insertUsesP("m2", { "y", "z" });
			usesPBox.insertUsesP("m3", { "w", "x" });
			usesPBox.insertUsesP("m4", { "a", "z" });
			usesPBox.insertUsesP("m5", { "b", "y" });
			usesPBox.insertProcCall("m5", "m4");
			usesPBox.insertProcCall("m4", "m3");
			usesPBox.insertProcCall("m3", "m2");
			usesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = usesPBox.getUsesPTable();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedRes;
			expectedRes.insert({ "m1", { "x", "y", "z", "w", "a", "b" } });
			expectedRes.insert({ "m2", { "x", "y", "z", "w", "a", "b" } });
			expectedRes.insert({ "m3", { "x", "y", "z", "w", "a", "b" } });
			expectedRes.insert({ "m4", { "y", "z", "a", "b" }});
			expectedRes.insert({ "m5", { "b", "y" } });

			for (auto& row : res) {
				std::string key = row.first;
				std::vector<std::string> varLst = row.second;
				std::unordered_set<std::string> varSet = std::unordered_set<std::string>(varLst.begin(), varLst.end());
				Assert::IsTrue(expectedRes.at(key) == varSet);
			}
		}
	};
}  // namespace UnitTesting
