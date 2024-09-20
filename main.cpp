#include "includes.h"
using namespace std;

const int primes[32] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 13};
const int start_N = 33;
const int end_N = 126;

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
    // Vectors to store values necessary for scrambling text

    int number;
    int scramble_key = 0;                  // Key that will be used to seed the rand() values
    int padding_number = 32 - number_char; // How many extra characters will need to be added
    int input_interval;                    // How many times i will need to add extra characters
    int number_of_inputs;                  // How many characters to add per interval

    cout << padding_number << endl;

    for (int i = 1; i <= padding_number; i++)
    {
        if (padding_number % i == 0)
        {
            divisors.push_back(i);
            cout << i << " ";
        }
    }
    cout << endl;

    int number_of_divisors = divisors.size();

    if (number_of_divisors == 1)
    {
        input_interval = divisors[0];
        number_of_inputs = padding_number;
    }

    if (number_of_divisors == 2)
    {
        input_interval = divisors[0];
        number_of_inputs = divisors[1];
    }

    if (number_of_divisors == 3)
    {
        input_interval = divisors[1];
        number_of_inputs = divisors[1];
    }

    if (number_of_divisors >= 4)
    {
        divisors.erase(divisors.begin());
        divisors.pop_back();
        input_interval = divisors[0];
        int placeholder = divisors.size();
        number_of_inputs = divisors[placeholder - 1];
    }

    cout << input_interval << ", " << number_of_inputs << endl;

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

    for (int i : values)
    {
        scramble_key += i;
    }

    cout << scramble_key << endl;

    int tracker = 0;
    int track = 0;

    stringstream result;
    for (size_t i = 0; i < values.size(); i++)
    {

        int_placeholder = values[i] + 2;

        if (int_placeholder + 2 > 126)
        {
            int_placeholder += 2 - 126 + 32;
        }

        srand(scramble_key + track); // decimal value sum + other value
        result << (rand() % (end_N - start_N + 1)) + end_N;

        // result << values[i] + 2;

        if (i != values.size() - 1)
        {
            result << " ";
        }

        tracker++;
        track++;

        if (tracker == input_interval)
        {
            for (size_t y = 0; y < number_of_inputs; y++)
            {
                srand(scramble_key + primes[track + y]);
                result << (rand() % (end_N - start_N + 1)) << " ";
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
    string myString = "Hee";

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