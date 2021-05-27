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
			vector<string> Text =
			{
				{
					"инт фанк()"
					"{"
					"	инт тмп;"
					"	ретурн 0;"
					"}"
				},
				{
					"Tmp"
				}
			};
			vector<string> exp_result = { "Введены недопустимые символы в тексте программы. Используйте латинский алфавит для записи. Код Ошибки: 1" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(invalid_characters_in_varaible)
		{
			vector<string> Text =
			{
				{
					"int main()"
					"{"
					"	int tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"Тмп"
				}
			};
			vector<string> exp_result = { "Введены недопустимые символы в названиях переменных. Используйте латинский алфавит для записи. Код Ошибки: 2" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(invalid_characters_in_text_and_varaible)
		{
			vector<string> Text =
			{
				{
					"инт фанк()"
					"{"
					"	инт тмп;"
					"	ретурн 0;"
					"}"
				},
				{
					"Тмп"
				}
			};
			vector<string> exp_result = { "Введены недопустимые символы в тексте и названиях переменных. Используйте латинский алфавит для записи. Код Ошибки: 3" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(correct_characters_in_text_and_varaible)
		{
			vector<string> Text =
			{
				{
					"int main()"
					"{"
					"	int tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"Tmp"
				}
			};
			vector<string> exp_result =
			{
				{
					"int main()"
					"{"
					"	int tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"Tmp"
				}
			};
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(elementary_instructions_on_one_line)
		{
			vector<string> Text =
			{
				{
					"int func(int abc)"
					"{"
					"	int m; int n;"
					"	return 0;"
					"}"
				},
				{
					"n m"
				}
			};
			vector<string> exp_result = { "Некоторые элементарные инструкции записаны на одной строке. Вводите элементарные инструкции на разных строках. Код Ошибки: 4" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(global_variables_in_text)
		{
			vector<string> Text =
			{
				{
					"int Global;"
					"int main()"
					"{"
					"	int n;"
					"	return 0;"
					"}"
				},
				{
					"n"
				}
			};
			vector<string> exp_result = { "В тексте программы присутствуют глобальные переменные. Не вводите глобальные переменные. Код Ошибки: 5" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(incorrect_declarer_in_text)
		{
			vector<string> Text =
			{
				{
					"int main()"
					"{"
					"	chor tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"tmp"
				}
			};
			vector<string> exp_result =
			{
				{
					"int main()"
					"{"
					"	chor tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"tmp"
				}
			};
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_declarer_in_text)
		{
			vector<string> Text =
			{
				{
					"int main()"
					"{"
					"	tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"tmp"
				}
			};
			vector<string> exp_result =
			{
				{
					"int main()"
					"{"
					"	tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					"tmp"
				}
			};
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(macros_in_text)
		{
			vector<string> Text =
			{
				{
					"#define bar() int var = 10;"
					"void func()"
					"{"
					"	int tmp = 5;"
					"	bar();"
					"}"
					"int main()"
					"{"
					"	func()"
					"	return 0;"
					"}"
				},
				{
					"tmp"
				}
			};
			vector<string> exp_result = { "В тексте программы присутствуют макросы. Не вводите макросы. Код Ошибки: 6" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_text)
		{
			vector<string> Text =
			{
				{
					""
				},
				{
					"Tmp"
				}
			};
			vector<string> exp_result = { "Отсутсвует текст программы. Код Ошибки: 7" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_varaible)
		{
			vector<string> Text =
			{
				{
					"int main()"
					"{"
					"	int tmp = 0;"
					"	return 0;"
					"}"
				},
				{
					""
				}
			};
			vector<string> exp_result = { "Отсутствуют переменные. Код Ошибки: 8" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}

		TEST_METHOD(no_text_and_varaible)
		{
			vector<string> Text =
			{
				{
					""
				},
				{
					""
				}
			};
			vector<string> exp_result = { "Отсутствуют переменные и текст программы. Код Ошибки: 9" };
			vector<string> real_result = getStringFromFunc(Text);

			Assert::IsTrue(exp_result == real_result);
		}


		vector<string> getStringFromFunc(vector<string> Text)
		{
			vector<string> function;
			string string;
			try
			{
				Spell_check(Text);
			}
			catch (Exception& exception)
			{
				string = string + exception.what() + ". " + "Код ошибки: " + exception.getErrorCode();

			}
			function = Spell_check(Text);

			return function;
		}
	};

}
