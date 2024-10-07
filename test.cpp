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

    // string b = sha256(str_placeholder);
    // cout << b << endl;

    // system("pause");

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