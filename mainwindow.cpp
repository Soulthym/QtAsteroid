#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{    //instatiate other windows here
    setMinimumWidth(500);
    setMinimumHeight(400);

    create_main_menu ();
    mainGame = new AsteroidGame (parent);
    optionMenu = new OptionMenu (parent);
    scoreboardMenu = new ScoreBoardMenu (parent);

    link_events ();

    setCentralWidget(mainMenu);
}

void MainWindow::create_main_menu () {
    //Allocations
    mainMenu = new QWidget (this);
    choicesLayout = new QVBoxLayout (mainMenu);

    quitButton = new QPushButton ("Quit", mainMenu);
    startButton = new QPushButton ("Start", mainMenu);
    scoreboardButton = new QPushButton ("Score board", mainMenu);
    optionsButton = new QPushButton ("Options", mainMenu);

    gameTitle = new QLabel ("AsQtroids", mainMenu);

    //set QLabel
    gameTitle->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
   // gameTitle->setScaledContents(true);
    gameTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QFont font = gameTitle->font();
    font.setPointSize(72);
    font.setBold(true);
    gameTitle->setFont(font);

    QSpacerItem *test;
    test = new QSpacerItem (20, 40);

    //set layout
    choicesLayout->setSizeConstraint(QLayout::SetMinimumSize);

    choicesLayout->addWidget(gameTitle);
    choicesLayout->addWidget(startButton);
    choicesLayout->addWidget(scoreboardButton);
    choicesLayout->addWidget(optionsButton);
    choicesLayout->addSpacerItem(test);
    choicesLayout->addWidget(quitButton);

    mainMenu->setLayout(choicesLayout);
}

void MainWindow::link_events (){    //button event linking
    connect(quitButton, &QPushButton::pressed, this, &QMainWindow::close);
    connect(startButton, &QPushButton::pressed, this, &MainWindow::start_game);
    connect(optionsButton, &QPushButton::pressed, this, &MainWindow::display_option_menu);
    connect(scoreboardButton, &QPushButton::pressed, this, &MainWindow::display_scoreboard_menu);
}


/*
 *      SLOTS
 */

void MainWindow::start_game() {
    mainMenu = takeCentralWidget();
    setCentralWidget(mainGame);
}

void MainWindow::display_option_menu() {
    mainMenu = takeCentralWidget();
    setCentralWidget(optionMenu);
}

void MainWindow::display_scoreboard_menu() {
    mainMenu = takeCentralWidget();
    setCentralWidget(scoreboardMenu);
}

