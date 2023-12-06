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

vector<string> split_string(const string &input, char delimiter)
{
    vector<string> result;
    istringstream stream(input);

    string token;

    while (std::getline(stream, token, delimiter))
    {
        result.push_back(token);
    }

    return result;
}

vector<long> parse_numbers(string str)
{
    vector<char> char_vec;
    vector<long> row_data;

    cout << "Parsing line:" << str << endl;

    for (int i = 0; i < str.length(); i++)
    {

        if (str[i] != ' ')
        {
            char_vec.push_back(str[i]);
        }

        if (str[i] == ' ')
        {
            if (char_vec.size() > 0)
            {
                string num_str(char_vec.begin(), char_vec.end());
                row_data.push_back(stol(num_str));
            }
            char_vec.clear();
        }
    }

    if (char_vec.size() > 0)
    {
        string num_str(char_vec.begin(), char_vec.end());
        row_data.push_back(stol(num_str));
    }

    return row_data;
}

int main()
{
    string line;
    map<int, vector<vector<long> > > elem_map;

    int map_idx = -1;
    bool parse_mode = false;
    vector<vector<long> > group_data;
    vector<long> seed_vec;

    // Parse the input data input maps
    while (getline(infile, line))
    {
        if (line.find("seeds:") != string::npos)
        {
            vector<string> seed_line = split_string(line, ':');
            seed_vec = parse_numbers(seed_line[1]);
            continue;
        }

        if (line.find("map:") != string::npos)
        {
            parse_mode = true;
            map_idx++;
            cout << "Updated index: " << map_idx << endl;
            continue;
        }

        if (line.length() == 0)
        {
            if (parse_mode)
            {
                elem_map[map_idx] = group_data;
            }
            parse_mode = false;
            group_data.clear();
            cout << "Encountered empty line." << endl;
            continue;
        }

        if (parse_mode)
        {
            vector<long> data_vec = parse_numbers(line);
            group_data.push_back(data_vec);
        }
    }

    // Handle last row elem
    if (group_data.size() > 0)
    {
        elem_map[map_idx] = group_data;
    }

    // @todo: For each seed loop through the elem_map
    // for each entry check if the seed is between the range of the second col and the addition of the third column.
    // If it is get the diff and add it to the first column.
    // And repeat.
    vector<long> seed_cost;
    for (auto const &seed : seed_vec)
    {
        cout << "The seed val:" << seed << endl;
        for (auto const &elem : elem_map)
        {
            cout << "Map index: " << elem.first << endl;
            vector<vector<long> > map_data = elem.second;

            for (auto const &row : map_data)
            {
                if (seed >= row[1] && seed <= row[1] + row[2])
                {
                    cout << "bingo!" << endl;
                }

                // for(auto const& col : row){
                //     cout << col << " ";
                // }
                cout << endl;
            }
        }
    }

    return 0;
}
