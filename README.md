# Bloku-Grandines

# Pseudo-kodas

```plaintext
START

SET start_N = 33, end_N = 255

FUNCTION convert_to_decimal(input)
    INITIALIZE an empty stringstream
    FOR each character in input
        CONVERT character to its ASCII value
        ADD value to stringstream
        IF not the last character
            ADD space to stringstream
    RETURN stringstream content

FUNCTION convert_to_string(decimalString)
    INITIALIZE stringstream with decimalString
    INITIALIZE empty result string
    WHILE stringstream has values
        CONVERT each decimal value to a character
        ADD character to result
    RETURN result string

FUNCTION getScrambleKey(values)
    INITIALIZE scramble_key = 1, count = 0
    FOR each value in values
        MULTIPLY scramble_key by value
        INCREMENT count
        IF count == 10
            BREAK loop
    RETURN scramble_key

FUNCTION Scrambler(input, number_char)
    PARSE input into list of integers (values)
    CALCULATE padding_number = 32 - number_char
    FIND divisors of padding_number and store in divisors list
    SET input_interval and number_of_inputs based on divisors
    IF padding_number is 0
        SET input_interval = 0, number_of_inputs = 0
    CALCULATE scramble_key using getScrambleKey(values)
    INSERT extra characters into values based on input_interval and number_of_inputs
    SEED random number generator with scramble_key
    FOR each value in values
        REPLACE value with random number between start_N and end_N
    RETURN scrambled decimal string

FUNCTION string_to_hex(input)
    INITIALIZE an empty output string
    FOR each character in input
        CONVERT character to hex and ADD to output string
    RETURN output string

FUNCTION input_by_hand()
    ASK user for input string
    CONVERT input string to decimal string
    SCRAMBLE decimal string
    CONVERT scrambled decimal back to string
    CONVERT scrambled string to hexadecimal
    PRINT hexadecimal hash

FUNCTION input_by_file()
    ASK user for file name
    OPEN file for reading and output file for writing
    WHILE there are lines in the file
        CONVERT line to decimal string
        SCRAMBLE decimal string
        CONVERT scrambled decimal back to string
        CONVERT scrambled string to hexadecimal
        WRITE hexadecimal hash to output file

FUNCTION main()
    ASK user to choose input type (file or hand)
    IF hand
        CALL input_by_hand()
    ELSE
        CALL input_by_file()

END
```

# Eksperimentinis tyrimas ir rezultatų analizė

### 1 ekspirimentas

- "Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio."
1) Test_1char_1.txt
2) Test_1char_2.txt

- "Bent du failai būtų sudaryti iš daug (> 1000) atsitiktinai sugeneruotų simbolių"
1) Test_rnd_1.txt
2) Test_rnd_2.txt

- "Bent du failai būtų sudaryti iš daug (> 1000) simbolių, bet skirtųsi vienas nuo kito tik vienu (pvz. vidurinėje pozicijoje esančiu) simboliu."
1) Test_same_1.txt
2) Test_same_2.txt

- "Tuščio failo"
1) empty.txt

- Patenkina reikalavimus visuose atvejuose hash ilgis yra 64 simboliai.

### 2 eksperimentas

Ištirkite Jūsų sukurtos hash funkcijos efektyvumą, t.y., patikrinkite, kaip Jūsų hash'avimo
funkcija atitinka 4-ą reikalavimą. Tuo tikslu pirmiausiai suhash'uokite vieną eilutę iš failo konstitucija.txt ir išmatuokite kiek laiko visa tai užtruko.
    1) Tuomet pakartokite eksperimentą hash'uojant 2 eilutes, 4 eilutes, 8 eilutes ir t.t. (16, 32, 64, ...). Pažymime, kad reikia matuoti, tik hash'avimo funkcijos veikimo laiką (be
    input'o nuskaitymo/parengimo). Reiktų pateikti suvidurkintą (kartojant tą patį
    eksperimentą pvz. 5 kartus) hash'avimo laiko priklausomybę nuo input dydžio (eilučių skaičiaus). Kitaip sakant, reikia ištirti, kaip hash'avimo laikas didėja, didėjant input dydžiui.
    2) Rezultatą prašytume pavaizduoti grafiškai, parodant kaip laikas priklauso nuo input dydžio.
    3) Galima (bet ne privaloma) ir algoritmų sudėtingumą (tiesinis, kvadratinis, logaritminis, eksponentinis ir pan.) pasitelkti, norint įvertinti šią priklausomybę.

