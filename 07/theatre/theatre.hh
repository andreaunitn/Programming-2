 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 */

#ifndef THEATRE_HH
#define THEATRE_HH

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Theatre class
class Theatre
{
public:
    // Constructor. It receives as parameter the name of the theatre
    Theatre(const string& name);

    // Returns theatre's name
    string get_name() const;

    // Inserts the given play, player and seats into the theatre class
    void insert_play(const string& play_name, const string& player, const string& seats);

    // Returns a set with all the plays
    set<string> get_play_names() const;

    // Checks if the given play is in the theatre
    bool is_play_in_theatre(const string& name) const;

    // Returns a set with all the plays that have available seats
    set<string> get_free_seat_plays() const;

    // Returns a set with the names of the players acting in the give play
    set<string> get_player_names(const string& play_name) const;

private:
    const string name_;

    // Data structure to store plays and their information
    map<string, vector<pair<string, string> > > plays_;

    // Returns the name of the play formatted with the given delimiter
    string format_play_name(const string& name, const string& delimiter) const;

    // Returns an array with the alias of the given play
    vector<string> get_play_alias(const string& name) const;
};

#endif // THEATRE_HH
