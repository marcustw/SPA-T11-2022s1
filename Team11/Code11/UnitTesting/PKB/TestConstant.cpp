#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/Constant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestConstant)
	{
	public:
		TEST_METHOD(insertConst_getAllConsts_singleConst)
		{
			Constant constant = Constant();
			constant.insertConst(3, { 2 });

			std::vector<std::string> res = constant.getAllConsts();
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertConst_getAllConsts_diffConst)
		{
			Constant constantBox = Constant();
			constantBox.insertConst(3, { 2 });
			constantBox.insertConst(4, { 1 });

			std::vector<std::string> res = constantBox.getAllConsts();
			std::vector<std::string> expectedRes = { "2", "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertConst_getAllConsts_multipleConst)
		{
			Constant constantBox = Constant();
			constantBox.insertConst(3, { 2, 4 });

			std::vector<std::string> res = constantBox.getAllConsts();
			std::vector<std::string> expectedRes = { "2", "4" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertConst_getAllConsts_multipleInsertion)
		{
			Constant constantBox = Constant();
			constantBox.insertConst(3, { 2 });
			constantBox.insertConst(3, { 4 });

			std::vector<std::string> res = constantBox.getAllConsts();
			std::vector<std::string> expectedRes = { "2", "4" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertConst_getAllConsts_emptyTable)
		{
			Constant constantBox = Constant();

			std::vector<std::string> res = constantBox.getAllConsts();
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
