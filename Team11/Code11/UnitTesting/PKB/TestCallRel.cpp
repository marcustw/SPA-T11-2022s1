#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/CallRel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestCallRel)
	{
	public:
		TEST_METHOD(insertCalls_getCallsLeftArgLst_singleCall)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo" });

			std::vector<std::string> res = callsBox.getCallsLeftArgLst("pTwo");
			std::vector<std::string> expectedRes = { "pOne" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsLeftArgLst_multipleCalls)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo", "pThree" });

			std::vector<std::string> res = callsBox.getCallsLeftArgLst("pThree");
			std::vector<std::string> expectedRes = { "pOne" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsLeftArgLst_multipleInsertions)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo" });
			callsBox.insertCalls("pThree", { "pFour" });

			std::vector<std::string> res = callsBox.getCallsLeftArgLst("pTwo");
			std::vector<std::string> expectedRes = { "pOne" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsLeftArgLst_nestedCalls)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "PTwo", "pThree" });
			callsBox.insertCalls("pTwo", { "pFour" });

			std::vector<std::string> res = callsBox.getCallsLeftArgLst("pFour");
			std::vector<std::string> expectedRes = { "pTwo" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsLeftArgLst_nonExistentCall)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo", "pThree" });

			std::vector<std::string> res = callsBox.getCallsLeftArgLst("pFour");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsRightArgLst_singleCall)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo", "pThree" });

			std::vector<std::string> res = callsBox.getCallsRightArgLst("pOne");
			std::vector<std::string> expectedRes = { "pTwo", "pThree"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsRightArgLst_multipleCalls)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo" });
			callsBox.insertCalls("pOne", { "pThree" });

			std::vector<std::string> res = callsBox.getCallsRightArgLst("pOne");
			std::vector<std::string> expectedRes = { "pTwo", "pThree" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsRightArgLst_nestedCalls)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo", "pThree" });
			callsBox.insertCalls("pTwo", { "pFour" });

			std::vector<std::string> res = callsBox.getCallsRightArgLst("pTwo");
			std::vector<std::string> expectedRes = { "pFour" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertCalls_getCallsRightArgLst_nonExistentCall)
		{
			CallRel callsBox = CallRel();
			callsBox.insertCalls("pOne", { "pTwo", "pThree" });

			std::vector<std::string> res = callsBox.getCallsRightArgLst("pFour");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
