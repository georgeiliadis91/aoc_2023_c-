#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <map>

using namespace std;

ifstream infile("input_day_three.txt");

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

string construct_str(int a,int b){
    string partA = to_string(a);
    string partB = to_string(b);
    return partA + "-" + partB;
}

// In order for an entry to be valid we need a char that 
// is not a . or a number to surround it
string check_if_valid_entry(vector<string> grid, int s_idx, int e_idx, int row, int vl, int hl){

    bool is_first_in_row = s_idx == 0;
    bool is_last_in_row = e_idx == hl - 1;
    bool is_first_line = row == 0;
    bool is_last_line = row == vl - 1;

    if( !is_first_in_row && grid[row][s_idx-1] == '*' ){
        return construct_str(row,s_idx-1);
    }

    if( !is_last_in_row && grid[row][e_idx+1] == '*' ){
        return construct_str(row,e_idx+1);
    }

    // Calc indexes
    int start = s_idx - 1;
    if(is_first_in_row){ start = s_idx; }

    int end = e_idx + 1;
    if(is_last_in_row){ end = e_idx; }

    // Previours line check 
    if(!is_first_line){
        for(int i = start ; i <= end ; i++ ){
            if(grid[row - 1][i] == '*'){
                return construct_str(row-1,i);
            }
        }
    }

    // next line check
    if(!is_last_line){
        for(int i = start ; i <= end ; i++ ){
            if(grid[row + 1][i] == '*'){
                return construct_str(row+1,i);
            }
        }
    }

    return "NOT_FOUND";
}

int main() {
    string line;
    int sum = 0;
    vector<string> grid_vec;
    int h_len, v_len;

    while (getline(infile, line)){
        grid_vec.push_back(line);  
    }

    h_len = grid_vec[0].length();
    v_len = grid_vec.size();

    vector<char> num_candidate;
    map<string,vector<string> > star_hash_map;

    for(int i = 0; i < v_len ; i++){
        for(int j = 0; j < h_len ; j++){

            const bool is_num = is_number(grid_vec[i][j]);
            if(is_num){
                num_candidate.push_back(grid_vec[i][j]);
            }
            // If the vec is not empty
            // and
            // Check if we are at the end Or The next char is not a num
            int size =  num_candidate.size() ;

            if( (!is_num || j == (h_len-1) ) && num_candidate.size() > 0 ){
                // Go do the num verification process.
                std::string str(num_candidate.begin(), num_candidate.end());;

                int s_index;
                int e_index;

                if(is_num){
                    e_index = j;
                    s_index = j - num_candidate.size() +1 ;
                }else{
                    e_index = j -1;
                    s_index = j -1 - num_candidate.size() + 1;
                }

                string res = check_if_valid_entry(grid_vec, s_index, e_index, i, v_len, h_len);

                if(res != "NOT_FOUND"){
                    star_hash_map[res].push_back(str);
                }

                num_candidate.clear();
            }
        }
    }

    for (const auto& pair : star_hash_map) {
        const string& key = pair.first;
        const vector<string>& values = pair.second;

        int amount = 1;
        if(values.size() > 1){
            cout<< " The key: " << key;
            for (string value : values) {
                cout<< " val: " << value;
                amount *= stoi(value);
            }
            cout <<endl;
            sum+=amount;
        }
    }

    cout << sum << endl;
    return 0;
}

