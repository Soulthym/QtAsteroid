#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>

class OptionMenu : public QWidget
{
    Q_OBJECT
public:
    explicit OptionMenu(QWidget *parent = nullptr);
    void connectReturnButton ( const QObject *receiver, const char * slotMemberFunction );
    int get_difficulty ();      //return choosen difficulty
    qreal get_sound_volume ();  //return sound volume

signals:
    void signal_sound_volume_changed (qreal newSoundVolume);
    void difficulty_changed (int index);

public slots:
    void display_remove_confirmation ();
    void change_sound_volume (int value);
    void change_difficulty (int index);

private :
    QGridLayout *optionMenu;
    QLabel *optionMenuTitle;

    QComboBox *difficulty;
    QLabel *diffLabel;

    QLabel *displaySoundValue;
    QSlider *soundSlider;

    QPushButton *resetScoreboard;   //remove the score file
    QPushButton *retourMainMenu;    //return to main menu

    qreal soundVolume;
};

#endif // OPTIONMENU_H
