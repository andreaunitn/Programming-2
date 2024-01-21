 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 */

#include "gameboard.hh"
#include <iostream>
#include <cmath>

GameBoard::GameBoard(char fill_character): fill_character_(fill_character)
{
    init_board();

    pieces_left_ = NUMBER_OF_NON_EMPTY_PIECES;
    moves_ = 0;
}

void GameBoard::init_board()
{
    board_.resize(SIZE);

    for(unsigned int i = 0; i < SIZE; ++i)
    {   
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            if((i >= 2 && i <= 5) && (j >= 2 && j <= 5))
            {
                board_.at(i).push_back(' ');
            } 
            else
            {
                board_.at(i).push_back(fill_character_);
            }
        }
    }
}

bool GameBoard::is_game_finished() const
{
    return pieces_left_ == 1;
}

void GameBoard::make_move(unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y)
{
    // Computes coordinates for the middle point between starting and destination points
    int diagonal_x = static_cast<int>(dst_x) - static_cast<int>(src_x);
    int diagonal_y = static_cast<int>(dst_y) - static_cast<int>(src_y);
    int step_x = (diagonal_x > 0) ? 1 : -1;
    int step_y = (diagonal_y > 0) ? 1 : -1;

    // Replaces starting, middle and destination points with the correct character 
    board_.at(src_y).at(src_x) = ' ';
    board_.at(src_y + step_y).at(src_x + step_x) = ' ';
    board_.at(dst_y).at(dst_x) = fill_character_;

    // Updates game info
    pieces_left_ -= 1;
    moves_ += 1;
}

bool GameBoard::is_move_possible(unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y) const
{
    // Checks if starting and destination points in the board contain the correct character
    if((board_.at(src_y).at(src_x) != fill_character_) || (board_.at(dst_y).at(dst_x) != ' '))
    {
        return false;
    }

    // Computes coordinates for the middle point and checks if it contains a filling character
    int diagonal_x = static_cast<int>(dst_x) - static_cast<int>(src_x);
    int diagonal_y = static_cast<int>(dst_y) - static_cast<int>(src_y);

    if(abs(diagonal_x) != abs(diagonal_y))
    {
        return false;
    }

    int step_x = (diagonal_x > 0) ? 1 : -1;
    int step_y = (diagonal_y > 0) ? 1 : -1;
    unsigned int x = src_x + step_x;
    unsigned int y = src_y + step_y;
    int middlecount = 0;

    while(x != dst_x || y != dst_y)
    {
        if(board_.at(y).at(x) == fill_character_)
        {
            middlecount++;
        } else 
        {
            return false;
        }

        x += step_x;
        y += step_y;
    }

    return middlecount == 1;
}

void GameBoard::print_stats() const
{
    std::cout << moves_ << " move(s) made." << std::endl;
    std::cout << pieces_left_ << " piece(s) left." << std::endl;

}

void GameBoard::print() const
{
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            // Print here empty or the element (i, j) in the gameboard
            std::cout << board_.at(i).at(j) << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}
