#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>

class OptionMenu : public QWidget
{
    Q_OBJECT
public:
    explicit OptionMenu(QWidget *parent = nullptr);
    void connectReturnButton ( const QObject *receiver, const char * slotMemberFunction );

signals:

public slots:

private :
    QGridLayout *optionMenu;
    QComboBox *difficulty;
    QPushButton *apply;    //apply changes and back to main menu
    QPushButton *retourMainMenu;    //return to main menu
};

#endif // OPTIONMENU_H
