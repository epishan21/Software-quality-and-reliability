#include "Prototypes_of_functions.h"

int main()
{
    return 0;
}

vector<string> Read_file(vector<string> text, string path, string exp_file_extension)
{

    string text_in;          // Текст получаемый из файла
    vector<string> text_out; // Полученное содержимое файла 

    string file_extension;   // Расширение файла

    // Считывание содержимого из файла
    ifstream readFile(path); // Открыть файл для чтения

    if (exp_file_extension == ".c")
    {
        // У файла с текстом программы отсутствует расширение
        if (path.find(".c") == string::npos)
        {
            throw Exception("Отсутствует расширение у файла с текстом программы. Файл должен иметь расширение .c", "1");
        }
        // Получение расширения файла
        else
        {
            file_extension = path.substr(path.find_last_of('.'));
        }

        // Было неверно указано расширение файла с текстом программы
        if (exp_file_extension != file_extension)
        {
            throw Exception("Неверно указано расширение файла с текстом программы. Файл должен иметь расширение .c", "3");
        }
    }
    else if (file_extension == ".txt")
    {
        // У файла с именами переменных отсутствует расширение
        if (path.find(".txt") == string::npos)
        {
            throw Exception("Отсутствует расширение у файла с именами переменных. Файл должен иметь расширение .txt", "2");
        }
        // Получение расширения файла
        else
        {
            file_extension = path.substr(path.find_last_of('.'));
        }

        // Было неверно указано расширение файла с именами переменных
        if (exp_file_extension != file_extension)
        {
            throw Exception("Неверно указано расширение файла с именами переменных. Файл должен иметь расширение .txt", "4");
        }
    }

    if (!readFile.is_open())
    {
        throw Exception("Неверно указан файл с входными данными. Возможно файл не существует", "5");
    }
    // Непосредственно считывание данных из файла
    else
    {
        while (getline(readFile, text_in))
        {
            text_out.push_back(text_in);
        }
    }
    readFile.close(); // Закрытие файла   

    text = text_out;
    return text; // Полученное содержимое файла 
}

// Проверить наличие и корректность текста на языке С и имен переменных
vector<string> Spell_check(vector<string> text, bool type)
{
    return { "" };
}

// Найти и проверить объявление переменной в тексте
vector<string> Find_and_check_variable_declaration(vector<string> text, vector<string> names_variable)
{
    string strings_with_variable;    // Строки с найденной переменной
    string found_declared_variables; // Найденные переменные

    vector<string> result;           // Результат проверки

    // Найти и проверить объявление каждой переменной, если их больше чем одна 
    for (int i = 0; i < names_variable.size(); i++)
    {
        // Найти переменную
        strings_with_variable = Find_variable(text, names_variable[i]);

        // Если переменная нашлась
        if (strings_with_variable != "")
        {
            // Проверить объявление
            found_declared_variables = Check_declaration(strings_with_variable, names_variable[i]);

            // Если переменная объявленна
            if (found_declared_variables != "")
            {
                // Записать имя переменной в результат 
                result.push_back(found_declared_variables);
            }
        }
    }
    return result;
}

// Найти переменнкю в тексте
string Find_variable(vector<string> text, string name_variable)
{
    string string_with_variable;      // Полная строка с найденной переменной

    vector<string> symbols = { " ", "*", ";", "=", "[", "(", "+", "-", "{", "\0" }; // Символы, которые могут стоять после переменной

    int lenth = name_variable.size(); // Длина имени переменной

    string string_starts_variable;    // Строка начинается с переменной

    bool its_function = false;        // Флаг для проверки объявления функции

    string string_without_comment;    // Строка с удаленным комментарием

     // Добавить к переменной пробел спереди
    string variable_with_space = " ";
    variable_with_space = variable_with_space + name_variable;

    // Добавить к переменной указатель спереди
    string variable_with_pointer = "*";
    variable_with_pointer = variable_with_pointer + name_variable;

    lenth++;

    // Проверить в каждой строке наличие данной переменной
    for (int i = 0; i < text.size(); i++)
    {
        // Проверить корректность переменной, если нашлось совпадение
        if ((text[i].find(variable_with_space) != -1) || (text[i].find(variable_with_pointer) != -1))
        {
            // Убрать комментарий из строки               
            int position_slash = text[i].find_first_of("/");
            string_without_comment.append(text[i], 0, position_slash);

            // Повтороить, если имя переменной совпадает с имемени функции, при этом переменная объявленна как аргумент этой же функции
        find_var_again:

            // Найти первое вхождение переменной
            int position = string_without_comment.find(variable_with_space);
            string_starts_variable = string_without_comment.substr(position + 1, lenth); // Строка содержит имя ожидаемой переменной и еще один символ полсе нее

            // Проверить следующий символ после имени переменной
            int next_sym_after_variable = name_variable.size();
            for (int j = 0; j < symbols.size(); j++)
            {
                if (string_starts_variable[next_sym_after_variable] == symbols[j][0])
                {
                    // Проверить корректность написания переменной
                    string_starts_variable = string_starts_variable.substr(0, lenth - 1);

                    // Если переменная корректна
                    if (string_starts_variable == name_variable)
                    {
                        // Проверить не является ли имя переменной - именем функции
                        // Узнать индекс последнего символа переменной
                        int last_position_of_var = string_without_comment.find(name_variable) + string_starts_variable.size();

                        // Узнать позицию открывающейся скобки
                        int position_of_bracket = string_without_comment.find('(', last_position_of_var);

                        // Если после имени переменной есть открывающаяся скобка, то это функция                   
                        if (position_of_bracket == -1)
                        {
                            // Записать строку с переменной
                            string_with_variable = text[i];
                            its_function = false;
                        }
                        else
                        {
                            // Скопировать строку после открывающейся скобки и заново проверить
                            its_function = true;
                            string_without_comment = string_without_comment.substr(position_of_bracket);

                            // Снова проверить уже обрезанный участок
                            goto find_var_again;
                        }
                        break;
                    }
                }
            }
            // Если именем переменной не была функция
            if(its_function == false)
            {
                break;
            }
        }
    }
    return string_with_variable;
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

void Write_to_file(vector<string> result, string path_out)
{
    string file_extension; // Расширение файла
    const string exp_file_extension = ".txt"; // Ожидаемое расширение файла

    // У файла отсутствует расширение
    if (path_out.find(".txt") == string::npos)
    {
        throw Exception("Отсутствует расширение у выходного файла", "6");
    }
    // Получение расширения файла
    else
    {
        file_extension = path_out.substr(path_out.find_last_of('.'));
    }

    // Было неверно указано расширение файла
    if (exp_file_extension != file_extension)
    {
        throw Exception("Неверно указано расширение у выходного файла. Выходной файл должен иметь расширение .txt", "7");
    }

    // Запись результата работы программы в файл
    ofstream write_to_file;
    write_to_file.open(path_out);
    if (!write_to_file.is_open()) // Неверный путь к файлу
    {
        throw Exception("Неверно указан файл с выходными данными. Возможно файл не существует", "8");
    }
    // Непосредственно запись результата работы программы в файл
    else
    {
        for (int j = 0; j < result.size(); j++)
        {
            write_to_file << result[j];
            write_to_file << "\n";
        }
    }
    write_to_file.close(); // Закрытие файла
}
