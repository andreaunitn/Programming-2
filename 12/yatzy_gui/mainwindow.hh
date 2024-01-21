/* yatzy GUI
 *
 * Desc:
 *   This file implements the Graphics User Interface of the game yatzy.
 *   It defines all the elements and the interactions with the user, like
 *   rolling the dices, switching players, lock dices and restart the
 *   game.
 *   Moreover, it uses the functions made available by the GameEngine
 *   interface to performs the required actions.s
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

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameengine.hh"
#include "functions.hh"
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLabel>

const int TIMEOUT = 1000;

// Names for images
const std::vector<std::string> image_names = {"1", "2", "3", "4", "5", "6"};

const std::string PREFIX(":/images/");
const std::string SUFFIX(".png");

// Constants for the visualization of the dice images
const int MARGIN = 35;
const int DICE_SIZE = 80;
const int OFFSET_X = 30;
const int OFFSET_Y = 100;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Resets all the labels, button and the timer
    void on_reset_clicked();

    // Locks dice 1
    void on_lock_button_1_clicked();

    // Locks dice 2
    void on_lock_button_2_clicked();

    // Locks dice 3
    void on_lock_button_3_clicked();

    // Locks dice 4
    void on_lock_button_4_clicked();

    // Locks dice 5
    void on_lock_button_5_clicked();

    // Changes player in turn, update the player's labels the dices and the lock buttons
    void on_next_player_clicked();

    // Performs a new roll of the dices (if possible) and update the corresponding dice images
    void on_new_roll_clicked();

private:
    // Initializes the game and sets all the ui parts with the "default" values
    void init_game();

    // Update seconds and minutes of the timer
    void update_timer();

    // Set the minutes and seconds of the timer to 0
    void reset_timer();

    // Sets the player id, the number of rolls done and the number of rolls left
    void set_player_labels(Player& player);

    // Draws the images of the dices
    void draw_dices(Player& player);

    Ui::MainWindow *ui;

    GameEngine* game_;
    QTimer* timer_;

    std::vector<QLabel*> dices_;
    std::vector<QPushButton*> lock_buttons_;

    int seconds_;
    int minutes_;
};

#endif // MAINWINDOW_HH
