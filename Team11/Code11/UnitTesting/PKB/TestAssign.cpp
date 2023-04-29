#include "stdafx.h"
#include "CppUnitTest.h"

#include "../source/PKB/Entity/Assign.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAssign)
	{
	public:
		TEST_METHOD(insertAssign_getAllAssignments_singleAssignment)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");

			std::vector<std::string> res = assignBox.getAllAssignments();
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAllAssignments_multipleAssignmentsWithDiffVars)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");

			std::vector<std::string> res = assignBox.getAllAssignments();
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAllAssignments_multipleAssignmentsWithSameVars)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "x");

			std::vector<std::string> res = assignBox.getAllAssignments();
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAllAssignments_multipleAssignments)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");
			assignBox.insertAssign(3, "z");
			assignBox.insertAssign(4, "x");

			std::vector<std::string> res = assignBox.getAllAssignments();
			std::vector<std::string> expectedRes = { "1", "2", "3", "4"};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAllAssignments_noAssignments)
		{
			Assign assignBox = Assign();

			std::vector<std::string> res = assignBox.getAllAssignments();
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getStmtLstByVarAssignment_singleAssignment)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");

			std::vector<std::string> res = assignBox.getStmtLstByVarAssignment("x");
			std::vector<std::string> expectedRes = { "1" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getStmtLstByVarAssignment_multipleAssignments)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");

			std::vector<std::string> res = assignBox.getStmtLstByVarAssignment("y");
			std::vector<std::string> expectedRes = { "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getStmtLstByVarAssignment_multipleAssignmentsWithSameVars)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "x");

			std::vector<std::string> res = assignBox.getStmtLstByVarAssignment("x");
			std::vector<std::string> expectedRes = { "1", "2" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getStmtLstByVarAssignment_noAssignment)
		{
			Assign assignBox = Assign();

			std::vector<std::string> res = assignBox.getStmtLstByVarAssignment("x");
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAssignmentFromStmtIdx_singleAssignment)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");

			std::vector<std::string> res = assignBox.getAssignmentFromStmtIdx(1);
			std::vector<std::string> expectedRes = { "x" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAssignmentFromStmtIdx_multipleAssignments1)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");

			std::vector<std::string> res = assignBox.getAssignmentFromStmtIdx(2);
			std::vector<std::string> expectedRes = { "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAssignmentFromStmtIdx_multipleAssignments2)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");
			assignBox.insertAssign(3, "y");

			std::vector<std::string> res = assignBox.getAssignmentFromStmtIdx(2);
			std::vector<std::string> expectedRes = { "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAssignmentFromStmtIdx_reinsertion)
		{
			Assign assignBox = Assign();
			assignBox.insertAssign(1, "x");
			assignBox.insertAssign(2, "y");
			assignBox.insertAssign(2, "z");

			std::vector<std::string> res = assignBox.getAssignmentFromStmtIdx(2);
			std::vector<std::string> expectedRes = { "y" };

			Assert::IsTrue(expectedRes == res);
		}

		TEST_METHOD(insertAssign_getAssignmentFromStmtIdx_noAssignment)
		{
			Assign assignBox = Assign();

			std::vector<std::string> res = assignBox.getAssignmentFromStmtIdx(1);
			std::vector<std::string> expectedRes = {};

			Assert::IsTrue(expectedRes == res);
		}
	};
}  // namespace UnitTesting
