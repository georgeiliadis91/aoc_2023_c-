#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

using namespace std;

ifstream infile("input_day_2.txt");


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> split_string(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

int main() {

    std::unordered_map<std::string,int> data_map;

    data_map["red"] = 12;
    data_map["green"] = 13;
    data_map["blue"] = 14;


    string line;
    int sum = 0 ;

    while (getline(infile, line))
    {

        std::vector<std::string> line_vec = split_string(line, ':');
        // Got the game part of the line
        std::vector<std::string> game_num = split_string(line_vec[0], ' ');

        bool is_game_valid = true;
        std::string game;

        istringstream iss2(line_vec[1]);

        // Splitting the games
        while (std::getline(iss2, game, ';')) {

            std::string game_set;
            istringstream iss3(game);
            
            // Splitting to sets
            while (std::getline(iss3, game_set, ',')) {
                
                std::string trimmed_str = trim(game_set);
                std::vector<std::string> game_set_vec= split_string(trimmed_str, ' ');

                if(data_map[game_set_vec[1]] < std::stoi(game_set_vec[0])){
                    is_game_valid = false;
                }

                if(!is_game_valid) break;

            }
            if(!is_game_valid) break;
        }

        if(is_game_valid){
            sum += std::stoi(game_num[1]);
        }

    }

    cout << "The result is: " << sum << endl;
    return 0;
}

