#include "pch.h"
#include "CppUnitTest.h"
#include "../Checking_variable_declaration/Prototypes_of_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFindandcheckvariabledeclar
{
	TEST_CLASS(TestFindandcheckvariabledeclaration)
	{
	public:
		TEST_METHOD(variable_declared)
		{
			vector<string> names_variable = { "abc" };
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int abc = 0;",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "abc" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(variable_declared_as_function_argument)
		{
			vector<string> names_variable = { "text" };
			vector<string> text =
			{
				"int Find_var(char text[5][5])",
				"{",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "text" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(function_declared)
		{
			vector<string> names_variable = { "Find_var", "abc" };
			vector<string> text =
			{
				"int Find_var(char text[5][5])",
				"{",
				"	 int abc = 0;",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "abc" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(union_enum_structure_declared)
		{
			vector<string> names_variable = { "student", "chill", "poas" };
			vector<string> text =
			{
				"struct student",
				"{",
				"	int n;",
				"	int m;",
				"}",
				"enum chill",
				"{",
				"	 DOG,",
				"	 CAT",
				"}",
				"union poas",
				"{",
				"	  int i;",
				"}"
			};
			vector<string> exp_names_variable = { "student", "chill", "poas" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(variable_name_is_incorrect)
		{
			vector<string> names_variable = { "tmp" };
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int temp = 0;",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(declarer_is_incorrect)
		{
			vector<string> names_variable = { "tmp" };
			vector<string> text =
			{
				"int main()",
				"{",
				"	 tint tmp = 0;",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(variable_and_function_have_same)
		{
			vector<string> names_variable = { "main" };
			vector<string> text =
			{
				"int main()",
				"{",
				"	 int main = 0;",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "main" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(variable_as_argument_of_function_and_function_have_same_name)
		{
			vector<string> names_variable = { "main" };
			vector<string> text =
			{
				"int main(int main)",
				"{",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "main" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}

		TEST_METHOD(variable_as_argument_of_function)
		{
			vector<string> names_variable = { "tmp" };
			vector<string> text =
			{
				"int main(int tmp)",
				"{",
				"	 return 0;",
				"}"
			};
			vector<string> exp_names_variable = { "tmp" };

			vector<string> real_names_variable = Find_and_check_variable_declaration(text, names_variable);

			Assert::IsTrue(exp_names_variable == real_names_variable);
		}
	};
}
