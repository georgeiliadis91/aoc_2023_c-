#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <set>

using namespace std;

ifstream infile("input_day_four.txt");

vector<string> split_string(const string& input, char delimiter) {
    vector<string> result;
    istringstream stream(input);
    string token;

    while(std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

// num parser 
void parse_numbers(string card_numbers,set<int>& set_data){
    vector<char> char_vec;

    for(int i = 0; i < card_numbers.length(); i++){

        if(card_numbers[i] != ' '){
            char_vec.push_back(card_numbers[i]);

            //Last element has nothing after it, so if we are here do not skip it add it.
            if( i == card_numbers.length() - 1){
                string num_str(char_vec.begin(), char_vec.end());
                set_data.insert(stoi(num_str));
            }
        }

        if(card_numbers[i] == ' '){
            if(char_vec.size() > 0){
                string num_str(char_vec.begin(), char_vec.end());
                set_data.insert(stoi(num_str));
            }
            char_vec.clear();
        }
    }   
}

int main() {
    string line;
    unordered_map<int,int> card_amount_map;

    while (getline(infile, line))
    {
        vector<string> line_vec = split_string(line, ':');
        vector<string> nums_vec = split_string(line_vec[1], '|');
        vector<string> game_label = split_string(line_vec[0], ' ');

        cout << game_label[0];

        int key_val = stoi(game_label[1]);
        if(card_amount_map.find(key_val) == card_amount_map.end()){
            card_amount_map[key_val] = 1;
        }

        set<int> game_res_set;
        set<int> player_choice_set;

        parse_numbers(nums_vec[0],game_res_set);
        parse_numbers(nums_vec[1],player_choice_set);

        int score = 0 ;

        for (int num : player_choice_set) {
            if(game_res_set.count(num) > 0){
                score++;
            }
        }

        if(score > 0 ){
            int card_copies = card_amount_map[key_val];
            for(int i = 1; i <= score; i++){
                int key = key_val + i;
                if(card_amount_map.find(key) == card_amount_map.end()){
                    card_amount_map[key] = card_copies;
                }else{
                    card_amount_map[key] += card_copies;
                }
            }
        }

        game_res_set.clear();
        player_choice_set.clear();
    }
        cout<< "here" <<endl;

    int sum = 0 ;
    for (auto const& x : card_amount_map){
        cout << x.first  << ':' << x.second << endl;
        sum += x.second;
    }

    cout << "The result is: " << sum << endl;
    return 0;
}

