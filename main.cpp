#include "includes.h"
using namespace std;

const int primes[15] = {5, 7, 11, 13, 61, 41, 53, 89, 97, 29, 23, 19, 59, 71, 43};

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

string Scrambler(const string &input, int number_char)
{
    stringstream ss(input);
    int int_placeholder = 0;

    vector<int> values;
    vector<int> divisors;
    int number;
    int padding_number = 32 - number_char;
    cout << padding_number << endl;

    for (int i = 1; i <= padding_number; i++)
    {
        if (padding_number % i == 0)
        {
            divisors.push_back(i);
            cout << i << " ";
        }

        if (i == 1)
        {
            divisors.pop_back();
        }

        if (i == padding_number)
        {
            divisors.pop_back();
        }
    }
    cout << endl;

    for (int i : divisors)
    {
        cout << i << " ";
    }

    cout << endl;

    // Finish only works with 21!!!!!!!!!

    while (ss >> number)
    {
        values.push_back(number);
    }

    int tracker = 0;

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

        tracker++;

        if (tracker == divisors[0])
        {
            for (size_t y = 0; y < divisors[1]; y++)
            {
                result << 80 << " ";
            }

            tracker = 0;
        } // Update
    }

    values.clear();
    divisors.clear();
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
    string myString = "Hello World";

    string decimalString = convert_to_decimal(myString);
    cout << "Decimal: " << decimalString << endl;

    string stringDEC = convert_to_string(decimalString);
    cout << "String: " << stringDEC << endl;

    string scb_dec = Scrambler(decimalString, stringDEC.size());
    cout << "Srambled decimal: " << scb_dec << endl;

    string scb_string = convert_to_string(scb_dec);
    cout << "Srambled string: " << scb_string << endl;

    string hash = string_to_hex(scb_string);
    cout << "Hash: " << hash << endl;

    return 0;
}