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
#include <QObject>

class ScoreBoardMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreBoardMenu(QWidget *parent = nullptr);
    void reloadCsv();
    void loadCsv(const QString filename, QTableWidget *table);
    void backToMenu(const QObject *receiver, const char *slotMemberFunction);

public slots:
    void clearCsv();
    
signals:

private:
    QString scoreFilename;
    QVBoxLayout *topLayout;
    QHBoxLayout *buttonPanel;
    QTableWidget *table;
    QPushButton *exitButton;
    QPushButton *clearButton;
};

#endif // SCOREBOARDMENU_H
