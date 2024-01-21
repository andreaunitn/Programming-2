/*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 *
 * */

#include "gameengine.hh"
#include "functions.hh"
#include <iostream>
#include <sstream>

GameEngine::GameEngine():
    game_turn_(0), game_over_(false)
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::add_player(const Player player)
{
    players_.push_back(player);
}

void GameEngine::update_guide() const
{
    if(players_.size() <= game_turn_)
    {
        std::cout << "Internal error: update_guide" << std::endl;
        return;
    }
    ostringstream outputstream{""};
    outputstream << "Player " << game_turn_ + 1 << " in turn, "
                 << players_.at(game_turn_).rolls_left_ << " trials left!";
    std::cout << outputstream.str() << std::endl;
}

void GameEngine::give_turn()
{
    // Searching for the next player among those, whose id_ is greater than
    // that of the current player
    for ( unsigned int i = game_turn_ + 1; i < players_.size(); ++i )
    {
        if ( players_.at(i).rolls_left_ > 0 )
        {
            game_turn_ = i;
            return;
        }
    }

    // A suitable next player couldn't be found in the previous search, so
    // searching for the next player among those, whose id_ is less than
    // or equal to that of the current player
    // (perhaps the current player is the only one having turns left)
    for(unsigned int i = 0; i <= game_turn_; ++i)
    {
        if(players_.at(i).rolls_left_ > 0)
        {
            game_turn_ = i;
            return;
        }
    }

    // No player has turns left
    report_winner();
}

std::string GameEngine::report_winner()
{
    vector<vector<int>> all_point_values;
    for ( auto player : players_ )
    {
        all_point_values.push_back(player.best_point_values_);
    }
    string winner_text = decide_winner(all_point_values);
    std::cout << winner_text << std::endl;
    game_over_ = true;

    return winner_text;
}

bool GameEngine::is_game_over() const
{
    return game_over_;
}

void GameEngine::create_players()
{
    for(int i = 0; i < INITIAL_NUMBER_OF_PLAYERS; i++)
    {
        Player p;
        p.id_= i + 1;
        p.rolls_left_ = INITIAL_NUMBER_OF_ROLLS;
        p.dices_locked_ = std::vector<bool>(NUMBER_OF_DICES, true);
        add_player(p);
    }
}

Player& GameEngine::get_player_turn()
{
    return players_.at(game_turn_);
}

void GameEngine::reset_game()
{
    game_over_ = false;

    // Resetting players
    for(Player& p: players_)
    {
        p.rolls_left_ = INITIAL_NUMBER_OF_ROLLS;
        p.latest_point_values_.clear();
        p.best_point_values_.clear();
        p.dices_locked_.clear();
        p.dices_locked_ = std::vector<bool>(NUMBER_OF_DICES, true);
    }
}

void GameEngine::roll(const unsigned int dices_left)
{
    if(players_.size() <= game_turn_)
        {
            std::cout << "Internal error: roll" << std::endl;
            return;
        }

        if(players_.at(game_turn_).rolls_left_ == 0)
        {
            std::cout << "No more rolls left" << std::endl;
            return;
        }

        ostringstream outputstream{""};
        vector<int> tmp;
        vector<int> new_points;
        unsigned int dice = 0;

        while(dice < dices_left)
        {
            int point_value = roll_dice();
            tmp.push_back(point_value);

            ++dice;
        }

        Player& player = players_.at(game_turn_);

        int j = 0;
        for(int i = 0; i < NUMBER_OF_DICES; i++)
        {
            if(player.dices_locked_.at(i))
            {
                new_points.push_back(tmp.at(j));
                j++;

            } else
            {
                new_points.push_back(player.latest_point_values_.at(i));
            }
        }

        player.best_point_values_ = new_points;

        update_points(new_points);
        report_player_status();

        // Decreasing rolls left
        --players_.at(game_turn_).rolls_left_;

        // Checking if the player in turn has rolls left
        if ( players_.at(game_turn_).rolls_left_ == 0 )
        {
            outputstream << "Turn of " << players_.at(game_turn_).id_
                         << " has ended!";
            std::cout << outputstream.str() << std::endl;
        }

        // Checking if any player has turns left
        if ( all_turns_used() )
        {
            report_winner();
        }
}

unsigned int GameEngine::get_dices_left()
{
    unsigned int dices_left = NUMBER_OF_DICES;
    Player player = players_.at(game_turn_);

    for(int i = 0; i < NUMBER_OF_DICES; i++)
    {
        // If the dice is not locked it means that it can be used
        if(!player.dices_locked_.at(i))
        {
            dices_left--;
        }
    }

    return dices_left;
}

void GameEngine::report_player_status() const
{
    if ( players_.size() <= game_turn_ )
    {
        std::cout << "Internal error: report_player_status" << std::endl;
        return;
    }
    string textual_description = "";
    construe_result(players_.at(game_turn_).latest_point_values_,
                    textual_description);
    std::cout << textual_description << std::endl;
}

void GameEngine::update_points(const std::vector<int>& new_points)
{
    if ( players_.size() <= game_turn_ )
    {
        std::cout << "Internal error: update_points" << std::endl;
        return;
    }
    string dummy = "";
    int new_result = construe_result(new_points, dummy);
    int best_result_so_far
            = construe_result(players_.at(game_turn_).best_point_values_,
                              dummy);
    if ( new_result > best_result_so_far )
    {
        players_.at(game_turn_).best_point_values_ = new_points;
    }
    players_.at(game_turn_).latest_point_values_ = new_points;
}

bool GameEngine::all_turns_used() const
{
    for ( auto player : players_ )
    {
        if ( player.rolls_left_ > 0 )
        {
            return false;
        }
    }
    return true;
}
