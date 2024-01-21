 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "theatre.hh"

using namespace std;

Theatre::Theatre(const string& name): name_(name) {}

void Theatre::insert_play(const string& play_name, const string& player, const string& seats)
{
    pair<string, string> p;
    p.first = player;
    p.second = seats;

    if(plays_.find(play_name) != plays_.end())
    {
        plays_.at(play_name).push_back(p);
    } else
    {
        vector<pair<string, string> > tmp;
        tmp.push_back(p);

        plays_.insert({play_name, tmp});
    }
}

string Theatre::get_name() const
{
    return name_;
}

string Theatre::format_play_name(const string& name, const string& delimiter) const
{
    string n = "";

    // if '/' character is found splits the string into the corresponding names
    if(name.find('/') != string::npos)
    {
        string tmp1 = name.substr(0, name.find('/'));
        string tmp2 = name.substr(name.find('/') + 1, name.length());

        n = tmp1 + delimiter + tmp2;
    } else
    {
        n = name;
    }

    return n;
}

set<string> Theatre::get_play_names() const
{
    set<string> play_names;

    for(const auto& play: plays_)
    {
        string name = format_play_name(play.first, " *** ");
        play_names.insert(name);
    }

    return play_names;
}

bool Theatre::is_play_in_theatre(const string& name) const
{
    for(const auto& play: plays_)
    {
        string n = play.first;
        size_t f = n.find("/");

        // Case where the name contains '/' and we want to check if the alias match the given name
        if(f != string::npos)
        {
            string tmp1 = n.substr(0, n.find('/'));
            string tmp2 = n.substr(n.find('/') + 1, n.length());

            if(name == tmp1 || name == tmp2)
            {
                return true;
            } else
            {
                return false;
            }
        }

        if(name == play.first)
        {
            return true;
        }
    }

    return false;
}

set<string> Theatre::get_free_seat_plays() const
{
    set<string> free_seat_plays;

    for(const auto& play: plays_)
    {
        for(int i = play.second.size() - 1; i >= 0; i--)
        {
            // Checks if the last play has no seats available. In that case we have to consider the next one
            if(play.second.back().second == "none")
            {
                break;
            }

            if(play.second.at(i).second != "none")
            {
                // Construct the final output string
                string name = format_play_name(play.first, " --- ");
                string result = name_ + " : " + name + " : " + play.second.at(i).second;

                free_seat_plays.insert(result);
                break;
            }
        }
    }

    return free_seat_plays;
}

vector<string> Theatre::get_play_alias(const string& name) const
{
    vector<string> alias;

    size_t found = name.find("/");

    // '/' character is found
    if(found != string::npos)
    {
        // Splits the string into the corresponding parts
        string tmp1 = name.substr(0, name.find('/'));
        string tmp2 = name.substr(name.find('/') + 1, name.length());

        alias.push_back(tmp1);
        alias.push_back(tmp2);
    } else
    {
        alias.push_back(name);
    }

    return alias;
}

set<string> Theatre::get_player_names(const string& play_name) const
{
    set<string> player_names;

    // Iterates over all plays
    for(const auto& play: plays_)
    {
        // Iterates over all pairs of <player_name, available_seats>
        for(const auto& p: play.second)
        {
            // Constructs final output string
            string result = name_ + " : ";
            if(play.first == play_name)
            {
                size_t found = play.first.find("/");
                if(found != string::npos)
                {
                    break;
                } else
                {
                    result += p.first;
                    player_names.insert(result);
                }
            } else
            {
                vector<string> alias = get_play_alias(play.first);

                if(play_name == alias[0] || play_name == alias[1])
                {
                    result += p.first;
                    player_names.insert(result);
                }
            }
        }
    }

    return player_names;
}
