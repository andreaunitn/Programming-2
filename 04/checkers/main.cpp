/* Checkers (for one player)
 *
 * Desc:
 *   This program implements a checkers game for one player. The size of
 * the gameboard is 8 x 8, and it will filled with empty spaces and
 * game pieces (character given by the user).
 *   At first, the gameboard is filled with pieces, but there is an
 * empty area of size 4 x 4 in the middle of the gameboard. The aim is to
 * remove pieces such that only one of them is left. A piece can be moved
 * diagonally over another piece, whereupon the piece that was skipped
 * will be removed.
 *   On each round, the user is asked for two points (four coordinates):
 * the piece to be moved and its target position. The program checks if
 * if the move is possible.
 *   The program terminates when there is only one piece left or if the
 * user gives a quitting command ('q' or 'Q'). In such case the program
 * prints the number of moves made and that of pieces left.
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

#include "gameboard.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Number of accepted input coordinates
const unsigned int INPUT_NUMBER = 4;

// Extracts the points from the command separated by the delimiter, converts it into numeric points and insert in into a vector. Return true if all operations are OK
bool extract_convert_points(const string& command, const char delimiter, vector<unsigned int>& points)
{
    // Extraction of points from command
    vector<string> str_points;

    int start = 0;
    int end = command.find(delimiter);

    while(end != -1)
    {
        str_points.push_back(command.substr(start, end - start));
        start = end + 1;
        end = command.find(delimiter, start);
    }
    str_points.push_back(command.substr(start, end - start));

    // Conversion of points into numeric values
    for(string coordinate: str_points)
    {
        if(coordinate.empty())
        {
            return false;
        }

        for(char digit: coordinate)
        {
            if(!isdigit(digit))
            {
                return false;
            }
        }
        points.push_back(stoi(coordinate));
    }

    // Checks if the number of given points is correct
    if(points.size() != INPUT_NUMBER)
    {
        return false;
    }

    return true;
}

// Checks if the given points are inside the game board
bool is_coordinates_inside_board(vector<unsigned int>& points)
{
    for(unsigned int point: points)
    {
        if(point < 1 || point > SIZE)
        {
            return false;
        }
    }
    return true;
}

// Checks if the given command and the vector of points respect the given contraints
bool is_command_valid(string& command, vector<unsigned int>& points)
{
    if(!extract_convert_points(command, ' ', points))
    {
        return false;
    }

    if(!is_coordinates_inside_board(points))
    {
        return false;
    }

    return true;
}

// Checks if the move using the given points is possible
bool can_move_to_destination(GameBoard& gameboard, vector<unsigned int>& points)
{
    unsigned int src_x = points.at(0) - 1;
    unsigned int src_y = points.at(1) - 1;
    unsigned int dst_x = points.at(2) - 1;
    unsigned int dst_y = points.at(3) - 1;
    return gameboard.is_move_possible(src_x, src_y, dst_x, dst_y);
}

int main()
{   
    // Reads piece character
    cout << "Enter piece character: ";

    string fill_character;
    getline(cin, fill_character);

    // Initializes gameboard object and prints the game board
    GameBoard gameboard(fill_character.at(0));
    gameboard.print();

    // While the game is not finished, asks for starting and destination points, make the move (if possible) and print the board
    while(!gameboard.is_game_finished())
    {
        cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";

        string command;
        getline(cin, command);

        if(command == "q" || command == "Q")
        {
            break;
        }

        vector<unsigned int> points;
        if(!is_command_valid(command, points))
        {
            cout << "Invalid start/destination point." << endl;
            continue;
        }

        if(!can_move_to_destination(gameboard, points))
        {
            cout << "Cannot move from start point to destination point." << endl;
            continue;
        }

        gameboard.make_move(points.at(0) - 1, points.at(1) - 1, points.at(2) - 1, points.at(3) - 1);
        gameboard.print();
    }

    // Prints the game statistics
    gameboard.print_stats();

    return 0;
}
