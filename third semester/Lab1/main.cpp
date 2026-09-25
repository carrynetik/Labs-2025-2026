#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

bool contains(const wstring& row, wchar_t symbol)
{
    return row.find(symbol) != wstring::npos;
}

wchar_t toLowerRussian(wchar_t symbol)
{
    if (symbol >= L'А' && symbol <= L'Я')
        return symbol + (L'а' - L'А');

    if (symbol == L'Ё')
        return L'ё';

    return symbol;
}

int getGroup(wchar_t symbol)
{
    symbol = toLowerRussian(symbol);

    const wstring vowels = L"аеёиоуыэюя";
    const wstring consonants = L"бвгджзйклмнпрстфхцчшщъь";

    if (contains(vowels, symbol))
        return 0;

    if (contains(consonants, symbol))
        return 1;

    if (symbol >= L'0' && symbol <= L'9')
        return 2;

    if (symbol != L'@')
        return 3;

    return -1;
}

int main()
{
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    string input;

    cout << "Введите строку:\n";
    getline(cin, input);

    wstring text = converter.from_bytes(input);

    if (text.length() > 50)
    {
        cout << "Ошибка: строка должна содержать не более 50 символов.\n";
        return 0;
    }

    vector<wstring> array(4);

    for (wchar_t symbol : text)
    {
        int group = getGroup(symbol);

        if (group == -1)
            continue;

        if (group == 0 || group == 1)
            symbol = toLowerRussian(symbol);

        if (!contains(array[group], symbol))
            array[group] += symbol;
    }

    cout << "Массив:\n";

    for (const wstring& row : array)
    {
        for (wchar_t symbol : row)
            cout << converter.to_bytes(wstring(1, symbol)) << ' ';

        cout << '\n';
    }

    text += L"+123АБВ";

    const char* colors[4] =
    {
        "\033[31m",
        "\033[34m",
        "\033[32m",
        "\033[33m"
    };

    cout << "Результат:\n";

    for (wchar_t symbol : text)
    {
        wchar_t symbolForSearch = toLowerRussian(symbol);
        int group = -1;

        for (int i = 0; i < 4; i++)
        {
            if (contains(array[i], symbolForSearch))
            {
                group = i;
                break;
            }
        }

        string utf8Symbol = converter.to_bytes(wstring(1, symbol));

        if (group != -1)
            cout << colors[group] << utf8Symbol << "\033[0m";
        else
            cout << utf8Symbol;
    }

    cout << '\n';

    return 0;
}