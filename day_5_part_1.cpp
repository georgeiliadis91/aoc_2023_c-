#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <set>

using namespace std;

ifstream infile("input_day_5.txt");

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

vector<string> split_string(const string& input, char delimiter) {
    vector<string> result;
    istringstream stream(input);

    string token;

    while(std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

vector<long> parse_numbers(string str){
    vector<char> char_vec;
    vector<long> row_data;
    cout << "Parsing line:" << str << endl;
    for(int i = 0; i < str.length(); i++){

        if(str[i] != ' '){
            char_vec.push_back(str[i]);
        }

        if(str[i] == ' '){
            if(char_vec.size() > 0){
                string num_str(char_vec.begin(), char_vec.end());
                row_data.push_back(stol(num_str));
            }
            char_vec.clear();
        }
    }   

    if(char_vec.size() > 0){
        string num_str(char_vec.begin(), char_vec.end());
        row_data.push_back(stol(num_str));
    }

    return row_data;
}

int main() {
    string line;
    map<int,vector<vector<long> >  > elem_map;


    int map_idx = -1;
    bool parse_mode = false;
    vector<vector<long> > group_data;

    // Parse the input data input maps
    while (getline(infile, line)){
        if(line.find("seeds:") != string::npos){
            // @todo: Extract the seed numbers into a map.
            continue;
        }

        if(line.find("map:") != string::npos){
            parse_mode = true;
            map_idx++;
            cout << "Updated index: " << map_idx <<endl;
            continue;
        }

        if(line.length() == 0 ){
            parse_mode = false;
            elem_map[map_idx] = group_data;
            cout << "Encountered empty line." << endl;
            continue;
        }


        if(parse_mode){
            vector<long> data_vec = parse_numbers(line);
            group_data.push_back( data_vec );
        }
    }

    return 0;
}

