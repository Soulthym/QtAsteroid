#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "QVBoxLayout"
#include "QLabel"
#include "QPushButton"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void link_events ();    //link button events

private:
    //declare windows pointers here
    QWidget *layoutContainerWitget;

    QVBoxLayout *choicesLayout;

    QPushButton *quitButton;

    QPushButton *startButton;
    QPushButton *scoreboardButton;
    QPushButton *optionsButton;

    QLabel *gameTitle;
};

#endif // MAINWINDOW_H
