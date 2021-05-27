#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

/*! Нахождение переменной в коде программы
   \param[in] Text - Текст на языке С
   \param[in] Name_variable - Имя искомой переменной
   \param[out] String_with_variable - Строка с искомой переменной, если она нашлась
*/
string Find_variable(vector<string> Text, string Name_variable);


/*! Проверка объявления
   \param[in] Name_variable - Имя искомой переменной
   \param[in] String_with_variable - Выходная строка содержащая строку с искомой переменной
   \param[out] Name_checked_variable  - Имя искомой переменной, если она объявлена
*/
string Check_declaration(string String_with_variable, string Name_variable);


/*! Нахождение и проверка объявления переменной в коде программы
   \param[in] Text - Текст на языке С
   \param[in] Name_variable - Имя искомой переменной
   \param[out] Strings_with_variable - Массив строк содержащий строки с искомой переменной, если они объявлены
*/
vector<string> Find_and_check_variable_declaration(vector<string> Text, vector<string> Names_variable);


/*! Проверка наличия и корректности текста на языке С и имен переменных
    \param[in] Text[2][MAX_NUMBER_LINES][MAX_LENGTH_LINE] - Текст на языке С и имен переменных
    \param[out] Text[2][MAX_NUMBER_LINES][MAX_LENGTЫH_LINE] - Если содержимое прошло проверку или Error если содержимое не соответсвует заданному формату
*/
vector<string> Spell_check(vector<string> Text);

/*! Считывание входных данных с C и txt файла по заданному пользователем пути
    \param[in] Path_C - Путь расположения c файла
    \param[in] Path_txt - Путь расположения txt файла
    \param[out] Text[2][MAX_NUMBER_LINES][MAX_LENGTH_LINE] - Текст на языке С и названия переменных
*/
string Read_file(char* Path_C, char* Path_txt);

/*! Запись результата выполнения программы в txt файл
    \param[in] Strings_with_variable[MAX_NUMBER_LINES][MAX_LENGTH_LINE] - Массив строк содержащий строки с искомой переменной, если они объявлены
*/
void Write_to_file(vector<string> Strings_with_variable);
