/* Theatre
 *
 * Desc:
 *   This program implements a theatre visualization system for several
 * cities. Each theatre contains information about the play, the players
 * present and the number of available seats.
 *   At first, the program reads data from a file given as input and saves
 * them appropriately within a predefined data structure. Next, a user
 * interface is shown in which commands are entered to obtain different
 * types of information, such as: the names of the theatres, the names of
 * plays and the cities in which they take place, and the players in a
 * particular play.
 *   Each time the user enters a command it is checked for correctness
 * and if not an error message is shown.
 *   The program terminates when the 'quit' command is entered.
 *
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 *
 * Notes about the program and its implementation (if any):
 *
 * */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#include "theatre.hh"

using namespace std;

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const string PROMPT = "the> ";

// Error and other messages
const string EMPTY_FIELD = "Error: empty field in line ";
const string FILE_ERROR = "Error: input file cannot be opened";
const string WRONG_PARAMETERS = "Error: wrong number of parameters";
const string THEATRE_NOT_FOUND = "Error: unknown theatre";
const string PLAY_NOT_FOUND = "Error: unknown play";
const string PLAYER_NOT_FOUND = "Error: unknown player";
const string TOWN_NOT_FOUND = "Error: unknown town";
const string COMMAND_NOT_FOUND = "Error: unknown command";
const string NOT_AVAILABLE = "No plays available";

// Casual split function, if delim char is between "'s, ignores it.
vector<string> split(const string& str, char delim)
{
    vector<string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    return result;
}

// Checks if the given string is made only of spaces
bool has_only_spaces(const string& str)
{
    string::const_iterator it = str.begin();
    while(it != str.end())
    {
        if(*it != ' ')
        {
            return false;
        }

        it++;
    }

    return true;
}

// Checks if the line of the input file respects the constraints
bool check_input(const vector<string>& input)
{
    if(input.size() != NUMBER_OF_FIELDS)
    {
        return false;
    }

    for(string elem: input)
    {
        if(has_only_spaces(elem))
        {
            return false;
        }
    }

    return true;
}

// Checks if the input command is in the list of the possible ones
bool is_command_valid(const string& command)
{
    vector<string> commands = {"theatres", "plays", "theatres_of_play", "plays_in_theatre", "plays_in_town", "players_in_play"};
    return find(commands.begin(), commands.end(), command) != commands.end();
}

// Checks for the given command if the number of arguments is correct
bool check_input_command(const string& command, const vector<string>& arguments)
{
    if(command == "theatres") {return arguments.size() == 1;}
    if(command == "plays") {return arguments.size() == 1;}
    if(command == "theatres_of_play") {return arguments.size() == 2;}
    if(command == "plays_in_theatre") {return arguments.size() == 2;}
    if(command == "plays_in_town") {return arguments.size() == 2;}
    if(command == "players_in_play") {return arguments.size() == 2 || arguments.size() == 3;}

    return false;
}

// Saves the data read from the file within the chosen structure
void save_info_into_data_structure(map<string, vector<Theatre> >& city_theatre, const vector<string>& splitted_line)
{
    // Extracts all info from the given file line
    const string town = splitted_line[0];
    const string theatre_name = splitted_line[1];
    const string play_name = splitted_line[2];
    const string player = splitted_line[3];
    const string seats = splitted_line[4];

    if(city_theatre.find(town) != city_theatre.end())
    {
        for(Theatre& t: city_theatre.at(town))
        {
            if(t.get_name() == theatre_name)
            {
                t.insert_play(play_name, player, seats);
                return;
            }
        }

        Theatre theatre(theatre_name);
        theatre.insert_play(play_name, player, seats);

        city_theatre.at(town).push_back(theatre);
    } else
    {
        Theatre theatre(theatre_name);
        theatre.insert_play(play_name, player, seats);

        vector<Theatre> tmp;
        tmp.push_back(theatre);

        city_theatre.insert({town, tmp});
    }
}

// Prints all the known theatres in alphabetical order
void theatres(const map<string, vector<Theatre> >& city_theatre)
{
    set<string> theatre_names;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            theatre_names.insert(t.get_name());
        }
    }

    for(string name: theatre_names)
    {
        cout << name << endl;
    }
}

// Prints, one below the other, all the plays in alphabetical order
void plays(const map<string, vector<Theatre> >& city_theatre)
{
    set<string> play_names;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            set<string> tmp = t.get_play_names();
            for(string elem: tmp)
            {
                play_names.insert(elem);
            }
        }
    }

    for(string name: play_names)
    {
        cout << name << endl;
    }
}

// Prints all the theatres that offer the given play
void theatres_of_play(const map<string, vector<Theatre> >& city_theatre, const string& name)
{
    set<string> theatre_names;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            if(t.is_play_in_theatre(name))
            {
                theatre_names.insert(t.get_name());
            }
        }
    }

    // If no play is found prints the corresponding error message
    if(theatre_names.size() == 0)
    {
        cout << PLAY_NOT_FOUND << endl;
    } else
    {
        for(string name: theatre_names)
        {
            cout << name << endl;
        }
    }
}

