#include "Prototypes_of_functions.h"

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);       // Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // Установка кодовой страницы win-cp 1251 в поток вывода

    string file_extension_c;    // Расширение файла с текстом программы
    const string exp_file_extension_c = ".c";     // Ожидаемое расширение файла с текстом программы

    string file_extension_txt;  // Расширение файла с именами переменных
    const string exp_file_extension_txt = ".txt"; // Ожидаемое расширение файла с именами переменных

    vector<string> text; // Текст программы
    vector<string> names_variables; // Имена переменных

    vector<string> error_message = { "" }; // Ошибка, которая запишется в файл

    bool type = 0; // Проверить текст программы на исключения 

    try
    {
        // Если введено правильное количество путей
        if (argc == 4)
        {
            text = Read_file(text, argv[1], exp_file_extension_c);
            names_variables = Read_file(names_variables, argv[2], exp_file_extension_txt);
            Spell_check(text, type);
            type = 1; // Проверить имена переменных на исключения
            Spell_check(names_variables, type);
            vector<string> found_declared_variables = Find_and_check_variable_declaration(text, names_variables);
            Write_to_file(found_declared_variables, argv[3]); // Запись в файл
        }
        else
        {
            throw Exception("Отсутствует нужное количество аргументов командной строки. Нужное количество путей равно 4. Код Ошибки: ", "0");
        }
    }
    catch (Exception& exception)
    {
        if (exception.getErrorCode() == "0" || exception.getErrorCode() == "1" || exception.getErrorCode() == "2" || exception.getErrorCode() == "3" || exception.getErrorCode() == "4" || exception.getErrorCode() == "5" || exception.getErrorCode() == "6" || exception.getErrorCode() == "7" || exception.getErrorCode() == "8")
        {
            cout << exception.what() << exception.getErrorCode();
            return 0;
        }
        else
        {
            error_message[0] = error_message[0] + exception.what() + exception.getErrorCode();
            Write_to_file(error_message, argv[3]);
        }
    }
    return 0;
}

