#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_recursive(std::map<std::string, std::vector<std::string> >& data, std::string& id, std::string identation)
{
    std::cout << identation << id << std::endl;
    if(data.find(id) == data.end())
    {
        return;
    } else 
    {
        identation += "..";
        for(std::string marketer: data.at(id))
        {
            print_recursive(data, marketer, identation);
        }
    }
}

unsigned int count(std::map<std::string, std::vector<std::string> >& data, std::string& id)
{
    if (data.find(id) != data.end())
    {
        unsigned int totalCount = data.at(id).size();
        for (std::string marketer : data.at(id))
        {
            totalCount += count(data, marketer);
        }
        return totalCount;
    }

    return 0;
}

unsigned int maxDepth(std::map<std::string, std::vector<std::string> >& data, std::string& id)
{
    if (data.find(id) != data.end())
    {
        unsigned int maxChildDepth = 1;
        for (std::string marketer : data.at(id))
        {
            unsigned int childDepth = maxDepth(data, marketer);
            maxChildDepth = std::max(maxChildDepth, childDepth);
        }
        return maxChildDepth + 1;
    }

    return 1;
}

int main()
{
    std::map<std::string, std::vector<std::string> > data;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if(data.find(id1) != data.end())
            {
                data.at(id1).push_back(id2);
            } else 
            {
                std::vector<std::string> tmp;
                tmp.push_back(id2);

                data.insert({id1, tmp});
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::string identation = "";
            print_recursive(data, id, identation);
        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            unsigned int subnetword_size = count(data, id);
            std::cout << subnetword_size << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            unsigned int network_depth = maxDepth(data, id);
            std::cout << network_depth << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
