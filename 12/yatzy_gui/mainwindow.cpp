/*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 *
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), seconds_(0), minutes_(0)
{
    ui->setupUi(this);

    // Adding dices to the dice's vector
    dices_.push_back(ui->dice_1);
    dices_.push_back(ui->dice_2);
    dices_.push_back(ui->dice_3);
    dices_.push_back(ui->dice_4);
    dices_.push_back(ui->dice_5);

    // Adding the lock buttons to the lock button's vector
    lock_buttons_.push_back(ui->lock_button_1);
    lock_buttons_.push_back(ui->lock_button_2);
    lock_buttons_.push_back(ui->lock_button_3);
    lock_buttons_.push_back(ui->lock_button_4);
    lock_buttons_.push_back(ui->lock_button_5);

    init_game();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game_;
    delete timer_;
}

void MainWindow::on_reset_clicked()
{
    // GameEngine part
    // Reset game and players
    game_->reset_game();

    // UI part
    // Reset dices
    for(QLabel* dice: dices_)
    {
        dice->clear();
    }

    // Reset lock buttons
    for(QPushButton* lock_button: lock_buttons_)
    {
        lock_button->setEnabled(false);
    }

    // Reset new roll and next player buttons
    ui->new_roll->setEnabled(true);
    ui->next_player->setEnabled(true);

    // Reset player info
    set_player_labels(game_->get_player_turn());

    // Reset winner
    ui->winner->setText("");

    // Reset timer
    reset_timer();

    // Reset background color
    this->setStyleSheet("QMainWindow {background-color: light gray;}");
}


void MainWindow::on_lock_button_1_clicked()
{
    Player& player = game_->get_player_turn();
    player.dices_locked_.at(0) = false;
    lock_buttons_.at(0)->setEnabled(false);
}


void MainWindow::on_lock_button_2_clicked()
{
    Player& player = game_->get_player_turn();
    player.dices_locked_.at(1) = false;
    lock_buttons_.at(1)->setEnabled(false);
}


void MainWindow::on_lock_button_3_clicked()
{
    Player& player = game_->get_player_turn();
    player.dices_locked_.at(2) = false;
    lock_buttons_.at(2)->setEnabled(false);
}


void MainWindow::on_lock_button_4_clicked()
{
    Player& player = game_->get_player_turn();
    player.dices_locked_.at(3) = false;
    lock_buttons_.at(3)->setEnabled(false);
}


void MainWindow::on_lock_button_5_clicked()
{
    Player& player = game_->get_player_turn();
    player.dices_locked_.at(4) = false;
    lock_buttons_.at(4)->setEnabled(false);
}


void MainWindow::on_next_player_clicked()
{
    // GameEngine part
    // Give the turn to the next player
    game_->give_turn();
    Player& player = game_->get_player_turn();

    // UI part
    set_player_labels(player);

    // Set dices figures value and lock buttons accordingly
    for(int i = 0; i < NUMBER_OF_DICES; i++)
    {
        if(player.dices_locked_.at(i))
        {
            dices_.at(i)->clear();
        } else
        {
            // Converting image (png) to pixmap
            std::string filename = PREFIX + image_names.at(player.latest_point_values_.at(i) - 1) + SUFFIX;
            QPixmap image(QString::fromStdString(filename));

            // Scaling the pixmap
            image = image.scaled(DICE_SIZE, DICE_SIZE);

            // Setting the pixmap for the dice label
            dices_.at(i)->setGeometry(MARGIN + i * (DICE_SIZE + MARGIN) + OFFSET_X, MARGIN + OFFSET_Y, DICE_SIZE + OFFSET_Y, DICE_SIZE);
            dices_.at(i)->setPixmap(image);
        }

        lock_buttons_.at(i)->setEnabled(false);
    }

    // Set new roll button
    if(ui->num_rolls_left->text() == "0")
    {
        ui->new_roll->setEnabled(false);
    } else
    {
        ui->new_roll->setEnabled(true);
    }
}


void MainWindow::on_new_roll_clicked()
{
    Player& player = game_->get_player_turn();

    // Set lock buttons for the current player
    for(int i = 0; i < NUMBER_OF_DICES; i++)
    {
        lock_buttons_.at(i)->setEnabled(player.dices_locked_.at(i));
    }

    // Roll dices
    game_->roll(game_->get_dices_left());

    // Draw images for the dices
    draw_dices(player);

    // Adjust labels and buttons
    ui->num_rolls_done->setText(QString::number(INITIAL_NUMBER_OF_ROLLS - player.rolls_left_));
    ui->num_rolls_left->setText(QString::number(player.rolls_left_));

    // If there are no rolls left disable new roll button
    if(ui->num_rolls_left->text() == "0")
    {
        ui->new_roll->setEnabled(false);
    }

    // Check if the game is over
    if(game_->is_game_over())
    {
        // Update labels based on the winner
        ui->winner->setText(QString::fromStdString(game_->report_winner()));

        // Stop timer
        timer_->stop();

        // Disable next roll and next player buttons
        ui->new_roll->setEnabled(false);
        ui->next_player->setEnabled(false);

        // Set background color
        this->setStyleSheet("QMainWindow {background-color: #D1FFBD;}");
    }
}

void MainWindow::init_game()
{
    // GameEngine part
    game_ = new GameEngine();

    // Create players
    game_->create_players();

    // Give turn to the first player and set player's label
    Player& player = game_->get_player_turn();
    set_player_labels(player);

    // UI part
    // Initialize dices labels
    for(QLabel* dice: dices_)
    {
        dice->clear();
    }

    // Set initial state for lock buttons
    for(QPushButton* lock_button: lock_buttons_)
    {
        lock_button->setEnabled(false);
    }

    // Set number of players
    ui->num_of_players->setText(QString::number(INITIAL_NUMBER_OF_PLAYERS));

    // Start timer
    timer_ = new QTimer();
    timer_->start(TIMEOUT);
    connect(timer_, &QTimer::timeout, this, &MainWindow::update_timer);
}

void MainWindow::update_timer()
{
    seconds_++;

    if(seconds_ >= 60)
    {
        minutes_++;
        seconds_ = 0;
    }

    // Update ui elements
    ui->lcd_number_sec->display(seconds_);
    ui->lcd_number_min->display(minutes_);
}

void MainWindow::reset_timer()
{
    seconds_ = 0;
    minutes_ = 0;

    if(!timer_->isActive())
    {
        timer_->start(TIMEOUT);
    }

    // Update ui elements
    ui->lcd_number_sec->display(0);
    ui->lcd_number_min->display(0);
}

void MainWindow::set_player_labels(Player& player)
{
    ui->player_in_turn->setText(QString::number(player.id_));
    ui->num_rolls_done->setText(QString::number(INITIAL_NUMBER_OF_ROLLS - player.rolls_left_));
    ui->num_rolls_left->setText(QString::number(player.rolls_left_));
}

void MainWindow::draw_dices(Player& player)
{
    for(int i = 0; i < NUMBER_OF_DICES; i++)
    {
        // Converting image (png) to pixmap
        std::string filename = PREFIX + image_names.at(player.latest_point_values_.at(i) - 1) + SUFFIX;
        QPixmap image(QString::fromStdString(filename));

        // Scaling the pixmap
        image = image.scaled(DICE_SIZE, DICE_SIZE);

        // Setting the pixmap for the dice label
        dices_.at(i)->setGeometry(MARGIN + i * (DICE_SIZE + MARGIN) + OFFSET_X, MARGIN + OFFSET_Y, DICE_SIZE + OFFSET_Y, DICE_SIZE);
        dices_.at(i)->setPixmap(image);
    }
}

