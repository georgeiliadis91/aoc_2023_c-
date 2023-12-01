#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

std::ifstream infile("input.txt");

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

int main() {
    // Declare an ordered_map with string keys and int values
    std::unordered_map<std::string, char> num_hash_map;

    num_hash_map["one"] = '1';
    num_hash_map["two"] = '2';
    num_hash_map["three"] = '3';
    num_hash_map["four"] = '4';
    num_hash_map["five"] = '5';
    num_hash_map["six"] = '6';
    num_hash_map["seven"] = '7';
    num_hash_map["eight"] = '8';
    num_hash_map["nine"] = '9';

    std::string line;
    int sum = 0;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::vector< char > arr;

        std::map<int, char> value_store;
        // Replace number string with numbers on each line
        for (const auto& pair : num_hash_map) {
            // Check if value inside the hash map exists and save the index of where it begins
            size_t start = line.find(pair.first);

            while(start != std::string::npos) {
                value_store[start] = pair.second;

                // Check if there is another
                start = line.find(pair.first, start+1);
            }
        }

        for (int i = 0; i < line.length(); i++) {
            if (is_number(line[i])) {
                value_store[i] = line[i];
            }
        }

        string str_num;
        str_num[0] = value_store.begin()->second;
        str_num[1] = value_store.rbegin()->second;
        int number = std::stoi(str_num);
        sum += number;


    }
    cout << "The result is:" << sum << endl;
    return sum;
}

