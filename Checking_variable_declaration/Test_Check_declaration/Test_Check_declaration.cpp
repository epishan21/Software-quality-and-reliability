#include "pch.h"
#include "CppUnitTest.h"
#include "../Checking_variable_declaration/Prototypes_of_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCheckdeclaration
{
	TEST_CLASS(TestCheckdeclaration)
	{
	public:
		TEST_METHOD(many_spaces_between_declarerand_and_variable)
		{
			string data_type = "int";
			string strings_with_variable = { "int         tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(one_pointer_between_declarerand_and_variable)
		{
			string data_type = "int";
			string strings_with_variable = { "int * tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(many_pointers_between_declarerand_and_variable_with_spaces)
		{
			string data_type = "int";
			string strings_with_variable = { "int *** tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(many_pointers_between_declarerand_and_variable_without_spaces)
		{
			string data_type = "int";
			string strings_with_variable = { "int***tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(many_pointers_near_declarerand_and_variable_with_spaces)
		{
			string data_type = "int";
			string strings_with_variable = { "int* *tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(one_pointer_near_variable_and_between_declarerand)
		{
			string data_type = "int";
			string strings_with_variable = { "int *tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(one_pointer_near_declarerand_and_between_variable)
		{
			string data_type = "int";
			string strings_with_variable = { "int* tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(mane_pointers_alternately_between_declarerand_and_variable)
		{
			string data_type = "int";
			string strings_with_variable = { "int * * * tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_int)
		{
			string data_type = "int";
			string strings_with_variable = { "int tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_char)
		{
			string data_type = "char";
			string strings_with_variable = { "char tmp[1];" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_double)
		{
			string data_type = "double";
			string strings_with_variable = { "double tmp;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_float)
		{
			string data_type = "float";
			string strings_with_variable = { "float tmp;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_string)
		{
			string data_type = "string";
			string strings_with_variable = { "string tmp;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_bool)
		{
			string data_type = "bool";
			string strings_with_variable = { "bool tmp;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_struct)
		{
			string data_type = "struct";
			string strings_with_variable = { "struct tmp" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_union)
		{
			string data_type = "union";
			string strings_with_variable = { "union tmp" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(data_type_enum)
		{
			string data_type = "enum";
			string strings_with_variable = { "enum tmp" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(declarer_has_size_and_pointer)
		{
			string data_type = "int";
			string strings_with_variable = { "unsigned long int * tmp = 0;" };
			string exp_name_variable = "tmp";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(declarer_is_missing)
		{
			string data_type = "int";
			string strings_with_variable = { "tmp = 0;" };
			string exp_name_variable = "";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(extraneous_characters_between_declarerand_and_variable)
		{
			string data_type = "int";
			string strings_with_variable = { "int* 434hkjh* -=14235235 *tmp = 0;" };
			string exp_name_variable = "";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(declarer_is_incorrect)
		{
			string data_type = "int";
			string strings_with_variable = { "imt tmp = 0;" };
			string exp_name_variable = "";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}

		TEST_METHOD(declarer_is_incorrect_at_beginning)
		{
			string data_type = "int";
			string strings_with_variable = { "tint tmp = 0;" };
			string exp_name_variable = "";

			string real_name_variable = Check_declaration(strings_with_variable, exp_name_variable);

			Assert::AreEqual(exp_name_variable, real_name_variable);
		}
	};
}

