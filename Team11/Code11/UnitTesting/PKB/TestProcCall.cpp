#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/ProcCall.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestProcCall)
	{
	public:
		TEST_METHOD(insertProcCall_getAllProcCalls_singleCall)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");

			std::vector<std::string> res = procCallBox.getAllProcCalls();
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getAllProcCalls_multipleCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");
			procCallBox.insertProcCall(5, "m4", "m3");

			std::vector<std::string> res = procCallBox.getAllProcCalls();
			std::vector<std::string> expectedRes = { "1", "5" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getProcCallFromStmtIdx_singleCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");

			std::vector<std::string> res = procCallBox.getProcCallFromStmtIdx(1);
			std::vector<std::string> expectedRes = { "m2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getStmtLstFromProcCall_singleCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");
			procCallBox.insertProcCall(5, "m2", "m3");

			std::vector<std::string> res = procCallBox.getStmtLstFromProcCall("m2");
			std::vector<std::string> expectedRes = { "1", "5" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getProcCallLstFromCallerProc_singleCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");

			std::vector<std::string> res = procCallBox.getProcCallLstFromCallerProc("m1");
			std::vector<std::string> expectedRes = { "m2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getProcCallLstFromCallerProc_multipleCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");
			procCallBox.insertProcCall(5, "m3", "m1");

			std::vector<std::string> res = procCallBox.getProcCallLstFromCallerProc("m1");
			std::vector<std::string> expectedRes = { "m2", "m3" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertProcCall_getProcCallLstFromCallerProc_nestedCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");
			procCallBox.insertProcCall(5, "m3", "m1");
			procCallBox.insertProcCall(8, "m4", "m2");

			std::vector<std::string> res1 = procCallBox.getProcCallLstFromCallerProc("m1");
			std::vector<std::string> res2 = procCallBox.getProcCallLstFromCallerProc("m2");
			std::vector<std::string> expectedRes1 = { "m2", "m3" };
			std::vector<std::string> expectedRes2 = { "m4" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertProcCall_getProcCallLstFromCallerProc_deepNestedCalls)
		{
			ProcCall procCallBox = ProcCall();
			procCallBox.insertProcCall(1, "m2", "m1");
			procCallBox.insertProcCall(8, "m4", "m2");
			procCallBox.insertProcCall(5, "m5", "m4");

			std::vector<std::string> res1 = procCallBox.getProcCallLstFromCallerProc("m1");
			std::vector<std::string> res2 = procCallBox.getProcCallLstFromCallerProc("m2");
			std::vector<std::string> res3 = procCallBox.getProcCallLstFromCallerProc("m4");
			std::vector<std::string> expectedRes1 = { "m2" };
			std::vector<std::string> expectedRes2 = { "m4" };
			std::vector<std::string> expectedRes3 = { "m5" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
			Assert::IsTrue(expectedRes3 == res3);
		}
	};
}  // namespace UnitTesting
