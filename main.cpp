#include "includes.h"
using namespace std;

string convert_to_decimal(const string &input)
{
    stringstream ss;

    for (size_t i = 0; i < input.size(); i++)
    {
        ss << static_cast<int>(input[i]);

        if (i != input.size() - 1)
        {
            ss << " ";
        }
    }

    return ss.str();
}

string convert_to_string(const string &decimalString)
{
    stringstream ss(decimalString);
    string result;
    int decimalValue;

    while (ss >> decimalValue)
    {
        result += static_cast<char>(decimalValue);
    }

    return result;
}

string Scrambler(const string &input)
{
    stringstream ss(input);
    int int_placeholder = 0;

    vector<int> values;
    int number;

    while (ss >> number)
    {
        values.push_back(number);
    }

    stringstream result;
    for (size_t i = 0; i < values.size(); i++)
    {
        int_placeholder = values[i] + 2;

        if (int_placeholder + 2 > 126)
        {
            int_placeholder += 2 - 126 + 32;
        }

        result << int_placeholder;

        // result << values[i] + 2;

        if (i != values.size() - 1)
        {
            result << " ";
        }
    }

    return result.str();
}

string string_to_hex(const string &input)
{
    static const char hex_digits[] = "0123456789abcdef";

    string output;

    output.reserve(input.length() * 2);

    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }

    return output;
}

int main()
{
    string myString = "Password123";

    string decimalString = convert_to_decimal(myString);
    cout << "Decimal: " << decimalString << endl;

    string stringDEC = convert_to_string(decimalString);
    cout << "String: " << stringDEC << endl;

    string val = Scrambler(decimalString);
    cout << "Srambled decimal: " << val << endl;

    string hash = convert_to_string(val);
    cout << "Srambled string: " << hash << endl;

    string hex = string_to_hex(hash);
    cout << "Hex: " << hex << endl;

    return 0;
}