| Test 1 |
| Liniju skaicius | 1 laikas | 2 laikas | 3 laikas |
| :---: | :---: | :---: | :---: |
| 1 | 0.00019 s | 0.0001714 s | 0.0001784 s|
| 2 | 0.0002372 s | 0.0002356 s | 0.0005987 s|
| 4 | 0.0003466 s | 0.0003191 s| 0.0003229 s|
| 8 | 0.0006737 s| 0.0006553 s| 0.000623 s|
| 16 | 0.0013954 s| 0.0010928 s| 0.0010868 s|
| 64 | 0.00422 s| 0.0036397 s| 0.0042821 s|
| 128 | 0.0103805 s| 0.0087922 s| 0.0094359 s|
| 256 | 0.0205727 s| 0.0201353 s| 0.0200644 s|
| 512 | 0.0451074 s| 0.0457614 s| 0.0496028 s|

### 3 eksperimentas

1) 25000 po 10 simbolių (random_string_pairs_10.txt)
    - Kolizijos: 0;
2) 25000 po 100 simbolių (random_string_pairs_100.txt)
    - Kolizijos: 0;
3) 25000 po 500 simbolių (random_string_pairs_500.txt)
    - Kolizijos: 0;
4) 25000 po 1000 simbolių (random_string_pairs_1000.txt)
    - Kolizijos: 0;

### 3 testo funkcija

```cpp
void test_file() {
    string input = "random_string_pairs_1000.txt";
    ifstream inputFile(input);
    ofstream file1("output_file1.txt");
    ofstream file2("output_file2.txt");

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string str1, str2;

        // Split the line by the comma to get the two strings
        if (std::getline(ss, str1, ',') && std::getline(ss, str2)) {
            file1 << str1 << "\n";  // Write the first string to the first file
            file2 << str2 << "\n";  // Write the second string to the second file
        }
    }

    inputFile.close();
    file1.close();
    file2.close();

    inputFile.open("output_file1.txt");
    ofstream write(input + "_output1.txt");
    string str_placeholder;

    while (getline(inputFile, str_placeholder)) {
        string decimalString = convert_to_decimal(str_placeholder);
        string stringDEC = convert_to_string(decimalString);
        string scb_dec = Scrambler(decimalString, stringDEC.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        write << hash << endl;
    }

    write.close();
    inputFile.close();

    inputFile.open("output_file2.txt");
    ofstream Write(input + "_output2.txt");

    while (getline(inputFile, str_placeholder)) {
        string decimalString = convert_to_decimal(str_placeholder);
        string stringDEC = convert_to_string(decimalString);
        string scb_dec = Scrambler(decimalString, stringDEC.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        Write << hash << endl;
    }

    inputFile.close();
    Write.close();

    inputFile.open(input + "_output1.txt");
    ifstream inputFile2(input + "_output2.txt");

    string a, b;
    int match = 0;

    for (int i = 0; i < 25000; i++) {
        inputFile >> a;
        inputFile2 >> b;

        if (a == b) {
            match++;
        }
    }

    cout << "Collisions: " << match << endl;

}
```

### 4 eksperimentas

1) 100,000 simbolių poros nuo 1 iki 100 simboliu (random_string_pairs_max100.txt)

    - Bit-level differences:
    - Minimum: 0
    - Maximum: 220
    - Average: 75.3068

    - Hex-level differences:
    - Minimum: 0
    - Maximum: 64
    - Average: 26.1662


