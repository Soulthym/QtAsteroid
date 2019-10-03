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
    choicesLayout = new QGridLayout (mainMenu);

    quitButton = new QPushButton ("Quit", mainMenu);
    startButton = new QPushButton ("Start", mainMenu);
    scoreboardButton = new QPushButton ("Score board", mainMenu);
    optionsButton = new QPushButton ("Options", mainMenu);

    gameTitle = new QLabel ("AsQtroids", mainMenu);

    //set QLabel
    gameTitle->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
    gameTitle->setScaledContents(true);

    QFont font = gameTitle->font();
    font.setPointSize(72);
    font.setBold(true);
    gameTitle->setFont(font);

    //set layout
    choicesLayout->setSizeConstraint(QLayout::SetMinimumSize);
    for(int i=0; i<7; i++)
        choicesLayout->setRowStretch(i, 1);

    choicesLayout->addWidget(gameTitle, 0, 0, 1, 3);
    choicesLayout->addWidget(startButton, 2, 1, 1, 1);
    choicesLayout->addWidget(scoreboardButton, 3, 1, 1, 1);
    choicesLayout->addWidget(optionsButton, 4, 1, 1, 1);

    choicesLayout->addWidget(quitButton, 6, 0, 1, 1);

    mainMenu->setLayout(choicesLayout);
}

void MainWindow::link_events (){    //button event linking
    connect(quitButton, &QPushButton::pressed, this, &QMainWindow::close);
    connect(startButton, &QPushButton::pressed, this, &MainWindow::start_game);
    connect(optionsButton, &QPushButton::pressed, this, &MainWindow::display_option_menu);
    connect(scoreboardButton, &QPushButton::pressed, this, &MainWindow::display_scoreboard_menu);

    optionMenu->connectReturnButton(this, SLOT(option_return_to_main_menu()) );
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

void MainWindow::option_return_to_main_menu () {
    optionMenu = (OptionMenu*)takeCentralWidget();
    setCentralWidget(mainMenu);
}

