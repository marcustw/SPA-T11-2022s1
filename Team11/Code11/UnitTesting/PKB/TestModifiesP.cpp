#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/ModifiesP.h"
#include "../source/Common/SPAException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifiesP)
	{
	public:
		TEST_METHOD(insertModifiesP_getModifiesPVarLstFromProc_singleProc)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });

			std::vector<std::string> res = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPVarLstFromProc_multipleInsertion1)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x", "y" });

			std::vector<std::string> res = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x", "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPVarLstFromProc_multipleInsertion2)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x", "y"});
			modifiesPBox.insertModifiesP("m1", { "z" });

			std::vector<std::string> res = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "x", "y", "z" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPVarLstFromProc_procDoesNotExist)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });

			std::vector<std::string> res = modifiesPBox.getModifiesPVarLstFromProc("m2");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPTable_singleProc)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("main", {"x"});

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["main"] = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertModifiesP_getModifiesPTable_multipleProcs)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", {"x"});
			modifiesPBox.insertModifiesP("m2", {"w"});

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x"};
			expectedRes["m2"] = {"w"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPVarLstFromProc_singleProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });
			modifiesPBox.insertModifiesP("m2", { "y" });
			modifiesPBox.insertProcCall("m2", "m1");

			std::vector<std::string> res1 = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> res2 = modifiesPBox.getModifiesPVarLstFromProc("m2");
			std::vector<std::string> expectedRes1 = { "x", "y" };
			std::vector<std::string> expectedRes2 = { "y" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertProcCall_getModifiesPVarLstFromProc_overlapVars)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x", "y" });
			modifiesPBox.insertModifiesP("m2", { "y" });
			modifiesPBox.insertProcCall("m2", "m1");

			std::vector<std::string> res1 = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> res2 = modifiesPBox.getModifiesPVarLstFromProc("m2");
			std::vector<std::string> expectedRes1 = { "x", "y" };
			std::vector<std::string> expectedRes2 = { "y" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertProcCall_getModifiesPVarLstFromProc_deepNestedProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "a" });
			modifiesPBox.insertModifiesP("m2", { "b" });
			modifiesPBox.insertModifiesP("m3", { "c" });
			modifiesPBox.insertModifiesP("m4", { "d" });
			modifiesPBox.insertModifiesP("m5", { "e" });
			modifiesPBox.insertProcCall("m5", "m4");
			modifiesPBox.insertProcCall("m4", "m3");
			modifiesPBox.insertProcCall("m3", "m2");
			modifiesPBox.insertProcCall("m2", "m1");

			std::vector<std::string> res = modifiesPBox.getModifiesPVarLstFromProc("m1");
			std::vector<std::string> expectedRes = { "a", "b", "c", "d", "e" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_singleProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", {"x"});
			modifiesPBox.insertModifiesP("m2", {"y"});
			modifiesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x", "y"};
			expectedRes["m2"] = {"y"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_multipleProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", {"x"});
			modifiesPBox.insertModifiesP("m2", {"y"});
			modifiesPBox.insertModifiesP("m3", {"z"});
			modifiesPBox.insertProcCall("m2", "m1");
			modifiesPBox.insertProcCall("m3", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x", "y", "z"};
			expectedRes["m2"] = { "y" };
			expectedRes["m3"] = { "z" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_overlapVars)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });
			modifiesPBox.insertModifiesP("m2", { "y" });
			modifiesPBox.insertModifiesP("m3", { "x" });
			modifiesPBox.insertProcCall("m2", "m1");
			modifiesPBox.insertProcCall("m3", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x", "y"};
			expectedRes["m2"] = {"y"};
			expectedRes["m3"] = {"x"};

			Assert::IsTrue(expectedRes == res);
			}

		TEST_METHOD(insertProcCall_getModifiesPTable_nestedProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });
			modifiesPBox.insertModifiesP("m2", { "y" });
			modifiesPBox.insertModifiesP("m3", { "z" });
			modifiesPBox.insertProcCall("m3", "m2");
			modifiesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x", "y", "z"};
			expectedRes["m2"] = {"y", "z"};
			expectedRes["m3"] = {"z"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_nestedOverlapProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "x" });
			modifiesPBox.insertModifiesP("m2", { "y" });
			modifiesPBox.insertModifiesP("m3", { "y" });
			modifiesPBox.insertProcCall("m2", "m1");
			modifiesPBox.insertProcCall("m3", "m2");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = {"x", "y"};
			expectedRes["m2"] = {"y"};
			expectedRes["m3"] = {"y"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_deepNestedProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "a" });
			modifiesPBox.insertModifiesP("m2", { "b" });
			modifiesPBox.insertModifiesP("m3", { "c" });
			modifiesPBox.insertModifiesP("m4", { "d" });
			modifiesPBox.insertModifiesP("m5", { "e" });
			modifiesPBox.insertProcCall("m5", "m4");
			modifiesPBox.insertProcCall("m4", "m3");
			modifiesPBox.insertProcCall("m3", "m2");
			modifiesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::vector<std::string>> expectedRes;
			expectedRes["m1"] = { "a", "b", "c", "d", "e" };
			expectedRes["m2"] = { "b", "c", "d", "e" };
			expectedRes["m3"] = { "c", "d", "e" };
			expectedRes["m4"] = { "d", "e" };
			expectedRes["m5"] = { "e" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getModifiesPTable_deeopNestedOverlapProcCall)
		{
			ModifiesP modifiesPBox = ModifiesP();
			modifiesPBox.insertModifiesP("m1", { "a", "b" });
			modifiesPBox.insertModifiesP("m2", { "b" });
			modifiesPBox.insertModifiesP("m3", { "c", "e", "g" });
			modifiesPBox.insertModifiesP("m4", { "d" });
			modifiesPBox.insertModifiesP("m5", { "e", "f" });
			modifiesPBox.insertProcCall("m5", "m4");
			modifiesPBox.insertProcCall("m4", "m3");
			modifiesPBox.insertProcCall("m3", "m2");
			modifiesPBox.insertProcCall("m2", "m1");

			std::unordered_map<std::string, std::vector<std::string>> res = modifiesPBox.getModifiesPTable();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedRes;
			expectedRes["m1"] = { "a", "b", "c", "d", "e", "f", "g" };
			expectedRes["m2"] = { "b", "c", "d", "e", "f", "g" };
			expectedRes["m3"] = { "c", "d", "e", "f", "g" };
			expectedRes["m4"] = { "d", "e", "f" };
			expectedRes["m5"] = { "e", "f" };

			for (auto& row : res) {
				std::string key = row.first;
				std::vector<std::string> varLst = row.second;
				std::unordered_set<std::string> varSet = std::unordered_set<std::string>(varLst.begin(), varLst.end());
				Assert::IsTrue(expectedRes.at(key) == varSet);
			}
		}
	};
}  // namespace UnitTesting
