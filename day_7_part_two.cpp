#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <set>

using namespace std;

ifstream infile("input_day_7.txt");

vector<string> split_string(string input, char delimiter)
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

int hand_sort(map<char, int> m)
{
    if (m.size() == 1)
    {
        return 6;
    }

    // 4 of a kind OR Full house
    if (m.size() == 2)
    {
        for (auto const card : m)
        {
            // 4 of a kind
            if (card.second == 4 || card.second == 1)
            {
                return 5;
            }

            if (card.second == 3 || card.second == 2)
            {
                return 4;
            }
        }
    }

    // 2 of a kind, OR 3 high pair
    if (m.size() == 3)
    {
        for (auto const card : m)
        {
            // Three of a kind
            if (card.second == 3)
            {
                return 3;
            }
            // 2 pair
            if (card.second == 2)
            {
                return 2;
            }
        }
    }

    // Case: High Pair
    if (m.size() == 4)
    {
        return 1;
    }

    // Case: High Card
    if (m.size() == 5)
    {
        return 0;
    }
}

string convert_string(string str)
{
    map<char, string> card_value_map;
    card_value_map['J'] = "0";
    card_value_map['2'] = "1";
    card_value_map['3'] = "2";
    card_value_map['4'] = "3";
    card_value_map['5'] = "4";
    card_value_map['6'] = "5";
    card_value_map['7'] = "6";
    card_value_map['8'] = "7";
    card_value_map['9'] = "8";
    card_value_map['T'] = "9";
    card_value_map['Q'] = "A";
    card_value_map['K'] = "B";
    card_value_map['A'] = "C";

    string new_string = "";

    for (int i = 0; i < str.length(); i++)
    {
        new_string += card_value_map[str[i]];
    }

    return new_string;
}

int main()
{
    // Converting those to equivalent single digit chars that can be
    // used inside a sorted map to be alphabetically be sorted
    // without requiring any operation
    string line;
    map<string, int> hand_map;

    while (getline(infile, line))
    {
        vector<string> parsed_line = split_string(line, ' ');
        hand_map[convert_string(parsed_line[0])] = stoi(parsed_line[1]);
    }

    map<int, map<string, int> > sorted_hands;
    for (auto const &hand : hand_map)
    {
        map<char, int> hand_types;

        for (int i = 0; i < hand.first.length(); i++)
        {
            if (hand_types.count(hand.first[i]) > 0)
            {
                hand_types[hand.first[i]] += 1;
            }
            else
            {
                hand_types[hand.first[i]] += 1;
            }
        }

        int amount_of_j = hand_types.count('0');
        if (amount_of_j <= 0 || amount_of_j == 5)
        {
            int key = hand_sort(hand_types);
            sorted_hands[key].insert(hand);
        }
        else
        {
            map<char, int> tmp_hand_types;
            int amount = 0;
            char max_key;
            for (auto const &item : hand_types)
            {
                if (item.first != '0' && item.second > amount)
                {
                    amount = item.second;
                    max_key = item.first;
                }
            }

            for (auto const &item : hand_types)
            {
                if (item.first != 'J')
                {
                    if (item.first == max_key)
                    {
                        tmp_hand_types[item.first] = item.second + amount;
                    }
                    else
                    {
                        tmp_hand_types[item.first] = item.second;
                    }
                }
            }

            int key = hand_sort(tmp_hand_types);
            sorted_hands[key].insert(hand);
        }
    }

    // Calculate score

    long score = 0;
    long idx = 1;
    for (auto const &group : sorted_hands)
    {
        for (auto const &hand : group.second)
        {
            cout << hand.first << " " << hand.second;
            score += idx * hand.second;
            cout << " The score: " << score << " The index " << idx << endl;
            idx++;
        }
    }
    cout << "Result: " << score << endl;
    return 0;
}
