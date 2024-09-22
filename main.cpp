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

int getScrambleKey(vector<int> &values)
{
    int scramble_key;

    for (int i : values)
    {
        scramble_key += i;
    }

    return scramble_key;
}

string Scrambler(const string &input, int number_char)
{
    stringstream ss(input);
    int int_placeholder = 0;

    vector<int> values;
    vector<int> divisors;
    vector<int> extras;
    // Vectors to store values necessary for scrambling text

    int number;
    int scramble_key = 0; // Key that will be used to seed the rand() values
    int extra_scrable = 0;
    int input_interval;   // How many times i will need to add extra characters
    int number_of_inputs; // How many characters to add per interval
    int overflow;

    while (ss >> number)
    {
        values.push_back(number);
    }

    if (number_char > 32)
    {
        overflow = number_char - 32;
        cout << "Number of extra char: " << overflow << endl;

        for (size_t i = 0; i < overflow; i++)
        {
            extras.push_back(values[0]);
            cout << "values swaped: " << values[0] << endl;
            values.erase(values.begin());
        }

        number_char -= overflow;
    }

    int padding_number = 32 - number_char;

    cout << "Padding number: " << padding_number << endl;

    for (int i = 1; i <= padding_number; i++)
    {
        if (padding_number % i == 0)
        {
            divisors.push_back(i);
            cout << i << " ";
        }
    }

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

    if (padding_number == 0)
    {
        input_interval = 0;
        number_of_inputs = 0;
    }

    cout << input_interval << ", " << number_of_inputs << endl;

    for (int i : divisors)
    {
        cout << i << " ";
    }

    cout << endl;

    extra_scrable = getScrambleKey(extras);
    scramble_key = getScrambleKey(values) + extra_scrable;

    cout << scramble_key << endl;

    int tracker = 0;
    int track = 0;
    int element_count = 0;

    stringstream result;

    int input_coordinate = input_interval;
    for (size_t i = 0; i < input_interval; i++)
    {
        for (size_t y = 0; y < number_of_inputs; y++)
        {
            values.insert(values.begin() + input_coordinate, 1);
        }

        input_coordinate += number_of_inputs + input_interval;
    }

    for (size_t i = 0; i < values.size(); i++)
    {

        int_placeholder = values[i] + 2;

        if (int_placeholder + 2 > 126)
        {
            int_placeholder += 2 - 126 + 32;
        }

        srand(scramble_key + primes[i]); // decimal value sum + other value
        result << (rand() % (end_N - start_N + 1)) + end_N << " ";
    }

    cout << "Number of elements in string: " << element_count << endl;

    values.clear();
    divisors.clear();
    extras.clear();
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

void input_by_hand()
{
    string input;
    cout << "Input: ";
    cin >> input;

    string decimalString = convert_to_decimal(input);
    string stringDEC = convert_to_string(decimalString);
    string scb_dec = Scrambler(decimalString, stringDEC.size());
    string scb_string = convert_to_string(scb_dec);
    string hash = string_to_hex(scb_string);

    cout << "Hash: " << hash << endl;
}

int main()
{
    // string myString = "la";

    // string decimalString = convert_to_decimal(myString);
    // cout << "Decimal: " << decimalString << endl;

    // string stringDEC = convert_to_string(decimalString);
    // cout << "String: " << stringDEC << endl;

    // string scb_dec = Scrambler(decimalString, stringDEC.size());
    // cout << "Srambled decimal: " << scb_dec << endl;

    // string scb_string = convert_to_string(scb_dec);
    // cout << "Srambled string: " << scb_string << endl;

    // string hash = string_to_hex(scb_string);
    // cout << "Hash: " << hash << endl;

    int input_type;

    do
    {
        cout << "To input by file enter [1]; To input by hand type [2];" << endl;
        cout << "Input: ";
        cin >> input_type;

    } while (input_type < 1 || input_type > 2);

    if (input_type == 2)
    {
        input_by_hand();
    }
    return 0;
}