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

string convert_string(string str)
{
    map<char, string> card_value_map;
    card_value_map['2'] = "0";
    card_value_map['3'] = "1";
    card_value_map['4'] = "2";
    card_value_map['5'] = "3";
    card_value_map['6'] = "4";
    card_value_map['7'] = "5";
    card_value_map['8'] = "6";
    card_value_map['9'] = "7";
    card_value_map['T'] = "8";
    card_value_map['J'] = "9";
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

        // Figure out what hands we have
        // Case: 5 of a kind
        if (hand_types.size() == 1)
        {
            sorted_hands[6].insert(hand);
        }

        // 4 of a kind OR Full house
        if (hand_types.size() == 2)
        {
            for (auto const card : hand_types)
            {
                // 4 of a kind
                if (card.second == 4 || card.second == 1)
                {
                    sorted_hands[5].insert(hand);
                    break;
                }

                if (card.second == 3 || card.second == 2)
                {
                    sorted_hands[4].insert(hand);
                    break;
                }
            }
        }

        // 2 of a kind, needs extract check for 3, 1 , 1
        if (hand_types.size() == 3)
        {
            for (auto const card : hand_types)
            {
                // Three of a kind
                if (card.second == 3)
                {
                    sorted_hands[3].insert(hand);
                    break;
                }
                // 2 pair
                if (card.second == 2)
                {
                    sorted_hands[2].insert(hand);
                    break;
                }
            }
        }

        // Case: High Pair
        if (hand_types.size() == 4)
        {
            sorted_hands[1].insert(hand);
        }

        // Case: High Card
        if (hand_types.size() == 5)
        {
            sorted_hands[0].insert(hand);
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
