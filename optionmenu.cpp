#include "optionmenu.h"

#include <QFile>
#include <QMessageBox>
#include <QSoundEffect>
#include <QAudio>

OptionMenu::OptionMenu(QWidget *parent) : QWidget(parent)
{
    soundVolume = 0.5;
    optionMenu = new QGridLayout (this);

    difficulty = new QComboBox ();

    retourMainMenu = new QPushButton ("Return");
    resetScoreboard = new QPushButton ("Reset scoreboard");
    soundSlider = new QSlider;
    displaySoundValue = new QLabel;

    //set difficulty choice
    const QStringList diffChoices = {"Easy", "Normal", "Difficult"};
    difficulty->addItems(diffChoices);
    difficulty->setCurrentIndex(1);

    //sound slider setup
    soundSlider->setOrientation(Qt::Orientation::Horizontal);
    soundSlider->setRange(0, 100);
    soundSlider->setValue( (int)soundVolume * 100);
    displaySoundValue->setText( QString::number((int)soundVolume * 100) + "%");
    displaySoundValue->setAlignment(Qt::AlignCenter);

    connect (soundSlider, &QSlider::valueChanged, this, &OptionMenu::change_sound_volume);

    //set grid layout
    optionMenu->addWidget(difficulty, 0, 0, 1, 3);
    optionMenu->addWidget(resetScoreboard, 1, 1, 1, 1);
    optionMenu->addWidget(displaySoundValue, 2, 0, 1, 1);
    optionMenu->addWidget(soundSlider, 2, 1, 1, 2);
    optionMenu->addWidget(retourMainMenu, 3, 2, 1, 1);

    connect (resetScoreboard, &QPushButton::pressed, this, &OptionMenu::display_remove_confirmation);
}

void OptionMenu::connectReturnButton ( const QObject *receiver, const char * slotMemberFunction ) {
    //called by MainWindow to activate return button
    connect (retourMainMenu, SIGNAL(pressed()), receiver, slotMemberFunction);
}

int OptionMenu::get_difficulty() {
    return difficulty->currentIndex();
}

qreal OptionMenu::get_sound_volume () {
    return soundVolume;
}

/*
 * SLOTS
 */

void OptionMenu::change_sound_volume (int value) {
    soundVolume = QAudio::convertVolume(value / (qreal)100.0,
                                        QAudio::VolumeScale::LinearVolumeScale,
                                        QAudio::VolumeScale::LogarithmicVolumeScale
                                        );
    displaySoundValue->setText( QString::number(value) + "%");
    emit signal_sound_volume_changed ();
}

void OptionMenu::display_remove_confirmation () {   //display infoBoxes when user want to remove scoreboards
    if (QFile::exists ("scores.csv")) {  //file exists so remove it
        QMessageBox mess (QMessageBox::Icon::Warning,
                          "Attention", "Are you sure ? This will remove all saved scores !",
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
                          "Info", "Saved scores already empty",
                          QMessageBox::StandardButton::Ok , this);
        mess.exec();
    }
}

