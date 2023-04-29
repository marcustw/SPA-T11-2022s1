#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/Follows.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestFollows)
	{
	public:
		TEST_METHOD(insertFollows_getFollowLeftArg_singleInsertion)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);

			std::vector<std::string> res = followsBox.getFollowLeftArg(2);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollows_getFollowLeftArg_multipleInsertion)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);
			followsBox.insertFollows(2, 3);

			std::vector<std::string> res = followsBox.getFollowLeftArg(3);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollows_getFollowLeftArg_nonExistentStatement)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);
			followsBox.insertFollows(2, 3);

			std::vector<std::string> res = followsBox.getFollowLeftArg(4);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollows_getFollowRightArg_singleInsertion)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);

			std::vector<std::string> res = followsBox.getFollowRightArg(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollows_getFollowRightArg_multipleInsertion)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);
			followsBox.insertFollows(3, 4);

			std::vector<std::string> res = followsBox.getFollowRightArg(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollows_getFollowRightArg_noFollowingStatement)
		{
			Follows followsBox = Follows();
			followsBox.insertFollows(1, 2);

			std::vector<std::string> res = followsBox.getFollowRightArg(2);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
