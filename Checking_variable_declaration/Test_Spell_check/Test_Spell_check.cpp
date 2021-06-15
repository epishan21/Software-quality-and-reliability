#include "pch.h"
#include "CppUnitTest.h"
#include "../Checking_variable_declaration/Prototypes_of_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSpellcheck
{
	TEST_CLASS(TestSpellcheck)
	{
	public:
		TEST_METHOD(invalid_characters_in_text)
		{
			vector<string> text =
			{
				"инт фанк()",
				"{",
				"	инт тмп;",
				"	ретурн 0;",
				"}"
			};
			string exp_result = { "9" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(invalid_characters_in_varaible)
		{
			vector<string> text = {	"Тмп" };
			string exp_result = { "10" };
			string real_result = Get_string_from_func(text, 1);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(correct_characters_in_text)
		{
			vector<string> text =
			{
				"int main()",
				"{",
				"	int tmp = 0;",
				"	return 0;",
				"}"												
			};
			string exp_result = { "" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(elementary_instructions_on_one_line)
		{
			vector<string> text =
			{			
				"int func(int abc)",
				"{",
				"	int m; int n;",
				"	return 0;",
				"}"				
			};
			string exp_result = { "11" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(global_variables_in_text)
		{
			vector<string> text =
			{			
				"int Global;",
				"int main()",
				"{",
				"	int n;",
				"	return 0;",
				"}"				
			};
			string exp_result = { "12" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(incorrect_declarer_in_text)
		{
			vector<string> text =
			{			
				"int main()",
				"{",
				"	chor tmp = 0;",
				"	return 0;",
				"}"
			};
			string exp_result = { "" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_declarer_in_text)
		{
			vector<string> text =
			{	
				"int main()",
				"{",
				"	tmp = 0;",
				"	return 0;",
				"}"
			};
			string exp_result = { "" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(macros_in_text)
		{
			vector<string> text =
			{
				"#define bar() int var = 10;",
				"void func()",
				"{",
				"	int tmp = 5;",
				"	bar();",
				"}",
				"int main()",
				"{",
				"	func()",
				"	return 0;",
				"}"
			};
			string exp_result = { "13" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(multiline_comment_in_line)
		{
			vector<string> text =
			{
				"void func()",
				"{",
				"	int tmp = 5;",
				"   /* Комментарий */"
				"	bar();",
				"}",
				"int main()",
				"{",
				"	func()",
				"	return 0;",
				"}"
			};
			string exp_result = { "15" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_text)
		{
			vector<string> text =
			{				
				""				
			};
			string exp_result = { "14" };
			string real_result = Get_string_from_func(text, 0);

			Assert::IsTrue(exp_result == real_result);
		}

		string Get_string_from_func(vector<string> text, bool type)
		{
			vector<string> function;
			string string = { "" };
			try
			{
				Spell_check(text, type);
			}
			catch (Exception& exception)
			{
				string = exception.getErrorCode();
			}

			return string;
		}
	};

}
