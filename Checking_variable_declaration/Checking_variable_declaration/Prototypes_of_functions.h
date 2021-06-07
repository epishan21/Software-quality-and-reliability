#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

/*! Нахождение переменной в коде программы
   \param[in] text - Текст на языке С
   \param[in] name_variable - Имя искомой переменной
   \param[out] atring_with_variable - Строка с искомой переменной, если она нашлась
*/
string Find_variable(vector<string> text, string name_variable);


/*! Проверка объявления
   \param[in] name_variable - Имя искомой переменной
   \param[in] atring_with_variable - Выходная строка содержащая строку с искомой переменной
   \param[out] name_checked_variable  - Имя искомой переменной, если она объявлена
*/
string Check_declaration(string string_with_variable, string name_variable);


/*! Нахождение и проверка объявления переменной в коде программы
   \param[in] text - Текст на языке С
   \param[in] name_variable - Имя искомой переменной
   \param[out] strings_with_variable - Массив строк содержащий строки с искомой переменной, если они объявлены
*/
vector<string> Find_and_check_variable_declaration(vector<string> text, vector<string> names_variable);


/*! Проверка наличия и корректности текста на языке С и имен переменных
    \param[in] text - Текст на языке С и имен переменных
    \param[in] type - Текст или имена переменных
*/
vector<string> Spell_check(vector<string> text, bool type);

/*! Считывание входных данных с C и txt файла по заданному пользователем пути
	\param[in] path - Путь расположения c файла
	\param[in] file_extension - Расширение файла
	\param[out] Text - Текст на языке С и названия переменных
*/
vector<string> Read_file(vector<string> text, string path, string file_extension);

/*! Запись результата выполнения программы в txt файл
	\param[in] Strings_with_variable - Массив строк содержащий строки с искомой переменной, если они объявлены
	\param[in] path - Путь для записи
*/
void Write_to_file(vector<string> strings_with_variable, string path);

class Exception :public exception
{
public:
	Exception(const char* msg, string errorCode) :exception(msg)
	{
		this->errorCode = errorCode;
	}
	string getErrorCode()
	{
		return errorCode;
	}

private:
	string errorCode;
};