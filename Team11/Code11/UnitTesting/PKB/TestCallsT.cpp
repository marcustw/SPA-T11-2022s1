#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/CallsT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestCallsT)
	{
	public:
		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_singleCall)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", {"pTwo", "pThree", "pFour"});

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pTwo");
			std::vector<std::string> expectedRes = {"pOne"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_multipleCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", {"pFour"});
			callsTBox.insertCallsT("pTwo", {"pFour"});
			callsTBox.insertCallsT("pThree", {"pFour"});

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pFour");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = {"pOne", "pThree", "pTwo"};

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_nestedCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree" });
			callsTBox.insertCallsT("pTwo", { "pThree" });

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pThree");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "pOne", "pTwo" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_deepNestedCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour", "pFive", "pSix"});
			callsTBox.insertCallsT("pTwo", { "pThree", "pFour", "pFive", "pSix" });
			callsTBox.insertCallsT("pThree", { "pFour", "pFive", "pSix" });
			callsTBox.insertCallsT("pFour", { "pFive", "pSix" });
			callsTBox.insertCallsT("pFive", { "pSix" });

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pSix");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "pOne", "pTwo", "pThree", "pFour", "pFive"};

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_deepNestedComplexCalls1)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour", "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pTwo", { "pThree", "pFour",  "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pFour", { "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pSix", { "pSeven", "pEight"});

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pEight");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "pSix", "pFour", "pTwo", "pOne" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_deepNestedComplexCalls2)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour", "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pTwo", { "pThree", "pFour",  "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pFour", { "pFive", "pSix", "pSeven", "pEight" });
			callsTBox.insertCallsT("pSix", { "pSeven", "pEight" });

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pTwo");
			std::vector<std::string> expectedRes = { "pOne" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCallsT_getCallsTLeftArgLst_nonExistentCall)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour" });

			std::vector<std::string> res = callsTBox.getCallsTLeftArgLst("pFive");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCallsT_getCallsTRightArgLst_singleCall)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour", "pFive" });

			std::vector<std::string> res = callsTBox.getCallsTRightArgLst("pOne");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "pTwo", "pThree", "pFour", "pFive" };

			Assert::IsTrue(expectedRes == resSet);
		}

		TEST_METHOD(insertCallsT_getCallsTRightArgLst_multipleCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pFour" });
			callsTBox.insertCallsT("pTwo", { "pFour" });
			callsTBox.insertCallsT("pThree", { "pFour" });

			std::vector<std::string> res = callsTBox.getCallsTRightArgLst("pOne");
			std::vector<std::string> expectedRes = { "pFour" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCallsT_getCallsTRightArgLst_nestedCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree" });
			callsTBox.insertCallsT("pTwo", { "pThree" });

			std::vector<std::string> res = callsTBox.getCallsTRightArgLst("pOne");
			std::vector<std::string> expectedRes = { "pTwo", "pThree" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCallsT_getCallsTRightArgLst_deepNestedCalls)
		{
			CallsT callsTBox = CallsT();
			callsTBox.insertCallsT("pOne", { "pTwo", "pThree", "pFour", "pFive", "pSix" });
			callsTBox.insertCallsT("pTwo", { "pThree", "pFour", "pFive", "pSix" });
			callsTBox.insertCallsT("pThree", { "pFour", "pFive", "pSix" });
			callsTBox.insertCallsT("pFour", { "pFive", "pSix" });
			callsTBox.insertCallsT("pFive", { "pSix" });

			std::vector<std::string> res = callsTBox.getCallsTRightArgLst("pTwo");
			std::unordered_set<std::string> resSet = std::unordered_set<std::string>(res.begin(), res.end());
			std::unordered_set<std::string> expectedRes = { "pThree", "pFour", "pFive", "pSix" };

			Assert::IsTrue(expectedRes == resSet);
		}
	};
}  // namespace UnitTesting
