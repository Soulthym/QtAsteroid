#include "optionmenu.h"

#include <QFile>
#include <QMessageBox>

OptionMenu::OptionMenu(QWidget *parent) : QWidget(parent)
{
    optionMenu = new QGridLayout (this);

    difficulty = new QComboBox ();

    apply = new QPushButton ("Apply changes");
    retourMainMenu = new QPushButton ("Return");
    resetScoreboard = new QPushButton ("Reset scoreboard");

    const QStringList diffChoices = {"Noob", "GitGud", "Noice", "Casual"};
    difficulty->addItems(diffChoices);

    optionMenu->addWidget(difficulty, 0, 0, 1, 3);
    optionMenu->addWidget(resetScoreboard, 1, 1, 1, 1);
    optionMenu->addWidget(apply, 3, 0, 1, 1);
    optionMenu->addWidget(retourMainMenu, 3, 2, 1, 1);

    connect (resetScoreboard, &QPushButton::pressed, this, &OptionMenu::display_remove_confirmation);
}

void OptionMenu::connectReturnButton ( const QObject *receiver, const char * slotMemberFunction ) {
    //called by MainWindow to activate return button
    connect (retourMainMenu, SIGNAL(pressed()), receiver, slotMemberFunction);
}


/*
 * SLOTS
 */

void OptionMenu::display_remove_confirmation () {

    if (QFile::exists ("score.csv")) {  //file exists so remove it
        QMessageBox mess (QMessageBox::Icon::Warning,
                          "Attention", "Are you sure ? This will remove all saved scores",
                          QMessageBox::StandardButton::Cancel |
                          QMessageBox::StandardButton::Yes , this);
        int res = mess.exec();
        switch (res) {
            case QMessageBox::Yes :
            case QMessageBox::Ok :
                QFile::remove("score.csv");
            break;

            default :
            break;
        }
    }
    else {  //file does not exist
        QMessageBox mess (QMessageBox::Icon::Information,
                          "Info", "There is no scoreboard file",
                          QMessageBox::StandardButton::Ok , this);
        mess.exec();
    }
}

