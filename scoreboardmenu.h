#ifndef SCOREBOARDMENU_H
#define SCOREBOARDMENU_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QHeaderView>
#include <QPushButton>

class ScoreBoardMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreBoardMenu(QWidget *parent = nullptr);

    void loadCsv(const QString filename, QTableWidget *table);

signals:

public slots:

private:
    QVBoxLayout *topLayout;
    QHBoxLayout *buttonPanel;
    QTableWidget *table;
    QPushButton *exitButton;
    QPushButton *clearButton;

};

#endif // SCOREBOARDMENU_H
