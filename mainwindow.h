#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "asteroidgame.h"
#include "scoreboardmenu.h"
#include "optionmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void start_game ();
    void display_option_menu ();
    void display_scoreboard_menu ();

    void option_return_to_main_menu ();
    void scoreboard_return_to_main_menu ();
    void game_return_to_main_menu(bool playerDead);

signals :

protected:
    void link_events ();    //link button events
    void create_main_menu ();

private:
    //declare windows pointers here
    AsteroidGame *mainGame;
    QWidget *mainMenu;
    OptionMenu *optionMenu;
    ScoreBoardMenu *scoreboardMenu;

    //Main menu display elements
    QGridLayout *choicesLayout;
    QPushButton *quitButton;
    QPushButton *startButton;
    QPushButton *scoreboardButton;
    QPushButton *optionsButton;
    QLabel *gameTitle;
};

#endif // MAINWINDOW_H
