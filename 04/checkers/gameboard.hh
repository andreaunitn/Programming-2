 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>

using Board = std::vector<std::vector<char> >;

// Size of the gameboard
const unsigned int SIZE = 8;

// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// Number of non empty pieces on the board at the beginning
const unsigned int NUMBER_OF_NON_EMPTY_PIECES = (SIZE * SIZE) - 16;

// GameBoard class
class GameBoard
{
public:
    // Constructor. It receives as parameter the game board's filling character
    GameBoard(char fill_character);

    // Checks if the game is over
    bool is_game_finished() const;

    // Make a move given the coordinates of the starting (src_x, src_y) and destination point (dst_x, dst_y)
    void make_move(unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y);

    // Checks if it's possible to make a move given the coordinates of the starting point (src_x, src_y) and destination point (dst_x, dst_y)
    bool is_move_possible(unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y) const;

    // Prints the number of pieces left and the number of moves made
    void print_stats() const;

    // Prints the gameboard
    void print() const;

private:
    char fill_character_;
    Board board_;
    unsigned int pieces_left_;
    unsigned int moves_;

    // Initializes the game board with the correct characters
    void init_board();

    // Prints a line with the given length and fill character
    void print_line(unsigned int length, char fill_character) const;
};

#endif // GAMEBOARD_HH