// Считывание входных данных с C и txt файла по заданному пользователем пути
vector<string> Read_file(vector<string> text, string path, string exp_file_extension)
{

    string text_in;          // Текст получаемый из файла
    vector<string> text_out; // Полученное содержимое файла 

    string file_extension;   // Расширение файла

    if (exp_file_extension == ".c")
    {
        // У файла с текстом программы отсутствует расширение
        if (path.find(".c") == string::npos)
        {
            throw Exception("Отсутствует правильное расширение у файла с текстом программы. Файл должен иметь расширение .c. Код Ошибки: ", "1");
        }
        // Получение расширения файла
        else
        {
            file_extension = path.substr(path.find_last_of('.'));
        }

        // Было неверно указано расширение файла с текстом программы
        if (exp_file_extension != file_extension)
        {
            throw Exception("Неверно указано расширение файла с текстом программы. Файл должен иметь расширение .c. Код Ошибки: ", "3");
        }
    }
    else if (file_extension == ".txt")
    {
        // У файла с именами переменных отсутствует расширение
        if (path.find(".txt") == string::npos)
        {
            throw Exception("Отсутствует расширение у файла с именами переменных. Файл должен иметь расширение .txt. Код Ошибки: ", "2");
        }
        // Получение расширения файла
        else
        {
            file_extension = path.substr(path.find_last_of('.'));
        }

        // Было неверно указано расширение файла с именами переменных
        if (exp_file_extension != file_extension)
        {
            throw Exception("Неверно указано расширение файла с именами переменных. Файл должен иметь расширение .txt. Код Ошибки: ", "4");
        }
    }

    // Считывание содержимого из файла
    ifstream readFile(path);  // Открыть файл для чтения
    if (!readFile.is_open())
    {
        throw Exception("Неверно указан файл с входными данными. Возможно файл не существует. Код Ошибки: ", "5");
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
    string string_without_comment;
    int size = text.size();
    if (size == 0)
    {
        throw Exception("Отсутсвуют данные в файле с текстом программы. Код Ошибки: ", "14");
    }
    int k = 0;
    // Удалить все функции  
    string rus_letters = { "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" };

    if (type == 0)
    {
        for (int i = 0; i < size; i++)
        {
            int length = text[i].length();

            if (text[i].find("/*") != -1) // Проверить либо только на русские символы либо на все кроме английских и чисел и посторонних символов
            {
                throw Exception("В тексте программы присутствуют многострочные комментарии. Не вводите многострочные комментарии. Код Ошибки: ", "15");
            }

            // Убрать комментарий из строки               
            int position_slash = text[i].find_first_of("/");
            if (position_slash != -1)
            {
                string_without_comment = text[i].append(text[i], 0, position_slash);
            }
            else
            {
                string_without_comment = text[i];
            }

            if (length == 0)
            {
                k++;
                if (k == size)
                {
                    throw Exception("Отсутсвуют данные в файле с текстом программы. Код Ошибки: ", "14");
                }
            }
            else
            {

                if ((string_without_comment.find("#define") != -1) && ((string_without_comment.find(60) == -1) && (string_without_comment.find(34) == -1)))
                {
                    throw Exception("В тексте программы присутствуют макросы. Не вводите макросы. Код Ошибки: ", "13");
                }

                if (string_without_comment.find_first_of(rus_letters) != -1) // Проверить либо только на русские символы либо на все кроме английских и чисел и посторонних символов
                {
                    throw Exception("Введены недопустимые символы в тексте программы. Используйте латинский алфавит для записи. Код Ошибки: ", "9");
                }       
                              
                if (string_without_comment.find(59) != -1) // Если в строке обнаржуенно две ";" 
                {
                    string_without_comment = string_without_comment.substr(string_without_comment.find(59) + 1); // Строка начинается с символа после первой ";"

                    if (string_without_comment.find(59) != -1)
                    {
                        throw Exception("Некоторые элементарные инструкции записаны на одной строке. Вводите элементарные инструкции на разных строках. Код Ошибки: ", "11");
                    }
                }

            }
        }
        
        int size = text.size(); // Количество строк в тексте
        int index_close_bracket = 0; // Индекс закрывающейся скобки 
        int index_open_bracket = 0; // Индекс открывающейся скобки 

        // Проверить наличие закрывающейся скобки в каждой строке
        for (int i = size - 1; i > 0; i--)
        {
            // Начать поиск закрывающейся скобки с конца
            if (text[i].find('}') != -1)
            {
                // Если скобка закрывающаяся то найти парную ей открывающуюся
                index_close_bracket = i;
                index_open_bracket = i;

                // Задать количество закрывающихся скобок без пары равным 1
                int num_close_bracket_without_pair = 1;

                // Пока не найдена парная открывающаяся скобка(количество закрывающихся скобок = 0)
                while (num_close_bracket_without_pair != 0)
                {
                    // Перейти на строчку выше
                    index_open_bracket--;
                    {
                        // Если текущая строка содержит открывающуюся скобку
                        if (text[index_open_bracket].find('{') != -1)
                        {
                            // Уменьшить количество закрывающихся скобок без пары на 1
                            num_close_bracket_without_pair--;
                        }
                        else if (text[index_open_bracket].find('}') != -1)  // Иначе если текущяя строка содержит закрывающуюся скобку
                        {
                            // Увеличить  количество закрывающихся скобок без пары на 1
                            num_close_bracket_without_pair++;
                        }
                    }
                }
            }
            else
            {
                continue;
            }

            index_open_bracket--; // Перейти на строку выше

            // Проверить строки над открывающейся скобкой на наличие текста
            int num_white_spaces_in_line = 0; // Количество пустых пробелов в строке

            // Пока строка - пустая(т.е. \0 или с белыми пробелами)
            for (int i = index_open_bracket; i > 0; i--)
            {
                int num_characters_in_line = text[i].length(); // Количество всех символов в строке
                if (num_characters_in_line == 0)  // То есть строка пуста
                {
                    // Перейти на строчку выше
                    index_open_bracket--;
                }
                else
                {   // Посчитать пробелы
                    for (int i = 0; i < num_characters_in_line; i++)
                    {
                        if ((text[index_open_bracket][i] == ' '))
                            num_white_spaces_in_line++;
                    }
                    // Если строка состоит из белых пробелов
                    if (num_white_spaces_in_line == num_characters_in_line)
                    {
                        // Перейти на строчку выше
                        index_open_bracket--;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            // Удалить строки начиная с функции, заканчивая "}"
            for (int i = index_open_bracket; i <= index_close_bracket; i++)
            {
                text[i].clear();
            }
        }

        // Создать массив слов объявлений(int, char, double, float, string, bool)
        vector<string> data_type = { "int", "char", "double", "float", "string", "bool" };

        bool declarerand_incorrect = false; // Объявитель некорректен 

        //Проверить есть ли любое из слов объявлений в строке
        for (int j = 0; j < text.size(); j++)
        {
            for (int i = 0; i < data_type.size(); i++)
            {
                // Проверить корректность слова объявления, если нашлось совпадение         
                if (text[j].find(data_type[i]) != -1)
                {
                    // Найти первое вхождение объявителя
                    int position = text[j].find(data_type[i]);

                    declarerand_incorrect = false;
                    // Если объявитель начинается сначала строки или перед ним стоит пробел 
                    if (!((position == 0) || (text[j][position - 1] == ' ') || (text[j][position - 1] == '\t')))
                    {
                        // Объявитель некорректен
                        declarerand_incorrect = true;
                    }

                    // Если объявитель корректен
                    if (declarerand_incorrect == false)
                    {
                        throw Exception("В тексте программы присутствуют глобальные переменные. Не вводите глобальные переменные. Код Ошибки: ", "12");
                    }
                }
            }
        }
    }
    else if (type == 1)
    {
        for (int i = 0; i < size; i++)
        {
            if (size == 0)
            {
                throw Exception("Отсутсвуют данные в файле с именами переменных. Код Ошибки: ", "15");
            }
            if (text[i].find_first_of(rus_letters) != -1)
            {
                throw Exception("Введены недопустимые символы в названиях переменных. Используйте латинский алфавит для записи. Код Ошибки: ", "10");
            }
        }
    }

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
            if ((position == 0) || (string_with_variable[position - 1] == ' ') || (string_with_variable[position - 1] == '(') || (string_with_variable[position - 1] == '\t'))
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
        throw Exception("Отсутствует нужное расширение у выходного файла. Код ошибки: ", "6");
    }
    // Получение расширения файла
    else
    {
        file_extension = path_out.substr(path_out.find_last_of('.'));
    }

    // Было неверно указано расширение файла
    if (exp_file_extension != file_extension)
    {
        throw Exception("Неверно указано расширение у выходного файла. Выходной файл должен иметь расширение .txt. Код ошибки: ", "7");
    }

    // Запись результата работы программы в файл
    ofstream write_to_file;
    write_to_file.open(path_out);
    if (!write_to_file.is_open()) // Неверный путь к файлу
    {
        throw Exception("Неверно указан файл с выходными данными. Возможно файл не существует. Код ошибки: ", "8");
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
