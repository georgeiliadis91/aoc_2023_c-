#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <set>

using namespace std;

ifstream infile("input_day_6.txt");

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
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            char_vec.push_back(str[i]);
        }
    }
    // End of line handling
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
    vector<long> time_vec;
    vector<long> distance_vec;

    while (getline(infile, line))
    {
        if (line.find("Time:") != string::npos)
        {
            vector<string> time_line = split_string(line, ':');
            time_vec = parse_numbers(time_line[1]);
        }

        if (line.find("Distance:") != string::npos)
        {
            vector<string> distance_line = split_string(line, ':');
            distance_vec = parse_numbers(distance_line[1]);
        }
    }

    map<int, vector<long> > times_map;
    for (long i = 0; i < distance_vec.size(); i++)
    {
        const long goal_to_beat = distance_vec[i];
        const long time_limit = time_vec[i];
        for (long j = 0; j < time_limit; j++)
        {
            long time_left = time_limit - j;
            long distance_covered = j * time_left;
            if (distance_covered >= goal_to_beat)
            {
                times_map[i].push_back(distance_covered);
            }
        }
    }

    int total = 1;
    for (auto const &item : times_map)
    {
        cout << "Map index: " << item.second.size() << endl;
        total *= item.second.size();
    }
    cout << "result: " << total << endl;
    return 0;
}
