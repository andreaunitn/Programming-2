#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

using Count = pair<unsigned int, set<unsigned int> >;

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

    map<string, Count> word_count;

    unsigned int line_count = 1;
    string line;

    while(getline(input_file, line))
    {
        string word = "";
        string::iterator iter = line.begin();

        bool loop = true;
        while(loop)
        {
            if(iter == line.end())
            {
                if(word_count.find(word) != word_count.end())
                {
                    word_count.at(word).second.insert(line_count);
                    word_count.at(word).first = word_count.at(word).second.size();
                } else
                {
                    Count tmp;
                    set<unsigned int> s;

                    tmp.first = 1;
                    tmp.second = s;
                    tmp.second.insert(line_count);

                    word_count.insert({word, tmp});
                }

                word = "";
                break;
            }

            if(*iter == ' ')
            {
                if(word_count.find(word) != word_count.end())
                {
                    word_count.at(word).second.insert(line_count);
                    word_count.at(word).first = word_count.at(word).second.size();
                } else
                {
                    Count tmp;
                    set<unsigned int> s;

                    tmp.first = 1;
                    tmp.second = s;
                    tmp.second.insert(line_count);

                    word_count.insert({word, tmp});
                }

                word = "";
            } else 
            {
                word += *iter;
            }
            iter++;
        }

        line_count++;
    }

    for(auto word: word_count)
    {
        cout << word.first << " " << word.second.first << ": ";

        auto it = word.second.second.begin();
        for(unsigned int i = 0; i < word.second.second.size(); ++i)
        {
            if(i == word.second.second.size() - 1)
            {
                cout << *it;
            } else
            {
                cout << *it << ", ";
            }

            ++it;
        }

        cout << endl;
    }

    input_file.close();

    return 0;
}