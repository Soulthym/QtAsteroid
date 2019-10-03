#include "optionmenu.h"

OptionMenu::OptionMenu(QWidget *parent) : QWidget(parent)
{
    optionMenu = new QGridLayout (this);

    difficulty = new QComboBox ();
    apply = new QPushButton ("Apply changes");
    retourMainMenu = new QPushButton ("Return");

    const QStringList diffChoices = {"Noob", "GitGud", "Noice", "Casual"};
    difficulty->addItems(diffChoices);

    optionMenu->addWidget(difficulty, 0, 1, 1, 2);
    optionMenu->addWidget(apply, 3, 0, 1, 1);
    optionMenu->addWidget(retourMainMenu, 3, 2, 1, 1);
}

void OptionMenu::connectReturnButton ( const QObject *receiver, const char * slotMemberFunction ) {
    connect (retourMainMenu, SIGNAL(pressed()), receiver, slotMemberFunction);
}