### 4 testo funkcijos
```cpp
void test_file() {
    string input = "random_string_pairs_max100.txt";
    ifstream inputFile(input);
    ofstream file1("output_file100max_1.txt");
    ofstream file2("output_file100max_2.txt");

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string str1, str2;

        // Split the line by the comma to get the two strings
        if (std::getline(ss, str1, ',') && std::getline(ss, str2)) {
            file1 << str1 << "\n";  // Write the first string to the first file
            file2 << str2 << "\n";  // Write the second string to the second file
        }
    }

    inputFile.close();
    file1.close();
    file2.close();

    inputFile.open("output_file100max_1.txt");
    ofstream write(input + "_output1.txt");
    string str_placeholder;

    while (getline(inputFile, str_placeholder)) {
        string decimalString = convert_to_decimal(str_placeholder);
        string stringDEC = convert_to_string(decimalString);
        string scb_dec = Scrambler(decimalString, stringDEC.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        write << hash << endl;
    }

    write.close();
    inputFile.close();

    inputFile.open("output_file100max_2.txt");
    ofstream Write(input + "_output2.txt");

    while (getline(inputFile, str_placeholder)) {
        string decimalString = convert_to_decimal(str_placeholder);
        string stringDEC = convert_to_string(decimalString);
        string scb_dec = Scrambler(decimalString, stringDEC.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        Write << hash << endl;
    }

    inputFile.close();
    Write.close();
}

int calculate_bit_difference(const std::string& hash1, const std::string& hash2) {
    int bit_diff = 0;
    for (size_t i = 0; i < hash1.size(); ++i) {
        unsigned char byte1 = static_cast<unsigned char>(hash1[i]);
        unsigned char byte2 = static_cast<unsigned char>(hash2[i]);
        unsigned char xor_result = byte1 ^ byte2;
        // Count the number of 1s in the XOR result (Hamming distance)
        bit_diff += __builtin_popcount(xor_result);
    }
    return bit_diff;
}

// Function to calculate hex-level difference between two SHA-256 hashes
int calculate_hex_difference(const std::string& hash1, const std::string& hash2) {
    int hex_diff = 0;
    for (size_t i = 0; i < hash1.size(); ++i) {
        if (hash1[i] != hash2[i]) {
            ++hex_diff;
        }
    }
    return hex_diff;
}

int main() {
    const int num_pairs = 100000;
    const int lengths[] = {10, 100, 500, 1000};
    
    std::vector<int> bit_differences;
    std::vector<int> hex_differences;
    
    int min_bit_diff = INT_MAX, max_bit_diff = 0;
    int min_hex_diff = INT_MAX, max_hex_diff = 0;
    int total_bit_diff = 0, total_hex_diff = 0;

    ifstream read1("random_string_pairs_max100.txt_output1.txt");
    ifstream read2("random_string_pairs_max100.txt_output2.txt");

    std::string hash1;
    std::string hash2;

    for (int length : lengths) {
        for (int i = 0; i < num_pairs / 4; ++i) {
            
            // Hash both strings using SHA-256
            read1 >> hash1;
            read2 >> hash2;
            
            // Calculate bit-level and hex-level differences
            int bit_diff = calculate_bit_difference(hash1, hash2);
            int hex_diff = calculate_hex_difference(hash1, hash2);
            
            bit_differences.push_back(bit_diff);
            hex_differences.push_back(hex_diff);
            
            // Update minimum and maximum differences
            min_bit_diff = std::min(min_bit_diff, bit_diff);
            max_bit_diff = std::max(max_bit_diff, bit_diff);
            min_hex_diff = std::min(min_hex_diff, hex_diff);
            max_hex_diff = std::max(max_hex_diff, hex_diff);
            
            total_bit_diff += bit_diff;
            total_hex_diff += hex_diff;
        }
    }

    // Calculate average differences
    double avg_bit_diff = static_cast<double>(total_bit_diff) / num_pairs;
    double avg_hex_diff = static_cast<double>(total_hex_diff) / num_pairs;
    
    // Output the results
    std::cout << "Bit-level differences:" << std::endl;
    std::cout << "Minimum: " << min_bit_diff << std::endl;
    std::cout << "Maximum: " << max_bit_diff << std::endl;
    std::cout << "Average: " << avg_bit_diff << std::endl;
    
    std::cout << "\nHex-level differences:" << std::endl;
    std::cout << "Minimum: " << min_hex_diff << std::endl;
    std::cout << "Maximum: " << max_hex_diff << std::endl;
    std::cout << "Average: " << avg_hex_diff << std::endl;
    
    return 0;
}
```

# Eksperimentinio tyrimo rezultatai

### 1 testo išvados

Šiame teste buvo paimti testo failuose esantys inputai ir suhashuoti naudojantis mano hashavimo funkcija. Gautus rezultatų ilgį patikrinau naudojantis įrankiu esančiu šiame puslapyje `https://www.lettercount.com`.

Visais atvejais hasho ilgis buvo 64 simbolių, tai hash funkcija veikia puikiai šiuo atspektu.

### 2 testo išvados

Šiame teste buvo hashuojamos eilutės esančios šio testo faile ir matuojamas ir išvedamas hashavimo greitis.

Pagal greičio rezultatus hash funkcija veikia visai greitai ir efektyviai.

### 3 testo išvados

Šiame teste buvo paimti testo failuose rastos poros ir išskaidytos į du skirtingus failus ir juose esantys inputai buvo užhashuoti ir patikrinti su nurodytu kodu.

Koliziju kiekis kiekvienu atveju buvo 0, tai hash funkcija atitinka 6 reikalavimą.

### 4 testo išvados

Šiame teste buvo paimti testo faile rasti elementai ir išskaidyti bei užhashuoti lygiai taip pat kaip ir 3 teste. Tada pagal nurodyta kodą buvo apskaičiuotos reikšmės.

Pagal šio testo išvados hash funkcija neveikia optimaliai, bet kaip 2 savaičių darbui visai neblogai.

# Papildomos užduotys

### 1 užduotis

