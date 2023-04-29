#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Relationship/FollowsT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestFollowsT)
	{
	public:
		TEST_METHOD(insertFollowsT_getFollowsTLeftArgLst_singleInsertion)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2 });

			std::vector<std::string> res = followsTBox.getFollowsTLeftArgLst(2);
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}
		TEST_METHOD(insertFollowsT_getFollowsTLeftArgLst_multipleInsertion1)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2, 3 });
			followsTBox.insertFollowsT(2, { 3 });

			std::vector<std::string> res1 = followsTBox.getFollowsTLeftArgLst(3);
			std::vector<std::string> res2 = followsTBox.getFollowsTLeftArgLst(2);
			std::vector<std::string> expectedRes1 = { "1", "2" };
			std::vector<std::string> expectedRes2 = { "1" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertFollowsT_getFollowsTLeftArgLst_multipleInsertion2)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2 });
			followsTBox.insertFollowsT(2, { 3 });
			followsTBox.insertFollowsT(1, { 3 });

			std::vector<std::string> res1 = followsTBox.getFollowsTLeftArgLst(3);
			std::vector<std::string> res2 = followsTBox.getFollowsTLeftArgLst(2);
			std::vector<std::string> expectedRes1 = { "2", "1" };
			std::vector<std::string> expectedRes2 = { "1" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertFollowsT_getFollowsTLeftArgLst_multipleInsertion3)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 4, 5, 7, 8 });
			followsTBox.insertFollowsT(4, { 5, 7, 8 });
			followsTBox.insertFollowsT(5, { 7, 8 });
			followsTBox.insertFollowsT(7, { 8 });

			std::vector<std::string> res = followsTBox.getFollowsTLeftArgLst(8);
			std::vector<std::string> expectedRes = { "1", "4", "5", "7" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollowsT_getFollowsTLeftArgLst_nonExistentRightArg)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2, 3 });
			followsTBox.insertFollowsT(2, { 3 });

			std::vector<std::string> res = followsTBox.getFollowsTLeftArgLst(4);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollowsT_getFollowsTRightArgLst_singleInsertion)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2 });

			std::vector<std::string> res = followsTBox.getFollowsTRightArgLst(1);
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertFollowsT_getFollowsTRightArgLst_multipleInsertion1)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2, 3 });
			followsTBox.insertFollowsT(2, { 3 });

			std::vector<std::string> res1 = followsTBox.getFollowsTRightArgLst(1);
			std::vector<std::string> res2 = followsTBox.getFollowsTRightArgLst(2);
			std::vector<std::string> expectedRes1 = { "2", "3" };
			std::vector<std::string> expectedRes2 = { "3" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertFollowsT_getFollowsTRightArgLst_multipleInsertion2)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2 });
			followsTBox.insertFollowsT(2, { 3 });
			followsTBox.insertFollowsT(1, { 3 });

			std::vector<std::string> res1 = followsTBox.getFollowsTRightArgLst(1);
			std::vector<std::string> res2 = followsTBox.getFollowsTRightArgLst(2);
			std::vector<std::string> expectedRes1 = { "2", "3" };
			std::vector<std::string> expectedRes2 = { "3" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertFollowsT_getFollowsTRightArgLst_multipleInsertion3)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 4, 5, 7, 8 });
			followsTBox.insertFollowsT(4, { 5, 7, 8 });
			followsTBox.insertFollowsT(5, { 7, 8 });
			followsTBox.insertFollowsT(7, { 8 });

			std::vector<std::string> res1 = followsTBox.getFollowsTRightArgLst(4);
			std::vector<std::string> res2 = followsTBox.getFollowsTRightArgLst(1);
			std::vector<std::string> expectedRes1 = { "5", "7", "8" };
			std::vector<std::string> expectedRes2 = { "4", "5", "7", "8" };

			Assert::IsTrue(expectedRes1 == res1);
			Assert::IsTrue(expectedRes2 == res2);
		}

		TEST_METHOD(insertFollowsT_getFollowsTRightArgLst_nonExistentLeftArg)
		{
			FollowsT followsTBox = FollowsT();
			followsTBox.insertFollowsT(1, { 2, 3 });
			followsTBox.insertFollowsT(2, { 3 });

			std::vector<std::string> res = followsTBox.getFollowsTRightArgLst(3);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
