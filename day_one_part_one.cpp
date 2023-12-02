#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

ifstream infile("input.txt");

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

int main() {
    string line;
    int sum = 0;

    while (getline(infile, line))
    {
        vector< char > arr;

        for (int i = 0; i < line.length(); i++) {
            if (is_number(line[i])) { arr.push_back(line[i]);}
        }
        
        if (arr.size() > 0){
            string str_num;
            str_num[0] = arr.front();
            str_num[1] = arr.back();
            int number = stoi(str_num);
            sum += number;
        }

    }
    cout << "The result is:" << sum << endl;
    return 0;
}

