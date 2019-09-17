#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{    //instatiate other windows here
    setMinimumWidth(500);
    setMinimumHeight(400);

    //Allocations
    layoutContainerWitget = new QWidget (this);

    choicesLayout = new QVBoxLayout (layoutContainerWitget);

    quitButton = new QPushButton ("Quit", this);
    startButton = new QPushButton ("Start", this);
    scoreboardButton = new QPushButton ("Score board", this);
    optionsButton = new QPushButton ("Options", this);

    gameTitle = new QLabel ("AsQtroids", this);

    //set QLabel
    gameTitle->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    //set layout
    choicesLayout->addWidget(startButton);
    choicesLayout->addWidget(scoreboardButton);
    choicesLayout->addWidget(optionsButton);

    layoutContainerWitget->setLayout(choicesLayout);

    //place widgets
    layoutContainerWitget->setGeometry(170, 130, 160, 190);
    quitButton->setGeometry(40, 320, 50, 50);
    gameTitle->setGeometry(0, 80, 490, 50);

    link_events ();
}

void MainWindow::link_events (){
    //event linking
    connect(quitButton, &QPushButton::pressed, this, &QMainWindow::close);
}