Spartos palyginimas tarp ssh-256 ir mano hash generatoriaus. Šis testas buvo atliekamas pasirašius ssh-256 generatoriu pagal kodą randamą šiame puslapyje `http://www.zedwood.com/article/cpp-sha256-function`. Tad buvo sugenruoti 4 testiniai failai visi po 25000 linijų, po 10, 100, 500 , 1000 ilgumo. Buvo testuojama kaip greita bus suhashintos 10, 100, 1000, 10000, 25000 linijų ir įrašytos į output failą.

Failai: 

- ef_10.txt
- ef_100.txt
- ef_500.txt
- ef_1000.txt

Testo kodai:

```cpp
#include <iostream>
#include <fstream>
#include <chrono>
#include "sha256.h"

using namespace std;
using namespace chrono;

int main(){
    string input = "ef_1000.txt";
    string str_placeholder;
    int i = 0;

    ifstream read;
    read.open(input);
    ofstream write(input + "_output.txt");

    auto start = high_resolution_clock::now();
    while (i < 25000) {
        getline(read, str_placeholder);

        str_placeholder = sha256(str_placeholder);

        write << str_placeholder << endl;

        i++;
    }
    auto stop = high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;

    cout << diff.count() << endl;

    system("pause");

    return 0;
}
```

```cpp
auto start = high_resolution_clock::now();
    while (i < 25000) {
        getline(read, str_placeholder);

        string decimalString = convert_to_decimal(str_placeholder);
        string scb_dec = Scrambler(decimalString, str_placeholder.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        write << hash << endl;

        i++;
    }
    auto stop = high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;

    cout << diff.count() << endl;
```

Rezultatai:

| ssh-256 |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 10 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0001885s | 0.0008776s | 0.007072s | 0.0585016s | 0.143816s |
| 2 | 0.0001843s | 0.0007936s | 0.0066258s | 0.0537173s | 0.142012s |
| 3 | 0.0001658s | 0.000801s | 0.0058283s | 0.056276s | 0.133865s | 

| ssh-256 |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 100 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.000248s | 0.001031s | 0.0081273s | 0.0608638s | 0.152864s |
| 2 | 0.0001966s | 0.0007827s | 0.0076877s | 0.061863s | 0.157531s |
| 3 | 0.0002005s | 0.0010351s | 0.0088392s | 0.0593632s | 0.158376s | 

| ssh-256 |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 500 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0004797s | 0.0016508s | 0.0135581s | 0.102063s | 0.241124s |
| 2 | 0.0002567s | 0.0013856s | 0.0139081s | 0.10475s | 0.252649s |
| 3 | 0.0002175s | 0.0014006s | 0.0130472s | 0.103381s | 0.257518s | 

| ssh-256 |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 1000 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0005612s | 0.0019457s | 0.0194008s | 0.156211s | 0.379072s |
| 2 | 0.0002642s | 0.002026s | 0.0195892s | 0.16072s | 0.379785s |
| 3 | 0.0002923s | 0.0018662s | 0.0165413s | 0.153447s | 0.383071s | 

| Mano hash |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 10 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0003224s | 0.0018359s | 0.0164886s | 0.146471s | 0.348089s |
| 2 | 0.0002707s | 0.0019488s | 0.0152511s | 0.159157s | 0.332322s |
| 3 | 0.0002787s | 0.0018217s | 0.0170708s | 0.146476s | 0.340839s |

| Mano hash |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 100 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0007213s | 0.0033545s | 0.03224s | 0.265788s | 0.67738s |
| 2 | 0.0004847s | 0.003681s | 0.0294569s | 0.250297s | 0.635976s |
| 3 | 0.0007337s | 0.0033653s | 0.0297593s | 0.260272s | 0.654822s | 

| Mano hash |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 500 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0013865s | 0.0115651s | 0.102048s | 1.02839s | 2.56407s |
| 2 | 0.0015027s | 0.0107514s | 0.0992344s | 1.07457s | 2.52774s |
| 3 | 0.0012098s | 0.011023s | 0.0983781s | 1.01573s | 2.64231s | 

| Mano hash |
| Liniju skaicius | 10 | 100 | 1000 | 10000 | 25000 |
| 1000 | laikas | laikas | laikas | laikas | laikas |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 0.0038992s | 0.0198524s | 0.200292s | 1.94406s | 4.92643s |
| 2 | 0.0021072s | 0.0205061s | 0.200365s | 1.93235s | 4.80392s |
| 3 | 0.0021554s | 0.0202164s | 0.205636s | 1.92314s | 4.82039s | 

Išvados:

Mano hash generatorius yra lėtesnis nuo 2 iki 10 kartų už ssh-256 generatorių.
