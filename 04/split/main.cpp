#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string line, const char separator, bool ignore_empty = false) 
{
    std::vector<std::string> splitted_string;

    std::string word = "";
    for(char c: line)
    {
        if(c != separator)
        {
            word += c;
        } else
        {
            splitted_string.push_back(word);
            word = "";
        }
    }

    std::string::size_type temp = word.find(separator);
    if(temp == std::string::npos)
    {
        splitted_string.push_back(word);
    }
    
    // ignore_empty = true
    if(ignore_empty)
    {
        std::vector<std::string> splitted_string_no_empty;
        for(std::string s: splitted_string)
        {
            if(s != "")
            {
                splitted_string_no_empty.push_back(s);
            }
        }

        return splitted_string_no_empty;
    }

    return splitted_string;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
