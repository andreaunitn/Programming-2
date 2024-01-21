/* yatzy
 *
 * Desc:
 *   This file implement the main logic of the game yatzi. In particular
 *   it defines the actions that a player can do and several utility
 *   methods for managing the game. The functionalitis implemented include:
 *   the possibility of creating and adding new players, give the turn to next one,
 *   reporting the winner/s, reset the game, rolling the dices reporting the
 *   player status and update its points.
 *   To implement such actions it uses methods offered by the "functions.hh"
 *   interface.
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

#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <string>
#include <vector>

// Obvious constants
const int INITIAL_NUMBER_OF_ROLLS = 3;
const int NUMBER_OF_DICES = 5;

const int INITIAL_NUMBER_OF_PLAYERS = 2;

// Data of each player
struct Player
{
    unsigned int id_;
    unsigned int rolls_left_;
    std::vector<int> latest_point_values_;
    std::vector<int> best_point_values_;
    std::vector<bool> dices_locked_;
};

class GameEngine
{
public:
    // Constructor
    GameEngine();

    // Destructor
    ~GameEngine();

    // Adds a new player
    void add_player(const Player player);

    // Prints guide text, telling which player is in turn and how many trials
    // they have left.
    void update_guide() const;

    // Gives turn for the next player having turns left, i.e. for the next
    // element in the players_ vector. After the last one, turn is given for
    // the second one (since the first one is NOBODY).
    void give_turn();

    // Reports a winner based on the current situation and sets the game_over_
    // attribute as true.
    std::string report_winner();

    // Tells if the game is over, i.e. if all players have used all their
    // turns.
    bool is_game_over() const;

    // Creates INITIAL_NUMBER_OF_PLAYERS players and adds it to the game
    void create_players();

    // Returns the player that is currently in turn
    Player& get_player_turn();

    // Resets the game, i.e. set game_over_ to false and sets the player's
    // attributes to their initial values
    void reset_game();

    // Rolls all dices left, i.e. draws a new series of face numbers for the player
    // currently in turn. Moreover, reports the winner, if after the draw, all
    // players have used all their turns.
    void roll(const unsigned int dices_left);

    // Returns the number of dices left for the current player
    unsigned int get_dices_left();

private:
    // Reports the status of the player currently in turn
    void report_player_status() const;

    // Updates best and latest points of the player in turn:
    // latest_point_values_ will always be new_points,
    // best_point_values_ will be new_points, if the last_mentioned is better.
    void update_points(const std::vector<int>& new_points);

    // Returns true if all turns of all players have been used,
    // otherwise returns false.
    bool all_turns_used() const;

    // Vector of all players
    std::vector<Player> players_;

    // Tells the player currently in turn (index of players_ vector)
    unsigned int game_turn_;

    // Tells if the game is over
    bool game_over_;
};

#endif // GAMEENGINE_HH
