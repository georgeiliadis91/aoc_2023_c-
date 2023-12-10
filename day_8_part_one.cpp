#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ifstream infile("input_day_8.txt");

vector<string> split_string(string input, char delimiter)
{
    vector<string> result;
    istringstream stream(input);
    string token;
    
    int line_idx = 0;
    while (std::getline(stream, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');

    if (first == string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

string extract_chars(string str){
    string s = "";
    for(int i = 0; i < str.length() ; i++){
        if(str[i]!= ' ' && str[i] != '(' && str[i] != ')' ){
            s+=str[i];
        }
    }
    return s;

}

vector<string> extract_node_paths(string str){
    vector<string> nodes;
    vector<string> dirty_nodes = split_string(str,',');
    for(int i = 0; i < dirty_nodes.size(); i++){
        nodes.push_back(extract_chars(dirty_nodes[i]));
    }
    return nodes;
}

int main()
{
    string line;
    string steps_vector; 
    map<string, vector<string> > node_map;
    int line_idx = 0 ;

    while (getline(infile, line))
    {
        // First line is the steps input
        if(line_idx == 0 ){
            steps_vector = line;
            line_idx++;
            continue;
        }

        if(line.length() == 0){
            //empty line
            continue;
        }

        // Node creation
        // Split on = get, trim first part -> key
        // Second part extract chars as string.
        vector<string> str_parts = split_string(line, '=');
        node_map[trim(str_parts[0])] = extract_node_paths(str_parts[1]);
        line_idx++;
    }

    string start_node = "AAA";
    string end_node= "ZZZ";
    long idx = 0 ;
    string curr_node = start_node;

    while(true){
        char step = steps_vector[idx % steps_vector.size()];

        if(curr_node == end_node){
            break;
        }

        if(step == 'L'){
            curr_node = node_map[curr_node][0];
        }else{
            curr_node = node_map[curr_node][1];
        }
               
        idx++;
    }

    cout << "Result: " << idx << endl;

    return 0;
}