// Prints the plays of the given theatre
void plays_in_theatre(const map<string, vector<Theatre> >& city_theatre, const string& name)
{
    set<string> play_names;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            if(t.get_name() == name)
            {
                set<string> tmp = t.get_play_names();
                for(string elem: tmp)
                {
                    play_names.insert(elem);
                }
            }
        }
    }

    // If no theatre is found prints the corresponding error message
    if(play_names.size() == 0)
    {
        cout << THEATRE_NOT_FOUND << endl;
    } else
    {
        for(string name: play_names)
        {
            cout << name << endl;
        }
    }
}

// Prints those plays in the given town that have free seats
void plays_in_town(const map<string, vector<Theatre> >& city_theatre, const string& name)
{
    set<string> play_names;

    bool found_town = false;
    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        if(it->first == name)
        {
            found_town = true;
        }
    }

    // No town found
    if(!found_town)
    {
        cout << TOWN_NOT_FOUND << endl;
        return;
    }

    vector<Theatre> theatres = city_theatre.at(name);
    for(Theatre t: theatres)
    {
        set<string> tmp = t.get_free_seat_plays();
        for(string elem: tmp)
        {
            play_names.insert(elem);
        }
    }

    // If no play has free seats print the corresponding error message
    if(play_names.size() == 0)
    {
        cout << NOT_AVAILABLE << endl;
    } else
    {
        for(string name: play_names)
        {
            cout << name << endl;
        }
    }
}

// Prints the players in the given play
void players_in_play(const map<string, vector<Theatre> >& city_theatre, const string& play_name)
{
    set<string> player_names;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            set<string> tmp = t.get_player_names(play_name);
            for(string elem: tmp)
            {
                player_names.insert(elem);
            }
        }
    }

    // If no play is found prints the corresponding error message
    if(player_names.size() == 0)
    {
        cout << PLAY_NOT_FOUND << endl;
    } else
    {
        for(string name: player_names)
        {
            cout << name << endl;
        }
    }
}

// Prints the players in the given play. In this case the function accepts also the name of the theatre in which to search
void players_in_play_with_theatre_arg(const map<string, vector<Theatre> >& city_theatre, const string& play_name, const string& theatre_name)
{
    set<string> player_names;

    bool play_found = false;
    bool theatre_found = false;

    map<string, vector<Theatre> >::const_iterator it;
    for(it = city_theatre.begin(); it != city_theatre.end(); it++)
    {
        for(Theatre t: it->second)
        {
            if(t.get_name() == theatre_name)
            {
                theatre_found = true;

                if(t.is_play_in_theatre(play_name))
                {
                    play_found = true;
                }

                set<string> tmp = t.get_player_names(play_name);
                for(string elem: tmp)
                {
                    player_names.insert(elem);
                }
            }
        }
    }

    // If no theatre is found prints the corresponding error message
    if(!theatre_found)
    {
        cout << THEATRE_NOT_FOUND << endl;
        return;
    }

    // If no play is found prints the corresponding error message
    if(!play_found)
    {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }

    for(string name: player_names)
    {
        cout << name << endl;
    }
}

// Takes as input the data structure and the command. Performs all the checks and in case call the appropriate function
void parse_and_execute_command(const map<string, vector<Theatre> >& city_theatre, const string& command)
{
    vector<string> arguments = split(command, ' ');

    // Checks if command exists
    if(!is_command_valid(arguments[0]))
    {
        cout << COMMAND_NOT_FOUND << endl;
        return;
    }

    // Checks if command has the right number of arguments
    if(!check_input_command(arguments[0], arguments))
    {
        cout << WRONG_PARAMETERS << endl;
        return;
    }

    // Parse and execute command
    if(arguments[0] == "theatres")
    {
        theatres(city_theatre);
    } else if(arguments[0] == "plays")
    {
        plays(city_theatre);
    } else if(arguments[0] == "theatres_of_play")
    {
        theatres_of_play(city_theatre, arguments[1]);
    } else if(arguments[0] == "plays_in_theatre")
    {
        plays_in_theatre(city_theatre, arguments[1]);
    } else if(arguments[0] == "plays_in_town")
    {
        plays_in_town(city_theatre, arguments[1]);
    } else if(arguments[0] == "players_in_play")
    {
        if(arguments.size() == 2)
        {
            players_in_play(city_theatre, arguments[1]);
        } else
        {
            players_in_play_with_theatre_arg(city_theatre, arguments[1], arguments[2]);
        }
    }
}

// Main function
int main()
{
    // Data structure
    map<string, vector<Theatre> > city_theatre;

    string file_name;
    cout << "Input file: ";
    cin >> file_name;

    // File opening
    ifstream input_file(file_name);
    if(!input_file)
    {
        cout << FILE_ERROR << endl;
        return EXIT_FAILURE;
    }

    // Reading file and saving info into data structure
    string line;
    unsigned int line_number = 1;
    while(getline(input_file, line))
    {
        vector<string> splitted_line = split(line, ';');
        if(!check_input(splitted_line))
        {
            cout << EMPTY_FIELD << line_number << endl;
            return EXIT_FAILURE;
        }

        save_info_into_data_structure(city_theatre, splitted_line);

        line_number++;
    }

    input_file.close();

    // Reading command to execute
    while(true)
    {
        cout << PROMPT;

        string command;
        getline(cin >> ws, command);

        // Exit if 'quit' command is entered
        if(command == "quit")
        {
            break;
        }

        parse_and_execute_command(city_theatre, command);
    }

    return EXIT_SUCCESS;
}
