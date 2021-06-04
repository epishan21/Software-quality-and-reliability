#include "pch.h"
#include "CppUnitTest.h"
#include "../Checking_variable_declaration/Prototypes_of_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFindvariable
{
	TEST_CLASS(TestFindvariable)
	{
	public:
		TEST_METHOD(variable_is_correct)
		{
			string name_variable = "abc";
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int abc = 0;",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "	 int abc = 0;";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(variable_is_not_correct)
		{
			string name_variable = "abc";
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int abcd = 0;",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(name_variable_is_part_of_another_name_variable)
		{
			string name_variable = "bab";
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int alibaba = 0;",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(name_variable_is_name_function)
		{
			string name_variable = "Find_var";
			vector<string> text =
			{
				"int Find_var(char text[5][5])",
				"{",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "int Find_var(char text[5][5])";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(variable_declared_as_argument_to_function_and_also_present_in_function_code)
		{
			string name_variable = "text";
			vector<string> text =
			{
				"int Find_var(char text[5][5])",
				"{",
				"    text[5][5]={“”};",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "int Find_var(char text[5][5])";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(variable_is_not_declared)
		{
			string name_variable = "abc";
			vector<string> text =
			{
				"int main()",
				"{",
				"   abc++;",
				"	return 0;",
				"}"
			};
			string exp_string_with_variable = "   abc++;";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

		TEST_METHOD(variable_and_function_have_same_name)
		{
			string name_variable = "Find_var";
			vector<string> text =
			{
				"int Find_var(char text[5][5])",
				"{",
				"    int Find_var;",
				"	 return 0;",
				"}"
			};
			string exp_string_with_variable = "int Find_var(char text[5][5])";

			string real_string_with_variable = Find_variable(text, name_variable);

			Assert::AreEqual(exp_string_with_variable, real_string_with_variable);
		}

	};
}
