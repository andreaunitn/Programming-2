#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>

using namespace std;

int main()
{
    cout << "Input file: ";

    string input_file_name;
    cin >> input_file_name;

    ifstream input_file(input_file_name);
    if(!input_file)
    {
        cout << "Error! The file " << input_file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, unsigned int> name_points;

    string line;
    while(getline(input_file, line))
    {
        string name = "";
        string str_points = "";

        string::iterator iter = line.begin();
        while(*iter != ':')
        {
            name += *iter;
            iter++;
        }

        iter++;
        while(iter != line.end())
        {
            str_points += *iter;
            iter++;
        }

        unsigned int points = stoi(str_points);

        if(name_points.find(name) != name_points.end())
        {
            unsigned int tmp = name_points.at(name);
            tmp += points;
            name_points.at(name) = tmp;
        } else 
        {
            name_points.insert({name, points});
        }
    }

    cout << "Final scores:" << endl;
    
    for(pair<string, unsigned int> score: name_points)
    {
        cout << score.first << ": " << score.second << endl;
    }

    input_file.close();

    return 0;
}