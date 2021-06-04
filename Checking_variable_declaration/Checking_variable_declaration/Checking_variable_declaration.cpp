#include "Prototypes_of_functions.h"

int main()
{
    return 0;
}

// Проверить наличие и корректность текста на языке С и имен переменных
vector<string> Spell_check(vector<string> text)
{
    return { "" };
}

// Найти и проверить объявление переменной в тексте
vector<string> Find_and_check_variable_declaration(vector<string> text, vector<string> names_variable)
{
    return { "" };
}

// Найти переменнкю в тексте
string Find_variable(vector<string> text, string name_variable)
{
    return { "" };
}

// Проверить объявление найденной переменной
string Check_declaration(string string_with_variable, string name_variable)
{
    // Создать массив слов объявлений(int, char, double, float, string, bool, struct, union, enum)
    vector<string> data_type = { "int", "char", "double", "float", "string", "bool", "struct", "union", "enum" };

    string name_checked_variable = ""; // Имя проверенной переменной

    char separate[3] = { " *" }; // Разделители

    bool extraneous_sym = false; // Посторонние символы между объявителем и переменной

    bool declarerand_incorrect = false; // Объявитель некорректен 

    //Проверить есть ли любое из слов объявлений перед найденной переменной
    for (int i = 0; i < 9; i++)
    {
        // Проверить корректность слова объявления, если нашлось совпадение         
        if (string_with_variable.find(data_type[i]) != -1)
        {
            // Найти первое вхождение объявителя
            int position = string_with_variable.find(data_type[i]);

            declarerand_incorrect = false;
            // Если объявитель начинается сначала строки или перед ним стоит пробел или открывающаяся скобка
            if ((position == 0) || (string_with_variable[position - 1] == ' ') || (string_with_variable[position - 1] == '('))
            {
                // Строка начинается с объявителя
                string_with_variable = string_with_variable.substr(position);
            }
            else
            {
                // Объявитель некорректен
                declarerand_incorrect = true;
            }

            // Если объявитель корректен
            if (declarerand_incorrect == false)
            {
                // Узнать индекс последнего символа объявителя
                int position_of_declaration = data_type[i].size();

                // Узнать индекс первого символа переменной
                int position_of_var = string_with_variable.find(name_variable);

                // Посчитать количество символов между объявителем и переменной
                int count = position_of_var - position_of_declaration;

                // Скопировать участок между объявителем и переменной
                string section_between_declarerand_and_variable = string_with_variable.substr(position_of_declaration, count);

                extraneous_sym = false;
                // Проверить участок на наличие посторонних символов кроме "*" и " "
                for (int j = 0; j < section_between_declarerand_and_variable.size(); j++)
                {
                    // если есть посторонние символы то переменная не объявлена
                    if ((section_between_declarerand_and_variable[j] != '*') && (section_between_declarerand_and_variable[j] != ' '))
                    {
                        // Перейти на следующее слово
                        extraneous_sym = true;
                        break;
                    }
                }

                // Если посторонние символы не обнаружены
                if (extraneous_sym == false)
                {
                    // Скопировать объявитель    
                    char* chrstr = new char[string_with_variable.length() + 1];
                    strcpy(chrstr, string_with_variable.c_str());

                    strtok(chrstr, separate);

                    string_with_variable = string(chrstr);

                    // Если объявитель корректен
                    if (string_with_variable == data_type[i])
                    {
                        // Записать имя объявленной переменной
                        name_checked_variable = name_variable;
                    }
                }
            }
        }
    }
    return name_checked_variable;
}

